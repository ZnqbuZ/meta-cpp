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
        using ret = Cons<Arg(Value(HEAD)), starting_from<NEXT<HEAD>>>;//Ret(NEXT, HEAD)
    };
};

template<
    template<typename T> typename F>
struct STREAM_MAP
{
    template<typename stream> struct on
    {
        using curr = STREAM_CAR(typename stream);
        using res = STREAM_CDR(typename stream);
        using ret = Cons<
            Arg(Value(F<curr>)),//Ret(F,curr)
            on<res>>;
    };
};

template<
    template<typename T> typename F>
struct STREAM_FILTER
{
    template<typename stream> struct on
    {
        using curr = STREAM_CAR(typename stream);
        using res = STREAM_CDR(typename stream);

        //template<
        //    template<typename Context> typename F,
        //    typename U>
        //    struct delayed
        //{
        //    using ret = typename F<U>::ret;
        //};

        //template<
        //    typename U,
        //    template<typename Context> typename F,
        //    typename V>
        //    struct __check;
        //template<
        //    template<typename Context> typename F,
        //    typename V>
        //    struct __check<True, F, V>
        //{
        //    using ret = Cons<curr, delayed<F, V>>;
        //};
        //template<
        //    template<typename Context> typename F,
        //    typename V>
        //    struct __check<False, F, V>
        //{
        //    using ret = typename delayed<F, V>::ret;
        //};

        template<typename ARGS>
        struct __DO_IF_FUN
        {
            template<
                typename cond,
                template<typename _1> typename THEN,
                typename THEN_ARG,
                template<typename _2> typename ELSE,
                typename ELSE_ARG>
                struct __DO_IF;
            template<
                template<typename _1> typename THEN,
                typename THEN_ARG,
                template<typename _2> typename ELSE,
                typename ELSE_ARG>
                struct __DO_IF<True, THEN, THEN_ARG, ELSE, ELSE_ARG>
            {
                using ret = typename THEN<THEN_ARG>::ret;
            };
            template<
                template<typename _1> typename THEN,
                typename THEN_ARG,
                template<typename _2> typename ELSE,
                typename ELSE_ARG>
                struct __DO_IF<False, THEN, THEN_ARG, ELSE, ELSE_ARG>
            {
                using ret = typename ELSE<ELSE_ARG>::ret;
            };

            using ret =
                typename __DO_IF<
                typename ARGS::_1,
                typename ARGS::_2,
                typename ARGS::_3,
                typename ARGS::_4,
                typename ARGS::_5>::ret;
        };

        template<
            typename cond,
            template<typename __THEN_ARGS> typename THEN,
            typename THEN_ARGS,
            template<typename __ELSE_ARGS> typename ELSE,
            typename ELSE_ARGS>
            struct __DO_IF_PACK_ARGS
        {
            using _1 = cond;
            template<typename __2_ARGS> using _2 = THEN<__2_ARGS>;
            using _3 = THEN_ARGS;
            template<typename __4_ARGS> using _4 = ELSE<__4_ARGS>;
            using _5 = ELSE_ARGS;
        };

        using ret =
            //    typename _Do<Cons<curr, on<res>>>::template _If<Ret(F, curr)>::template _Else<delayed>;
            //    typename _If<Ret(F, curr), Cons<curr, on<res>>>::template ret<delayed<on, res>::ret>;
            //    typename __check<Ret(F, curr), on, res>::ret;
            typename __DO_IF_FUN<__DO_IF_PACK_ARGS<
            Ret(F, curr),
            MK_CONS_FUN, MK_CONS_PACK_ARGS<curr, on<res>>,
            on, res>>::ret;
    };
};

using inc_stream = MK_STREAM<_Inc::Func>;//_Inc
using integers = inc_stream::starting_from<Int<1>>::ret;

//template<typename T>
//struct twice
//{
//    using ret = Mul(T, Int<2>);
//};

struct twice
{
    template<typename T>
    using Func = Mul(T, Int<2>);
};

using evens = STREAM_MAP<twice::Func>::on<integers>::ret;

template<typename T>
using twice_dec = composition<_Dec::Func, twice::Func, T>;

using odds = STREAM_MAP<twice_dec>::on<integers>::ret;