#include <stdio.h>
#include "typesdef.h"
#include "outmsg.h"
#include "arith.h"
#include "pair.h"
#include "algor.h"
//#include "stream.h"
#include <type_traits>

#pragma region Ω◊≥À
template <typename T>
struct factorial;
template <int N>
struct factorial<Int<N>>
{
    using ret = Mul(Int<N>, Ret(factorial, Sub(Int<N>, Int<1>)));
};
template <>
struct factorial<Int<0>>
{
    using ret = Int<1>;
};
#pragma endregion

template<typename T> struct is_prime;
template<int n> struct is_prime<Int<n>>
{
    template<typename U> struct loop;
    template<int i>
    struct loop<Int<i>>
    {
        using ret = And(
            Not(IsEqual(Mod(Int<n>, Int<i>), Int<0>)),
            Ret(loop, Inc(Int<i>)));
    };

    template<>
    struct loop<Div(Int<n>, Int<2>)>
    {
        using ret = Not(IsEqual(Mod(Int<n>, Int<2>), Int<0>));
    };

    template<>
    struct loop<Int<n>>
    {
        using ret = True;
    };

    using ret = Ret(loop, Int<2>);
};

#pragma region —≠ª∑≤‚ ‘

template <typename Index>
struct doToIndex
{
    using ret = Inc(Index);
};

template <typename Index>
struct StopBy
{
    using ret = IsGreaterEqual(Index, Int<10>);
};

template <typename Context>
struct LoopFunc
{
    using ret = Mul(Context, Int<2>);
};
#pragma endregion

template<typename T> struct Display;

template <typename... Types>
constexpr int init(Types... args)
{
#pragma region À„ ı‘ÀÀ„≤‚ ‘
    //Display(Formatted(
    //    Add(ARG(6), ARG(int, 5))));
    //Display(Formatted(
    //    Sub(ARG(7), ARG(int, 2))));
    //Display(Formatted(
    //    Mul(ARG(7), ARG(int, 2))));
    //Display(Formatted(
    //    Div(ARG(7), ARG(int, 2))));
    //Display(Formatted(
    //    Mod(ARG(7), ARG(int, 2))));
    //Display(Formatted(
    //    Add(ARG('e'), ARG(int, 5))));
    //Display(Formatted(
    //    Mul(ARG('0'), ARG(int, 2))));
    //Display(Formatted(
    //    Inc(ARG('a'))));
#pragma endregion
#pragma region Œª‘ÀÀ„≤‚ ‘
    //Display(Formatted(
    //    ARG(true)));
    //Display(Formatted(
    //    IsGreater(ARG(int, 5), ARG('e'))));
    //Display(Formatted(
    //    And(ARG(125), ARG(234))));
    //Display(Formatted(
    //    Or(ARG(125), ARG(234))));
    //Display(Formatted(
    //    Not(ARG(125))));
    //Display(Formatted(
    //    Not(ARG(true))));
    //Display(Formatted(
    //    Xor(ARG(125), ARG(234))));
#pragma endregion

#pragma region —°‘ÒΩ·ππ≤‚ ‘
    //Format(
    //    If(IsEqual(ARG(1), ARG(0)),
    //        True,
    //        False));

    //Format(
    //    Ifs(ARG(1), IsEqual(ARG(1), ARG(0)),
    //        ARG(2), IsEqual(ARG(1), ARG(6))));

    //Ifs(
    //    ARG(1), IsEqual(ARG(1), ARG(0)),
    //    ARG(2), IsEqual(ARG(1), ARG(6)),
    //    Format(ARG(3)));

    //Format(
    //    Switch(ARG(1),
    //        ARG(2), ARG(2),
    //        ARG(3), ARG(3),
    //        ARG(1)));
#pragma endregion


#pragma region ¡˜≤‚ ‘
    //Format(STREAM_CAR(evens));
    //Format(STREAM_CAR(STREAM_CDR(evens)));

    //Format(STREAM_CAR(odds));
    //Format(STREAM_CAR(STREAM_CDR(odds)));

    //Format(STREAM_CAR(integers));
    //Format(STREAM_CAR(STREAM_CDR(integers)));
    //STREAM_CDR(integers);
#pragma endregion

    //using primes =
    //    STREAM_FILTER<is_prime>::on<inc_stream::starting_from<Int<2>>::ret>::ret;
    //primes;
    //STREAM_CDR(primes);
    //STREAM_CDR(
    //    STREAM_CDR(primes));

    //Format(STREAM_CAR(primes));
    //Format(STREAM_CAR(STREAM_CDR(primes)));
    //Format(
    //    STREAM_CAR(
    //        STREAM_CDR(
    //            STREAM_CDR(primes))));

    //using my_cons
    //    = MK_CONS_FUN<MK_CONS_PACK_ARGS<_Inc, _Dec>>::ret;

#pragma region ±Ì≤‚ ‘
    using my_list = List<
        List<Int<1>, Int<2>>,
        List<Int<3>, Char<'a'>>,
        List<Char<'b'>, False>>;
    //my_list;
    Display(DeepMap::template Func<List<
        typename compose::template Func<List<Format, _Inc>>::ret,
        my_list>
    >::ret);

    using my_list2 =
        List<
        List<
        List<List<Int<7>>, List<Int<11>, Int<12>>, Int<6>>,
        Int<1>,
        Int<2>
        >,
        List<
        Int<2>,
        List<Int<1>, Int<3>>
        >
        >;

    //Ret(Flatten::Func, List<my_list2>);

    //Ret(DeepMap::Func, List<_Inc, my_list2>);

    using swaped_my_list = Ret(Map::template Func, List<Swap, my_list>);
    //swaped_my_list;

    //Ret(DeepMap::Func, List<Format, swaped_my_list>);

    //Ret(DeepMap::template Func, List<Format, swaped_my_list>);

    //Ret(Format::Func, List<IsGreater(Int<5>, Int<6>)>);
    //Ret(Format::Func, List<Add(Char<'1'>, Int<5>)>);

    Display(Ret(DeepMap::template Func, List<Format, Merge::Func<List<my_list>>::ret>));
    //Flatten::Func<my_list2>::ret;
#pragma endregion

    return 0;
}

int main()
{
    static_assert(init() != 0, "init end.");
}
