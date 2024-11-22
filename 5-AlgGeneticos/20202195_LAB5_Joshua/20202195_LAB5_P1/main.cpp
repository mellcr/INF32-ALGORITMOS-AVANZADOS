/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: alulab14
 *
 * Created on 22 de junio de 2024, 08:09 AM
 */

#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Item {
    double precioActual;
    double precioOptimistaFuturo;
    double precioPesimistaFuturo;

    Item(double pa, double pfo, double pfp) : precioActual(pa), 
        precioOptimistaFuturo(pfo), precioPesimistaFuturo(pfp){}
};

struct Individual {
    vector<int> chromosome;
    int fitness;

    Individual(vector<int> chromo) : chromosome(chromo), fitness(0) {}
};

void calculate_fitness(Individual& ind, vector<Item>& itemPool, int maxInversion) {
    int inversionActual=0;
    int total_value = 0;
    for (int i = 0; i < ind.chromosome.size(); ++i) {
        if (ind.chromosome[i] == 1) {
            total_value += abs(itemPool[i].precioOptimistaFuturo-itemPool[i].precioActual)
                    -abs(itemPool[i].precioPesimistaFuturo-itemPool[i].precioActual);
            inversionActual+=itemPool[i].precioActual;
        }
    }
    if(inversionActual > maxInversion)
        ind.fitness=0;
    else
        ind.fitness=total_value;
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

int calculate_fitness1(vector<int> chromosome, int maxInversion,
        vector<Item> itemPool) {
    int inversionActual=0;
    int total_value = 0;
    for (int i = 0; i <chromosome.size(); ++i) {
        if (chromosome[i] == 1) {
            total_value += abs(itemPool[i].precioOptimistaFuturo-itemPool[i].precioActual)
                    -abs(itemPool[i].precioPesimistaFuturo-itemPool[i].precioActual);
            inversionActual+=itemPool[i].precioActual;
        }
    }
    if(inversionActual > maxInversion)
        return 0;
    else
        return total_value;
}

vector<Individual> init_population1(int population_size, int chromosome_length, 
        int maxInversion,vector<Item> itemPool) {
    vector<Individual> population;
    for (int i = 0; i < population_size; ++i) {
        vector<int> chromosome(chromosome_length);
        for (int j = 0; j < chromosome_length; ++j) {
            chromosome[j] = rand() % 2;
        }
        /*Verificamos si la solucion cumple*/
        if(calculate_fitness1(chromosome,maxInversion,itemPool))
            population.push_back(Individual(chromosome));
        else    /*En caso cumpla disminuimos en uno el i ya que no encontramos una solucion valida*/
            i--;
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

void evaluate_population(vector<Individual>& population, vector<Item>& itemPool, 
        int maxInversion) {
    for (Individual& ind : population) {
        calculate_fitness(ind, itemPool, maxInversion);
    }
}

vector<Individual> select_survivors_ranking(vector<Individual>& population, 
        vector<Individual>& offspring_population, int numsurvivors) {
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

int genetic_algorithm(vector<Individual>& population, vector<Item>& assetPool, 
        int maxInversion, int generations, double mutation_rate, int tournament_size) {
    int popsize = population.size();
    evaluate_population(population, assetPool, maxInversion);
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
            mating_pool.push_back(make_pair(tournament_selection(population, tournament_size), 
                    tournament_selection(population, tournament_size)));
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

        evaluate_population(offspring_population, assetPool, maxInversion); // evalua poblacion descendencia
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
    int i=0;
    int suma=0;
    for (int gene : best_individual->chromosome) {
        if(gene==1){
            suma+=assetPool[i].precioActual;
        }
        i++;
    }
    cout<<"Inversion Inicial para el mejor fitness "<<suma<<endl;
    return best_individual->fitness;
}

int main() {
    srand(time(0));

    const int NUM_ITEMS = 20;
    const int MAX_INVERSION=1000;

    // crea el pool de items
    vector<Item> assetPool={
            {100,150,80},{200,250,180},{150,220,130},{120,180,100},{180,230,160},
            {110,170,90},{130,200,110},{160,210,140},{140,190,120},{210,270,190},
            {170,240,150},{190,260,170},{220,300,200},{200,280,180},{180,250,160},
            {195,260,175},{205,275,185},{215,285,195},{225,295,205},{235,305,215},
    };
    const int POPSIZE = 10;
    const int GENERATIONS = 100;
    const double MUTATION_RATE = 0.8;
    const int TOURNAMENT_SIZE = 3;
    int solucionesEncontradas[10];
    // inicializa poblacion
    for(int i=0; i<10; i++){
        /*Pregunta 1*/
        //vector<Individual> population = init_population(POPSIZE, NUM_ITEMS);
        /*Pregunta 2*/
        vector<Individual> population = init_population1(POPSIZE, NUM_ITEMS,
                MAX_INVERSION,assetPool);
        // corre el algoritmo genetico
        solucionesEncontradas[i]=genetic_algorithm(population, assetPool, MAX_INVERSION, GENERATIONS, 
                MUTATION_RATE, TOURNAMENT_SIZE);
    }
    cout<<"Soluciones encontradas: "<<endl;
    for(int i=0; i<10; i++)
        cout<<solucionesEncontradas[i]<<" ";
    cout<<endl;
    
    return 0;
}

