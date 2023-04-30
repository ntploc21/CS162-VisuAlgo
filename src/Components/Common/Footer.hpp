#ifndef COMPONENTS_COMMON_FOOTER_HPP
#define COMPONENTS_COMMON_FOOTER_HPP

#include "Animation/AnimationController.hpp"
#include "Container.hpp"

namespace GUI {
    template< typename T >
    class Footer : public GUI::Container {
    public:
        Footer();
        ~Footer();
        void Draw(T* animController, Vector2 base = (Vector2){0, 0});
    };
};  // namespace GUI

#include "Global.hpp"
#include "Utils.hpp"
// #include "raygui.h"

template< typename T >
GUI::Footer< T >::Footer() {}

template< typename T >
GUI::Footer< T >::~Footer() {}

template< typename T >
void GUI::Footer< T >::Draw(T* animController, Vector2 base) {
    base.x += mPosition.x;
    base.y += mPosition.y;
    DrawRectangleRec((Rectangle){base.x, base.y, global::SCREEN_WIDTH, 40},
                     BLACK);

    animController->SetSpeed(
        int(GuiSlider((Rectangle){base.x + 80, base.y + 15, 140, 10}, nullptr,
                      TextFormat("%dx", int(animController->GetSpeed())),
                      animController->GetSpeed(), 1, 7)));

    {  // Draw Reset
        if (Utils::DrawIcon(129, base.x + 345, base.y + 12, 1, WHITE,
                            (Color){82, 188, 105, 255})) {
            animController->Reset();
        }
    }

    {  // Draw Step Backward
        if (Utils::DrawIcon(130, base.x + 365, base.y + 12, 1, WHITE,
                            (Color){82, 188, 105, 255})) {
            animController->StepBackward();
        }
    }

    {  // Draw play button
        if (animController->Done()) {
            if (Utils::DrawIcon(74, base.x + 385, base.y + 12, 1, WHITE,
                                (Color){82, 188, 105, 255})) {
                animController->Reset();
            }
        } else if (animController->IsPlaying()) {
            if (Utils::DrawIcon(132, base.x + 385, base.y + 12, 1, WHITE,
                                (Color){82, 188, 105, 255})) {
                animController->Pause();
            }
        } else if (Utils::DrawIcon(133, base.x + 385, base.y + 12, 1, WHITE,
                                   (Color){82, 188, 105, 255})) {
            animController->Continue();
        }
    }

    {  // Draw Step Forward
        if (Utils::DrawIcon(131, base.x + 405, base.y + 12, 1, WHITE,
                            (Color){82, 188, 105, 255})) {
            animController->StepForward();
        }
    }

    {  // Draw Run All
        if (Utils::DrawIcon(134, base.x + 425, base.y + 12, 1, WHITE,
                            (Color){82, 188, 105, 255})) {
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