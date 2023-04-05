#ifndef COMPONENTS_NAVIGATIONBAR_HPP
#define COMPONENTS_NAVIGATIONBAR_HPP

#include <functional>

#include "../SceneNode.hpp"
#include "FontHolder.hpp"
#include "StateIdentifiers.hpp"
#include "raygui.h"

class NavigationBar : public SceneNode {
public:
    NavigationBar(FontHolder* fonts);
    NavigationBar();
    ~NavigationBar();
    void DrawCurrent();

    void SetHomepageID(States::ID id);
    void SetSettingsID(States::ID id);
    void SetDirectLink(std::function< void(States::ID) > link);

    void SetCategory(std::string category);

    void InsertTitle(std::string title, States::ID stateID);
    void ClearTitle();

private:
    bool DrawLogo();
    FontHolder* fonts;
    std::string currentCategory;

    bool DrawSettings();

    std::map< std::string, States::ID > mTitles;

private:
    std::function< void(States::ID) > toLink;
    States::ID homepageID;
    States::ID settingsID;
};

#endif  // COMPONENTS_NAVIGATIONBAR_HPP
