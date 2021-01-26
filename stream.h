#pragma once

#include "typesdef.h"

#define STREAM_CAR(...) Car(__VA_ARGS__)
#define STREAM_CDR(...) Cdr(__VA_ARGS__)::ret

//#define MK_STREAM(NAME, NEXT) \
//template<typename T> struct NAME##_starting_from\
//{\
//    using ret= Cons<Arg(Value(T)), NAME##_starting_from<NEXT(T)>>;\
//}

//#define GET_STREAM(NAME, HEAD) Ret(NAME##_starting_from, HEAD)

template<
    template<typename T> typename NEXT>
struct MK_STREAM
{
    template<typename HEAD> struct starting_from
    {
        using ret = Cons<Arg(Value(HEAD)), starting_from<Ret(NEXT, HEAD)>>;
    };
};

template<
    template<typename T> typename F>
struct STREAM_MAP
{
    template<typename stream> struct on
    {
        using ret = Cons<
            Arg(Value(Ret(F, STREAM_CAR(typename stream)))),
            on<STREAM_CDR(typename stream)>>;
    };
};

using integers = MK_STREAM<_Inc>::starting_from<Int<1>>::ret;

template<typename T>
struct twice
{
    using ret = Mul(T, Int<2>);
};

using evens = STREAM_MAP<twice>::on<integers>::ret;

template<typename T>
using twice_dec = composition<_Dec, twice, T>;

using odds = STREAM_MAP<twice_dec>::on<integers>::ret;