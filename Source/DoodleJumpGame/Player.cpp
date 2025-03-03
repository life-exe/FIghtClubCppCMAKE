#include "Player.h"
#include <algorithm>

Player::Player(const ScreenSize& screenSize, const Config& config)  //
    : c_screenSize(screenSize), c_config(config), m_velocityY(0.0f)
{
    m_x = (screenSize.width - c_config.width) * 0.5f;
    m_y = screenSize.height * 0.5f - c_config.initialOffsetY;
    m_previousY = m_y;
}

void Player::update(float deltaTime)
{
    m_previousY = m_y;
    m_velocityY += c_config.gravity * deltaTime;
    m_y += m_velocityY * deltaTime;

    // wrap up player position
    const float playerCenterX = m_x + c_config.width * 0.5f;
    if (playerCenterX >= c_screenSize.width)
    {
        m_x = 0.0f;
    }
    else if (playerCenterX <= 0.0f)
    {
        m_x = c_screenSize.width - c_config.width;
    }
}

void Player::moveLeft(float deltaTime)
{
    m_x -= c_config.velocityX * deltaTime;
}

void Player::moveRight(float deltaTime)
{
    m_x += c_config.velocityX * deltaTime;
}

void Player::jump()
{
    m_velocityY = c_config.jumpVelocityY;
}

void Player::setY(float y)
{
    m_y = y;
}

float Player::y() const
{
    return m_y;
}

float Player::velocityY() const
{
    return m_velocityY;
}

Rectangle Player::aabb() const
{
    return {m_x, m_y, c_config.width, c_config.height};
}

Rectangle Player::sweepAABB() const
{
    const float startY = std::min(m_previousY, m_y);
    const float endY = std::max(m_previousY, m_y);
    return {m_x, startY, c_config.width, endY - startY + c_config.height};
}
