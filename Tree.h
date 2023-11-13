#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#include "Node.h"
#include "Utils.h"

class Tree {
	Node *root;


	Node *create_tree(std::vector<std::string> words, int &start) {
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
public:
	void create(std::string formula){
		int index = 0;
		std::vector<std::string> words = split_string(formula);
		root = create_tree(words, index);
		root->fix();
	}

	std::vector<std::string> get_errors() {
		std::vector<std::pair<std::string, int> > errors = root->get_errors();
		std::vector<std::string> str_errors(errors.size());

		for (int i = 0; i < errors.size(); i++)
		{
			std::ostringstream ss;
			ss << errors[i].second;
			std::string word_n = ss.str();
			std::string message = errors[i].first;
			std::string err = "Error in word number " + word_n + ". " + message;
			str_errors.push_back(err);
		}

		return str_errors;
	}

	std::set<std::string> get_vars() {
		return root->get_variables();
	}

	float evaluate(std::vector<int> values) {
		std::set<std::string> vars = get_vars();
		if(vars.size() != values.size())
			throw std::logic_error("Invalid values");

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

	void joinWith(Tree *tree) {
		root->replace_rightmost(tree->root);
		tree->root = 0;
		delete tree;
	}

	std::string to_string() {
		return root->to_string();
	}
};