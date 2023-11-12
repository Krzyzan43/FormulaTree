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

void Node::print() {
    std::cout << symbol << " ";
    for (int i = 0; i < childCount; i++)
        children[i]->print();
}

std::string Node::get_error() {
    return error;
}

std::vector<std::pair<std::string, int> > Node::get_errors() {
    std::vector<std::pair<std::string, int> > errors;
    collect_errors(errors);
    return errors;
}

std::vector<std::string> Node::get_variables() {
    std::vector<std::string> variables;
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

void Node::collect_variables(std::vector <std::string> &variables) {
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
    throw std::logic_error("Not implemented");
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
    throw std::logic_error("Not implemented");
}
void VariableNode::collect_variables(std::vector<std::string> &variables)  {
    variables.push_back(symbol);
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
    throw std::logic_error("Not implemented");
}

int ConstNode::to_int(std::string str) {
    int result = 0;
    return 5;
}
