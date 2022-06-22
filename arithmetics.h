#pragma once

#include "types.h"

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

#pragma region 位运算和逻辑运算

#define DEFN_UNARY_LOGIC_FUN(name, var, bit_op, logic_op) \
    struct name                                           \
    {                                                     \
        FUNC_HEAD_THROW(name);                            \
        template <is::arg var>                            \
        struct apply_on<var>                              \
        {                                                 \
            using ret = A(bit_op Value(var), Type(var));  \
        };                                                \
        template <is::bool_type var>                      \
        struct apply_on<var>                              \
        {                                                 \
            using ret = A(logic_op Value(var), Type(var));\
        };                                                \
    }

#define DEFN_BINARY_LOGIC_FUN(name, var1, var2, bit_op, logic_op)                  \
    struct name                                                                    \
    {                                                                              \
        FUNC_HEAD_THROW(name);                                                     \
        WAIT_FOR_n_DELAYED_ARGS(name, 2);                                          \
        template <                                                                 \
            is::arg var1,                                                          \
            is::arg var2>                                                          \
        struct apply_on<L(var1, var2)>                                             \
        {                                                                          \
            using ret = A(Value(var1) bit_op Value(var2), Type(var1));             \
        };                                                                         \
        template <                                                                 \
            is::bool_type var1,                                                    \
            is::arg var2>                                                          \
        struct apply_on<L(var1, var2)>                                             \
        {                                                                          \
            using ret = A(Value(var1) logic_op RetV(cast, var2, bool), Type(var1));\
        };                                                                         \
    }

DEFN_BINARY_LOGIC_FUN(And, x, y, &, &&);
DEFN_BINARY_LOGIC_FUN(Or, x, y, |, ||);

DEFN_UNARY_LOGIC_FUN(Not, x, ~, !);

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
