#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <memory>

#include "NonCopyable.hpp"
#include "raylib.h"

namespace GUI {
    class Component : private NonCopyable< Component > {
    public:
        typedef std::shared_ptr< Component > Ptr;

    public:
        Component();
        virtual ~Component();

        virtual void Draw(Vector2 base);

        virtual bool isSelectable() const = 0;
        bool isSelected() const;
        virtual void select();
        virtual void deselect();

    public:
        void SetPosition(float x, float y);

        Vector2 GetPosition();

    protected:
        Vector2 position;

    private:
        bool mIsSelected;
    };
};  // namespace GUI

#endif  // COMPONENT_HPP