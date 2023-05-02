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

void Settings::LoadDarkColors() {
    /* Background */
    mColors[ColorTheme::Background] = Color{57, 62, 70, 255};
    mColors[ColorTheme::Text] = Color{238, 238, 238, 255};

    /* GUI */
    /* Logo color */
    mColors[ColorTheme::Logo1FirstPart] = Color{238, 238, 238, 255};
    mColors[ColorTheme::Logo1SecondPart] = Color{0, 173, 181, 255};
    mColors[ColorTheme::Logo2FirstPart] = Color{238, 238, 238, 255};
    mColors[ColorTheme::Logo2SecondPart] = Color{0, 173, 181, 255};

    /* Navigation bar */
    mColors[ColorTheme::NavigationBar_SelectedTitle] =
        Color{238, 238, 238, 255};
    mColors[ColorTheme::NavigationBar_UnselectedTitle] =
        Color{170, 170, 170, 255};
    mColors[ColorTheme::NavigationBar_Background] = Color{34, 40, 49, 255};

    /* Footer */
    mColors[ColorTheme::Footer_Background] = Color{34, 40, 49, 255};
    mColors[ColorTheme::Footer_Icon] = Color{238, 238, 238, 255};
    mColors[ColorTheme::Footer_HoveredIcon] = Color{0, 173, 181, 255};

    /* Button */
    mColors[ColorTheme::Button_Background] = Color{0, 173, 181, 255};
    mColors[ColorTheme::Button_HoveredBackground] = Color{238, 238, 238, 255};
    mColors[ColorTheme::Button_Text] = Color{34, 40, 49, 255};

    /* Card (title) */
    mColors[ColorTheme::Card_Background] = Color{34, 40, 49, 255};
    mColors[ColorTheme::Card_Text] = Color{238, 238, 238, 255};

    /* Action list */
    mColors[ColorTheme::ActionList_Text] = Color{34, 40, 49, 255};
    mColors[ColorTheme::ActionList_Background] = Color{0, 173, 181, 255};
    mColors[ColorTheme::ActionList_HoverBackground] = Color{238, 238, 238, 255};
    /* Action list input */
    mColors[ColorTheme::InputField_Inactive] = Color{34, 40, 49, 255};

    /* Code highlighter */
    mColors[ColorTheme::ActionDescription_Background] = Color{8, 217, 214, 255};
    mColors[ColorTheme::ActionDescription_Text] = Color{37, 42, 52, 255};
    mColors[ColorTheme::CodeHighlighter_Background] = Color{255, 46, 99, 255};
    mColors[ColorTheme::CodeHighlighter_Text] = Color{37, 42, 52, 255};
    mColors[ColorTheme::CodeHighlighter_HighlightedLineBackground] =
        Color{234, 234, 234, 255};

    /* Visualizer */
    mColors[ColorTheme::Visualizer_ErrorText] = Color{255, 46, 99, 255};
    mColors[ColorTheme::Visualizer_Label] = Color{255, 46, 99, 255};

    /* Node */
    /* Default */
    mColors[ColorTheme::Visualizer_Node_Default_Outline1] =
        Color{232, 106, 51, 255};
    mColors[ColorTheme::Visualizer_Node_Default_Outline2] =
        Color{232, 106, 51, 255};
    mColors[ColorTheme::Visualizer_Node_Default_Background1] =
        Color{242, 227, 219, 255};
    mColors[ColorTheme::Visualizer_Node_Default_Background2] =
        Color{242, 227, 219, 255};
    mColors[ColorTheme::Visualizer_Node_Default_Text1] =
        Color{232, 106, 51, 255};
    mColors[ColorTheme::Visualizer_Node_Default_Text2] =
        Color{232, 106, 51, 255};

    /* Active */
    mColors[ColorTheme::Visualizer_Node_Active_Outline1] =
        Color{232, 106, 51, 255};
    mColors[ColorTheme::Visualizer_Node_Active_Outline2] =
        Color{255, 46, 99, 255};
    mColors[ColorTheme::Visualizer_Node_Active_Background1] =
        Color{242, 227, 219, 255};
    mColors[ColorTheme::Visualizer_Node_Active_Background2] =
        Color{255, 46, 99, 255};
    mColors[ColorTheme::Visualizer_Node_Active_Text1] =
        Color{232, 106, 51, 255};
    mColors[ColorTheme::Visualizer_Node_Active_Text2] =
        Color{242, 227, 219, 255};

    /* Active Blue */
    mColors[ColorTheme::Visualizer_Node_ActiveBlue_Outline1] =
        Color{232, 106, 51, 255};
    mColors[ColorTheme::Visualizer_Node_ActiveBlue_Outline2] =
        Color{46, 187, 209, 255};
    mColors[ColorTheme::Visualizer_Node_ActiveBlue_Background1] =
        Color{242, 227, 219, 255};
    mColors[ColorTheme::Visualizer_Node_ActiveBlue_Background2] =
        Color{46, 187, 209, 255};
    mColors[ColorTheme::Visualizer_Node_ActiveBlue_Text1] =
        Color{232, 106, 51, 255};
    mColors[ColorTheme::Visualizer_Node_ActiveBlue_Text2] =
        Color{242, 227, 219, 255};

    /* Active Green */
    mColors[ColorTheme::Visualizer_Node_ActiveGreen_Outline1] =
        Color{232, 106, 51, 255};
    mColors[ColorTheme::Visualizer_Node_ActiveGreen_Outline2] =
        Color{82, 188, 105, 255};
    mColors[ColorTheme::Visualizer_Node_ActiveGreen_Background1] =
        Color{242, 227, 219, 255};
    mColors[ColorTheme::Visualizer_Node_ActiveGreen_Background2] =
        Color{82, 188, 105, 255};
    mColors[ColorTheme::Visualizer_Node_ActiveGreen_Text1] =
        Color{232, 106, 51, 255};
    mColors[ColorTheme::Visualizer_Node_ActiveGreen_Text2] =
        Color{242, 227, 219, 255};

    /* Active Red */
    mColors[ColorTheme::Visualizer_Node_ActiveRed_Outline1] =
        Color{232, 106, 51, 255};
    mColors[ColorTheme::Visualizer_Node_ActiveRed_Outline2] =
        Color{217, 81, 60, 255};
    mColors[ColorTheme::Visualizer_Node_ActiveRed_Background1] =
        Color{242, 227, 219, 255};
    mColors[ColorTheme::Visualizer_Node_ActiveRed_Background2] =
        Color{217, 81, 60, 255};
    mColors[ColorTheme::Visualizer_Node_ActiveRed_Text1] =
        Color{232, 106, 51, 255};
    mColors[ColorTheme::Visualizer_Node_ActiveRed_Text2] =
        Color{242, 227, 219, 255};

    /* Iterated */
    mColors[ColorTheme::Visualizer_Node_Iterated_Outline1] =
        Color{255, 46, 99, 255};
    mColors[ColorTheme::Visualizer_Node_Iterated_Outline2] =
        Color{255, 46, 99, 255};
    mColors[ColorTheme::Visualizer_Node_Iterated_Background1] =
        Color{255, 46, 99, 255};
    mColors[ColorTheme::Visualizer_Node_Iterated_Background2] =
        Color{242, 227, 219, 255};
    mColors[ColorTheme::Visualizer_Node_Iterated_Text1] =
        Color{242, 227, 219, 255};
    mColors[ColorTheme::Visualizer_Node_Iterated_Text2] =
        Color{255, 46, 99, 255};

    /* Arrow */
    mColors[ColorTheme::Visualizer_Arrow_Default] = Color{232, 106, 51, 255};
    mColors[ColorTheme::Visualizer_Arrow_Active] = Color{255, 46, 99, 255};
}

