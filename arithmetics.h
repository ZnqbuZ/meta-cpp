#pragma once

#include "basic_types.h"

#pragma region 皮亚诺运算

DEFN_UNARY_FUN(Inc, x, A(Value(x) + 1));
DEFN_UNARY_FUN(Neg, x, A(-Value(x)));
using Dec = C(Neg, Inc, Neg);

#pragma endregion

#pragma region 四则运算

DEFN_BINARY_FUN(Add, x, y, A(Value(x) + Value(y), Type(x)));
DEFN_BINARY_FUN(Sub, x, y, A(Value(x) - Value(y), Type(x)));
DEFN_BINARY_FUN(Mul, x, y, A(Value(x) * Value(y), Type(x)));
DEFN_BINARY_FUN(Div, x, y, A(Value(x) / Value(y), Type(x)));
DEFN_BINARY_FUN(Mod, x, y, A(Value(x) % Value(y), Type(x)));

#pragma endregion

#pragma region 位运算

// 懒得为逻辑运算单独优化了

DEFN_BINARY_FUN(And, x, y, A(Value(x) & Value(y), Type(x)));
DEFN_BINARY_FUN(Or, x, y, A(Value(x) | Value(y), Type(x)));

// bool 如果用~会有警告
struct Not
{
    FUNC_HEAD_THROW(Not);

    template <is::arg x>
    struct apply_on<x>
    {
        using ret = A(~Value(x), Type(x));
    };

    template <is::bool_type x>
    struct apply_on<x>
    {
        using ret = A(!Value(x), Type(x));
    };
};

DEFN_BINARY_FUN(Xor, x, y, A(Value(x) ^ Value(y), Type(x)));
using NAnd = C(Not, And);
using NOr = C(Not, Or);

#pragma endregion

#define INC(...) Ret(Inc, __VA_ARGS__)
#define NEG(...) Ret(Neg, __VA_ARGS__)
#define DEC(...) Ret(Dec, __VA_ARGS__)

#define ADD(...) Ret(Add, __VA_ARGS__)
#define SUB(...) Ret(Sub, __VA_ARGS__)
#define MUL(...) Ret(Mul, __VA_ARGS__)
#define DIV(...) Ret(Div, __VA_ARGS__)
#define MOD(...) Ret(Mod, __VA_ARGS__)

#define AND(...) Ret(And, __VA_ARGS__)
#define OR(...) Ret(Or, __VA_ARGS__)
#define NOT(...) Ret(Not, __VA_ARGS__)
#define XOR(...) Ret(Xor, __VA_ARGS__)
#define NAND(...) Ret(NAnd, __VA_ARGS__)
#define NOR(...) Ret(NOr, __VA_ARGS__)
