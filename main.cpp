#include <iostream>
#include "Tree.h"

int main() {
    std::cout << "Enter formula: ";
    std::string formula;
    std::getline(std::cin, formula);

    Tree tree;
    tree.create(formula);
    tree.print();
    return 0;
}