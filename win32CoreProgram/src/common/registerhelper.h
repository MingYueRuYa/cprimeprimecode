/****************************************************************************
**
** Copyright (C) 2018 635672377@qq.com
** All rights reserved.
**
****************************************************************************/

#ifndef registerhelper_h
#define registerhelper_h

#include "utili.hpp"

#include <map>
#include <string>
#include <memory>
#include <windows.h>

using std::map;
using std::wstring;
using std::shared_ptr;
using std::make_shared;
using std::make_shared_array;

namespace XIBAO {

/*! \brief common::registerhelper
 	\author liushixiong (liushixiongcpp@163.cn)
 	\version 0.01
	\description ע�����ȡ����
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
					mValue(tValue),
					mByteSize(MAX_PATH*2)
			{ 
				// ��̬����
				static_assert(! std::is_pointer<T>::value, 
								"Not support pinter type.");
			}

			explicit RegDataType(DWORD regType)
				:	mRegType(regType),
					mValue(T()),
					mByteSize(MAX_PATH*2)
			{ 
				// ��̬����
				static_assert(! std::is_pointer<T>::value, 
								"Not support pinter type.");
			}

			~RegDataType() {}
			RegDataType(const RegDataType &right) = default;
			RegDataType& operator=(const RegDataType &right) = default;

			unsigned int ValueSize() const { return sizeof(T); }
			const T *GetAddress() const { return &mValue; }
			DWORD GetType() const { return mRegType; }
			DWORD *GetType() { return &mRegType; }
			
			BYTE *GetByte()
			{
				if (nullptr == mshByte.get()) {
					mshByte = make_shared<BYTE>(mByteSize);
				} 
				return mshByte.get();
			}

			DWORD *GetByteSize() { return &mByteSize; }

			T GetValue() 
			{
				mValue = *(reinterpret_cast<T *>(mshByte.get()));
				return mValue;
			}

		public:
			DWORD mRegType;
			DWORD mByteSize;
			T	  mValue;
			shared_ptr<BYTE> mshByte;
	};

	template <>
	class RegDataType<wstring> {
	public:
		RegDataType(DWORD regType, const wstring &tValue)
			: mRegType(regType),
			  mValue(tValue),
			  mByteSize(MAX_PATH*2)
		{ 
		}

		RegDataType(DWORD regType)
			: mRegType(regType),
			  mValue(wstring(L"")),
			  mByteSize(MAX_PATH*2)
		{ 
		}

		~RegDataType() {}

		RegDataType(const RegDataType &right) = default;
		RegDataType& operator=(const RegDataType &right) = default;

		unsigned int ValueSize() const 
		{ return mValue.length() * sizeof(wchar_t); }
		const wchar_t *GetAddress() const { return mValue.c_str(); }
		DWORD GetType() const { return mRegType; }

		wchar_t *GetByte()
		{
			if (nullptr == mshByte.get()) {
				mshByte = make_shared_array<wchar_t>(mByteSize);
			} 
			return mshByte.get();
		}

		DWORD *GetByteSize() { return &mByteSize; }

		wstring GetValue() 
		{
			mValue = wstring(mshByte.get());
			return mValue;
		}

	public:
		DWORD	mRegType;
		wstring	mValue;
		DWORD mByteSize;
		shared_ptr<wchar_t> mshByte;
	};

public:
	RegisterHelper(HKEY key, const wstring &subPath, REGSAM regSam);
	RegisterHelper(const RegisterHelper &right);
	RegisterHelper& operator=(const RegisterHelper &right);
	~RegisterHelper();

	DWORD SetDWORD(const wstring &keyName, DWORD dwValue);
	DWORD GetDWORD(const wstring &keyName, DWORD &dwValue);

	DWORD SetQWORD(const wstring &keyName, int64_t dwValue);
	DWORD GetQWORD(const wstring &keyName, int64_t &dwValue);

	DWORD SetSZ(const wstring &keyName, const wstring &strValue);
	DWORD GetSZ(const wstring &keyName, wstring &strValue);

	DWORD SetMultiSZ(const wstring &keyName, const wstring &strValue);
	DWORD GetMultiSZ(const wstring &keyName, wstring &strValue);

	DWORD SetExpandSZ(const wstring &keyName, const wstring &strValue);
	DWORD GetExpandSZ(const wstring &keyName, wstring &strValue);

	DWORD DeleteValue(const wstring &keyName);
	DWORD DeleteAllValues();
	DWORD DeleteKey();
	DWORD TraverseKey();
	DWORD TraverseValue();

private:
	template<typename TRetValue>
	DWORD GetValue(DWORD regType, const wstring &keyName, TRetValue &value)
	{
		HKEY hKey		= 0;
		DWORD result	= NOERROR;

		RegDataType<TRetValue> regdata(regType);

		long lRet = RegOpenKeyExW(mRootKey, mSubPath.c_str(), 0,
									mSamDesired, &hKey);
		if (lRet != ERROR_SUCCESS) {
			return GetLastError();
		}

		DWORD regtype;
		lRet = RegQueryValueExW(hKey, 
								keyName.c_str(), 
								NULL, 
								&regtype, 
								(BYTE *)regdata.GetByte(),
								regdata.GetByteSize()
								);
		
		if (lRet != ERROR_SUCCESS) {
			return GetLastError();
		}
		value = regdata.GetValue();
		return 0;
	}

	template<typename TRetValue>
	DWORD SetValue(DWORD regType,
					const wstring &keyName,
					const TRetValue &value
					)
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

		lpData = new BYTE[datatype.ValueSize()];
		CopyMemory(lpData, datatype.GetAddress(), datatype.ValueSize());
		lRet = RegSetValueEx(hKey, keyName.c_str(), 0, datatype.GetType(), 
								lpData, datatype.ValueSize());
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
	// ����
	HKEY mRootKey;
	// ����
	wstring mSubPath;
	// ��ȡȨ��
	REGSAM mSamDesired;
	map<wstring, InnerRegData> mMapRegData;
	
};

}

#endif // registerhelper_h