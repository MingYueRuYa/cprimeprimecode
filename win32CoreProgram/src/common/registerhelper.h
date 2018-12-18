/****************************************************************************
**
** Copyright (C) 2018 635672377@qq.com
** All rights reserved.
**
****************************************************************************/

#ifndef registerhelper_h
#define registerhelper_h

#include <map>
#include <string>
#include <windows.h>

using std::map;
using std::wstring;

namespace XIBAO {

/*! \brief common::registerhelper
 	\author liushixiong (liushixiongcpp@163.cn)
 	\version 0.01
	\description 注册表读取助手
 	\date 2018-12-13 20:13:42
*/
class RegisterHelper
{
private:
	class InnerRegData {
		public:
			InnerRegData();
			~InnerRegData();
			InnerRegData(const InnerRegData &right);
			InnerRegData& operator=(const InnerRegData &right);

		private:
			void _CopyValue(const InnerRegData &right);
			
		public:
			wstring mKeyName;
			wstring value;
			DWORD	valueType;
	};

	template <typename T>
	class RegDataType {
		public:
			explicit RegDataType(DWORD regType, const T &tValue)
				:	mRegType(regType),
					mValue(tValue)
			{ 
				// 静态断言
				static_assert(! std::is_pointer<T>::value, "Not support pinter type.");
			}

			~RegDataType() {}
			RegDataType(const RegDataType &right) = default;
			RegDataType& operator=(const RegDataType &right) = default;

			unsigned int size() const { return sizeof(T); }
			T *GetAddress() const { return &mValue; }
			DWORD GetType() const { return mRegType; }

		public:
			DWORD mRegType;
			T	  mValue;
	};

	template <>
	class RegDataType<wstring> {
	public:
		RegDataType(DWORD regType, const wstring &tValue)
			: mRegType(regType),
			  mValue(tValue)
		{ 
		}

		~RegDataType() {}

		RegDataType(const RegDataType &right) = default;
		RegDataType& operator=(const RegDataType &right) = default;

		unsigned int size() const { return mValue.length() * sizeof(wchar_t); }
		const wchar_t *GetAddress() const { return mValue.c_str(); }
		DWORD GetType() const { return mRegType; }

	public:
		DWORD	mRegType;
		wstring	mValue;
	};

public:
	RegisterHelper(HKEY key, const wstring &subPath, REGSAM regSam);
	RegisterHelper(const RegisterHelper &right);
	RegisterHelper& operator=(const RegisterHelper &right);
	~RegisterHelper();

	template<typename TRetValue>
	DWORD GetValue(const wstring &keyName, TRetValue &value)
	{
		HKEY hKey = 0;
		DWORD result = NOERROR;

		long lRet = RegOpenKeyExW(mRootKey, mSubPath.c_str(), 0,
			mSamDesired, &hKey);
		if (lRet != ERROR_SUCCESS) {
			return GetLastError();
		}

		// 1024
		DWORD regtype;
		DWORD count		= MAX_PATH*4;
		BYTE *lpData	= new BYTE[MAX_PATH*4];
		lRet			= RegQueryValueExW(hKey, 
											keyName.c_str(), 
											NULL, 
											&regtype, 
											lpData, 
											&count);
		
		if (lRet != ERROR_SUCCESS) {
			delete[] lpData;
			return GetLastError();
		}

		
		//TODO 需要优化下此处的if语句
		if (REG_SZ == regtype || REG_EXPAND_SZ == regtype ||
			REG_MULTI_SZ == regtype) {
			value = TRetValue((reinterpret_cast<wchar_t *>(lpData)));
		} else if (REG_DWORD == regtype || 
					REG_DWORD_LITTLE_ENDIAN == regtype ||
					REG_DWORD_BIG_ENDIAN == regtype || 
					REG_QWORD == regtype ||
					REG_DWORD_BIG_ENDIAN == regtype) {
			value = *(reinterpret_cast<TRetValue *>(lpData));
		}

		delete[] lpData;
		return 0;
	}

	template<typename TRetValue>
	DWORD SetValue(const wstring &keyName, 
					const TRetValue &value,
					DWORD regType)
	{
		RegDataType<TRetValue> datatype(regType, value);

		HKEY hKey			= 0;
		BYTE *lpData		= nullptr;
		DWORD result		= NOERROR;

		long lRet = RegOpenKeyExW(mRootKey, mSubPath.c_str(), 0, 
											mSamDesired, &hKey);
		if (lRet != ERROR_SUCCESS) {
			if (ERROR_SUCCESS != RegCreateKeyW(mRootKey, 
												mSubPath.c_str(), 
												&hKey)) {
				result = GetLastError();
				goto CreateError;
			}
		}

		lpData = new BYTE[datatype.size()];
		CopyMemory(lpData, datatype.GetAddress(), datatype.size());
		lRet = RegSetValueEx(hKey, keyName.c_str(), 0, 
								datatype.GetType(), lpData, datatype.size());
		result = lRet;
		RegCloseKey(hKey);
		delete[] lpData;
		return result;	

	CreateError:
		RegCloseKey(hKey);
		delete[] lpData;
		return result;
	}

private:
	void _CopyValue(const RegisterHelper &right);

private:
	// 主键
	HKEY mRootKey;
	// 副键
	wstring mSubPath;
	// 读取权限
	REGSAM mSamDesired;
	map<wstring, InnerRegData> mMapRegData;
	
};

}

#endif // registerhelper_h