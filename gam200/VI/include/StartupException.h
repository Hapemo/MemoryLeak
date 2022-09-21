#pragma once
#include "pch.h"

class StartUpException : public std::exception {
private:
	std::string reason;

public:
	StartUpException(std::string reason) : reason(reason) {};
	
	virtual const char* what() const noexcept { return reason.c_str(); }
};
