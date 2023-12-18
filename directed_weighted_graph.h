//
// Created by hechu on 23-12-4.
//

#ifndef DIRECTED_WEIGHTED_GRAPH_DIRECTED_WEIGHTED_GRAPH_H
#define DIRECTED_WEIGHTED_GRAPH_DIRECTED_WEIGHTED_GRAPH_H

#include <vector>
#include <set>
#include <functional>
#include <limits>
#include <iostream>
#include <queue>
#include <unordered_set>

template<class T>
class directed_weighted_graph {
public:
    class node;

    class edge;

    std::vector<node *> nodes;

    std::vector<edge *> edges;

    node *create_node(T value) {
        auto new_node = new directed_weighted_graph::node(value);
        nodes.push_back(new_node);
        return new_node;
    }

    void set_weight(node* from, node* to, int weight) {
        if (std::find(nodes.begin(), nodes.end(), from) == nodes.end())
            nodes.push_back(from);
        if (std::find(nodes.begin(), nodes.end(), to) == nodes.end())
            nodes.push_back(to);
        auto edge = find_edge_or_else_create(from, to);
        edge->weight = weight;
        edges.push_back(edge);
    }

    void remove_edge(node *from, node *to) {
        auto edge = find_edge(from, to);
        if (edge != edges.end())
            edges.erase(edge);
        else{
            throw std::runtime_error("边不存在");
        }
    }

    void remove_node(node *n) {
        auto node_iter = std::find(nodes.begin(), nodes.end(), n);
        if (node_iter != nodes.end())
            nodes.erase(node_iter);
        for (auto *e : edges) {
            if (e->from == n || e->to == n) {
                remove_edge(e->from, e->to);
            }
        }
    }

    std::unordered_map<node *, int> shortest_paths_spfa(node *start) {
        std::unordered_map<node *, int> distance;
        std::unordered_map<node *, int> in_queue_count;
        for (auto *n : nodes) {
            distance[n] = std::numeric_limits<int>::max();
            in_queue_count[n] = 0;
        }
        distance[start] = 0;

        std::queue<node *> q;
        std::unordered_set<node *> in_queue;

        q.push(start);
        in_queue.insert(start);

        while (!q.empty()) {
            auto *current = q.front();
            q.pop();
            in_queue.erase(current);

            for (auto *e : edges) {
                if (distance[e->from] != std::numeric_limits<int>::max() &&
                    distance[e->to] > distance[e->from] + e->weight) {
                    distance[e->to] = distance[e->from] + e->weight;

                    if (in_queue.find(e->to) == in_queue.end()) {
                        q.push(e->to);
                        in_queue.insert(e->to);
                        in_queue_count[e->to]++;
                        if (in_queue_count[e->to] >= nodes.size()) {
                            // 存在负权环
                            throw std::runtime_error("存在负权环路，无法计算最短路径");
                        }
                    }
                }
            }
        }

        return distance;
    }

    node* find_node_or_else_null(T value) {
        auto node = std::find_if(nodes.begin(), nodes.end(),
                                 [value](const directed_weighted_graph::node *node) {
                                     return node->value == value;
                                 });
        return node != nodes.end() ? *node : nullptr;
    }

    auto find_edge(node *from, node *to) {
        auto edge = std::find_if(edges.begin(), edges.end(),
                                 [from, to](const directed_weighted_graph::edge *edge) {
                                     return edge->from == from && edge->to == to;
                                 });
        return edge;
    }

    auto find_edge_or_else_create(node *from, node *to) {
        auto edge_iter = find_edge(from, to);
        return (edge_iter != edges.end()) ? *edge_iter : new directed_weighted_graph::edge(from, to);
    }

    class node {
    public:
        T value;

        explicit node(T value) {
            this->value = value;
        }
    };

    class edge {
    public:
        node *from;
        node *to;
        int weight = 0;

        explicit edge(node *from, node *to, int weight = 0) {
            this->from = from;
            this->to = to;
            this->weight = weight;
        }
    };
};


#endif //DIRECTED_WEIGHTED_GRAPH_DIRECTED_WEIGHTED_GRAPH_H
