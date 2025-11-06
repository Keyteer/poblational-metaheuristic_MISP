#include <random>

#include "utils.h"
#include "NeighList.h"
#include "PheromoneTree.h"

struct Ant{
    
    NeighList *nl;
    MISP_Solution *sol;
    pheromoneTree *tree;


    Ant(NeighList *nl, float evaporation_rate){
        this->nl = nl;
        this->sol = new MISP_Solution(nl);
        this->tree = new pheromoneTree(nl->n, evaporation_rate);
    }

    void constructSolution(vector<int> &solution){
        // Implementation of solution construction using the NeighList
        if(rand()%2) {
            int node = tree.randSearch();
        }
    }

};