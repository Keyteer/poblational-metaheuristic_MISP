#include <chrono>

#include "Ant.h"
#include "PheromoneTree.h"

using namespace std;

int AntColony(NeighList *nl, double time_limit, float evaporation_rate, int deposit_amount, bool verbose=false, int *iterations=nullptr) {
    auto start_time = chrono::high_resolution_clock::now();

    int it = 0; // Trick to avoid using dynamic memory allocation
    if (iterations == nullptr) {
        iterations = &it;
    }
    
    pheromoneTree pheromones(nl->n, evaporation_rate);

    int best_size = 0;
    
    Ant *ant = new Ant(nl, &pheromones);
    while (chrono::duration<double>(chrono::high_resolution_clock::now() - start_time).count() < time_limit) {
        int size = ant->constructPondSolution();
        if (size > best_size) {
            best_size = size;
            ant->depositInSolution(deposit_amount);
            
            if (verbose) {
                printf("New best size: %d at iteration %d\n", best_size, *iterations);
            }
        }
        ant->reset();
        pheromones.evaporate();

        (*iterations)++;
    }

    if (verbose) {
        printf("Best size found: %d in %d iterations\n", best_size, *iterations);
    }

    delete ant;

    return best_size;
}