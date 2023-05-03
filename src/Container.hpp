#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <memory>
#include <vector>

#include "Component.hpp"
#include "Core/Deque.hpp"

namespace GUI {
    /**
     * @brief The base container class that is used to represent a GUI container
     * in the GUI.
     */
    class Container : public Component {
    public:
        /**
         * @brief The shared pointer to the container.
         * @details The GUI container is commonly used by multiple components,
         * so a shared pointer is used.
         * @see std::shared_ptr
         */
        typedef std::shared_ptr< Container > Ptr;

    public:
        /**
         * @brief Construct a new Container object.
         */
        Container();

        /**
         * @brief Pack a component into the container.
         * @details This function packs a component into the container.
         * @param component The component to pack.
         */
        void pack(Component::Ptr component);

        /**
         * @brief Unpack all components from the container.
         * @details This function unpacks all components from the container.
         * @see pack
         */
        void UnpackAll();

        /**
         * @brief Draw the container.
         * @details This function draws the container.
         * @param base The base position of the container.
         */
        virtual void Draw(Vector2 base = (Vector2){0, 0});

        /**
         * @deprecated This function is deprecated.
         * @brief Check if the container is selectable.
         * @details This function checks if the container is selectable.
         * @return True if the container is selectable.
         */
        virtual bool isSelectable() const;

        /**
         * @brief Get the pack components of the container.
         * @details This function returns the all of the pack components of the
         * container.
         * @return The children of the container.
         */
        Core::Deque< Component::Ptr > GetChildren();

        virtual void DrawCurrent(Vector2 base);

        /**
         * @brief Get the size of the container.
         * @details This function returns the size of the container.
         * @return The size of the container.
         */
        virtual Vector2 GetSize();

    protected:
        // std::vector< Component::Ptr > mChildren;
        Core::Deque< Component::Ptr > mChildren;
    };
};      // namespace GUI

#endif  // CONTAINER_HPP