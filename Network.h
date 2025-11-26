#pragma once
#include <iostream>
#include <unordered_map>
#include <vector>
#include <unordered_set>
#include "Pipe.h"
#include "Station.h"

class Network {
    std::unordered_map<int, std::unordered_map<int, double>> graph;
    std::unordered_map<int, Pipe>& pipes;
    std::unordered_map<int, Station>& stations;
    std::unordered_set<int> using_pipes;

    std::vector<int> getTopologicalSortedNodes();

    std::pair<std::vector<int>, double> getShortestWay(int start, int end);

    void deleteZeroDegreeNodes();

public:
    void initializeNetwork();

    void createConnection();

    void deleteConnection();

    void showNetwork();

    void showTopologicalSortedNetwork();

    void findShortestWay();

    Network(std::unordered_map<int, Pipe>& pipes, 
        std::unordered_map<int, Station>& stations) : pipes(pipes), stations(stations) {}
};