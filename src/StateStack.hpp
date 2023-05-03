#ifndef STATESTACK_HPP
#define STATESTACK_HPP

#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <vector>

#include "Core/Deque.hpp"
#include "NonCopyable.hpp"
#include "State.hpp"

namespace State {
    /**
     * @brief The state stack that is used to store the states (scenes) of the
     * application and support the navigation between states (scenes).
     */
    class StateStack : private NonCopyable< StateStack > {
    public:
        /**
         * @brief The action that is used to modify the state stack
         * @details The action can be one of the following:
         * - Push: Add a new state to the top of the stack (or equivalent to
         * switching to a new state/scene)
         * - Pop: Remove the top state from the stack (or equivalent to
         * returning to the previous state/scene, or exiting the application if
         * the stack is empty)
         * - Clear: Remove all the states from the stack (or equivalent to
         * clearing the stack)
         */
        enum class Action {
            Push,
            Pop,
            Clear,
        };

    public:
        /**
         * @brief Construct a new StateStack object
         * @param context The context that is used to share the resources
         * (fonts, textures, ...) between states (scenes).
         */
        explicit StateStack(State::Context context);

        /**
         * @brief Register a new state/scene to the state stack
         * @tparam T The type of the state/scene
         * @param stateID The ID of the state/scene
         */
        template< class T >
        void RegisterState(States::ID stateID);

        /**
         * @brief Update the the components of the current state/scene
         * @param dt The time interval between the previous and the new frame
         */
        void Update(float dt);

        /**
         * @brief Draw the current state/scene
         */
        void Draw();

        /**
         * @brief Push a new state/scene to the top of the stack
         * @param stateID The ID of the state/scene
         */
        void PushState(States::ID stateID);

        /**
         * @brief Pop the top state/scene from the stack
         * @details If the stack is empty, the application will be closed.
         */
        void PopState();

        /**
         * @brief Clear all the states/scenes from the stack, this is equivalent
         * to closing the application
         */
        void ClearStates();

        /**
         * @brief Check if the state stack is empty
         * @return true if the state stack is empty, false otherwise
         */
        bool IsEmpty() const;

    private:
        /**
         * @brief Create a new state/scene
         * @param stateID The ID of the state/scene
         * @return A pointer to the new state/scene
         * @exception std::runtime_error Thrown if the state/scene ID is not
         * registered
         */
        State::Ptr createState(States::ID stateID);

        /**
         * @brief Apply the pending changes to the state stack
         */
        void ApplyPendingChanges();

    private:
        /**
         * @brief The pending changes that are applied to the state stack
         * @details The pending changes can be one of the following:
         * - Push: Add a new state to the top of the stack (or equivalent to
         * switching to a new state/scene)
         * - Pop: Remove the top state from the stack (or equivalent to
         * returning to the previous state/scene, or exiting the application if
         * the stack is empty)
         * - Clear: Remove all the states from the stack (or equivalent to
         * clearing the stack)
         * @see Action
         * @see StateStack::ApplyPendingChanges
         */
        struct PendingChange {
            explicit PendingChange(Action action,
                                   States::ID stateID = States::None);
            PendingChange();
            Action action;
            States::ID stateID;
        };

    private:
        /**
         * @brief The stack that is used to store the states/scenes
         */
        std::vector< State::Ptr > mStack;

        /**
         * @brief The pending changes that are applied to the state stack
         * @see PendingChange
         */
        Core::Deque< PendingChange > mPendingList;

        /**
         * @brief The context that is used to share the resources
         * (fonts, textures, ...) between states (scenes).
         */
        State::Context mContext;

        /**
         * @brief The factories that are used to create the states/scenes
         */
        std::map< States::ID, std::function< State::Ptr() > > mFactories;
    };
};  // namespace State

template< class T >
void State::StateStack::RegisterState(States::ID stateID) {
    mFactories[stateID] = [this]() {
        return State::Ptr(new T(*this, mContext));
    };
}

#endif  // STATESTACK_HPP