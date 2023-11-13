#include <sstream>

#include "Tree.h"
#include "Utils.h"

Node *Tree::create_tree(const std::vector<std::string> &words, int &start) {
    if(start >= words.size()) {
        return NULL;
    }

    Node *node = Node::create(words[start], start + 1);
    for (int i = 0; i < node->get_child_count(); i++)
    {
        start++;
        node->setChild(i, create_tree(words, start));
    }
    return node;
}

void Tree::create(const std::string &formula){
    int index = 0;
    std::vector<std::string> words = split_string(formula);
    root = create_tree(words, index);
    root->fix();
}

std::vector<std::string> Tree::get_errors() const {
    std::vector<std::pair<std::string, int> > errors = root->get_errors();
    std::vector<std::string> str_errors(errors.size());

    for (int i = 0; i < errors.size(); i++)
    {
        std::ostringstream ss;
        ss << errors[i].second;
        std::string word_n = ss.str();
        std::string message = errors[i].first;
        std::string err = WORD_ERROR + word_n + message;
        str_errors.push_back(err);
    }

    return str_errors;
}

std::set<std::string> Tree::get_vars() const {
    return root->get_variables();
}

float Tree::evaluate(const std::vector<int> &values) const {
    std::set<std::string> vars = get_vars();
    if(vars.size() != values.size())
        return 0; 

    std::map<std::string, int> map;
    std::set<std::string>::iterator it;
    it = vars.begin();
    for (int  i = 0; i < values.size(); i++)
    {
        map[*it] = values[i];
        it++;
    }
		
    return root->evaluate(map);
}

void Tree::joinWith(Tree *tree) {
    root->replace_rightmost(tree->root);
    tree->root = 0;
    delete tree;
}

std::string Tree::to_string() const {
    return root->to_string();
}