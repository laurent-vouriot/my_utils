/**____________________________________________________________________________
                           _   _ _      
                          | | (_) |     
 _ __ ___  _   _     _   _| |_ _| |___  
| '_ ` _ \| | | |   | | | | __| | / __| 
| | | | | | |_| |   | |_| | |_| | \__ \
|_| |_| |_|\__, |    \__,_|\__|_|_|___/ 
            __/ |                       
           |___/                        

 my_utils/trace.hpp
 Laurent VOURIOT
 Fall 2021 

 ____________________________________________________________________________

 Trace functions and macros for debug purposes 

 ____________________________________________________________________________

 ______________________________________________________________________________*/
#ifndef TRACE_HPP
#define TRACE_HPP 

/**
 * macro TRACE
 * returns a string with trace informations such as the : 
 * - the function name
 * - the file name 
 * - the line 
 *  where the macro was called.
 */
#define TRACE trace(__func__, __FILE__, __LINE__)

/**
 * macro TEST_TRACE
 * returns a string with trace informations and tests informations such as : 
 * - the test name
 * - the file name
 * - the line number
 * - the suit name
 *	This macro is used in test cases so it contains test case trace infos.
 */
#define TEST_TRACE(test_name, suit_name) test_trace(test_name, __FILE__,  \
													__LINE__, suit_name)

/**
 * function trace 
 * 
 * :param: (const char*) function_name
 * :param: (const char*) file_name
 * :param: (unsigned)    line_number 
 *
 * :returns: (string) a string containing the trace infos 
 */
std::string trace(const char* function_name, const char* file_name, 
						const unsigned line_number) {
	return "\n\tin function : " + std::string(function_name)   +
		   "\n\tin file : "     + std::string(file_name)	   +
		   "\n\tat line : "		+ std::to_string(line_number);
}// print_trace


/*
 *	function test_trace 
 *	to be called in test cases it returns the test name and the test suit
 *	in addition of the other informations.
 *
 *	:param: (const char*) test_name
 *	:param: (const char*) file_name
 *	:param: (unsigned) line_number 
 *	:param: (const char*) suit_name
 *  
 *  :returns: (string) a string containg the test trace infos.
 */
std::string test_trace(const char* test_name, const char* file_name, 
					   const unsigned &line_number, const char* suit_name)  {
	return "\n\tin test : " + std::string(test_name)   +
		   "\n\tin file : " + std::string(file_name)   +
		   "\n\tat line : "	+ std::to_string(line_number) + 
		   "\n\tin suit : "	+ std::string(suit_name); 

}// print_test_trace() 

#endif // TRACE_HPP 
