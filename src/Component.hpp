#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <map>
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

        virtual void SetVisible(bool visible);
        virtual bool GetVisible();

    public:
        void SetPosition(float x, float y);
        void SetPosition(Vector2 position);

        Vector2 GetPosition();

    protected:
        Vector2 mPosition;
        bool mVisible;

    private:
        bool mIsSelected;

    protected:
        virtual void UpdateMouseCursorWhenHover(
            std::map< std::string, Rectangle > bounds, bool hover,
            bool noHover);
        virtual void UpdateMouseCursorWhenHover(Rectangle bound, bool hover,
                                                bool noHover);
        virtual bool GetHoverStatus(std::map< std::string, Rectangle > bounds,
                                    bool hover, bool noHover);
        virtual bool GetHoverStatus(Rectangle bound, bool hover, bool noHover);
    };
};  // namespace GUI

#endif  // COMPONENT_HPP