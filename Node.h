#pragma once

#include <vector>
#include <map>
#include <set>

#include "MathFunctions.h"

const std::string FUNCTION_ERROR = ". Invalid number of function arguments.";
const std::string VARIABLE_ERROR = ". Illegal characters in variable name.";
const std::string CONST_ERROR = ". Illegal characters in number.";

class Node {

public:
    static Node *create(const std::string &symbol, int id = -1);

    Node(const std::string &symbol, int id);

    void set_child(int i, Node *child);

    int get_child_count() const;

    std::string to_string() const;

    virtual void fix() = 0;

    std::string get_error() const;

    std::vector<std::pair<std::string, int> > get_errors() const;

    std::set<std::string> get_variables() const;

    virtual float evaluate(std::map<std::string, int> &values) const = 0;

    void replace_rightmost(Node *replacement);

    Node *get_rightmost();

    const Node *get_rightmost() const;

    ~Node();

protected:
    int child_count;
    std::string symbol;
    Node** children;
    std::string error;
    int id;

    void collect_errors(std::vector<std::pair<std::string, int> > &errors) const;

    virtual void collect_variables(std::set<std::string> &variables) const;

    static bool is_digit(char c);

    static bool is_letter(char c);
};




class FunctionNode :public Node {

public:
    FunctionNode(const MathFuction &f, int id);

    void fix();

    float evaluate(std::map<std::string, int> &values) const;

private:
    const MathFuction f;
};




class VariableNode :public Node {

public:
    VariableNode(const std::string &v, int id);

    void fix();

    float evaluate(std::map<std::string, int> &values) const;

protected:
    void collect_variables(std::set<std::string> &variables) const;
};




class ConstNode :public Node {

public:
    ConstNode(const std::string &c, int id);

    void fix();

    float evaluate(std::map<std::string, int> &_) const;

private:
    int to_int(std::string str);
    
    int value;
};