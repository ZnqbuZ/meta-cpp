#pragma once

#define __EXPAND(...) __VA_ARGS__

#define WAIT_FOR_DELAYED_ARGS(name) \
    template <is::delayed d>        \
    struct apply_on<d>              \
    {                               \
        using ret = D(name, d);     \
    }

#define WAIT_FOR_n_DELAYED_ARGS(name, n)                    \
    template <typename... Ts>                               \
    requires(                                               \
        (sizeof...(Ts) == n) &&                             \
        (is::delayed<Ts> || ...)) struct apply_on<L(Ts...)> \
    {                                                       \
        using ret = D(name, Ts...);                         \
    }

#define WAIT_FOR_EVERY_DELAYED(name)                           \
    template <typename... Ts>                                  \
    requires(is::delayed<Ts> || ...) struct apply_on<L(Ts...)> \
    {                                                          \
        using ret = D(name, Ts...);                            \
    }

#define FUNC_HEAD_THROW_NO_WAIT                    \
    template <typename T>                          \
    struct ERROR_UNIDENTIFIED;                     \
    template <typename _ARG_LIST>                  \
    struct apply_on                                \
    {                                              \
        using ret = ERROR_UNIDENTIFIED<_ARG_LIST>; \
    }

#define FUNC_HEAD_THROW(name) \
    FUNC_HEAD_THROW_NO_WAIT;  \
    WAIT_FOR_DELAYED_ARGS(name)

#define FUNC_HEAD_THROW_WAIT_ALL(name) \
    FUNC_HEAD_THROW(name);             \
    WAIT_FOR_EVERY_DELAYED(name)

#define FUNC_HEAD_ID       \
    template <typename T>  \
    struct apply_on        \
    {                      \
        using ret = Id(T); \
    }

#ifdef _MSC_VER
#define MK_CHAR(x) #@ x
#else
#define MK_CHAR(x) #x[0]
#endif

#define __FIND_5TH_ARG(arg1, arg2, arg3, arg4, arg5, ...) arg5
#define __FIND_6TH_ARG(arg1, arg2, arg3, arg4, arg5, arg6, ...) arg6

#define __DEFN_NAMED_ARG(name, type, value, self) \
    struct name                                   \
    {                                             \
        using __type = type;                      \
        constexpr static __type __value = value;  \
                                                  \
        template <typename arg_list>              \
        struct apply_on                           \
        {                                         \
            using ret = self;                     \
        };                                        \
    }

#define __DEFN_UNNAMED_ARG(name, type, value) \
    __DEFN_NAMED_ARG(name, type, value, name)

#define __DEFN_ARG(...)           \
    __EXPAND(                     \
        __EXPAND(                 \
            __FIND_5TH_ARG(       \
                __VA_ARGS__,      \
                __DEFN_NAMED_ARG, \
                __DEFN_UNNAMED_ARG))(__VA_ARGS__))

