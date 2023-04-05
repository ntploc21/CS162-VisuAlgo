#ifndef COMPONENTS_NAVIGATIONBAR_HPP
#define COMPONENTS_NAVIGATIONBAR_HPP

#include <functional>

#include "../SceneNode.hpp"
#include "DSIdentifiers.hpp"
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

    void InsertTitle(DataStructures::ID titleID, States::ID stateID,
                     std::string abbrTitle, std::string titleName);
    void SetActiveTitle(DataStructures::ID title);
    void ClearTitle();

private:
    bool DrawSettings();
    bool DrawLogo();
    States::ID DrawTitles();

private:
    struct TitleInfo {
        States::ID stateID;
        std::string abbrTitle;
        std::string titleName;
    };

    FontHolder* fonts;
    std::string currentCategory;
    std::map< DataStructures::ID, TitleInfo > mTitles;
    DataStructures::ID activeTitle;

private:
    std::function< void(States::ID) > toLink;
    States::ID homepageID;
    States::ID settingsID;
};

#endif  // COMPONENTS_NAVIGATIONBAR_HPP
