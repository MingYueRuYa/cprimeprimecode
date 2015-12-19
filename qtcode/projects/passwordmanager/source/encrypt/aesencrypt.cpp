/****************************************************************************
**
** Copyright (C) 2015 liushixiong. (635672377@qq.com)
** All rights reserved.
**
****************************************************************************/

#include "aesencrypt.h"

AesEncrypt::AesEncrypt(int keysize,unsigned char* keyBytes)
{
    SetNbNkNr(keysize); //设置密钥块数，轮数
    memcpy(key,keyBytes,keysize);                //字符串拷贝函数，把keyBytes的keysize个字符复制到key中
    KeyExpansion();                              //密钥扩展，必须提前做的初始化
}

AesEncrypt::~AesEncrypt()
{
}

void AesEncrypt::Init(DWORD KeySize, UCHAR *KeyBytes)
{
}

int AesEncrypt::Encrypt(const LPVOID InBuffer, DWORD InLength, LPVOID OutBuffer)
{
    DWORD OutLength = 0;
    if (NULL ==  InBuffer || NULL == OutBuffer) {
        return 0;
    }

    UCHAR *lpCurInBuff = (UCHAR *)InBuffer;
    UCHAR *lpCurOutBuff = (UCHAR *)OutBuffer;
    long blocknum = InLength / 16;
    long leftnum = InLength % 16;
    for(long i = 0; i<blocknum; i++) {
        Cipher(lpCurInBuff, lpCurOutBuff);
        lpCurInBuff += 16;
        lpCurOutBuff += 16;
        OutLength += 16;
    }
    //多余出leftnum 字节 则加密时 多出16-leftnum 个字节
    if (leftnum) {
        UCHAR inbuff[16];
        memset(inbuff, 0, 16);
        memcpy(inbuff, lpCurInBuff, leftnum);
        Cipher(inbuff, lpCurOutBuff);
        lpCurOutBuff += 16;
        OutLength += 16;
    }
    //新增16个字节，用以确定增加的字节数
    UCHAR extrabuff[16];
    memset(extrabuff, 0, 16);
    *((LPDWORD)extrabuff) = 16 + (16 - leftnum) % 16; //多出16+(16-leftnum)%16个字节
    Cipher(extrabuff, lpCurOutBuff);
    OutLength += 16;
    return OutLength;
}

int AesEncrypt::Decrypt(const LPVOID InBuffer, DWORD InLength, LPVOID OutBuffer)
{
    DWORD OutLength = 0;
    if (NULL ==  InBuffer || NULL == OutBuffer) {
        return 0;
    }
    UCHAR *lpCurInBuff = (UCHAR *)InBuffer;
    UCHAR *lpCurOutBuff = (UCHAR *)OutBuffer;
    long blocknum = InLength / 16;
    long leftnum = InLength % 16;
    if (leftnum) {
        return 0;
    }
    for(long i = 0; i < blocknum; i++) {
        InvCipher(lpCurInBuff,lpCurOutBuff);
        lpCurInBuff += 16;
        lpCurOutBuff += 16;
        OutLength += 16;
    }

    UCHAR *lpExtraInBuff = lpCurOutBuff - 16;
    DWORD dwExtraBytes = *((LPDWORD)lpExtraInBuff);
    return (OutLength - dwExtraBytes);
}

void AesEncrypt::Cipher(unsigned char* input, unsigned char* output)
{
    memset(&State[0][0],0,16);
    for(int i = 0; i < 4 * Nb; i++) {//这里是先写列后写行的，即输入是一列一列的进来的
        State[i % 4][i / 4] = input[i];                    //换成先写行后写列也是可以的，只要在输出时也是这样就可以了
    }
    AddRoundKey(0);                                    //轮密钥加

    for (int round = 1; round <= (Nr - 1); round++) {// main round loop
        SubBytes();                                    //字节代换
        ShiftRows();                                //行移位
        MixColumns();                                //列混淆
        AddRoundKey(round);                            //轮密钥加
    }

    SubBytes();                                        //字节代换
    ShiftRows();                                    //行移位
    AddRoundKey(Nr);                                //轮密钥加

    for (int i = 0; i < (4 * Nb); i++) {
        output[i] = State[i % 4][ i / 4];
    }
}

void AesEncrypt::InvCipher(unsigned char* input,unsigned char* output)
{
    memset(&State[0][0], 0, 16);
    for (int i = 0; i < (4 * Nb); i++)
    {
        State[i % 4][ i / 4] = input[i];
    }

    AddRoundKey(Nr);

    for (int round = Nr-1; round >= 1; round--) // main round loop
    {
        InvShiftRows();
        InvSubBytes();
        AddRoundKey(round);
        InvMixColumns();
    } // end main round loop for InvCipher

    InvShiftRows();
    InvSubBytes();
    AddRoundKey(0);

    for (int i = 0; i < (4 * Nb); i++) {
        output[i] = State[i % 4][ i / 4];
    }
}

