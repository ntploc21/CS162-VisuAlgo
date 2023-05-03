#ifndef DSINFO_HPP
#define DSINFO_HPP

#include <cassert>
#include <map>
#include <memory>
#include <string>

#include "CategoryIdentifiers.hpp"
#include "DSIdentifiers.hpp"
#include "NonCopyable.hpp"
#include "ResourceIdentifiers.hpp"
#include "StateIdentifiers.hpp"

/**
 * @brief The data structure info class that is used to store information about
 * the data structures.
 * @details The data structure info class is used to store information about the
 * data structures. Also, this class is using the flyweight pattern to store the
 * information about the data structures.
 * @see DataStructures::ID
 * @see States::ID
 * @see Category::ID
 * @see Textures::ID
 * @see NonCopyable
 * @see Info
 * @see Register
 */
class DSInfo : private NonCopyable< DSInfo > {
private:
    /**
     * @brief The info struct that is used to store information about the data
     * structures.
     * @details The info struct is used to store information about the data
     * structures. This struct is used to store the data structure ID, the state
     * ID, the category ID, the thumbnail texture ID, the data structure name,
     * and the data structure abbreviation.
     */
    struct Info {
        /**
         * @brief The constructor.
         * @details The constructor that is used to initialize the data
         * structure info struct.
         * @param ID The data structure ID.
         * @param stateID The state ID.
         * @param categoryID The category ID.
         * @param thumbnail The thumbnail texture ID.
         * @param name The data structure name.
         * @param abbr The data structure abbreviation.
         */
        Info(DataStructures::ID ID, States::ID stateID, Category::ID categoryID,
             Textures::ID thumbnail, std::string name, std::string abbr);

        /**
         * @brief The data structure ID.
         * @see DataStructures::ID
         */
        DataStructures::ID ID;

        /**
         * @brief The state ID.
         * @see States::ID
         */
        States::ID stateID;

        /**
         * @brief The category ID.
         * @see Category::ID
         */
        Category::ID categoryID;

        /**
         * @brief The thumbnail texture ID.
         * @see Textures::ID
         */
        Textures::ID thumbnail;

        /**
         * @brief The data structure name.
         */
        std::string name;

        /**
         * @brief The data structure abbreviation.
         */
        std::string abbr;
    };

    /**
     * @brief The factory map that is used to store the factories.
     * @details The factory map is used to store the factories. The factories
     * are used to create the data structures.
     */
    std::map< DataStructures::ID, Info > mFactories;

public:
    /**
     * @brief This function is used to register the data structure info.
     * @details This function is used to register the data structure info.
     * @param id The data structure ID.
     * @param info The data structure info.
     */
    void Register(DataStructures::ID, Info info);

    /**
     * @brief This function is used to retrieve the data structure info.
     * @details This function is used to retrieve the data structure info.
     * @param id The data structure ID.
     * @return The data structure info.
     */
    Info Get(DataStructures::ID id) const;
};

#endif  // DSINFO_HPP