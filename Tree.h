#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#include "Node.h"
#include "Utils.h"

const std::string WORD_ERROR = "Error in word number ";

class Tree {
public:
	void create(const std::string &formula);

	std::vector<std::string> get_errors() const;

	std::set<std::string> get_vars() const;

	float evaluate(const std::vector<int> &values) const;

	void joinWith(Tree *tree);

	std::string to_string() const;
private:
	Node *root;

	Node *create_tree(const std::vector<std::string> &words, int &start);
};