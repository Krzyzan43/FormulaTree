#include <iostream>

int TOTAL_OPERATIONS = 6;

enum FunctionType {
    add,
    sub,
    mul,
    div,
    sin,
    cos
};

struct MathFuction {
    const std::string symbol;
    const int argument_n;
    const FunctionType type;
    const std::string fix_string;   

    MathFuction(std::string symbol, FunctionType type, int argument_n, std::string fix_string)
        :symbol(symbol),
        type(type),
        argument_n(argument_n),
        fix_string(fix_string) {};
};

const MathFuction MATH_FUNCTION_LIST[] = {
    MathFuction("+", add, 2, "0"),
    MathFuction("-", sub, 2, "0"),
    MathFuction("*", mul, 2, "1"),
    MathFuction("/", div, 2, "1"),
    MathFuction("sin", sin, 1, "0"),
    MathFuction("cos", cos, 1, "22 / 7"),
};