#include "Game.h"
#include "Character.h"
#include <utility>

using namespace LifeExe;

Game::Game()
{
    m_attacker = std::make_shared<Character>("Durden");
    m_defender = std::make_shared<Character>("Angel Face");

    m_hero1 = m_attacker;
    m_hero2 = m_defender;
}

Game::~Game() {}

GameState LifeExe::Game::gamestate() const
{
    return m_gameState;
}

bool Game::running() const
{
    return m_gameState == GameState::Running;
}

void Game::update()
{
    if (!running()) return;

    ++m_roundNum;

    const bool fired = m_attacker->attack(*m_defender);
    if (!m_lastFireStatus && !fired)
    {
        m_gameState = GameState::FriendshipWins;
        return;
    }
    m_lastFireStatus = fired;

    if (m_defender->dead())
    {
        m_gameState = GameState::GameOver;
        return;
    }

    std::swap(m_attacker, m_defender);
}
