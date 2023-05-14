#ifndef CORE_LIST_HPP
#define CORE_LIST_HPP

// #define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
// #define _SILENCE_CXX17_ITERATOR_BASE_CLASS_DEPRECATION_WARNING

#include <algorithm>
#include <cstddef>
#include <functional>
#include <initializer_list>
#include <iterator>
#include <stdexcept>

#include "Node.hpp"

namespace Core {
    /**
     * @brief The base container for implementing other data structures
     * @tparam T the type of the elements
     */
    template< typename T >
    class List {
    public:
        class iterator;
        class const_iterator;

    private:
        /**
         * @brief The head of the list
         */
        iterator mBegin;

        /**
         * @brief The end of the list (one past the last element)
         */
        iterator mEnd;

        /**
         * @brief The size of the list
         */
        std::size_t mSize;

        void reset() {
            this->mBegin = this->mEnd;
            this->mEnd.ptr->mPrev = nullptr;
            this->mSize = 0;
        }

        /**
         * @brief Insert an iterator before the specified iterator
         * @param it The iterator to insert the iterator (prev) before
         * @param it_prev The iterator to insert
         */
        void insert_previous(const iterator& it, const iterator& it_prev) {
            Node< T >* node = it.ptr;
            Node< T >* node_prev = it_prev.ptr;

            node_prev->mNext = node;
            node_prev->mPrev = node->mPrev;
            // node->mPrev = node_prev;
            node_prev->mNext->mPrev = node_prev;
            if (node_prev->mPrev != nullptr) {
                node_prev->mPrev->mNext = node_prev;
            }

            if (it == this->begin()) {
                this->mBegin = node_prev;
            }

            ++this->mSize;
        }

        /* @brief Move nodes from a list of range [`first`, `last`) to before
         * `it`
         * @param it The iterator to insert the nodes before
         * @return iterator pointing to the first inserted element, or
         * `it` if `first` == `last`.
         * @exception: undefined behaviour: null pointer reference
         */
        iterator move_previous(const iterator& it, const iterator& first,
                               const iterator& last) {
            mSize += std::distance(first, last);

            iterator prev = it;
            prev--;

            if (first != last) {
                Node< T >* node = it.ptr;
                Node< T >* node_first = first.ptr;
                Node< T >* node_last = last.ptr->mPrev;

                node_first->mPrev = node->mPrev;
                if (node->mPrev != nullptr) {
                    node->mPrev->mNext = node_first;
                }

                node_last->mNext = node;
                node->mPrev = node_last;

                if (it == this->begin()) {
                    this->mBegin = node_first;
                }
            }

            return prev == nullptr ? this->begin() : prev++;
        }

        /**
         * @brief Returns an iterator to the element at index `index`
         * @param index The index of the element
         * @return An iterator to the element at index `index`
         * @exception std::out_of_range if `index` is out of range
         */
        iterator get_iterator(std::size_t index) {
            if (!(index >= 0 && index < this->size())) {
                throw std::out_of_range("Index out of range");
            }

            iterator it;
            if (index < this->size() / 2) {
                it = this->begin();
                for (std::size_t i = 0; i < index; ++i) ++it;
            } else {
                it = this->end();
                for (std::size_t i = this->size() - 1; i >= index; --i) --it;
            }
            return it;
        }

    public:
        /**
         * @brief Default constructor
         */
        List() : mSize(0) { this->mBegin = this->mEnd = new Node< T >(); }

        /**
         * @brief Constructs the container with the contents of the initializer
         * list
         * @param init_list The initializer list
         */
        List(std::initializer_list< T > list) : mSize(0) {
            this->mBegin = this->mEnd = new Node< T >();
            for (const auto& element : list) {
                this->push_back(element);
            }
        }

        /**
         * @brief Destructor
         */
        ~List() {
            this->clear();
            delete mEnd.ptr;
        }

        /**
         * @brief Copy constructor
         * @param rhs The other container
         */
        List(const List< T >& list) : mSize(0) {
            this->mBegin = this->mEnd = new Node< T >();
            for (const auto& element : list) {
                this->push_back(element);
            }
        }

        /**
         * @brief Move constructor
         * @param rhs The other container
         */
        List(List< T >&& list) : mSize(0) {
            this->mBegin = this->mEnd = new Node< T >();
            move_previous(this->end(), list.begin(), list.end());
            list.reset();
        }

