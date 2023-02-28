#pragma once

#include <string>
#include <iostream>
#include <vector>

/**
 * @brief A single weaver word
 *
 */
class Node
{
    friend bool isLegalWeaverMove(Node const &a, Node const &b);

public:
    Node(std::string name, int distanceMax) : _name(name), _visited(false), _neighbours(), _source(nullptr), _distance(distanceMax) {}
    
    /**
     * @brief Add a neighbour pointer to the neighbours table
     * 
     * @param node 
     */
    void addNeighbour(Node *node);

    void debugPrint();
    

    /**
     * @brief Return the neighbour at index
     * 
     * @param index 
     * @return Node* 
     */
    Node *operator[](int index) const;
    int getNeighboursLength() const;
    std::string &getName();
    bool getVisited() const;
    void setVisited(bool a);
    int getDistance() const;
    void setDistance(int a);
    void setSource(Node *a);
    Node *getSource() const;

    ~Node()
    {
        _neighbours.clear();
    }

private:
    // Data for this node
    std::string _name;
    // Structure information
    std::vector<Node *> _neighbours;
    // Dijkstra metadata
    bool _visited;
    int _distance;
    Node *_source;
};

bool isLegalWeaverMove(Node const &a, Node const &b);