// Scheme_In_Templates.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <stdio.h>
#include "typesdef.h"
#include "outmsg.h"
#include "arith.h"
#include "pair.h"
#include "algor.h"

#pragma region 阶乘
template<typename T> struct factorial;
template<int N> struct factorial<Int<N>>
{
    using ret = Mul(Int<N>, Ret(factorial, Sub(Int<N>, Int<1>)));
};
template<> struct factorial<Int<0>>
{
    using ret = Int<1>;
};
#pragma endregion

#pragma region 模板模板参数
template<
    template<typename...Types> typename myTemp>
struct TestTemp
{
    template<typename...Types> using ret = myTemp<Types...>;
};

template<
    template<
    template<typename...Types> typename myTempTemp> typename myTemp>
struct TestTemp2
{
    template<template<typename...Types> typename myTempTemp> using ret = myTemp<myTempTemp>;
};
#pragma endregion

struct packStructA
{
    template<typename T> struct Func
    {
        using ret = Add(T, Int<2>);
    };
};
struct packStructB
{
    template<typename T> struct Func
    {
        using ret =
            RawRet(If(False,
                packStructB,
                packStructA)::Func,
                Inc(T));

        //此处的递归会产生语法错误
        // TODO：错误分析
        // 
        /*RawRet(If(IsLess(T, Int<5>),
            packStructB,
            packStructA)::Func,
            Inc(T));*/
    };
};

#pragma region 循环测试
template<typename Index> struct doToIndex
{
    using ret = Inc(Index);
};

template<typename Index> struct StopBy
{
    using ret = IsGreaterEqual(Index, Int<10>);
};

template<typename Context> struct LoopFunc
{
    using ret = Mul(Context, Int<2>);
};
#pragma endregion


template<typename...Types> constexpr int init(Types...args)
{
#pragma region 算术运算测试
    //Display(
    //    Add(Arg('e'), Arg(int, 5)));

    //Display(
    //    Inc(Arg('a')));
#pragma endregion

#pragma region 选择结构测试
    //Display(
    //    If(IsEqual(Arg(1), Arg(0)),
    //        True,
    //        False));

    //Display(
    //    Ifs(Arg(1), IsEqual(Arg(1), Arg(0)),
    //        Arg(2), IsEqual(Arg(1), Arg(6))));

    //Ifs(
    //    Arg(1), IsEqual(Arg(1), Arg(0)),
    //    Arg(2), IsEqual(Arg(1), Arg(6)),
    //    Display(Arg(3)));

    //Display(
    //    Switch(Arg(1),
    //        Arg(2), Arg(2),
    //        Arg(3), Arg(3),
    //        Arg(1)));
#pragma endregion

#pragma region 序对测试
    //using mycons = Cons<Int<1>>;
    //Display(Car(mycons));
    //Display(Cdr(mycons));
#pragma endregion

#pragma region 逻辑运算测试
    //Display(Arg(true));

    //Display(
    //    IsGreater(Arg(int, 5), Arg('e')));

    //Display(
    //    And(Arg(125), Arg(234)));

    //Display(
    //    Or(Arg(125), Arg(234)));

    //Display(
    //    Not(Arg(125)));

    //Display(
    //    Not(Arg(true)));

    //Display(
    //    Xor(Arg(125), Arg(234)));
#pragma endregion

    Display(
        For(LoopFunc, Int<3>, StopBy));

    Display(
        If(Ret(StopBy, Int<0>),
            Null,
            Int<1>));

    //Display(
    //    Ret(_If<False, packStructA, packStructB>::ret::Func, Int<1>));
    Display(
        RawRet(
            If(False,
                packStructA,
                packStructB)::Func,
            Int<1>));

    return 0;
}

int main()
{
    static_assert(init() != 0, "init end.");
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
