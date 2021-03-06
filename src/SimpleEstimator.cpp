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
    nrOut.resize(graph->getNoLabels());
    nrPaths.resize(graph->getNoLabels());
    nrIn.resize(graph->getNoLabels());

    nodesOut.resize(graph->getNoLabels());
    nodesIn.resize(graph->getNoLabels());

    for (uint32_t i=0; i < graph->getNoLabels(); i++) {
        nrPaths[i] = 0;
    }

    for (uint32_t v=0; v < graph->adj.size(); v++) {
        for (uint32_t w=0; w < graph->adj[v].size(); w++) {
            auto label = graph->adj[v][w].first;
            nrPaths[label]++;
            nodesOut[label].insert(v);
            nodesIn[label].insert(graph->adj[v][w].second);
        }
    }

    for (uint32_t i=0; i < graph->getNoLabels(); i++) {
        nrOut[i] = (uint32_t) nodesOut[i].size();
        nrIn[i] = (uint32_t) nodesIn[i].size();
    }
}

cardStat SimpleEstimator::estimate(RPQTree *q) {

    cardStat tree = join(q);
    uint32_t noOut = 0;
    uint32_t noIn = 0;

    // For noOut we check the first label of the query. Based on + or - we estimate noOut with nrOut or nrIn.
    auto firstNode = q;
    while (!firstNode->isLeaf()) {
        firstNode = firstNode->left;
    }
    auto firstLabel = firstNode->data;
    if (firstLabel.substr(firstLabel.size()-1, firstLabel.size()) == "+"){
        noOut = nrOut[stoi(firstLabel.substr(0,firstLabel.size()-1))];
    } else {
        noOut = nrIn[stoi(firstLabel.substr(0,firstLabel.size()-1))];
    }

    // For noIn we check the last label of the query. We make an estimate in a similar way to noOut.
    auto lastNode = q;
    while (!lastNode->isLeaf()) {
        lastNode = lastNode->right;
    }
    auto lastLabel = lastNode->data;
    if (lastLabel.substr(lastLabel.size()-1,lastLabel.size()) == "+") {
        noIn = nrIn[stoi(lastLabel.substr(0,lastLabel.size()-1))];
    } else {
        noIn = nrOut[stoi(lastLabel.substr(0,lastLabel.size()-1))];
    }


    return cardStat {noOut, tree.noPaths, noIn};
}

cardStat SimpleEstimator::join(RPQTree *q){
    uint32_t noOut = 0;
    uint32_t noIn = 0;
    uint32_t noPaths = 0;

    if(!q->isLeaf()){
        cardStat leftCard = join(q->left);
        cardStat rightCard = join(q->right);
        //Tr - nrOut for left and Ts - nrIn for right side
        //V(R,Y) - nr distinct outgoing paths from left
        //V(S,Y) - nr distinct incoming paths to right
        uint32_t v = std::max(leftCard.noIn, rightCard.noOut);
        noPaths = (leftCard.noPaths * rightCard.noPaths)/v;
        noIn = leftCard.noOut;
        noOut = rightCard.noIn;
        return cardStat {noOut, noPaths, noIn};
    }
    else{
        //find for label
        auto label = q->data;
        auto actLabel = stoi(label.substr(0,label.size()-1));
        if (label.substr(label.size()-1, label.size()) == "+"){
            noOut = nrOut[actLabel];
            noIn = nrIn[actLabel];
        } else {
            noOut = nrIn[actLabel];
            noIn = nrOut[actLabel];
        }
        noPaths = nrPaths[actLabel];
        return cardStat {noOut, noPaths, noIn};
    }
}

