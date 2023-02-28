#include "node.h"

void Node::addNeighbour(Node *node)
{
    _neighbours.push_back(node);
}
int Node::getNeighboursLength() const
{
    return _neighbours.size();
}
Node *Node::operator[](int index) const
{
    return _neighbours[index];
}

std::string &Node::getName()
{
    return _name;
}

bool isLegalWeaverMove(Node const &a, Node const &b)
{
    int diff = 0;
    for (int i = 0; i < a._name.size(); i++)
    {
        if ((a._name)[i] != (b._name)[i])
            diff++;
        if (diff > 1)
            return false;
    }
    return true;
}

void Node::debugPrint()
{
    std::cout << _name << std::endl;
    for (int i = 0; i < this->_neighbours.size(); i++)
    {
        std::cout << "    --->" << _neighbours[i]->getName() << std::endl;
    }
}

bool Node::getVisited() const
{
    return _visited;
}
void Node::setVisited(bool a)
{
    _visited = a;
}
int Node::getDistance() const
{
    return _distance;
}
void Node::setDistance(int a)
{
    _distance = a;
}
void Node::setSource(Node *a)
{
    _source = a;
}
Node *Node::getSource() const
{
    return _source;
}
