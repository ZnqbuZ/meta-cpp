#pragma once

#include "basic_types.h"

#pragma region 皮亚诺运算

DEFN_UNARY_FUN(Inc, x, Value(x) + 1);
DEFN_UNARY_FUN(Neg, x, -Value(x));
using Dec = C(Neg, Inc, Neg);

#pragma endregion

#pragma region 四则运算

DEFN_BINARY_FUN(Add, x, y, Value(x) + Value(y));
DEFN_BINARY_FUN(Sub, x, y, Value(x) - Value(y));
DEFN_BINARY_FUN(Mul, x, y, Value(x)* Value(y));
DEFN_BINARY_FUN(Div, x, y, Value(x) / Value(y));
DEFN_BINARY_FUN(Mod, x, y, Value(x) % Value(y));

#pragma endregion

#pragma region 位运算

// 懒得为逻辑运算单独优化了

DEFN_BINARY_FUN(And, x, y, Value(x)& Value(y));
DEFN_BINARY_FUN(Or, x, y, Value(x) | Value(y));
// bool 如果用~会有警告
DEFN_UNARY_FUN(Not, x, ~Value(x));
template<is::bool_type var>
struct Not::apply_on<var>
{
    using ret = A(!Value(var), Type(var));
};
DEFN_BINARY_FUN(Xor, x, y, Value(x) ^ Value(y));
using NAnd = C(Not, And);
using NOr = C(Not, Or);

#pragma endregion

#define INC(...)    Ret(Inc, __VA_ARGS__)
#define NEG(...)    Ret(Neg, __VA_ARGS__)
#define DEC(...)    Ret(Dec, __VA_ARGS__)

#define ADD(...)    Ret(Add, __VA_ARGS__)
#define SUB(...)    Ret(Sub, __VA_ARGS__)
#define MUL(...)    Ret(Mul, __VA_ARGS__)
#define DIV(...)    Ret(Div, __VA_ARGS__)
#define MOD(...)    Ret(Mod, __VA_ARGS__)

#define AND(...)    Ret(And, __VA_ARGS__)
#define OR(...)     Ret(Or, __VA_ARGS__)
#define NOT(...)    Ret(Not, __VA_ARGS__)
#define XOR(...)    Ret(Xor, __VA_ARGS__)
#define NAND(...)   Ret(NAnd, __VA_ARGS__)
#define NOR(...)    Ret(NOr, __VA_ARGS__)
