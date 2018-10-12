#include "RNK.h"
#include "DNK.h"
#include <unordered_map>
#include <algorithm>
#include <gtest/gtest.h>
using namespace std;
using namespace biology_lib;
TEST(Mem, push_back) {

	_CrtMemState stady1 = { 0 };
	_CrtMemState stady2 = { 0 };

	_CrtMemCheckpoint(&stady1);

	RNK* rnk = new RNK(1, T);
	for (int i = 0; i < 500000; i++) {
		rnk->push_back(T);
	}

	delete rnk;

	_CrtMemCheckpoint(&stady2);

	_CrtMemState result = { 0 };

	EXPECT_FALSE(_CrtMemDifference(&result, &stady1, &stady2));
}

TEST(Operators, skobonki) {
	RNK rnk(5000000);
	for (int i = 0; i < 5000000; i++) {
		rnk[i] = G;
	}
	for (int i = 0; i < 5000000; i++) {
		EXPECT_EQ(G, rnk[i]);
	}
}

TEST(Operators, const_scobonki) {
	const RNK rnk(G, 5000000);
	for (int i = 0; i < 5000000; i++) {
		EXPECT_EQ(G, rnk[i]);
	}
}

TEST(Methods, push_back) {
	RNK rnk(1, T);
	for (int i = 0; i < 500000; i++) {
		rnk.push_back(T);
	}
	
	for (int i = 0; i < 500000; i++) {
		EXPECT_EQ(T, rnk[i]);
	}
}

TEST(Operators, eq) {
	RNK rnk1(5, A, G, C, T, A);
	RNK rnk2(5, A, G, C, T, A);
	EXPECT_TRUE(rnk1 == rnk2);
	RNK rnk3(4, A, A, G, G);
	EXPECT_FALSE(rnk1 == rnk3);
	RNK rnk4(5, A, T, C, G, A);
	EXPECT_TRUE(rnk1 == rnk4);
	const RNK rnk5(5, A, T, T,  G, A);
	EXPECT_FALSE(rnk1 == rnk5);
}

TEST(Methods, reverse) {
	RNK rnk(1, A);
	for (int i = 0; i < 500000/4; i+=4) {
		rnk.push_back(A);
		rnk.push_back(G);
		rnk.push_back(C);
		rnk.push_back(T);
	}

	rnk.reverse();

	for (int i = 0; i < 500000 / 4; i += 4) {
		EXPECT_EQ(rnk[i], T);
		EXPECT_EQ(rnk[i+1], C);
		EXPECT_EQ(rnk[i+2], G);
		EXPECT_EQ(rnk[i+3], A);
	}

}

TEST(Operators, plus) {
	RNK rnk1(1, A);
	RNK rnk2(1, A);
	for (int i = 0; i < 500000; i += 4) {
		rnk1.push_back(A);
		rnk1.push_back(G);
		rnk1.push_back(C);
		rnk1.push_back(T);
		rnk2.push_back(A);
		rnk2.push_back(G);
		rnk2.push_back(C);
		rnk2.push_back(T);
	}

	RNK rnk = rnk1 + rnk2;

	EXPECT_EQ(rnk.get_length(), 1000002);
}

TEST(Operators, NOT) {
	RNK rnk1;
	for (int i = 0; i < 500000; i += 4) {
		rnk1.push_back(A);
		rnk1.push_back(G);
		rnk1.push_back(C);
		rnk1.push_back(T);
	}
	rnk1 = !rnk1;
	for (int i = 0; i < 500000; i += 4) {
		EXPECT_EQ(rnk1[i], T);
		EXPECT_EQ(rnk1[i + 1], C);
		EXPECT_EQ(rnk1[i + 2], G);
		EXPECT_EQ(rnk1[i + 3], A);
	}
}

TEST(Methods, is_comp) {
	RNK rnk1;
	RNK rnk2;
	for (int i = 0; i < 500000; i += 4) {
		rnk1.push_back(A);
		rnk1.push_back(G);
		rnk1.push_back(C);
		rnk1.push_back(T);
	}
	rnk2 = !rnk1;
	EXPECT_TRUE(rnk2.is_complimentary(rnk1));
}

TEST(Methods, trim) {
	RNK rnk1;
	for (int i = 0; i < 500000; i += 4) {
		rnk1.push_back(A);
		rnk1.push_back(G);
		rnk1.push_back(C);
		rnk1.push_back(T);
	}
	rnk1.trim(25000);
	EXPECT_EQ(rnk1.get_length(), 25000);
}

TEST(Methods, split) {
	RNK rnk1;
	RNK rnk2;
	for (int i = 0; i < 500000; i += 4) {
		rnk1.push_back(A);
		rnk1.push_back(G);
		rnk1.push_back(C);
		rnk1.push_back(T);
		rnk2.push_back(A);
		rnk2.push_back(G);
		rnk2.push_back(C);
		rnk2.push_back(T);
	}

	RNKS rnks = (rnk1+rnk2).split(rnk1.get_length());

	EXPECT_EQ(rnks.first->get_length(), rnk1.get_length());
	EXPECT_EQ(rnks.second->get_length(), rnk2.get_length());
}

TEST(Methods, cardinalityN) {
	RNK rnk1;
	for (int i = 0; i < 500000; i += 4) {
		rnk1.push_back(A);
		rnk1.push_back(G);
		rnk1.push_back(C);
		rnk1.push_back(T);
	}
	EXPECT_EQ(rnk1.cardinality(A), 125000);
	EXPECT_EQ(rnk1.cardinality(G), 125000);
	EXPECT_EQ(rnk1.cardinality(C), 125000);
	EXPECT_EQ(rnk1.cardinality(T), 125000);
}

TEST(Methods, cardinality) {
	RNK rnk1;
	for (int i = 0; i < 500000; i += 4) {
		rnk1.push_back(A);
		rnk1.push_back(G);
		rnk1.push_back(C);
		rnk1.push_back(T);
	}



	unordered_map<Nucleotide, size_t> map = rnk1.cardinality();
	EXPECT_EQ(map[A], 125000);
	EXPECT_EQ(map[G], 125000);
	EXPECT_EQ(map[C], 125000);
	EXPECT_EQ(map[T], 125000);
}

TEST(Operator, get_from_empty) {
	RNK rnk;
	for (int i = -2000; i < 2000; i++) {
		EXPECT_ANY_THROW(rnk[i]);
	}
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();

	system("pause");
	return 0;
}