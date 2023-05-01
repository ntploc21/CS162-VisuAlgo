#ifndef CORE_STACK_HPP
#define CORE_STACK_HPP

#include "List.hpp"

namespace Core {
    template< typename T >
    class Stack : public List< T > {
    private:
        using List = Core::List< T >;

    public:
        using List::List;
        using List::operator=;
        using List::swap;

    public:
        using List::empty;
        using List::size;

    public:
        T& top() { return List::front(); };
        const T& top() const { return List::front(); };

    public:
        void push(const T& value) { List::push_front(value); };
        void push(T&& value) { List::push_front(std::move(value)); };

    public:
        void pop() { List::pop_front(); };
    };
};  // namespace Core

#endif  // CORE_STACK_HPP