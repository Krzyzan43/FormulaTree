#include <iostream>

#include "Tree.h"
#include "Utils.h"

class CLI {
public:
    CLI() :tree(0) {}

    void start() {
        while(true)
            enter();
    }
private:
    Tree *tree;

    void enter() {
        println("");
        std::string input;
        std::getline(std::cin, input);
        std::vector<std::string> command_args = split_string(input, 1);
        if(command_args.size() == 0) {
            return;
        }

        std::string command = command_args[0];
        std::string args = command_args.size() == 2 ? command_args[1] : "";
        if(command == "enter") {
            handle_enter(args);
        } else if(command == "vars") {
            handle_vars(args);
        } else if(command == "print") {
            handle_print(args);
        } else if(command == "comp") {
            handle_comp(args);
        } else if(command == "join") {
            handle_join(args);
        } else {
            println("Unsupported operation");
        }

    }

    void handle_enter(std::string args) {
        if(args == "") {
            println("Missing argument");
            return;
        }

        if(tree != 0)
            delete tree;
        tree = new Tree();
        tree->create(args);
        std::vector<std::string> errors = tree->get_errors();
        if(errors.size() != 0) {
            println("There have been errors.");
            for (int i = 0; i < errors.size(); i++)
                println(errors[i]);
            println("Resulting tree: " +tree->to_string());
        }
    }

    void handle_vars(std::string args) {
        if(args != "") {
            println("Invalid argument");
            return;
        }
        if(tree == 0) {
            println("Tree not created");
            return;
        }

        println("Variables:");
        std::set<std::string> vars = tree->get_vars();
        std::set<std::string>::iterator it, end;
        for(it = vars.begin(), end = vars.end(); it != end; it++) {
            println(*it);
        }
    }

    void handle_print(std::string args) {
        if(args != "") {
            println("Invalid argument");
            return;
        }
        if(tree == 0) {
            println("Tree not created");
            return;
        }

        println(tree->to_string());
    }

    void handle_comp(std::string args) {
        if(tree == 0) {
            println("Tree not created");
            return;
        }
        std::vector<std::string> words = split_string(args);
        std::set<std::string> vars = tree->get_vars();
        if(words.size() != vars.size()){
            println("Invalid argument");
            return;
        }

        bool is_a_number = true;
        std::vector<int> values(words.size());
        for (int i = 0; i < words.size(); i++)
        {
            values[i] = to_int(words[i], is_a_number);
            if(!is_a_number) {
                println("Invalid argument");
                return;
            }
        }
        
        float val = tree->evaluate(values);
        std::cout << "Tree evaluates to: " << val << '\n';
    }

    void handle_join(std::string args) {
        if(args == "") {
            println("Missing argument");
            return;
        }

        Tree *joined_tree = new Tree();
        joined_tree->create(args);
        std::vector<std::string> errors = joined_tree->get_errors();
        if(errors.size() != 0) {
            println("There have been errors.");
            for (int i = 0; i < errors.size(); i++)
                println(errors[i]);
        }

        tree->joinWith(joined_tree);
        println("Current tree: ");
        println(tree->to_string());
    }

    void print(std::string str) {
        std::cout << str;
    }

    void println(std::string str) {
        std::cout << str << std::endl;
    }
};