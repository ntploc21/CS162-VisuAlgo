#ifndef STATE_HPP
#define STATE_HPP

#include <memory>

#include "Components/NavigationBar.hpp"
#include "FontHolder.hpp"
#include "StateIdentifiers.hpp"
#include "TextureHolder.hpp"

// Categories and Data Structures identifiers
#include "CategoryInfo.hpp"
#include "DSInfo.hpp"

class StateStack;

class State {
public:
    typedef std::unique_ptr< State > Ptr;
    struct Context {
        Context();
        Context(FontHolder* fonts, TextureHolder* textures,
                CategoryInfo* categories, DSInfo* dsInfo);
        FontHolder* fonts;
        TextureHolder* textures;
        CategoryInfo* categories;
        DSInfo* dsInfo;
    };

public:
    State(StateStack& stack, Context context);
    virtual ~State();
    virtual void Draw() = 0;
    virtual bool Update(float dt) = 0;
    // virtual bool handleEvent(Event event) = 0;

protected:
    void RequestStackPush(States::ID stateID);
    void RequestStackPop();
    void RequestStackClear();
    Context GetContext() const;

    void InitNavigationBar();

private:
    StateStack* mStack;
    Context mContext;

protected:
    NavigationBar navigation;
};

#endif  // STATE_HPP