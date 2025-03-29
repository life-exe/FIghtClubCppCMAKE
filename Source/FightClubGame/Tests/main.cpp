#include "Utils/Math.h"
#include "Game/Character.h"
#include <gtest/gtest.h>
#include <iostream>

using namespace LifeExe;

TEST(Math, MaxShouldBeCalculatedCorrectly)
{
    ASSERT_TRUE(max(3, 0) == 3);
    ASSERT_TRUE(max(-3, 0) == 0);
}

TEST(Character, CharacterCanBeKilled)
{
    Character hero("Pacman");
    ASSERT_TRUE(!hero.dead());

    hero.takeDamage(10);
    ASSERT_TRUE(!hero.dead());

    hero.takeDamage(10000);
    ASSERT_TRUE(hero.dead());
}
