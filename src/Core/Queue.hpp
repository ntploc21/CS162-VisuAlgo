#ifndef CORE_QUEUE_HPP
#define CORE_QUEUE_HPP

#include "List.hpp"

namespace Core {
    template< typename T >
    class Queue : public List< T > {
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
        T& front() { return List::front(); };
        const T& front() const { return List::front(); };

        T& back() { return List::back(); };
        const T& back() const { return List::back(); };

    public:
        void push(const T& value) { List::push_back(value); };
        void push(T&& value) { List::push_back(std::move(value)); };

    public:
        void pop() { List::pop_front(); };
    };
};  // namespace Core

#endif  // CORE_QUEUE_HPP