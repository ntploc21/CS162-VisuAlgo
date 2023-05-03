#ifndef NONCOPYABLE_HPP
#define NONCOPYABLE_HPP

/**
 * @brief The self-explanatory non-copyable class.
 * @details This class is used to make a class non-copyable.
 * @tparam T The class that is going to be made non-copyable.
 */
template< class T >
class NonCopyable {
public:
    /**
     * @brief The copy constructor is deleted.
     * @details The copy constructor is deleted to make the class non-copyable.
     */
    NonCopyable(const NonCopyable &) = delete;

    /**
     * @brief The assignment operator is deleted.
     * @details The assignment operator is deleted to make the class
     * non-copyable.
     */
    T &operator=(const T &) = delete;

protected:
    /**
     * @brief Construct a new NonCopyable object.
     * @details This constructor is used to construct a new NonCopyable object.
     */
    NonCopyable() = default;

    /**
     * @brief Destroy the NonCopyable object.
     * @details This destructor is used to destroy the NonCopyable object.
     */
    ~NonCopyable() = default;  // Protected non-virtual destructor
};

#endif  // NONCOPYABLE_HPP