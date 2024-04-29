//Oscar Li does test coding.
// Use driver.cc to test out your code. If you didn't know,
// gtest suite is on the server.
#include <gtest/gtest.h>
#include <iostream>
using namespace std;

string fizzbuzz(int x) {
	//This won't compile, since it's not returning anything
	if (x < 1 or x > 100) {
		return "Error";
	} else if (x % 3 == 0 and x % 5 == 0) {
		return "Fizzbuzz"; 
	} else if (x % 3 == 0) {
		return "Fizz"; 
	} else if (x % 5 == 0) {
		return "Buzz";
	} else {
		return to_string(x);
	}
}

TEST(Fizzbuzz, GoodTests) {
	EXPECT_EQ(fizzbuzz(15), "Fizzbuzz");
	EXPECT_EQ(fizzbuzz(5), "Buzz");
	EXPECT_EQ(fizzbuzz(3), "Fizz");
	EXPECT_EQ(fizzbuzz(7), "7");
}
TEST(Fizzbuzz, BadTests) {
	EXPECT_EQ(fizzbuzz(-5), "Error");
}
TEST(Fizzbuzz, EdgeTests) {
	EXPECT_EQ(fizzbuzz(101), "Error");
	EXPECT_EQ(fizzbuzz(1), "1");
	EXPECT_EQ(fizzbuzz(100), "Buzz");
	EXPECT_EQ(fizzbuzz(99), "Fizz");
}

/*TEST(Example, GoodTests) {
    EXPECT_EQ(Example, What_you_are_expecting);
}
*/

int main(int argc, char** argv) {
	fizzbuzz(15);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
