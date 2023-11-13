#include "Node.h"

Node *Node::create(std::string symbol, int id) {
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

Node::Node(std::string symbol, int id)
    :symbol(symbol),
    id(id),
    error("") {};

void Node::setChild(int i, Node *child) {
    children[i] = child;
}

int Node::get_child_count() {
    return childCount;
}

std::string Node::to_string() {
    std::string res = symbol;
    for (int i = 0; i < childCount; i++)
        res += " " + children[i]->to_string();
    return res;
}

std::string Node::get_error() {
    return error;
}

std::vector<std::pair<std::string, int> > Node::get_errors() {
    std::vector<std::pair<std::string, int> > errors;
    collect_errors(errors);
    return errors;
}

std::set<std::string> Node::get_variables() {
    std::set<std::string> variables;
    collect_variables(variables);
    return variables;
}

void Node::collect_errors(std::vector<std::pair<std::string, int> > &errors) {
    if(error != "")
        errors.push_back(std::pair<std::string, int>(error, id));
    for (int i = 0; i < childCount; i++)
    {
        if(children[i] != NULL)
            children[i]->collect_errors(errors);
    } 
}

void Node::collect_variables(std::set<std::string> &variables) {
    for (int i = 0; i < childCount; i++)
    {
        if(children[i] != NULL)
            children[i]->collect_variables(variables);
    }
}

bool Node::isNumber(char c) {
    return '0' <= c && c <= '9';
}

bool Node::isLetter(char c) {
    return 'a' <= c && c <= 'z' || 'A' <= c && c <= 'Z';
}



// Function/operator Node -----------------------------------------
FunctionNode::FunctionNode(const MathFuction &f, int id) 
:Node(f.symbol, id),
f(f) {
    childCount = f.argument_n;
    children = new Node*[childCount];
};

void FunctionNode::fix()  {
    for (int i = 0; i < childCount; i++)
    {
        if(children[i] == NULL) {
            children[i] = Node::create(f.fix_string);
            error = FUNCTION_ERROR;
        }
        children[i]->fix();
    }
}

float FunctionNode::evaluate(std::map<std::string, int> &values) {
    float res = 0;
    float *c_res = new float[childCount];
    for (int i = 0; i < childCount; i++)
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

Node *Node::get_rightmost() {
    if(childCount == 0)
        return 0;
    else
        return children[childCount - 1];
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
    replacement->children[childCount - 1] = node;
}

// Variable Node ---------------------------------------------------
VariableNode::VariableNode(const std::string &v, int id) :Node(v, id) {
    childCount = 0;
};

void VariableNode::fix()  {
    std::string result = "";
    for (int i = 0; i < symbol.length(); i++)
    {
        if(isNumber(symbol.at(i)) || isLetter(symbol.at(i)))
            result += symbol.at(i);
    }
    if(result != symbol)
        error = VARIABLE_ERROR;
    symbol = result;
}

float VariableNode::evaluate(std::map<std::string, int> &values)  {
    return values[symbol];
}

void VariableNode::collect_variables(std::set<std::string> &variables)  {
    variables.insert(symbol);
    Node::collect_variables(variables);
}



// Const Node -------------------------------------------------------
ConstNode::ConstNode(const std::string &c, int id) :Node(c, id) {
    childCount = 0;
};

void ConstNode::fix()  {
    std::string result = "";
    for (int i = 0; i < symbol.length(); i++)
    {
        if(isNumber(symbol.at(i)))
            result += symbol.at(i);
    }
    if(result == "")
        result = "0";
    if(result != symbol)
        error = CONST_ERROR;
    symbol = result;

    value = to_int(symbol);
}

float ConstNode::evaluate(std::map<std::string, int> &_)  {
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
