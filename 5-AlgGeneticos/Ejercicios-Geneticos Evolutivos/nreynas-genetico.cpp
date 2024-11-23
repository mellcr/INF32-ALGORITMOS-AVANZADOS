/**
 * Implementacion de algoritmo Genetico para encontrar una solucion al 
 *  problema de las N-Reinas
 *
 * Autor: Dr. Edwin Villanueva
 *
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <numeric> // for iota

using namespace std;

struct Individual {
    /* Cada elemento del chromosome indica la posición de una reina en una columna específica del tablero. 
     * Por ejemplo, si el vector es [2, 4, 7, 3, 0, 6, 1, 5], esto significa que la reina de la 
     * columna 0 está en la fila 2, la reina de la columna 1 está en la fila 4, y así sucesivamente.*/
    vector<int> chromosome; 
    int fitness;   // Valor de fitness del individuo.

    // Constructor que inicializa el cromosoma con el vector dado y establece el fitness en -1.
    Individual(vector<int> chromo) : chromosome(chromo), fitness(-1) {}
    Individual() : fitness(-1) {}  // Constructor por defecto que inicializa el fitness en -1.
};

void calculate_fitness(Individual& ind) {
    //Calcula el fitness de un cromosoma: nro de pares de reinas no atacadas) 
    int n = ind.chromosome.size();
    int fitness = 0;
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (ind.chromosome[j] != ind.chromosome[i] && 
                ind.chromosome[j] != ind.chromosome[i] - (j - i) && 
                ind.chromosome[j] != ind.chromosome[i] + (j - i)) {
                fitness++;
            }
        }
    }
    ind.fitness = fitness;
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

pair<Individual, Individual> crossover_orderpermutation(Individual& parent1, Individual& parent2) {
    /* Uniform order-based crossover: Genera 2 cromosomas hijos  que tambien deben ser permutaciones
       Retorna dos nuevos individuos del cruzamiento de permutacion entre parent1 y parent2"
       Escoge aleatoriamente la mitad de posiciones del cromosoma parent1 y lo copia a un hijo child1_chromo 
       en las mismas posiciones. Los numeros faltantes los copia de other en el mismo orden en que aparecen en parent2 "
       El hijo child2_chromo se crea de la misma forma intercambiando parent1 por parent2"
    */
    int size = parent1.chromosome.size();
    vector<int> child1_chromo(size, -1);
    vector<int> child2_chromo(size, -1);
    vector<int> pos_constantes;

    for (int i = 0; i < size / 2; ++i) {
        int pos = rand() % size;
        pos_constantes.push_back(pos);
    }

    // Copia los valores en las posiciones constantes del padre a los hijos
    for (int pos : pos_constantes) {
        child1_chromo[pos] = parent1.chromosome[pos];
        child2_chromo[pos] = parent2.chromosome[pos];
    }
    
   // Función lambda para rellenar los valores faltantes
    auto fill_remaining = [](vector<int>& child_chromo, const vector<int>& parent_chromo) {
        int idx = 0;
        for (int gene : parent_chromo) {
            if (find(child_chromo.begin(), child_chromo.end(), gene) == child_chromo.end()) {
                while (child_chromo[idx] != -1) ++idx;
                child_chromo[idx] = gene;
            }
        }
    };

    // Rellena los valores faltantes en los hijos
    fill_remaining(child1_chromo, parent2.chromosome);
    fill_remaining(child2_chromo, parent1.chromosome);

    return make_pair(Individual(child1_chromo), Individual(child2_chromo));
}

Individual mutate_position(Individual& ind) {
    Individual mutated(ind.chromosome);
    int mutGene = rand() % mutated.chromosome.size();
    int newAllele = rand() % mutated.chromosome.size() + 1;
    mutated.chromosome[mutGene] = newAllele;
    return mutated;
}

