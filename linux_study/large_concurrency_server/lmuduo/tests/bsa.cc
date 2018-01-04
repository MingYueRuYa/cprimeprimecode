#include <boost/static_assert.hpp>

class Timestamp
{
private: 
	int64_t microSecondSinceEproch_;
	// int microSecondSinceEproch_;
};

// 编译时期检查
BOOST_STATIC_ASSERT(sizeof(Timestamp) == sizeof(int64_t));

int main(void)
{
	return 0;
}

