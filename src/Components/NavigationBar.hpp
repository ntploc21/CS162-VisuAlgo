#ifndef COMPONENTS_NAVIGATIONBAR_HPP
#define COMPONENTS_NAVIGATIONBAR_HPP

#include <functional>

#include "../SceneNode.hpp"
#include "FontHolder.hpp"
#include "raygui.h"

class NavigationBar : public SceneNode {
public:
    NavigationBar(FontHolder* fonts);
    NavigationBar();
    ~NavigationBar();
    void DrawCurrent();

    void SetHomepageLink(std::function< void() > homepageLink);
    void SetSettings(std::function< void() > settingsLink);

    void SetCategory(std::string category);

private:
    bool DrawLogo();
    FontHolder* fonts;
    std::string currentCategory;

    bool DrawSettings();

private:
    std::function< void() > toHomepage;
    std::function< void() > toSettings;
};

#endif  // COMPONENTS_NAVIGATIONBAR_HPP
