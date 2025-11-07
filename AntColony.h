#include <chrono>

#include "Ant.h"
#include "PheromoneTree.h"

using namespace std;

int AntColony(NeighList *nl, double time_limit, float evaporation_rate, int deposit_amount, int n_ants, int *iterations=nullptr) {
    auto start_time = chrono::high_resolution_clock::now();
    
    pheromoneTree pheromones(nl->n, evaporation_rate);

    int best_size = 0;

    Ant *ants[n_ants];
    for (int i = 0; i < n_ants; i++) {
        ants[i] = new Ant(nl, &pheromones);
    }

    while (chrono::duration<double>(chrono::high_resolution_clock::now() - start_time).count() < time_limit) {
        for(int i = 0; i < n_ants; i++) {
            if (ants[i]->pondSolutionStep() == -1) {
                if (ants[i]->sol.size() > best_size) {
                    best_size = ants[i]->sol.size();
                    ants[i]->depositInSolution(deposit_amount);
                }
                ants[i]->reset();
                (*iterations)++;
            }
        }

        pheromones.evaporate();

    }

    for (int i = 0; i < n_ants; i++) {
        delete ants[i];
    }
    delete[] ants;

    return best_size;
}