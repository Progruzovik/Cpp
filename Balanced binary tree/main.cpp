#include <iostream>
#include <vector>
#include <algorithm>
#include "BalancedTree.h"

int main()
{
    std::cout << "Enter the number of elements in the tree: ";
    int n;
    std::cin >> n;
    std::cout << "Enter a sequence of " << n << " elements:" << std::endl;
    std::vector<int> v(n, 0);
    for (int i = 0; i < n; i++) {
        std::cin >> v[i];
    }
    std::sort(v.begin(), v.end());
    BalancedTree* root = new BalancedTree(v, n);
    std::cout << std::endl << "Balanced binary tree: " << root << std::endl << std::endl;
    root->out();
    std::cout << std::endl << "Minimum: " << root->minimum() << std::endl;
    delete root;
    return 0;
}
