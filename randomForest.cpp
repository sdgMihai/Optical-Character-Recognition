// copyright Luca Istrate, Andrei Medar
#include "randomForest.h"
#include <iostream>
#include <random>
#include <vector>
#include <string>
#include "decisionTree.h"

using std::vector;
using std::pair;
using std::string;
using std::mt19937;

vector<vector<int>> get_random_samples(const vector<vector<int>> &samples,
                                       int num_to_return) {
    // generator de numere random
    mt19937 rng;
    int i;
    // adaugarea unui seed random
    rng.seed(std::random_device()());
    int size = samples.size();  // dimensiunea matricei samples
    // distributie in intervalul [0, size-1]
    std::uniform_int_distribution<mt19937::result_type> dist(0, size - 1);

    vector<vector<int>> ret;
    /*
    // vectorul alreadyAdded are grija de cazurile in care
    // o anumita linie a fost adaugata deja.
    // alreadyAdded[i] e 0 daca linia i nu a mai fost adaugata
    // si 0 altfel
    */
    vector<bool> alreadyAdded(size, 0);

    for (i = 0; i < num_to_return; i++) {
        // generarea unui index random
        int idx = dist(rng);

        if (alreadyAdded[idx] == 0) {
            ret.push_back(samples[idx]);
            alreadyAdded[idx] = 1;
        } else {
            /*
            // daca gasim o linie care a mai fost deja adaugata
            // atuncim mai adaugam inca o linie de generat
            */
            num_to_return++;
            continue;
        }
    }

    return ret;
}

RandomForest::RandomForest(int num_trees, const vector<vector<int>> &samples)
    : num_trees(num_trees), images(samples) {}

void RandomForest::build() {
    // Aloca pentru fiecare Tree cate n / num_trees
    // Unde n e numarul total de teste de training
    // Apoi antreneaza fiecare tree cu testele alese
    assert(!images.empty());
    vector<vector<int>> random_samples;

    int data_size = images.size() / num_trees;

    for (int i = 0; i < num_trees; i++) {
        // cout << "Creating Tree nr: " << i << endl;
        random_samples = get_random_samples(images, data_size);

        // Construieste un Tree nou si il antreneaza
        trees.push_back(Node());
        trees[trees.size() - 1].train(random_samples);
    }
}

int RandomForest::predict(const vector<int> &image) {
    // TODO(you)
    // Va intoarce cea mai probabila prezicere pentru testul din argument
    // se va interoga fiecare Tree si se va considera raspunsul final ca
    // fiind cel majoritar

    // folosim metoda vectorului de frecventa
    int frec[10] = {0};
    int a;
    for (int i = 0; i < num_trees; ++i)
    {
        a = trees[i].predict(image);
        frec[a]++;
    }
    int maxim = frec[0];
    for (int i = 1; i < 10; ++i) {
        if (maxim < frec[i])
            maxim = frec[i];
    }
    return maxim;
}
