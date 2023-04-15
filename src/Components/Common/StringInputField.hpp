#ifndef COMPONENTS_STRINGINPUTFIELD_HPP
#define COMPONENTS_STRINGINPUTFIELD_HPP

#include "InputField.hpp"

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

#endif  // COMPONENTS_STRINGINPUTFIELD_HPP