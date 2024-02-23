
#ifndef EVAL_H
#define EVAL_H

#include <string>
#include <cstdlib>
#include <cmath>

#include "EvalException.h"

typedef double op_word;

/**
 * @class Op
 * @file Op.h
 * @brief A class that holds the operations that can be applied to operands in a math expression.
**/
class Op {
private:

	/**
	 * @brief Applies a unary minus operator to a, then returns the result
	 * @param a the variable to apply the operation to
	 * @param b Not used.
	 * @return The result of applying the operation
	**/
	static op_word uminus(op_word a, op_word b);
	
	/**
	 * @brief Applies a exponent operator to a and b, then returns the result
	 * @param a The base
	 * @param b The power
	 * @return The result of applying the operation
	**/
	static op_word exp(op_word a, op_word b);
	
	/**
	 * @brief Applies a multiplication operator to a and b, then returns the result
	 * @param a A number
	 * @param b A second number
	 * @return The result of applying the operation
	**/
	static op_word mul(op_word a, op_word b);
	
	/**
	 * @brief Applies a division operator to a and b, then returns the result
	 * @param a The dividend
	 * @param b The divisor
	 * @return The result of applying the operation
	 * @throws EvalException if the divisor is zero
	**/
	static op_word div(op_word a, op_word b);
	
	/**
	 * @brief Applies a modulus operator to a and b, then returns the result
	 * @param a The dividend
	 * @param b The divisor
	 * @return The result of applying the operation
	 * @throws EvalException if the divisor is zero
	**/
	static op_word mod(op_word a, op_word b);
	
	/**
	 * @brief Applies a addition operator to a and b, then returns the result
	 * @param a A number
	 * @param b A second number
	 * @return The result of applying the operation
	**/
	static op_word add(op_word a, op_word b);
	
	/**
	 * @brief Applies a subtraction operator to a and b, then returns the result
	 * @param a A number
	 * @param b A second number
	 * @return The result of applying the operation
	**/
	static op_word sub(op_word a, op_word b);
	
	/**
	 * @brief Evaluates the sine of a, then returns the result
	 * @param a A number in radians
	 * @param b Not used
	 * @return The result of applying the operation
	 * @see deg() and rad()
	**/
	static op_word sin(op_word a, op_word b);
	
	/**
	 * @brief Evaluates the cosine of a, then returns the result
	 * @param a A number in radians
	 * @param b Not used
	 * @return The result of applying the operation
	 * @see deg() and rad()
	**/
	static op_word cos(op_word a, op_word b);
	
	/**
	 * @brief Evaluates the tangent of a, then returns the result
	 * @param a A number in radians
	 * @param b Not used
	 * @return The result of applying the operation
	 * @see deg() and rad()
	**/
	static op_word tan(op_word a, op_word b);
	
	/**
	 * @brief Determines the larger of two numbers a and b, then returns the result
	 * @param a A number
	 * @param b A second number
	 * @return The result of applying the operation
	**/
	static op_word max(op_word a, op_word b);
	
	/**
	 * @brief Determines the smaller of two numbers a and b, then returns the result
	 * @param a A number
	 * @param b A second number
	 * @return The result of applying the operation
	**/
	static op_word min(op_word a, op_word b);
	
	/**
	 * @brief Determines the floor of a, then returns the result
	 * @param a A number
	 * @param b Not used
	 * @return The result of applying the operation
	**/
	static op_word floor(op_word a, op_word b);
	
	/**
	 * @brief Determines the ceil of a, then returns the result
	 * @param a A number
	 * @param b Not used
	 * @return The result of applying the operation
	**/
	static op_word ceil(op_word a, op_word b);
	
	/**
	 * @brief Converts a (a value in degrees) to its equivalent in radians
	 * @param a the variable to apply the operation to
	 * @param b Not used.
	 * @return The result of applying the operation
	**/
	static op_word rad(op_word a, op_word b);
	
	/**
	 * @brief Converts a (a value in radians) to its equivalent in degrees
	 * @param a the variable to apply the operation to
	 * @param b Not used.
	 * @return The result of applying the operation
	**/
	static op_word deg(op_word a, op_word b);
	
	/**
	 * @brief Determines the square root of a, then returns the result
	 * @param a the variable to apply the operation to
	 * @param b Not used.
	 * @return The result of applying the operation
	**/
	static op_word sqrt(op_word a, op_word b);
	
	/**
	 * @brief Returns a random number between a and b (both inclusive)
	 * @param a The lower limit
	 * @param b The upper limit
	 * @return A random number between a and b (both inclusive)
	**/
	static op_word rnd(op_word a, op_word b);
public:

	/**
	 * @brief Used to represent the directional association of operators
	**/
	enum Association {
		NONE = 0,
		LEFT,
		RIGHT
	};
	
	/**
	 * @brief A struct to contain all info about an operator
	 */
	struct op_struct {
		std::string op;
		int prec;
		enum Association assoc;
		int unary;
		op_word (*eval)(op_word a, op_word b);
	};
	
private:

	/**
	 * @brief A table containing all the operations
	 * @see op_struct
	**/
	static struct op_struct ops[22];
	
public:

	/**
	 * @brief Returns a struct containing all info about an operator
	 * @param op A string representing the operator to look for
	 * @return An op_struct if the operator is found, otherwise NULL
	 * @see op_struct
	**/
	static struct op_struct *getop(std::string &op);
};

#endif /* EVAL_H */

