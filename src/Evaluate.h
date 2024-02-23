
#ifndef EVALUATE_H
#define EVALUATE_H

#include <iostream>

#include <string>
#include <vector>

#include "Op.h"
#include "EvalException.h"

/**
 * @class Evaluate
 * @file Evaluate.h
 * @brief A class to hold the logic of evaluating infix expressions.
**/
class Evaluate {
private:

	/**
	 * @brief The purpose of the delimiter is to help push multiple numbers on the stack
	**/
	static const std::string DELIMITER;
	
	/**
	 * @brief Used for debugging. Prints a message
	 * @param msg A message to print
	**/
	static void prnt(std::string msg);
	
	/**
	 * @brief Used for debugging. Prints a vector
	 * @param v A vector to print
	**/
	template<typename T>
	static void prnt(std::vector<T> &v);
	
	/**
	 * @brief Removes all occurances of T from a vector
	 * @param haystack The vector to remove from
	 * @param needle The item to remove
	**/
	template<typename T>
	static void removeAll(std::vector<T> &haystack, const T &needle);
	
	/**
	 * @brief Replaces all occurances of a string with another string
	 * @param str The string to search
	 * @param from The substring to find
	 * @param to The string to replace the substring with
	 * @return The new string
	**/
	static std::string replaceAll(std::string str, const std::string& from, const std::string& to);
	
	/**
	 * @brief Counts all occurances of a character in a string
	 * @param haystack The string to search
	 * @param needle the character to search for
	 * @return The count of the needle character in the haystack string
	**/
	static int count(std::string &haystack, char needle);
	
	/**
	 * @brief Converts a character to a string
	 * @param c the character to convert
	 * @return The string equivalent of the character c
	**/
	static std::string to_string(char c);
	
	/**
	 * @brief Attempts to convert the string to a number.
	 * @param v The string to convert
	 * @return A number if the conversion was successful
	 * @throws throw std::invalid_argument if the requested type is not supported
	**/
	template <typename T>
	static T fromString(std::string &v);
	
	/**
	 * @brief Determines if the string contains alpha characters.
	 * @param s The string to check
	 * @return true if the string is valid, otherwise false.
	**/
	static bool isAlpha(std::string &s);
	
	/**
	 * @brief Determines if the string is a number.
	 * @param s The string to check
	 * @return true if the number is valid, otherwise false.
	**/
	static bool isNumber(std::string &s);
	
	/**
	 * @brief Determines if the string is a function.
	 * @param s The string to check
	 * @return true if the function is valid, otherwise false.
	**/
	static bool isFunction(std::string &s);
	
	/**
	 * @brief Determines if the string is an operator.
	 * @param s The string to check
	 * @return true if the operator is valid, otherwise false.
	**/
	static bool isOperator(std::string &s);
	
	/**
	 * @brief Determines if the operator requires two operands. 
	 * @param s The operator to check for being binary
	 * @return true if the operatoris right-associated, otherwise false.
	 * 			a return value of false does not guarantee any other operand count
	**/
	static bool isBinary(std::string &s);
	
	/**
	 * @brief Determines if the operator is right-associated. 
	 * @param s The operator to determine the association of
	 * @return true if the operatoris right-associated, otherwise false.
	 * 			a return value of false does not guarantee left association
	**/
	static bool isRight(std::string &s);
	
	/**
	 * @brief Determines if the operator is left-associated. 
	 * @param s The operator to determine the association of
	 * @return true if the operatoris left-associated, otherwise false.
	 * 			a return value of false does not guarantee right association
	**/
	static bool isLeft(std::string &s);
	
	/**
	 * @brief Determines the precedence of the operator relative to other operators
	 * @param s The operator to determine the precedence of
	 * @return The precedence of the operator if it is valid otherwise -1
	**/
	static int precedence(std::string &s);
	
	/**
	 * @brief A method for determining if a is less than b
	 * @param a any integer
	 * @param b any integer
	 * @return true only if a is less than b, otherwise false
	**/
	static bool cmp_lt(int a, int b);
	
	/**
	 * @brief A method for determining if a is less than or equal to b
	 * @param a any integer
	 * @param b any integer
	 * @return true only if a is less than or equal to b, otherwise false
	**/
	static bool cmp_lte(int a, int b);
	
	/**
	 * @brief Pops one operator from the stack_op stack and appends it to the back of the ret vector
	 * @param ret [Out] The vector to append the operator to
	 * @param stack_nb Not used.
	 * @param stack_op A stack of current operators
	**/
	static void popOp(std::vector<std::string> &ret, std::vector<std::string> &stack_nb, std::vector<std::string> &stack_op);
	
	/**
	 * @brief Evalutes an infix math expression and converts it to postfix.
	 * 			Successful conversion to postfix does not guarantee validity
	 * @param exp [In] The string containing the infix math expression to convert
	 * @param r [Out] The postfix expression equivalent to the infix expression
	 * @param basic if true, functions aside from sqrt, will cause an error
	 * @throws EvalException
	**/
	static void evaluate(std::string &exp, std::vector<std::string> &r, bool basic);
	
	/**
	 * @brief Evalutes a postfix expression and leaves the result in the stack.
	 * 			If the stack contains contain only one item after the evaluation
	 * 			is complete an it was successful, otherwise an EvalException is thrown
	 * @param e [In] The string containing the infix math expression to convert
	 * @param s [Out] The resulting stack
	 * @return The result of an evaluation if successful, otherwise throws an
	 * 			EvalException exception
	 * @throws EvalException
	**/
	static op_word evaluate(std::vector<std::string> &e, std::vector<std::string> &s);
public:

	/**
	 * @brief Evaluates an infix math expression and returns the result
	 * @param s The math expression string to evaluate
	 * @param basic if true, functions aside from sqrt, will cause an error
	 * @return The evaluated result of the expression
	 * @throws EvalException
	**/
	static op_word evaluate(std::string &s, bool basic);
};

#endif /* EVALUATE_H */

