#pragma once

#include "typesdef.h"
#include "pair.h"
#include "algor.h"
#include <type_traits>

struct Format
{
    template<typename arg_list> struct Func;

    template<typename T>
    struct Func<List<T>>
    {
        using ret = typename T::formatted;
    };
};

template <int Line> struct LINE;
template<typename LINE, typename T> struct Output;

//将变量转换为基础形式(Int、Bool、Char)，以警告消息的形式输出
//必须绑定行号，因为VS输出的行号不准确，而且会合并内容相同的警告消息
//输出格式化后的列表
#define Formatted(...)              \
        Ret(DeepMap::template Func, \
            List<                   \
                Format,             \
                List<__VA_ARGS__>>)

#define Display(...) Output<LINE<__LINE__>,__VA_ARGS__>
