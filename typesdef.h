#pragma once

#include <type_traits>

//Ret(Function<Context>, Context...)
#define Ret(func,...) typename func<__VA_ARGS__>::ret
//#define Ret(func_name,...) typename func_name::template Func<List<__VA_ARGS__>>::ret

//有时可能遇到Ret嵌套，这将导致两个以上typename叠加. 这时使用RawRet
//#define RawRet(func,...) func<__VA_ARGS__>::ret

#ifdef _MSC_VER
#define MK_CHAR(x) #@x
#else
#define MK_CHAR(x)\
'\
x\
'
#endif

#define NEED_FORMATTED

struct Arg
{
    friend struct Format;
#ifndef NEED_FORMATTED
    template <typename T, T value>
    struct _;
#else
private:
    template <int n> struct Int;
    //template <char c> struct Char;
    //template <bool b> struct Bool;
    struct True;
    struct False;

    template<typename T, T value>
    struct Undefined;

public:
    template <typename T, T value>
    struct _
    {
        using formatted = Undefined<T, value>;
    };

    template <int n>
    struct _<int, n>
    {
        using formatted = Int<n>;
    };

    template<>
    struct _<bool, true>
    {
        using formatted = True;
    };
    template<>
    struct _<bool, false>
    {
        using formatted = False;
    };

#pragma region CHAR

#define __GEN_CH_MAKER(type,c)                  \
private:                                        \
    struct type##Char_##c##_;                   \
public:                                         \
    template <>                                 \
    struct _<char, MK_CHAR(c)>           \
    {                                           \
        using formatted = type##Char_##c##_;    \
    }

private:
    template<char c> struct SpecialChar_ASCII;
public:
    template<char c>
    struct _<char, c>
    {
        using formatted = SpecialChar_ASCII<c>;
    };

    __GEN_CH_MAKER(Number, 0);
    __GEN_CH_MAKER(Number, 1);
    __GEN_CH_MAKER(Number, 2);
    __GEN_CH_MAKER(Number, 3);
    __GEN_CH_MAKER(Number, 4);
    __GEN_CH_MAKER(Number, 5);
    __GEN_CH_MAKER(Number, 6);
    __GEN_CH_MAKER(Number, 7);
    __GEN_CH_MAKER(Number, 8);
    __GEN_CH_MAKER(Number, 9);
    __GEN_CH_MAKER(Letter, A);
    __GEN_CH_MAKER(Letter, B);
    __GEN_CH_MAKER(Letter, C);
    __GEN_CH_MAKER(Letter, D);
    __GEN_CH_MAKER(Letter, E);
    __GEN_CH_MAKER(Letter, F);
    __GEN_CH_MAKER(Letter, G);
    __GEN_CH_MAKER(Letter, H);
    __GEN_CH_MAKER(Letter, I);
    __GEN_CH_MAKER(Letter, J);
    __GEN_CH_MAKER(Letter, K);
    __GEN_CH_MAKER(Letter, L);
    __GEN_CH_MAKER(Letter, M);
    __GEN_CH_MAKER(Letter, N);
    __GEN_CH_MAKER(Letter, O);
    __GEN_CH_MAKER(Letter, P);
    __GEN_CH_MAKER(Letter, Q);
    __GEN_CH_MAKER(Letter, R);
    __GEN_CH_MAKER(Letter, S);
    __GEN_CH_MAKER(Letter, T);
    __GEN_CH_MAKER(Letter, U);
    __GEN_CH_MAKER(Letter, V);
    __GEN_CH_MAKER(Letter, W);
    __GEN_CH_MAKER(Letter, X);
    __GEN_CH_MAKER(Letter, Y);
    __GEN_CH_MAKER(Letter, Z);
    __GEN_CH_MAKER(Letter, a);
    __GEN_CH_MAKER(Letter, b);
    __GEN_CH_MAKER(Letter, c);
    __GEN_CH_MAKER(Letter, d);
    __GEN_CH_MAKER(Letter, e);
    __GEN_CH_MAKER(Letter, f);
    __GEN_CH_MAKER(Letter, g);
    __GEN_CH_MAKER(Letter, h);
    __GEN_CH_MAKER(Letter, i);
    __GEN_CH_MAKER(Letter, j);
    __GEN_CH_MAKER(Letter, k);
    __GEN_CH_MAKER(Letter, l);
    __GEN_CH_MAKER(Letter, m);
    __GEN_CH_MAKER(Letter, n);
    __GEN_CH_MAKER(Letter, o);
    __GEN_CH_MAKER(Letter, p);
    __GEN_CH_MAKER(Letter, q);
    __GEN_CH_MAKER(Letter, r);
    __GEN_CH_MAKER(Letter, s);
    __GEN_CH_MAKER(Letter, t);
    __GEN_CH_MAKER(Letter, u);
    __GEN_CH_MAKER(Letter, v);
    __GEN_CH_MAKER(Letter, w);
    __GEN_CH_MAKER(Letter, x);
    __GEN_CH_MAKER(Letter, y);
    __GEN_CH_MAKER(Letter, z);
#pragma endregion
#endif
};

//MSVC将__VA_ARGS__看做为一个参数整体，所以必须加中间层__Expand
#define __Expand(...)                           __VA_ARGS__
//#define __MK_UNTYPED_ARG(value)               Arg__<std::decay_t<decltype(value)>,value>
#define __MK_TYPED_ARG(type,value)              Arg::_<type,(value)>
#define __MK_UNTYPED_ARG(value)                 __MK_TYPED_ARG(decltype(value),value)
#define __FIND_3RD_ARG(arg1,arg2,arg3,...)      arg3
//用于创建新变量，可省略类型说明
//Arg(optional type, value)
#define ARG(...)                                __Expand(\
                                                    __Expand(\
                                                        __FIND_3RD_ARG(\
                                                            __VA_ARGS__, __MK_TYPED_ARG, __MK_UNTYPED_ARG))\
                                                    (__VA_ARGS__))

// TODO：重构Type函数
#define Type(...) Ret(_getType::template Func,__VA_ARGS__)
struct _getType
{
    template<typename T> struct Func;
    template<typename U, U value>
    struct Func<ARG(U, value)> { using ret = U; };
};

//不能使用auto，否则输出将无法正确读取类型名
#define Value(...) _getValue::template Func<__VA_ARGS__>::ret
struct _getValue
{
    template<typename T> struct Func;
    template<typename U, U value>
    struct Func<ARG(U, value)> { static constexpr U ret = value; };
};

template<int n>    using Int = ARG(int, n);
template<bool b>   using Bool = ARG(bool, b);
template<char c>   using Char = ARG(char, c);

using True = Bool<true>;
using False = Bool<false>;