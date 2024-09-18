#pragma once

namespace LifeExe
{
class Weapon
{
public:
    Weapon(int bullets);
    bool fire();
    int damage() const;

private:
    int m_bullets{23};
};
}  // namespace LifeExe
