#include "exception.hpp"


MethodException::MethodException(std::string text)
:runtime_error(text)
{
	message = text;
}

MethodException::~MethodException() {}

CommandException::CommandException(std::string text)
:runtime_error(text)
{
	message = text;
}

CommandException::~CommandException() {}

AcessibilityException::AcessibilityException(std::string text)
:runtime_error(text)
{
	message = text;
}

AcessibilityException::~AcessibilityException() {}

ArgumentException::ArgumentException(std::string text)
:runtime_error(text)
{
	message = text;
}

ArgumentException::~ArgumentException() {}

AvailabilityException::AvailabilityException(std::string text)
:runtime_error(text)
{
	message = text;
}

AvailabilityException::~AvailabilityException() {}