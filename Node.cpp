#include <math.h>
#include <string>

#include "Node.h"

Node *Node::create(const std::string &symbol, int id) {
    // Check if its an operator or a function
    for (int i = 0; i < TOTAL_OPERATIONS; i++)
    {
        if(MATH_FUNCTION_LIST[i].symbol == symbol) {
            return new FunctionNode(MATH_FUNCTION_LIST[i], id);
        }
    }
    
    // Check if its a variable
    for (int i = 0; i < symbol.length(); i++)
    {
        char c = symbol.at(i);
        if('a' <= c && c <= 'z' || 'A' <= c && c <= 'Z') {
            return new VariableNode(symbol, id);
        }
    }
    
    // Not a variable nor a function -- must be a number
    return new ConstNode(symbol, id);
}

Node::Node(const std::string &symbol, int id)
    :symbol(symbol),
    id(id),
    error("") {};

void Node::set_child(int i, Node *child) {
    children[i] = child;
}

int Node::get_child_count() const {
    return child_count;
}

std::string Node::to_string() const {
    std::string res = symbol;
    for (int i = 0; i < child_count; i++)
        res += " " + children[i]->to_string();
    return res;
}

std::string Node::get_error() const {
    return error;
}

std::vector<std::pair<std::string, int> > Node::get_errors() const {
    std::vector<std::pair<std::string, int> > errors;
    collect_errors(errors);
    return errors;
}

std::set<std::string> Node::get_variables() const {
    std::set<std::string> variables;
    collect_variables(variables);
    return variables;
}

void Node::collect_errors(std::vector<std::pair<std::string, int> > &errors) const {
    if(error != "")
        errors.push_back(std::pair<std::string, int>(error, id));
    for (int i = 0; i < child_count; i++)
    {
        if(children[i] != 0)
            children[i]->collect_errors(errors);
    } 
}

void Node::collect_variables(std::set<std::string> &variables) const {
    for (int i = 0; i < child_count; i++)
    {
        if(children[i] != 0)
            children[i]->collect_variables(variables);
    }
}

bool Node::is_digit(char c) {
    return '0' <= c && c <= '9';
}

bool Node::is_letter(char c) {
    return 'a' <= c && c <= 'z' || 'A' <= c && c <= 'Z';
}

Node *Node::get_rightmost() {
    if(child_count == 0)
        return 0;
    else
        return children[child_count - 1];
}

const Node *Node::get_rightmost() const {
    if(child_count == 0)
        return 0;
    else
        return children[child_count - 1];
}

void Node::replace_rightmost(Node *node) {
    Node *replacement = this;
    Node *next = get_rightmost();
    if(next == 0)
        return;

    while (next->get_rightmost() != 0){
        replacement = next;
        next = next->get_rightmost();
    }

    delete next;
    replacement->children[child_count - 1] = node;
}

Node::~Node()
{
    for (int i = 0; i < child_count; i++)
    {
        delete children[i];
    }
    delete[] children;
}



// Function/operator Node -----------------------------------------
FunctionNode::FunctionNode(const MathFuction &f, int id) 
:Node(f.symbol, id),
f(f) {
    child_count = f.argument_n;
    children = new Node*[child_count];
};

// Checks if mathematical function/operation has all necessary arguments
// If not, creates a default argument. For example expression "+ 2 * 3"
// turns into "+ 2 * 3 1"
void FunctionNode::fix()  {
    for (int i = 0; i < child_count; i++)
    {
        if(children[i] == 0) {
            children[i] = Node::create(f.fix_string);
            error = FUNCTION_ERROR;
        }
        children[i]->fix();
    }
}

float FunctionNode::evaluate(std::map<std::string, int> &values) const {
    float res = 0;
    float *c_res = new float[child_count];
    for (int i = 0; i < child_count; i++)
        c_res[i] = children[i]->evaluate(values);
    
    switch (f.type)
    {
        case add_fun:
            res = c_res[0] + c_res[1];
            break;
        case sub_fun:
            res = c_res[0] - c_res[1];
            break;
        case mul_fun:
            res = c_res[0] * c_res[1];
            break;
        case div_fun:
            res = c_res[0] / c_res[1];
            break;
        case sin_fun:
            res = sin(c_res[0]);
            break;
        case cos_fun:
            res = cos(c_res[0]);
    }
    delete[] c_res;
    return res;
}



// Variable Node ---------------------------------------------------
VariableNode::VariableNode(const std::string &v, int id) :Node(v, id) {
    child_count = 0;
};

// Removes all characters that are not letter or number from the symbol
void VariableNode::fix()  {
    std::string result = "";
    for (int i = 0; i < symbol.length(); i++)
    {
        if(is_digit(symbol.at(i)) || is_letter(symbol.at(i)))
            result += symbol.at(i);
    }
    if(result != symbol)
        error = VARIABLE_ERROR;
    symbol = result;
}

float VariableNode::evaluate(std::map<std::string, int> &values) const {
    return values[symbol];
}

void VariableNode::collect_variables(std::set<std::string> &variables) const {
    variables.insert(symbol);
    Node::collect_variables(variables);
}



// Const Node -------------------------------------------------------
ConstNode::ConstNode(const std::string &c, int id) :Node(c, id) {
    child_count = 0;
};

// Removes all characters that aren't a digit from the symbol
// If no characters are left, then it assigns 0
// Converts symbol to int
void ConstNode::fix()  {
    std::string result = "";
    for (int i = 0; i < symbol.length(); i++)
    {
        if(is_digit(symbol.at(i)))
            result += symbol.at(i);
    }
    if(result == "")
        result = "0";
    if(result != symbol)
        error = CONST_ERROR;
    symbol = result;

    value = to_int(symbol);
}

float ConstNode::evaluate(std::map<std::string, int> &_) const {
    return value;
}

int ConstNode::to_int(std::string str) {
    int result = 0;
    for (int i = 0; i < str.length(); i++)
    {
        int exponent = str.length() - i - 1;
        result += (str.at(i) - '0') * pow(10, exponent);
    }
    return result;
}