void Settings::LoadDefaultColors() {
    /* Background */
    mColors[ColorTheme::Background] = RAYWHITE;
    mColors[ColorTheme::Text] = BLACK;

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

    /* Footer */
    mColors[ColorTheme::Footer_Background] = BLACK;
    mColors[ColorTheme::Footer_Icon] = WHITE;
    mColors[ColorTheme::Footer_HoveredIcon] = Color{82, 188, 105, 255};

    /* Button */
    mColors[ColorTheme::Button_Background] = Color{82, 188, 105, 255};
    mColors[ColorTheme::Button_HoveredBackground] = BLACK;
    mColors[ColorTheme::Button_Text] = WHITE;

    /* Card (title) */
    mColors[ColorTheme::Card_Background] = LIGHTGRAY;
    mColors[ColorTheme::Card_Text] = BLACK;

    /* Action list */
    mColors[ColorTheme::ActionList_Text] = WHITE;
    mColors[ColorTheme::ActionList_Background] = Color{82, 188, 105, 255};
    mColors[ColorTheme::ActionList_HoverBackground] = BLACK;
    /* Input */
    mColors[ColorTheme::InputField_Inactive] = BLACK;

    /* Code highlighter */
    mColors[ColorTheme::CodeHighlighter_Background] = Color{46, 187, 209, 255};
    mColors[ColorTheme::CodeHighlighter_Text] = WHITE;
    mColors[ColorTheme::CodeHighlighter_HighlightedLineBackground] = BLACK;
    mColors[ColorTheme::ActionDescription_Background] =
        Color{255, 133, 39, 255};
    mColors[ColorTheme::ActionDescription_Text] = WHITE;

    /* Visualizer */
    /* Label */
    mColors[ColorTheme::Visualizer_Label] = RED;
    mColors[ColorTheme::Visualizer_ErrorText] = RED;
    mColors[ColorTheme::Visualizer_ActionText] = BLACK;
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

    /* Active Red */
    mColors[ColorTheme::Visualizer_Node_ActiveRed_Outline1] = BLACK;
    mColors[ColorTheme::Visualizer_Node_ActiveRed_Outline2] =
        Color{217, 81, 60, 255};
    mColors[ColorTheme::Visualizer_Node_ActiveRed_Background1] = WHITE;
    mColors[ColorTheme::Visualizer_Node_ActiveRed_Background2] =
        Color{217, 81, 60, 255};
    mColors[ColorTheme::Visualizer_Node_ActiveRed_Text1] = BLACK;
    mColors[ColorTheme::Visualizer_Node_ActiveRed_Text2] = WHITE;

    /* Iterated */
    mColors[ColorTheme::Visualizer_Node_Iterated_Outline1] =
        Color{255, 138, 39, 255};
    mColors[ColorTheme::Visualizer_Node_Iterated_Outline2] =
        Color{255, 138, 39, 255};
    mColors[ColorTheme::Visualizer_Node_Iterated_Background1] =
        Color{255, 138, 39, 255};
    ;
    mColors[ColorTheme::Visualizer_Node_Iterated_Background2] = WHITE;

    mColors[ColorTheme::Visualizer_Node_Iterated_Text1] = WHITE;
    mColors[ColorTheme::Visualizer_Node_Iterated_Text2] =
        Color{255, 138, 39, 255};

    /* Arrow */
    mColors[ColorTheme::Visualizer_Arrow_Default] = BLACK;
    mColors[ColorTheme::Visualizer_Arrow_Active] = Color{255, 138, 39, 255};
}

