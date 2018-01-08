/*
 *	08 别让异常逃离析构函数
 *  如果析构函数可能会爆出异常，比如说关闭数据库连接的时候。
 *  那么采用设计方式解决。比如提供一个Close接口，让用户自己去调用，
 *  如果发生了异常，那么用户自己也有处理的机会，但是用户自己不调用Close，
 *  说明用户不关心异常。与我们何干。但是我们在析构函数里面依然要走老路吐下
 *  异常或者是终止程序。
 * */

#include <iostream>

using std::cout;
using std::endl;

/*
 * 数据库连接对象
 * */
class DBConnection {
public:
	DBConnection() {
		cout << "DBConnection ctor..." << endl;
	}

	~DBConnection() = default;

	void Close() {
		// 测试代码
		throw ("abc");
		cout << "close DB connection..." << endl;
	}

};

/*
 * 数据库连接管理对象
 * */
class DBController {
public:
	DBController() {
		cout << "DBController ctor..." << endl;
	}

	~DBController() {
		try {
			if (! mIsClosed) {
				mDBConnection.Close();
			}
		} catch (const char *msg) {
			cout << msg << endl;
		}
	}

	void Close() {
		mIsClosed = true;
		mDBConnection.Close();
	}

private:
	DBConnection mDBConnection;
	bool 		 mIsClosed;
};

int main(int argc, char *argv[])
{
	DBController dbc;
	try {
		dbc.Close();	//让用户自己关闭连接
	} catch (const char *msg) {
		cout << msg << endl;
	}
	return 0;
}
