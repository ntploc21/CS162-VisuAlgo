#ifndef COMPONENTS_CARD_HPP
#define COMPONENTS_CARD_HPP

#include <functional>

#include "../Component.hpp"
#include "../FontHolder.hpp"
#include "../Identifiers/StateIdentifiers.hpp"
#include "raygui.h"

/* Little note
    - Card height: 250
    - Card width: 200
    - Title: 24px
    - Image: 160x250

*/

class Card : public GUI::Component {
public:
    Card(std::string text, Texture thumbnail, FontHolder* fonts);
    Card();
    ~Card();
    void SetLink(std::function< void(States::ID) > link);
    void SetStateID(States::ID stateID);

    void SetText(std::string text);

public:
    bool isSelectable() const;
    void Draw(Vector2 base = (Vector2){0, 0});

private:
    bool DrawImage(Vector2 base);
    bool DrawTitle(Vector2 base);

private:
    FontHolder* fonts;
    Texture thumbnail;
    std::string title;
    std::function< void(States::ID) > toLink;
    States::ID stateID;

private:
    std::map< std::string, Rectangle > hoverBounds;
    bool isHover;
};

#endif  // COMPONENTS_CARD_HPP