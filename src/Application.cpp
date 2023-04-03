#include "Application.hpp"

#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
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
    InitWindow(global::SCREEN_WIDTH, global::SCREEN_HEIGHT,
               global::kTitle.c_str());
    LoadResources();
    Image favicon = LoadImageFromTexture(images->Get(Textures::Favicon));

    SetWindowIcon(favicon);

    UnloadImage(favicon);
    // SetTargetFPS(global::kFramesPerSecond);

    mStack.PushState(States::Homepage);
}

bool Application::WindowClosed() { return closed; }

void Application::Close() { CloseWindow(); }

void Application::Run() {
    /* render */
    Update(GetFrameTime());
    Render();

    if (WindowShouldClose()) closed = true;
}

void Application::Render() {
    BeginDrawing();

    ClearBackground(RAYWHITE);
    mStack.Draw();

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

void Application::LoadResources() {
    // Load fonts
    fonts->Load(Fonts::Default, "../assets/fonts/PTSans-Regular.ttf");
    fonts->Load(Fonts::Default_Italic, "../assets/fonts/PTSans-Italic.ttf");
    fonts->Load(Fonts::Default_Bold, "../assets/fonts/PTSans-Bold.ttf");
    fonts->Load(Fonts::Silkscreen, "../assets/fonts/Silkscreen-Regular.ttf");
    // ==============

    // Load images
    images->Load(Textures::Blank, "assets/images/favicon.png");
    images->Load(Textures::StaticArray, "assets/images/favicon.png", 250, 160);
    images->Load(Textures::DynamicArray, "assets/images/favicon.png", 250, 160);
    images->Load(Textures::SinglyLinkedList, "assets/images/list.gif", 250,
                 160);
    images->Load(Textures::DoublyLinkedList, "assets/images/list.gif", 250,
                 160);
    images->Load(Textures::CircularLinkedList, "assets/images/list.gif", 250,
                 160);
    images->Load(Textures::Stack, "assets/images/list.gif", 250, 160);
    images->Load(Textures::Queue, "assets/images/list.gif", 250, 160);
    images->Load(Textures::Favicon, "assets/images/favicon.png");
}

Application::Application()
    : mStack(State::Context(fonts = new FontHolder(),
                            images = new TextureHolder())) {
    RegisterStates();
}

Application::~Application() {}