#pragma once

#include "API.h"
#include <memory>

namespace LifeExe
{
class Weapon;

class GAME_API Character
{
public:
    Character(const char* name);
    ~Character();

    const char* name() const;
    bool dead() const;
    int health() const;
    float healthPercent() const;
    bool attack(Character& target);
    void takeDamage(int damage);

private:
    const char* m_name;
    Weapon* m_weapon;

    const int c_maxHealth{100};
    int m_health{c_maxHealth};
};
}  // namespace LifeExe