        /**
         * @brief Copy assign the container with the contents of the initializer
         * list
         * @param init_list The initializer list
         */
        List< T >& operator=(std::initializer_list< T > list) {
            assign(list);
            return *this;
        }

        /**
         * @brief Copy assignment operator
         * @param rhs The other container
         */
        List< T >& operator=(const List< T >& list) {
            if (this == &list) return *this;
            this->assign(list.begin(), list.end());
            return *this;
        }

        /**
         * @brief Move assignment operator
         * @param rhs The other container
         */
        List< T >& operator=(List< T >&& list) {
            if (this == &list) return *this;
            this->clear();
            this->move_previous(this->end(), list.begin(), list.end());
            list.reset();
            return *this;
        }

    protected:
        iterator begin() { return mBegin; }
        const_iterator begin() const { return mBegin; }
        iterator end() { return mEnd; }
        const_iterator end() const { return mEnd; }

    public:
        /**
         * @brief Check whether the container is empty
         * @retval true The container is empty
         * @retval false The container is not empty
         */
        [[nodiscard]] bool empty() const { return this->size() == 0; }

        /**
         * @brief Returns the size of the container
         * @return The size of the container
         */
        [[nodiscard]] std::size_t size() const { return this->mSize; }

    protected:
        /**
         * @brief Returns the reference to the element at the front of the
         * container
         * @return T& The reference to the element at the front of the container
         * @exception: undefined behavior: null pointer dereference
         */
        T& front() { return *this->begin(); }

        /**
         * @brief Returns the reference to the element at the front of the
         * container
         * @return T& The reference to the element at the front of the container
         * @exception: undefined behavior: null pointer dereference
         */
        const T& front() const { return *this->begin(); }

        /**
         * @brief Returns the reference to the element at the back of the
         * container
         * @return T& The reference to the element at the back of the container
         * @exception: undefined behavior: null pointer dereference
         */
        T& back() {
            auto it = this->end();
            --it;
            return *it;
        }

        /**
         * @brief Returns the reference to the element at the back of the
         * container
         * @return T& The reference to the element at the back of the container
         * @exception: undefined behavior: null pointer dereference
         */
        const T& back() const {
            auto it = this->end();
            --it;
            return *it;
        }

        /**
         * @brief Returns the reference to the element at the given index
         * @param index The index of the element
         * @return T& The reference to the element at the given index
         * @exception: std::out_of_range: index out of range
         */
        T& operator[](std::size_t index) { return *this->get_iterator(index); }

        /**
         * @brief Returns the reference to the element at the given index
         * @param index The index of the element
         * @return T& The reference to the element at the given index
         * @exception: std::out_of_range: index out of range
         */
        const T& operator[](std::size_t index) const {
            return *this->get_iterator(index);
        }

        /**
         * @brief Returns the reference to the element at the given index
         * @param index The index of the element
         * @return T& The reference to the element at the given index
         * @exception: std::out_of_range: index out of range
         */
        T& at(std::size_t index) { return (*this)[index]; }

        /**
         * @brief Returns the reference to the element at the given index
         * @param index The index of the element
         * @return T& The reference to the element at the given index
         * @exception: std::out_of_range: index out of range
         */
        const T& at(std::size_t index) const { return (*this)[index]; }

        /**
         * @brief Pushes the element to the front of the container
         * @param elem The element to be pushed into the front
         */
        void push_front(const T& value) {
            Node< T >* node = new Node< T >(value);
            this->insert_previous(this->begin(), iterator(node));
        }

        /**
         * @brief Pushes the element to the back of the container
         * @param elem The element to be pushed into the back
         */
        void push_back(const T& value) {
            Node< T >* node = new Node< T >(value);
            this->insert_previous(this->end(), iterator(node));
        }

        /**
         * @brief Removes the element at the front of the container
         */
        void pop_front() {
            auto it = this->begin();
            this->remove(it);
        }

        /**
         * @brief Removes the element at the back of the container
         */
        void pop_back() {
            auto it = --this->end();
            this->remove(it);
        }

    protected:
        /**
         * @brief Removes the element iterator in the container
         * @param it The iterator to the element to be removed
         * @return iterator The iterator to the next element
         * @exception: std::out_of_range: iterator out of range
         */
        iterator remove(const iterator& it) {
            if (it == this->end()) {
                throw std::out_of_range("Iterator out of range");
            }

            Node< T >* node = it.ptr;
            Node< T >* node_prev = node->mPrev;
            Node< T >* node_next = node->mNext;

            if (node_prev != nullptr) node_prev->mNext = node_next;

            if (node_next != nullptr) node_next->mPrev = node_prev;

            if (it == this->begin()) {
                this->mBegin = node_next;
            }

            delete node;
            --this->mSize;
            return node_next;
        }