template <int n>
__DEFN_ARG(Int, int, n, Int<n>);
__DEFN_ARG(True, bool, true);
__DEFN_ARG(False, bool, false);
namespace chars
{
    template <char c>
    __DEFN_ARG(Special_ASCII, char, c);

#define __DEFN_CHAR_ARG(ch_type, c) \
    __DEFN_ARG(                     \
        ch_type##_##c##_, char, MK_CHAR(c))

    __DEFN_CHAR_ARG(Number, 0);
    __DEFN_CHAR_ARG(Number, 1);
    __DEFN_CHAR_ARG(Number, 2);
    __DEFN_CHAR_ARG(Number, 3);
    __DEFN_CHAR_ARG(Number, 4);
    __DEFN_CHAR_ARG(Number, 5);
    __DEFN_CHAR_ARG(Number, 6);
    __DEFN_CHAR_ARG(Number, 7);
    __DEFN_CHAR_ARG(Number, 8);
    __DEFN_CHAR_ARG(Number, 9);
    __DEFN_CHAR_ARG(Letter, A);
    __DEFN_CHAR_ARG(Letter, B);
    __DEFN_CHAR_ARG(Letter, C);
    __DEFN_CHAR_ARG(Letter, D);
    __DEFN_CHAR_ARG(Letter, E);
    __DEFN_CHAR_ARG(Letter, F);
    __DEFN_CHAR_ARG(Letter, G);
    __DEFN_CHAR_ARG(Letter, H);
    __DEFN_CHAR_ARG(Letter, I);
    __DEFN_CHAR_ARG(Letter, J);
    __DEFN_CHAR_ARG(Letter, K);
    __DEFN_CHAR_ARG(Letter, L);
    __DEFN_CHAR_ARG(Letter, M);
    __DEFN_CHAR_ARG(Letter, N);
    __DEFN_CHAR_ARG(Letter, O);
    __DEFN_CHAR_ARG(Letter, P);
    __DEFN_CHAR_ARG(Letter, Q);
    __DEFN_CHAR_ARG(Letter, R);
    __DEFN_CHAR_ARG(Letter, S);
    __DEFN_CHAR_ARG(Letter, T);
    __DEFN_CHAR_ARG(Letter, U);
    __DEFN_CHAR_ARG(Letter, V);
    __DEFN_CHAR_ARG(Letter, W);
    __DEFN_CHAR_ARG(Letter, X);
    __DEFN_CHAR_ARG(Letter, Y);
    __DEFN_CHAR_ARG(Letter, Z);
    __DEFN_CHAR_ARG(Letter, a);
    __DEFN_CHAR_ARG(Letter, b);
    __DEFN_CHAR_ARG(Letter, c);
    __DEFN_CHAR_ARG(Letter, d);
    __DEFN_CHAR_ARG(Letter, e);
    __DEFN_CHAR_ARG(Letter, f);
    __DEFN_CHAR_ARG(Letter, g);
    __DEFN_CHAR_ARG(Letter, h);
    __DEFN_CHAR_ARG(Letter, i);
    __DEFN_CHAR_ARG(Letter, j);
    __DEFN_CHAR_ARG(Letter, k);
    __DEFN_CHAR_ARG(Letter, l);
    __DEFN_CHAR_ARG(Letter, m);
    __DEFN_CHAR_ARG(Letter, n);
    __DEFN_CHAR_ARG(Letter, o);
    __DEFN_CHAR_ARG(Letter, p);
    __DEFN_CHAR_ARG(Letter, q);
    __DEFN_CHAR_ARG(Letter, r);
    __DEFN_CHAR_ARG(Letter, s);
    __DEFN_CHAR_ARG(Letter, t);
    __DEFN_CHAR_ARG(Letter, u);
    __DEFN_CHAR_ARG(Letter, v);
    __DEFN_CHAR_ARG(Letter, w);
    __DEFN_CHAR_ARG(Letter, x);
    __DEFN_CHAR_ARG(Letter, y);
    __DEFN_CHAR_ARG(Letter, z);
#undef __DEFN_CHAR_ARG
}; // namespace chars

template <typename, typename, typename...>
struct ListBase;
template <typename T1, typename T2, typename... Ts>
struct List : public ListBase<T1, T2, Ts...>
{
};
#define L(...) List<__VA_ARGS__>

// 不能在delayed中检测f是否是函数，如果f中有无终止条件的递归（如流）将检测失败
template <typename f, typename...>
struct delayed;
#define D(...) delayed<__VA_ARGS__>

namespace is
{
    template <typename T>
    concept function =
        requires { typename T::template apply_on<Int<0>>::ret; };

    template <typename T>
    concept arg =
        function<T> &&requires
    {
        typename T::__type;
        T::__value;
    };

    template <typename T>
    concept list =
        requires { typename T::__length; };

    template <typename T>
    concept delayed =
        requires
    {
        typename T::__func;
        typename T::__args;
    };

    template <typename T>
    concept not_delayed = !delayed<T>;

    template <typename T>
    concept ford = function<T> || delayed<T>;
}; // namespace is

class make final
{
private:
    make();
    template <typename type, type>
    struct __arg;

    template <typename... Ts>
    struct __pack
    {
        using ret = L(Ts...);
    };
    template <typename T>
    struct __pack<T>
    {
        using ret = T;
    };

public:
    template <auto value, typename type = decltype(value)>
    using arg = typename __arg<type, value>::ret;

    template <typename... Ts>
    using pack = typename __pack<Ts...>::ret;

