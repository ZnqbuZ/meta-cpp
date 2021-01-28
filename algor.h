#pragma once
#include "typesdef.h"
#include "arith.h"
#include "pair.h"

// 复合函数
struct compose
{
    template<typename arg_list> struct Func;

    template<typename T, typename V>
    struct Func<List<T, V>>
    {
        struct ret
        {
            template<typename arg_list> struct Func
            {
                using ret = Ret(T::template Func, List<Ret(V::template Func, arg_list)>);
            };
        };
    };
};

#define IsEqual(...) Ret(_isEqual::Func, List<__VA_ARGS__>)
struct _isEqual
{
    template<typename ARGS> struct Func;

    template<typename T, typename V>
    struct Func<List<T, V>> { using ret = False; };

    template<typename T>
    struct Func<List<T, T>> { using ret = True; };
};

DEFN_BINARY_FUN(isValueEqual, x, y, bool, (Value(x) == Value(y)));
DEFN_BINARY_FUN(isGreater, x, y, bool, (Value(x) > Value(y)));
DEFN_BINARY_FUN(isLess, x, y, bool, (Value(x) < Value(y)));
#define IsValueEqual(...)   Ret(_isValueEqual::Func, List<__VA_ARGS__>)
#define IsGreater(...)      Ret(_isGreater::Func, List<__VA_ARGS__>)
#define IsLess(...)         Ret(_isLess::Func, List<__VA_ARGS__>)

//#define IsGreater(...) Ret(_isGreater,__VA_ARGS__)
//template<typename T, typename V> struct _isGreater { using ret = ARG(bool, (Value(T) > Value(V))); };
//
//#define IsLess(...) Ret(_isLess,__VA_ARGS__)
//template<typename T, typename V> struct _isLess { using ret = ARG(bool, (Value(T) < Value(V))); };

#define IsGreaterEqual(...) Not(IsLess(__VA_ARGS__))
#define IsLessEqual(...) Not(IsGreater(__VA_ARGS__))

//template<typename T> constexpr add_rvalue_reference_t<T> typedval();

//例：If(cond, struct1{fun}, struct2{fun})::fun<context>
//TODO：对例所示的过程进行更高阶的抽象

//TODO：使if延迟计算THEN和ELSE
// 或许可考虑If(cond,CONS<THEN,ELSE>)
// 不可行，因为似乎THEN和ELSE只要作为参数就会被计算
// 
//如果需要在If中输出，必须在外层加Format
//If(cond, THEN, ELSE)
//#define If(...) Ret(_If,__VA_ARGS__)


//#define If(cond, THEN, ELSE) typename _Do<THEN>::template _If<cond>::template _Else<ELSE>;
//template<typename THEN> struct _Do
//{
//    template<typename cond> struct _If;
//    template<> struct _If<True> { template<typename T> using _Else = THEN; };
//    template<> struct _If<False> { template<typename T> using _Else = T; };
//};

//#define If(cond, THEN, ELSE) typename _If<cond,THEN>::template ret<ELSE>
//template <typename cond, typename THEN> struct _If;
//template<typename THEN> struct _If<True, THEN>
//{
//    template<typename T> using ret = THEN;
//};
//template<typename THEN> struct _If<False, THEN>
//{
//    template<typename T> using ret = T;
//};

#define If(...) Ret(_if::template Func, List<__VA_ARGS__>)
struct _if
{
    template<typename ARGS> struct Func;

    template<typename THEN, typename ELSE>
    struct Func<List<True, THEN, ELSE>>
    {
        using ret = THEN;
    };

    template<typename THEN, typename ELSE>
    struct Func<List<False, THEN, ELSE>>
    {
        using ret = ELSE;
    };
};

//Ifs和Switch仅可用于g++，我也不知道为什么
//因为上面的If宏的ret之前必须加template，都怪SB的MSVC

//若没有传入ELSE，则在所有条件均不成立的情况下返回Null
//Ifs(THEN1,cond1,THEN2,cond2,...,ELSE)
#define Ifs(...) Ret(_Ifs,__VA_ARGS__)
template<typename THEN, typename cond = True, typename...Tcs> struct _Ifs
{
    using ret = If(cond, THEN, Ifs(Tcs...));
};

template<typename ELSE> struct _Ifs<ELSE> { using ret = ELSE; };

//若没有传入Default，则在所有情况均不匹配时返回Null
//Switch(arg, THEN1, case1, THEN2, case2, ..., Default)
#define Switch(arg,...) Ret(_Switch<arg>::__Switch,__VA_ARGS__)
template<typename arg> struct _Switch
{
    template<typename THEN = Null, typename __case = arg, typename...Tcs>
    struct __Switch
    {
        using ret = If(IsEqual(arg, __case), THEN, Ret(__Switch, Tcs...));
    };
    template<typename Default> struct __Switch<Default> { using ret = Default; };
};

//这里定义的For函数是一个迭代器，它的运算结果为Func<Func<...Func<Context>...>>
//For(LoopFunc<Context>, Context, StopBy<Index>, doToIndex<Index> = Inc, Index = Int<0>)
#define For(...) Ret(_For,__VA_ARGS__)
template<
    template<typename Context> typename LoopFunc,
    typename Context,
    template<typename Index> typename StopBy,
    template<typename Index> typename doToIndex = _Inc::Func,//_Inc
    typename Index = Int<0>> struct _For
    // 注意声明形参的顺序，如果模板模板参数的参数与其它参数重名则必须
    // 首先声明模板模板参数. 如本函数中的StopBy和doToIndex必须在
    // Index之前，否则有可能出现错误.
{
    //错误的写法
    // 
    //template<typename Index, typename Context> struct __MainLoop
    //{
    //    using __FuncRet = Ret(LoopFunc, Context);
    //    using ret =
    //        If(Ret(StopBy, Index),
    //            __FuncRet,
    //            Ret(__MainLoop, Ret(doToIndex, Index), __FuncRet));
    //};

    template<typename shallStop, typename __Index, typename __Context> struct __MainLoop;
    template<typename __Index, typename __Context> struct __MainLoop<True, __Index, __Context>
    {
        using ret = __Context;
    };
    template<typename __Index, typename __Context> struct __MainLoop<False, __Index, __Context>
    {
        using __NextIndex = Ret(doToIndex, __Index);
        using __FuncRet = Ret(LoopFunc, __Context);

        using ret =
            Ret(__MainLoop,
                Ret(StopBy, __NextIndex),
                __NextIndex,
                __FuncRet);
    };

    using ret =
        Ret(__MainLoop,
            Ret(StopBy, Index),
            Index,
            Context);

    //以下写法也是正确的(结果正确)，但会产生编译错误
    // 见init.cpp
    // 
    //struct __LoopEnd
    //{
    //    template<typename Index, typename Context> struct Func
    //    {
    //        using ret = Context;
    //    };
    //};

    //struct __MainLoop
    //{
    //    template<typename Index, typename Context> struct Func
    //    {
    //        using __NextIndex = Ret(doToIndex, Index);
    //        using __FuncRet = Ret(LoopFunc, Context);

    //        using ret =
    //            RawRet(
    //                If(Ret(StopBy, __NextIndex),
    //                    __LoopEnd,
    //                    __MainLoop)::Func,
    //                __NextIndex, __FuncRet);
    //    };
    //};

    //using ret =
    //    RawRet(
    //        If(Ret(StopBy, Index),
    //            __LoopEnd,
    //            __MainLoop)::Func,
    //        Index, Context);
};