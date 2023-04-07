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
        void Draw(Vector2 base);
        virtual bool isSelectable() const;

    private:
        std::vector< Component::Ptr > mChildren;
    };
};  // namespace GUI

#endif  // CONTAINER_HPP