#include <Native/NativeApplication.h>
#include <Game/Game.h>


int main() {
    Engine::Native::NativeApplication app;

    Game::Game game(std::move(app.make_context()));
    app.run();
    
    return 0;
}