    struct stream;
};

#define A(...) make::arg<__VA_ARGS__>
#define P(...) make::pack<__VA_ARGS__>
#define S(...) Ret(make::stream, __VA_ARGS__)

class get final
{
private:
    get();
    template <typename f, typename...>
    requires(is::function<f> || is::delayed<f>) struct __ret;

    template <is::function f, typename... args>
    struct __ret<f, args...>
    {
        using ret = typename f::template apply_on<P(args...)>::ret;
    };

    template <is::delayed f, typename... args>
    struct __ret<f, args...>
    {
        using ret = D(f, args...);
    };

public:
    template <typename f, typename... args>
    requires(is::function<f> || is::delayed<f>) using ret = typename __ret<f, args...>::ret;
    template <is::arg T>
    using self = typename T::__self;
    template <is::arg T>
    using type = typename T::__type;
    template <is::arg T>
    static constexpr auto value = T::__value;
    template <is::function f, typename... args>
    static constexpr auto ret_v = value<ret<f, args...>>;
    template <is::list T>
    using length = typename T::__length;
    template <is::delayed d>
    using d_func = typename d::__func;
    template <is::delayed d>
    using d_args = typename d::__args;
};

#define Type(...) get::type<__VA_ARGS__>
#define Value(...) get::value<__VA_ARGS__>
#define RetV(...) get::ret_v<__VA_ARGS__>
#define Len(...) get::length<__VA_ARGS__>
#define Id(...) get::ret<id, __VA_ARGS__>
#define Ret(...) Id(get::ret<__VA_ARGS__>)

struct is_same
{
    FUNC_HEAD_THROW(is_same);
    WAIT_FOR_n_DELAYED_ARGS(is_same, 2);

    template <typename T, typename V>
    struct apply_on<L(T, V)>
    {
        using ret = False;
    };

    template <typename T>
    struct apply_on<L(T, T)>
    {
        using ret = True;
    };
};

namespace is
{
    // const bool 等也认为是bool_value
    template <typename T>
    concept bool_type =
        arg<T> && (Value(T) == true ||
                   Value(T) == false);

