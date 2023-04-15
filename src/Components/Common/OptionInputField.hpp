#ifndef COMPONENTS_OPTIONINPUTFIELD_HPP
#define COMPONENTS_OPTIONINPUTFIELD_HPP

#include <functional>

#include "Button.hpp"
#include "Container.hpp"
#include "InputField.hpp"

class OptionInputField : public GUI::Container {
public:
    typedef std::shared_ptr< OptionInputField > Ptr;

public:
    OptionInputField(FontHolder *fonts);
    ~OptionInputField();
    void SetOption(
        std::string content, std::vector< InputField::Ptr > fields,
        std::function< void(std::map< std::string, std::string >) > action);
    void SetNoFieldOption(std::string content, std::function< void() > action);

    void ToggleInputFields();

    void DrawCurrent(Vector2 base = (Vector2){0, 0});
    void SetVisible(bool visible);

public:
    virtual Vector2 GetSize();

private:
    std::map< std::string, std::string > ExtractInput();
    void AddInputField(InputField::Ptr inputField);
    void AddSubmitField(
        std::function< void(std::map< std::string, std::string >) > action);

private:
    bool HasInputField();
    GUI::Container::Ptr mInputField;
    std::map< std::string, std::string > mInput;

private:
    FontHolder *fonts;
    bool hasInputField;
    // std::function< void(std::map< std::string, std::string >) > mAction;
};

#endif  // COMPONENTS_OPTIONINPUTFIELD_HPP