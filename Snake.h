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

Snake::Snake(int maxLength, int squareSize, int screenWidth, int screenHeight)
    : maxLength(maxLength), squareSize(squareSize), screenWidth(screenWidth), screenHeight(screenHeight) {
    body.resize(maxLength);
    previousPositions.resize(maxLength);
    Init();
}

void Snake::Init() {
    tailLength = 1;
    allowMove = false;
    Vector2 offset = { static_cast<float>(screenWidth % squareSize), static_cast<float>(screenHeight % squareSize) };
    for (int i = 0; i < maxLength; ++i) {
        body[i].position = { offset.x / 2, offset.y / 2 };
        body[i].size = { (float)squareSize, (float)squareSize };
        body[i].speed = { (float)squareSize, 0 };
        body[i].color = (i == 0) ? DARKGREEN : GREEN;
        previousPositions[i] = { 0.0f, 0.0f };
    }
}

void Snake::Update() {
    if (IsKeyPressed(KEY_RIGHT) && body[0].speed.x == 0 && allowMove) { body[0].speed = { (float)squareSize, 0 }; allowMove = false; }
    if (IsKeyPressed(KEY_LEFT) && body[0].speed.x == 0 && allowMove) { body[0].speed = { -(float)squareSize, 0 }; allowMove = false; }
    if (IsKeyPressed(KEY_UP) && body[0].speed.y == 0 && allowMove) { body[0].speed = { 0, -(float)squareSize }; allowMove = false; }
    if (IsKeyPressed(KEY_DOWN) && body[0].speed.y == 0 && allowMove) { body[0].speed = { 0, (float)squareSize }; allowMove = false; }

    for (int i = 0; i < tailLength; ++i) previousPositions[i] = body[i].position;

    static int frameCounter = 0; 
    frameCounter++; 

    if ((GetFrameTime() > 0) && (frameCounter % 5 == 0)) {
        for (int i = 0; i < tailLength; ++i) {
            if (i == 0) {
                body[0].position.x += body[0].speed.x;
                body[0].position.y += body[0].speed.y;
                allowMove = true;
            }
            else {
                body[i].position = previousPositions[i - 1];
            }
        }
    }
}

void Snake::Draw() {
    for (int i = 0; i < tailLength; ++i) {
        DrawRectangleV(body[i].position, body[i].size, body[i].color);
    }
}

void Snake::Grow() {
    if (tailLength < maxLength) {
        body[tailLength].position = previousPositions[tailLength - 1];
        tailLength++;
    }
}

bool Snake::CheckSelfCollision() const {
    for (int i = 1; i < tailLength; ++i) {
        if (body[0].position.x == body[i].position.x && body[0].position.y == body[i].position.y)
            return true;
    }
    return false;
}

bool Snake::CheckCollisionWith(const Vector2& pos, const Vector2& size) const {
    return (body[0].position.x < pos.x + size.x &&
        body[0].position.x + body[0].size.x > pos.x &&
        body[0].position.y < pos.y + size.y &&
        body[0].position.y + body[0].size.y > pos.y);
}

const Vector2& Snake::GetHeadPosition() const {
    return body[0].position;
}

