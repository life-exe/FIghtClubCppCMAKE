#include "DoodleJump.h"
#include "raylib.h"
#include "Types.h"
#include "Player.h"
#include "PlatformManager.h"
#include "Utils/Math.h"

namespace
{
constexpr ScreenSize c_screenSize{500, 700};

bool isOnPlatformGround(const Rectangle& player, const Rectangle& platform, float yThreshold = 10.0f)
{
    return CheckCollisionRecs(player, platform) && (player.y + player.height <= platform.y + yThreshold);
}

}  // namespace

DoodleJump::DoodleJump()
{
    reset();
}

DoodleJump::~DoodleJump() {}

void DoodleJump::reset()
{
    m_isGameOver = false;
    m_score = 0;
    m_player.reset(new Player(c_screenSize));
    m_platformManager.reset(new PlatformManager(c_screenSize, LifeExe::randomFloat));
}

void DoodleJump::run()
{
    const char* windowTitle = "Doodle Jump";
    InitWindow(c_screenSize.width, c_screenSize.height, windowTitle);
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        SetWindowTitle(TextFormat("%s - %d FPS", windowTitle, GetFPS()));
        if (!m_isGameOver)
        {
            handleInput();
            update();
            draw();
        }
        else
        {
            if (IsKeyDown(KEY_ENTER))
            {
                reset();
            }
            drawGameOver();
        }
    }

    CloseWindow();
}

void DoodleJump::handleInput()
{
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
    {
        m_player->moveLeft(GetFrameTime());
    }

    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
    {
        m_player->moveRight(GetFrameTime());
    }
}

void DoodleJump::update()
{
    m_player->update(GetFrameTime());

    // the player is falling down
    if (m_player->velocityY() > 0.0f)
    {
        for (const auto& platform : m_platformManager->platforms())
        {
            if (isOnPlatformGround(m_player->aabb(), platform))
            {
                m_player->jump();
                break;
            }
        }
    }

    // the player is jumping
    const float screenCenterY = c_screenSize.height * 0.5f;
    if (m_player->y() < screenCenterY)
    {
        const float offsetY = screenCenterY - m_player->y();
        m_player->setY(screenCenterY);
        m_platformManager->applyScroll(offsetY);
        m_score += static_cast<int>(offsetY);
    }

    m_isGameOver = m_player->y() > c_screenSize.height;
}

void DoodleJump::draw()
{
    BeginDrawing();
    ClearBackground(BLACK);

    for (const auto& platform : m_platformManager->platforms())
    {
        DrawRectangleRec(platform, WHITE);
    }

    // DrawRectangleRec(m_player->sweepAABB(), {255, 255, 255, 120});
    DrawRectangleRec(m_player->aabb(), {255, 171, 0, 255});
    DrawRectangleLinesEx(m_player->aabb(), 2, LIGHTGRAY);

    DrawText(TextFormat("Score: %d", m_score), 10, 10, 20, WHITE);
    EndDrawing();
}

void DoodleJump::drawGameOver()
{
    const int gameOverTextWidth = MeasureText("GAME OVER", 70);
    const int gameOverCenterX = (c_screenSize.width - gameOverTextWidth) / 2;

    const char* scoreText = TextFormat("Score: %d", m_score);
    const int scoreTextWidth = MeasureText(scoreText, 50);
    const int scoreCenterX = (c_screenSize.width - scoreTextWidth) / 2;

    BeginDrawing();
    ClearBackground(BLACK);
    DrawText("GAME OVER", gameOverCenterX, c_screenSize.height / 2 - 80, 70, WHITE);
    DrawText(scoreText, scoreCenterX, c_screenSize.height / 2 + 30, 50, WHITE);
    EndDrawing();
}
