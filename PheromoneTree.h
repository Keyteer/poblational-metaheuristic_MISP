#pragma once

#include <random>

struct pheromoneTree {

    int n;
    int *pheromones;
    float evaporation_rate;


    pheromoneTree(int n , float evaporation_rate) {
        this->n = n;
        pheromones = new int[(2*n)-1];
        for (int i = n; i < 2*n; i++) {
            pheromones[i] = 1;

        }
        this->evaporation_rate = evaporation_rate;
    }
    ~pheromoneTree() {
        delete[] pheromones;
    }

    void evaporate() {
        for (int i = n; i < 2*n; i++) {
            pheromones[i] = static_cast<int>(pheromones[i] * (1.0 - evaporation_rate));
            if (pheromones[i] < 1) {
                pheromones[i] = 1; 
            }
            propagate(i);
        }
    }
    void deposit(int node, int amount) {
        pheromones[node] += amount;
    }

    private:

    void propagate(int node) {
        int current = node;
        int base;
        while (current > 0) {
            int father = (current - 1) / 2;
            base = (1 << father)+1;
            if (current == base) {
                pheromones[father] = pheromones[current] + pheromones[base + 1];
            } else {
                pheromones[father] = pheromones[current] + pheromones[base];
            }
            current = father;
        }
    }

    public:

    int maxSearch(int father=0){

        int base;
        do {
            base = (1 << father);

            if (pheromones[base + 1] < pheromones[base + 2]){
                father = base + 2;
            }else{
                father = base + 1;
            }
        } while (father > n-1);

        return father;
    }

    int randSearch(int father=0){

        int base;
        do {
            base = (1 << father);

            if (pheromones[base + 1] != 0 && pheromones[base + 2] != 0) {
                father = base + 1 + rand()%2;
            } else {
                if (pheromones[base + 1] != 0 ) {
                    father = base + 1;
                } else if (pheromones[base + 2] != 0) {
                    father = base + 2;
                } else {
                    return -1;
                }
            }
        } while (father > n-1);

        return father;
    }

    int pondSearch(int father=0){

        int base;
        do {
            base = (1 << father);

            if (pheromones[base + 1] < pheromones[base + 2]){
                father = base + 2;
            }else{
                father = base + 1;
            }
        } while (father > n-1);

        return father;
    }

    void deletear(int node) {
        pheromones[node] = 0;
        propagate(node);
    }

};
