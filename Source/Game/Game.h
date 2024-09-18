#pragma once

#include "API.h"
#include <memory>

namespace LifeExe
{
class Character;
using CharacterPtr = std::shared_ptr<Character>;

enum class GameState
{
    Running = 0,
    GameOver,
    FriendshipWins
};

class GAME_API Game final
{
public:
    Game();
    ~Game();

    GameState gamestate() const;
    bool running() const;
    void update();

    int round() const { return m_roundNum; }

    CharacterPtr attacker() { return m_attacker; }
    CharacterPtr defender() { return m_defender; }

    CharacterPtr hero1() { return m_hero1; }
    CharacterPtr hero2() { return m_hero2; }

private:
    CharacterPtr m_hero1;
    CharacterPtr m_hero2;

    CharacterPtr m_attacker;
    CharacterPtr m_defender;

    bool m_running{true};
    GameState m_gameState{GameState::Running};
    int m_roundNum{1};
    bool m_lastFireStatus{true};
};
}  // namespace LifeExe
