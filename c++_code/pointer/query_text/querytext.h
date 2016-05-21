/****************************************************************
 **
 **	Copyright (C) 2016 635672377@qq.com
 ** All rights reserved.
 **
 ***************************************************************/

#ifndef queytext_h

#define querytext_h

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <memory>

using namespace std;
using std::shared_ptr;

class QueryResult;

class QueryText {

public:
	using LineNo = vector<string>::size_type;

	QueryText(const string &filepath);

	~QueryText();

	QueryResult Query(const string &pKeyWord);

private:
	shared_ptr<vector<string> > mShared_Vector;

	map<string, shared_ptr<set<LineNo> > > mString_Set_Map;

};

class QueryResult {
public:
	friend std::ostream& print(std::ostream &pCout, const QueryResult& pQueryResult);	

public:
	QueryResult(string pKeyWord, shared_ptr<vector<string> > pShared_Vector, shared_ptr<set<QueryText::LineNo> > pShared_Set);
	
	~QueryResult();

	string GetKeyWord() const;

//private:
	string mKeyWord;
	
	shared_ptr<vector<string> > mShared_Vector;

	shared_ptr<set <QueryText::LineNo> > mShared_Set;
};

std::ostream& print(std::ostream &pCout, const QueryResult& pQueryResult);	

#endif //queytext_h
