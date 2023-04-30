#ifndef COMPONENTS_INPUTFIELD_HPP
#define COMPONENTS_INPUTFIELD_HPP

#include <vector>

#include "Component.hpp"
#include "FontHolder.hpp"

namespace GUI {
    class InputField : public GUI::Component {
    public:
        typedef std::shared_ptr< InputField > Ptr;
        InputField(FontHolder* fonts);
        ~InputField();
        virtual std::string ExtractValue() = 0;
        virtual void Draw(Vector2 base = (Vector2){0, 0});
        virtual void DrawField(Vector2 base = (Vector2){0, 0}) = 0;
        virtual bool isSelectable() const;

    public:
        virtual void SetLabelSize(float fontSize);
        virtual void SetInputFieldSize(Vector2 size);
        virtual Vector2 GetSize();
        virtual void SetLabel(std::string labelContent);
        virtual std::string GetLabel() const;

    protected:
        virtual bool IsClicked(Vector2 base = (Vector2){0, 0}) const;
        virtual void SetEditMode(bool canEdit);
        virtual bool GetEditMode() const;
        virtual void AllFieldDisableEdit();

    public:
        virtual void Randomize();

    protected:
        bool editMode;
        std::size_t mFieldIndex;

    protected:
        float labelFontSize;
        Vector2 inputFieldSize;

    protected:
        std::string label;
        FontHolder* fonts;
        std::string extractedValue;

    public:
        static std::vector< bool > fields;
    };
};  // namespace GUI

#endif  // COMPONENTS_INPUTFIELD_HPP