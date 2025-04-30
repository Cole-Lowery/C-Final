#include "Game.h"
#include "raylib.h"

Game::Game() : snake(256, squareSize, screenWidth, screenHeight), food(squareSize, screenWidth, screenHeight) {}

void Game::Init() {
    frameCounter = 0;
    gameOver = false;
    pause = false;
    snake.Init();
    food.Deactivate();
}

void Game::Update() {
    if (!gameOver) {
        if (IsKeyPressed(KEY_P)) pause = !pause;

        if (!pause) {
            snake.Update();

            if (!food.IsActive()) {
                food.Spawn(nullptr, 0); // Replace with actual avoidance if needed
            }

            if (snake.CheckCollisionWith(food.GetPosition(), food.GetSize())) {
                snake.Grow();
                food.Deactivate();
            }

            if (snake.CheckSelfCollision() ||
                snake.GetHeadPosition().x < 0 || snake.GetHeadPosition().y < 0 ||
                snake.GetHeadPosition().x > screenWidth || snake.GetHeadPosition().y > screenHeight) {
                gameOver = true;
            }

            frameCounter++;
        }
    }
    else {
        if (IsKeyPressed(KEY_ENTER)) {
            Init();
        }
    }
}

void Game::Draw() {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    if (!gameOver) {
        snake.Draw();
        food.Draw();
        if (pause) DrawText("PAUSED", screenWidth / 2 - 60, screenHeight / 2, 40, GRAY);
    }
    else {
        DrawText("PRESS ENTER TO RESTART", screenWidth / 2 - 150, screenHeight / 2, 20, RED);
    }

    EndDrawing();
}

void Game::Unload() {}
