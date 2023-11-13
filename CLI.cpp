#include <iostream>

#include "CLI.h"
#include "Utils.h"


CLI::CLI() :tree(0) {}

void CLI::start() {
    while(true)
        enter();
}

void CLI::enter() {
    println("");
    std::string input;
    std::getline(std::cin, input);
    std::vector<std::string> command_args = split_string(input, 1);
    if(command_args.size() == 0) {
        return;
    }

    std::string command = command_args[0];
    std::string args = command_args.size() == 2 ? command_args[1] : "";
    if(command == ENTER_COMMAND) {
        handle_enter(args);
    } else if(command == VARS_COMMAND) {
        handle_vars(args);
    } else if(command == PRINT_COMMAND) {
        handle_print(args);
    } else if(command == COMP_COMMAND) {
        handle_comp(args);
    } else if(command == JOIN_COMMAND) {
        handle_join(args);
    } else {
        println(UNSUPPORTED_OPERATION);
    }

}

void CLI::handle_enter(const std::string &args) {
    if(args == "") {
        println(MISSING_ARGUMENT);
        return;
    }

    if(tree != 0)
        delete tree;
    tree = new Tree();
    tree->create(args);
    std::vector<std::string> errors = tree->get_errors();
    if(errors.size() != 0) {
        println(TREE_ERROR);
        for (int i = 0; i < errors.size(); i++)
            println(errors[i]);
        println(CURRENT_TREE +tree->to_string());
    }
}

void CLI::handle_vars(const std::string &args) {
    if(args != "") {
        println(INVALID_ARGUMENT);
        return;
    }
    if(tree == 0) {
        println(TREE_NOT_CREATED);
        return;
    }

    std::set<std::string> vars = tree->get_vars();
    std::set<std::string>::iterator it, end;
    for(it = vars.begin(), end = vars.end(); it != end; it++) {
        println(*it);
    }
}

void CLI::handle_print(const std::string &args) {
    if(args != "") {
        println(INVALID_ARGUMENT);
        return;
    }
    if(tree == 0) {
        println(TREE_NOT_CREATED);
        return;
    }

    println(tree->to_string());
}

void CLI::handle_comp(const std::string &args) {
    if(tree == 0) {
        println(TREE_NOT_CREATED);
        return;
    }
    std::vector<std::string> words = split_string(args);
    std::set<std::string> vars = tree->get_vars();
    if(words.size() != vars.size()){
        println(INVALID_ARGUMENT);
        return;
    }

    bool is_a_number = true;
    std::vector<int> values(words.size());
    for (int i = 0; i < words.size(); i++)
    {
        values[i] = to_int(words[i], is_a_number);
        if(!is_a_number) {
            println(INVALID_ARGUMENT);
            return;
        }
    }
        
    float val = tree->evaluate(values);
    std::cout << val << '\n';
}

void CLI::handle_join(const std::string &args) {
    if(args == "") {
        println(MISSING_ARGUMENT);
        return;
    }

    Tree *joined_tree = new Tree();
    joined_tree->create(args);
    std::vector<std::string> errors = joined_tree->get_errors();
    if(errors.size() != 0) {
        println(TREE_ERROR);
        for (int i = 0; i < errors.size(); i++)
            println(errors[i]);
    }

    tree->joinWith(joined_tree);
    println(CURRENT_TREE);
    println(tree->to_string());
}

void CLI::print(const std::string &str) {
    std::cout << str;
}

void CLI::println(const std::string &str) {
    std::cout << str << std::endl;
}