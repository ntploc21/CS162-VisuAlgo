#ifndef COMPONENTS_INTEGERINPUTFIELD_HPP
#define COMPONENTS_INTEGERINPUTFIELD_HPP

#include "InputField.hpp"

namespace GUIComponent {
    class IntegerInputField : public InputField {
    public:
        typedef std::shared_ptr< IntegerInputField > Ptr;
        IntegerInputField(FontHolder* fonts);
        ~IntegerInputField();
        std::string ExtractValue();
        void DrawField(Vector2 base = (Vector2){0, 0});

        void SetConstraint(int minValue, int maxValue);
        bool isSelectable() const;

    public:
        void Randomize();

    private:
        int mMinValue;
        int mMaxValue;
        int input;
    };
};      // namespace GUIComponent

#endif  // COMPONENTS_INTEGERINPUTFIELD_HPP