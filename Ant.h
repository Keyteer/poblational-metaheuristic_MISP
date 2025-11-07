#include <random>
#include <vector>

#include "NeighList.h"
#include "PheromoneTree.h"

struct Ant{

    NeighList *nl;
    vector<int> sol;
    pheromoneTree *global_tree;
    pheromoneTree tree;

    Ant(NeighList *nl, pheromoneTree *tree) : tree(*tree) {
        this->global_tree = tree;
        this->nl = nl;
    }
    ~Ant(){
        tree.~pheromoneTree();
    }
    void reset() {
        this->tree = *global_tree;
        sol.clear();
    }

    int constructPondSolution() {
        // assumed empty solution
        for (int node = tree.pondRandSearch(); node != -1; node = tree.pondRandSearch()) {
            sol.push_back(node);
            // invalidate neighbors
            tree.invalidateVector(nl->neighborhoods[node]);
            // invalidate node itself
            tree.invalidate(node);
        }
        return sol.size();
    }

    void depositInSolution(int deposit_amount) {
        for (int node : sol) {
            global_tree->deposit(node, deposit_amount);
        }
    }
};