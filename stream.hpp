#pragma once

#include "types.hpp"
#include "algorithms.hpp"

struct force {
    template<is::delayed d>
    struct avoid;

    FUNC_HEAD_ID;

    template<is::delayed d>
    struct apply_on<d> {
        using ret = Ret(Ret(force, get::d_func<d>), Ret(map, force, get::d_args<d>));
    };
};

template<typename f, typename... args>
struct delayed {
    using __func = f;
    using __args = Id(args...);

    template<typename T>
    struct apply_on {
        using ret = D(D(f, args...), Id(T));
    };
};

namespace is {
    template<typename T>
    concept stream =
    list<T> &&
    delayed<Ret(peek_back, T)>;
}

struct make::stream {
    FUNC_HEAD_THROW(stream);

    template<is::function next, typename... Ts>
    struct apply_on<L(next, Ts...) > {
        struct find_next {
            template<typename l>
            struct apply_on {
                using next_item = Ret(next, l);
                using next_args = Ret(pop_front, Ret(push_back, next_item, l));
                using ret = L(next_item, D(find_next, next_args));
            };
        };

        using ret = L(Ts..., D(find_next, Ts...));
    };

    template<is::function next, typename T>
    struct apply_on<L(next, T) > {
        struct find_next {
            template<typename l>
            struct apply_on {
                using next_item = Ret(next, l);
                using ret = L(next_item, D(find_next, next_item));
            };
        };

        using ret = L(T, D(find_next, T));
    };
};

struct calc {
    FUNC_HEAD_THROW(calc);

    WAIT_FOR_n_DELAYED_ARGS(calc, 2);

    template<is::not_delayed s, is::not_delayed times> requires (is::stream<s> && is::arg<times>)
    struct apply_on<L(s, times) > {
        using ret = Ret(
                calc,
                Ret(
                        Select(Ret(is_greater, Len(s), A(2)), join, push_front),
                        L(Ret(pop_back, s), Id(F(Ret(peek_back, s))))),
                DEC(times));
    };

    template<is::stream s>
    struct apply_on<L(s, A(0))> {
        using ret = s;
    };
};

struct map_s {
    FUNC_HEAD_THROW(map_s);
    WAIT_FOR_n_DELAYED_ARGS(map_s, 2);

    template<is::function f, is::stream s>
    struct apply_on<L(f, s) > {
        using ret = Ret(
                Select(Ret(is_greater, Len(s), A(2)), push_back, swap),
                Id(Ret(map_s, f, Ret(peek_back, s))), Ret(map, f, Ret(pop_back, s)));
    };
};

struct filter_s {
private:
    struct find_filtered_next {
        FUNC_HEAD_THROW_NO_WAIT;

        template<is::function f, typename find_next>
        struct apply_on<L(f, force::avoid<find_next>)> {
            using next_list = F(find_next);
            using next_item = Ret(peek_front, next_list);
            using next_finder = force::avoid<Ret(peek_back, next_list)>;

            using allowed = Ret(cast, Ret(f, next_item), bool);

            using ret = Ret(do_if, allowed,
                            id, L(next_item, D(find_filtered_next, f, next_finder)),
                            find_filtered_next, L(f, next_finder));
        };
    };

public:
    FUNC_HEAD_THROW(filter_s);

    template<is::function f, is::stream s>
    struct apply_on<L(f, s) > {
        using filtered = Ret(filter, f, Ret(pop_back, s));
        using finder = Ret(peek_back, s);

        using ret = Ret(do_if, Ret(is_same, filtered, filter::Null),
                        force, Ret(find_filtered_next, f, force::avoid<finder>),
                        replace_l, L(D(find_filtered_next, f, force::avoid<finder>), s, DEC(Len(s))));
    };
};
