#pragma once
#include "raylib.h"

class Food {
public:
    Food(int squareSize, int screenWidth, int screenHeight);

    void Spawn(const Vector2* avoidPositions, int count);
    void Draw();
    bool IsActive() const;
    void Deactivate();
    const Vector2& GetPosition() const;
    const Vector2& GetSize() const;

private:
    Vector2 position;
    Vector2 size;
    bool active;
    Color color;
    int squareSize, screenWidth, screenHeight;
};
Food::Food(int squareSize, int screenWidth, int screenHeight)
    : squareSize(squareSize), screenWidth(screenWidth), screenHeight(screenHeight) {
    size = { (float)squareSize, (float)squareSize };
    color = RED;
    active = false;
}

void Food::Spawn(const Vector2* avoidPositions, int count) {
    active = true;
    Vector2 offset = { (float)(screenWidth % squareSize), (float)(screenHeight % squareSize) };

    bool valid;
    do {
        valid = true;
        position = {
            (float)(GetRandomValue(0, (screenWidth / squareSize) - 1) * squareSize + offset.x / 2),
            (float)(GetRandomValue(0, (screenHeight / squareSize) - 1) * squareSize + offset.y / 2)
        };

        for (int i = 0; i < count; ++i) {
            if (position.x == avoidPositions[i].x && position.y == avoidPositions[i].y) {
                valid = false;
                break;
            }
        }
    } while (!valid);
}

void Food::Draw() {
    if (active) DrawRectangleV(position, size, color);
}

bool Food::IsActive() const { return active; }
void Food::Deactivate() { active = false; }
const Vector2& Food::GetPosition() const { return position; }
const Vector2& Food::GetSize() const { return size; }
