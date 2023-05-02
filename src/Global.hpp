#pragma once

#include <iostream>

// Global variables
namespace global {
    constexpr int SCREEN_WIDTH = 1300;
    constexpr int SCREEN_HEIGHT = 800;
    // constexpr int kFramesPerSecond = 120;
    const std::string kTitle = "CS162 - VisuAlgo Clone";

    const std::string favicon = "assets/images/favicon.png";

    const std::string defaultColorPath = "assets/themes/default-theme.dat";
}  // namespace global