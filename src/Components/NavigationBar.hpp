#ifndef COMPONENTS_NAVIGATIONBAR_HPP
#define COMPONENTS_NAVIGATIONBAR_HPP

#include <functional>

#include "../Identifiers/DSIdentifiers.hpp"
#include "../Identifiers/StateIdentifiers.hpp"
#include "../SceneNode.hpp"
#include "FontHolder.hpp"
#include "raygui.h"

class NavigationBar {
public:
    NavigationBar(FontHolder* fonts);
    NavigationBar();
    ~NavigationBar();
    void Draw();

    void SetHomepageID(States::ID id);
    void SetSettingsID(States::ID id);
    void SetDirectLink(std::function< void(States::ID) > link);
    void SetBackToPreviousLink(std::function< void() > link);

    void AtSettings(bool settings);

    void SetCategory(std::string category);

    void InsertTitle(DataStructures::ID titleID, States::ID stateID,
                     std::string abbrTitle, std::string titleName);
    void SetActiveTitle(DataStructures::ID title);
    void ClearTitle();

    void SetVisableTitle(bool visible);

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
    bool hasTitle;

private:
    std::function< void(States::ID) > toLink;
    std::function< void() > backToPrvState;
    States::ID homepageID;
    States::ID settingsID;
    bool atSettings;
};

#endif  // COMPONENTS_NAVIGATIONBAR_HPP
