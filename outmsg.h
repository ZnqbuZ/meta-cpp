#pragma once

#include "typesdef.h"
#include "pair.h"
#include "algor.h"

//将变量转换为基础形式(Int、Bool、Char、Null)，以警告消息的形式输出
//仅支持输出字符的ASCII码
//必须绑定行号，因为VS输出的行号不准确，而且会合并内容相同的警告消息
#define Display(...) __CastAndBind<__VA_ARGS__, __LINE__>::ret

#pragma region CastAndBind
template <int Line>
struct Line__;

template <typename T, int LINE>
struct __CastAndBind
{
    using ret = Cons<Arg(Value(T)), Line__<LINE>>;
};
template <int LINE>
struct __CastAndBind<True, LINE>
{
    using ret = Cons<True, Line__<LINE>>;
};
template <int LINE>
struct __CastAndBind<False, LINE>
{
    using ret = Cons<False, Line__<LINE>>;
};
/*template<bool b, int LINE> struct __CastAndBind<Bool<b>, LINE> { using ret = Cons<Bool<b>, Line__<LINE>>; };*/
template <int LINE>
struct __CastAndBind<Null, LINE>
{
    using ret = Cons<Null, Line__<LINE>>;
};

// #define __LetterTypeGenerator(letter) using letter = Arg(#@letter)
// 已弃用.因为仅MSVC支持#@
struct Letter__
{
#pragma region LowerCase
    using a = Arg('a');
    using b = Arg('b');
    using c = Arg('c');
    using d = Arg('d');
    using e = Arg('e');
    using f = Arg('f');
    using g = Arg('g');
    using h = Arg('h');
    using i = Arg('i');
    using j = Arg('j');
    using k = Arg('k');
    using l = Arg('l');
    using m = Arg('m');
    using n = Arg('n');
    using o = Arg('o');
    using p = Arg('p');
    using q = Arg('q');
    using r = Arg('r');
    using s = Arg('s');
    using t = Arg('t');
    using u = Arg('u');
    using v = Arg('v');
    using w = Arg('w');
    using x = Arg('x');
    using y = Arg('y');
    using z = Arg('z');
#pragma endregion

#pragma region UpperCase
    using A = Arg('A');
    using B = Arg('B');
    using C = Arg('C');
    using D = Arg('D');
    using E = Arg('E');
    using F = Arg('F');
    using G = Arg('G');
    using H = Arg('H');
    using I = Arg('I');
    using J = Arg('J');
    using K = Arg('K');
    using L = Arg('L');
    using M = Arg('M');
    using N = Arg('N');
    using O = Arg('O');
    using P = Arg('P');
    using Q = Arg('Q');
    using R = Arg('R');
    using S = Arg('S');
    using T = Arg('T');
    using U = Arg('U');
    using V = Arg('V');
    using W = Arg('W');
    using X = Arg('X');
    using Y = Arg('Y');
    using Z = Arg('Z');
#pragma endregion
};

#define __LetterCastAndBindGenerator(letter)              \
    template <int LINE>                                   \
    struct __CastAndBind<Letter__::letter, LINE>          \
    {                                                     \
        using ret = Cons<Letter__::letter, Line__<LINE>>; \
    }

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

#pragma endregion

template <typename T>
struct _display
{
    static constexpr char msg = 1/( sizeof(T)-sizeof(T));
};
