#include "taesclass.h"


  TAesClass::TAesClass()
  {
      m_lpAes=NULL;
      InitializePrivateKey(16,(unsigned char*)"\x79\x76\x68\x6B\x77\x66\x6E\x68\x72\x65\x73\x63\x6C\x6B\x70\x6E");
  }

  TAesClass::~TAesClass()
  {
      if (m_lpAes!=NULL)
      {
          delete m_lpAes;
      }
  }
  //------------------------------------------------------------------------------------------------------------
  // 编写人员：wfnhddd
  //
  // 函数名称：InitializeAes
  //
  // 函数描述：初始化AES 密钥，密钥用于加密解密
  //
  // 调用参数：详细说明参考 MSDN 中的相关描述或相关的开发文档
  //
  // 返回数值：无
  //
  // 最近修改：2009 年 08 月 07 日
  //------------------------------------------------------------------------------------------------------------


  VOID TAesClass::InitializePrivateKey(DWORD KeySize,UCHAR *KeyBytes)
  {
      if (m_lpAes)
      {
          delete m_lpAes;
          m_lpAes=NULL;
      }
      m_lpAes=new Aes(KeySize,KeyBytes);

  }

  //------------------------------------------------------------------------------------------------------------
  // 编写人员：wfnhddd
  //
  // 函数名称：OnAesEncrypt
  //
  // 函数描述：用AES加密算法加密数据
  //
  // 调用参数：详细说明参考 MSDN 中的相关描述或相关的开发文档
  //
  // 返回数值：加密后的数据大小 ，错误返回值 0
  //
  // 最近修改：2009 年 08 月 07 日
  //------------------------------------------------------------------------------------------------------------

  DWORD TAesClass::OnAesEncrypt(LPVOID InBuffer,DWORD InLength,LPVOID OutBuffer)
  {
      DWORD OutLength=0;
      if (m_lpAes==NULL||OutBuffer==NULL)
      {
          return 0;
      }

      UCHAR *lpCurInBuff=(UCHAR *)InBuffer;
      UCHAR *lpCurOutBuff=(UCHAR *)OutBuffer;
      long blocknum=InLength/16;
      long leftnum=InLength%16;
      for(long i=0;i<blocknum;i++)
      {
          m_lpAes->Cipher(lpCurInBuff,lpCurOutBuff);
          lpCurInBuff+=16;
          lpCurOutBuff+=16;
          OutLength+=16;
      }
      if(leftnum) //多余出leftnum 字节 则加密时 多出16-leftnum 个字节
      {
          UCHAR inbuff[16];
          memset(inbuff,0,16);
          memcpy(inbuff,lpCurInBuff,leftnum);
          m_lpAes->Cipher(inbuff,lpCurOutBuff);
          lpCurOutBuff+=16;
          OutLength+=16;
      }
                                  //新增16个字节，用以确定增加的字节数
      UCHAR extrabuff[16];
      memset(extrabuff,0,16);
      *((LPDWORD)extrabuff)=16+(16-leftnum)%16; //多出16+(16-leftnum)%16个字节
      m_lpAes->Cipher(extrabuff,lpCurOutBuff);
      OutLength+=16;
      return OutLength;

  }


  //------------------------------------------------------------------------------------------------------------
  // 编写人员：wfnhddd
  //
  // 函数名称：OnAesUncrypt
  //
  // 函数描述：用AES加密算法解密数据
  //
  // 调用参数：详细说明参考 MSDN 中的相关描述或相关的开发文档
  //
  // 返回数值：解密后的数据大小 ，错误返回值 0
  //
  // 最近修改：2009 年 08 月 07 日
  //------------------------------------------------------------------------------------------------------------
  DWORD TAesClass::OnAesUncrypt(LPVOID InBuffer,DWORD InLength,LPVOID OutBuffer)
  {
      DWORD OutLength=0;
      if (m_lpAes==NULL||OutBuffer==NULL)
      {
          return 0;
      }
      UCHAR *lpCurInBuff=(UCHAR *)InBuffer;
      UCHAR *lpCurOutBuff=(UCHAR *)OutBuffer;
      long blocknum=InLength/16;
      long leftnum=InLength%16;
          if(leftnum)
      {
                  return 0;
      }
      for(long i=0;i<blocknum;i++)
      {
          m_lpAes->InvCipher(lpCurInBuff,lpCurOutBuff);
          lpCurInBuff+=16;
          lpCurOutBuff+=16;
          OutLength+=16;
      }

      UCHAR *lpExtraInBuff=lpCurOutBuff-16;
      DWORD dwExtraBytes=*((LPDWORD)lpExtraInBuff);
      return (OutLength-dwExtraBytes);

  }
