#include "graph.h"

std::string getFilename();
unsigned int getNode(int order = 0);
float getLength();

int main()
{
    int t;
    unsigned int num1, num2;
    Graph<float> g;
    std::cout << "1 - create a new graph" << std::endl;
    std::cout << "2 - load graph from a file" << std::endl;
    std::cin >> t;
    if (t == 2) {
        g.loadFromFile(getFilename());
    }
    while (t) {
        std::cout << std::endl << "Select the action:" << std::endl;
        std::cout << "1 - add edge" << std::endl;
        std::cout << "2 - find edge" << std::endl;
        std::cout << "3 - delete edge" << std::endl;
        std::cout << "4 - delete node" << std::endl;
        std::cout << "5 - set the output settings of the graph" << std::endl;
        std::cout << "6 - show information about the graph and it's adjacency matrix" << std::endl;
        std::cout << "7 - save graph to a file" << std::endl;
        std::cout << "0 - exit the program" << std::endl;
        std::cin >> t;
        switch (t) {
        case 1:
            num1 = getNode(1);
            num2 = getNode(2);
            g.addEdge(num1, num2, getLength());
            std::cout << "Edge was succesfully added!" << std::endl;
            break;
        case 2:
            num1 = getNode(1);
            std::cout << g.getEdge(num1, getNode(2)) << std::endl;
            break;
        case 3:
            num1 = getNode(1);
            g.delEdge(num1, getNode(2));
            std::cout << "Edge was succesfully deleted!" << std::endl;
            break;
        case 4:
            if (g.delNode(getNode())) {
                std::cout << "Node and all it's edges was succesfully deleted!" << std::endl;
            } else {
                std::cout << "This node doesn't exist!" << std::endl;
            }
            break;
        case 5:
            std::cout << "Enter the number of digits of the numbers: ";
            std::cin >> num1;
            std::cout << "Enter the column width: ";
            std::cin >> num2;
            g.setFormat(num1, num2);
            std::cout << "The output settings of the graph was applied!" << std::endl;
            break;
        case 6:
            std::cout << std::endl << g << std::endl;
            break;
        case 7:
            g.saveToFile(getFilename());
            std::cout << "Graph was succesfully saved!" << std::endl;
            break;
        }
    }
    return 0;
}

std::string getFilename()
{
    std::string filename;
    std::cout << "Enter the filename: ";
    std::cin >> filename;
    return filename;
}

unsigned int getNode(int order)
{
    if (order == 1) {
        std::cout << "First node. ";
    } else if (order == 2) {
        std::cout << "Second node. ";
    }
    unsigned int node;
    std::cout << "Enter the number of the node: ";
    std::cin >> node;
    return node;
}

float getLength()
{
    float length;
    std::cout << "Enter the length of the edge: ";
    std::cin >> length;
    return length;
}
