// meta-cpp.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "basic_types.h"
#include "algorithms.h"
#include "arithmetics.h"
#include "stream.h"

int main()
{
}

#pragma region test lists
using test_list_1 =
L(
    A(9),
    L(
        A(1),
        L(
            A(2),
            A(4))),
    L(
        A(3),
        A(4)),
    L(
        A(7),
        L(
            A(6),
            L(
                A(2),
                A(4)))),
    A(10)
);

using test_list_2 =
L(
    L(A(1), A(2)),
    L(A(2), A(3)),
    L(A(3), A(4)));

using test_list_3 = Ret(push_back, L(L(A(4), A(5), A(7)), A(5)), test_list_2);
#pragma endregion

DEFN_UNARY_FUN(twice, x, 2 * Value(x));
DEFN_UNARY_FUN(odd, x, Value(x) % 2);

//#define ALGOR_TEST

#ifdef ALGOR_TEST

Ret(peek_front, A(1));
Ret(peek_front, test_list_1);
Ret(pop_front, test_list_1);
Ret(peek_back, test_list_1);
Ret(pop_back, test_list_1);

Ret(flatten, test_list_1);
Ret(join, test_list_1, test_list_2);

Ret(deep_map, Inc, test_list_1);
Ret(deep_map, Neg, test_list_1);
Ret(deep_map, Dec, test_list_1);

Ret(map, swap, test_list_2);

Ret(map, Add, test_list_2);
Ret(map, Sub, test_list_2);
Ret(map, Mul, test_list_2);
Ret(map, Div, test_list_2);
Ret(map, Mod, test_list_2);

Ret(map, And, test_list_2);
Ret(map, Or, test_list_2);
Ret(map, Xor, test_list_2);
Ret(deep_map, Not, test_list_2);
Ret(map, NAnd, test_list_2);
Ret(map, NOr, test_list_2);

Ret(insert_l, A(999), test_list_2, A(-1));
Ret(insert_l, A(999), test_list_2, A(0));
Ret(insert_l, A(999), test_list_2, A(1));
Ret(insert_l, A(999), test_list_2, A(2));
Ret(insert_l, A(999), test_list_2, A(3));
Ret(insert_l, A(999), test_list_2, A(4));

Ret(remove_l, test_list_2, A(-1));
Ret(remove_l, test_list_2, A(0));
Ret(remove_l, test_list_2, A(1));
Ret(remove_l, test_list_2, A(2));
Ret(remove_l, test_list_2, A(3));

Ret(replace_l, A(999), test_list_2, A(-1));
Ret(replace_l, A(999), test_list_2, A(0));
Ret(replace_l, A(999), test_list_2, A(1));
Ret(replace_l, A(999), test_list_2, A(2));
Ret(replace_l, A(999), test_list_2, A(3));
Ret(replace_l, A(999), test_list_2, A(4));

test_list_3;

Ret(remove_l, test_list_3, A(-1));
Ret(remove_l, test_list_3, A(0));
Ret(remove_l, test_list_3, A(1));
Ret(remove_l, test_list_3, A(2));
Ret(remove_l, test_list_3, A(3));

Ret(filter, Not, L(True, False));
Ret(filter, Not, L(False, False));
Ret(filter, Not, L(True, True));

Ret(filter, odd, Ret(flatten, test_list_1));
Ret(filter, odd, Ret(flatten, test_list_3));

Ret(deep_filter, odd, test_list_1);
Ret(deep_filter, odd, test_list_3);
#endif

#pragma region test streams

using integer_seq = S(Inc, A(1));
using even_seq = Ret(map_s, twice, integer_seq);
using fibonacci_seq = S(Add, A(1), A(1));
using odd_seq = Ret(filter_s, odd, integer_seq);
using odd_fibonacci_seq = Ret(filter_s, odd, fibonacci_seq);

struct mk_prime_finder
{
    FUNC_HEAD_THROW(mk_prime_finder);

    template<is::arg N, is::delayed finder>
    struct apply_on<L(N, force::avoid<finder>)>
    {
        using last_prime = Id(N);

        using s = L(last_prime, finder);

        using p_aliquant = C(
            Ret(
                bind,
                cast,
                L(bool, A(1))),
            Ret(
                bind,
                Mod,
                L(last_prime, A(1))));

        using temp_s = L(INC(last_prime), Ret(peek_back, s));

        using new_finder =
            Ret(peek_back,
                Ret(
                    filter_s,
                    p_aliquant,
                    temp_s)
            );

        using next_list = F(new_finder);
        using next_prime = Ret(peek_front, next_list);

        using ret = L(Id(next_prime), D(mk_prime_finder, L(next_prime, force::avoid<Ret(peek_back, next_list)>)));
    };
};
using prime_seq =
L(A(2), D(mk_prime_finder, L(A(2), force::avoid<Ret(peek_back, integer_seq)>)));
#pragma endregion

#define STREAM_TEST

#ifdef STREAM_TEST

Ret(pop_back, Ret(calc, integer_seq, A(9)));
Ret(pop_back, Ret(calc, even_seq, A(9)));
Ret(pop_back, Ret(calc, fibonacci_seq, A(9)));
Ret(pop_back, Ret(calc, odd_seq, A(9)));
Ret(pop_back, Ret(calc, odd_fibonacci_seq, A(9)));

Ret(pop_back, Ret(calc, prime_seq, A(30)));
#endif
