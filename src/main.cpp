
#include <iostream>
#include <limits>
#include <string>
// #include <cstdlib> // exit function prototype

#include "Evaluate.h"
#include "EvalException.h"
#include "Util.h"

/**
 * @brief In basic mode functions, except sqrt, are not allowed
**/
bool basic = false;

/**
 * @brief Performs a test evaluation of a string
 * @param expr The expression to evaluate
 * @param c The expected result
**/
void test_eval(std::string expr, std::string c) {
	std::cout << expr << std::endl;
	try{
		op_word r = Evaluate::evaluate(expr, false);
		std::cout << " = " << r << std::endl;
	} catch (EvalException &ex) {
		std::cout << ex.what() << std::endl;
	} catch (...) {
		std::exception_ptr p = std::current_exception();
		std::cout << (p ? p.__cxa_exception_type()->name() : "null") << std::endl;
	}
	std::cout << "Should be \"" << c << "\"" << std::endl;
	std::cout << std::endl;
}

/**
 * @brief Performs a console evaluation of a string
 * @param s The string to evaluate
 * @param eq if true, prepends an equals sign to the output result (for display purposes)
 * @param basic if true, functions aside from sqrt, will cause an error
**/
void eval(std::string &s, bool eq, bool basic) {
	try{
		op_word r = Evaluate::evaluate(s, basic);
		// std::cout << "\"" << s << "\"" << std::endl;
		if (eq) {
			std::cout << " = ";
		}
		std::cout << r << std::endl;
	} catch (EvalException &ex) {
		std::cout << ex.what() << std::endl;
	} catch (...) {
		std::exception_ptr p = std::current_exception();
		std::cout << "Unexpected exception: " << (p ? p.__cxa_exception_type()->name() : "null") << std::endl;
	}
}

/**
 * @brief Performs many test evaluations
**/
void test() {
	test_eval("23+45*67", "3038");
	test_eval("3 + 4 * 2 / ( 1 - 5 ) ^ 2 ^ 3", "3.000122");
	test_eval("sin ( max ( 2, 3 ) / 3 * 4 )", "-0.756802");
	test_eval("sin ( 4 )", "-0.756802");
	test_eval("sin ( 4 )", "-0.756802");
	test_eval("7.5 / 1.5", "5");
	test_eval("sqrt(7.5 / 1.5 * 7.5 / 1.5)", "5");
	test_eval("max ( - 5 - - 6 , 1 0 - - 1 5 )", "25");
	test_eval("5*(6)", "30");
	test_eval("10mod9", "1");
	test_eval("(10)mod9", "1");
	test_eval("10mod(9)", "1");
	test_eval("(10)mod(9)", "1");
	test_eval("(()(10))mod(())(()9)", "1");
	test_eval("10(mod)9", "Malformed expression. Extra operator or missing operand.");
	test_eval("5*)6", "Malformed expression. Missing opening bracket.");
	test_eval("5*(6", "Malformed expression. Missing closing bracket.");
	test_eval("5..6", "Malformed expression. Too many decimals in number.");
	test_eval("5|6", "Malformed expression. Unknown operator.");
	test_eval("5**6", "Malformed expression. Extra operator or missing operand.");
	test_eval("sqrt 9 mod 5", "3");
	test_eval("sqrt (9) mod 5", "3");
	test_eval("sqrt (9 mod 5)", "2");
}

void exec() {
	std::cout << "Type 'help' to display help, ";
	std::cout << "type 'exit' to quit, ";
	std::cout << "or enter a math expression." << std::endl;
	
	std::string ln;
	while (true) {
		std::cout << std::endl;
		std::cout << " >>> ";
		//std::cin >> ln; // <-- Whitespace breaks this
		std::getline(std::cin,ln); // <-- works with whitespace
		std::cout << std::endl;
		if (std::cin.good()) {
			ln = Util::toLowerCase(ln);
			if (ln.compare("exit") == 0 || ln.compare("quit") == 0 || ln.compare("q") == 0) {
				return; // exit(0);
			} else if (ln.compare("help") == 0 || ln.compare("h") == 0) {
				//std::cout << " >>> Help <<<" << std::endl;
				std::cout << " === Availible basic operations ===" << std::endl;
				std::cout << " _    Unary minus (negative number)" << std::endl;
				std::cout << " +    Addition" << std::endl;
				std::cout << " -    Subtraction" << std::endl;
				std::cout << " *    Multiplication" << std::endl;
				std::cout << " /    Division" << std::endl;
				std::cout << " %    Modulus" << std::endl;
				std::cout << " mod  Modulus" << std::endl;
				std::cout << " ^    Exponent" << std::endl;
				std::cout << " sqrt(x)   The square root of x" << std::endl;
				std::cout << std::endl;
				std::cout << " === Availible advanced functions ===" << std::endl;
				std::cout << " sin(x)    Sin of x" << std::endl;
				std::cout << " cos(x)    Cosine of x" << std::endl;
				std::cout << " tan(x)    Tangent of x" << std::endl;
				std::cout << " floor(x)  Floor of x" << std::endl;
				std::cout << " ceil(x)   Ceil of x" << std::endl;
				std::cout << " max(x,y)  The larger of x and y" << std::endl;
				std::cout << " min(x,y)  The smaller of x and y" << std::endl;
				std::cout << " rad(x)    The radian equivalent of x in degrees" << std::endl;
				std::cout << " deg(x)    The degree equivalent of x in radians" << std::endl;
				std::cout << " rand(x,y) Generates a random number between x and y (both-inclusive)" << std::endl;
				std::cout << std::endl;
				std::cout << " === Commands ===" << std::endl;
				std::cout << " switch    Switches between basic and advanced calc mode." << std::endl;
				std::cout << " show      Shows which mode the calculator is currently in." << std::endl;
				std::cout << " which     Shows which mode the calculator is currently in." << std::endl;
				std::cout << " basic     Set calc mode to basic." << std::endl;
				std::cout << " advanced  Set calc mode to advanced." << std::endl;
				std::cout << " exit      Exit the calculator." << std::endl;
			} else if (ln.compare("clear") == 0 || ln.compare("cls") == 0) {
				#ifdef _WIN32
				system("cls");
				#elif __linux__
				system("clear");
				#endif
			} else if (ln.compare("test") == 0) {
				test();
			} else if (ln.compare("switch") == 0) {
				basic = !basic;
				std::cout << " Mode changed to ";
				if (basic) {
					std::cout << "basic." << std::endl;
				} else {
					std::cout << "advanced." << std::endl;
				}
			} else if (ln.compare("basic") == 0) {
				basic = true;
				std::cout << " Mode changed to basic." << std::endl;
			} else if (ln.compare("advanced") == 0 || ln.compare("adv") == 0 || ln.compare("scientific") == 0) {
				basic = false;
				std::cout << " Mode changed to advanced." << std::endl;
			} else if (ln.compare("show") == 0 || ln.compare("which") == 0) {
				std::cout << " Currently in ";
				if (basic) {
					std::cout << "basic mode." << std::endl;
				} else {
					std::cout << "advanced mode." << std::endl;
				}
			} else {
				eval(ln, true, basic);
			}
		} else {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		// std::cout << std::endl;
	}
}

int main(int argc, char **argv) {
	if (argc > 1) {
		int i;
		for (i = 1; i < argc; i++) {
			std::string s(argv[i]);
			eval(s, false, false);
		}
	} else {
		exec();
	}
	return 0;
}

