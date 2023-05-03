#ifndef COMPONENTS_STRINGINPUTFIELD_HPP
#define COMPONENTS_STRINGINPUTFIELD_HPP

#include "InputField.hpp"

namespace GUIComponent {
    /**
     * @brief The string input field class that is used to represent a string
     * input field in the GUI.
     * @details The string input field is used to get string input from the
     * user.
     */
    class StringInputField : public InputField {
    public:
        typedef std::shared_ptr< StringInputField > Ptr;
        StringInputField(FontHolder* fonts);
        ~StringInputField();
        std::string ExtractValue();
        void DrawField(Vector2 base = (Vector2){0, 0});
        bool isSelectable() const;

    private:
        std::size_t mMaxLength;
        std::string content;
    };
};      // namespace GUIComponent

#endif  // COMPONENTS_STRINGINPUTFIELD_HPP