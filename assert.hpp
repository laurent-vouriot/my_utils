/**
                           _   _ _      
                          | | (_) |     
 _ __ ___  _   _     _   _| |_ _| |___  
| '_ ` _ \| | | |   | | | | __| | / __| 
| | | | | | |_| |   | |_| | |_| | \__ \
|_| |_| |_|\__, |    \__,_|\__|_|_|___/ 
            __/ |                       
           |___/                        
                                        
 my_utils/assert.hpp 
 Laurent VOURIOT
 Fall 2021
 
 ____________________________________________________________________________

 Assertion structure and macros to assert conditions
 the differents assertions : 

 assert_true(condition) 
 assert_false(condition)
 assert_equals(a, b) : a == b
 assert_not_equals(a, b) : a != b
 assert_gt(a, b) : a > b
 assert_lt(a, b) : a < b
 assert_raises(function, exc, var, var2) : function raises exc with parameters
 var and var2
 ____________________________________________________________________________

 There are two types of macros the normal assertions, and the test assertions. 
 The test assertions are meant to be called in Tests bodies whereas the normal 
 assertions can be called anywhere. The Macros log something only if the ass-
 ertion is false. 
 
*/
#ifndef ASSERT_HPP
#define ASSERT_HPP 

#include <iostream>
#include <vector>

#include "trace.hpp"
#include "log.hpp"


// ASSERTIONS MACROS

/**
 * macro ASSERT_TRUE
 * print assert log and trace if assertion is false
 *
 * :param: (bool) condition
 */
#define ASSERT_TRUE(condition)		if(!Assert::assertTrue(condition)) {	\
										Log::assert(#condition, TRACE);     \
									}								 	    \
/**
 * macro ASSERT_FALSE
 * print assert log and trace if assertion is false
 *
 * :param: (bool) condition
 */
#define ASSERT_FALSE(condition)		if(!Assert::assertFalse(condition)) {  \
										Log::assert(#condition, TRACE);    \
									}
/**
 * macro ASSERT_EQUALS
 * print assert log and trace if assertion is false
 *
 * :param: (T) a
 * :param: (T) b
 */
#define ASSERT_EQUALS(a, b)			if(!Assert::assertEquals(a, b)) {	   \
										Log::assert(#a " == "  #b, TRACE); \
									}
/**
 * macro ASSERT_NOT_EQUALS
 * print assert log and trace if assertion is false
 *
 * :param: (T) a
 * :param: (T) b
 */
#define ASSERT_NOT_EQUALS(a, b)     if(!Assert::assertNotEquals(a, b)) {	\
										Log::assert(#a " != " #b, TRACE);   \
									}
/**
 * macro ASSERT_GT
 * print assert log and trace if assertion is false
 *
 * :param: (T) a
 * :param: (T) b
 */
#define ASSERT_GT(a, b)				if(!Assert::assertGt(a, b)) {	     \
										Log::assert(#a " > " #b, TRACE); \
									}
/**
 * macro ASSERT_LT
 * print assert log and trace if assertion is false
 *
 * :param: (T) a
 * :param: (T) b
 */
#define ASSERT_LT(a, b)				if(!Assert::assertLt(a, b)) {	  \
										Log::assert(#a " < "  #b, TRACE); \
									}
/**
 * macro ASSERT_RAISES
 * print assert log and trace if assertion is false
 *
 * :param: (T) function : function that should raise the exception
 * :param: (T) exc : exception that should be raised
 * :param: (Types...) ... : variadic arguments to pass to function in 
 * order to raise the exception exc
 */
#define ASSERT_RAISES(function, exc, ...)		if(!Assert::assertRaises(function, exc, __VA_ARGS__)) {	    \
													Log::assertRaises(#function, #exc, TRACE, __VA_ARGS__); \
												}								
								
// TEST ASSERTIONS MACROS
// theses macros are meant to be used in test cases, so that we can use the 
// TEST_TRACE macros and set the passed_ attribute to false.
										
#define T_ASSERT_TRUE(condition)		if(!Assert::assertTrue(condition)) {	\
											Log::assert(#condition,				\
														TEST_TRACE(test_name_,	\
														suit_name_.c_str()));	\
											passed_ = false;					\
										}									    \

#define T_ASSERT_FALSE(condition)		if(!Assert::assertFalse(condition)) {	\
											Log::assert(#condition,				\
														TEST_TRACE(test_name_,	\
														suit_name_.c_str()));	\
											passed_ = false;					\
										}									    \

