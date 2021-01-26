#pragma once

#include "typesdef.h"

//后继
//Inc(Arg: M)::Ret = (M)Arg: M++
#define Inc(...) Ret(_Inc,__VA_ARGS__)
template<typename M> struct _Inc { using ret = Arg(Type(M), Value(M) + 1); };

//相反数
//Neg(Arg: M)::Ret = (M)Arg: -M
#define Neg(...) Ret(_Neg,__VA_ARGS__)
template<typename M> struct _Neg { using ret = Arg(Type(M), -Value(M)); };

//前驱
//Dec(Arg: M)::Ret = (M)Arg: M--
//#define Dec(...) Neg(Inc(Neg(__VA_ARGS__))
#define Dec(...) Ret(_Dec,__VA_ARGS__)
template<typename M> struct _Dec { using ret = Arg(Type(M), Value(M) - 1); };

#pragma region 四则运算
//Add(Arg: M, Arg: N)::Ret = (M)Arg: M+N
#define Add(...) Ret(_Add,__VA_ARGS__)
template<typename M, typename N> struct _Add { using ret = Arg(Type(M), Value(M) + Value(N)); };
//Sub(Arg: M, Arg: N)::Ret = (M)Arg: M-N
#define Sub(...) Ret(_Sub,__VA_ARGS__)
template<typename M, typename N> struct _Sub { using ret = Arg(Type(M), Value(M) - Value(N)); };
//Mul(Arg: M, Arg: N)::Ret = (M)Arg: M*N
#define Mul(...) Ret(_Mul,__VA_ARGS__)
template<typename M, typename N> struct _Mul { using ret = Arg(Type(M), Value(M)* Value(N)); };
//Div(Arg: M, Arg: N)::Ret = (M)Arg: M/N
#define Div(...) Ret(_Div,__VA_ARGS__)
template<typename M, typename N> struct _Div { using ret = Arg(Type(M), Value(M) / Value(N)); };
#pragma endregion

#pragma region 逻辑运算
//And(Arg: A, Arg: B)::Ret = (A)Arg: A&B
#define And(...) Ret(_And,__VA_ARGS__)
template<typename A, typename B> struct _And { using ret = Arg(Type(A), Value(A)& Value(B)); };
//Or(Arg: A, Arg: B)::Ret = (A)Arg: A|B
#define Or(...) Ret(_Or,__VA_ARGS__)
template<typename A, typename B> struct _Or { using ret = Arg(Type(A), Value(A) | Value(B)); };
//Not(Arg: A)::Ret = (A)Arg: !A
#define Not(...) Ret(_Not,__VA_ARGS__)
template<typename A> struct _Not { using ret = Arg(Type(A), ~Value(A)); };
template<bool b> struct _Not<Bool<b>> { using ret = Bool<!b>; };
//Or(Arg: A, Arg: B)::Ret = (A)Arg: A^B
#define Xor(...) Ret(_Xor,__VA_ARGS__)
template<typename A, typename B> struct _Xor { using ret = Arg(Type(A), Value(A) ^ Value(B)); };
//NAnd(Arg: A, Arg: B)::Ret = (A)Arg: !(A&B)
#define NAnd(...) Not(And(__VA_ARGS__))
//NOr(Arg: A, Arg: B)::Ret = (A)Arg: !(A|B)
#define NOr(...) Not(Or(__VA_ARGS__))
#pragma endregion
