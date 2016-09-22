#include <iostream>
#include <vector>

#pragma once

class BalancedTree
{
public:
    BalancedTree(const std::vector<int> &v, int f, int s = 1);
    BalancedTree(BalancedTree* root);
    ~BalancedTree(void);

    int num;
	
    BalancedTree* left;
    BalancedTree* right;
	
    void out(int depth = 0);
    int minimum();
    friend std::ostream& operator<<(std::ostream& os, BalancedTree* a);
};
