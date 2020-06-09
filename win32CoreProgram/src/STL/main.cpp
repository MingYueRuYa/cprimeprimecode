#include <set>
#include <string>
#include <iostream>
#include <algorithm>

#include "../common/chronotimer.hpp"

using std::set;
using std::cout;
using std::endl;
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

int main(int argc, char *argv[])
{
    return 0;
}