void AesEncrypt::SetNbNkNr(int keySize)
{
    Nb = 4;
    if(keySize == Bits128) {
        Nk = 4; //4*4字节，128位密钥，10轮加密
        Nr = 10;
    } else if(keySize == Bits192) {
        Nk = 6; //6*4字节，192位密钥，12轮加密
        Nr = 12;
    } else if(keySize == Bits256) {
        Nk = 8; //8*4字节，256位密钥，14轮加密
        Nr = 14;
    }
}

//轮密钥加
void AesEncrypt::AddRoundKey(int round)
{
    int i, j; //i行 j列 //因为密钥w是一列一列排列的，即 k0 k4 k8 k12
    for(j = 0; j<4; j++) {               
        for(i = 0; i < 4; i++) {                    
            State[i][j] = (unsigned char)( (int)State[i][j]^(int)w[4 * ((round * 4) + j) + i] );
        }
    }
}

//字节代换函数
void AesEncrypt::SubBytes()
{
    int i, j;
    for(j = 0; j < 4;j ++) {
        for(i = 0;i < 4; i++) {
            State[i][j] = AesSbox[State[i][j]];
        }
    }
}

void AesEncrypt::InvSubBytes()
{
    int i, j;
    for(j = 0; j < 4; j++) {
        for(i = 0; i < 4; i++) {
            State[i][j]=AesiSbox[State[i][j]];
        }
    }
}

void AesEncrypt::ShiftRows()
{
    unsigned char temp[4 * 4];
    int i, j;
    for(j = 0; j < 4; j++) {
        for(i = 0; i < 4; i++) {
            temp[4 * i+ j] = State[i][j];
        }
    }
    for(i = 1; i < 4; i++) {
        for(j = 0; j < 4; j++) {
            if(i == 1) {
                State[i][j] = temp[4 * i + (j + 1) % 4];      //第一行左移1位
            } else if(i == 2) {
                State[i][j] = temp[4*i+(j+2)%4];                //第二行左移2位
            } else if(i == 3) {
                State[i][j] = temp[4*i+(j+3)%4];                //第三行左移3位
            }
        }
    }
}

void AesEncrypt::InvShiftRows()
{
    unsigned char temp[4 * 4];
    int i, j;
    for(j = 0; j < 4; j++) {
        for(i = 0;i < 4; i++) {
            temp[4 * i + j] = State[i][j];
        }
    }
    for(i = 1; i < 4; i++) {
        for(j = 0; j < 4; j++) {
            if(i == 1) {
               State[i][j] = temp[4 * i + (j + 3) % 4];
            } else if (i == 2) {
               State[i][j] = temp[4 * i + (j + 2) % 4];
            } else if(i == 3) {
               State[i][j] = temp[4 * i + (j + 1) % 4];
            }
        }
    }

}

void AesEncrypt::MixColumns()
{
    unsigned char temp[4 * 4];
    int i, j;
    for(j = 0; j < 4; j++) {
        for(i = 0; i < 4; i++) {
            temp[4 * i + j]=State[i][j];
        }
    }
    for(j = 0; j < 4; j++) {
        State[0][j] = (unsigned char)((int)gfmultby02(temp[0 + j]) ^ (int)gfmultby03(temp[4 * 1 + j]) ^
            (int)gfmultby01(temp[4 * 2 + j]) ^ (int)gfmultby01(temp[4 * 3+ j]) );
        State[1][j] = (unsigned char)((int)gfmultby01(temp[0 + j]) ^ (int)gfmultby02(temp[4 * 1 + j]) ^
            (int)gfmultby03(temp[4 * 2 + j]) ^ (int)gfmultby01(temp[4 * 3 + j]));
        State[2][j] = (unsigned char)((int)gfmultby01(temp[0 + j]) ^ (int)gfmultby01(temp[4 * 1 + j]) ^
            (int)gfmultby02(temp[4 * 2+ j]) ^ (int)gfmultby03(temp[4 * 3 + j]));
        State[3][j] = (unsigned char)((int)gfmultby03(temp[0 + j]) ^ (int)gfmultby01(temp[4 * 1 + j]) ^
            (int)gfmultby01(temp[4 * 2 + j]) ^ (int)gfmultby02(temp[4 * 3 + j]));
    }

}