/*
void Settings::SaveToFile(const std::string& path) {
    std::ofstream out(path, std::ios::binary);

    for (int i = 0; i < ColorTheme::Count; i++) {
        unsigned color = ColorToInt(getColor(i));
        out.write(reinterpret_cast< char* >(&color), sizeof(unsigned));
    }
    out.close();
}
*/

/*
void Settings::LoadFromFile(const std::string& path) {
    std::ifstream in(path, std::ios::binary);

    // if (!in.is_open()) {
    //     LoadDefaultColors();
    //     SaveToFile(path);

    //     in.close();
    //     in.open(path, std::ios::binary);
    // }

    unsigned hexColor;
    for (int i = 0; i < ColorTheme::Count; i++) {
        in.read(reinterpret_cast< char* >(&hexColor), sizeof(unsigned));
        mColors[i] = GetColor(hexColor);
    }
}
*/

Settings::~Settings() {
    // SaveToFile(global::defaultColorPath);
}

Color Settings::getColor(std::size_t id) const {
    auto found = mColors.find(id);
    assert(found != mColors.end());

    return found->second;
}

void Settings::Load() {
    mCurrentColorTheme = 0;
    LoadDefaultColors();
}

void Settings::SwitchTheme() {
    mCurrentColorTheme = 1 - mCurrentColorTheme;
    switch (mCurrentColorTheme) {
        case 0:
            LoadDefaultColors();
            break;
        case 1:
            LoadDarkColors();
            break;
    }
}
