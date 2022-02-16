#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <string>

class Exception {
    std::string _message;
public:
    Exception(std::string message) : _message(std::move(message)) {}
    const std::string& message() { return _message; }
};

class IllegalIndexException : public Exception {
public:
    IllegalIndexException(size_t index) : Exception("IllegalIndex " + std::to_string(index)) {}
};

class IllegalAccessException : public Exception {
public:
    IllegalAccessException() : Exception("IllegalAccessException") {}
};

#endif