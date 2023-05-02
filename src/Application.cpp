#include "Application.hpp"

#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "Global.hpp"
#include "Settings.hpp"

// States
#include "Settings.hpp"
#include "States/Array/DynamicArrayState.hpp"
#include "States/Array/StaticArrayState.hpp"
#include "States/HomepageState.hpp"
#include "States/LinkedList/CLLState.hpp"
#include "States/LinkedList/DLLState.hpp"
#include "States/LinkedList/QueueState.hpp"
#include "States/LinkedList/SLLState.hpp"
#include "States/LinkedList/StackState.hpp"

std::vector< bool > GUI::InputField::fields(std::vector< bool >(0));

void Application::Init() {
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(global::SCREEN_WIDTH, global::SCREEN_HEIGHT,
               global::kTitle.c_str());
    LoadResources();
    Image favicon = LoadImageFromTexture(images->Get(Textures::Favicon));

    SetWindowIcon(favicon);

    UnloadImage(favicon);

    Settings& settings = Settings::getInstance();
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

    const Color backgroundColor =
        Settings::getInstance().getColor(ColorTheme::Background);
    ClearBackground(backgroundColor);
    mStack.Draw();

    EndDrawing();
}

void Application::Update(float dt) { mStack.Update(dt); }

void Application::RegisterStates() {
    // Register Categories
    categories->Register(Category::Array, {Category::Array,
                                           {DataStructures::StaticArray,
                                            DataStructures::DynamicArray},
                                           "array"});
    categories->Register(
        Category::LinkedList,
        {Category::LinkedList,
         {DataStructures::SinglyLinkedList, DataStructures::DoublyLinkedList,
          DataStructures::CircularLinkedList, DataStructures::Stack,
          DataStructures::Queue},
         "list"});

    // Register Data Structures Information
    dsInfo->Register(
        DataStructures::StaticArray,
        {DataStructures::StaticArray, States::StaticArray, Category::Array,
         Textures::StaticArray, "Static Array", "Static Array"});
    dsInfo->Register(
        DataStructures::DynamicArray,
        {DataStructures::DynamicArray, States::DynamicArray, Category::Array,
         Textures::DynamicArray, "Dynamic Array (Vector)", "Dynamic Array"});
    dsInfo->Register(DataStructures::SinglyLinkedList,
                     {DataStructures::SinglyLinkedList,
                      States::SinglyLinkedList, Category::LinkedList,
                      Textures::SinglyLinkedList, "Singly Linked List", "SLL"});
    dsInfo->Register(DataStructures::DoublyLinkedList,
                     {DataStructures::DoublyLinkedList,
                      States::DoublyLinkedList, Category::LinkedList,
                      Textures::DoublyLinkedList, "Doubly Linked List", "DLL"});
    dsInfo->Register(
        DataStructures::CircularLinkedList,
        {DataStructures::CircularLinkedList, States::CircularLinkedList,
         Category::LinkedList, Textures::CircularLinkedList,
         "Circular Linked List", "CLL"});
    dsInfo->Register(DataStructures::Stack,
                     {DataStructures::Stack, States::Stack,
                      Category::LinkedList, Textures::Stack, "Stack", "Stack"});
    dsInfo->Register(DataStructures::Queue,
                     {DataStructures::Queue, States::Queue,
                      Category::LinkedList, Textures::Queue, "Queue", "Queue"});

    // Register States
    mStack.RegisterState< State::HomepageState >(States::Homepage);
    mStack.RegisterState< State::StaticArrayState >(States::StaticArray);
    mStack.RegisterState< State::DynamicArrayState >(States::DynamicArray);
    mStack.RegisterState< State::SLLState >(States::SinglyLinkedList);
    mStack.RegisterState< State::DLLState >(States::DoublyLinkedList);
    mStack.RegisterState< State::CLLState >(States::CircularLinkedList);
    mStack.RegisterState< State::StackState >(States::Stack);
    mStack.RegisterState< State::QueueState >(States::Queue);
}

void Application::LoadResources() {
    // Load fonts
    fonts->Load(Fonts::Default, "assets/fonts/PTSans-Regular.ttf");
    fonts->Load(Fonts::Default_Italic, "assets/fonts/PTSans-Italic.ttf");
    fonts->Load(Fonts::Default_Bold, "assets/fonts/PTSans-Bold.ttf");
    fonts->Load(Fonts::Silkscreen, "assets/fonts/Silkscreen-Regular.ttf");
    fonts->Load(Fonts::Consolas, "assets/fonts/CONSOLA.TTF");
    fonts->Load(Fonts::Courier, "assets/fonts/CourierPrime-Regular.ttf");
    fonts->Load(Fonts::Courier_Bold, "assets/fonts/CourierPrime-Bold.ttf");

    // ==============

    // Load images
    images->Load(Textures::Blank, "assets/images/favicon.png");
    images->Load(Textures::StaticArray, "assets/images/StaticArray.png", 250,
                 160, true);
    images->Load(Textures::DynamicArray, "assets/images/DynamicArray.png", 250,
                 160, true);
    images->Load(Textures::SinglyLinkedList,
                 "assets/images/SinglyLinkedList.png", 250, 160, true);
    images->Load(Textures::DoublyLinkedList,
                 "assets/images/DoublyLinkedList.png", 250, 160, true);
    images->Load(Textures::CircularLinkedList,
                 "assets/images/CircularLinkedList.png", 250, 160, true);
    images->Load(Textures::Stack, "assets/images/Stack.png", 250, 160, true);
    images->Load(Textures::Queue, "assets/images/Queue.png", 250, 160, true);
    images->Load(Textures::Favicon, "assets/images/favicon.png");

    // ===============
    Settings::getInstance().Load();
}

Application::Application()
    : mStack(State::State::Context(
          fonts = new FontHolder(), images = new TextureHolder(),
          categories = new CategoryInfo(), dsInfo = new DSInfo())) {
    RegisterStates();
}

Application::~Application() {}