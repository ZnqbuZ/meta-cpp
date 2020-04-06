#pragma once

#include "typesdef.h"
#include "pair.h"
#include "algor.h"

//将变量转换为基础形式(Int、Bool、Char、Null)，以警告消息的形式输出
//仅支持输出字符的ASCII码
//必须绑定行号，因为VS输出的行号不准确，而且会合并内容相同的警告消息
#define Display(...) __CastAndBind<__VA_ARGS__,__LINE__>::ret
template<int Line> struct Line__;

template<typename T, int LINE> struct __CastAndBind { using ret = Cons<Arg(Value(T)), Line__<LINE>>; };
template<int LINE> struct __CastAndBind<True, LINE> { using ret = Cons<True, Line__<LINE>>; };
template<int LINE> struct __CastAndBind<False, LINE> { using ret = Cons<False, Line__<LINE>>; };
/*template<bool b, int LINE> struct __CastAndBind<Bool<b>, LINE> { using ret = Cons<Bool<b>, Line__<LINE>>; };*/
template<int LINE> struct __CastAndBind<Null, LINE> { using ret = Cons<Null, Line__<LINE>>; };

#define __LetterTypeGenerator(letter) \
using letter = Arg(#@letter);
struct Letter__
{
#pragma region LowerCase
    __LetterTypeGenerator(a);
    __LetterTypeGenerator(b);
    __LetterTypeGenerator(c);
    __LetterTypeGenerator(d);
    __LetterTypeGenerator(e);
    __LetterTypeGenerator(f);
    __LetterTypeGenerator(g);
    __LetterTypeGenerator(h);
    __LetterTypeGenerator(i);
    __LetterTypeGenerator(j);
    __LetterTypeGenerator(k);
    __LetterTypeGenerator(l);
    __LetterTypeGenerator(m);
    __LetterTypeGenerator(n);
    __LetterTypeGenerator(o);
    __LetterTypeGenerator(p);
    __LetterTypeGenerator(q);
    __LetterTypeGenerator(r);
    __LetterTypeGenerator(s);
    __LetterTypeGenerator(t);
    __LetterTypeGenerator(u);
    __LetterTypeGenerator(v);
    __LetterTypeGenerator(w);
    __LetterTypeGenerator(x);
    __LetterTypeGenerator(y);
    __LetterTypeGenerator(z);
#pragma endregion

#pragma region UpperCase
    __LetterTypeGenerator(A);
    __LetterTypeGenerator(B);
    __LetterTypeGenerator(C);
    __LetterTypeGenerator(D);
    __LetterTypeGenerator(E);
    __LetterTypeGenerator(F);
    __LetterTypeGenerator(G);
    __LetterTypeGenerator(H);
    __LetterTypeGenerator(I);
    __LetterTypeGenerator(J);
    __LetterTypeGenerator(K);
    __LetterTypeGenerator(L);
    __LetterTypeGenerator(M);
    __LetterTypeGenerator(N);
    __LetterTypeGenerator(O);
    __LetterTypeGenerator(P);
    __LetterTypeGenerator(Q);
    __LetterTypeGenerator(R);
    __LetterTypeGenerator(S);
    __LetterTypeGenerator(T);
    __LetterTypeGenerator(U);
    __LetterTypeGenerator(V);
    __LetterTypeGenerator(W);
    __LetterTypeGenerator(X);
    __LetterTypeGenerator(Y);
    __LetterTypeGenerator(Z);
#pragma endregion
};

#define __LetterCastAndBindGenerator(letter) \
template<int LINE> struct __CastAndBind<Letter__::letter, LINE> { using ret = Cons<Letter__::letter, Line__<LINE>>; }

#pragma region LowerCase
__LetterCastAndBindGenerator(a);
__LetterCastAndBindGenerator(b);
__LetterCastAndBindGenerator(c);
__LetterCastAndBindGenerator(d);
__LetterCastAndBindGenerator(e);
__LetterCastAndBindGenerator(f);
__LetterCastAndBindGenerator(g);
__LetterCastAndBindGenerator(h);
__LetterCastAndBindGenerator(i);
__LetterCastAndBindGenerator(j);
__LetterCastAndBindGenerator(k);
__LetterCastAndBindGenerator(l);
__LetterCastAndBindGenerator(m);
__LetterCastAndBindGenerator(n);
__LetterCastAndBindGenerator(o);
__LetterCastAndBindGenerator(p);
__LetterCastAndBindGenerator(q);
__LetterCastAndBindGenerator(r);
__LetterCastAndBindGenerator(s);
__LetterCastAndBindGenerator(t);
__LetterCastAndBindGenerator(u);
__LetterCastAndBindGenerator(v);
__LetterCastAndBindGenerator(w);
__LetterCastAndBindGenerator(x);
__LetterCastAndBindGenerator(y);
__LetterCastAndBindGenerator(z);
#pragma endregion

#pragma region UpperCase
__LetterCastAndBindGenerator(A);
__LetterCastAndBindGenerator(B);
__LetterCastAndBindGenerator(C);
__LetterCastAndBindGenerator(D);
__LetterCastAndBindGenerator(E);
__LetterCastAndBindGenerator(F);
__LetterCastAndBindGenerator(G);
__LetterCastAndBindGenerator(H);
__LetterCastAndBindGenerator(I);
__LetterCastAndBindGenerator(J);
__LetterCastAndBindGenerator(K);
__LetterCastAndBindGenerator(L);
__LetterCastAndBindGenerator(M);
__LetterCastAndBindGenerator(N);
__LetterCastAndBindGenerator(O);
__LetterCastAndBindGenerator(P);
__LetterCastAndBindGenerator(Q);
__LetterCastAndBindGenerator(R);
__LetterCastAndBindGenerator(S);
__LetterCastAndBindGenerator(T);
__LetterCastAndBindGenerator(U);
__LetterCastAndBindGenerator(V);
__LetterCastAndBindGenerator(W);
__LetterCastAndBindGenerator(X);
__LetterCastAndBindGenerator(Y);
__LetterCastAndBindGenerator(Z);
#pragma endregion