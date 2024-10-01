#include "Game.h"
#include <Application.h>

using namespace Core;

int main(void)
{
    ApplicationSpecification appInfo;
    appInfo.name = "Platformer";
    appInfo.author = "Magnus Ahlstromer V";
    appInfo.windowWidth = 1280;
    appInfo.windowHeight = 720;
    appInfo.isVsyncEnabled = true;

    Game game(appInfo);
    game.Run();

    return 0;
}
