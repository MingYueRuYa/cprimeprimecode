#ifndef chronotimer_hpp
#define chronotimer_hpp

#include <chrono>

using std::chrono::high_resolution_clock;

class ChronoTimer {
public:
    ChronoTimer()
    {
        FlushTime();
    }

    virtual ~ChronoTimer() {}

    void FlushTime()
    {
        _time = high_resolution_clock::now();
    }

    double GetSecInterval()
    {
        return GetMicroSecInterval() * 0.000001;
    }

    long long GetMicroSecInterval()
    {
        return std::chrono::duration_cast<std::chrono::microseconds>(high_resolution_clock::now()-_time).count();
    }

private:
    std::chrono::time_point<high_resolution_clock> _time;

};

#endif // chronotimer_hpp