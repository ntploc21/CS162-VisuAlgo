#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <memory>
#include <vector>

#include "Component.hpp"

namespace GUI {
    class Container : public Component {
    public:
        typedef std::shared_ptr< Container > Ptr;

    public:
        Container();
        void pack(Component::Ptr component);
        void Draw(Vector2 base = (Vector2){0, 0});
        virtual bool isSelectable() const;
        std::vector< Component::Ptr > GetChildren();

    protected:
        std::vector< Component::Ptr > mChildren;
    };
};  // namespace GUI

#endif  // CONTAINER_HPP