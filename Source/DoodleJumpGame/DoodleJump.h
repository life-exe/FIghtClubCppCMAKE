#pragma once

#include <memory>

class Player;
class PlatformManager;

class DoodleJump
{
public:
    DoodleJump();
    ~DoodleJump();
    void run();

private:
    int m_score;
    bool m_isGameOver;
    std::unique_ptr<Player> m_player;
    std::unique_ptr<PlatformManager> m_platformManager;

    void reset();
    void handleInput();
    void update();
    void draw();
    void drawGameOver();
};