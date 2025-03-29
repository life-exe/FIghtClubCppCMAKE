#include "gtest/gtest.h"
#include "Types.h"
#include "Player.h"
#include "PlatformManager.h"

namespace
{
int randFuncIndex = 0;
float mockRandomFuncFromArray(float min = 0.0f, float max = 0.0f)
{
    const std::vector<float> randomValues = {10.0f, 20.0f, 30.0f, 40.0f, 50.0f, 60.0f, 70.0f, 80.0f, 90.0f, 100.0f};
    return randomValues[(randFuncIndex++) % randomValues.size()];
}
}  // namespace

TEST(PlayerTest, JumpVelocityShouldBeSetCorrectly)
{
    const ScreenSize screenSize{500, 700};
    Player::Config config;
    config.jumpVelocityY = 913.0f;
    Player player(screenSize, config);
    player.jump();

    ASSERT_EQ(player.velocityY(), config.jumpVelocityY);
}

TEST(PlayerTest, PlayerShouldFallUnderTheGravity)
{
    const ScreenSize screenSize{500, 700};
    Player::Config config;
    Player player(screenSize, config);

    player.update(1.0f);

    const float initialY = screenSize.height * 0.5f - config.initialOffsetY;
    ASSERT_EQ(player.y(), initialY + config.gravity);
}

TEST(PlatformManagerTest, PlatformPositionsShouldBeSetCorrectly)
{
    const ScreenSize screenSize{500, 700};
    PlatformManager platformManager(screenSize, mockRandomFuncFromArray);

    const int platformCount = 10;
    const auto platforms = platformManager.platforms();
    ASSERT_EQ(platforms.size(), platformCount);

    randFuncIndex = 0;
    const float verticalSpacing = static_cast<float>(screenSize.height) / platformCount;
    for (int i = 0; i < platforms.size(); ++i)
    {
        const float expectedX = mockRandomFuncFromArray();
        const float expectedY = i * verticalSpacing + mockRandomFuncFromArray();

        EXPECT_NEAR(platforms[i].x, expectedX, 0.001f);
        EXPECT_NEAR(platforms[i].y, expectedY, 0.001f);
    }
}
