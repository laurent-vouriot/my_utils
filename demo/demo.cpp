/**
 * demo.cpp 
 */
#include <exception>

#include "../test.hpp"

/**
 *  Creating a test suit 
 */
TestSuit demo_suit("demo_suit"); 

/*
 * custom exception to show how assert raises work
 */
struct DivideByZeroExc : std::exception {
	const char* what() const noexcept { return "cannot divide by zero";	}
};

/*
 * simple function to show of test cases work
 */
int multiply(int a,int b) {
	return a * b; 
}

/*
 * simple function to show how test cases work, this function should throw 
 * an exception when you try to divide by zero, (b = 0)
 */
int divide(int a, int b) {
	if(b == 0) {
		DivideByZeroExc exc; 
		throw exc;
	}	
	return a/b;
}

/**
 *	simple explicitly buggy function to show how test cases work
 */ 
int multiply_buggy(int a, int b) {
	// example of use a logs
	Log::debug("multiply_buggy ", a, b); 
	return a + b;
}
 
/*
 * Test case, need a test name and the test suit it belongs to
 */
TEST(testMultiplication, demo_suit) {
	T_ASSERT_EQUALS(multiply(2, 2), 4);
}

/*
 * Test case to test the divide function
 */
TEST(testDivide, demo_suit) {
	T_ASSERT_EQUALS(divide(2, 2), 1);
	DivideByZeroExc exc;
	T_ASSERT_RAISES(divide, exc, 2, 0);
}

/**
 * buggy test suit, all the test from this test suit should fail
 */
TestSuit buggy_suit("buggy_suit");

TEST(testMultiplyBuggy, buggy_suit) { 
	T_ASSERT_EQUALS(multiply_buggy(1, 2), 2); 

}

TEST(testDivide2, buggy_suit) { 
	DivideByZeroExc exc;
	T_ASSERT_RAISES(divide, exc, 2, 3);
}

int main() {
	// run all tests from the different tests suits 
	demo_suit.runAllTests();
	buggy_suit.runAllTests();

	try {
		divide(2, 0); 
	} 
	catch(DivideByZeroExc exc) {
		// log exception with trace 
		Log::exc(exc.what(), TRACE);
	}

	return 0; 
}
