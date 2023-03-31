#ifndef NONCOPYABLE_HPP
#define NONCOPYABLE_HPP

template< class T >
class NonCopyable {
public:
    NonCopyable(const NonCopyable &) = delete;
    T &operator=(const T &) = delete;

protected:
    NonCopyable() = default;
    ~NonCopyable() = default;  // Protected non-virtual destructor
};

#endif  // NONCOPYABLE_HPP