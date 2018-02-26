//
// Created by Nikolay Yakovets on 2018-02-01.
//

#include "SimpleGraph.h"
#include "SimpleEstimator.h"

SimpleEstimator::SimpleEstimator(std::shared_ptr<SimpleGraph> &g){

    // works only with SimpleGraph
    graph = g;
}

void SimpleEstimator::prepare() {

    nrIn.resize(graph->getNoLabels());
    nrPaths.resize(graph->getNoLabels());
    nrOut.resize(graph->getNoLabels());

    std::vector<std::unordered_set<uint32_t>> nodesIn;
    std::vector<std::unordered_set<uint32_t>> nodesOut;

    for (uint32_t i=0; i < graph->getNoLabels(); i++) {
        nrPaths[i] = 0;
    }

    for (uint32_t v=0; v < graph->adj.size(); v++) {
        for (uint32_t w=0; w < graph->adj[v].size(); w++) {
            auto label = graph->adj[v][w].first;
            nrPaths[label]++;
            nodesOut[label].insert(v);
            nodesIn[label].insert(w);
        }
    }

    for (uint32_t i=0; i < graph->getNoLabels(); i++) {
        nrIn[i] = (uint32_t) nodesIn[i].size();
        nrOut[i] = (uint32_t) nodesOut[i].size();
    }
}

cardStat SimpleEstimator::estimate(RPQTree *q) {

    // perform your estimation here

    return cardStat {0, 0, 0};
}