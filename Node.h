#include <iostream>
#include <vector>
#include <map>

#include "MathFunctions.h"

const std::string FUNCTION_ERROR = "Invalid number of function arguments.";
const std::string VARIABLE_ERROR = "Illegal characters in variable name.";
const std::string CONST_ERROR = "Illegal characters in number.";

class Node {
public:
    Node(std::string symbol, int id = -1) {
        this->id = id;
        genereate_from_symbol(symbol);
    }

    void setChild(int i, Node *child) {
        children[i] = child;
    }

    int get_child_count() {
        return childCount;
    }

    void print() {
        std::cout << symbol << " ";
        for (int i = 0; i < childCount; i++)
            children[i]->print();
    }

    void fix_children() {
        if(type != function)
            return;

        std::string fix = "";
        for (int i = 0; i < TOTAL_OPERATIONS; i++)
        {
            if(symbol == MATH_FUNCTION_LIST[i].symbol) {
                fix = MATH_FUNCTION_LIST[i].fix_string;
                break;
            }
        }

        for (int i = 0; i < childCount; i++)
        {
            if(children[i] == NULL){
                children[i] = new Node(fix);
                error = FUNCTION_ERROR;
            }
            children[i]->fix_children();
        }
    }

    std::string get_error() {
        return error;
    }

    std::vector<std::pair<std::string, int> > get_errors() {
        std::vector<std::pair<std::string, int> > errors;
        collect_errors(errors);
        return errors;
    }
private:
    enum NodeType {
        function,
        constant,
        variable,
    };

    int childCount;
    std::string symbol;
    Node** children;
    NodeType type;

    int id;
    std::string error;

    void genereate_from_symbol(std::string symbol) {
        // Check if its an operator or a function
        for (int i = 0; i < TOTAL_OPERATIONS; i++)
        {
            if(MATH_FUNCTION_LIST[i].symbol == symbol) {
                childCount = MATH_FUNCTION_LIST[i].argument_n;
                children = new Node*[childCount];
                type = function;
                this->symbol = symbol;
                return;
            }
        }
        
        // Check if its a variable
        for (int i = 0; i < symbol.length(); i++)
        {
            char c = symbol.at(i);
            if('a' <= c && c <= 'z' || 'A' <= c && c <= 'Z') {
                childCount = 0;
                type = variable;
                this->symbol = sanitaze_variable(symbol);
                return;
            }
        }
        
        // Not a variable nor a function -- must be a number
        this->symbol = sanitaze_constant(symbol);
        type = constant;
        childCount = 0;
        return;

    }

    std::string sanitaze_variable(std::string v) {
        std::string result = "";
        for (int i = 0; i < v.length(); i++)
        {
            if(isNumber(v.at(i)) || isLetter(v.at(i)))
                result += v.at(i);
        }
        if(result != v)
            error = VARIABLE_ERROR;
        return result;
    }

    std::string sanitaze_constant(std::string c) {
        std::string result = "";
        for (int i = 0; i < c.length(); i++)
        {
            if(isNumber(c.at(i)))
                result += c.at(i);
        }
        if(result == "")
            result = "0";
        if(result != c)
            error = CONST_ERROR;
        return result;
    }

    bool isNumber(char c) {
        return '0' <= c && c <= '9';
    }

    bool isLetter(char c) {
        return 'a' <= c && c <= 'z' || 'A' <= c && c <= 'Z';
    }

    void collect_errors(std::vector<std::pair<std::string, int> > &errors) {
        if(error != "")
            errors.push_back(std::pair<std::string, int>(error, id));
        for (int i = 0; i < childCount; i++)
        {
            if(children[i] != NULL)
                children[i]->collect_errors(errors);
        } 
    }
};
