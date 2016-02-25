#ifndef INCLUDE_bencode_algorithm_hpp__
#define INCLUDE_bencode_algorithm_hpp__

#include <iterator>


namespace bencode
{


template
< typename _InputIterator
, typename _OutputIterator
, typename _Predicate >
_InputIterator copy_until(_InputIterator __first, _InputIterator __last,
    _OutputIterator __result, _Predicate __pred)
{
    for (; __pred(*__first) && __first != __last;
        ++__first, ++__result)
    { *__result = *__first; }

    return __first;
}


template
< typename _InputIterator
, typename _OutputIterator
, typename _Predicate
, typename _Distance >
_InputIterator copy_until(_InputIterator __first, _OutputIterator __result,
    _Predicate __pred, _Distance __len)
{
    auto __last = __first;

    for (; __pred(*__first) && std::distance(__first, __last) < __len;
        ++__first, ++__result)
    { *__result = *__first; }

    return __first;
}


}


#endif // INCLUDE_bencode_algorithm_hpp__
