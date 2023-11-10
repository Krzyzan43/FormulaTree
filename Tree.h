#include <iostream>
#include <vector>
#include <string>

#include "Node.h"



class Tree {
	Node *root;

	std::vector<std::string> split_formula(std::string formula) {
		
		std::string current_symbol = "";
		std::vector<std::string> result;
		for (int i = 0; i < formula.length(); i++)
		{
			char c = formula.at(i);
			if(c != ' ')
				current_symbol += c;
			else if(current_symbol != "") {
				result.push_back(current_symbol);
				current_symbol = "";
			}
		}
		if(current_symbol != "")
			result.push_back(current_symbol);
		return result;
	}

	Node *create_tree(std::vector<std::string> words, int &start) {
		if(start >= words.size()) {
			return NULL;
		}

		Node *node = new Node(words[start]);
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
		std::vector<std::string> words= split_formula(formula);
		root = create_tree(words, index);
		root->fix();
	}

	void print() {
		root->print();
	}
};