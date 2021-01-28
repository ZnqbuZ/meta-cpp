#pragma once

#include "typesdef.h"

#define __DEFN_TYPED_UNARY_FUN(type,name,arg,expr)          \
struct _##name                                              \
{                                                           \
    template<typename args> struct Func;                    \
    template<typename T, T arg>                             \
    struct Func<List<Arg(T, arg)>>                          \
    {                                                       \
        using ret = Arg(type, expr);                        \
    };                                                      \
}

#define __DEFN_UNTYPED_UNARY_FUN(name,arg,expr)             \
        __DEFN_TYPED_UNARY_FUN(T,name,arg,expr)

#define __FIND_5TH_ARG(arg1,arg2,arg3,arg4,arg5,...)        arg5

#define DEFN_UNARY_FUN(...)                                 \
        __Expand(                                           \
            __Expand(                                       \
                __FIND_5TH_ARG(                             \
                    __VA_ARGS__,                            \
                    __DEFN_TYPED_UNARY_FUN,                 \
                    __DEFN_UNTYPED_UNARY_FUN))              \
            (__VA_ARGS__))

#define __DEFN_TYPED_BINARY_FUN(type,name,arg1,arg2,expr)   \
struct _##name                                              \
{                                                           \
    template<typename args> struct Func;                    \
    template<                                               \
        typename T, T arg1,                                 \
        typename V, V arg2>                                 \
    struct Func<                                            \
            List<                                           \
                Arg(T, arg1),                               \
                Arg(V, arg2)>>                              \
    {                                                       \
        using ret = Arg(type, expr);                        \
    };                                                      \
}

#define __DEFN_UNTYPED_BINARY_FUN(name,arg1,arg2,expr)      \
        __DEFN_TYPED_BINARY_FUN(T,name,arg1,arg2,expr)

#define __FIND_6TH_ARG(arg1,arg2,arg3,arg4,arg5,arg6,...)   arg6

#define DEFN_BINARY_FUN(...)                                \
        __Expand(                                           \
            __Expand(                                       \
                __FIND_6TH_ARG(                             \
                    __VA_ARGS__,                            \
                    __DEFN_TYPED_BINARY_FUN,                \
                    __DEFN_UNTYPED_BINARY_FUN))             \
            (__VA_ARGS__))

//后继
//Inc(Arg: M)::Ret = (M)Arg: M++
//#define Inc(...) Ret(_Inc,__VA_ARGS__)
//template<typename M> struct _Inc { using ret = Arg(Type(M), Value(M) + 1); };

DEFN_UNARY_FUN(Inc, x, x + 1);
#define Inc(...) Ret(_Inc::Func, List<__VA_ARGS__>)

//相反数
//Neg(Arg: M)::Ret = (M)Arg: -M
//#define Neg(...) Ret(_Neg,__VA_ARGS__)
//template<typename M> struct _Neg { using ret = Arg(Type(M), -Value(M)); };

DEFN_UNARY_FUN(Neg, x, -x);
#define Neg(...) Ret(_Neg::Func, List<__VA_ARGS__>)

//前驱
//Dec(Arg: M)::Ret = (M)Arg: M--
//#define Dec(...) Neg(Inc(Neg(__VA_ARGS__))
//#define Dec(...) Ret(_Dec,__VA_ARGS__)
//template<typename M> struct _Dec { using ret = Arg(Type(M), Value(M) - 1); };

DEFN_UNARY_FUN(Dec, x, x - 1);
#define Dec(...) Ret(_Dec::Func, List<__VA_ARGS__>)

#pragma region 四则运算

//Add(Arg: M, Arg: N)::Ret = (M)Arg: M+N
//#define Add(...) Ret(_Add,__VA_ARGS__)
//template<typename M, typename N> struct _Add { using ret = Arg(Type(M), Value(M) + Value(N)); };

