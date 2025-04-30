#include "raylib.h"
#include "Game.h"

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

Game game;

void UpdateDrawFrame() {
    game.Update();
    game.Draw();
}

int main() {
    InitWindow(800, 450, "Snake");
    game.Init();

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 60, 1);
#else
    SetTargetFPS(40);
    while (!WindowShouldClose()) {
        UpdateDrawFrame();
    }
#endif

    game.Unload();
    CloseWindow();

    return 0;
}
