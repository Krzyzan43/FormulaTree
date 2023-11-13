#include "Tree.h"

const std::string UNSUPPORTED_OPERATION = "Unsupported operation";
const std::string INVALID_ARGUMENT = "Invalid argument";
const std::string TREE_NOT_CREATED = "Tree not created";
const std::string MISSING_ARGUMENT = "Missing argument";
const std::string CURRENT_TREE = "Current tree: ";
const std::string TREE_ERROR = "There have been errors";
const std::string   ENTER_COMMAND = "enter",
                    VARS_COMMAND = "vars",
                    COMP_COMMAND = "comp",
                    PRINT_COMMAND = "print",
                    JOIN_COMMAND = "join";

// Command line interface, heart of the program
// Handles all input and interfaces the "Tree" class
class CLI {

public:
    CLI();

    // Enters infinite loop of reading commands and executing them with "enter()"
    // Start point of the program
    void start();

    ~CLI();
private:
    Tree *tree;

    // Reads command, splits it into command and arguments
    // And calls appropiate "handle" function with recieved arguments
    void enter();

    // Creates the tree based. Args are expected to be 
    // a formula in reverse notation where symbols are
    // seperated by spaces (i.e. + 2 * a / b sin x)
    void handle_enter(const std::string &args);

    // prints all the variables in current formula
    // args are expected to be empty
    // prints error if args aren't empty
    void handle_vars(const std::string &args);

    // Prints current tree formula in reverse notation
    void handle_print(const std::string &args);

    // Prints result of the computed formula with args
    // being values for variables. Args are expected to
    // be given in order that "handle_vars()" prints vars
    void handle_comp(const std::string &args);

    // Creates tree based on formula in args and joins
    // the root of newly created tree to the rightmost leaf
    // of existing tree
    void handle_join(const std::string &args);

    // prints string
    void print(const std::string &str);

    // prints string and adds a new line
    void println(const std::string &str);
};