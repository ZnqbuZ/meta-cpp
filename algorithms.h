#pragma once

#include "basic_types.h"
#include "arithmetics.h"

using is_greater_equal = C(Not, is_less);
using is_less_equal = C(Not, is_greater);

struct swap
{
    FUNC_HEAD_THROW(swap);

    template <typename T, typename V>
    struct apply_on<L(T, V)>
    {
        using ret = L(Id(V), Id(T));
    };
};

struct do_if
{
    FUNC_HEAD_THROW(do_if);

    template <
        is::delayed cond,
        is::function THEN, typename THEN_arg_list,
        is::function ELSE, typename ELSE_arg_list>
    struct apply_on<L(cond, THEN, THEN_arg_list, ELSE, ELSE_arg_list)>
    {
        using ret = D(do_if, cond, THEN, THEN_arg_list, ELSE, ELSE_arg_list);
    };

    template <
        is::bool_type cond,
        is::function THEN, typename THEN_arg_list,
        is::function ELSE, typename ELSE_arg_list>
    requires(Value(cond)) struct apply_on<L(cond, THEN, THEN_arg_list, ELSE, ELSE_arg_list)>
    {
        using ret = Ret(THEN, THEN_arg_list);
    };

    template <
        is::bool_type cond,
        is::function THEN, typename THEN_arg_list,
        is::function ELSE, typename ELSE_arg_list>
    requires(!Value(cond)) struct apply_on<L(cond, THEN, THEN_arg_list, ELSE, ELSE_arg_list)>
    {
        using ret = Ret(ELSE, ELSE_arg_list);
    };
};

struct push_front
{
    FUNC_HEAD_THROW(push_front);

    template <typename T, typename V>
    struct apply_on<L(T, V)>
    {
        using ret = L(Id(T), Id(V));
    };

    template <typename T, is::delayed V>
    struct apply_on<L(T, V)>
    {
        using ret = D(push_front, T, V);
    };

    template <typename T, is::list V>
    struct apply_on<L(T, V)>
    {
        using ret = Ret(typename V::push_front, T);
    };
};

struct push_back
{
    FUNC_HEAD_THROW(push_back);

    template <typename T, typename V>
    struct apply_on<L(T, V)>
    {
        using ret = L(Id(V), Id(T));
    };

    template <typename T, is::delayed V>
    struct apply_on<L(T, V)>
    {
        using ret = D(push_back, T, V);
    };

    template <typename T, is::list V>
    struct apply_on<L(T, V)>
    {
        using ret = Ret(typename V::push_back, T);
    };
};

struct join
{
    FUNC_HEAD_THROW(join);

    template <typename T, typename V>
    struct apply_on<L(T, V)>
    {
        using ret = L(Id(T), Id(V));
    };

    WAIT_FOR_n_DELAYED_ARGS(join, 2);

    template <is::not_delayed T, is::list l>
    struct apply_on<L(T, l)>
    {
        using ret = Ret(push_front, T, l);
    };

    template <is::list l, is::not_delayed V>
    struct apply_on<L(l, V)>
    {
        using ret = Ret(push_back, V, l);
    };

    template <typename... Ts, typename... Vs>
    struct apply_on<L(L(Ts...), L(Vs...))>
    {
        using ret = L(Ts..., Vs...);
    };
};

struct peek_front
{
    FUNC_HEAD_ID;
    WAIT_FOR_DELAYED_ARGS(peek_front);

    template <is::list V>
    struct apply_on<V>
    {
        using ret = Ret(typename V::peek_front, void);
    };
};

struct peek_back
{
    FUNC_HEAD_ID;
    WAIT_FOR_DELAYED_ARGS(peek_back);

    template <is::list V>
    struct apply_on<V>
    {
        using ret = Ret(typename V::peek_back, void);
    };
};

struct pop_front
{
    FUNC_HEAD_THROW(pop_front);

    template <is::list V>
    struct apply_on<V>
    {
        using ret = Ret(typename V::pop_front, void);
    };
};

struct pop_back
{
    FUNC_HEAD_THROW(pop_back);

    template <is::list V>
    struct apply_on<V>
    {
        using ret = Ret(typename V::pop_back, void);
    };
};

struct insert_l
{
    FUNC_HEAD_THROW(insert_l);

