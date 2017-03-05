/****************************************************************
 **
 **	Copyright (C) 2017 635672377@qq.com
 ** All rights reserved.
 **
 ***************************************************************/

#ifndef blob_h
#define blob_h

#include <memory>
#include <vector>

#include "blobptr.h"

using namespace std;

template <typename T> class BlobPtr;

template <typename T> class Blob
{
public:
	friend class BlobPtr<T>;

	typedef typename std::vector<T>::size_type size_type;

	Blob();

	~Blob();

	Blob(std::initializer_list<T> il);

	size_type Size() const;

	bool	  Empty() const;

	void Push_Back(const T& pElement);

	void Push_Back(const T&& pElement);

	void Pop_Back();

	T &Back();

	T &operator[](size_type pIndex);

	const T &Back() const;

	const T &operator[](size_type pIndex) const;

private:
	std::shared_ptr<std::vector<T> > mData;

	void Check(size_type pIndex, const std::string &pMsg) const;

};

template <typename T>
Blob<T>::Blob(): mData(std::make_shared<std::vector<T> >())
{
}

template <typename T>
Blob<T>::~Blob()
{
}

template <typename T>
Blob<T>::Blob(std::initializer_list<T> il):
	mData(make_shared<std::vector<T> >(il))
{
}

template <typename T>
typename Blob<T>::size_type Blob<T>::Size() const
{
	return mData->size();
}

template <typename T>
bool Blob<T>::Empty() const
{
	return mData->empty();
}

template <typename T>
void Blob<T>::Push_Back(const T& pElement)
{
	mData->push_back(pElement);
}

template <typename T>
void Blob<T>::Push_Back(const T&& pElement)
{
	mData->push_back(std::move(pElement));
}

template <typename T>
void Blob<T>::Pop_Back()
{
	Check(0, "pop_back on empty Blob.");
	mData->pop_back();
}

template <typename T>
T &Blob<T>::Back()
{
	Check(0, "pop_back on empty Blob.");
	mData->back();
}

template <typename T>
T &Blob<T>::operator[](size_type pIndex)
{
	Check(pIndex, "subscript out of range");
	return (*mData)[pIndex];
}

template <typename T>
const T &Blob<T>::Back() const
{
	Check(0, "pop_back on empty Blob.");
	return mData->back();
}

template <typename T>
const T &Blob<T>::operator[](size_type pIndex) const
{
	Check(pIndex, "subscript out of range");
	return (*mData)[pIndex];
}

template <typename T>
void Blob<T>::Check(size_type pIndex, const std::string &pMsg) const
{
	if (pIndex >= mData->size()) {
		throw std::out_of_range(pMsg);
	}
}

#endif //blob_h
