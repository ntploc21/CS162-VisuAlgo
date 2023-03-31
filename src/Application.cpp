#include "Application.hpp"

#include "Global.hpp"
#include "States/Array/DynamicArrayState.hpp"
#include "States/Array/StaticArrayState.hpp"
#include "States/HomepageState.hpp"
#include "States/LinkedList/CLLState.hpp"
#include "States/LinkedList/DLLState.hpp"
#include "States/LinkedList/QueueState.hpp"
#include "States/LinkedList/SLLState.hpp"
#include "States/LinkedList/StackState.hpp"
#include "States/SettingsState.hpp"

void Application::Init() {
    InitWindow(global::kScreenWidth, global::kScreenHeight,
               global::kTitle.c_str());
    favicon = LoadImage(global::favicon.c_str());

    SetWindowIcon(favicon);
    // SetTargetFPS(global::kFramesPerSecond);

    mStack.PushState(States::Homepage);
}

bool Application::WindowClosed() { return closed; }

void Application::Close() {
    CloseWindow();
    UnloadImage(favicon);
}

void Application::Run() {
    /* render */
    Update(GetFrameTime());
    Render();

    if (WindowShouldClose()) closed = true;
}

void Application::Render() {
    BeginDrawing();

    ClearBackground(RAYWHITE);

    EndDrawing();
}

void Application::Update(float dt) { mStack.Update(dt); }

void Application::RegisterStates() {
    mStack.RegisterState< HomepageState >(States::Homepage);
    mStack.RegisterState< SettingsState >(States::Settings);
    mStack.RegisterState< StaticArrayState >(States::StaticArray);
    mStack.RegisterState< DynamicArrayState >(States::DynamicArray);
    mStack.RegisterState< SLLState >(States::SinglyLinkedList);
    mStack.RegisterState< DLLState >(States::DoublyLinkedList);
    mStack.RegisterState< CLLState >(States::CircularLinkedList);
    mStack.RegisterState< StackState >(States::Stack);
    mStack.RegisterState< QueueState >(States::Queue);
}

Application::Application() : mStack(State::Context()) { RegisterStates(); }

Application::~Application() {}