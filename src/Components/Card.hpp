#ifndef COMPONENTS_CARD_HPP
#define COMPONENTS_CARD_HPP

#include <functional>

#include "../SceneNode.hpp"
#include "FontHolder.hpp"
#include "StateIdentifiers.hpp"
#include "raygui.h"

/* Little note
    - Card height: 250
    - Card width: 200
    - Title: 24px
    - Image: 160x250

*/

class Card : public SceneNode {
public:
    Card(int cornerX, int cornerY, std::string text, Texture thumbnail,
         FontHolder* fonts);
    Card();
    ~Card();
    void DrawCurrent();

    void SetLink(std::function< void(States::ID) > link);
    void SetStateID(States::ID stateID);

    void SetText(std::string text);

private:
    bool DrawImage();
    bool DrawTitle();

private:
    int cornerX, cornerY;
    FontHolder* fonts;
    Texture thumbnail;
    std::string title;
    std::function< void(States::ID) > toLink;
    States::ID stateID;
};

#endif  // COMPONENTS_CARD_HPP