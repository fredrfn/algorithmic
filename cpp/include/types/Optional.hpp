#ifndef OPTIONAL_HPP
#define OPTIONAL_HPP

#include "types/Exceptions.hpp"

template <typename T>
class Optional {
    T _value;
    bool _isPresent; 
public:
    Optional() : _isPresent(false) {}
    explicit Optional(T value) : _value(value), _isPresent(true) {}
    T& value() { 
        if (!_isPresent) throw IllegalAccessException(); 
        return value; 
    }
    bool isPresent() { return _isPresent; }
    bool isAbsent() { return !_isPresent; }
    void value(T value) { _value = value; _isPresent = true; }
    void reset() { _isPresent = false; }
};

#endif 