#define T_ASSERT_EQUALS(a, b)   		if(!Assert::assertEquals(a, b)) {	        \
											Log::assert(#a " == " #b,			\
														TEST_TRACE(test_name_,	\
														suit_name_.c_str()));	\
											passed_ = false;					\
										}									    \

#define T_ASSERT_NOT_EQUALS(a, b)		if(!Assert::assertNotEquals(a, b)) {	\
											Log::assert(#a " == " #b,			\
														TEST_TRACE(test_name_,	\
														suit_name_.c_str()));	\
											passed_ = false;					\
										}									    \


#define T_ASSERT_GT(a, b)	       	if(!Assert::assertGt(a, b)) {	            \
											Log::assert(#a " > " #b,			\
														TEST_TRACE(test_name_,	\
														suit_name_.c_str()));	\
											passed_ = false;					\
										}									    \

#define T_ASSERT_LT(a, b)	       	if(!Assert::assertLt(a, b)) {	            \
											Log::assert(#a " < " #b,			\
														TEST_TRACE(test_name_,	\
														suit_name_.c_str()));	\
											passed_ = false;					\
									}										    \

								
#define T_ASSERT_RAISES(function, exc, ...)	 \
									if(!Assert::assertRaises(function, exc, __VA_ARGS__)) {	      \
										Log::assertRaises(#function, #exc, TEST_TRACE(test_name_, \
														  suit_name_.c_str()), __VA_ARGS__);      \
										passed_ = false;									      \
									}	  

/**
 * struct assert 
 * contains all the assertion functions.
 *
 */
struct Assert {
	/**
	 *	function assertTrue()
	 *	static function 
	 *
	 *  condition
	 *
	 *	:param: (bool) condition 
	 *	:returns: (bool) 
	 */
	static bool assertTrue(bool condition) {
		return condition;
	}// asserTrue()
	
	// ----------------------------------------------------------------------------
	
	/**
	 *	function assertFalse()
	 *	static function 
	 *	
	 *	!condition 
	 *
	 *	:param: (bool) condition 
	 *	:returns: (bool) 
	 */
	static bool assertFalse(bool condition) {
		return !condition;
	}// assert_false()

	// ----------------------------------------------------------------------------
	
	/**
	 *	function assertFalse()
	 *	static generic function 
	 *	
	 *	expected == result
	 *
	 *	:param: (T) expected
	 *	:param: (T) result
	 *
	 *	:returns: (bool) 
	 */
	template <typename T>
	static bool assertEquals(T expected, T result) {
		return expected == result;
	}// assert_equals()

	// -----------------------------------------------------------------------------
	
	/**
	 * function assertNotEquals()
	 * static generic function 
	 *
	 * expected != result
	 *
	 * :param: (T) expected
	 * :param: (T) result 
	 *
	 * :returns (bool) 
	 */
	template <typename T>
	static bool assertNotEquals(T expected, T result) {
		return expected != result;
	}// assert_not_equals()

	// -----------------------------------------------------------------------------
	
	/**
	 * function assertGt()
	 * static generic function 
	 *
	 * expected > result
	 *
	 * :param: (T) a
	 * :param: (T) b 
	 *
	 * :returns (bool) 
	 */
	template <typename T> 
	static bool assertGt(T a,T b) {
		return a > b;
	}// assert_gt()  

	// -----------------------------------------------------------------------------
	
	/**
	 * function assertLt()
	 * static generic function 
	 *
	 * expected < result
	 *
	 * :param: (T) a
	 * :param: (T) b 
	 *
	 * :returns (bool) 
	 */
	template <typename T>
	static bool assertLt(T a, T b) {
		return a < b;
	}// assert_lt()

	// -----------------------------------------------------------------------------
	
	/** 
	 * function assertRaises() 
	 * static gerneric variadic function
	 *
	 * function function should raises exception exc with arguments args 
	 * args is variadic parameter so we can an pass unknown amount of parameters 
	 * to function in order to raise the exception 
	 *
	 * :param: (T) function : function that should raise an exception 
	 * :param: (U) exc : exception that should be raised
	 * :param: (Types...) args : variadic arguments
	 */
	template <typename T, typename U, typename... Types>
	static bool assertRaises(T function, U exc, Types... args) {
		bool catched = false;
		try {
			function(args...);		
		} catch(U &exc) {
			catched = true;
		}
		return catched;
	}// catches()
};// Assert

#endif // ASSERT_HPP
