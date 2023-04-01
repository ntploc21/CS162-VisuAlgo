#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "StateStack.hpp"

class Application {
public:
    Application();
    ~Application();
    void Run();
    void Close();
    void Init();
    bool WindowClosed();

private:
    void Render();
    void RegisterStates();
    void Update(float dt);

private:
    bool closed = false;
    // Image favicon;

private:
    StateStack mStack;
};

#endif  // APPLICATION_HPP