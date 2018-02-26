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

    for (uint32_t i=0; i < graph->getNoLabels(); i++) {
        nrPaths[i] = 0;
    }
    
    for (uint32_t v=0; v < graph->adj.size(); v++) {
        for (uint32_t w=0; w < graph->adj[v].size(); w++) {
            nrPaths[graph->adj[v][w].first]++;
        }
    }
}

cardStat SimpleEstimator::estimate(RPQTree *q) {

    // perform your estimation here

    return cardStat {0, 0, 0};
}