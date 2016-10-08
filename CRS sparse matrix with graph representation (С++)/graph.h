#ifndef GRAPH_H
#define GRAPH_H

#include "sparsematrix.h"
#include <cstring>

template <typename T>
class Graph : protected SparseMatrix<T>
{
public:
    Graph();
    void addEdge(unsigned int from, unsigned int to, T length);
    std::string getEdge(unsigned int from, unsigned int to);
    void delEdge(unsigned int from, unsigned int to);
    bool delNode(unsigned int node);
    void saveToFile(const std::string &filename);
    void loadFromFile(const std::string &filename);
    void setFormat(int precision, int width);
    template <typename U>
    friend std::ostream &operator<<(std::ostream &os, Graph<U> &g);
};

#include "graph.cpp"

#endif // GRAPH_H
