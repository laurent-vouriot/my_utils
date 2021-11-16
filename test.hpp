/**____________________________________________________________________________

                           _   _ _      
                          | | (_) |     
 _ __ ___  _   _     _   _| |_ _| |___  
| '_ ` _ \| | | |   | | | | __| | / __| 
| | | | | | |_| |   | |_| | |_| | \__ \
|_| |_| |_|\__, |    \__,_|\__|_|_|___/ 
            __/ |                       
           |___/                        
                                        
 my_utils/test.hpp
 Laurent VOURIOT
 Fall 2021  
 
 ____________________________________________________________________________
 Test case and test suit classes for unit tests. A test suit is a set of test
 cases, in each test cases there can be one or more assertions. Each test 
 written by the user is a sub class of the TestCase class.
 ____________________________________________________________________________
 
 usage : 
 
 first you need to create a TestSuit object, then using the TEST macro you can 
 create a sub test case class. Inside the macro you can use assertions T_ASSERTIONS
 macros to test your code. Then inside your main function call the runAllTests() on 
 your suit.
 
 TestSuit suit("my_first_suit"); 
  
 TEST(test_name, suit_name) { 
    T_ASSERT_TRUE(1 == 1);
	T_ASSERT_GT(1, 4);
 }
 
 int main() {
	suit.runAllTests();
 }
 ______________________________________________________________________________*/
#ifndef TEST_HPP
#define TEST_HPP 

#include <string> 
#include <vector>
#include <chrono> 

#include "trace.hpp"  
#include "assert.hpp"

/**
 *	TEST Macro to create a test case, overrides the testCase class
 *	the testBody function is overriden and you put your assertions 
 *	inside 
 *
 *	:param: test_name : name of the test case 
 *	:param: suit_name : name of the suit that contains the test case
 *
 */
#define TEST(test_name, suit) 	   class test_name : public TestCase {				\
								   public:											\
								        test_name(const char* test_name,			\
												  TestSuit &suit)					\
										: TestCase(#test_name) {					\
											suit_name_ = suit.getSuitName();		\
									        suit.add(this);							\
										}											\
								        void testBody();							\
							       }test_name(#test_name, suit);					\
								   void test_name::testBody()

// ____________________________________________________________________________
/**
 *
 * TestCase class
 * base class for tests
 *
 * a test case is made of :
 * - the test name (const char*) 
 * - name of the suits it belongs to (string)
 * - a boolean set to false if there is one assertion that fails
 *
 */ 
class TestCase {
protected:
	const char* test_name_;
	std::string suit_name_;
	bool passed_ = true;
public:
	/** 
	 * virtual destructor to overrides the class
	 */
	virtual ~TestCase() {}

	/*
	 * constructor
	 */ 
	TestCase(const char* test_name) 
		: test_name_(test_name) {}
	
	/**
	 * function hasPassed() 
	 * :returns: (bool) true if all the test have passed
	 *					false otherwise 
	 */ 
	bool hasPassed() { return passed_; }
	
	/**
	 * function testBody()
	 * virtual pure function to be overriden 
	 *
	 * will contain the body of the test with assertions and fixtures 
	 */ 
	virtual void testBody() = 0; 
};

// ____________________________________________________________________________


/**
 * TestSuit class
 * Test suits are vectors of test cases 
 *
 * a test suit is made of : 
 * - a suit name (string)
 * - a vector of test cases (std::vector<TestCase *>)
 * 
 */ 
class TestSuit {
private:
	std::string suit_name_;
	std::vector<TestCase*> tests_;
public:
	/**
	 * constructor
	 */
	TestSuit(std::string suit_name) 
		: suit_name_(suit_name) {}

	/**
	 * function add()
	 * add a test case to the test suit
	 *
	 * :param: (TestCase*) 
	 */
	void add(TestCase* test_case) { tests_.push_back(test_case); }
	
	/**
	 * function runAllTests() 
	 * run all the tests from the test suit and print informations 
	 * about the suit
	 */
	void runAllTests() {

		unsigned passed_tests = 0;
		
		// time duration of the test suits    
		auto start_time = std::chrono::system_clock::now();
		for(auto test : tests_) {
			test->testBody();
			if(test->hasPassed()) { 
				passed_tests++;
			}
		}
		
		std::chrono::duration<double> duration = (std::chrono::system_clock::now() - start_time);
		std::cout << "\n_____________________________________________________________\n" 
			      << "[TEST]\t tests from " << suit_name_ << " ran in : " << duration.count() 
				  << " seconds\n" 
				  << "[TEST]\t " <<  passed_tests << "/" << tests_.size() << " tests passed"
				  << "\n_____________________________________________________________\n";
	}// runAllTests()

	
	/**
	 * function getSuitName() 
	 * this getter is used for the test trace
	 *
	 * :returns: (string) the suit name
	 */
	std::string getSuitName() { return suit_name_; }
};


#endif // TEST_HPP
