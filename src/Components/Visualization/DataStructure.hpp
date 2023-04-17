#ifndef COMPONENTS_VISUALIZATION_DATASTRUCTURE_HPP
#define COMPONENTS_VISUALIZATION_DATASTRUCTURE_HPP

#include "Container.hpp"
#include "Node.hpp"

namespace GUI {
    class DataStructure : public GUI::Container {
    public:
        typedef std::shared_ptr< DataStructure > Ptr;

    public:
        DataStructure();
        virtual ~DataStructure();
        virtual bool isSelectable() const;
        virtual void Draw(Vector2 base);
    };
};  // namespace GUI

#endif  // COMPONENTS_VISUALIZATION_DATASTRUCTURE_HPP