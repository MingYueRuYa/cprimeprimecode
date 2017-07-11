#include <windows.h>
#include <tchar.h>

BOOL PromotePrivilege(BOOL p_IsPromotion, LPCTSTR p_lpszPriviliges)
{
	HANDLE hToken = NULL;
    HANDLE processhandle = GetCurrentProcess();
	if (! OpenProcessToken(processhandle, TOKEN_ADJUST_PRIVILEGES, &hToken)) {
        _tprintf(TEXT("OpenProcessToken error:%u.\n"), GetLastError());
        return FALSE;
    }

    LUID luid;
    //NULL loopup privilege on local system
    //privilege to lookup
    //receives LUID of privilege
    if (! LookupPrivilegeValue(NULL, p_lpszPriviliges, &luid)) {
        _tprintf(TEXT("Loopup PrivilegeValue error:%u.\n"), GetLastError());
        return FALSE; 
    }

    TOKEN_PRIVILEGES tokenpriviliges = {0};
    tokenpriviliges.PrivilegeCount = 1;
    tokenpriviliges.Privileges[0].Luid = luid;
    tokenpriviliges.Privileges[0].Attributes = p_IsPromotion ? SE_PRIVILEGE_ENABLED : 0;

    //enable the privilege or disable all privilege
    if (! AdjustTokenPrivileges(hToken, FALSE, &tokenpriviliges, sizeof(TOKEN_PRIVILEGES), (PTOKEN_PRIVILEGES)NULL, (PDWORD)NULL)) {
        _tprintf(TEXT("AdjustTokenPriviliges error:%u.\n"), GetLastError());
        return FALSE;
    }

    if (ERROR_NOT_ALL_ASSIGNED == GetLastError()) {
        _tprintf(TEXT("The token dose not have the specified privilege.\n"));
        return FALSE;
    }
	return TRUE;
}


int _tmain02(int argc, char *argv[])
{
    if (PromotePrivilege(TRUE, SE_DEBUG_NAME)) {
        _tprintf(TEXT("Promotion privilege ok!!!"));
    }
    _gettchar();
	return 0;
}

#include <iostream>
#include <windows.h>
    using namespace std;

    int main01()
    {
        int DiskCount = 0;
        DWORD DiskInfo= GetLogicalDrives();
        //利用GetLogicalDrives()函数可以获取系统中逻辑驱动器的数量，函数返回的是一个32位无符号整型数据。
        while (DiskInfo)//通过循环操作查看每一位数据是否为1，假如为1则磁盘为真,假如为0则磁盘不存在。
        {
            if (DiskInfo & 1)//通过位运算的逻辑与操作，判定是否为1
            {
                ++DiskCount;
            }
            DiskInfo = DiskInfo >> 1;//通过位运算的右移操作保证每循环一次所检查的位置向右移动一位。
            //DiskInfo = DiskInfo/2;
        }
        cout << "逻辑磁盘数量:" << DiskCount << endl;
        //-------------------------------------------------------------------

        int DSLength = GetLogicalDriveStrings(0, NULL);
        //通过GetLogicalDriveStrings()函数获取所有驱动器字符串信息长度。
        TCHAR* DStr = new TCHAR[DSLength];//用获取的长度在堆区创建一个c风格的字符串数组
        GetLogicalDriveStrings(DSLength, (LPTSTR)DStr);
        //通过GetLogicalDriveStrings将字符串信息复制到堆区数组中,其中保存了所有驱动器的信息。

        int DType;
        int si = 0;
        BOOL fResult;
        unsigned _int64 i64FreeBytesToCaller;
        unsigned _int64 i64TotalBytes;
        unsigned _int64 i64FreeBytes;
        //string strdiskinfo(DStr);
        for (int i = 0; i < DSLength / 4; ++i)
            //为了显示每个驱动器的状态，则通过循环输出实现，由于DStr内部保存的数据是A:\NULLB:\NULLC:\NULL，这样的信息，所以DSLength/4可以获得具体大循环范围
        {
            //char dir[3] = { DStr[si], ':', '\\' };
            //char dir[3] = { DStr[si], ' ', ' ' };
            //cout << dir;
            char ch = (char)DStr[si];
            cout << (char)DStr[si];
            /*
            DType = GetDriveType((LPCTSTR)DStr + i * 4);
            //GetDriveType函数，可以获取驱动器类型，参数为驱动器的根目录
            if (DType == DRIVE_FIXED)
            {
                cout << "硬盘";
            }
            else if (DType == DRIVE_CDROM)
            {
                cout << "光驱";
            }
            else if (DType == DRIVE_REMOVABLE)
            {
                cout << "可移动式磁盘";
            }
            else if (DType == DRIVE_REMOTE)
            {
                cout << "网络磁盘";
            }
            else if (DType == DRIVE_RAMDISK)
            {

                cout << "虚拟RAM磁盘";
            }
            else if (DType == DRIVE_UNKNOWN)
            {
                cout << "未知设备";
            }

            fResult = GetDiskFreeSpaceEx(
                (LPCTSTR)dir,
                (PULARGE_INTEGER)&i64FreeBytesToCaller,
                (PULARGE_INTEGER)&i64TotalBytes,
                (PULARGE_INTEGER)&i64FreeBytes);
            //GetDiskFreeSpaceEx函数，可以获取驱动器磁盘的空间状态,函数返回的是个BOOL类型数据
            if (fResult)//通过返回的BOOL数据判定驱动器是否在工作状态
            {
                //cout << " totalspace:" << (float)i64TotalBytes / 1024 / 1024 << " MB";//磁盘总容量
                //cout << " freespace:" << (float)i64FreeBytesToCaller / 1024 / 1024 << " MB";//磁盘剩余空间
            }
            else
            {
                cout << " 设备未预备好";
            }
            */
            cout << endl;
            si += 4;
        }

        system("pause");
        return 0;
    }