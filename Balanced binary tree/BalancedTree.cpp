#include "BalancedTree.h"

BalancedTree::BalancedTree(const std::vector<int> &v, int f, int s)
{
	int m = s + (f - s) / 2;
    num = v[m - 1];
	if (s > m - 1) {
		left = 0;
	} else {
        left = new BalancedTree(v, m - 1, s);
	}
	if (m + 1 > f) {
		right = 0;
	} else {
        right = new BalancedTree(v, f, m + 1);
	}
}

BalancedTree::BalancedTree(BalancedTree* root)
{
	num = root->num;
	if (root->left) {
        left = new BalancedTree(root->left);
	} else {
		left = 0;
	}
	if (root->right) {
        right = new BalancedTree(root->right);
	} else {
		right = 0;
	}
}

BalancedTree::~BalancedTree(void)
{
	if (left) {
		delete left;
	}
	if (right) {
		delete right;
	}
}

void BalancedTree::out(int depth)
{
	if (right) {
		right->out(depth + 1);
	}
	for (int i = 0; i < depth; i++) {
		for (int j = 0; j < 5; j++) {
			std::cout << ' ';
		}
	}
	std::cout << num << '\n';
	if (left) {
		left->out(depth + 1);
	}
}

int BalancedTree::minimum()
{
	if (left) {
		return left->minimum();
	}
	return num;
}

std::ostream& operator<<(std::ostream& os, BalancedTree* a)
{
	os << a->num << ' ';
	if (a->left) {
		os << a->left;
	}
	if (a->right) {
		os << a->right;
	}
	return os;
}
