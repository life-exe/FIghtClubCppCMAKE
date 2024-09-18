#include <gtest/gtest.h>
#include "Utils/Math.h"
#include "Game/Character.h"

using namespace LifeExe;
TEST(Math, MaxShouldBeCalculatedCorrected)
{
    ASSERT_TRUE(max(3, 0) == 3);
    ASSERT_TRUE(max(-3, 0) == 0);
}

TEST(Character, CharacterShouldTakeDamage)
{
    Character hero("Pacman");
    ASSERT_TRUE(!hero.dead());

    hero.takeDamage(10);
    ASSERT_TRUE(hero.health() == 90);
}

TEST(Character, CharacterCanBeKilled)
{
    Character hero("Pacman");
    ASSERT_TRUE(!hero.dead());

    hero.takeDamage(10000);
    ASSERT_TRUE(hero.dead());
}
