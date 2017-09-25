/****************************************************************************
**
** Copyright (C) 2017 liushixiongcpp@163.com
** All rights reserved.
**
****************************************************************************/

/*
* 备忘录模式：在不破坏的封装的前提下，捕获一个对象的内部状态。并在改对象之外保存该状态。
* 	在需要的时候在恢复到原先的状态
*
*/

#ifndef memento_h
#define memento_h

#include <iostream>
#include <string>
#include <map>

using std::map;
using std::pair;

using std::cout;
using std::endl;

using std::string;

namespace memento
{
class Memento
{
public:
    Memento() 
    {
        mVitality = -1;
        mAttack   = -1;
        mDefense  = -1;
    }

    Memento(const int &pVitality, const int &pAttack, const int &pDefense) :
        mVitality(pVitality), mAttack(pAttack), mDefense(pDefense) 
    {}

    ~Memento() = default;

    Memento(const Memento &pMemento)
    {
        CopyValue(pMemento);
    }

    Memento &operator= (const Memento &pMemento)
    {
        CopyValue(pMemento);
        return *this;
    }

    void SetVitality(const int &pVitality) { mVitality = pVitality; }
    int GetVitality() const { return mVitality; }

    void SetAttack(const int &pAttack) { mAttack = pAttack; }
    int GetAttack() const { return mAttack; }

    void SetDefense(const int &pDefense) { mDefense = pDefense; }
    int GetDefense() const { return mDefense; }

private:
    void CopyValue(const Memento &pMemento)
    {
        mVitality = pMemento.mVitality;
        mAttack = pMemento.mAttack;
        mDefense = pMemento.mDefense;
    }

private:
    int mVitality;
    int mAttack;
    int mDefense;

};

class GameRole
{

public:
    GameRole(const int &pVitality, const int &pAttack, const int &pDefense) : 
        mMemento(pVitality, pAttack, pDefense) 
    {}

    ~GameRole() = default;

    void Load(const Memento &pMemento) { mMemento = pMemento; }

    Memento Save()
    {
       return mMemento;
    }

    void Vitality(const int pVitality)
    {
        mMemento.SetVitality(mMemento.GetVitality() - (-pVitality));
    }

    void Attack(const int pAttackVal)
    {
        mMemento.SetAttack(mMemento.GetAttack() - (-pAttackVal));
    }

    void Defense(const int pDefense)
    {
        mMemento.SetDefense(mMemento.GetDefense() - (-pDefense));
    }

    void Show()
    {
        cout << "vitality:" << mMemento.GetVitality() << " attack:" << mMemento.GetAttack() << " defense:" << mMemento.GetDefense() << endl;
    }

private:
    Memento mMemento;

};

class CareTake
{
public:
    CareTake() = default;

    ~CareTake() = default;

    Memento GetMemento(const string &pName) { return mStrMementoMap[pName]; }

    void SaveMemento(const string &pName, const Memento &pMemento) { mStrMementoMap[pName] = pMemento; }

private: 
    map<string, Memento> mStrMementoMap;

};

    static void test_memento()
    {
        cout << "######################################\n" \
                "##  this is memento demo...         ##\n" \
                "##                                  ##\n" \
                "######################################"   \
             << endl;

        //封装的还不够好，客户端的责任比较重。需要知道GameRole和CareTake两个class。目前是按照GOF的UML图实现功能
        GameRole role(10, 20, 20);
        CareTake caretake; 
        caretake.SaveMemento("1", role.Save());
        role.Show();

        role.Attack(-5);
        role.Vitality(5);
        role.Defense(2);
        caretake.SaveMemento("2", role.Save());
        role.Show();
        
        //恢复1状态
        role.Load(caretake.GetMemento("1"));
        role.Show();

        //恢复2状态
        role.Load(caretake.GetMemento("2"));
        role.Show();

    }

};

#endif //memento_h
