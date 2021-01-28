#pragma once

#include "typesdef.h"
#include "pair.h"
#include "algor.h"
#include <type_traits>

//将变量转换为基础形式(Int、Bool、Char、Null)，以警告消息的形式输出
//仅支持输出字符的ASCII码
//必须绑定行号，因为VS输出的行号不准确，而且会合并内容相同的警告消息
//#define Format(...) __CastAndBind<__VA_ARGS__, __LINE__>::ret

//DeepMap<Format,List>?

#pragma region CastAndBind
template <int Line>
struct __Line_;

struct ch
{
#ifdef _MSC_VER
#define MK_CHAR(x) #@x
#else
#define MK_CHAR(x)\
'\
x\
'
#endif

#define __GEN_CH_TYPE(type,c)\
using type##_##c = Arg(MK_CHAR(c))

#pragma region LowerCase
    __GEN_CH_TYPE(letter, a);
    __GEN_CH_TYPE(letter, b);
    __GEN_CH_TYPE(letter, c);
    __GEN_CH_TYPE(letter, d);
    __GEN_CH_TYPE(letter, e);
    __GEN_CH_TYPE(letter, f);
    __GEN_CH_TYPE(letter, g);
    __GEN_CH_TYPE(letter, h);
    __GEN_CH_TYPE(letter, i);
    __GEN_CH_TYPE(letter, j);
    __GEN_CH_TYPE(letter, k);
    __GEN_CH_TYPE(letter, l);
    __GEN_CH_TYPE(letter, m);
    __GEN_CH_TYPE(letter, n);
    __GEN_CH_TYPE(letter, o);
    __GEN_CH_TYPE(letter, p);
    __GEN_CH_TYPE(letter, q);
    __GEN_CH_TYPE(letter, r);
    __GEN_CH_TYPE(letter, s);
    __GEN_CH_TYPE(letter, t);
    __GEN_CH_TYPE(letter, u);
    __GEN_CH_TYPE(letter, v);
    __GEN_CH_TYPE(letter, w);
    __GEN_CH_TYPE(letter, x);
    __GEN_CH_TYPE(letter, y);
    __GEN_CH_TYPE(letter, z);
#pragma endregion

#pragma region UpperCase
    __GEN_CH_TYPE(letter, A);
    __GEN_CH_TYPE(letter, B);
    __GEN_CH_TYPE(letter, C);
    __GEN_CH_TYPE(letter, D);
    __GEN_CH_TYPE(letter, E);
    __GEN_CH_TYPE(letter, F);
    __GEN_CH_TYPE(letter, G);
    __GEN_CH_TYPE(letter, H);
    __GEN_CH_TYPE(letter, I);
    __GEN_CH_TYPE(letter, J);
    __GEN_CH_TYPE(letter, K);
    __GEN_CH_TYPE(letter, L);
    __GEN_CH_TYPE(letter, M);
    __GEN_CH_TYPE(letter, N);
    __GEN_CH_TYPE(letter, O);
    __GEN_CH_TYPE(letter, P);
    __GEN_CH_TYPE(letter, Q);
    __GEN_CH_TYPE(letter, R);
    __GEN_CH_TYPE(letter, S);
    __GEN_CH_TYPE(letter, T);
    __GEN_CH_TYPE(letter, U);
    __GEN_CH_TYPE(letter, V);
    __GEN_CH_TYPE(letter, W);
    __GEN_CH_TYPE(letter, X);
    __GEN_CH_TYPE(letter, Y);
    __GEN_CH_TYPE(letter, Z);
#pragma endregion

#pragma region Number
    __GEN_CH_TYPE(number, 0);
    __GEN_CH_TYPE(number, 1);
    __GEN_CH_TYPE(number, 2);
    __GEN_CH_TYPE(number, 3);
    __GEN_CH_TYPE(number, 4);
    __GEN_CH_TYPE(number, 5);
    __GEN_CH_TYPE(number, 6);
    __GEN_CH_TYPE(number, 7);
    __GEN_CH_TYPE(number, 8);
    __GEN_CH_TYPE(number, 9);
#pragma endregion
};

struct Format
{
    template<typename args> struct Func;

    template<typename type, type value>
    struct Func<List<Arg(type, value)>>
    {
        using ret = Arg(type, value);
    };

    template<>
    struct Func<List<True>>
    {
        using ret = True;
    };
    template<>
    struct Func<List<False>>
    {
        using ret = False;
    };

#define __CH_FORMATTER(type,c)          \
    template<>                          \
    struct Func<List<ch::type##_##c>>   \
    {                                   \
        using ret = ch::type##_##c;     \
    }

#pragma region LowerCase
    __CH_FORMATTER(letter, a);
    __CH_FORMATTER(letter, b);
    __CH_FORMATTER(letter, c);
    __CH_FORMATTER(letter, d);
    __CH_FORMATTER(letter, e);
    __CH_FORMATTER(letter, f);
    __CH_FORMATTER(letter, g);
    __CH_FORMATTER(letter, h);
    __CH_FORMATTER(letter, i);
    __CH_FORMATTER(letter, j);
    __CH_FORMATTER(letter, k);
    __CH_FORMATTER(letter, l);
    __CH_FORMATTER(letter, m);
    __CH_FORMATTER(letter, n);
    __CH_FORMATTER(letter, o);
    __CH_FORMATTER(letter, p);
    __CH_FORMATTER(letter, q);
    __CH_FORMATTER(letter, r);
    __CH_FORMATTER(letter, s);
    __CH_FORMATTER(letter, t);
    __CH_FORMATTER(letter, u);
    __CH_FORMATTER(letter, v);
    __CH_FORMATTER(letter, w);
    __CH_FORMATTER(letter, x);
    __CH_FORMATTER(letter, y);
    __CH_FORMATTER(letter, z);
#pragma endregion

#pragma region UpperCase
    __CH_FORMATTER(letter, A);
    __CH_FORMATTER(letter, B);
    __CH_FORMATTER(letter, C);
    __CH_FORMATTER(letter, D);
    __CH_FORMATTER(letter, E);
    __CH_FORMATTER(letter, F);
    __CH_FORMATTER(letter, G);
    __CH_FORMATTER(letter, H);
    __CH_FORMATTER(letter, I);
    __CH_FORMATTER(letter, J);
    __CH_FORMATTER(letter, K);
    __CH_FORMATTER(letter, L);
    __CH_FORMATTER(letter, M);
    __CH_FORMATTER(letter, N);
    __CH_FORMATTER(letter, O);
    __CH_FORMATTER(letter, P);
    __CH_FORMATTER(letter, Q);
    __CH_FORMATTER(letter, R);
    __CH_FORMATTER(letter, S);
    __CH_FORMATTER(letter, T);
    __CH_FORMATTER(letter, U);
    __CH_FORMATTER(letter, V);
    __CH_FORMATTER(letter, W);
    __CH_FORMATTER(letter, X);
    __CH_FORMATTER(letter, Y);
    __CH_FORMATTER(letter, Z);
#pragma endregion

#pragma region Number
    __CH_FORMATTER(number, 0);
    __CH_FORMATTER(number, 1);
    __CH_FORMATTER(number, 2);
    __CH_FORMATTER(number, 3);
    __CH_FORMATTER(number, 4);
    __CH_FORMATTER(number, 5);
    __CH_FORMATTER(number, 6);
    __CH_FORMATTER(number, 7);
    __CH_FORMATTER(number, 8);
    __CH_FORMATTER(number, 9);
#pragma endregion
};

#pragma endregion

template <typename T>
struct _display
{
    static constexpr char msg = 1 / (sizeof(T) - sizeof(T));
};
