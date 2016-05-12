#include "strblob.h"

StrBlob::StrBlob()
	: data(make_shared<vector<string>>())
{

}

StrBlob::StrBlob(initializer_list<string> il)
	: data(make_shared<vector<string>>(il))
{

}

StrBlob::size_type StrBlob::size() const
{
	return data->size();
}

bool StrBlob::empty() const
{
	return data->empty();
}

void StrBlob::push_back(const string &pStr)
{
	data->push_back(pStr);
}

void StrBlob::pop_back()
{
	check(0, "pop_back empty on StrBlob");
	data->pop_back();
}

string& StrBlob::front()
{
	check(0, "front on empty StrBlob");
	return data->front();
}

string& StrBlob::back()
{
	check(0, "back on empty StrBlob");
	return data->back();
}

void StrBlob::check(size_type i, const string &msg) const
{
	if (i >= data->size()) {
		throw out_of_range(msg);
	}
}
