#include <functional>
#include <vector>
#include <time.h>
#include <algorithm>

using namespace std;

namespace stl_function {
    template<typename itr, typename Compare>
    itr my_find_if(itr begin, itr end, Compare compare)
    {
        while(begin != end)
        {
            if (compare(*begin))
            {
                return begin;
            }
            ++begin;
        }
        return end;
    }


    int test_function1()
    {
        vector<int> vec;
        srand(time(nullptr));
        //初始化容器中的变量
        for (int i = 0; i < 20; ++i)
        {
            vec.push_back(rand() % 100 + 1);
        }

        sort(vec.begin(), vec.end(), greater<int>()); // 大到小排序

        for_each(vec.begin(), vec.end(), [] (int number) ->void { cout << number << " "; });
        cout << endl;
        //在这里我们把元素70按序插入
        // auto it1 = find_if(vec.begin(), vec.end(), bind1st(greater<int>(), 70));
        // 自定义find_if函数
        auto it1 = my_find_if(vec.begin(), vec.end(), std::bind(greater<int>(), 70, std::placeholders::_1));

        if (it1 != vec.end())
        {
            vec.insert(it1, 70);
        }

        for_each(vec.begin(), vec.end(), [] (int number) ->void { cout << number << " "; });
        cout << endl;

        return 0;
    }


    int sum(int a, int b)
    {
        return a+b;
    }

    class TestClassSum
    {
    public:
        TestClassSum() = default;
        ~TestClassSum() = default;

        int sum(int a, int b)
        {
            return a+b;
        }
    };
    void test_function2()
    {
        function<int(int, int)> sum_func = sum;
        cout << "sum:" << sum_func(1, 2) << endl;

        // 类的成员函数，需要使用std::bind包装一层
        function<int(int, int)> class_sum_func = bind(&TestClassSum::sum, 
                TestClassSum(), placeholders::_1, placeholders::_2);
        cout <<  "test class memeber func:" << class_sum_func(10, 20) << endl;
    }

    // 自定义function,Ret返回值, Args参数
    template<typename Fty>
    class my_function{};
    template<typename Ret, typename... Args>
    class my_function< Ret(Args...) >
    {
    public:
        using pFunc = Ret(*)(Args...);
        explicit my_function(pFunc func): func_(func)
        {}

        Ret operator()(Args...args)
        {
            return func_(args...);
        }

    private:
        pFunc func_;
    };

    void test_my_func()
    {
        my_function<int(int, int)> sum_func(sum);
        cout << "test custom function:"<< sum_func(10, 30) << endl;
    }
}