#pragma once

#include <random>
#include <vector>
#include <stdexcept>

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
            i = i << 1;    // search smallest power of 2 greater than n
        }
        tree_size = i*2 - 1;

        this->n = n;
        pheromones = new int[tree_size];
        memset(pheromones, 0, tree_size * sizeof(int));
        for (int i = getLeaf(0); i <= getLeaf(n - 1); i++) {
            pheromones[i] = 1;
        }
        propagateAll();
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

    void evaporate() {
        for (int i = getLeaf(0); i <= getLeaf(n - 1); i++) {
            pheromones[i] = static_cast<int>(pheromones[i] * (1.0 - evaporation_rate));
            if (pheromones[i] < 1) {
                pheromones[i] = 1; 
            }
        }
        propagateAll();
    }
    void deposit(int node, int amount) {
        node = getLeaf(node);
        pheromones[node] += amount;
        propagate(node);
    }
    void invalidate(int node) {
        node = getLeaf(node);
        if (pheromones[node] == 0) {
            return;
        }
        pheromones[node] = 0;
        propagate(node);
    }
    void invalidateVector(const std::vector<int>& nodes) {
        for (int node : nodes) {
            pheromones[getLeaf(node)] = 0;
        }
        propagateAll();
    }

    private:

    void propagate(int node) {
        while(node > 0) {
            pheromones[getFather(node)] = pheromones[node] + pheromones[getBrother(node)];
            node = getFather(node);
        }
    }
    void propagateAll() {
        for (int i = tree_size / 2 - 1; i >= 0; i--) {
            pheromones[i] = pheromones[getLeftChild(i)] + pheromones[getRightChild(i)];
        }
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
    inline int getNodeFromLeaf(int leaf) {
        return leaf - tree_size / 2;
    }

    inline int getFather(int node) {
        return (node - 1) / 2;
    }
    inline int getLeftChild(int node) {
        return (node << 1) + 1;
    }
    inline int getRightChild(int node) {
        return (node << 1) + 2;
    }
    inline int getBrother(int node) {
        // returns -1 if root
        if (node % 2 == 0) {
            return node - 1;
        } else {
            return node + 1;
        }
    }
    inline bool isLeaf(int node) {
        return node >= tree_size / 2;
    }

    public:

    int maxSearch(int father=0){

        if (pheromones[getLeftChild(father)] == 0 && pheromones[getRightChild(father)] == 0) {
            return -1;
        }

        while (!isLeaf(father)) {
            if (pheromones[getLeftChild(father)] < pheromones[getRightChild(father)]){
                father = getRightChild(father);
            }else{
                father = getLeftChild(father);
            }
        }

        return getNodeFromLeaf(father);
    }
    int randSearch(int father=0){

        if (pheromones[getLeftChild(father)] == 0 && pheromones[getRightChild(father)] == 0) {
            return -1;
        }

        while (!isLeaf(father)) {
            if (pheromones[getLeftChild(father)] != 0 && pheromones[getRightChild(father)] != 0) {
                father = getLeftChild(father) + rand()%2;
            } else {
                if (pheromones[getLeftChild(father)] != 0 ) {
                    father = getLeftChild(father);
                } else {
                    father = getRightChild(father);
                }
            }
        }

        return getNodeFromLeaf(father);
    }
    int pondRandSearch(int father=0){

        if (pheromones[getLeftChild(father)] == 0 && pheromones[getRightChild(father)] == 0) {
            return -1;
        }

        while (!isLeaf(father)) {
            if (rand() % (pheromones[getLeftChild(father)] + pheromones[getRightChild(father)]) < pheromones[getLeftChild(father)]) {
                father = getLeftChild(father);
            }else{
                father = getRightChild(father);
            }
        }

        return getNodeFromLeaf(father);
    }

};
