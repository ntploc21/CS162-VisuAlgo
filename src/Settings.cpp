#include "Settings.hpp"

#include <cassert>
#include <fstream>
#include <iomanip>
#include <iostream>

#include "Global.hpp"
#include "raylib.h"

Settings& Settings::getInstance() {
    static Settings settings;
    return settings;
}

void Settings::LoadDefaultColors() {
    /* Background */
    mColors[ColorTheme::Background] = RAYWHITE;
    /* GUI */
    /* Logo color */
    mColors[ColorTheme::Logo1FirstPart] = WHITE;
    mColors[ColorTheme::Logo1SecondPart] = ORANGE;
    mColors[ColorTheme::Logo2FirstPart] = BLACK;
    mColors[ColorTheme::Logo2SecondPart] = ORANGE;

    /* Navigation bar */
    mColors[ColorTheme::NavigationBar_SelectedTitle] = WHITE;
    mColors[ColorTheme::NavigationBar_UnselectedTitle] =
        Color{170, 170, 170, 255};
    mColors[ColorTheme::NavigationBar_Background] = BLACK;

    /* Card (title) */
    mColors[ColorTheme::Card_Background] = LIGHTGRAY;
    mColors[ColorTheme::Card_Text] = BLACK;

    /* Action list */
    mColors[ColorTheme::ActionList_Text] = WHITE;
    mColors[ColorTheme::ActionList_Background] = Color{82, 188, 105, 255};
    mColors[ColorTheme::ActionList_HoverBackground] = BLACK;

    /* Code highlighter */
    mColors[ColorTheme::CodeHighlighter_Background] = Color{46, 187, 209, 255};
    mColors[ColorTheme::ActionDescription_Background] =
        Color{255, 133, 39, 255};

    /* Visualizer */
    /* Label */
    mColors[ColorTheme::Visualizer_Label] = RED;
    /* Node */
    /* Default */
    mColors[ColorTheme::Visualizer_Node_Default_Outline1] = BLACK;
    mColors[ColorTheme::Visualizer_Node_Default_Outline2] = BLACK;
    mColors[ColorTheme::Visualizer_Node_Default_Background1] = WHITE;
    mColors[ColorTheme::Visualizer_Node_Default_Background2] = WHITE;
    mColors[ColorTheme::Visualizer_Node_Default_Text1] = BLACK;
    mColors[ColorTheme::Visualizer_Node_Default_Text2] = BLACK;

    /* Active */
    mColors[ColorTheme::Visualizer_Node_Active_Outline1] = BLACK;
    mColors[ColorTheme::Visualizer_Node_Active_Outline2] =
        Color{255, 138, 39, 255};
    mColors[ColorTheme::Visualizer_Node_Active_Background1] = WHITE;
    mColors[ColorTheme::Visualizer_Node_Active_Background2] =
        Color{255, 138, 39, 255};
    mColors[ColorTheme::Visualizer_Node_Active_Text1] = BLACK;
    mColors[ColorTheme::Visualizer_Node_Active_Text2] = WHITE;

    /* Active Blue */
    mColors[ColorTheme::Visualizer_Node_ActiveBlue_Outline1] = BLACK;
    mColors[ColorTheme::Visualizer_Node_ActiveBlue_Outline2] =
        Color{46, 187, 209, 255};
    mColors[ColorTheme::Visualizer_Node_ActiveBlue_Background1] = WHITE;
    mColors[ColorTheme::Visualizer_Node_ActiveBlue_Background2] =
        Color{46, 187, 209, 255};
    mColors[ColorTheme::Visualizer_Node_ActiveBlue_Text1] = BLACK;
    mColors[ColorTheme::Visualizer_Node_ActiveBlue_Text2] = WHITE;

    /* Active Green */
    mColors[ColorTheme::Visualizer_Node_ActiveGreen_Outline1] = BLACK;
    mColors[ColorTheme::Visualizer_Node_ActiveGreen_Outline2] =
        Color{82, 188, 105, 255};
    mColors[ColorTheme::Visualizer_Node_ActiveGreen_Background1] = WHITE;
    mColors[ColorTheme::Visualizer_Node_ActiveGreen_Background2] =
        Color{82, 188, 105, 255};
    mColors[ColorTheme::Visualizer_Node_ActiveGreen_Text1] = BLACK;
    mColors[ColorTheme::Visualizer_Node_ActiveGreen_Text2] = WHITE;

    /* Iterated */
    mColors[ColorTheme::Visualizer_Node_Iterated_Outline1] =
        Color{255, 138, 39, 255};
    mColors[ColorTheme::Visualizer_Node_Iterated_Outline2] =
        Color{255, 138, 39, 255};
    mColors[ColorTheme::Visualizer_Node_Iterated_Background1] = WHITE;
    mColors[ColorTheme::Visualizer_Node_Iterated_Background2] =
        Color{255, 138, 39, 255};
    mColors[ColorTheme::Visualizer_Node_Iterated_Text1] = WHITE;
    mColors[ColorTheme::Visualizer_Node_Iterated_Text2] =
        Color{255, 138, 39, 255};

    /* Active Red */
    mColors[ColorTheme::Visualizer_Node_ActiveRed_Outline1] = BLACK;
    mColors[ColorTheme::Visualizer_Node_ActiveRed_Outline2] =
        Color{217, 81, 60, 255};
    mColors[ColorTheme::Visualizer_Node_ActiveRed_Background1] = WHITE;
    mColors[ColorTheme::Visualizer_Node_ActiveRed_Background2] =
        Color{217, 81, 60, 255};
    mColors[ColorTheme::Visualizer_Node_ActiveRed_Text1] = BLACK;
    mColors[ColorTheme::Visualizer_Node_ActiveRed_Text2] = WHITE;

    /* Arrow */
    mColors[ColorTheme::Visualizer_Arrow_Default] = BLACK;
    mColors[ColorTheme::Visualizer_Arrow_Active] = Color{255, 138, 39, 255};
}

void Settings::SaveToFile(const std::string& path) {}

void Settings::LoadFromFile(const std::string& path) {}

Settings::~Settings() { SaveToFile(global::defaultColorPath); }

Color& Settings::getColor(ColorTheme::ID id) {
    auto found = mColors.find(id);
    assert(found != mColors.end());
    return found->second;
}

Color Settings::getColor(ColorTheme::ID id) const {
    auto found = mColors.find(id);
    assert(found != mColors.end());
    return found->second;
}