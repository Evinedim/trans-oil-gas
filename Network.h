#pragma once
#include <iostream>
#include <unordered_map>
#include <vector>
#include <unordered_set>
#include "Pipe.h"
#include "Station.h"

class Network {
    std::unordered_map<int, std::unordered_map<int, int>> graph;
    std::unordered_map<int, Pipe>& pipes;
    std::unordered_map<int, Station>& stations;
    std::unordered_set<int> using_pipes;

    std::vector<int> getTopologicalSortedNodes();

    void deleteZeroDegreeNodes();

public:
    void clear();

    void showNetwork();

    void showTopologicalSortedNetwork();

    void createConnection();

    void deleteConnection();

    Network(std::unordered_map<int, Pipe>& pipes, 
        std::unordered_map<int, Station>& stations) : pipes(pipes), stations(stations) {}
};