#pragma once
#include "Snake.h"
#include "Food.h"

class Game {
public:
    Game();
    void Init();
    void Update();
    void Draw();
    void Unload();

private:
    int screenWidth = 800;
    int screenHeight = 450;
    int squareSize = 31;

    Snake snake;
    Food food;
    bool gameOver;
    bool pause;
    int frameCounter;
};
