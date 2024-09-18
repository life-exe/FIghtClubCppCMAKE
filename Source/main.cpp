#include "Game/Game.h"
#include "Game/Character.h"
#include <string>
#include <format>
#include <memory>
#include "raylib.h"

using namespace LifeExe;

enum class Margin
{
    Left,
    Right
};

struct HeroInfoPosition
{
    const int x;
    const int y;
    const int healthTextOffset;
    const int healthBarOffset;
    const Margin margin;
};

class HeroInfoDrawer
{
public:
    HeroInfoDrawer(const HeroInfoPosition& position) : m_position(position) {}

    void draw(std::shared_ptr<Character> hero, int screenWidth) const
    {
        const int x = calculateXPosition(hero->name(), screenWidth);
        const std::string health = std::format("{}", hero->health());

        DrawText(hero->name(), x, m_position.y, c_nameFontData.size, c_nameFontData.color);
        DrawText(health.c_str(), x, m_position.y + m_position.healthTextOffset, c_healhTextFontData.size, c_healhTextFontData.color);
        DrawRectangle(x, m_position.y + m_position.healthBarOffset, c_healthBarSize.width * hero->healthPercent(), c_healthBarSize.height,
            c_healhBarColor);
    }

private:
    struct FontData
    {
        const int size;
        const Color color;
    };

    struct HealthBarSize
    {
        const int width;
        const int height;
    };

    const HeroInfoPosition m_position;
    const FontData c_nameFontData{20, MAROON};
    const FontData c_healhTextFontData{60, LIGHTGRAY};
    const Color c_healhBarColor{GREEN};
    HealthBarSize c_healthBarSize{150, 20};

    int calculateXPosition(const char* name, int screenWidth) const
    {
        const int textWidth = MeasureText(name, c_nameFontData.size);
        if (m_position.margin == Margin::Right)
        {
            return screenWidth - m_position.x - textWidth;
        }
        return m_position.x;
    }
};

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Fight Club Game");
    SetTargetFPS(60);

    std::unique_ptr<Game> fightClubGame = std::make_unique<Game>();

    double startTime = GetTime();

    const HeroInfoDrawer hero1Drawer(HeroInfoPosition{90, 175, 25, 85, Margin::Left});
    const HeroInfoDrawer hero2Drawer(HeroInfoPosition{90, 175, 25, 85, Margin::Right});

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(DARKBLUE);

        const std::string roundMsg = std::format("Round {}\n\n", fightClubGame->round());
        DrawText(roundMsg.c_str(), 10, 10, 20, LIGHTGRAY);

        {
            const int fontSize = 20;
            const std::string attackMsg =
                std::format("{} attacks {}\n\n", fightClubGame->attacker()->name(), fightClubGame->defender()->name());
            const int textWidth = MeasureText(attackMsg.c_str(), fontSize);

            DrawText(attackMsg.c_str(), (screenWidth - textWidth) / 2, 100, fontSize, LIGHTGRAY);
        }

        hero1Drawer.draw(fightClubGame->hero1(), screenWidth);
        hero2Drawer.draw(fightClubGame->hero2(), screenWidth);

        EndDrawing();

        if (fightClubGame->running())
        {
            if (GetTime() - startTime > 1.0)
            {
                startTime = GetTime();
                fightClubGame->update();
            }
        }
        else
        {
            const int fontSize = 20;
            const auto gameOver = fightClubGame->gamestate() == GameState::GameOver;
            const std::string gameOverMsg =
                gameOver ? std::format("GAME OVER, {} wins\n\n", fightClubGame->attacker()->name()) : "Friendship wins!";

            const int textWidth = MeasureText(gameOverMsg.c_str(), fontSize);
            DrawText(gameOverMsg.c_str(), (screenWidth - textWidth) / 2, 350, fontSize, PINK);
        }

        if (IsKeyDown(KEY_ENTER))
        {
            fightClubGame.reset(new Game());
        }
    }

    return EXIT_SUCCESS;
}
