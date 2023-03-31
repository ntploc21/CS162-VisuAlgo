#include "Application.hpp"

int main() {
    Application app;
    app.Init();
    while (!app.WindowClosed()) app.Run();
    app.Close();
}