    struct ERROR_INDEX_OUT_OF_RANGE;
    template <typename T, is::arg Index, is::list l>
    struct apply_on<L(T, l, Index)>
    {
        using ret = ERROR_INDEX_OUT_OF_RANGE;
    };

    template <typename T, is::arg Index, typename T1, typename... Ts>
    requires(
        RetV(is_greater, Index, A(0)) &&
        RetV(is_less, Index, A(1 + sizeof...(Ts)))) struct apply_on<L(T, L(T1, Ts...), Index)>
    {
        using ret = Ret(push_front, T1, Ret(insert_l, T, Id(Ts...), DEC(Index)));
    };

    template <typename T, is::list l>
    struct apply_on<L(T, l, A(0))>
    {
        using ret = Ret(push_front, T, l);
    };

    template <typename T, is::list l>
    struct apply_on<L(T, l, Len(l))>
    {
        using ret = Ret(push_back, T, l);
    };

    template <typename T, typename T1, typename T2>
    struct apply_on<L(T, L(T1, T2), A(1))>
    {
        using ret = L(Id(T1), Id(T), Id(T2));
    };
};

struct remove_l
{
    FUNC_HEAD_THROW(remove_l);

    struct ERROR_INDEX_OUT_OF_RANGE;
    template <is::arg Index, is::list l>
    struct apply_on<L(l, Index)>
    {
        using ret = ERROR_INDEX_OUT_OF_RANGE;
    };

    template <is::arg Index, typename T1, typename... Ts>
    requires(
        RetV(is_greater, Index, A(0)) &&
        RetV(is_less, Index, A(sizeof...(Ts)))) struct apply_on<L(L(T1, Ts...), Index)>
    {
        using ret = Ret(push_front, T1, Ret(remove_l, Id(Ts...), DEC(Index)));
    };

    template <is::list l>
    struct apply_on<L(l, A(0))>
    {
        using ret = Ret(pop_front, l);
    };

    template <is::list l>
    struct apply_on<L(l, DEC(Len(l)))>
    {
        using ret = Ret(pop_back, l);
    };

    template <typename T1, typename T, typename T2>
    struct apply_on<L(L(T1, T, T2), A(1))>
    {
        using ret = L(Id(T1), Id(T2));
    };
};

struct replace_l
{
    FUNC_HEAD_THROW(replace_l);

    struct ERROR_INDEX_OUT_OF_RANGE;
    template <typename T, is::arg Index, is::list l>
    struct apply_on<L(T, l, Index)>
    {
        using ret = ERROR_INDEX_OUT_OF_RANGE;
    };

    template <typename T, is::arg Index, is::list l>
    requires(
        RetV(is_greater_equal, Index, A(0)) &&
        RetV(is_less, Index, Len(l))) struct apply_on<L(T, l, Index)>
    {
        using ret = Ret(remove_l, Ret(insert_l, T, l, Index), INC(Index));
    };
};

struct bind
{
private:
    template <is::list l>
    struct __1_arg;

public:
    struct take_as_1_arg
    {
        FUNC_HEAD_THROW(take_as_1_arg);

        template <is::list l>
        struct apply_on<l>
        {
            using ret = __1_arg<l>;
        };
    };

    FUNC_HEAD_THROW(bind);

    template <typename T, is::arg N>
    struct mask_list
    {
        template <typename V>
        struct apply_on
        {
            using ret = L(T, V);
        };

        template <typename V>
        requires(RetV(is_greater, N, A(0))) struct apply_on<V>
        {
            using ret = L(V, T);
        };

        template <is::list V>
        struct apply_on<__1_arg<V>>
        {
            using ret = L(T, V);
        };

        template <is::list V>
        requires(RetV(is_greater, N, A(0))) struct apply_on<__1_arg<V>>
        {
            using ret = L(V, T);
        };

        template <is::list arg_list>
        struct apply_on<arg_list>
        {
            using ret = Ret(insert_l, T, arg_list, N);
        };
    };

    template <is::function f, typename T, is::arg N>
    struct apply_on<L(f, T, N)>
    {
        using ret = C(f, mask_list<T, N>);
    };
};

struct flatten
{
    FUNC_HEAD_ID;
    WAIT_FOR_DELAYED_ARGS(flatten);

