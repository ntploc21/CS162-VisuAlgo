#ifndef CORE_STACK_HPP
#define CORE_STACK_HPP

#include "List.hpp"

namespace Core {
    /**
     * @brief The stack container
     * @tparam T the type of the elements
     */
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
        /**
         * @brief Returns the reference to the top element of the stack
         * @return T& the reference to the top element of the stack
         */
        T& top() { return List::front(); };

        /**
         * @brief Returns the const reference to the top element of the stack
         * @return const T& the const reference to the top element of the stack
         */
        const T& top() const { return List::front(); };

    public:
        /**
         * @brief Pushes the given value to the top of the stack
         * @param value the value to be pushed
         */
        void push(const T& value) { List::push_front(value); };

        /**
         * @brief Pushes the given value to the top of the stack
         * @param value the value to be pushed
         */
        void push(T&& value) { List::push_front(std::move(value)); };

    public:
        /**
         * @brief Removes the top element of the stack
         */
        void pop() { List::pop_front(); };
    };
};  // namespace Core

#endif  // CORE_STACK_HPP