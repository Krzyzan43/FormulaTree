#include <iostream>
#include <vector>
#include <map>


const std::pair<std::string, int> ALLOWED_OPERATIONS[] = {
    std::pair<std::string, int>("+", 2),
    std::pair<std::string, int>("-", 2),
    std::pair<std::string, int>("*", 2),
    std::pair<std::string, int>("/", 2),
    std::pair<std::string, int>("sin", 1),
    std::pair<std::string, int>("cos", 1),
};

const std::pair<std::string, std::string> OPERATIONS_FIX[] = {
    std::pair<std::string, std::string>("+", "0"),
    std::pair<std::string, std::string>("-", "0"),
    std::pair<std::string, std::string>("*", "1"),
    std::pair<std::string, std::string>("/", "1"),
    std::pair<std::string, std::string>("sin", "3.14159"),
    std::pair<std::string, std::string>("cos", "0"),
};

int TOTAL_OPERATIONS = 6;


class Node {
public:
    Node(std::string symbol) {
        childCount = get_children(symbol);
        children = new Node*[childCount];
        this->symbol = symbol;
    }

    void setChild(int i, Node *child) {
        children[i] = child;
    }

    int get_child_count() {
        return childCount;
    }

    void print() {
        std::cout << symbol;
        for (int i = 0; i < childCount; i++)
            children[i]->print();
    }

    void fix() {
        if(childCount == 0)
            return;

        std::string fix = "";
        for (int i = 0; i < TOTAL_OPERATIONS; i++)
        {
            if(symbol == OPERATIONS_FIX[i].first) {
                fix = OPERATIONS_FIX[i].second;
                break;
            }
        }

        for (int i = 0; i < childCount; i++)
        {
            if(children[i] == NULL)
                children[i] = new Node(fix);
            children[i]->fix();
        }
    }

private:
    int childCount;
    std::string symbol;
    Node** children;

    int get_children(std::string symbol) {
        for (int i = 0; i < TOTAL_OPERATIONS; i++)
        {
            if(ALLOWED_OPERATIONS[i].first == symbol)
                return ALLOWED_OPERATIONS[i].second;
        }
        return 0; 
    }
};