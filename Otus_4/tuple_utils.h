#pragma once
#include <tuple>
//стянуто https://habr.com/ru/post/318236/
namespace tuple_utils
{
    // вызвать 'callback' для каждого элемента кортежа
    /*
        struct callback
        {
            template<std::size_t, class T>
            void operator()( T&& element )
            {
                // do something
            }
        };
        tupleForeach( callback(), myTuple );
    */
    template<class TCallback, class ...TParams>
    void tupleForeach(TCallback& callback, const std::tuple<TParams...>& tuple);

    namespace
    {

        template<std::size_t Index, class TCallback, class ...TParams>
        struct _foreach_
        {
            static void tupleForeach_(TCallback& callback, const std::tuple<TParams...>& tuple)
            {
                // такой пересчёт необходим для выполнения callback'a над элементами в порядке их следования
                const std::size_t idx = sizeof...(TParams) - Index;
                callback/*.operator*/()<idx> (std::get<idx>(tuple));
                _foreach_<Index - 1, TCallback, TParams...>::tupleForeach_(callback, tuple);
            }
        };

        template<class TCallback, class ...TParams>
        struct _foreach_<0, TCallback, TParams...>
        {
            static void tupleForeach_(TCallback& /*callback*/, const std::tuple<TParams...>& /*tuple*/) {}
        };

    } //
    template<class TCallback, class ...TParams>
    void tupleForeach(TCallback& callback, const std::tuple<TParams...>& tuple)
    {
        _foreach_<sizeof...(TParams), TCallback, TParams...>::tupleForeach_(callback, tuple);
    }

} // tuple_utils
#pragma once
