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
