#pragma once
#include "typesdef.h"
#include "arith.h"

#define IsEqual(...) Ret(_isEqual,__VA_ARGS__)
template<typename T, typename V> struct _isEqual { using ret = False; };
template<typename T> struct _isEqual<T, T> { using ret = True; };

#define IsGreater(...) Ret(_isGreater,__VA_ARGS__)
template<typename T, typename V> struct _isGreater { using ret = Arg(bool, (Value(T) > Value(V))); };

//例：If(cond, struct1{fun}, struct2{fun})::fun<context>
//TODO：对例所示的过程进行更高阶的抽象

//如果需要在If中输出，必须在外层加Format
//If(cond, THEN, ELSE)
#define If(...) Ret(_If,__VA_ARGS__)
template<typename cond, typename THEN, typename ELSE = Null> struct _If;
template<typename THEN, typename ELSE> struct _If<True, THEN, ELSE> { using ret = THEN; };
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

//TODO:测试循环函数
//For(LoopFunc<Context>, Context, EndCond<Index>, Index = Int<0>, doToIndex<Index> = Inc)
#define For(...) Ret(_For,__VA_ARGS__)
template<
    template<typename Context> typename LoopFunc,
    typename Context,
    template<typename Index> typename StopBy,
    typename Index = Int<0>,
    template<typename Index> typename doToIndex = _Inc> struct _For
{
    template<typename Index> struct __MainLoop
    {
        //除最后一次循环外抛弃所有循环体函数的返回值
        using __FuncRet = Ret(LoopFunc, Context);
        using ret = If(Ret(StopBy, Index), __FuncRet, Ret(__MainLoop, Ret(doToIndex, Index)));
    };
    using ret = If(Ret(StopBy, Index), Null, Ret(__MainLoop, Index));
};