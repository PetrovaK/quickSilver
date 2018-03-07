//
// Created by Nikolay Yakovets on 2018-02-01.
//

#ifndef QS_SIMPLEESTIMATOR_H
#define QS_SIMPLEESTIMATOR_H

#include "Estimator.h"
#include "SimpleGraph.h"

class SimpleEstimator : public Estimator {

    std::shared_ptr<SimpleGraph> graph;

    std::vector<uint32_t> nrOut;
    std::vector<uint32_t> nrPaths;
    std::vector<uint32_t> nrIn;

    std::vector<std::unordered_set<uint32_t>> nodesOut;
    std::vector<std::unordered_set<uint32_t>> nodesIn;

public:
    explicit SimpleEstimator(std::shared_ptr<SimpleGraph> &g);
    ~SimpleEstimator() = default;

    void prepare() override ;
    cardStat estimate(RPQTree *q) override ;
    cardStat join(RPQTree *q);

};


#endif //QS_SIMPLEESTIMATOR_H
