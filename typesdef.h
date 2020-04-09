#pragma once

//Ret(Function<Context>, Context...)
#define Ret(func,...) typename func<__VA_ARGS__>::ret

//有时可能遇到Ret嵌套，这将导致两个以上typename叠加.这时使用RawRet
#define RawRet(func,...) func<__VA_ARGS__>::ret

#define Type(...) Ret(_getType,__VA_ARGS__)
template<typename T> struct _getType { using ret = typename T::__type; };

//不能使用auto，否则输出将无法正确读取类型名
#define Value(...) _getValue<__VA_ARGS__>::ret
template<typename T> struct _getValue { static constexpr Type(T) ret = T::__value; };

//不允许类型嵌套，如IntType<IntType<1>>
template<typename T, T value> struct Arg__
{
    using __type = T;
    static constexpr T __value = value;
};

//MSVC将__VA_ARGS__看做为一个参数整体，所以必须加中间层__Expand
#define __Expand(...)                           __VA_ARGS__
#define __UntypedArg(value)                     Arg__<decltype(value),value>
#define __TypedArg(type,value)                  Arg__<type,value>
#define __FIND_THIRD_ARG(arg1,arg2,arg3,...)    arg3
//用于创建新变量，可省略类型说明
//Arg(optional type, value)
#define Arg(...)                                __Expand(\
                                                    __Expand(\
                                                        __FIND_THIRD_ARG(\
                                                            __VA_ARGS__,__TypedArg,__UntypedArg))\
                                                    (__VA_ARGS__))
// #define IntType(N)          Arg(int,N)
// #define BoolType(b)         Arg(bool,b)
// #define CharType(ch)        Arg(char,ch)

template<int N>     using Int = Arg__<int, N>;
template<bool b>    using Bool = Arg__<bool, b>;
template<char ch>   using Char = Arg__<char, ch>;

// template<int N> struct IntType { enum { __value = N }; };
// template<bool b> struct BoolType { enum { __value = b }; };
// template<char ch> struct CharType { enum { __value = ch }; };

using True = Bool<true>;
using False = Bool<false>;

struct Null {};