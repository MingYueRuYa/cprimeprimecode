/****************************************************************
 **
 **	Copyright (C) 2016 635672377@qq.com
 ** All rights reserved.
 **
 ***************************************************************/

#include <fstream>
#include <sstream>
#include <algorithm>

#include <ctype.h>

#include "querytext.h"

using namespace std;

QueryText::QueryText(const string &filepath) : mShared_Vector(new vector<string>())
{
	fstream fs;
	fs.open(filepath.c_str(), fstream::in | fstream::out);
	if (fs.fail()) {
		return;
	}
	string content;
	while (getline(fs, content)) {
		//delete punct
		char punct = content.c_str()[content.length() - 1];
		if (ispunct(punct)) {
			content.erase(content.length()-1, 1);
		}
		mShared_Vector->push_back(content);
	}
	fs.close();

	for (LineNo i = 0; i < mShared_Vector->size(); ++i) {
		content = (*mShared_Vector)[i];
		istringstream stringstream(content);
		string keyword;
		while (stringstream >> keyword) {
			shared_ptr<set<LineNo> > set_ptr = mString_Set_Map[keyword];
			if (NULL == set_ptr) {
				set_ptr.reset(new set<LineNo>);	
				set_ptr->insert(i);
				mString_Set_Map[keyword] = set_ptr;
			} else {
				set_ptr->insert(i);	
			}
		}

	}

//	for_each(mString_Set_Map.begin(), mString_Set_Map.end(),
//			[](const pair<string, shared_ptr<set<int> > > pPair) {
//				cout << pPair.first << " ";
//				set<int>::iterator begin = (pPair.second)->begin();
//				cout << (pPair.second) << endl;
//				for (; begin != (pPair.second)->end(); ++begin) {
//					cout << *begin << " ";
//				}
//				cout << endl;
//			});
	
}

QueryText::~QueryText()
{

}

QueryResult QueryText::Query(const string &pKeyWord)
{
	static shared_ptr<set<LineNo> > nulldata(new set<LineNo>());
	map<string, shared_ptr<set<LineNo> > >::iterator finddata =	mString_Set_Map.find(pKeyWord);
	if (finddata == mString_Set_Map.end()) {
		return QueryResult(pKeyWord, mShared_Vector, nulldata);
	} else {
		return QueryResult(pKeyWord, mShared_Vector, finddata->second);
	}
}

QueryResult::QueryResult(string pKeyWord, shared_ptr<vector<string> > pShared_Vector, shared_ptr<set<QueryText::LineNo> > pShared_Set)
{
	mKeyWord = pKeyWord;
	mShared_Vector = pShared_Vector;
	mShared_Set = pShared_Set;
}

QueryResult::~QueryResult()
{

}

string QueryResult::GetKeyWord() const
{
	return mKeyWord;
}

std::ostream& print(std::ostream &pCout, const QueryResult& pQueryResult)
{
	pCout << pQueryResult.GetKeyWord() << " occurs " << pQueryResult.mShared_Set->size()
		<< (pQueryResult.mShared_Set->size() > 1 ? " times" : " time") << endl;
	
	for (QueryText::LineNo index : *(pQueryResult.mShared_Set)) {
		pCout << "\t(line" << index + 1 << ") " << pQueryResult.mShared_Vector->at(index) << endl;
	}
	pCout << endl;
	return pCout;
}