    template <typename T>
    concept unidentified_type =
        !RetV(is_same, T, int) &&
        !RetV(is_same, T, bool) &&
        !RetV(is_same, T, char);
}; // namespace is

template <is::unidentified_type Unidentified, Unidentified value>
__DEFN_ARG(Arg, Unidentified, value);

#undef __DEFN_ARG

#pragma region make

#define __DEFN_ARG_MAKER(...)    \
    {                            \
        friend make;             \
                                 \
    private:                     \
        using ret = __VA_ARGS__; \
    }

template <typename Unidentified, Unidentified value>
struct make::__arg
    __DEFN_ARG_MAKER(Arg<Unidentified, value>);
template <int n>
struct make::__arg<int, n>
    __DEFN_ARG_MAKER(Int<n>);
template <>
struct make::__arg<bool, true>
    __DEFN_ARG_MAKER(True);
template <>
struct make::__arg<bool, false>
    __DEFN_ARG_MAKER(False);

#pragma region Char Argument Makers

template <char c>
struct make::__arg<char, c>
    __DEFN_ARG_MAKER(chars::Special_ASCII<c>);

#define __GEN_CHAR_ARG_MAKER(type, c)    \
    template <>                          \
    struct make::__arg<char, MK_CHAR(c)> \
        __DEFN_ARG_MAKER(chars::type##_##c##_)

__GEN_CHAR_ARG_MAKER(Number, 0);
__GEN_CHAR_ARG_MAKER(Number, 1);
__GEN_CHAR_ARG_MAKER(Number, 2);
__GEN_CHAR_ARG_MAKER(Number, 3);
__GEN_CHAR_ARG_MAKER(Number, 4);
__GEN_CHAR_ARG_MAKER(Number, 5);
__GEN_CHAR_ARG_MAKER(Number, 6);
__GEN_CHAR_ARG_MAKER(Number, 7);
__GEN_CHAR_ARG_MAKER(Number, 8);
__GEN_CHAR_ARG_MAKER(Number, 9);
__GEN_CHAR_ARG_MAKER(Letter, A);
__GEN_CHAR_ARG_MAKER(Letter, B);
__GEN_CHAR_ARG_MAKER(Letter, C);
__GEN_CHAR_ARG_MAKER(Letter, D);
__GEN_CHAR_ARG_MAKER(Letter, E);
__GEN_CHAR_ARG_MAKER(Letter, F);
__GEN_CHAR_ARG_MAKER(Letter, G);
__GEN_CHAR_ARG_MAKER(Letter, H);
__GEN_CHAR_ARG_MAKER(Letter, I);
__GEN_CHAR_ARG_MAKER(Letter, J);
__GEN_CHAR_ARG_MAKER(Letter, K);
__GEN_CHAR_ARG_MAKER(Letter, L);
__GEN_CHAR_ARG_MAKER(Letter, M);
__GEN_CHAR_ARG_MAKER(Letter, N);
__GEN_CHAR_ARG_MAKER(Letter, O);
__GEN_CHAR_ARG_MAKER(Letter, P);
__GEN_CHAR_ARG_MAKER(Letter, Q);
__GEN_CHAR_ARG_MAKER(Letter, R);
__GEN_CHAR_ARG_MAKER(Letter, S);
__GEN_CHAR_ARG_MAKER(Letter, T);
__GEN_CHAR_ARG_MAKER(Letter, U);
__GEN_CHAR_ARG_MAKER(Letter, V);
__GEN_CHAR_ARG_MAKER(Letter, W);
__GEN_CHAR_ARG_MAKER(Letter, X);
__GEN_CHAR_ARG_MAKER(Letter, Y);
__GEN_CHAR_ARG_MAKER(Letter, Z);
__GEN_CHAR_ARG_MAKER(Letter, a);
__GEN_CHAR_ARG_MAKER(Letter, b);
__GEN_CHAR_ARG_MAKER(Letter, c);
__GEN_CHAR_ARG_MAKER(Letter, d);
__GEN_CHAR_ARG_MAKER(Letter, e);
__GEN_CHAR_ARG_MAKER(Letter, f);
__GEN_CHAR_ARG_MAKER(Letter, g);
__GEN_CHAR_ARG_MAKER(Letter, h);
__GEN_CHAR_ARG_MAKER(Letter, i);
__GEN_CHAR_ARG_MAKER(Letter, j);
__GEN_CHAR_ARG_MAKER(Letter, k);
__GEN_CHAR_ARG_MAKER(Letter, l);
__GEN_CHAR_ARG_MAKER(Letter, m);
__GEN_CHAR_ARG_MAKER(Letter, n);
__GEN_CHAR_ARG_MAKER(Letter, o);
__GEN_CHAR_ARG_MAKER(Letter, p);
__GEN_CHAR_ARG_MAKER(Letter, q);
__GEN_CHAR_ARG_MAKER(Letter, r);
__GEN_CHAR_ARG_MAKER(Letter, s);
__GEN_CHAR_ARG_MAKER(Letter, t);
__GEN_CHAR_ARG_MAKER(Letter, u);
__GEN_CHAR_ARG_MAKER(Letter, v);
__GEN_CHAR_ARG_MAKER(Letter, w);
__GEN_CHAR_ARG_MAKER(Letter, x);
__GEN_CHAR_ARG_MAKER(Letter, y);
__GEN_CHAR_ARG_MAKER(Letter, z);

#undef __GEN_CHAR_ARG_MAKER
#pragma endregion

#undef __DEFN_ARG_MAKER
#pragma endregion

template <bool b>
using Bool = A(b);
template <char c>
using Char = A(c);

struct id
{
    template <typename T>
    struct apply_on
    {
        using ret = T;
    };

    template <is::arg T>
    struct apply_on<T>
    {
        using ret = get::ret<T, void>;
    };
};

template <typename T1, typename T2, typename... Ts>
struct ListBase
{
    using __length = Int<2 + sizeof...(Ts)>;
    struct push_front
    {
        template <typename T>
        struct apply_on
        {
            using ret = L(Id(T), Id(T1), Id(T2), Ts...);
        };
    };
    struct push_back
    {
        template <typename T>
        struct apply_on
        {
            using ret = L(Id(T1), Id(T2), Ts..., Id(T));
        };
    };
    struct peek_front
    {
        template <typename T>
        struct apply_on
        {
            using ret = Id(T1);
        };
    };
    struct peek_back
    {
        template <typename T>
        struct apply_on
        {
            using ret = decltype(Id(T1){}, ((Id(T2){}), ..., (Id(Ts){})));
        };
    };
    struct pop_front
    {
        template <typename T>
        struct apply_on
        {
            using ret = P(Id(T2), Ts...);
        };
    };

private:
    template <typename...>
    struct discard_last;
    template <typename V1, typename V2, typename V3, typename... Vs>
    struct discard_last<V1, V2, V3, Vs...>
    {
        using ret = Ret(typename discard_last<V2, V3, Vs...>::ret::push_front, Id(V1));
    };
    template <typename V1, typename V2, typename V3>
    struct discard_last<V1, V2, V3>
    {
        using ret = L(Id(V1), Id(V2));
    };
    template <typename V1, typename V2>
    struct discard_last<V1, V2>
    {
        using ret = Id(V1);
    };

public:
    struct pop_back
    {
        template <typename T>
        struct apply_on
        {
            using ret = typename discard_last<T1, T2, Ts...>::ret;
        };
    };
};

template <is::function T1, is::function T2, is::function... Ts>
struct List<T1, T2, Ts...> : public ListBase<T1, T2, Ts...>
{
    template <typename arg_list>
    struct apply_on
    {
        using ret = L(Ret(T1, arg_list), Ret(T2, arg_list), Ret(Ts, arg_list)...);
    };
};

template <typename f, typename... args>
struct delayed
{
    using __func = f;
    using __args = P(args...);
};

#define C(...) Ret(compose, __VA_ARGS__)
struct compose
{
    FUNC_HEAD_THROW(compose);

    template <is::ford f, is::ford... gs>
    struct apply_on<L(f, gs...)>
    {
        using ret = C(f, C(gs...));
    };

    template <is::ford f, is::ford g>
    struct apply_on<L(f, g)>
    {
        struct ret
        {
            template <typename arg_list>
            struct apply_on
            {
                using ret = Ret(f, Ret(g, arg_list));
            };
        };
    };
};

namespace is
{
    template <typename a, typename T>
    concept castable =
        arg<a> &&requires { (T) Value(a); };
} // namespace is

struct cast
{
    FUNC_HEAD_THROW(cast);
    WAIT_FOR_n_DELAYED_ARGS(cast, 2);

    template <is::arg arg, typename T>
    requires(is::castable<arg, T>) struct apply_on<L(arg, T)>
    {
        using ret = A((T)Value(arg), Id(T));
    };
};

#pragma region Simple Function Generators

#define DEFN_UNARY_FUN(name, var, expr) \
    struct name                         \
    {                                   \
        FUNC_HEAD_THROW(name);          \
        template <is::arg var>          \
        struct apply_on<var>            \
        {                               \
            using ret = expr;           \
        };                              \
    }

#define DEFN_BINARY_FUN(name, var1, var2, expr) \
    struct name                                 \
    {                                           \
        FUNC_HEAD_THROW(name);                  \
        WAIT_FOR_n_DELAYED_ARGS(name, 2);       \
        template <                              \
            is::arg var1,                       \
            is::arg var2>                       \
        struct apply_on<L(var1, var2)>          \
        {                                       \
            using ret = expr;                   \
        };                                      \
    }
#pragma endregion

DEFN_BINARY_FUN(is_value_equal, x, y, A(Value(x) == Value(y), bool));
DEFN_BINARY_FUN(is_greater, x, y, A((Value(x) > Value(y)), bool));
DEFN_BINARY_FUN(is_less, x, y, A(Value(x) < Value(y), bool));

#define Select(...) Ret(select, __VA_ARGS__)
struct select
{
    FUNC_HEAD_THROW(select);

    template <is::delayed cond, typename THEN, typename ELSE>
    struct apply_on<L(cond, THEN, ELSE)>
    {
        using ret = D(select, cond, THEN, ELSE);
    };

    template <is::bool_type cond, typename THEN, typename ELSE>
    requires(Value(cond)) struct apply_on<L(cond, THEN, ELSE)>
    {
        using ret = THEN;
    };

    template <is::bool_type cond, typename THEN, typename ELSE>
    requires(!Value(cond)) struct apply_on<L(cond, THEN, ELSE)>
    {
        using ret = ELSE;
    };
};