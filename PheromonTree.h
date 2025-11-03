#pragma once

struct pheromonTree {

    int n;
    int *pheromones;
    float evaporation_rate;


    pheromonTree(int n , float evaporation_rate) {
        this->n = n;
        pheromones = new int[(2*n)-1];
        for (int i = n; i < 2*n; i++) {
            pheromones[i] = 1;

        }
        this->evaporation_rate = evaporation_rate;
    }
    ~pheromonTree() {
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

    void propagate(int node) {
        int current = node;
        while (current > 0) {
            int father = (current - 1) / 2;
            pheromones[father] = pheromones[current] + pheromones[search(father)];
            current = father;
        }
    }

    int search(int father) {
        if (pheromones[ (1 << father) + 1] < pheromones[ (1 << father) + 2]){
            if (pheromones[(1 << father) + 2] > n-1){
                return (1 << father) + 2;
            }else{
                return search((1 << father) + 2);
            }
        }else{
            if (pheromones[(1 << father) + 1] > n-1){
                return (1 << father) + 1;
            }else{
                return search((1 << father) + 1);
            }
        }
    }

};
