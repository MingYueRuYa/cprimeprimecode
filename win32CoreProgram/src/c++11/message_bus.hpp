#ifndef message_bus_h
#define message_bus_h

#include <string>
#include <map>
#include <any>

#include "function_traits.hpp"

using std::string;

class NonCopyable {
 public:
  NonCopyable(const NonCopyable&) = delete;             // deleted
  NonCopyable& operator=(const NonCopyable&) = delete;  // deleted
  NonCopyable() = default;                              // available
};

class MessageBus : public NonCopyable {
 public:
  // 注册消息
  template <typename F>
  void Attach(F&& f, const string& strTopic = "") {
    auto func = to_function(std::forward<F>(f));
    Add(strTopic, std::move(func));
  }

  template <typename R>
  void SendSeq(const string& strTopic = "") {
    using function_type = std::function<R()>;
    string strMsgType = strTopic + typeid(function_type).name();
    auto range = m_map.equal_range(strMsgType) for (Iterator it = range.first;
                                                    it != range.second; ++it) {
      auto f = std::any_cast<function_type>(it->second);
      f();
    }
  }

  template <typename R, typename... Args>
  void SendReq(Args&&... args, const string& strTopic = "") {
    using function_type = std::function<R(Args...)>;
    string strMsgType = strTopic + typeid(function_type).name();
    auto range = m_map.equal_range(strMsgType);
    for (Iterator it = range.first; it != range.second; ++it) {
      auto f = std::any_cast<function_type>(it->second);
      f(std::forward<Args>(args)...);
    }
  }

  // 移除某个消息主题， 需要主题和消息类型
  template <typename R, typename... Args>
  void Remove(const string& strTopic = "") {
    using function_type = std::function<R(Args...)>;
    string strMsgType = strTopic + typeid(function_type).name();
    int count = m_map.count(strMsgType);
    auto range = m_map.equal_range(strMsgType);
    m_map.erase(range.first, range.second);
  }

 private:
  template <typename F>
  void Add(const string& strTopic, F&& f) {
    string strMsgType = strTopic + typeid(f).name();
    m_map.emplace(std::move(strMsgType), std::forward<F>(f));
  }

 private:
  std::multimap<string, std::any> m_map;
  typedef std::multimap<string, std::any>::iterator Iterator;
};

#endif  // message_bus_h