        /**
         * @brief Removes the elements in the range [begin, end)
         * @param begin The iterator to the first element to be removed
         * @param end The iterator to the last element to be removed
         * @return iterator The iterator to the next element
         * @exception: std::out_of_range: iterator out of range
         */
        int remove(const T& value, const iterator& begin, const iterator& end) {
            return this->remove_if(
                [&value](const T& element) { return element == value; }, begin,
                end);
        }

        /**
         * @brief Removes the elements that has the same value as the given one
         * @param value The value of the elements to be removed
         * @return iterator The iterator to the next element
         */
        int remove(const T& value) {
            return this->remove_if(
                [&value](const T& element) { return element == value; },
                this->begin(), this->end());
        }

        /*
            @brief Removes all elements satisfying specific criteria from the
           range [first, last) and returns a past-the-end iterator for the new
           end of the range.
            @return the resulting size
        */
        int remove_if(std::function< bool(const T&) > predicate,
                      const iterator& begin, const iterator& end) {
            for (auto it = begin; it != end;) {
                if (predicate(*it)) {
                    it = this->remove(it);
                } else {
                    ++it;
                }
            }
            return this->size();
        }

        /*
            @brief Removes all elements satisfying specific criteria from the
           range [first, last) and returns a past-the-end iterator for the new
           end of the range.
            @return the resulting size
        */
        int remove_if(std::function< bool(const T&) > predicate) {
            return this->remove_if(predicate, this->begin(), this->end());
        }

        /**
         * @brief Resizes the container to contain the given number of elements
         * @param count The new size of the container
         */
        void resize(std::size_t count) {
            while (this->size() < count) this->push_back(T());

            while (this->size() > count) this->pop_back();
        }

        /**
         * @brief Resizes the container to contain the given number of elements
         * @param count The new size of the container
         * @param value The value to be used to fill the container
         */
        void resize(std::size_t count, const T& value) {
            while (this->size() < count) this->push_back(value);

            while (this->size() > count) this->pop_back();
        }

        /**
         * @brief Assigns new contents to the list, replacing its current
         * content with `count` copies of `value`
         * @param count The new size of the container
         * @param value The value to be used to fill the container
         */
        void assign(std::size_t count, const T& value) {
            this->clear();
            this->resize(count, value);
        }

        /**
         * @brief Assigns new contents to the list, replacing its current
         * content
         * @param begin The iterator to the first element to be assigned
         * @param end The iterator to the last element to be assigned
         */
        void assign(const const_iterator& begin, const const_iterator& end) {
            this->resize(std::distance(begin, end));

            auto itOther = begin;
            for (auto it = this->begin(); it != this->end(); ++it, ++itOther) {
                *it = *itOther;
            }
        }

        /**
         * @brief Assigns new contents to the list, replacing its current
         * content
         * @param list The initializer list to be assigned
         */
        void assign(std::initializer_list< T > list) {
            this->resize(list.size());

            auto itOther = list.begin();
            for (auto it = this->begin(); it != this->end(); ++it, ++itOther) {
                (*it) = (*itOther);
            }
        }

        /**
         * @brief Eliminates all except the first element from every
         * consecutive group of equivalent elements from the range [`first`,
         * `last`) and returns a past-the-end iterator for the new logical end
         * of the range.
         * @return the resulting size
         */
        std::size_t unique() {
            iterator last = std::unique(this->begin(), this->end());
            this->resize(std::distance(this->begin(), last));

            return this->size();
        }

        /**
         * @brief Eliminates all except the first element from every
         * consecutive group of equivalent elements from the range [`first`,
         * `last`) and returns a past-the-end iterator for the new logical end
         * of the range.
         * @param predicate Binary predicate that, taking two values of the same
         * type than those contained in the list, returns true to remove the
         * element passed as first argument from the container, and false
         * otherwise.
         * @return the resulting size
         */
        std::size_t unique(
            std::function< bool(const T&, const T&) > predicate) {
            iterator last = std::unique(this->begin(), this->end(), predicate);
            this->resize(std::distance(this->begin(), last));

            return this->size();
        }

