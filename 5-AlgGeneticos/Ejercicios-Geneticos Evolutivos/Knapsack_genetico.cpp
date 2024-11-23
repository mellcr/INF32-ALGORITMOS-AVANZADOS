/**
 * Implementacion de Algoritmo de Genetico para resolver el problema de la mochila (knapsack). 
 * 
 * Autor: Dr. Edwin Villanueva
 *
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Item {
    int value;
    int weight;

    Item(int v, int w) : value(v), weight(w) {}
};

struct Individual {
    vector<int> chromosome;
    int fitness;

    Individual(vector<int> chromo) : chromosome(chromo), fitness(0) {}
};

void calculate_fitness(Individual& ind, vector<Item>& itemPool, int max_weight) {
    int total_weight = 0;
    int total_value = 0;
    for (int i = 0; i < ind.chromosome.size(); ++i) {
        if (ind.chromosome[i] == 1) {
            total_weight += itemPool[i].weight;
            total_value += itemPool[i].value;
        }
    }
    ind.fitness = (total_weight <= max_weight) ? total_value : 0;
}

pair<Individual, Individual> crossover_onepoint(Individual& parent1, Individual& parent2) {
    int size = parent1.chromosome.size();
    int crossover_point = rand() % size;
    vector<int> child1_chromo(size);
    vector<int> child2_chromo(size);

    for (int i = 0; i < size; ++i) {
        child1_chromo[i] = (i < crossover_point) ? parent1.chromosome[i] : parent2.chromosome[i];
        child2_chromo[i] = (i < crossover_point) ? parent2.chromosome[i] : parent1.chromosome[i];
    }

    return make_pair(Individual(child1_chromo), Individual(child2_chromo));
}

pair<Individual, Individual> crossover_uniform(Individual& parent1, Individual& parent2) {
    int size = parent1.chromosome.size();
    vector<int> child1_chromo(size);
    vector<int> child2_chromo(size);

    for (int i = 0; i < size; ++i) {
        if (rand() % 2) {
            child1_chromo[i] = parent1.chromosome[i];
            child2_chromo[i] = parent2.chromosome[i];
        } else {
            child1_chromo[i] = parent2.chromosome[i];
            child2_chromo[i] = parent1.chromosome[i];
        }
    }

    return make_pair(Individual(child1_chromo), Individual(child2_chromo));
}

void mutation_flip(Individual& ind) {
    int position = rand() % ind.chromosome.size();
    ind.chromosome[position] = 1 - ind.chromosome[position];
}

vector<Individual> init_population(int population_size, int chromosome_length) {
    vector<Individual> population;
    for (int i = 0; i < population_size; ++i) {
        vector<int> chromosome(chromosome_length);
        for (int j = 0; j < chromosome_length; ++j) {
            chromosome[j] = rand() % 2;
        }
        population.push_back(Individual(chromosome));
    }
    return population;
}

Individual tournament_selection(vector<Individual>& population, int tournament_size) {
    vector<Individual> tournament;
    for (int i = 0; i < tournament_size; ++i) {
        int random_index = rand() % population.size();
        tournament.push_back(population[random_index]);
    }

    return *max_element(tournament.begin(), tournament.end(), [](Individual& a, Individual& b) {
        return a.fitness < b.fitness;
    });
}

void evaluate_population(vector<Individual>& population, vector<Item>& itemPool, int max_weight) {
    for (Individual& ind : population) {
        calculate_fitness(ind, itemPool, max_weight);
    }
}

vector<Individual> select_survivors_ranking(vector<Individual>& population, vector<Individual>& offspring_population, int numsurvivors) {
    vector<Individual> next_population;
    population.insert(population.end(), offspring_population.begin(), offspring_population.end());
    sort(population.begin(), population.end(), [](Individual& a, Individual& b) {
        return a.fitness > b.fitness;
    });
    for (int i = 0; i < numsurvivors; ++i) {
        next_population.push_back(population[i]);
    }
    return next_population;
}

void genetic_algorithm(vector<Individual>& population, vector<Item>& itemPool, int max_weight, int generations, double mutation_rate, int tournament_size) {
    int popsize = population.size();
    evaluate_population(population, itemPool, max_weight);
    vector<int> bestfitness;
    auto best_individual = max_element(population.begin(), population.end(), [](Individual& a, Individual& b) {
        return a.fitness < b.fitness;
    });
    bestfitness.push_back(best_individual->fitness);

    cout << "Poblacion inicial, best_fitness = " << best_individual->fitness << endl;

    // loop de generaciones
    for (int g = 0; g < generations; ++g) {
        
        // crea las parejas a cruzarse (mating pool)
        vector<pair<Individual, Individual>> mating_pool;
        for (int i = 0; i < popsize / 2; ++i) {
            mating_pool.push_back(make_pair(tournament_selection(population, tournament_size), tournament_selection(population, tournament_size)));
        }

        // cruza las parejas del mating pool. Cada cruzamiento genera 2 hijos
        vector<Individual> offspring_population;
        for (auto& parents : mating_pool) {  // por cada pareja del mating pool
            // pair<Individual, Individual> children = crossover_onepoint(parents.first, parents.second); // cruzamiento one point
            pair<Individual, Individual> children = crossover_uniform(parents.first, parents.second);  // cruzamiento uniforme

            if ((double)rand() / RAND_MAX < mutation_rate) { // intenta mutar el hijo 1 de acuerdo a la tasa de mutacion
                mutation_flip(children.first);
            }
            if ((double)rand() / RAND_MAX < mutation_rate) { // intenta mutar el hijo 2 de acuerdo a la tasa de mutacion
                mutation_flip(children.second);
            }
            offspring_population.push_back(children.first);  // agrega el hijo 1 a la poblacion descendencia
            offspring_population.push_back(children.second); // agrega el hijo 2 a la poblacion descendencia
        }

        evaluate_population(offspring_population, itemPool, max_weight); // evalua poblacion descendencia
        population = select_survivors_ranking(population, offspring_population, popsize); // selecciona sobrevivientes por ranking

        // obtiene el mejor individuo de la poblacion sobreviviente
        best_individual = max_element(population.begin(), population.end(), [](Individual& a, Individual& b) {
            return a.fitness < b.fitness;
        });
        bestfitness.push_back(best_individual->fitness);

        if (g % 2 == 0) { // reporta cada 2 generaciones
            cout << "Generation " << g << ", Best fitness: " << best_individual->fitness << endl;
        }
    }

    cout << "Mejor individuo en la ultima generacion: [";
    for (int gene : best_individual->chromosome) {
        cout << gene << " ";
    }
    cout << "] con fitness: " << best_individual->fitness << endl;
}

int main() {
    srand(time(0));

    const int NUM_ITEMS = 60;
    const int MAX_ITEM_WEIGHT = 60;
    const int MAX_ITEM_VALUE = 60;
    const int MAX_WEIGHT = 10 * NUM_ITEMS;

    // crea el pool de items
    vector<Item> itemPool;
    for (int i = 0; i < NUM_ITEMS; ++i) {
        int value = rand() % (MAX_ITEM_VALUE + 1);
        int weight = rand() % (MAX_ITEM_WEIGHT + 1);
        itemPool.emplace_back(value, weight);
        cout << "Item " << i << ": Value = " << itemPool[i].value << ", Weight = " << itemPool[i].weight << endl; // Imprime ítem
    }

    const int POPSIZE = 50;
    const int GENERATIONS = 100;
    const double MUTATION_RATE = 0.5;
    const int TOURNAMENT_SIZE = 3;

    // inicializa poblacion
    vector<Individual> population = init_population(POPSIZE, NUM_ITEMS);

    // corre el algoritmo genetico
    genetic_algorithm(population, itemPool, MAX_WEIGHT, GENERATIONS, MUTATION_RATE, TOURNAMENT_SIZE);

    return 0;
}
