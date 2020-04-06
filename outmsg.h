#pragma once

#include "typesdef.h"
#include "pair.h"
#include "algor.h"

//将变量转换为基础形式(Int、Bool、Char、Null)，以警告消息的形式输出
//必须绑定行号，因为VS输出的行号不准确，而且会合并内容相同的警告消息
#define Display(...) __CastAndBind<__VA_ARGS__,__LINE__>::ret
template<int Line> struct Line__;

template<typename T, int LINE> struct __CastAndBind { using ret = Cons<Arg(Value(T)), Line__<LINE>>; };
template<int LINE> struct __CastAndBind<True, LINE> { using ret = Cons<True, Line__<LINE>>; };
template<int LINE> struct __CastAndBind<False, LINE> { using ret = Cons<False, Line__<LINE>>; };
/*template<bool b, int LINE> struct __CastAndBind<Bool<b>, LINE> { using ret = Cons<Bool<b>, Line__<LINE>>; };*/
template<int LINE> struct __CastAndBind<Null, LINE> { using ret = Cons<Null, Line__<LINE>>; };