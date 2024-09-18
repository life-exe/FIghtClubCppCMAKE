#include "Character.h"
#include "Weapon.h"
#include "Utils/Math.h"

using namespace LifeExe;

Character::Character(const char* name) : m_name(name)
{
    const int bulletsCount = LifeExe::randomInt(1, 10);
    m_weapon = new Weapon(bulletsCount);
}

Character::~Character()
{
    delete m_weapon;
    m_weapon = nullptr;
}

const char* Character::name() const
{
    return m_name;
}

bool Character::dead() const
{
    return m_health == 0;
}

int Character::health() const
{
    return m_health;
}

float LifeExe::Character::healthPercent() const
{
    return static_cast<float>(m_health) / c_maxHealth;
}

bool Character::attack(Character& target)
{
    const bool fired = m_weapon->fire();
    if (fired)
    {
        const int damage = m_weapon->damage();
        target.takeDamage(damage);
    }

    return fired;
}

void Character::takeDamage(int damage)
{
    m_health -= damage;
    if (m_health < 0) m_health = 0;
}
