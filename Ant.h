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
        int node;
        while ((node = tree.pondRandSearch()) != -1) {
            sol.push_back(node);
            // invalidate neighbors
            for (int neighbor : nl->neighborhoods[node]) {
                tree.invalidate(neighbor);
            }
        }
        return sol.size();
    }

    void depositInSolution(int deposit_amount) {
        for (int node : sol) {
            global_tree->deposit(node, deposit_amount);
        }
    }
};