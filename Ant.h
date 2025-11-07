#include <random>

#include "utils.h"
#include "NeighList.h"
#include "PheromoneTree.h"

struct Ant{

    NeighList *nl;
    MISP_Solution sol;
    pheromoneTree tree;

    Ant(NeighList *nl, float evaporation_rate) : sol(nl), tree(nl->n, evaporation_rate) {
        this->nl = nl;
    }
    ~Ant(){
        sol.~MISP_Solution();
        tree.~pheromoneTree();
    }

    void constructPondSolution(vector<int> &solution){
        // assumed empty solution
        int node;
        while ((node = tree.pondRandSearch()) != -1) {
            solution.push_back(node);
            // invalidate neighbors
            for (int neighbor : nl->neighborhoods[node]) {
                tree.invalidate(neighbor);
            }
        }
    }

};