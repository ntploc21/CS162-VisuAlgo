#ifndef COMPONENTS_NAVIGATIONBAR_HPP
#define COMPONENTS_NAVIGATIONBAR_HPP

#include "../SceneNode.hpp"

class NavigationBar : public SceneNode {
public:
    NavigationBar(int x = 0, int y = 0);
    ~NavigationBar();
    void DrawCurrent();

    bool MoveToSettings();

private:
    int posX, posY;

    bool move = false;
};

#endif  // COMPONENTS_NAVIGATIONBAR_HPP
