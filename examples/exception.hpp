#ifndef EXCEPTION
#define EXCEPTION

#include <stdexcept>
#include <string>

class MethodException : public std::runtime_error
{
public:
	MethodException(std::string text);
	~MethodException();
private:
	std::string message;
};


class CommandException : public std::runtime_error
{
public:
	CommandException(std::string text);
	~CommandException();
private:
	std::string message;
};

class AcessibilityException : public std::runtime_error
{
public:
	AcessibilityException(std::string text);
	~AcessibilityException();
private:
	std::string message;
};

class ArgumentException : public std::runtime_error
{
public:
	ArgumentException(std::string text);
	~ArgumentException();
private:
	std::string message;
};

class AvailabilityException : public std::runtime_error
{
public:
	AvailabilityException(std::string text);
	~AvailabilityException();
private:
	std::string message;
};

#endif