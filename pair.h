#pragma once

#include "typesdef.h"

#ifdef SCHEME
//Scheme式的序对定义，此种定义将使Display输出错误

//序对的元素是不可变的
#define Car(...) Ret(__VA_ARGS__::__dispatcher,True)
#define Cdr(...) Ret(__VA_ARGS__::__dispatcher,False)
//如果需要函数(模板)序对，可将模板包装在一临时结构体中
template<typename T, typename V = Null> struct Cons
{
    //True和False仅仅是标记，所以不使用If
    template<typename b> struct __dispatcher;
    template<> struct __dispatcher<True> { using ret = T; };
    template<> struct __dispatcher<False> { using ret = V; };
};
#endif

#ifndef SCHEME

//序对的元素是不可变的
#define Car(...) __VA_ARGS__::__Car
#define Cdr(...) __VA_ARGS__::__Cdr
//如果需要使用函数(模板)序对，可将模板包装在一临时结构体中
template<typename T, typename U = Null> struct Cons
{
    using __Car = T;
    using __Cdr = U;
};
#endif

//表
#define List(...) Ret(__MK_List, __VA_ARGS__)
template<typename T, typename...Ts> struct __MK_List
{
    using ret = Cons<T, __MK_List<Ts...>>;
};

template<
    template<typename T> typename F>
struct CONS_MAP
{
    template<typename U>
    struct on
    {
        using ret = Ret(F, U);
    };

    template<typename P, typename Q>
    struct on<Cons<P, Q>>
    {
        using ret = Cons<Ret(on, P), Ret(on, Q)>;
    };
};