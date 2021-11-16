/**____________________________________________________________________________
                           _   _ _      
                          | | (_) |     
 _ __ ___  _   _     _   _| |_ _| |___  
| '_ ` _ \| | | |   | | | | __| | / __| 
| | | | | | |_| |   | |_| | |_| | \__ \
|_| |_| |_|\__, |    \__,_|\__|_|_|___/ 
            __/ |                       
           |___/                        

 my_utils/log.hpp
 Laurent VOURIOT
 Fall 2021 

 ____________________________________________________________________________

 Simple and thread safe log functions.
 ____________________________________________________________________________

 usage : 
 Log::debug("my debug message : ", var1, var2, "var3");
 Log::assert("var1 == var2", TRACE); 
 Log::exc(caught_exc.what(), TRACE);

_______________________________________________________________________________*/
#ifndef LOG_HPP  
#define LOG_HPP 

#include <iostream> 
#include <mutex> 

#include "trace.hpp"

std::mutex mutex;

/**
* struct log
* containing all the log functions
* 
* most of these functions uses variadic parameters, it used to pass an unknown 
* amount of parameters to a function. so here it's used to print multiple variable
* in a log.
*/ 
struct Log {
	/**
	* log function without parameters
	* called last when there is no more variadic parameters
	*/
	static void log() { std::cout << std::endl; }
	
	// -------------------------------------------------------------------------

	/**
	* log recursive function with variadic parameters to print unknown 
	* amount of parameters	 
	*
	* :param: (T) first 
	* :param: (Types) ...args : variadic parameters
	*/
	template <typename T, typename ...Types>
	static void log(T first, Types ...args ) {
		std::cout << first << " ";	
		log(args ...);
	}// log()

	// -------------------------------------------------------------------------
	
	/**
	* debug log 
	* 
	* :param: (string) message
	* :param: (Types) ...args : variadic parameters
    */
	template <typename... Types>
	static void debug(const std::string &message, Types  ...args) {
		std::lock_guard<std::mutex> lock(mutex);
		std::cout << "[DEBUG]\t" << message;
		log(args...);
	}// debug() 
	
	// -------------------------------------------------------------------------
	
	/**
	* info log
	*
	* :param: (string) message
	* :param: (Types) ...args : variadic parameters 
	*
	*/
	template <typename... Types>
	static void info(const std::string &message, Types... args) {
		std::lock_guard<std::mutex> lock(mutex);
		std::cout << "[INFO]\t" << message;
		log(args...);
	}// info()

	// -------------------------------------------------------------------------
	
	/**
	 * warn log
	 * 
	 * :param: (string) message
	 * :param: (Types) ...args : variadic parameters 
	 */
	template <typename... Types>
	static void warn(const std::string &message, Types... args) {
		std::lock_guard<std::mutex> lock(mutex);
		std::cout << "[WARN]\t" << message;
		log(args...);
	}// warn()

	// -------------------------------------------------------------------------
	
	/**
	 * assert log with trace 
	 * called when an assertions fails
	 *
	 *
	 * :param: (const char*) condition : here we use const char* instead of 
	 * strings because of macros parameters returning const char* 
	 */
	static void assert(const char* condition, const std::string &trace) {
		std::lock_guard<std::mutex> lock(mutex);
		std::cout << "\033[31m[ASSERT] FAILED\t\n\033[0m" 
				  << "\tcondition : " <<  condition
			      << trace << std::endl;
	}// assert() 
	
	// -------------------------------------------------------------------------

	/**
	 * log assertRaises() 
	 * static variadic function 
	 */
	template <typename... Types> 
	static void assertRaises(const char* function_name, const char* exc_name, 
							 const std::string &trace, Types... args) {
		std::lock_guard<std::mutex> lock(mutex);
		std::cout << "\033[31m[ASSERT] FAILED\t\n\033[0m" 
				  << "\t" <<  function_name << " should have raised : " 
				  << exc_name << " with parameters : "; 
		log(args...); 
		std::cout << trace << std::endl;
	}// assert_raises() 
	
	// -------------------------------------------------------------------------
	
	/**
	 * exception log with trace 
	 * print the exception error message and the trace at the moment 
	 * the exception is called. 
	 *
	 */
	static void exc(const std::string &what, const std::string &trace) {
		std::lock_guard<std::mutex> lock(mutex);
		std::cout << "[EXCEPTION] exception caught : " << what
				  << trace << std::endl;
	}// exc()
};

#endif // LOG_HPP 
