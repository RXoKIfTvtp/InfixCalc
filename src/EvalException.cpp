
#include "EvalException.h"

// Private and not used
EvalException::EvalException(){}

EvalException::EvalException(std::string msg) {
	this->msg = new char[msg.length() + 1];
	strcpy(this->msg, msg.c_str());
}

char *EvalException::what() {
	return this->msg;
}

EvalException::~EvalException() {
	delete this->msg;
}

