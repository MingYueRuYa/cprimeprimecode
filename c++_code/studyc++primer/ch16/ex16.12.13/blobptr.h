/****************************************************************
 **
 **	Copyright (C) 2016 635672377@qq.com
 ** All rights reserved.
 **
 ***************************************************************/

#ifndef blobptr_h

#define blobptr_h

#include <iostream>

#include "blob.h"

template <typename T> class BlobPtr;

template <typename T> class Blob;

template <typename T>
bool operator ==(const BlobPtr<T> &pLeftBlobPtr, const BlobPtr<T> &pRightBlobPtr);

template <typename T>
bool operator <(const BlobPtr<T> &pLeftBlobPtr, const BlobPtr<T> &pRightBlobPtr);

template <typename T>
class BlobPtr
{
	friend bool operator ==<T>
	(const BlobPtr<T> &pLeftBlobPtr, const BlobPtr<T> &pRightBlobPtr);
 
	friend bool operator < <T>
	(const BlobPtr<T> &pLeftBlobPtr, const BlobPtr<T> &pRightBlobPtr);

public:
	BlobPtr();

	BlobPtr(Blob<T> &pBlob, std::size_t sz=0);

	T& operator*() const;

	//prefix
	BlobPtr &operator++();
	BlobPtr &operator--();

	//postfix
	BlobPtr operator++(int);
	BlobPtr operator--(int);

private:
	//return a share_ptr to the vector if che check succeeds
	std::shared_ptr<std::vector<T> > Check(std::size_t, const std::string &) const;

	std::weak_ptr<std::vector<T> > mWptr;

	std::size_t mCurr;

};


template <typename T>
bool operator ==(const BlobPtr<T> &pLeftBlobPtr, const BlobPtr<T> &pRightBlobPtr)
{
	return false;
}

template <typename T>
bool operator <(const BlobPtr<T> &pLeftBlobPtr, const BlobPtr<T> &pRightBlobPtr)
{
	return false;
}

template <typename T>
BlobPtr<T>::BlobPtr(): mCurr(0)
{
}

template <typename T>
BlobPtr<T>::BlobPtr(Blob<T> &pBlob, std::size_t sz)
	: mWptr(pBlob.mData), mCurr(sz)
{
}

template <typename T>
T& BlobPtr<T>::operator*() const
{
	std::shared_ptr<std::vector<T> > p = Check(mCurr, "Dereference past end.");
	return (*this)[mCurr];
}

//prefix
template <typename T>
BlobPtr<T> &BlobPtr<T>::operator++()
{
	Check(mCurr, "Increment past end of StrBlob.");
	++mCurr;
	return *this;
}

template <typename T>
BlobPtr<T> &BlobPtr<T>::operator--()
{
	--mCurr;
	Check(mCurr, "Decrement past end of StrBlob.");
	return *this;
}

//postfix ++
template <typename T>
BlobPtr<T> BlobPtr<T>::operator++(int)
{
	BlobPtr tempblobptr = *this;
	++*this;
	return tempblobptr;
}

//postfix --
template <typename T>
BlobPtr<T> BlobPtr<T>::operator--(int)
{
	BlobPtr tempblobptr = *this;
	--*this;
	return tempblobptr;
}

template <typename T>
std::shared_ptr<std::vector<T> > BlobPtr<T>::Check(std::size_t pIndex, const std::string &pMsg) const
{
	if (pIndex >= mWptr->size()) {
		throw std::out_of_range(pMsg);
		return nullptr;
	}
	return mWptr->mData;
}

#endif //blobptr_h
