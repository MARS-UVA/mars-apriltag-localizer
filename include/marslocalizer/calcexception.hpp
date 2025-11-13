#ifndef MARSLOCALIZER_CALCEXCEPTION_HPP
#define MARSLOCALIZER_CALCEXCEPTION_HPP

#include <stdexcept>
#include <string>

class CalcException : public std::runtime_error {
public:
    explicit CalcException(const std::string& msg)
        : std::runtime_error("calculation failure failure: " + msg) {}
};

#endif // MARSLOCALIZER_CALCEXCEPTION_HPP
