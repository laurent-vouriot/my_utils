/**
 *
 * demo.cpp 
 */
#include <exception>

#include "../my_utils/my_utils.hpp"


TestSuit demo_suit("demo_suit"); 

struct DivideByZeroExc : std::exception {
	const char* what() const noexcept { return "cannot divide by zero";	}
};

int multiply(int a,int b) {
	return a * b; 
}

int divide(int a, int b) {
	DivideByZeroExc exc; 
	if(b == 0)
		throw exc; 
	return a/b;
}

int multiply_buggy(int a, int b) {
	Log::debug("multiply_buggy ", a, b); 
	std::cin.get();
	return a + b;
}
 
TEST(testMultiplication, demo_suit) {
	T_ASSERT_EQUALS(multiply(2, 2), 4);
}

TEST(testDivide, demo_suit) {
	T_ASSERT_EQUALS(divide(2, 2), 1);
	DivideByZeroExc exc;
	T_ASSERT_RAISES(divide, exc, 2, 0);
}

TestSuit buggy_suit("buggy_suit");

TEST(testMultiplyBuggy, buggy_suit) { 
	T_ASSERT_EQUALS(multiply_buggy(1, 2), 2); 

}

TEST(testDivide2, buggy_suit) { 
	DivideByZeroExc exc;
	T_ASSERT_RAISES(divide, exc, 2, 3);
}

int main() {
	demo_suit.runAllTests();
	buggy_suit.runAllTests();

	multiply_buggy(2, 2); 

	try {
		divide(2, 0); 
	} 
	catch(DivideByZeroExc exc) {
		Log::exc(exc.what(), TRACE);
	}

	return 0; 
}



