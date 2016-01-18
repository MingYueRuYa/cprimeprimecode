
#ifndef basemanager_h

#define basemanager_h

class BaseManager
{
public:
	BaseManager();

	~BaseManager();

	virtual bool Save();

	virtual bool Load();

	virtual bool Search();

};

#endif //basemanager_h

