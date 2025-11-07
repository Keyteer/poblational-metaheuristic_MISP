#include <random>

#include "utils.h"
#include "NeighList.h"
#include "PheromoneTree.h"

struct Ant{

    NeighList *nl;
    MISP_Solution sol;
    pheromoneTree *global_tree;
    pheromoneTree tree;

    Ant(NeighList *nl, pheromoneTree *tree) : sol(nl), tree(*tree) {
        this->global_tree = tree;
        this->nl = nl;
    }
    ~Ant(){
        sol.~MISP_Solution();
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
            sol.addNode(node);
            // invalidate neighbors
            for (int neighbor : nl->neighborhoods[node]) {
                tree.invalidate(neighbor);
            }
        }
        return sol.size;
    }

    void depositInSolution(int deposit_amount) {
        for (int i = 0; i < sol.size; i++) {
            global_tree->deposit(sol.solution[i], deposit_amount);
        }
    }
};