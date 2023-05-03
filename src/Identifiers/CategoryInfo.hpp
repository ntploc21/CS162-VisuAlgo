#ifndef CATEGORYINFO_HPP
#define CATEGORYINFO_HPP

#include <cassert>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "CategoryIdentifiers.hpp"
#include "DSIdentifiers.hpp"
#include "NonCopyable.hpp"

/**
 * @brief The category info class that is used to store information about the
 * categories.
 * @details The category info class is used to store information about the
 * categories. Also, this class is using the flyweight pattern to store the
 * information about the categories.
 * @see Category::ID
 * @see DataStructures::ID
 * @see NonCopyable
 * @see Info
 */
class CategoryInfo : private NonCopyable< CategoryInfo > {
private:
    /**
     * @brief The info struct that is used to store information about the
     * categories.
     * @details The info struct is used to store information about the
     * categories. This struct is used to store the category ID, the category
     * name, and the data structures that are in the category.
     */
    struct Info {
        /**
         * @brief The constructor.
         * @details The constructor that is used to initialize the category info
         * struct.
         * @param categoryID The category ID.
         * @param mDS The data structures that are in the category.
         * @param name The category name.
         */
        Info(Category::ID categoryID, std::vector< DataStructures::ID > mDS,
             std::string name);

        /**
         * @brief The category ID.
         * @see Category::ID
         */
        Category::ID categoryID;

        /**
         * @brief The category name.
         */
        std::string categoryName;

        /**
         * @brief The data structures that are in the category.
         * @see DataStructures::ID
         */
        std::vector< DataStructures::ID > mDS;
    };

    /**
     * @brief The factory map that is used to store the factories.
     * @details The factory map is used to store the factories. The factories
     * are used to create the data structures.
     */
    std::map< Category::ID, Info > mFactories;

public:
    /**
     * @brief This function is used to register a category.
     * @details This function is used to register a category.
     * @see Category::ID
     * @see Info
     * @param id The category ID.
     * @param info The information about the category.
     */
    void Register(Category::ID, Info info);

    /**
     * @brief This function is used to retrieve the information about a
     * category.
     * @details This function is used to retrieve the information about a
     * category.
     * @see Category::ID
     * @see Info
     * @param id The category ID.
     * @return The information about the category.
     */
    const Info& Get(Category::ID id) const;
};

#endif  // CATEGORYINFO_HPP