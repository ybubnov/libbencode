#ifndef INCLUDE_bencode_algorithm_hpp__
#define INCLUDE_bencode_algorithm_hpp__

#include <iterator>


namespace bencode
{


/**
 *  @brief Copy the range util predicate returns True.
 *
 *  @tparam InputIterator   Input iterator type.
 *  @tparam OutputIterator  Output iterator type.
 *  @tparam Predicate       Unary predicate type.
 *
 *  @param __first   Start of the copy range.
 *  @param __last    End of the copy range.
 *  @param __result  Output iterator.
 *  @param __pred    Unary predicate to use.
 *
 *  Copies the values starting from the @a __first input iterator until
 *  the @a __last input iterator unless the specified predicate returns
 *  False.
 */
template
< typename InputIterator
, typename OutputIterator
, typename Predicate >
InputIterator copy_until(InputIterator __first, InputIterator __last,
    OutputIterator __result, Predicate __pred)
{
    for (; __pred(*__first) && __first != __last;
        ++__first, ++__result)
    { *__result = *__first; }

    return __first;
}


/**
 *  @brief Copy the range until predicate returns True.
 *
 *  @tparam InputIterator   Input iterator type.
 *  @tparam OutputIterator  Output iterator type.
 *  @tparam Predicate       Unary predicate type.
 *  @tparam Distance        Iterator distance type.
 *
 *  @param __first   Start of the copy range.
 *  @param __last    End of the copy range.
 *  @param __result  Output iterator.
 *  @param __pred    Unary predicate to use.
 *  @param __len     Count of elements to copy.
 *
 *  Copies the values starting from the @a __first input iterator until
 *  the @a __last input iterator unless the provided predicate returns
 *  False or specified count of elements already copied.
 */
template
< typename InputIterator
, typename OutputIterator
, typename Predicate
, typename Distance >
InputIterator copy_until(InputIterator __first, OutputIterator __result,
    Predicate __pred, Distance __len)
{
    auto __last = __first;

    for (; __pred(*__first) && std::distance(__first, __last) < __len;
        ++__first, ++__result)
    { *__result = *__first; }

    return __first;
}


}


#endif // INCLUDE_bencode_algorithm_hpp__
