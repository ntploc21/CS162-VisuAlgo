#ifndef COMPONENTS_NAVIGATIONBAR_HPP
#define COMPONENTS_NAVIGATIONBAR_HPP

#include "../SceneNode.hpp"
#include "raygui.h"

class NavigationBar : public SceneNode {
public:
    NavigationBar(Font *logoFont);
    NavigationBar();
    ~NavigationBar();
    void DrawCurrent();

    // bool ToTheHomepage();

private:
    int posX, posY;

    // bool toTheHomepage = false;
    Font *logoFont;
};

#endif  // COMPONENTS_NAVIGATIONBAR_HPP
