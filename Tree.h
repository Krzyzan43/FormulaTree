#pragma once

#include <vector>
#include <string>

#include "Node.h"

const std::string WORD_ERROR = "Error in word number ";

class Tree {
public:
	// Creates tree from formula
	// This function has no way of failing, the tree will be
	// automatically fixed no matter how bad the formula is.
	// Errors will be stored inside each node seperately
	// and can be collected with "get_errors"
	// This function is expected to be the first function called
	// after the creation of the tree
	void create(const std::string &formula);

	// Goes through all the nodes and collect errors
	std::vector<std::string> get_errors() const;

	// Goes through all the nodes and collect all variable names
	std::set<std::string> get_vars() const;

	// Returns result of computed formula. Values are variables
	// and are expected to be given in the same order that 
	// get_vars returns variables
	float evaluate(const std::vector<int> &values) const;

	// Attaches root of given tree to the rightmost leaf
	// No copy is made here, at the end the tree is destroyed
	void join_with(Tree *tree);

	// Returns formula in reverse notation
	std::string to_string() const;
private:
	Node *root;

	// Creates tree node from the words. Start is index of first word
	// Processed by this function. After execution start is the index of
	// last word processed by this function. This function is recursive
	Node *create_tree(const std::vector<std::string> &words, int &start);
};