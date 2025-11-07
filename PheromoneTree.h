#pragma once

#include <random>

struct pheromoneTree {
    /*
        pheromoneTree is a complete binary tree stored in an array.
        The leaves represent the pheromone levels of the nodes in the graph.
        Internal nodes store the sum of pheromone levels of their children.
    */

    int n;
    int tree_size;
    int *pheromones;
    float evaporation_rate;

    pheromoneTree(pheromoneTree const &other) {
        n = other.n;
        tree_size = other.tree_size;
        evaporation_rate = other.evaporation_rate;
        pheromones = new int[tree_size];
        memcpy(pheromones, other.pheromones, tree_size * sizeof(int));
    }
    pheromoneTree(int n , float evaporation_rate) {
        int i = 1;
        while( i < n) {
            // search smallest power of 2 greater than n
            i = i << 1;
        }
        tree_size = i*2 - 1;

        this->n = n;
        pheromones = new int[tree_size];
        memset(pheromones, 0, tree_size * sizeof(int));
        for (int i = getLeaf(0); i < getLeaf(n - 1); i++) {
            pheromones[i] = 1;
            propagate(i);
        }
        this->evaporation_rate = evaporation_rate;
    }
    ~pheromoneTree() {
        delete[] pheromones;
    }

    pheromoneTree& operator=(const pheromoneTree& other) {
        if (this != &other) {
            delete[] pheromones;
            n = other.n;
            tree_size = other.tree_size;
            evaporation_rate = other.evaporation_rate;
            pheromones = new int[tree_size];
            memcpy(pheromones, other.pheromones, tree_size * sizeof(int));
        }
        return *this;
    }

    inline int getLeaf(int node) {
        if (node < n) {
            return node + tree_size / 2;
        } else if (node > tree_size / 2) {
            return node;
        }else{
            throw std::out_of_range("Node index is not a valid leaf");
        }
        return -1;
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
        node = getLeaf(node);
        pheromones[node] += amount;
        propagate(node);
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
    int pondRandSearch(int father=0){

        int base;
        do {
            base = (1 << father);

            if (rand() % (pheromones[base + 1] + pheromones[base + 2]) < pheromones[base + 2]) {
                father = base + 2;
            }else{
                father = base + 1;
            }
        } while (father > n-1);

        return father;
    }

    void invalidate(int node) {
        node = getLeaf(node);
        pheromones[node] = 0;
        propagate(node);
    }

};
