#ifndef strblob_h

#define strblob_h

#include <iostream>
#include <memory>
#include <string>
#include <exception>
#include <initializer_list>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

using namespace std;
using namespace boost;

class StrBlob
{
public:
	typedef vector<string>::size_type size_type;

	StrBlob();
	
	StrBlob(initializer_list<string> il);

	size_type size() const;

	bool empty() const;

	void push_back(const string &pStr);

	void pop_back();

	string& front();

	string& back();

private:
	boost::shared_ptr<vector<string>>	data;

	void check(size_type i, const string &msg) const;

};

#endif //strblob_h
