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
    template< typename T >
    class List {
    public:
        class iterator;
        class const_iterator;

    private:
        iterator mBegin, mEnd;
        std::size_t mSize;

        void reset() {
            this->mBegin = this->mEnd;
            this->mEnd.ptr->mPrev = nullptr;
            this->mSize = 0;
        }

        void insert_previous(const iterator& it, const iterator& it_prev) {
            Node< T >* node = it.ptr;
            Node< T >* node_prev = it_prev.ptr;

            node_prev->mNext = node;
            node_prev->mPrev = node->mPrev;
            node->mPrev = node_prev;
            if (node_prev->mPrev != nullptr) {
                node_prev->mPrev->mNext = node_prev;
            }

            if (it == this->begin()) {
                this->mBegin = node_prev;
            }

            ++this->mSize;
        }

        /* @brief Move nodes from a list of range [`first`, `last`) to before
         * `it` */
        /* @brief Return iterator pointing to the first inserted element, or
         * `it` if `first` == `last`. */
        /* @exception: undefined behaviour: null pointer reference */
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
        List() : mSize(0) { this->mBegin = this->mEnd = new Node< T >(); }
        List(std::initializer_list< T > list) : mSize(0) {
            this->mBegin = this->mEnd = new Node< T >();
            for (const auto& element : list) {
                this->push_back(element);
            }
        }

        /* @brief Copy constructor */
        List(const List< T >& list) : mSize(0) {
            this->mBegin = this->mEnd = new Node< T >();
            for (const auto& element : list) {
                this->push_back(element);
            }
        }

        /* @brief Move constructor */
        List(List< T >&& list) : mSize(0) {
            this->mBegin = this->mEnd = new Node< T >();
            move_previous(this->end(), list.begin(), list.end());
            list.reset();
        }

        List< T >& operator=(std::initializer_list< T > list) {
            assign(list);
            return *this;
        }
        List< T >& operator=(const List< T >& list) {
            if (this == &list) return *this;
            this->assign(list.begin(), list.end());
            return *this;
        }
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
        [[nodiscard]] bool empty() const { return this->size() == 0; }
        [[nodiscard]] std::size_t size() const { return this->mSize; }

    protected:
        /* Exception(s): undefined behavior: null pointer dereference */
        T& front() { return *this->begin(); }
        const T& front() const { return *this->begin(); }
        /* Exception(s): undefined */
        T& back() {
            auto it = this->end();
            --it;
            return *it;
        }
        const T& back() const {
            auto it = this->end();
            --it;
            return *it;
        }

        T& operator[](std::size_t index) { return *this->get_iterator(index); }
        const T& operator[](std::size_t index) const {
            return *this->get_iterator(index);
        }

        T& at(std::size_t index) { return (*this)[index]; }

        const T& at(std::size_t index) const { return (*this)[index]; }

        void push_front(const T& value) {
            Node< T >* node = new Node< T >(value);
            this->insert_previous(this->begin(), iterator(node));
        }

        void push_back(const T& value) {
            Node< T >* node = new Node< T >(value);
            this->insert_previous(this->end(), iterator(node));
        }

        void pop_front() {
            auto it = this->begin();
            this->remove(it);
        }

        void pop_back() {
            auto it = --this->end();
            this->remove(it);
        }

    protected:
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

        /*
            Return resulting size
        */
        int remove(const T& value, const iterator& begin, const iterator& end) {
            return this->remove_if(
                [&value](const T& element) { return element == value; }, begin,
                end);
        }

        /*
            Return resulting size
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

        void resize(std::size_t count) {
            while (this->size() < count) this->push_back(T());

            while (this->size() > count) this->pop_back();
        }

        void resize(std::size_t count, const T& value) {
            while (this->size() < count) this->push_back(value);

            while (this->size() > count) this->pop_back();
        }

        void assign(std::size_t count, const T& value) {
            this->clear();
            this->resize(count, value);
        }

        /*
            @brief Assigns new contents to the list, replacing its current
           content with [`first`, `last`)
            @note [`first`, `last`) must not be part of this list, and `last`
           must be reachable by `first`
        */
        void assign(const const_iterator& begin, const const_iterator& end) {
            this->resize(std::distance(begin, end));

            auto itOther = begin;
            for (auto it = this->begin(); it != this->end(); ++it, ++itOther) {
                *it = *itOther;
            }
        }

        /*
            @brief Assigns new contents to the list, replacing its current
           content
        */
        void assign(std::initializer_list< T > list) {
            this->resize(list.size());

            auto itOther = list.begin();
            for (auto it = this->begin(); it != this->end(); ++it, ++itOther) {
                (*it) = (*itOther);
            }
        }

        /*
            @brief Eliminates all except the first element from every
           consecutive group of equivalent elements from the range [`first`,
           `last`) and returns a past-the-end iterator for the new logical end
           of the range.
            @return the resulting size
        */
        std::size_t unique() {
            iterator last = std::unique(this->begin(), this->end());
            this->resize(std::distance(this->begin(), last));

            return this->size();
        }

        std::size_t unique(
            std::function< bool(const T&, const T&) > predicate) {
            iterator last = std::unique(this->begin(), this->end(), predicate);
            this->resize(std::distance(this->begin(), last));

            return this->size();
        }

        /*
            @brief Reverses the order of the elements in the list
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
        void swap(List< T >& other) {
            std::swap(this->mBegin, other.mBegin);
            std::swap(this->mEnd, other.mEnd);
            std::swap(this->mSize, other.mSize);
        }

    public:
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

        iterator() : ptr{nullptr} {}
        iterator(Node< value_type >* const& p) : ptr(p) {}
        reference operator*() const {
            reference value = ptr->mValue;
            return value;
        }

        pointer operator->() const { return std::addressof(operator*()); }
        /* Prefix increment */
        iterator& operator++() {
            ptr = ptr->mNext;
            return *this;
        }
        /* Postfix increment */
        iterator operator++(int) {
            iterator tmp = *this;
            ++(*this);
            return tmp;
        }
        /* Prefix decrement */
        iterator& operator--() {
            ptr = ptr->mPrev;
            return *this;
        }
        /* Postfix decrement */
        iterator operator--(int) {
            iterator tmp = *this;
            --(*this);
            return tmp;
        }
        iterator& operator=(Node< value_type >* const& p) {
            ptr = p;
            return *this;
        }
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
        bool operator==(const iterator& it) const { return it.ptr == ptr; }
        bool operator!=(const iterator& it) const { return it.ptr != ptr; }
        void swap(iterator& other) { std::swap(this->ptr, other.ptr); }
    };

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

        const_iterator() : ptr{nullptr} {}
        const_iterator(Node< value_type >* const& p) : ptr(p) {}
        const_iterator(const iterator& other) : ptr(other.ptr) {}
        const_iterator(const const_iterator& other) : ptr(other.ptr) {}
        reference operator*() const {
            reference value = ptr->mValue;
            return value;
        }

        pointer operator->() const { return std::addressof(operator*()); }

        /* Prefix increment */
        const_iterator& operator++() {
            ptr = ptr->mNext;
            return *this;
        }

        /* Postfix increment */
        const_iterator operator++(int) {
            const_iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        /* Prefix decrement */
        const_iterator& operator--() {
            ptr = ptr->prev;
            return *this;
        }

        /* Postfix decrement */
        const_iterator operator--(int) {
            const_iterator tmp = *this;
            --(*this);
            return tmp;
        }
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
        const_iterator& operator=(Node< value_type >* const& p) {
            ptr = p;
            return *this;
        }
        const_iterator& operator=(const iterator& other) {
            ptr = other.ptr;
            return *this;
        }
        bool operator==(const const_iterator& it) const {
            return it.ptr == ptr;
        }
        bool operator!=(const const_iterator& it) const {
            return it.ptr != ptr;
        }
        void swap(const_iterator& other) { std::swap(this->ptr, other.ptr); }
    };
};  // namespace Core

#endif  // CORE_LIST_HPP