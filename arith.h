#pragma once

#include "typesdef.h"
#include "pair.h"

#define __DEFN_TYPED_UNARY_FUN(name,arg,type,expr)          \
struct _##name                                              \
{                                                           \
    template<typename arg_list> struct Func;                \
    template<typename arg>                                  \
    struct Func<List<arg>>                                  \
    {                                                       \
        using ret = ARG(type, expr);                        \
    };                                                      \
}

#define __DEFN_UNTYPED_UNARY_FUN(name,arg,expr)             \
        __DEFN_TYPED_UNARY_FUN(                             \
            name,arg,Type(arg),expr)

#define __FIND_5TH_ARG(arg1,arg2,arg3,arg4,arg5,...)        arg5

#define DEFN_UNARY_FUN(...)                                 \
        __Expand(                                           \
            __Expand(                                       \
                __FIND_5TH_ARG(                             \
                    __VA_ARGS__,                            \
                    __DEFN_TYPED_UNARY_FUN,                 \
                    __DEFN_UNTYPED_UNARY_FUN))              \
            (__VA_ARGS__))

#define __DEFN_TYPED_BINARY_FUN(name,arg1,arg2,type,expr)   \
struct _##name                                              \
{                                                           \
    template<typename args> struct Func;                    \
    template<                                               \
        typename arg1,                                      \
        typename arg2>                                      \
    struct Func<                                            \
            List<arg1,arg2>>                                \
    {                                                       \
        using ret = ARG(type, expr);                        \
    };                                                      \
}

#define __DEFN_UNTYPED_BINARY_FUN(name,arg1,arg2,expr)      \
        __DEFN_TYPED_BINARY_FUN(                            \
            name,arg1,arg2,Type(arg1),expr)

#define __FIND_6TH_ARG(arg1,arg2,arg3,arg4,arg5,arg6,...)   arg6

#define DEFN_BINARY_FUN(...)                                \
        __Expand(                                           \
            __Expand(                                       \
                __FIND_6TH_ARG(                             \
                    __VA_ARGS__,                            \
                    __DEFN_TYPED_BINARY_FUN,                \
                    __DEFN_UNTYPED_BINARY_FUN))             \
            (__VA_ARGS__))

DEFN_UNARY_FUN(Inc, x, Value(x) + 1);
DEFN_UNARY_FUN(Neg, x, -Value(x));
DEFN_UNARY_FUN(Dec, x, Value(x) - 1);

//后继
//Inc(ARG: M)::Ret = (M)ARG: M++
#define Inc(...) Ret(_Inc::template Func, List<__VA_ARGS__>)

//相反数
//Neg(ARG: M)::Ret = (M)ARG: -M
#define Neg(...) Ret(_Neg::template Func, List<__VA_ARGS__>)

//前驱
//Dec(ARG: M)::Ret = (M)ARG: M--
//TODO：用compose简化定义
#define Dec(...) Ret(_Dec::template Func, List<__VA_ARGS__>)

#pragma region 四则运算

DEFN_BINARY_FUN(Add, x, y, Value(x) + Value(y));
DEFN_BINARY_FUN(Sub, x, y, Value(x) - Value(y));
DEFN_BINARY_FUN(Mul, x, y, Value(x)* Value(y));
DEFN_BINARY_FUN(Div, x, y, Value(x) / Value(y));
DEFN_BINARY_FUN(Mod, x, y, Value(x) % Value(y));

//Add(ARG: M, ARG: N)::Ret = (M)ARG: M+N
#define Add(...) Ret(_Add::template Func, List<__VA_ARGS__>)

//Sub(ARG: M, ARG: N)::Ret = (M)ARG: M-N
#define Sub(...) Ret(_Sub::template Func, List<__VA_ARGS__>)

//Mul(ARG: M, ARG: N)::Ret = (M)ARG: M*N
#define Mul(...) Ret(_Mul::template Func, List<__VA_ARGS__>)

//Div(ARG: M, ARG: N)::Ret = (M)ARG: M/N
#define Div(...) Ret(_Div::template Func, List<__VA_ARGS__>)

//Mod(ARG: M, ARG: N)::Ret = (M)ARG: M%N
#define Mod(...) Ret(_Mod::template Func, List<__VA_ARGS__>)

#pragma endregion

#pragma region 位运算

DEFN_BINARY_FUN(And, x, y, Value(x)& Value(y));
DEFN_BINARY_FUN(Or, x, y, Value(x) | Value(y));
DEFN_UNARY_FUN(Not, x, ~Value(x));
// bool如果用~会有警告
// 我也不知道为什么非得在Arg中指定bool
template<bool b> struct _Not::Func<List<ARG(bool, b)>> { using ret = ARG(!b); };
DEFN_BINARY_FUN(Xor, x, y, Value(x) ^ Value(y));

//And(ARG: A, ARG: B)::Ret = (A)ARG: A&B
#define And(...) Ret(_And::template Func, List<__VA_ARGS__>)

//Or(ARG: A, ARG: B)::Ret = (A)ARG: A|B
#define Or(...) Ret(_Or::template Func, List<__VA_ARGS__>)

//Not(ARG: A)::Ret = (A)ARG: !A
#define Not(...) Ret(_Not::template Func, List<__VA_ARGS__>)

//Or(ARG: A, ARG: B)::Ret = (A)ARG: A^B
#define Xor(...) Ret(_Xor::template Func, List<__VA_ARGS__>)

//NAnd(ARG: A, ARG: B)::Ret = (A)ARG: !(A&B)
#define NAnd(...) Not(And(__VA_ARGS__))

//NOr(ARG: A, ARG: B)::Ret = (A)ARG: !(A|B)
#define NOr(...) Not(Or(__VA_ARGS__))
#pragma endregion
