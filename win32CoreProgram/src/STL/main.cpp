#include <set>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

#include "../common/chronotimer.hpp"

using std::set;
using std::cout;
using std::endl;
using std::vector;
using std::string;

struct Student
{
    Student(int id, string name)
        : ID(id), mName(name)
    {
    }
    int ID;
    string mName;

    Student& operator=(const Student &rhs)
    {
        this->ID = rhs.ID;
        this->mName = rhs.mName;
    }

public:
    // 注意这里的是const operator< 类型
    bool operator<(const Student &rhs) const
    {
        return (this->ID < rhs.ID);
    }
};

// 测试set自定义比较函数
int test_set_main(int argc, char *argv[])
{
    set<Student> set_student; 

    set_student.insert(Student(5, "linux"));
    set_student.insert(Student(5, "linux01"));
    set_student.insert(Student(3, "unix"));
    set_student.insert(Student(7, "FreeBSD"));

    std::for_each(set_student.begin(), set_student.end(), 
        [](const Student &stu) { cout << stu.ID << " " << stu.mName << endl; });


    return 0;
}

#include <map>

using std::map;

struct MapEntity
{
public:
    MapEntity(int id) 
    {
        age     = 0;
        width   = 0;
        height  = 0;
        num_id  = 0;
        name    = "";
    }

    MapEntity() 
    {
        age     = 0;
        width   = 0;
        height  = 0;
        num_id  = 0;
        name    = "";
    }

    MapEntity &operator=(const MapEntity &mapEntity)
    {
        if (this == &mapEntity) { return *this; }

        this->age     = mapEntity.age;
        this->width   = mapEntity.width;
        this->height  = mapEntity.height;
        this->name    = mapEntity.name;
        this->num_id  = mapEntity.num_id;

        return *this;
    }

    MapEntity(const MapEntity &mapEntity)
    {
        this->age     = mapEntity.age;
        this->width   = mapEntity.width;
        this->height  = mapEntity.height;
        this->name    = mapEntity.name;
        this->num_id  = mapEntity.num_id;
    }

    int age;
    int width;
    int height;
    int num_id;
    string name;
};

#include <map>

using std::map;

using EntityMap = map<int, MapEntity>;

template <typename MapType, typename KeyArgType, typename ValueArgType>
typename MapType::iterator efficentAddOrUpdate(MapType &mapType, 
                                            const KeyArgType &keyArgType,
                                            const ValueArgType &valueArgType)
{
    typename MapType::iterator ifind = mapType.lower_bound(keyArgType);

    // 如果key已经存在就是更新操作
    if (ifind != mapType.end() && 
        ! (mapType.key_comp()(keyArgType, ifind->first))) {

        ifind->second = valueArgType;

        return ifind;
    } else {    // 不存在就执行insert操作
        typedef typename MapType::value_type MVT;

        return mapType.insert(ifind, MVT(keyArgType, valueArgType));
    }
}

int test_map_main(int argc, char *argv[])
{
    ChronoTimer chrono_timer;

#define test_operator 1

#ifdef test_operator
    EntityMap entity_map;
    for (int i = 0; i < 1000000; ++i) {
        entity_map[i] = MapEntity(i);
    }

    cout << "插入1,000,000 需要的时间秒：" << chrono_timer.GetSecInterval() << endl;

    chrono_timer.FlushTime();
    for (int i = 0; i < 1000000; ++i) {
        entity_map[i] = MapEntity(i);
    }

    cout << "使用map operator[]需要的时间秒：" << chrono_timer.GetSecInterval() << endl;

    efficentAddOrUpdate(entity_map, 1000000, MapEntity(10000000));

#else
    // 如果是纯粹的插入操作，map 的insert效率会比较高，大概是(23-20)/23=13%
    EntityMap insert_entity_map;
    for (int i = 0; i < 1000000; ++i) {
        insert_entity_map.insert(std::pair<int, MapEntity>(i, MapEntity(i)));
    }

    cout << "使用map insert需要的时间秒：" << chrono_timer.GetSecInterval() << endl;
#endif // test_operator

    getchar();
     
    return 0;
}

