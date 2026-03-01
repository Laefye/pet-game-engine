#include <Native/NativeApplication.h>
#include <Game/Game.h>
#include <QApplication>
#include <thread>


int main(int argc, char *argv[])
{
    QApplication app{argc, argv};
    Engine::Native::NativeApplication gameApp;

    for (int i = 0; i < argc; ++i) {
        if (std::string(argv[i]) == "--console") {
            gameApp.open_console();
        }
    }

    std::thread gameThread([&gameApp, &game](){
        Game::Game game(std::move(gameApp.make_context()));
        gameApp.run();
    });

    int result = app.exec();

    gameThread.join();
    return result;
}
