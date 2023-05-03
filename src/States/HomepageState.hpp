#ifndef STATES_HOMEPAGESTATE_HPP
#define STATES_HOMEPAGESTATE_HPP

#include "Container.hpp"
// #include "../Core/Operations/Create/Create.hpp"
#include "Components/Common/Card.hpp"
#include "State.hpp"

namespace State {
    /**
     * @brief The homepage sceen
     * @details This class is used to display the homepage sceen of the
     * application.
     */
    class HomepageState : public State {
    private:
    public:
        /**
         * @brief Construct a new HomepageState object
         * @param stack The state stack that is used to store the states
         * (scenes) of the application and support the navigation between states
         * (scenes).
         * @param context The context that is used to share the resources
         * (fonts, textures, ...) between states (scenes).
         */
        HomepageState(StateStack& stack, Context context);

        /**
         * @brief Destroy the HomepageState scene
         */
        ~HomepageState();

        /**
         * @brief Draw the homepage scene
         */
        void Draw();

        /**
         * @brief Update the the components of the homepage scene
         * @param dt The time interval between the previous and the new frame
         * @return true (always)
         */
        bool Update(float dt);

    private:
        void DrawIntroduction();
        void InitCards();
        void CreateCard(States::ID stateID, std::string title,
                        Textures::ID textureID, int x, int y);

    private:
        GUI::Container mCards;
        bool hasInitializeCard;
    };
};  // namespace State

#endif  // STATES_HOMEPAGESTATE_HPP