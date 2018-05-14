// copyright Luca Istrate, Andrei Medar

#include "./decisionTree.h"  // NOLINT(build/include)
#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <limits>
#include <memory>
#include <random>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using std::string;
using std::pair;
using std::vector;
using std::unordered_map;
using std::make_shared;
using std::mt19937;

// structura unui nod din decision tree
// splitIndex = dimensiunea in functie de care se imparte
// split_value = valoarea in functie de care se imparte
// is_leaf si result sunt pentru cazul in care avem un nod frunza
Node::Node() {
    is_leaf = false;
    left = nullptr;
    right = nullptr;
}

void Node::make_decision_node(const int index, const int val) {
    split_index = index;
    split_value = val;
}

void Node::make_leaf(const vector<vector<int>> &samples,
                     const bool is_single_class) {
    is_leaf = true;
    // Seteaza nodul ca fiind de tip frunza (modificati is_leaf si result)
    // is_single_class = true -> toate testele au aceeasi clasa (acela e result)
    // is_single_class = false -> se alege clasa care apare cel mai des
}

pair<int, int> find_best_split(const vector<vector<int>> &samples,
                               const vector<int> &dimensions) {
    // TODO(you)
    // Intoarce cea mai buna dimensiune si valoare de split dintre testele
    // primite. Prin cel mai bun split (dimensiune si valoare)
    // ne referim la split-ul care maximizeaza IG
    // pair-ul intors este format din (split_index, split_value)

    int splitIndex = -1, splitValue = -1;
    return pair<int, int>(splitIndex, splitValue);
}

void Node::train(const vector<vector<int>> &samples) {
    // TODO(you)
    // Antreneaza nodul curent si copii sai, daca e nevoie
    // 1) verifica daca toate testele primite au aceeasi clasa (raspuns)
    // Daca da, acest nod devine frunza, altfel continua algoritmul.
    // 2) Daca nu exista niciun split valid, acest nod devine frunza. Altfel,
    // ia cel mai bun split si continua recursiv
}

int Node::predict(const vector<int> &image) const {
    // TODO(you)
    // Intoarce rezultatul prezis de catre decision tree
    return 0;
}

bool same_class(const vector<vector<int>> &samples) {
    // TODO(you)
    // Verifica daca testele primite ca argument au toate aceeasi
    // clasa(rezultat). Este folosit in train pentru a determina daca
    // mai are rost sa caute split-uri

    int i;
    /*
    // caut prin toate sample-urile
    // iar daca gasesc 2 sample-uri consecutive de clase diferite
    // functia intoarce false
    // daca toate au aceeasi clasa atunci va intoarce true
    */
    for (i = 0; i < samples.size() - 1; i++)
        if (samples[i][0] != samples[i + 1][0])
            return false;

    return true;
}

float get_entropy(const vector<vector<int>> &samples) {
    // Intoarce entropia testelor primite
    assert(!samples.empty());
    vector<int> indexes;

    int size = samples.size();
    for (int i = 0; i < size; i++) indexes.push_back(i);

    return get_entropy_by_indexes(samples, indexes);
}

float get_entropy_by_indexes(const vector<vector<int>> &samples,
                             const vector<int> &index) {
    // TODO(you)
    // Intoarce entropia subsetului din setul de teste total(samples)
    // Cu conditia ca subsetul sa contina testele ale caror indecsi se gasesc in
    // vectorul index (Se considera doar liniile din vectorul index)
    /*
	// parcurg liniile desemnate de vectorul index
	// calculez frecventa aparitiei fiecarui numar
	*/
	int frec[10] = { 0 };
	double entropy = 0;
	for (int i = 0; i < samples.size(); ++i) {
		frec[samples[i][0]]++;
	}
	// aplic formula entropiei
	for (i = 0; i < 10; ++i) {
		double probI = (frec[i] / index.size());
		if (frec[i])
			entropy += probI * log2(probI);
	}
    return entropy;
}

vector<int> compute_unique(const vector<vector<int>> &samples, const int col) {
    // Intoarce toate valorile (se elimina duplicatele)
    // care apar in setul de teste, pe coloana col
    int i;
    vector<int> uniqueValues;

    /*
    // parcurge toata coloana 'col', iar inainte de a adauga un element
    // il cauta in vectorul uniqueValues pentru a nu exista dubluri
    // in caz ca a gasit elementul, atunci nu il mai adauga
    */
    for (i = 0; i < samples.size(); i++) {
        auto start = uniqueValues.begin();
        auto finish = uniqueValues.end();
        auto it = std::find(start, finish, samples[i][col]);
        if (it == finish)  // adica elementul nu a mai fost adaugat inainte
            uniqueValues.push_back(samples[i][col]);  // il adaug in vector
    }

    return uniqueValues;
}

pair<vector<vector<int>>, vector<vector<int>>> split(
    const vector<vector<int>> &samples, const int split_index,
    const int split_value) {
    // Intoarce cele 2 subseturi de teste obtinute in urma separarii
    // In functie de split_index si split_value
    vector<vector<int>> left, right;

    auto p = get_split_as_indexes(samples, split_index, split_value);
    for (const auto &i : p.first) left.push_back(samples[i]);
    for (const auto &i : p.second) right.push_back(samples[i]);

    return pair<vector<vector<int>>, vector<vector<int>>>(left, right);
}

pair<vector<int>, vector<int>> get_split_as_indexes(
    const vector<vector<int>> &samples, const int split_index,
    const int split_value) {
    // Intoarce indecsii sample-urilor din cele 2 subseturi obtinute in urma
    // separarii in functie de split_index si split_value
    vector<int> left, right;
    int i;

    /*
    // se parcurge toata coloan split_index
    // si sunt creati cei doi vectori, left si right
    // in functie de split_index si split_values
    */
    for (i = 0; i < samples.size(); i++) {
        if (samples[i][split_index] <= split_value)
            left.push_back(i);
        else
            right.push_back(i);
    }

    return make_pair(left, right);
}

vector<int> random_dimensions(const int size) {
    // Intoarce sqrt(size) dimensiuni diferite pe care sa caute splitul maxim
    // Precizare: Dimensiunile gasite sunt > 0 si < size


    vector<int> rez;
    mt19937 rng;  // generator de numere random
    int i;
    rng.seed(std::random_device()());  // adaugarea unui seed random
    int dim = sqrt(size);
    // distributie in intervalul [1, size-1]
    std::uniform_int_distribution<mt19937::result_type> dist(1, size - 1);
    vector<bool> alreadyAdded(size, 0);

    /*
    // Generam numere random si verificam daca au mai fost deja adaugate
    // folosind vectorul alreadyAdded.
    // Daca au mai fost adaugate, atunci incrementam valoarea lui dim
    // pentru a mai face inca o cautare.
    */
    for (i = 0; i < dim; i++) {
        int idx = dist(rng);

        if (alreadyAdded[idx] == 0) {
            rez.push_back(idx);
            alreadyAdded[idx] = 1;
        }
        else
            dim++;
    }

    return rez;
}