void AesEncrypt::InvMixColumns()
{
    unsigned char temp[4 * 4];
    int i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) { 
            temp[4 * i + j] = State[i][j];
        }                                
    }

    for (j = 0; j < 4; j++) {
        State[0][j] = (unsigned char)((int)gfmultby0e(temp[j]) ^ (int)gfmultby0b(temp[4 + j]) ^
            (int)gfmultby0d(temp[4 * 2 + j]) ^ (int)gfmultby09(temp[4 * 3 + j]) );
        State[1][j] = (unsigned char)((int)gfmultby09(temp[j]) ^ (int)gfmultby0e(temp[4 + j]) ^
            (int)gfmultby0b(temp[4 * 2 + j]) ^ (int)gfmultby0d(temp[4 * 3 + j]) );
        State[2][j] = (unsigned char)((int)gfmultby0d(temp[j]) ^ (int)gfmultby09(temp[4 + j]) ^
            (int)gfmultby0e(temp[4 * 2 + j]) ^ (int)gfmultby0b(temp[4 * 3 + j]) );
        State[3][j] = (unsigned char)((int)gfmultby0b(temp[j]) ^ (int)gfmultby0d(temp[4 + j]) ^
            (int)gfmultby09(temp[4 * 2 + j]) ^ (int)gfmultby0e(temp[4 * 3 + j]) );
    }
}


unsigned char AesEncrypt::gfmultby01(unsigned char b)
{
    return b;
}
unsigned char AesEncrypt::gfmultby02(unsigned char b)
{
    if (b < 0x80) {
        return (unsigned char)(int)(b << 1);
		} else {
        return (unsigned char)( (int)(b << 1) ^ (int)(0x1b) );
		}
}

unsigned char AesEncrypt::gfmultby03(unsigned char b)
{
    return (unsigned char)( (int)gfmultby02(b) ^ (int)b );
}

unsigned char AesEncrypt::gfmultby09(unsigned char b)
{
    return (unsigned char)( (int)gfmultby02(gfmultby02(gfmultby02(b))) ^ (int)b );
}

unsigned char AesEncrypt::gfmultby0b(unsigned char b)
{
    return (unsigned char)( (int)gfmultby02(gfmultby02(gfmultby02(b))) ^
        (int)gfmultby02(b) ^ (int)b );
}

unsigned char AesEncrypt::gfmultby0d(unsigned char b)
{
    return (unsigned char)( (int)gfmultby02(gfmultby02(gfmultby02(b))) ^
        (int)gfmultby02(gfmultby02(b)) ^ (int)(b) );
}

unsigned char AesEncrypt::gfmultby0e(unsigned char b)
{
    return (unsigned char)( (int)gfmultby02(gfmultby02(gfmultby02(b))) ^
        (int)gfmultby02(gfmultby02(b)) ^(int)gfmultby02(b) );
}

void AesEncrypt::KeyExpansion()
{
    memset(w, 0, 16 * 15);
    for(int row = 0; row < Nk; row++) {
        w[4 * row + 0] = key[4 * row];
        w[4 * row + 1] = key[4 * row+1];
        w[4 * row + 2] = key[4 * row+2];
        w[4 * row + 3] = key[4 * row+3];
    }
    byte* temp = new byte[4];
    for(int row = Nk; row < 4 * (Nr + 1); row++) {
        temp[0] = w[4 * row - 4]; //当前列的前一列
        temp[1] = w[4 * row - 3];
        temp[2] = w[4 * row - 2];
        temp[3] = w[4 * row - 1];
        if(row%Nk == 0) {
            temp = SubWord(RotWord(temp)); //先移位，再代换，最后和轮常量异或
            temp[0] = (byte)( (int)temp[0] ^ (int) AesRcon[4 * (row / Nk) + 0] );
            temp[1] = (byte)( (int)temp[1] ^ (int) AesRcon[4 * (row / Nk) + 1] );
            temp[2] = (byte)( (int)temp[2] ^ (int) AesRcon[4 * (row / Nk) + 2] );
            temp[3] = (byte)( (int)temp[3] ^ (int) AesRcon[4 * (row / Nk) + 3] );
        }
        else if ( Nk > 6 && (row % Nk == 4) ) {
            temp = SubWord(temp);
        }
        w[4 * row + 0] = (byte) ( (int) w[4 * (row - Nk) + 0] ^ (int)temp[0] );
        w[4 * row + 1] = (byte) ( (int) w[4 * (row - Nk) + 1] ^ (int)temp[1] );
        w[4 * row + 2] = (byte) ( (int) w[4 * (row - Nk) + 2] ^ (int)temp[2] );
        w[4 * row + 3] = (byte) ( (int) w[4 * (row - Nk) + 3] ^ (int)temp[3] );
    }
}

unsigned char* AesEncrypt::RotWord(unsigned char* word)
{
    byte* temp = new byte[4];
    temp[0] = word[1];
    temp[1] = word[2];
    temp[2] = word[3];
    temp[3] = word[0];
    return temp;
}

unsigned char* AesEncrypt::SubWord(unsigned char* word)
{
    byte* temp = new byte[4];
    for(int j = 0; j < 4 ; j++) {
        temp[j] = AesSbox[16*(word[j] >> 4)+(word[j] & 0x0f)];
    }
    return temp;
}
