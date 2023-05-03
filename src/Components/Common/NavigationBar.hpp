#ifndef COMPONENTS_NAVIGATIONBAR_HPP
#define COMPONENTS_NAVIGATIONBAR_HPP

#include <functional>

#include "Component.hpp"
#include "FontHolder.hpp"
#include "Identifiers/DSIdentifiers.hpp"
#include "Identifiers/StateIdentifiers.hpp"
#include "raygui.h"

namespace GUIComponent {
    /**
     * @brief The navigation bar class that is used to represent a navigation
     * bar in the GUI.
     * @details The navigation bar is used to navigate between different pages
     * in the application. Also, it have a `switch theme` button that is used to
     * switch between different themes.
     */
    class NavigationBar : public GUI::Component {
    public:
        NavigationBar(FontHolder* fonts);
        NavigationBar();
        ~NavigationBar();

        void SetHomepageID(States::ID id);
        void SetDirectLink(std::function< void(States::ID) > link);

        void SetCategory(std::string category);

        void InsertTitle(DataStructures::ID titleID, States::ID stateID,
                         std::string abbrTitle, std::string titleName);
        void SetActiveTitle(DataStructures::ID title);
        void ClearTitle();

        void SetVisableTitle(bool visible);

    public:
        bool isSelectable() const;
        void Draw(Vector2 base = (Vector2){0, 0});

    private:
        bool DrawSwitchTheme();
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
        States::ID homepageID;

    private:
        std::map< std::string, Rectangle > hoverBounds;
        bool isHover;
    };
};      // namespace GUIComponent

#endif  // COMPONENTS_NAVIGATIONBAR_HPP
