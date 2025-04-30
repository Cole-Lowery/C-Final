#pragma once
#include "raylib.h"
#include <vector>

class Snake {
public:
    Snake(int maxLength, int squareSize, int screenWidth, int screenHeight);

    void Init();
    void Update();
    void Draw();
    void Grow();
    bool CheckSelfCollision() const;
    bool CheckCollisionWith(const Vector2& position, const Vector2& size) const;
    const Vector2& GetHeadPosition() const;

private:
    struct Segment {
        Vector2 position;
        Vector2 size;
        Vector2 speed;
        Color color;
    };

    std::vector<Segment> body;
    std::vector<Vector2> previousPositions;

    int maxLength;
    int squareSize;
    int screenWidth, screenHeight;
    int tailLength;
    bool allowMove;
};
