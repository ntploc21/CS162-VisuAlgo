#ifndef CORE_QUEUE_HPP
#define CORE_QUEUE_HPP

#include "List.hpp"

namespace Core {
    /**
     * @brief The queue container
     * @tparam T the type of the elements
     */
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
        /**
         * @brief Returns the reference to the front element of the queue
         * @return T& the reference to the front element of the queue
         */
        T& front() { return List::front(); };

        /**
         * @brief Returns the const reference to the front element of the queue
         * @return const T& the const reference to the front element of the
         * queue
         */
        const T& front() const { return List::front(); };

        /**
         * @brief Returns the reference to the back element of the queue
         * @return T& the reference to the back element of the queue
         */
        T& back() { return List::back(); };

        /**
         * @brief Returns the const reference to the back element of the queue
         * @return const T& the const reference to the back element of the queue
         */
        const T& back() const { return List::back(); };

    public:
        /**
         * @brief Inserts the element at the back of the queue
         * @param elem The element to insert
         */
        void push(const T& value) { List::push_back(value); };

        /**
         * @brief Inserts the element at the back of the queue
         * @param elem The element to insert
         */
        void push(T&& value) { List::push_back(std::move(value)); };

    public:
        /**
         * @brief Removes the front element of the queue
         */

        void pop() { List::pop_front(); };
    };
};  // namespace Core

#endif  // CORE_QUEUE_HPP