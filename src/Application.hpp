#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "StateStack.hpp"

/**
 * @brief The application class that represents the application.
 * @details The application class is used to represent the application. It
 * contains the main loop of the application.
 */
class Application {
public:
    /**
     * @brief Construct a new Application object.
     */
    Application();

    /**
     * @brief Destroy the Application object.
     */
    ~Application();

    /**
     * @brief Run the application.
     * @details This function runs the application.
     */
    void Run();

    /**
     * @brief Close the application.
     * @details This function closes the application.
     */
    void Close();

    void Init();

    /**
     * @brief Check if the window is closed.
     * @details This function checks if the window is closed.
     * @return True if the window is closed.
     */
    bool WindowClosed();

private:
    /**
     * @brief Draw/render the application.
     * @details This function draws the application.
     */
    void Render();

    /**
     * @brief Register the states/scenes of the application.
     * @details This function registers the states/scenes of the application.
     * @see StateStack::RegisterState
     */
    void RegisterStates();

    /**
     * @brief Load the resources of the application.
     * @details This function loads the resources of the application.
     * @see TextureHolder::Load
     * @see FontHolder::Load
     */
    void LoadResources();

    /**
     * @brief Update the application.
     * @details This function updates the application.
     * @param dt The delta time.
     */
    void Update(float dt);

private:
    bool closed = false;
    // Image favicon;

private:
    /**
     * @brief The state stack of the application.
     * @details The state stack is used to manage the states/scenes of the
     * application.
     * @see StateStack
     */
    State::StateStack mStack;

    /**
     * @brief The font holder of the application.
     * @details The font holder is used to hold the fonts of the application.
     * @see FontHolder
     */
    FontHolder* fonts;

    /**
     * @brief The texture holder of the application.
     * @details The texture holder is used to hold the textures of the
     * application.
     * @see TextureHolder
     */
    TextureHolder* images;

    /**
     * @brief The category info of the application.
     * @details The category info is used to hold the category info of the
     * application.
     * @see CategoryInfo
     */
    CategoryInfo* categories;

    /**
     * @brief The data structure info of the application.
     * @details The data structure info is used to hold the all of the
     * information about every data structure.
     * @see DSInfo
     */
    DSInfo* dsInfo;
};

#endif  // APPLICATION_HPP