        /**
         * @brief Reverses the order of the elements in the list
         */
        void reverse() {
            if (!this->empty()) {
                for (auto it = this->begin(), itNext = this->begin();
                     it != this->end(); it = itNext) {
                    itNext = it;
                    ++itNext;

                    Node< T >* node = it.ptr;
                    Node< T >* node_next = itNext.ptr;

                    node->mNext = node->mPrev;
                    node->mPrev = node_next;
                }
            }

            iterator new_head = this->end();
            --new_head;
            iterator new_tail = this->begin();

            new_head.ptr->mPrev = nullptr;
            new_tail.ptr->mNext = this->end().ptr;
            this->mBegin = new_head;
            this->mEnd.ptr->mPrev = new_tail.ptr;
        }

    protected:
        /**
         * @brief Swaps the contents of the list with those of other
         * @param other list to exchange the contents with
         */
        void swap(List< T >& other) {
            std::swap(this->mBegin, other.mBegin);
            std::swap(this->mEnd, other.mEnd);
            std::swap(this->mSize, other.mSize);
        }

    public:
        /**
         * @brief Frees all elements in the container
         *
         */
        void clear() {
            if (!this->empty()) {
                for (auto it = this->begin(); it != this->end();) {
                    Node< T >* node = it.ptr;
                    ++it;
                    delete node;
                }
            }
            this->reset();
        }
    };
};  // namespace Core

