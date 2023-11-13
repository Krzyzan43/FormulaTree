#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <math.h>
#include <set>

#include "MathFunctions.h"

const std::string FUNCTION_ERROR = "Invalid number of function arguments.";
const std::string VARIABLE_ERROR = "Illegal characters in variable name.";
const std::string CONST_ERROR = "Illegal characters in number.";

class Node {
public:
    static Node *create(std::string symbol, int id = -1);

    Node(std::string symbol, int id);

    void setChild(int i, Node *child);

    int get_child_count();

    std::string to_string();

    virtual void fix() = 0;

    std::string get_error();

    std::vector<std::pair<std::string, int> > get_errors();

    std::set<std::string> get_variables();

    virtual float evaluate(std::map<std::string, int> &values) = 0;

    void replace_rightmost(Node *replacement);

    Node *get_rightmost();
protected:
    int childCount;
    std::string symbol;
    Node** children;
    std::string error;
    int id;

    void collect_errors(std::vector<std::pair<std::string, int> > &errors);

    virtual void collect_variables(std::set<std::string> &variables);

    static bool isNumber(char c);

    static bool isLetter(char c);
};

class FunctionNode :public Node {
public:
    FunctionNode(const MathFuction &f, int id);

    void fix();

    float evaluate(std::map<std::string, int> &values);
private:
    const MathFuction f;
};

class VariableNode :public Node {
public:
    VariableNode(const std::string &v, int id);

    void fix();

    float evaluate(std::map<std::string, int> &values);
protected:
    void collect_variables(std::set<std::string> &variables);
};

class ConstNode :public Node {
public:
    ConstNode(const std::string &c, int id);

    void fix();

    float evaluate(std::map<std::string, int> &_);
private:
    int to_int(std::string str);
    
    int value;
};