//
// Created by hechu on 23-12-4.
//

#include "directed_weighted_graph.h"
#include "ranges"
#include <algorithm>

void print_graph(const directed_weighted_graph<int> &graph) {
    std::cout << "图信息：" << std::endl;
    std::cout << std::endl;

    std::cout << "节点信息: " << std::endl
              << "节点数量：" << graph.nodes.size() << std::endl;
    std::ranges::for_each(graph.nodes, [](directed_weighted_graph<int>::node *n) {
        std::cout << "节点 " << n->value << std::endl;
    });
    std::cout << std::endl;

    std::cout << "边信息: " << std::endl
              << "边数量：" << graph.edges.size() << std::endl;
    std::ranges::for_each(graph.edges, [](directed_weighted_graph<int>::edge *e) {
        std::cout << "边 " << e->from->value << "->" << e->to->value << ": " << e->weight
                  << std::endl;
    });
    std::cout << std::endl;
}

int main() {
    directed_weighted_graph<int> graph;

    std::vector<directed_weighted_graph<int>::node *> nodes;

    for (int i = 0; i < 10; ++i) {
        nodes.push_back(graph.create_node(i));
    }

    graph.set_weight(nodes[0], nodes[1], 3);
    graph.set_weight(nodes[1], nodes[2], 1);
    graph.set_weight(nodes[2], nodes[0], 9);
    graph.set_weight(nodes[2], nodes[3], 6);
    graph.set_weight(nodes[1], nodes[3], 1);
    graph.set_weight(nodes[0], nodes[3], -1);
    graph.set_weight(nodes[3], nodes[0], 1);

    // 输出图信息
    print_graph(graph);

    try {
        auto start = nodes[0];
        auto distances = graph.shortest_paths_spfa(start);
        std::cout << "最短距离：" << std::endl;
        // 输出最短路径长度
        for (const auto &entry: distances) {
            std::cout << start->value << "->" << entry.first->value << ": "
                      << (entry.second == std::numeric_limits<int>::max() ? "不可达" : std::to_string(
                              entry.second))
                      << std::endl;
        }
    }
    catch (std::runtime_error err) {
        std::cerr << err.what();
    }

    return 0;
}