DEFN_BINARY_FUN(Add, x, y, x + y);
#define Add(...) Ret(_Add::Func, List<__VA_ARGS__>)

//Sub(Arg: M, Arg: N)::Ret = (M)Arg: M-N
//#define Sub(...) Ret(_Sub,__VA_ARGS__)
//template<typename M, typename N> struct _Sub { using ret = Arg(Type(M), Value(M) - Value(N)); };

DEFN_BINARY_FUN(Sub, x, y, x - y);
#define Sub(...) Ret(_Sub::Func, List<__VA_ARGS__>)

//Mul(Arg: M, Arg: N)::Ret = (M)Arg: M*N
//#define Mul(...) Ret(_Mul,__VA_ARGS__)
//template<typename M, typename N> struct _Mul { using ret = Arg(Type(M), Value(M)* Value(N)); };

DEFN_BINARY_FUN(Mul, x, y, x* y);
#define Mul(...) Ret(_Mul::Func, List<__VA_ARGS__>)

//Div(Arg: M, Arg: N)::Ret = (M)Arg: M/N
//#define Div(...) Ret(_Div,__VA_ARGS__)
//template<typename M, typename N> struct _Div { using ret = Arg(Type(M), Value(M) / Value(N)); };

DEFN_BINARY_FUN(Div, x, y, x / y);
#define Div(...) Ret(_Div::Func, List<__VA_ARGS__>)

//Mod(Arg: M, Arg: N)::Ret = (M)Arg: M%N
//#define Mod(...) Ret(_Mod,__VA_ARGS__)
//template<typename M, typename N> struct _Mod { using ret = Arg(Type(M), Value(M) % Value(N)); };

DEFN_BINARY_FUN(Mod, x, y, x% y);
#define Mod(...) Ret(_Mod::Func, List<__VA_ARGS__>)

#pragma endregion

#pragma region 位运算
//And(Arg: A, Arg: B)::Ret = (A)Arg: A&B
//#define And(...) Ret(_And,__VA_ARGS__)
//template<typename A, typename B> struct _And { using ret = Arg(Type(A), Value(A)& Value(B)); };

DEFN_BINARY_FUN(And, x, y, x& y);
#define And(...) Ret(_And::Func, List<__VA_ARGS__>)

//Or(Arg: A, Arg: B)::Ret = (A)Arg: A|B
//#define Or(...) Ret(_Or,__VA_ARGS__)
//template<typename A, typename B> struct _Or { using ret = Arg(Type(A), Value(A) | Value(B)); };

DEFN_BINARY_FUN(Or, x, y, x | y);
#define Or(...) Ret(_Or::Func, List<__VA_ARGS__>)

//Not(Arg: A)::Ret = (A)Arg: !A
//#define Not(...) Ret(_Not,__VA_ARGS__)
//template<typename A> struct _Not { using ret = Arg(Type(A), ~Value(A)); };
//template<bool b> struct _Not<Bool<b>> { using ret = Bool<!b>; };

DEFN_UNARY_FUN(Not, x, ~x);
template<bool b> struct _Not::Func<Arg(b)> { using ret = Arg(!b); };
#define Not(...) Ret(_Not::Func, List<__VA_ARGS__>)

//Or(Arg: A, Arg: B)::Ret = (A)Arg: A^B
//#define Xor(...) Ret(_Xor,__VA_ARGS__)
//template<typename A, typename B> struct _Xor { using ret = Arg(Type(A), Value(A) ^ Value(B)); };

DEFN_BINARY_FUN(Xor, x, y, x^ y);
#define Xor(...) Ret(_Xor::Func, List<__VA_ARGS__>)

//NAnd(Arg: A, Arg: B)::Ret = (A)Arg: !(A&B)
#define NAnd(...) Not(And(__VA_ARGS__))
//NOr(Arg: A, Arg: B)::Ret = (A)Arg: !(A|B)
#define NOr(...) Not(Or(__VA_ARGS__))
#pragma endregion
