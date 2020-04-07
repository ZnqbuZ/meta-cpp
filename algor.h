#pragma once
#include "typesdef.h"
#include "arith.h"

#define IsEqual(...) Ret(_isEqual,__VA_ARGS__)
template<typename T, typename V> struct _isEqual { using ret = False; };
template<typename T> struct _isEqual<T, T> { using ret = True; };

#define IsGreater(...) Ret(_isGreater,__VA_ARGS__)
template<typename T, typename V> struct _isGreater { using ret = Arg(bool, (Value(T) > Value(V))); };

#define IsLess(...) Ret(_isLess,__VA_ARGS__)
template<typename T, typename V> struct _isLess { using ret = Arg(bool, (Value(T) < Value(V))); };

#define IsGreaterEqual(...) Not(IsLess(__VA_ARGS__))
#define IsLessEqual(...) Not(IsGreater(__VA_ARGS__))

//例：If(cond, struct1{fun}, struct2{fun})::fun<context>
//TODO：对例所示的过程进行更高阶的抽象

//TODO：修改if使得其可延迟计算THEN和ELSE
// 可尝试If(cond,CONS<THEN,ELSE>)
// 
//如果需要在If中输出，必须在外层加Format
//If(cond, THEN, ELSE)
#define If(...) Ret(_If,__VA_ARGS__)
template<typename cond, typename THEN, typename ELSE = Null> struct _If;
template<typename THEN, typename ELSE> struct _If<True, THEN, ELSE>
{
    using ret = THEN;
};
template<typename THEN, typename ELSE> struct _If<False, THEN, ELSE> { using ret = ELSE; };

//若没有传入ELSE，则在所有条件均不成立的情况下返回Null
//Ifs(THEN1,cond1,THEN2,cond2,...,ELSE)
#define Ifs(...) Ret(_Ifs,__VA_ARGS__)
template<typename THEN = Null, typename cond = True, typename...Tcs> struct _Ifs
{
    using ret = If(cond, THEN, Ifs(Tcs...));
};

template<typename ELSE> struct _Ifs<ELSE> { using ret = ELSE; };

//若没有传入Default，则在所有情况均不匹配时返回Null
//Switch(arg,THEN1,case1,THEN2,case2,...,Default)
#define Switch(arg,...) Ret(_Switch<arg>::__Switch,__VA_ARGS__)
template<typename arg> struct _Switch
{
    template<typename THEN = Null, typename __case = arg, typename...Tcs> struct __Switch
    {
        using ret = If(IsEqual(arg, __case), THEN, Ret(__Switch, Tcs...));
    };
    template<typename Default> struct __Switch<Default> { using ret = Default; };
};

//这里定义的For函数是一个迭代器，它的运算结果为Func<Func<...Func<Context>...>>
//For(LoopFunc<Context>, Context, StopBy<Index>, Index = Int<0>, doToIndex<Index> = Inc)
#define For(...) Ret(_For,__VA_ARGS__)
template<
    template<typename Context> typename LoopFunc,
    typename Context,
    template<typename Index> typename StopBy,
    template<typename Index> typename doToIndex = _Inc,
    typename Index = Int<0>> struct _For
    //注意形参的声明顺序：
    //如果模板模板参数的形参(如StopBy和doToIndex的参数Index)与其它形参重名，则必须将模板模板参数放在前面
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