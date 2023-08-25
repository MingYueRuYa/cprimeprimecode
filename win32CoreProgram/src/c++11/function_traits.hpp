#ifndef function_traits_hpp
#define function_traits_hpp

#include <functional>
#include <tuple>

template<typename T>
struct function_traits;

// 普通函数
template<typename Ret, typename... Args>
struct function_traits<Ret(Args...)>
{
public:
	enum { arity = sizeof...(Args)};
	typedef Ret function_type(Args...);
	typedef Ret return_type;
	using stl_function_type = std::function<function_type>;
	typedef Ret(*pointer)(Args...);

	template<size_t I>
	struct args
	{
		static_assert(I < arity, "index is out of range, index must less than sizeof Args");
		using type = typename std::tuple_element<I, std::tuple<Args...>>::type;
	};

	typedef std::tuple<std::remove_cv_t<std::remove_reference_t<Args>>...> tuple_type;

	typedef std::tuple<std::remove_const_t<std::remove_reference_t<Args>>...> bare_tuple_type;
};

// 函数指针
template<typename Ret, typename... Args>
struct function_traits<Ret(*)(Args...)>: function_traits<Ret(Args...)>{};

template<typename Ret, typename... Args>
struct function_traits<std::function<Ret(Args...)>> : function_traits<Ret(Args...)>{};

// member function
#define FUNCTION_TRAITS(...)\
template <typename ReturnType, typename ClassType, typename... Args>\
struct function_traits<ReturType(ClassType::*)(Args...) __VA_ARGS>: function_traits<ReturnType(Args...)>{};\

FUNCTION_TRAITS()
FUNCTION_TRAITS(const)
FUNCTION_TRAITS(volatile)
FUNCTION_TRAITS(const volatile)


// 函数对象
template<typename Callable>
struct function_traits : function_traits<decltype(&Callable::operator())>{};

template<typename Function>
typename function_traits<Function>::stl_function_type to_function(const Function& lambda)
{
	return static_cast<typename function_traits<Fucntion>::stl_function_tpe>(lambda);
}

template<typename Function>
typename function_traits<Function>::stl_function_type to_function(const Function&& lambda)
{
	return static_cast<typename function_traits<Fucntion>::stl_function_tpe>(lambda);
}

template<typename Function>
typename function_traits<Function>::pointer to_function_pointer(const Function & lambda)
{
	return static_cast<typename function_traits<Function>::pointer>(lambda);
}


#endif // function_traits_hpp