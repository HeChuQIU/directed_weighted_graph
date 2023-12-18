//
// Created by hechu on 23-12-4.
//

#include "directed_weighted_graph.h"
#include "ranges"
#include <algorithm>

void print_graph(const auto &graph) {
    std::cout << "图信息：" << std::endl;
    std::cout << std::endl;

    std::cout << "  节点信息: " << std::endl
              << "    节点数量：" << graph.nodes.size() << std::endl;
    std::ranges::for_each(graph.nodes, [](auto *n) {
        std::cout << "  节点 " << n->value << std::endl;
    });
    std::cout << std::endl;

    std::cout << "  边信息: " << std::endl
              << "    边数量：" << graph.edges.size() << std::endl;
    std::ranges::for_each(graph.edges, [](auto *e) {
        std::cout << "      边 " << e->from->value << "->" << e->to->value << ": " << e->weight
                  << std::endl;
    });
    std::cout << std::endl;
}

int main() {
    std::cout << "这是一个有向带权图的演示程序" << std::endl
              << std::endl;

    directed_weighted_graph<std::string> graph;
    int choice = -1;
    while (choice != 0) {
        std::cout << "1. 添加节点" << std::endl
                  << "2. 添加/编辑边" << std::endl
                  << "3. 删除节点" << std::endl
                  << "4. 删除边" << std::endl
                  << "5. 查看图信息" << std::endl
                  << "6. 计算最短路程" << std::endl
                  << "0. 退出" << std::endl
                  << "请选择操作：";
        std::cin >> choice;
        std::cout << std::endl;
        switch (choice) {
            case 1: {
                std::cout << "请输入节点名：";
                std::string value;
                std::cin >> value;
                if (graph.find_node_or_else_null(value) != nullptr) {
                    std::cout << "已存在同名节点" << std::endl;
                    break;
                }
                graph.create_node(value);
                std::cout << "已添加节点 " << value << std::endl;
                break;
            }
            case 2: {
                std::cout << "请输入边的起点名：";
                std::string from, to;
                std::cin >> from;
                auto from_node = graph.find_node_or_else_null(from);
                if (from_node == nullptr) {
                    std::cout << "不存在该节点" << std::endl;
                    break;
                }
                std::cout << "请输入边的终点名：";
                std::cin >> to;
                auto to_node = graph.find_node_or_else_null(to);
                if (to_node == nullptr) {
                    std::cout << "不存在该节点" << std::endl;
                    break;
                }
                std::cout << "请输入边的权重：";
                int weight;
                std::cin >> weight;
                graph.set_weight(from_node, to_node, weight);
                std::cout << "设置了边 " << from << "->" << to << ": " << weight << std::endl;
                break;
            }
            case 3: {
                std::cout << "请输入要删除的节点名：";
                std::string value;
                std::cin >> value;
                auto node = graph.find_node_or_else_null(value);
                if (node == nullptr) {
                    std::cout << "不存在该节点" << std::endl;
                    break;
                }
                graph.remove_node(node);
                std::cout << "已删除节点 " << value << std::endl;
                break;
            }
            case 4: {
                std::cout << "请输入要删除的边的起点名：";
                std::string from, to;
                std::cin >> from;
                auto from_node = graph.find_node_or_else_null(from);
                if (from_node == nullptr) {
                    std::cout << "不存在该节点" << std::endl;
                    break;
                }
                std::cout << std::endl;
                std::cout << "请输入要删除的边的终点名：";
                std::cin >> to;
                auto to_node = graph.find_node_or_else_null(to);
                if (to_node == nullptr) {
                    std::cout << "不存在该节点" << std::endl;
                    break;
                }
                graph.remove_edge(from_node, to_node);
                std::cout << "已删除边 " << from << "->" << to << std::endl;
                break;
            }
            case 5: {
                print_graph(graph);
                break;
            }
            case 6: {
                std::cout << "请输入起点名：";
                std::string from, to;
                std::cin >> from;
                auto from_node = graph.find_node_or_else_null(from);
                if (from_node == nullptr) {
                    std::cout << "不存在该节点" << std::endl;
                    break;
                }
                std::cout << "请输入终点名（不输入终点名则输出到所有终点的最短路程）：";
                std::getline(std::cin, to);
                std::getline(std::cin, to);

                auto to_node = graph.find_node_or_else_null(to);
                if (!to.empty() && to_node == nullptr) {
                    std::cout << "不存在该节点" << std::endl;
                    break;
                }

                auto distance = graph.shortest_paths_spfa(from_node);
                std::cout << "最短路程：" << std::endl;
                if (to.empty()) {
                    std::ranges::for_each(distance, [](auto pair) {
                        std::cout << "  " << pair.first->value << ": " << pair.second << std::endl;
                    });
                } else {
                    std::cout << "  " << to << ": " << distance[to_node] << std::endl;
                }
                break;
            }
            case 0: {
                std::cout << "退出程序" << std::endl;
                break;
            }
            default: {
                std::cout << "无效的操作" << std::endl;
                break;
            }
        }
        std::cout << std::endl;
    }
    return 0;
}