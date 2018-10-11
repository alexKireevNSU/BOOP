#include "gtest/gtest.h"
#include "RNK.h"
#include "DNK.h"

TEST(operators, is_eq) {
	RNK* rnk1 = new RNK(5, A, G, C, T);
	RNK* rnk2 = new RNK(5, A, G, C, T);
	bool a = (*rnk1 == (*rnk2));
	ASSERT_TRUE(a);
	/*a = (rnk2 == rnk1);
	EXPECT_TRUE(a);
	RNK rnk3(1, A);
	RNK rnk4(5, A, C, G, T);
	RNK rnk5(5, T, C, G, A);
	a = (rnk1 == rnk5);
	EXPECT_TRUE(a);
	a = (rnk1 == rnk3);
	EXPECT_FALSE(a);
	a = (rnk1 == rnk4);
	EXPECT_FALSE(a);*/
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	system("pause");
}
