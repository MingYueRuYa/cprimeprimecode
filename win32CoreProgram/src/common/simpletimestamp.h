/************************************************************************/
/*  ╫зя║вт muduo/base/Timestamp
/************************************************************************/

#ifndef simpletimestamp_h
#define simpletimestamp_h

#include <stdint.h>
#include <string>

using std::string;

namespace XIBAO {

///
/// Time stamp in UTC, in microseconds resolution.
///
/// This class is immutable.
/// It's recommended to pass it by value, since it's passed in register on x64.
///
class SimpleTimeStamp// : // public muduo::copyable,
                  // public boost::equality_comparable<Timestamp>,
                  // public boost::less_than_comparable<Timestamp>
{
public:
    static const string DEFUALT_STYLE;
    static const string STRING_STYLE;

 public:
  ///
  /// Constucts an invalid Timestamp.
  ///
	 SimpleTimeStamp()
    : microSecondsSinceEpoch_(0)
  {
  }

  ///
  /// Constucts a SimpleTimeStamp at specific time
  ///
  /// @param microSecondsSinceEpoch
	 explicit SimpleTimeStamp(int64_t microSecondsSinceEpochArg)
    : microSecondsSinceEpoch_(microSecondsSinceEpochArg)
  {
  }

	 void swap(SimpleTimeStamp& that)
  {
    std::swap(microSecondsSinceEpoch_, that.microSecondsSinceEpoch_);
  }

  // default copy/assignment/dtor are Okay

  string toString() const;
  string toFormattedString(const string formatStyle = SimpleTimeStamp::DEFUALT_STYLE,
                           bool showMicroseconds = true) const;

  bool valid() const { return microSecondsSinceEpoch_ > 0; }

  // for internal usage.
  int64_t microSecondsSinceEpoch() const { return microSecondsSinceEpoch_; }
  time_t secondsSinceEpoch() const
  { return static_cast<time_t>(microSecondsSinceEpoch_ / kMicroSecondsPerSecond); }

  ///
  /// Get time of now.
  ///
  static SimpleTimeStamp now();
  static SimpleTimeStamp invalid()
  {
    return SimpleTimeStamp();
  }

  static SimpleTimeStamp fromUnixTime(time_t t)
  {
    return fromUnixTime(t, 0);
  }

  static SimpleTimeStamp fromUnixTime(time_t t, int microseconds)
  {
	  return SimpleTimeStamp(static_cast<int64_t>(t)* kMicroSecondsPerSecond + microseconds);
  }

  static const int kMicroSecondsPerSecond = 1000 * 1000;

 private:
  int64_t microSecondsSinceEpoch_;
};

inline bool operator<(SimpleTimeStamp lhs, SimpleTimeStamp rhs)
{
  return lhs.microSecondsSinceEpoch() < rhs.microSecondsSinceEpoch();
}

inline bool operator==(SimpleTimeStamp lhs, SimpleTimeStamp rhs)
{
  return lhs.microSecondsSinceEpoch() == rhs.microSecondsSinceEpoch();
}

///
/// Gets time difference of two SimpleTimeStamps, result in seconds.
///
/// @param high, low
/// @return (high-low) in seconds
/// @c double has 52-bit precision, enough for one-microsecond
/// resolution for next 100 years.
inline double timeDifference(SimpleTimeStamp high, SimpleTimeStamp low)
{
  int64_t diff = high.microSecondsSinceEpoch() - low.microSecondsSinceEpoch();
  return static_cast<double>(diff) / SimpleTimeStamp::kMicroSecondsPerSecond;
}

///
/// Add @c seconds to given SimpleTimeStamp.
///
/// @return SimpleTimeStamp+seconds as TimeStamp
///
inline SimpleTimeStamp addTime(SimpleTimeStamp timestamp, double seconds)
{
  int64_t delta = static_cast<int64_t>(seconds * SimpleTimeStamp::kMicroSecondsPerSecond);
  return SimpleTimeStamp(timestamp.microSecondsSinceEpoch() + delta);
}

}

#endif // SimpleTimeStamp_h