namespace Core {
    /**
     * @brief The list iterator class
     * @tparam T The type of the elements
     */
    template< typename T >
    class List< T >::iterator
    // : public std::iterator< std::bidirectional_iterator_tag, T,
    //                         std::ptrdiff_t, T*, T& >
    // deprecated since C++17
    {
        friend class List;

    private:
        Node< T >* ptr;

    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        /**
         * @brief Construct a new iterator object
         *
         */
        iterator() : ptr{nullptr} {}

        /**
         * @brief Construct a new iterator object
         *
         * @param p The pointer to the node
         */
        iterator(Node< value_type >* const& p) : ptr(p) {}
        reference operator*() const {
            reference value = ptr->mValue;
            return value;
        }

        /**
         * @brief Returns a pointer to the object pointed to by the iterator
         *
         * @return pointer to the object pointed to by the iterator
         */
        pointer operator->() const { return std::addressof(operator*()); }

        /**
         * @brief Prefix increment
         * @return reference to the incremented iterator
         */
        iterator& operator++() {
            ptr = ptr->mNext;
            return *this;
        }

        /**
         * @brief Postfix increment
         * @return copy of the iterator before increment
         */
        iterator operator++(int) {
            iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        /**
         * @brief Prefix decrement
         * @return reference to the decremented iterator
         */
        iterator& operator--() {
            ptr = ptr->mPrev;
            return *this;
        }

        /**
         * @brief Postfix decrement
         * @return copy of the iterator before decrement
         */
        iterator operator--(int) {
            iterator tmp = *this;
            --(*this);
            return tmp;
        }

        /**
         * @brief Assignment operator
         * @param p The pointer to the node
         * @return reference to the assigned iterator
         */
        iterator& operator=(Node< value_type >* const& p) {
            ptr = p;
            return *this;
        }

        /**
         * @brief Returns an iterator after increased step steps
         * @param step The number of steps to increase
         * @return the resulting iterator
         */
        iterator operator+(const int& step) {
            iterator it = *this;
            if (step > 0) {
                for (int i = 0; i < step; ++i) ++it;
            }
            if (step < 0) {
                for (int i = 0; i < -step; ++i) --it;
            }
            return it;
        }

        /**
         * @brief Returns an iterator after decreased step steps
         * @param step The number of steps to decrease
         * @return the resulting iterator
         */
        iterator operator-(const int& step) {
            iterator it = *this;
            if (step > 0) {
                for (int i = 0; i < step; ++i) --it;
            }
            if (step < 0) {
                for (int i = 0; i < -step; ++i) ++it;
            }
            return it;
        }

        /**
         * @brief Checks if two iterators are equal
         * @param it The iterator to compare with
         * @return true if the iterators are equal
         */
        bool operator==(const iterator& it) const { return it.ptr == ptr; }

        /**
         * @brief Checks if two iterators are not equal
         * @param it The iterator to compare with
         * @return true if the iterators are not equal
         */
        bool operator!=(const iterator& it) const { return it.ptr != ptr; }

        /**
         * @brief Swaps the contents of the iterator with those of other
         * @param other iterator to exchange the contents with
         */
        void swap(iterator& other) { std::swap(this->ptr, other.ptr); }
    };

    /**
     * @brief The list const_iterator class
     * @tparam T The type of the elements
     */
    template< class T >
    class List< T >::const_iterator
    // : public std::iterator< std::bidirectional_iterator_tag, T,
    //                         std::ptrdiff_t, T*, T& >
    // deprecated since C++17
    {
        friend class List;

    private:
        const Node< T >* ptr;

    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;

        /**
         * @brief Construct a new const_iterator object
         *
         */
        const_iterator() : ptr{nullptr} {}

        /**
         * @brief Construct a new const_iterator object
         *
         * @param p The pointer to the node
         */
        const_iterator(Node< value_type >* const& p) : ptr(p) {}

        /**
         * @brief Construct a new const_iterator object
         *
         * @param other The iterator to copy
         */
        const_iterator(const iterator& other) : ptr(other.ptr) {}

        /**
         * @brief Construct a new const_iterator object
         *
         * @param other The const_iterator to copy
         */
        const_iterator(const const_iterator& other) : ptr(other.ptr) {}

        /**
         * @brief Returns a reference to the object pointed to by the iterator
         * @return reference to the object pointed to by the iterator
         */
        reference operator*() const {
            reference value = ptr->mValue;
            return value;
        }

        /**
         * @brief Returns a pointer to the object pointed to by the iterator
         * @return pointer to the object pointed to by the iterator
         */
        pointer operator->() const { return std::addressof(operator*()); }

        /**
         * @brief Prefix increment
         * @return reference to the incremented iterator
         */
        const_iterator& operator++() {
            ptr = ptr->mNext;
            return *this;
        }

        /**
         * @brief Postfix increment
         * @return copy of the iterator before increment
         */
        const_iterator operator++(int) {
            const_iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        /**
         * @brief Prefix decrement
         * @return reference to the decremented iterator
         */
        const_iterator& operator--() {
            ptr = ptr->mPrev;
            return *this;
        }

        /**
         * @brief Postfix decrement
         * @return copy of the iterator before decrement
         */
        const_iterator operator--(int) {
            const_iterator tmp = *this;
            --(*this);
            return tmp;
        }

        /**
         * @brief Returns an iterator after increased step steps
         * @param step The number of steps to increase
         * @return the resulting iterator
         */
        const_iterator operator+(const int& step) {
            const_iterator it = *this;
            if (step > 0) {
                for (int i = 0; i < step; ++i) ++it;
            }
            if (step < 0) {
                for (int i = 0; i < -step; ++i) --it;
            }
            return it;
        }

        /**
         * @brief Returns an iterator after decreased step steps
         * @param step The number of steps to decrease
         * @return the resulting iterator
         */
        const_iterator operator-(const int& step) {
            const_iterator it = *this;
            if (step > 0) {
                for (int i = 0; i < step; ++i) --it;
            }
            if (step < 0) {
                for (int i = 0; i < -step; ++i) ++it;
            }
            return it;
        }

        /**
         * @brief Checks if the content of the iterator is equal to other
         * @param other The pointer to the node to compare with
         * @return true if the content of the iterator is equal to the content
         * pointed by other
         */
        const_iterator& operator=(Node< value_type >* const& p) {
            ptr = p;
            return *this;
        }

        /**
         * @brief Checks if two iterators are equal
         * @param it The iterator to compare with
         * @return true if the iterators are equal
         */
        const_iterator& operator=(const iterator& other) {
            ptr = other.ptr;
            return *this;
        }

        /**
         * @brief Checks if two iterators are equal
         * @param it The iterator to compare with
         * @return true if the iterators are equal
         */
        bool operator==(const const_iterator& it) const {
            return it.ptr == ptr;
        }

        /**
         * @brief Checks if two iterators are not equal
         * @param it The iterator to compare with
         * @return true if the iterators are not equal
         */
        bool operator!=(const const_iterator& it) const {
            return it.ptr != ptr;
        }

        /**
         * @brief Swaps the contents of the iterator with those of other
         * @param other iterator to exchange the contents with
         */
        void swap(const_iterator& other) { std::swap(this->ptr, other.ptr); }
    };
};      // namespace Core

#endif  // CORE_LIST_HPP