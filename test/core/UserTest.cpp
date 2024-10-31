#include <gtest/gtest.h>

#include <User.h>

TEST(UserClassTest, initialTest)
{
	User user("Andrei");
	EXPECT_EQ(user.getName(), "Andrei");
}
