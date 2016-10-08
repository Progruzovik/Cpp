#ifndef GRAPH_CPP
#define GRAPH_CPP

#include "graph.h"
#include <sstream>
#include <fstream>

template <typename T>
Graph<T>::Graph() : SparseMatrix<T>() {}

template <typename T>
void Graph<T>::addEdge(unsigned int from, unsigned int to, T length)
{
    if (from != to) {
        this->setVal(length, from, to);
    }
}

template <typename T>
std::string Graph<T>::getEdge(unsigned int from, unsigned int to)
{
    T length = this->getVal(from, to);
    if (length) {
        std::stringstream st;
        st << "Found edge: (" << from << ")---[" << length << "]--->(" << to << ')';
        return st.str();
    }
    return "This edge doesn't exist!";
}

template <typename T>
void Graph<T>::delEdge(unsigned int from, unsigned int to)
{
    this->setVal(0, from, to);
}

template <typename T>
bool Graph<T>::delNode(unsigned int node)
{
    bool isRow = this->delRow(node), isCol = this->delCol(node);
    if (isRow || isCol) {
        return true;
    }
    return false;
}

template <typename T>
void Graph<T>::saveToFile(const std::string &filename)
{
    std::ofstream os(filename, std::ios::out | std::ios::trunc | std::ios::binary);
    int szInt = sizeof(int);
    os.write(reinterpret_cast<const char*>(&this->precision), szInt);
    os.write(reinterpret_cast<const char*>(&this->width), szInt);
    os.write(reinterpret_cast<const char*>(&this->n), szInt);
    int sz = this->values.size();
    os.write(reinterpret_cast<const char*>(&sz), szInt);
    os.write(reinterpret_cast<const char*>(&this->values[0]), sz * sizeof(float));
    sz = this->cols.size();
    os.write(reinterpret_cast<const char*>(&sz), szInt);
    os.write(reinterpret_cast<const char*>(&this->cols[0]), sz * szInt);
    sz = this->pointers.size();
    os.write(reinterpret_cast<const char*>(&sz), szInt);
    os.write(reinterpret_cast<const char*>(&this->pointers[0]), sz * szInt);
    os.close();
}

template <typename T>
void Graph<T>::loadFromFile(const std::string &filename)
{
    std::ifstream is(filename, std::ios::in | std::ios::binary);
    int sz, szInt = sizeof(int);
    is.read(reinterpret_cast<char*>(&this->precision), szInt);
    is.read(reinterpret_cast<char*>(&this->width), szInt);
    is.read(reinterpret_cast<char*>(&this->n), szInt);
    is.read(reinterpret_cast<char*>(&sz), szInt);
    this->values.resize(sz);
    is.read(reinterpret_cast<char*>(&this->values[0]), sz * sizeof(float));
    is.read(reinterpret_cast<char*>(&sz), sizeof(sz));
    this->cols.resize(sz);
    is.read(reinterpret_cast<char*>(&this->cols[0]), sz * szInt);
    is.read(reinterpret_cast<char*>(&sz), sizeof(sz));
    this->pointers.resize(sz);
    is.read(reinterpret_cast<char*>(&this->pointers[0]), sz * szInt);
    is.close();
}

template <typename T>
void Graph<T>::setFormat(int precision, int width)
{
    this->precision = precision;
    this->width = width;
}

template <typename U>
std::ostream &operator<<(std::ostream &os, Graph<U> &g)
{
    os << "The number of nodes in the graph: ";
    if (g.numCols() > g.numRows()) {
        os << g.numCols();
    } else {
        os << g.numRows();
    }
    os << std::endl << "Used memory: " << g.memUsed() << " bytes" << std::endl << "Adjacency sparse matrix:" << std::endl;
    return g.matrixToOstream(os);
}

#endif
