#pragma once

// CreateFile API
#include <stdio.h>
#include <windows.h>
#include <process.h>

int create_file_write()
{
  char enContent[] = "this is test content\r\n";
  char cnContent[] = "这是一个中文";

  HANDLE hFile = CreateFile(L"1.txt", GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, 0, NULL);
  if (INVALID_HANDLE_VALUE == hFile)
  {
    printf("Create file error\n");
    getchar();
    return 1;
  }

  WriteFile(hFile, enContent, strlen(enContent), NULL, NULL);
  FlushFileBuffers(hFile);
  CloseHandle(hFile);

  char enContent_r[255] = { 0 };
  hFile = CreateFile(L"1.txt", GENERIC_READ, 0, NULL, OPEN_ALWAYS, 0, NULL);
  if (INVALID_HANDLE_VALUE == hFile)
  {
    printf("Create file error\n");
    getchar();
    return 1;
  }
  ReadFile(hFile, enContent, 255, NULL, NULL);
  CloseHandle(hFile);
  printf("read conent:%s\n", enContent);

  return 0;
}

int read_write_chs()
{
  wchar_t chsContent[] = L"我是中文";
  DWORD writtenCount = 0;
  HANDLE hFile = CreateFile(L"中文.txt", GENERIC_WRITE | GENERIC_READ, 0, NULL, OPEN_ALWAYS, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
  if (INVALID_HANDLE_VALUE == hFile)
  {
    printf("Create file error 1, code:0x%x\n", GetLastError());
    return 1;
  }
  
  wchar_t head = 0xfeff;
  BOOL result = WriteFile(hFile, &head, sizeof(wchar_t), NULL, NULL);
  if (!result)
  {
    printf("WriteFile failed!!!");
    return 1;
  }

  result = WriteFile(hFile, chsContent, wcslen(chsContent)*sizeof(wchar_t), &writtenCount, NULL);
  if (!result)
  {
    printf("WriteFile failed!!!");
    return 1;
  }
  FlushFileBuffers(hFile);
  CloseHandle(hFile);

  hFile = CreateFile(L"中文.txt", GENERIC_WRITE | GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
  if (INVALID_HANDLE_VALUE == hFile)
  {
    printf("Create file error 2, code:0x%x\n", GetLastError());
    return 1;
  }
  
  // 移动两个字节，越过utf8的前两个字节0xfeff
  LARGE_INTEGER liMove;
  liMove.QuadPart = 2;
  SetFilePointerEx(hFile, liMove, NULL, FILE_BEGIN);

  wchar_t content_r[255] = { 0 };
  ReadFile(hFile, content_r, 255, 0, NULL);

  LARGE_INTEGER ulFileSize;
  if (GetFileSizeEx(hFile, &ulFileSize))
  {
    printf("file size:%d\n", ulFileSize.QuadPart);
  }


  CloseHandle(hFile);
  _wsetlocale(LC_ALL, L"chs");
  wprintf(L"%s", content_r);
}

// 此方法可以快速生成一个大文件
int set_file_size()
{
  HANDLE hFile = CreateFile(L"large_file.txt", GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, 0, NULL);
  LARGE_INTEGER liMove;
  // 10k
  liMove.QuadPart = 1024 * 10;
  SetFilePointerEx(hFile, liMove, NULL, FILE_BEGIN);
  SetEndOfFile(hFile);
  CloseHandle(hFile);
  return 0;
}


/*
内容：异步读写文件
API：CreateFile  WriteFile   ReadFile
异步判断：ERROR_IO_PENDING  GetLastError

异步IO完成通知的方法：
触发设备内核对象：允许一个线程发出IO请求，另一个线程对结果进行处理。
当向一个设备同时发出多个IO请求的时候，此方法无效。

触发事件内核对象：这种方法允许我们向一个设备同时发出多个IO请求，
它允许一个线程发出IO请求，另一个线程对结果进行处理。

使用可提醒IO：这种方法允许我们向一个设备发出多个IO请求。
发出IO请求的线程必须对结果进行处理。

使用IO完成端口：这种方法允许我们向一个设备同时发出多个IO请求。
它允许一个线程发出IO请求，另一个线程对结果进行处理。推荐使用，伸缩性和灵活性都很好。
IO完成接口的初衷就是与线程池配合使用
*/

int one_io_request()
{
#pragma region 只能处理一个io请求
  char content[] = "this is test content";
  HANDLE hFile = CreateFile(L"async_io.txt", GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_FLAG_OVERLAPPED, NULL);
  if (INVALID_HANDLE_VALUE == hFile)
  {
    printf("Create file error 2, code:0x%x\n", GetLastError());
    return 1;
  }

  OVERLAPPED ol = { 0 };
  if (!WriteFile(hFile, content, strlen(content), NULL, &ol))
  {
    if (ERROR_IO_PENDING == GetLastError())
    {
      printf("正在异步操作\n");
      WaitForSingleObject(hFile, INFINITE);
      printf("异步写入结束\n");
    }
  }
  CloseHandle(hFile);

  char enContent_r[255] = { 0 };
  HANDLE hFile2 = CreateFile(L"async_io.txt", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL);
  if (INVALID_HANDLE_VALUE == hFile2)
  {
    printf("CreateFile failed !!!\n");
    getchar();
    return 1;
  }
  DWORD readCount = 0;
  OVERLAPPED ol2 = { 0 };
  BOOL ret2 = ReadFile(hFile2, enContent_r, 255, &readCount, &ol2);
  if (false == ret2)
  {
    DWORD err = GetLastError();
    if (ERROR_IO_PENDING == err)
    {
      printf("正在异步操作\n");
      WaitForSingleObject(hFile2, INFINITE);
      printf("异步读取完毕\n");
      printf("%s", enContent_r);
    }
    else
    {
      printf("ReadFile failed !!!\n");
      getchar();
      return 1;
    }

  }

  CloseHandle(hFile2);
#pragma endregion
}


int multi_io_request()
{
  char enContent[] = "this is test content\r\n";
  char cnContent[] = "这是一个中文";

  HANDLE hFile = CreateFile(L"1.txt", GENERIC_READ|GENERIC_WRITE, 0, NULL, OPEN_ALWAYS,  FILE_FLAG_OVERLAPPED, NULL);
  if (INVALID_HANDLE_VALUE == hFile)
  {
    printf("Create file error\n");
    getchar();
    return 1;
  }

  OVERLAPPED ol1 = { 0 };
  OVERLAPPED ol2 = { 0 };
  ol1.hEvent = CreateEvent(NULL, true, false, NULL);
  ol2.hEvent = CreateEvent(NULL, true, false, NULL);
  // 这里的offset指的是文件指针的偏移
  ol2.Offset = 2;

  char enContent_r[255] = { 0 };
  bool ret = ReadFile(hFile, enContent_r, 255, NULL, &ol2);
  WriteFile(hFile, enContent, strlen(enContent), NULL, &ol1);
  if (!ret)
  {
    DWORD err = GetLastError();
    if (ERROR_IO_PENDING == err)
    {
      printf("正在异步操作\n");
      HANDLE handle[2];
      handle[0] = ol1.hEvent;
      handle[1] = ol2.hEvent;
      DWORD objnum = WaitForMultipleObjects(2, handle, false, INFINITE);
      switch (objnum)
      {
      case WAIT_OBJECT_0:
        printf("read file return, conent:%s\n", enContent_r);
        break;
      case WAIT_OBJECT_0+1:
        printf("write file return\n");
        break;
      case WAIT_FAILED:
        printf("wait failed, code:0x%x", GetLastError());
        break;

      }
    }
    else
    {
      printf("ReadFile failed !!!\n");
      getchar();
      return 1;
    }

  }

  CloseHandle(ol1.hEvent);
  CloseHandle(ol2.hEvent);
  CloseHandle(hFile);



}

void  WINAPI read_cb(DWORD dwErrorCode, DWORD dwNumberOfBytesTransfered,
  LPOVERLAPPED lpOverlapped)
{
  printf("call back.......\n");
}


void callback_io()
{
  HANDLE hFile = CreateFile(L"1.txt", GENERIC_READ|GENERIC_WRITE, 0, NULL, OPEN_ALWAYS,  FILE_FLAG_OVERLAPPED, NULL);
  if (INVALID_HANDLE_VALUE == hFile)
  {
    printf("Create file error\n");
    getchar();
  }

  char content_r[255] = { 0 };
  OVERLAPPED ol1 = { 0 };
  if (!ReadFileEx(hFile, content_r, 255, &ol1, read_cb))
  {
    printf("read error\n");
  }
  WaitForSingleObjectEx(hFile, INFINITE, true);
  CloseHandle(hFile);
}


HANDLE iocp = NULL;
unsigned __stdcall thread_func(void *context)
{
  getchar();

  OVERLAPPED ol = { 0 };
  ULONG_PTR key = 10;
  PostQueuedCompletionStatus(iocp, sizeof(ULONG_PTR), key, &ol);
  return 0;
}



void iocp_io()
{
  char enContent[] = "this is test content\r\n";

  HANDLE hFile = CreateFile(L"1.txt", GENERIC_READ|GENERIC_WRITE, 0, NULL, OPEN_ALWAYS,  FILE_FLAG_OVERLAPPED, NULL);
  if (INVALID_HANDLE_VALUE == hFile)
  {
    printf("Create file error\n");
    getchar();
    return;
  }

  iocp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
  if (NULL == iocp)
  {
    printf("create iocp error, code:0x%x", GetLastError());
    return;
  }

  ULONG_PTR CK_READ = 0;
  CreateIoCompletionPort(hFile, iocp, CK_READ, 0);

  unsigned int uiThreadID = 0;
  // 需要在另外一个线程通知iocp结束
  uintptr_t hth = _beginthreadex(NULL, 0, thread_func, NULL, 0, &uiThreadID);

  char username[255] = { 0 };
  OVERLAPPED ol1 = { 0 };
  ReadFile(hFile, username, 255, 0, &ol1);

  DWORD trans = 0;
  ULONG_PTR lpcontext = 0;
  OVERLAPPED *pol = NULL;
  while (GetQueuedCompletionStatus(iocp, &trans, &lpcontext, &pol, INFINITE))
  {
    if (lpcontext != NULL && 10 == (ULONG_PTR)lpcontext)
    {
      printf("我要退出了");
      break;
    }
    printf("%s", username);
  }

  CloseHandle(iocp);
  CloseHandle(hFile);
}

int async_io()
{
  //one_io_request()
   //multi_io_request();
  // callback_io();
  iocp_io();
  return 0;
}