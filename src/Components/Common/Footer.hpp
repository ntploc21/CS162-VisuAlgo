#ifndef COMPONENTS_COMMON_FOOTER_HPP
#define COMPONENTS_COMMON_FOOTER_HPP

#include "Animation/AnimationController.hpp"
#include "Container.hpp"
#include "Global.hpp"
#include "Settings.hpp"
#include "Utils/Utils.hpp"

namespace GUI {
    template< typename T >
    class Footer : public GUI::Container {
    public:
        Footer();
        ~Footer();
        void Draw(T* animController, Vector2 base = (Vector2){0, 0});
    };
};  // namespace GUI

template< typename T >
GUI::Footer< T >::Footer() {}

template< typename T >
GUI::Footer< T >::~Footer() {}

template< typename T >
void GUI::Footer< T >::Draw(T* animController, Vector2 base) {
    const Color backgroundColor =
        Settings::getInstance().getColor(ColorTheme::Footer_Background);
    const Color iconColor =
        Settings::getInstance().getColor(ColorTheme::Footer_Icon);
    const Color hoveredIconColor =
        Settings::getInstance().getColor(ColorTheme::Footer_HoveredIcon);

    base.x += mPosition.x;
    base.y += mPosition.y;
    DrawRectangleRec((Rectangle){base.x, base.y, global::SCREEN_WIDTH, 40},
                     backgroundColor);

    animController->SetSpeed(
        int(GuiSlider((Rectangle){base.x + 80, base.y + 15, 140, 10}, nullptr,
                      TextFormat("%dx", int(animController->GetSpeed())),
                      animController->GetSpeed(), 1, 7)));

    {  // Draw Reset
        if (Utils::DrawIcon(129, base.x + 345, base.y + 12, 1, iconColor,
                            hoveredIconColor)) {
            animController->Reset();
        }
    }

    {  // Draw Step Backward
        if (Utils::DrawIcon(130, base.x + 365, base.y + 12, 1, iconColor,
                            hoveredIconColor)) {
            animController->StepBackward();
        }
    }

    {  // Draw play button
        if (animController->Done()) {
            if (Utils::DrawIcon(74, base.x + 385, base.y + 12, 1, iconColor,
                                hoveredIconColor)) {
                animController->Reset();
            }
        } else if (animController->IsPlaying()) {
            if (Utils::DrawIcon(132, base.x + 385, base.y + 12, 1, iconColor,
                                hoveredIconColor)) {
                animController->Pause();
            }
        } else if (Utils::DrawIcon(133, base.x + 385, base.y + 12, 1, iconColor,
                                   hoveredIconColor)) {
            animController->Continue();
        }
    }

    {  // Draw Step Forward
        if (Utils::DrawIcon(131, base.x + 405, base.y + 12, 1, iconColor,
                            hoveredIconColor)) {
            animController->StepForward();
        }
    }

    {  // Draw Run All
        if (Utils::DrawIcon(134, base.x + 425, base.y + 12, 1, iconColor,
                            hoveredIconColor)) {
            animController->RunAll();
        }
    }

    // progressValue =
    animController->SetAnimation(
        GuiSliderBar((Rectangle){base.x + 450, base.y + 15, 400, 10}, nullptr,
                     nullptr, animController->GetAnimationIndex(), 0,
                     std::max(0, int(animController->GetNumAnimation() - 1))));
}

#endif  // COMPONENTS_COMMON_FOOTER_HPP