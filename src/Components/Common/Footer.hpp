#ifndef COMPONENTS_COMMON_FOOTER_HPP
#define COMPONENTS_COMMON_FOOTER_HPP

#include "Container.hpp"
#include "Core/Animation/AnimationController.hpp"

namespace GUI {
    class Footer : public GUI::Container {
    public:
        Footer();
        ~Footer();
        void Draw(Animation::AnimationController::Ptr animController,
                  Vector2 base = (Vector2){0, 0});
    };
};  // namespace GUI

#endif  // COMPONENTS_COMMON_FOOTER_HPP