#include <iostream>
#include <new>

using std::cout;
using std::endl;

class Widget
{
public:
    Widget() { cout << "widget ctor..." << endl; }
    ~Widget() { cout << "~widget dtor..." << endl; }
    
    // normal operator new
    static void *operator new(size_t size) 
    {
        cout << "normal op new" << endl;
        return ::operator new(size);
    }

    // normal operator delete
    static void operator delete(void *pMemory, size_t size) 
    {
        cout << "normal op delete" << endl;
        ::operator delete(pMemory);
    }

    static void *operator new(size_t size, void *pMemory)
    {
        cout << "placement new (size_t size, void *pMemory)" << endl;
        return pMemory;
    }

    static void operator delete(void *pStart, void *pMemory)
    {
        cout << "placement delete(void *pStart, void *pMemory)" << endl;
        return ::operator delete(pStart);
    }

    static void *operator new(size_t size, std::ostream &logstream)
    {
        cout << "placement new (size_t size, std::ostream &logstream)" << endl;
        return ::operator new(size);
    }

    static void operator delete(void *pStart, std::ostream &logstream)
    {
        cout << "placement delete(void *pStart, std::ostream &logstream)" << endl;
        return ::operator delete(pStart);
    }

};

int main(int argc, char *argv[])
{
    Widget *widget = new Widget();
    delete widget;
    widget = NULL;

    Widget tempwidget;
    Widget *placement_widget = new (&tempwidget) Widget();

    Widget *placemet_widget2 = new (std::cerr) Widget();
    delete placemet_widget2;
    return 0;
}
