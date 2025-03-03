#pragma once
#include "raylib.h"
#include "Types.h"

class Player
{
public:
    struct Config
    {
        float width{40.0f};
        float height{40.0f};
        float velocityX{240.0f};
        float gravity{400.0f};
        float jumpVelocityY{-500.0f};
        float initialOffsetY{50.0f};
    };

    Player(const ScreenSize& screenSize, const Config& config = {});

    void update(float deltaTime);
    void moveLeft(float deltaTime);
    void moveRight(float deltaTime);
    void jump();
    void setY(float y);

    float y() const;
    float velocityY() const;
    Rectangle aabb() const;
    Rectangle sweepAABB() const;

private:
    const ScreenSize c_screenSize;
    const Config c_config;

    float m_x;
    float m_y;
    float m_previousY;
    float m_velocityY;
};