template <typename T>
struct base
{

    void interface()
    {
        T &derived = static_cast<T &>(*this);
        derived.Implementation();
    }

};

struct derive : public base<derive>
{
    void Implementation()
    {
        cout << "child dosomething" << endl;
    }

};

struct grandson : public base<grandson>
{
    void Implementation()
    {
        cout << "grandson dosomething" << endl;
    }

};

template <typename T>
void Action(base<T> &child)
{
    child.interface();
}


// 测试模板的奇异模板递归
/*
    将动态的绑定，转化为在编译期间的绑定，这样做是为了避免虚函数的开销。
    但是无法真正做到运行时的动态绑定,
    在智能指针shared_ptr中返回自己的时候，也是用到了CRTP技术。
*/
int test_CRTP_main(int argc, char *argv[])
{
    derive child;
    Action(child);

    grandson son;
    Action(son);
    /*
    derive child;
    child.interface();

    grandson son;
    son.interface();
    */

    getchar();
    return 0;
}

int test_back_inserter_main(int argc, char *argv[])
{
    vector<int> vec_int;  
    vec_int.reserve(16);
    vec_int = {1, 2, 3, 4};
    vector<int> vec_int2 = {1, 2, 3, 4, 5, 6, 7, 8};

    std::copy(vec_int2.begin(), vec_int2.end(), std::back_inserter(vec_int));

    // std::transform(vec_int2.begin(), vec_int2.end(), std::back_insert(vec_int));
    // std::copy(vec_int2.begin(), vec_int2.end(), vec_int.begin());

    vector<int> vec_int3 = {9, 10, 11, 12, 13, 14, 15, 16};
    std::transform(vec_int3.begin(), vec_int3.end(), vec_int.begin(), [](int value) { return value; });
    std::transform(vec_int3.begin(), vec_int3.end(), std::back_inserter(vec_int), [](int value) { return value; });

    return 0;
}

class Widget
{
public:
    Widget(int id)
    : mID(id)
    {}

    bool operator<(const Widget &rhs) const
    {
        return this->mID < rhs.mID;
    }

    int GetID() const
    {
        return mID;
    }

private:
    int mID;
};

#include <random>

int main(int argc, char *argv[])
{
    vector<Widget> vec_widget = {Widget(20), Widget(19), Widget(21), Widget(10),
                                    Widget(5), Widget(21), Widget(30), 
                                    Widget(15), Widget(21), Widget(30), 
                                    Widget(1)};    

//    std::partial_sort(vec_widget.begin(), vec_widget.begin()+5, 
//                        vec_widget.end(),
//                        std::less<Widget>());
    cout << "第五个元素:" << vec_widget[1].GetID() << endl;

    std::nth_element(vec_widget.begin(), vec_widget.begin()+5, vec_widget.end());

    std::for_each(vec_widget.begin(), vec_widget.end(), 
        [](const Widget &widget) { cout << widget.GetID() << " "; });
    cout << endl;
    cout << "第五个元素:" << vec_widget[1].GetID() << endl;
    // parital_sort result:
    // 1
    // 5
    // 10
    // 15
    // 19
    // 21
    // 30
    // 21
    // 21
    // 30
    // 20

    vector<int> vec_int;
    vec_int.reserve(100);
   for (int i = 0; i < 100; ++i) {  
        vec_int.push_back (i);  
    }  
    unsigned seed = std::chrono::system_clock::now ().time_since_epoch().count ();  
    std::shuffle(vec_int.begin(), vec_int.end(), std::default_random_engine(seed));

    cout << "第五个元素" << vec_int[5] << endl;
    std::for_each(vec_int.begin(), vec_int.end(), [](int value) { cout << value << " "; });
    cout << endl;
    cout << "-----------------------" << endl;

    std::nth_element(vec_int.begin(), vec_int.begin()+5, vec_int.end());
    cout << "第五个元素" << vec_int[5] << endl;
    std::for_each(vec_int.begin(), vec_int.end(), [](int value) { cout << value << " "; });
    cout << endl;

    cout << endl;

    return 0;
}
