#include <cassert>
#include "Utils/Math.h"
#include "Game/Character.h"

int main()
{
    using namespace LifeExe;
    assert(max(10, 9) == 10);
    assert(max(1, 9) == 9);
    assert(max(3, 3) == 3);
    assert(max(-3, 3) == 3);
    assert(max(3, -3) == 3);

    Character hero1("Batman");

    hero1.takeDamage(1);
    assert(!hero1.dead());

    hero1.takeDamage(1000);
    assert(hero1.dead());
}