    template <typename T, typename... Ts>
    struct apply_on<L(T, Ts...)>
    {
        using ret = Ret(join, Ret(flatten, T), Ret(flatten, Id(Ts...)));
    };
};

struct map
{
    FUNC_HEAD_THROW(map);
    //WAIT_FOR_n_DELAYED_ARGS(map, 2);

    template <is::function f, typename T>
    struct apply_on<L(f, T)>
    {
        using ret = Ret(f, T);
    };

    template <is::function f, typename... Ts>
    struct apply_on<L(f, L(Ts...))>
    {
        using ret = L(Ret(f, Ts)...);
    };
};

struct deep_map
{
    FUNC_HEAD_THROW(deep_map);
    //WAIT_FOR_n_DELAYED_ARGS(deep_map, 2);

    template <is::function f, typename T>
    struct apply_on<L(f, T)>
    {
    private:
        struct on
        {
            template <typename V>
            struct apply_on
            {
                using ret = Ret(f, V);
            };

            //WAIT_FOR_DELAYED_ARGS(on);

            template <typename... Vs>
            struct apply_on<L(Vs...)>
            {
                using ret = L(Ret(on, Vs)...);
            };
        };

    public:
        using ret = Ret(on, T);
    };
};

struct filter
{
    struct Null;

    friend struct deep_filter;
    friend struct filter_s;

private:
    struct __check
    {
        FUNC_HEAD_THROW(__check);

        template <is::function f, typename T>
        struct apply_on<L(f, T)>
        {
            using ret = Select(Ret(cast, Ret(f, T), bool), T, Null);
        };
    };

    struct __trunc
    {
        FUNC_HEAD_THROW(__trunc);

        template <is::list l>
        requires(RetV(is_greater, Len(l), A(2))) struct apply_on<l>
        {
            using ret = Ret(C(pop_back, pop_back), l);
        };

        template <is::list l>
        requires(RetV(is_value_equal, Len(l), A(2))) struct apply_on<l>
        {
            using ret = Null;
        };
    };

    struct __filter
    {
    private:
        struct __shrink
        {
            friend __filter;

        private:
            struct STOP;

        public:
            FUNC_HEAD_THROW(__shrink);

            template <is::list l>
            struct apply_on<l>
            {
                using curr = Ret(peek_front, l);
                using rest = Ret(__shrink, Ret(pop_front, l));

                using ret = Ret(do_if, Ret(is_same, curr, Null),
                                id, rest,
                                push_front, L(curr, rest));
            };

            template <is::list l>
            requires(RetV(is_same, Ret(peek_front, l), STOP)) struct apply_on<l>
            {
                using ret = l;
            };
        };

    public:
        FUNC_HEAD_ID;

        template <is::list l>
        struct apply_on<l>
        {
            using ret = Ret(
                C(__trunc, __shrink),
                Ret(join, l, L(__shrink::STOP, __shrink::STOP)));
        };
    };

public:
    FUNC_HEAD_THROW(filter);
    WAIT_FOR_n_DELAYED_ARGS(filter, 2);

    template <is::function f, typename T>
    struct apply_on<L(f, T)>
    {
        using ret = Ret(__check, f, T);
    };

    template <is::function f, is::list l>
    struct apply_on<L(f, l)>
    {
    private:
        using __check_with_f = Ret(bind, __check, f, A(0));

    public:
        using ret = Ret(__filter, Ret(map, __check_with_f, l));
    };
};

struct deep_filter
{
private:
    using __check = filter::__check;
    using __filter = filter::__filter;

    struct __deep_filter
    {
        FUNC_HEAD_ID;

        template <is::list l>
        struct apply_on<l>
        {
            using ret = Ret(__filter, Ret(map, __deep_filter, l));
        };
    };

public:
    FUNC_HEAD_THROW(deep_filter);
    WAIT_FOR_n_DELAYED_ARGS(deep_filter, 2);

    template <is::function f, typename T>
    struct apply_on<L(f, T)>
    {
        using ret = Ret(__check, f, T);
    };

    template <is::function f, is::list l>
    struct apply_on<L(f, l)>
    {
    private:
        using __check_with_f = Ret(bind, __check, f, A(0));

    public:
        using ret = Ret(__deep_filter, Ret(deep_map, __check_with_f, l));
    };
};