Individual mutate_swap(Individual& ind) {
    Individual mutated(ind.chromosome);
    int mutGen1 = rand() % mutated.chromosome.size();
    int mutGen2 = rand() % mutated.chromosome.size();
    swap(mutated.chromosome[mutGen1], mutated.chromosome[mutGen2]);
    return mutated;
}

vector<Individual> init_population(int population_size, int chromosome_length) {
    vector<Individual> population;
    for (int i = 0; i < population_size; ++i) {
        vector<int> chromosome(chromosome_length);
        iota(chromosome.begin(), chromosome.end(), 0); //genera numeros consecutivos [0,1,...,chromosome_length-1]
        random_shuffle(chromosome.begin(), chromosome.end()); //permuta aleatoriamente los numeros
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

void evaluate_population(vector<Individual>& population) {
    for (Individual& ind : population) {
        if (ind.fitness == -1) {
            calculate_fitness(ind);
        }
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

void genetic_algorithm(vector<Individual>& population, int generations, double mutation_rate, int tournament_size, const string& crossover_method, const string& mutation_method) {
    int popsize = population.size();
    evaluate_population(population);   // Evalua la poblacion inicial
    auto best_individual = max_element(population.begin(), population.end(), [](Individual& a, Individual& b) { //encuentra mejor individuo
        return a.fitness < b.fitness;
    });
    vector<int> bestfitness = {best_individual->fitness}; //mejor fitness de pob. inicial
    cout << "Poblacion inicial, best_fitness = " << best_individual->fitness << endl;

    for (int g = 0; g < generations; ++g) {  // Por cada generacion
       
        //Selecciona las parejas de padres (mating pool) para cruzamiento con metodo de torneo
        vector<pair<Individual, Individual>> mating_pool;
        for (int i = 0; i < popsize / 2; ++i) {
            mating_pool.push_back(make_pair(tournament_selection(population, tournament_size), tournament_selection(population, tournament_size)));
        }

        //Crea la poblacion descendencia cruzando las parejas del mating pool
        vector<Individual> offspring_population;
        for (auto& parents : mating_pool) {
            pair<Individual, Individual> children;
            if (crossover_method == "onepoint") {
                children = crossover_onepoint(parents.first, parents.second);
            } else if (crossover_method == "uniform") {
                children = crossover_uniform(parents.first, parents.second);
            } else if (crossover_method == "orderpermutation") {
                children = crossover_orderpermutation(parents.first, parents.second);
            }
            offspring_population.push_back(children.first);
            offspring_population.push_back(children.second);
        }

        //Aplica el operador de mutacion con probabilidad mutation_rate en cada hijo generado
        for (Individual& ind : offspring_population) {
            if ((double)rand() / RAND_MAX < mutation_rate) {
                if (mutation_method == "position") {
                    ind = mutate_position(ind);
                } else if (mutation_method == "swap") {
                    ind = mutate_swap(ind);
                }
            }
        }

        //Evalua la poblacion descendencia creada
        evaluate_population(offspring_population);
        
        //Selecciona popsize individuos para la sgte. generación
        population = select_survivors_ranking(population, offspring_population, popsize);

        //Almacena el fitness del mejor individuo en el hitorico 
        best_individual = max_element(population.begin(), population.end(), [](Individual& a, Individual& b) {
            return a.fitness < b.fitness;
        });
        bestfitness.push_back(best_individual->fitness);

        if (g % 5 == 0) {  // muestra como va el algoritmo cada 5 generaciones
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

    const int SIZE_CHROMOSOME = 30;
    const int NUM_INDIVIDUALS = 20;
    const int GENERATIONS = 100;
    const double MUTATION_RATE = 0.5;
    const int TOURNAMENT_SIZE = 3;

    // obtiene poblacion inicial
    vector<Individual> population = init_population(NUM_INDIVIDUALS, SIZE_CHROMOSOME);

    // llama al algoritmo genetico
    genetic_algorithm(population, GENERATIONS, MUTATION_RATE, TOURNAMENT_SIZE, "orderpermutation", "swap");

    return 0;
}


