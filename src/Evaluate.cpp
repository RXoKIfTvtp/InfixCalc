
#include "Evaluate.h"

const std::string Evaluate::DELIMITER = "\\\\";

void Evaluate::prnt(std::string msg) {
	// std::cout << msg << std::endl;
}

template<typename T>
void Evaluate::prnt(std::vector<T> &v) {
	/*for (int i = 0; i < (int)v.size(); i++) {
		std::cout << v[i];
		std::cout << std::endl;
	}
	std::cout << std::endl;*/
}

template<typename T>
void Evaluate::removeAll(std::vector<T> &haystack, const T &needle) {
	for (typename std::vector<T>::iterator it = haystack.begin(); it != haystack.end();) {
		if (*it == needle) {
			haystack.erase(it);
		} else {
			it++;
		}
	}
}

std::string Evaluate::replaceAll(std::string str, const std::string& from, const std::string& to) {
	size_t start_pos = 0;
	while((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length();
	}
	return str;
}

int Evaluate::count(std::string &haystack, char needle) {
	int r = 0;
	int i;
	for (i = 0; i < (int)haystack.length(); i++) {
		if (haystack[i] == needle) {
			r++;
		}
	}
	return r;
}

std::string Evaluate::to_string(char c) {
	std::string s(1, c);
	return s;
}

template <typename T>
T Evaluate::fromString(std::string &v) {
	if (typeid(T) == typeid(int)) {
		return std::stoi(v);
	} else if (typeid(T) == typeid(double)) {
		return std::stod(v);
	} else if (typeid(T) == typeid(long double)) {
		return std::stold(v);
	} else if (typeid(T) == typeid(float)) {
		return std::stof(v);
	} else if (typeid(T) == typeid(long)) {
		return std::stol(v);
	} else if (typeid(T) == typeid(long long)) {
		return std::stoll(v);
	} else {
		throw std::invalid_argument("Unsupported type");
	}
}

// Explicit instantiation
template op_word Evaluate::fromString<op_word>(std::string &v);

bool Evaluate::isAlpha(std::string &s) {
	int i;
	for (i = 0; i < (int)s.length(); i++) {
		if (!isalpha(s[i])) {
			return false;
		}
	}
	return true;
}

bool Evaluate::isNumber(std::string &s) {
	int c = 0;
	int i;
	for (i = 0; i < (int)s.length(); i++) {
		if (!isdigit(s[i])) {
			if (s[i] == '.' && c == 0) {
				c++;
			} else {
				return false;
			}
		}
	}
	return true;
}

bool Evaluate::isFunction(std::string &s) {
	struct Op::op_struct *op = Op::getop(s);
	if (op != NULL) {
		return (op->op.length() > 1 && (op->prec == 0 || op->prec == 10 || op->prec < 0) && op->eval != NULL);
	}
	return false;
}

bool Evaluate::isOperator(std::string &s) {
	struct Op::op_struct *op = Op::getop(s);
	if (op != NULL) {
		return (op->prec > 0);
	}
	return false;
}

bool Evaluate::isBinary(std::string &s) {
	struct Op::op_struct *op = Op::getop(s);
	if (op != NULL) {
		return op->unary == 0;
	}
	return false;
}

bool Evaluate::isRight(std::string &s) {
	struct Op::op_struct *op = Op::getop(s);
	if (op != NULL) {
		return op->assoc == Op::Association::RIGHT;
	}
	return false;
}

bool Evaluate::isLeft(std::string &s) {
	struct Op::op_struct *op = Op::getop(s);
	if (op != NULL) {
		return op->assoc == Op::Association::LEFT;
	}
	return false;
}

int Evaluate::precedence(std::string &s) {
	struct Op::op_struct *op = Op::getop(s);
	if (op != NULL) {
		return op->prec;
	}
	return -1;
}

bool Evaluate::cmp_lt(int a, int b) {
	return a < b;
}

bool Evaluate::cmp_lte(int a, int b) {
	return a <= b;
}

void Evaluate::popOp(
	std::vector<std::string> &ret,
	std::vector<std::string> &stack_nb,
	std::vector<std::string> &stack_op
) {
	prnt("PopF " + stack_op.back());
	ret.push_back(Evaluate::DELIMITER);
	ret.push_back(stack_op.back());
	stack_op.pop_back();
}

void Evaluate::evaluate(std::string &exp, std::vector<std::string> &r, bool basic) {
	std::string &e = exp;
	
	e = replaceAll(e, ",", "),(");
	
	if (e.find("(),(") != std::string::npos || e.find("),()") != std::string::npos) {
		throw EvalException("Malformed expression. Stray comma?");
	}
	
	int clb = count(e, '(');
	int crb = count(e, ')');
	if (clb > crb) {
		throw EvalException("Malformed expression. Missing closing bracket?");
	}
	if (crb > clb) {
		throw EvalException("Malformed expression. Missing opening bracket?");
	}
	
	std::vector<std::string> stack_nb;
	std::vector<std::string> stack_op;
	std::vector<std::string> &ret = r;
	int l = e.length();
	char c;
	bool push_op = false;
	
	int i;
	for (i = 0; i < l; i++) {
		c = e[i];
		if (isspace(c)) {
			continue;
		}
		if (c == ',') {
			ret.push_back(Evaluate::DELIMITER);
			continue;
		}
		
		std::string str_c = to_string(c);
		push_op = false;
		
		if (str_c.compare("(") == 0) {
			prnt("Push (");
			stack_op.push_back("(");
		} else if (str_c.compare(")") == 0) {
			prnt("Pop1 stack till (");
			// Pop ops from op stack
			while (!stack_op.empty() && stack_op.back() != "(") {
				prnt("Pop2 " + stack_op.back());
				popOp(ret, stack_nb, stack_op);
			}
			if (!stack_op.empty() && stack_op.back() == "(") {
				// Pop open bracket and ignore it
				prnt("Pop3 " + stack_op.back());
				stack_op.pop_back();
			} else {
				throw EvalException("Malformed expression. Stray comma or missing opening bracket?");
			}
			
			bool pf = false;
			int j;
			for (j = i; j < l; j++) {
				if (e[j] == ',') {
					break;
				} else if (e[j] == '(') {
					pf = true;
					break;
				}
			}
			// Pop function from op stack
			if (pf && !stack_op.empty() && isFunction(stack_op.back())) {
				prnt("Pop4 " + stack_op.back());
				popOp(ret, stack_nb, stack_op);
			}
			ret.push_back(Evaluate::DELIMITER);
		} else if (isdigit(c)) {
			// Move digit to output
			if (ret.size() > 0 && isNumber(ret.back())) {
				ret.back() += str_c;
				stack_nb.back() += str_c;
			} else {
				ret.push_back(str_c);
				stack_nb.push_back(str_c);
			}
			prnt("Out " + str_c);
		} else if (c == '.') {
			// Move digit to output
			if (ret.size() > 0 && isNumber(ret.back())) {
				if (count(ret.back(), '.') == 0) {
					ret.back() += str_c;
					stack_nb.back() += str_c;
				} else {
					throw EvalException("Malformed expression. Too many decimals in number?");
				}
			} else {
				ret.push_back(str_c);
				stack_nb.push_back(str_c);
			}
		} else if (isalpha(c)) {
			// Push function name to op stack
			int j;
			std::string func = "";
			for (j = i; j < l; j++) {
				if (isalpha(e[j])) {
					func += e[j];
					if (isFunction(func)) {
						i += (j - i);
						break;
					}
					// Else just keep reading chars
				} else {
					i += (j - i) - 1;
					break;
				}
			}
			if (isFunction(func)) {
				if (basic && func.compare("sqrt") != 0) {
					throw EvalException("Malformed expression. Use of advanced functions in basic expression.");
				}
				prnt("push " + func);
				stack_op.push_back(func);
			} else if (isOperator(func)) {
				str_c = func;
				push_op = true;
			} else {
				throw EvalException("Malformed expression. Unexpected token \"" + func + "\"");
			}
		} else if (isOperator(str_c)) {
			push_op = true;
		} else {
			throw EvalException("Malformed expression. Unknown operator \"" + str_c + "\"");
		}
		
		if (push_op) {
			prnt("Try push: " + str_c);
			
			int ops = 0;
			int j;
			for (j = 0; j < (int)stack_op.size(); j++) {
				std::string temp = stack_op[stack_op.size() - 1 - j];
				if (temp == "(") {
					break;
				}
				ops++;
			}
			
			prnt("STACK OPS: " + std::to_string(ops));
			prnt("STACK NB SIZE: " + std::to_string(stack_nb.size()));
			
			if (str_c == "-") {
				if (
					(ops == 0 && stack_nb.size() == 0) ||
					(ops == 1 && stack_nb.size() % 2 == 1 && isBinary(stack_op.back()))
				) {
					str_c = "_";
					prnt("Changing op from - to _.");
				}
			}
			
			bool (*cmp)(int, int);
			if (isRight(str_c)) {
				cmp = cmp_lt;
			} else {
				cmp = cmp_lte;
			}
			
			// Pop high-precedence operators from stack and move to output
			while (!stack_op.empty() && cmp(precedence(str_c), precedence(stack_op.back()))) {
				prnt("Pop5 " + stack_op.back());
				popOp(ret, stack_nb, stack_op);
			}
			
			// Push new op to op stack
			ret.push_back(Evaluate::DELIMITER);
			stack_op.push_back(str_c);
			prnt("Pushed " + stack_op.back());
		}
	}
	
	// Pop remaining operators from op stack
	while (!stack_op.empty()) {
		if(stack_op.back().compare("(") == 0) {
			throw EvalException("Malformed expression. Missing closing bracket?");
		}
		//std::cout << "Pop " + stack_op.back() << std::endl;
		popOp(ret, stack_nb, stack_op);
	}
	
	Evaluate::removeAll<std::string>(ret, Evaluate::DELIMITER);
}

op_word Evaluate::evaluate(std::vector<std::string> &e, std::vector<std::string> &s) {
	std::string t;
	op_word a, b;
	
	try {
		while (e.size() > 0) {
			t = e.front();
			e.erase(e.begin()); // erase element 1 at index 0
			if (Evaluate::isNumber(t)) {
				s.push_back(t);
				//std::cout << "push: " + t << std::endl;
			} else {
				Op::op_struct *t_op = Op::getop(t);
				if (t_op != NULL && t_op->eval != NULL) {
					if (t_op->unary && s.size() > 0) {
						//std::cout << "op: " + t << std::endl;
						//std::cout << "type: unary" << std::endl;
						//std::cout << "arg1:" + s.top() << std::endl;
						a = fromString<op_word>(s.back());
						s.pop_back();
						b = 0;
					} else if (!(t_op->unary) && s.size() > 1) {
						//std::cout << "op: " + t << std::endl;
						//std::cout << "type: binary" << std::endl;
						//std::cout << "arg2:" + s.top() << std::endl;
						b = fromString<op_word>(s.back());
						s.pop_back();
						//std::cout << "arg1:" + s.top() << std::endl;
						a = fromString<op_word>(s.back());
						s.pop_back();
					} else {
						throw EvalException("Malformed expression. Extra operator or missing operand?");
					}
					std::string res = std::to_string(t_op->eval(a, b));
					prnt("ret:" + res);
					s.push_back(res);
				} else {
					throw EvalException("Malformed expression. \"" + t + "\" is not a valid operator?");
				}
			}
		}
	} catch (std::invalid_argument &e) {
		throw EvalException("Malformed expression. " + t + " is not a valid token?");
	}
	
	if (s.size() == 1) {
		return fromString<op_word>(s.back());
	} else {
		throw EvalException("Malformed expression. Too many operands?");
	}
}

op_word Evaluate::evaluate(std::string &s, bool basic) {
	std::vector<std::string> tmp;
	Evaluate::evaluate(s, tmp, basic);
	
	std::vector<std::string> stk;
	return Evaluate::evaluate(tmp, stk);
}

