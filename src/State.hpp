#ifndef STATE_HPP
#define STATE_HPP

#include <memory>

#include "Components/Common/NavigationBar.hpp"
#include "FontHolder.hpp"
#include "Identifiers/StateIdentifiers.hpp"
#include "TextureHolder.hpp"

// Categories and Data Structures identifiers
#include "Identifiers/CategoryInfo.hpp"
#include "Identifiers/DSInfo.hpp"
#include "NonCopyable.hpp"

namespace State {
    /**
     * @brief Forward declaration of the StateStack class.
     */
    class StateStack;

    /**
     * @brief The base state class that is used to represent a state/scene of
     * the application.
     */
    class State : private NonCopyable< State > {
    public:
        /**
         * @brief A unique pointer to the state object.
         */
        typedef std::unique_ptr< State > Ptr;

        /**
         * @brief The context that is used to share the resources (fonts,
         * textures, ...) between states (scenes).
         */
        struct Context {
            Context();
            Context(FontHolder* fonts, TextureHolder* textures,
                    CategoryInfo* categories, DSInfo* dsInfo);
            FontHolder* fonts;
            TextureHolder* textures;
            CategoryInfo* categories;
            DSInfo* dsInfo;
        };

    public:
        /**
         * @brief Construct a new State object
         * @param stack The state stack that is used to store the states
         * (scenes) of the application and support the navigation between states
         * (scenes).
         * @param context The context that is used to share the resources
         * (fonts, textures, ...) between states (scenes).
         */
        State(StateStack& stack, Context context);

        /**
         * @brief Destroy the State object
         */
        virtual ~State();

        /**
         * @brief Draw the state/scene
         * @note This function is pure virtual and must be implemented by the
         * derived class.
         */
        virtual void Draw() = 0;

        /**
         * @brief Update the the components of the state/scene
         * @param dt The time interval between the previous and the new frame
         * @return true (always)
         * @note This function is pure virtual and must be implemented by the
         * derived class.
         */
        virtual bool Update(float dt) = 0;

    protected:
        /**
         * @brief Request the state stack to push a new state/scene
         * @param stateID The ID of the state/scene that will be pushed
         * @see StateStack::PushState
         */
        void RequestStackPush(States::ID stateID);

        /**
         * @brief Request the state stack to pop the current state/scene
         * @see StateStack::PopState
         */
        void RequestStackPop();

        /**
         * @brief Request the state stack to clear all the states/scenes
         * @see StateStack::ClearStates
         */
        void RequestStackClear();

        /**
         * @brief Get the context that is used to share the resources (fonts,
         * textures, ...) between states (scenes).
         * @return The context that is used to share the resources (fonts,
         * textures, ...) between states (scenes).
         * @see Context
         */
        Context GetContext() const;

        /**
         * @brief Initialize the navigation bar as a component of the
         * state/scene
         * @see GUIComponent::NavigationBar
         */
        void InitNavigationBar();

    private:
        /**
         * @brief The state stack that is used to store the states (scenes) of
         * the application and support the navigation between states (scenes).
         */
        StateStack* mStack;

        /**
         * @brief The context that is used to share the resources (fonts,
         * textures, ...) between states (scenes).
         */
        Context mContext;

    protected:
        GUIComponent::NavigationBar navigation;
    };
};      // namespace State

#endif  // STATE_HPP