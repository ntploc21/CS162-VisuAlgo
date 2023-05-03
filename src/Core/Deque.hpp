#ifndef CORE_DEQUE_HPP
#define CORE_DEQUE_HPP

#include "List.hpp"

namespace Core {
    /**
     * @brief The deque container
     * @tparam T the type of the elements
     */
    template< typename T >
    class Deque : public List< T > {
    private:
        using List = Core::List< T >;

    public:
        using List::assign;
        using List::List;
        using List::operator=;
        using List::swap;

    public:
        using List::clear;
        using List::empty;
        using List::size;

    public:
        using List::back;
        using List::front;

    public:
        using List::push_back;
        using List::push_front;

    public:
        using List::pop_back;
        using List::pop_front;

    public:
        using List::begin;
        using List::end;

    public:
        using List::resize;

    public:
        using List::remove;
        using List::reverse;
        using List::unique;

    public:
        using List::at;
        using List::operator[];
    };
};  // namespace Core

#endif  // CORE_DEQUE_HPP