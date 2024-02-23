
#ifndef EVAL_EXCEPTION_H
#define EVAL_EXCEPTION_H

#include <string>
#include <cstring>
#include <exception>

/**
 * @class EvalException
 * @file EvalException.h
 * @brief A custom exception that may be thrown when evaluating a math expression string
**/
class EvalException : public std::exception {
private:
	
	/**
	 * @brief A custom message describing the evaluation error
	**/
	char *msg;
	
	/**
	 * @brief Default constructor is not used
	**/
	EvalException();
public:
	
	/**
	 * @brief
	 * @param s The custom message describing the evaluation error
	**/
	EvalException(std::string msg);
	
	/**
	 * @brief Overridden from base class
	 * @return A character pointer to a message describing the evaluation error
	**/
	char *what();
	
	/**
	 * @brief Destructor. Releases any resources used.
	**/
	~EvalException();
};

#endif /* EVAL_EXCEPTION_H */

