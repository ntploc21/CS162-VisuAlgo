#ifndef STATES_HOMEPAGESTATE_HPP
#define STATES_HOMEPAGESTATE_HPP

#include "../State.hpp"
#include "Components/Card.hpp"

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
    std::map< States::ID, std::unique_ptr< Card > > mCards;
};

#endif  // STATES_HOMEPAGESTATE_HPP