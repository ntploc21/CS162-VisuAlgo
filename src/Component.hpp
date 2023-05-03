#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <map>
#include <memory>
#include <string>

#include "NonCopyable.hpp"
#include "raylib.h"

namespace GUI {
    /**
     * @brief The base component class that is used to represent a GUI component
     * in the GUI.
     */
    class Component
    //: private NonCopyable< Component >
    {
    public:
        /**
         * @brief The shared pointer to the component.
         * @details The GUI component is commonly used by multiple components,
         * so a shared pointer is used.
         * @see std::shared_ptr
         */
        typedef std::shared_ptr< Component > Ptr;

    public:
        /**
         * @brief Construct a new Component object.
         */
        Component();

        /**
         * @brief Destroy the Component object.
         * @details The destructor is virtual so that the derived classes can
         * override it.
         */
        virtual ~Component();

        /**
         * @brief Draw the component.
         * @details This function draws the component.
         * @param base The base position of the component.
         */
        virtual void Draw(Vector2 base = (Vector2){0, 0});

        /**
         * @deprecated This function is deprecated.
         * @brief Check if the component is selectable.
         * @details This function checks if the component is selectable.
         * @return True if the component is selectable.
         */
        virtual bool isSelectable() const = 0;

        /**
         * @deprecated This function is deprecated.
         * @brief Check if the component is selected.
         * @details This function checks if the component is selected.
         * @return True if the component is selected.
         */
        bool isSelected() const;

        /**
         * @deprecated This function is deprecated.
         * @brief Select the component.
         * @details This function selects the component.
         */
        virtual void select();

        /**
         * @deprecated This function is deprecated.
         * @brief Deselect the component.
         * @details This function deselects the component.
         */
        virtual void deselect();

        /**
         * @brief Toggle the visibility of the component.
         * @details This function toggles the visibility of the component.
         */
        virtual void ToggleVisible();

        /**
         * @brief Set the visibility of the component.
         * @details This function sets the visibility of the component.
         * @param visible The visibility of the component.
         */
        virtual void SetVisible(bool visible);

        /**
         * @brief Get the visibility of the component.
         * @details This function gets the visibility of the component.
         * @return The visibility of the component.
         */
        virtual bool GetVisible();

    public:
        /**
         * @brief Set the position of the component.
         * @details This function sets the position of the component.
         * @param x The x coordinate of the position.
         * @param y The y coordinate of the position.
         */
        void SetPosition(float x, float y);

        /**
         * @brief Set the position of the component.
         * @details This function sets the position of the component.
         * @param position The position of the component.
         */
        void SetPosition(Vector2 position);

        /**
         * @brief Get the position of the component.
         * @details This function gets the position of the component.
         * @return The position of the component.
         */
        Vector2 GetPosition();

        /**
         * @brief Get the size of the component.
         * @details This function gets the size of the component.
         * @return The size of the component.
         */
        virtual Vector2 GetSize();

    protected:
        /**
         * @brief The position of the component.
         * @details This variable stores the position of the component.
         */
        Vector2 mPosition;

        /**
         * @brief The visibility of the component.
         * @details This variable stores the visibility of the component.
         */
        bool mVisible;

    private:
        /**
         * @deprecated This variable is deprecated.
         * @brief The selected status of the component.
         * @details This variable stores the selected status of the component.
         */
        bool mIsSelected;

    protected:
        /**
         * @brief Update the mouse cursor when hovering.
         * @details This function updates the mouse cursor when hovering.
         * @param bounds The list of bound of the component.
         */
        virtual void UpdateMouseCursorWhenHover(
            std::map< std::string, Rectangle > bounds, bool hover,
            bool noHover);

        /**
         * @brief Update the mouse cursor when hovering.
         * @details This function updates the mouse cursor when hovering.
         * @param bound The bound of the component.
         */
        virtual void UpdateMouseCursorWhenHover(Rectangle bound, bool hover,
                                                bool noHover);

        /**
         * @brief Get the hover status of the component.
         * @details This function returns the hover status of the component.
         * @param bounds The list of bound of the component.
         */
        virtual bool GetHoverStatus(std::map< std::string, Rectangle > bounds,
                                    bool hover, bool noHover);

        /**
         * @brief Get the hover status of the component.
         * @details This function returns the hover status of the component.
         * @param bound The bound of the component.
         */
        virtual bool GetHoverStatus(Rectangle bound, bool hover, bool noHover);
    };
};      // namespace GUI

#endif  // COMPONENT_HPP