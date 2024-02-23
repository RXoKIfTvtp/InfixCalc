
#include "Op.h"

/**
 * @class Op
 * @file Op.h
 * @brief Contains the definitions for functions/methods in the Op class
**/

#define PI 3.14159265359

op_word Op::uminus(op_word a, op_word b) {
	return (op_word)(-a);
}

op_word Op::exp(op_word a, op_word b) {
	return (op_word)std::pow(a, b);
}

op_word Op::mul(op_word a, op_word b) {
	return (op_word)(a * b);
}

op_word Op::div(op_word a, op_word b) {
	if (b == 0) {
		throw EvalException("Evaluation Error. Division by zero.");
	}
	return (op_word)(a / b);
}

op_word Op::mod(op_word a, op_word b) {
	if (b == 0) {
		throw EvalException("Evaluation Error. Division by zero.");
	}
	// a % b only works for integers
	return (op_word)std::fmod(a, b);
}

op_word Op::add(op_word a, op_word b) {
	return (op_word)(a + b);
}

op_word Op::sub(op_word a, op_word b) {
	return (op_word)(a - b);
}

op_word Op::sin(op_word a, op_word b) {
	return (op_word)std::sin(a);
}

op_word Op::cos(op_word a, op_word b) {
	return (op_word)std::cos(a);
}

op_word Op::tan(op_word a, op_word b) {
	return (op_word)std::tan(a);
}

op_word Op::max(op_word a, op_word b) {
	return (op_word)std::max(a, b);
}

op_word Op::min(op_word a, op_word b) {
	return (op_word)std::min(a, b);
}

op_word Op::floor(op_word a, op_word b) {
	return (op_word)std::floor(a);
}

op_word Op::ceil(op_word a, op_word b) {
	return (op_word)std::ceil(a);
}

op_word Op::rad(op_word a, op_word b) {
	return (op_word)(a * (PI / 180));
}

op_word Op::deg(op_word a, op_word b) {
	return (op_word)(a * (180 / PI));
}

op_word Op::sqrt(op_word a, op_word b) {
	return (op_word)std::sqrt(a);
}

op_word Op::rnd(op_word min, op_word max) {
	static bool is = false;
	if (!is) {
		srand(time(0));
		is = true;
	}
	double p = ((double)rand()) / ((double)RAND_MAX);
	return (op_word)(p * (max - min + 1) + min);
}

Op::op_struct Op::ops[22] = {
	{"\0", 0, NONE, 0, NULL},
	{"_", 12, RIGHT, 1, Op::uminus},
	{"^", 9, RIGHT, 0, Op::exp},
	{"*", 8, LEFT, 0, Op::mul},
	{"/", 8, LEFT, 0, Op::div},
	{"%", 8, LEFT, 0, Op::mod},
	{"mod", 8, RIGHT, 0, Op::mod},
	{"+", 5, LEFT, 0, Op::add},
	{"-", 5, LEFT, 0, Op::sub},
	{"(", 0, NONE, 0, NULL},
	{")", 0, NONE, 0, NULL},
	{"sin", 10, RIGHT, 1, Op::sin},
	{"cos", 10, RIGHT, 1, Op::cos},
	{"tan", 10, RIGHT, 1, Op::tan},
	{"floor", 10, RIGHT, 1, Op::floor},
	{"ceil", 10, RIGHT, 1, Op::ceil},
	{"max", 10, RIGHT, 0, Op::max},
	{"min", 10, RIGHT, 0, Op::min},
	{"rad", 10, RIGHT, 1, Op::rad},
	{"deg", 10, RIGHT, 1, Op::deg},
	{"sqrt", 10, RIGHT, 1, Op::sqrt},
	{"rand", 10, RIGHT, 0, Op::rnd}
};

struct Op::op_struct *Op::getop(std::string &op) {
	int i;
	int l = (int)sizeof(ops) / (int)sizeof(op_struct);
	for (i = 0; i < l; i++) {
		if (ops[i].op == op) {
			return &ops[i];
		}
	}
	return NULL;
}

