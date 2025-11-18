#include "Network.h"
#include <queue>


std::vector<int> Network::getTopologicalSortedNodes() {

    std::unordered_map<int, int> in_degrees;

        for (auto& [node, neighbors] : graph) {
            in_degrees[node];
            for (auto& [neighbor, weight] : neighbors) {
                in_degrees[neighbor]++;
            }
        }

        std::queue<int> queue;

        for (auto& [node, in_degree] : in_degrees) {
            if (in_degree == 0) {
                queue.push(node);
            }
        }

        std::vector<int> result;

        while (!queue.empty()) {
            int node = queue.front();
            queue.pop();
            result.push_back(node);

            for (auto& [neigbor, weight] : graph[node]) {
                in_degrees[neigbor]--;
                if (in_degrees[neigbor] == 0) {
                    queue.push(neigbor);
                }
            }
        }

        return result;
}