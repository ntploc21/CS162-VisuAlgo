#ifndef STATES_HOMEPAGESTATE_HPP
#define STATES_HOMEPAGESTATE_HPP

#include "Container.hpp"
// #include "../Core/Operations/Create/Create.hpp"
#include "Components/Common/Card.hpp"
#include "State.hpp"

namespace State {
    class HomepageState : public State {
    private:
    public:
        HomepageState(StateStack& stack, Context context);
        ~HomepageState();
        void Draw();
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
};      // namespace State

#endif  // STATES_HOMEPAGESTATE_HPP