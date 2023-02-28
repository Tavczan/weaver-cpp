#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#include "node.h"

/**
 * @brief Container for all weaver words in a graph
 *
 */
class WordGraph
{

public:
    WordGraph(std::string filename, int desiredLength)
    {

        std::ifstream file;
        file.open(filename);
        if (!file)
        {
            std::cout << "An error has occured and the words file could not be opened." << std::endl;
            throw std::invalid_argument("The file could not be opened");
        }

        std::string buffer;
        file >> buffer;
        int word = 0;
        while (!file.eof())
        {

            if (buffer.length() == desiredLength)
            {
                _nodes.push_back(new Node(buffer, -1)); // dictSize just has to be large enough to be considered 'infinity' from the algorithm's point of view
                this->buildConnections(word);
                word++;
            }
            file >> buffer;
        }
        file.close();

        int dictionarySize = _nodes.size();
        for (int i = 0; i < dictionarySize; i++)
        {
            _nodes[i]->setDistance(dictionarySize + 100);
        }
    }

    // Add pointers to node
    void buildConnections(int index);
    void printDebug();
    int operator[](std::string const &searched);
    std::vector<std::string> query(std::string const &source, std::string const &destination);

    ~WordGraph()
    {
        for (int i = 0; i < _nodes.size(); i++)
        {
            delete _nodes[i];
        }
    }

    Node *pickNextNode();

private:
    std::vector<Node *> _nodes;
};
