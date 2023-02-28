#include "wordgraph.h"

void WordGraph::buildConnections(int index)
{
    // Check every word except yourself
    for (int i = 0; i < index; i++)
    {
        if (isLegalWeaverMove(*_nodes[i], *_nodes[index]))
        {
            _nodes[i]->addNeighbour(_nodes[index]);
            _nodes[index]->addNeighbour(_nodes[i]);
        }
    }
}

void WordGraph::printDebug()
{
    int size = _nodes.size();
    for (int i = 0; i < size; i++)
    {
        _nodes[i]->debugPrint();
    }
}

std::vector<std::string> WordGraph::query(std::string const &source, std::string const &destination)
{
    /**
     * @brief Goal - assemble a vector of strings from source to destination using the graph structure and the Dijkstra algortihm
     *
     */
    int totalSize = _nodes.size();
    const int inf = totalSize + 100; // Infinity is disappointingly small

    std::vector<std::string> answer;
    if (source == destination)
        return answer;

    // Prepare the graph for pathfinding

    for (int i = 0; i < totalSize; i++)
    {
        _nodes[i]->setVisited(false);
        _nodes[i]->setDistance(inf);
        _nodes[i]->setSource(nullptr);
    }

    // Prepare the starting node

    _nodes[((*this)[source])]->setDistance(0);

    Node *current_node = _nodes[((*this)[source])];

    while (current_node->getDistance() != inf)
    {
        // Do distance setting on unvisited neighbouring nodes
        int neighborsAmount = current_node->getNeighboursLength();
        int current_distance = current_node->getDistance();

        for (int i = 0; i < neighborsAmount; i++)
        {
            if ((*current_node)[i]->getVisited() == false && (*current_node)[i]->getDistance() > current_distance + 1)
            {
                (*current_node)[i]->setDistance(current_distance + 1);
                (*current_node)[i]->setSource(current_node);
            }
        }

        // Done in this node, it will not be visited again
        current_node->setVisited(true);

        // Did we mark the word_b node as visited? If so, we're done and it's time to prepare the output
        if (current_node->getName() == destination)
        {

            Node *pointer = current_node;
            while (pointer)
            {
                answer.push_back(pointer->getName());
                pointer = pointer->getSource();
            }

            return answer;
        }

        // If not, find the other node
        current_node = this->pickNextNode();
    }

    // If we reach here it means the node is unreachable

    return answer;
}

Node *WordGraph::pickNextNode()
{

    int totalSize = _nodes.size();
    Node *smallestNode = _nodes[0];

    // Pick one that wasn't visited
    int i = 0;
    for (; i < totalSize; i++)
    {
        if (_nodes[i]->getVisited() == 0)
        {
            smallestNode = _nodes[i];
            break;
        }
    }

    for (; i < totalSize; i++)
    {
        if (_nodes[i]->getVisited() == 0 && _nodes[i]->getDistance() < smallestNode->getDistance())
        {
            smallestNode = _nodes[i];
        }
    }

    return smallestNode;
}

int WordGraph::operator[](std::string const &searched)
{
    int totalSize = _nodes.size();
    for (int i = 0; i < totalSize; i++)
    {
        if (_nodes[i]->getName() == searched)
            return i;
    }
    return -1;
}
