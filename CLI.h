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

class CLI {

public:
    CLI();

    void start();

private:
    Tree *tree;

    void enter();

    void handle_enter(const std::string &args);

    void handle_vars(const std::string &args);

    void handle_print(const std::string &args);

    void handle_comp(const std::string &args);

    void handle_join(const std::string &args);

    void print(const std::string &str);

    void println(const std::string &str);
};