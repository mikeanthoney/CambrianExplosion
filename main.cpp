// main.cpp for CambrianExplosion

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>

// Organism is a class that makes copies of itself every time
// it meets the fitness requirements of the ecological niche it occupies
// and has sufficient resources.
class Organism
{
private:
    // DNA determines fitness (at least one gene - organisms that occupy the same niche access
    // access resources in order of how many genes meet the niche requirements
    std::string organismDNA; // 4 genes comprising 4^4 possible combinations of C, G, A, and T
    bool statusAlive;
    int energyStore; // place for storing building blocks for next generation
    int energyCapacity;
    int energyWaste;
    int biteSize;
    int generationNumber;
    int parentOrganism;
    int iterationBorn;
    int iterationDied;
    int lifeSpan;
    int numberOffspring;// new


public:
    Organism(std::string dna="XXXXXXXXXXXXXXXX", bool status=false, int stored=4, int capacity=8, int waste=0,
             int bSize=2, int gNumber=1, int parent=0, int born=0, int died=0, int span=0,int brood=0):
        organismDNA(dna), statusAlive(status), energyStore(stored), energyCapacity(capacity), energyWaste(waste),
        biteSize(bSize), generationNumber(gNumber), parentOrganism(parent), iterationBorn(born), iterationDied(died),
        lifeSpan(span), numberOffspring(brood)
    {

    }

    void Reproduce(); // Make copies of itself every time it has sufficient resources
    int Excrete(); // Take in resources from environment to power and build DNA
    void Metabolize(); // Sort ingested materials into material and energy. Break resources into useable components for reproduction. Add material to the materialStore - if there is space.
    void Struggle(); // Check fitness, energy store, and determine if organism survives to the next round
    int Bite(int);
    void Move(); // Move from location if unable to find resources (energy or materials)
    void setDNA(std::string);
    void setEnergyStore(int);
    int getEnergyStore();
    void setEnergyCapacity(int);
    int getEnergyCapacity();
    void setBiteSize(int);
    void setGenerationNumber(int);
    int getGenerationNumber();
    void setStatusAlive(bool);
    bool getStatusAlive();
    void setParentOrganism(int);
    int getParentOrganism();
    void setIterationBorn(int);
    int getIterationBorn();
    void setIterationDied(int);
    int getIterationDied();
    int getLifeSpan();
    void incrementNumberOffspring();
    int getNumberOffspring();

protected:

};

void Organism::incrementNumberOffspring()
{
    numberOffspring++;
}

int Organism::getNumberOffspring()
{
    return numberOffspring;
}

int Organism::getLifeSpan()
{
    return iterationDied - iterationBorn;
};

void Organism::setIterationDied(int iteration)
{
    iterationDied = iteration;
};

int Organism::getIterationDied()
{
    return iterationDied;
};

void Organism::setIterationBorn(int iteration)
{
    iterationBorn = iteration;
};

int Organism::getIterationBorn()
{
    return iterationBorn;
};

void Organism::setEnergyStore(int energy)
{
    energyStore = energy;
};

int Organism::getEnergyStore()
{
    return energyStore;
};

void Organism::setParentOrganism(int parent)
{
    parentOrganism = parent;
};

int Organism::getParentOrganism()
{
    return parentOrganism;
};


void Organism::setEnergyCapacity(int energy)
{
    energyCapacity = energy;
};

int Organism::getEnergyCapacity()
{
    return energyCapacity;
};

void Organism::setBiteSize(int bitesize)
{
    biteSize = bitesize;
};

void Organism::setGenerationNumber(int generation)
{
    generationNumber = generation;
};

int Organism::getGenerationNumber()
{
    return generationNumber;
};

void Organism::setStatusAlive(bool Status)
{
    statusAlive = Status;
}

bool Organism::getStatusAlive()
{
    return statusAlive;
}

int Organism::Bite(int availableEnergy)
{
    if(availableEnergy >= biteSize)
    {
        energyStore += biteSize;
        return biteSize;
    }
    else if((availableEnergy < biteSize) && (availableEnergy > 0))
    {
        energyStore += availableEnergy;
        return availableEnergy;
    }
    else{return 0;}
};

void Organism::setDNA(std::string dna)
{
    organismDNA = dna;
};

void Organism::Reproduce()
{
    // Return an Organism Object with a potentially mutated version of parent DNA.
};

int Organism::Excrete()
{
    if (energyStore > energyCapacity)
    {
        energyWaste = energyStore - energyCapacity;
        energyStore = energyCapacity;
    }
    else{energyWaste = 0;}

    return energyWaste;
};

void Organism::Metabolize()
{
    --energyStore;
};


void Organism::Struggle()
{

};

void Organism::Move()
{
    // Organism will move to an adjacent location if unable to find resources (material/energy). - genes will determine direction and rate
};

using namespace std;

int main()
{
    int organismCounter,livingCount = 0, i;
    int iRandom;
    srand(time(0));
    int iterationCounter = 0;
    int maxIterations = 165;
    int populationVsIteration[maxIterations];
    int environmentEnergy = 500;
    int externalEnergy = 500;
    int populationLevel = 1;
    int runningPopulation = 1;
    int maxPopulation = 10000;
    ofstream populationHistory;
    ofstream populationRecord;
    populationHistory.open ("history.csv");
    populationRecord.open ("record.csv");
    Organism population[maxPopulation];
    cout << "Welcome to the Cambrian world!" << endl;
    population[0].setStatusAlive(true);
    population[0].setDNA("ACGTCGAATCTAGGGA\n");
    population[0].setIterationDied(maxIterations);
    cout<<environmentEnergy<<"\n";

    while(iterationCounter < maxIterations)
    {
        environmentEnergy += externalEnergy;
        for(organismCounter = 0; organismCounter < populationLevel; organismCounter++)
        {
            /*RANDOM DEATH PHASE*/
            /*If the organism is killed during the Random Death Phase, skip the Life Cycle Phase*/
            if(population[organismCounter].getStatusAlive())
            {

                iRandom = rand() % 100;
                if(iRandom < 10)
                {
                    population[organismCounter].setStatusAlive(false); //organism died due to random event
                    population[organismCounter].setIterationDied(iterationCounter);
                    runningPopulation--;
                }
            }

            /*LIFE CYCLE PHASE*/
            /*If the organism in the population array is not alive, skip the Life Cycle Phase*/
            if(population[organismCounter].getStatusAlive())
            {
                /*METABOLISM PHASE*/
                /*The organism will first metabolize energy to search for food and mates*/
                population[organismCounter].Metabolize();

                /*If organisms energy store has reaches zero during the metabolism phase, it dies*/
                if(population[organismCounter].getEnergyStore() == 0)
                {
                        population[organismCounter].setStatusAlive(false); // organism starved to death
                        population[organismCounter].setIterationDied(iterationCounter);
                        runningPopulation--;
                        environmentEnergy = environmentEnergy + 5; // organism's body becomes energy
                }

                /*CONSUMPTION PHASE*/
                /*If environment energy is zero - skip consumption phase (not possible to eat, yet)*/
                if (environmentEnergy > 0)
                {
                    environmentEnergy = environmentEnergy - population[organismCounter].Bite(environmentEnergy);
                    environmentEnergy = environmentEnergy + population[organismCounter].Excrete();
                }

                /*REPRODUCTION PHASE*/
                /*If population limit has been reached - skip reproduction phase (not possible to reproduce)*/
                if (populationLevel < maxPopulation)
                {
                    /*If organism has enough energy, the organism reproduces*/
                    if(population[organismCounter].getEnergyStore() == population[organismCounter].getEnergyCapacity())
                    {
                        runningPopulation++; // keep track of the total number of organisms created
                        population[organismCounter].setEnergyStore(population[organismCounter].getEnergyStore() - 3);
                        population[organismCounter].incrementNumberOffspring();
                        population[populationLevel].setStatusAlive(true);
                        population[populationLevel].setIterationBorn(iterationCounter);
                        population[populationLevel].setIterationDied(maxIterations);
                        population[populationLevel].setDNA("ACGTCGAATCTAGGGA\n");
                        population[populationLevel].setGenerationNumber(population[organismCounter].getGenerationNumber()+ 1);
                        population[populationLevel].setParentOrganism(organismCounter);
                        populationLevel++;
                    }
                }
            }

        }

        /*Track the population at each iteration to show population growth and decline over time(iteration)*/
        populationVsIteration[iterationCounter] = runningPopulation;
        iterationCounter++;
    }

    /*Keep a record of each organism's meta data throughout the case study*/
    populationRecord<<"Organism, Iteration Born, Iteration Died, Life Span, Generation, Parent Organism, Number of Offspring, Alive at End\n";
    for(i = 0; i < populationLevel; i++)
    {
        if(population[i].getStatusAlive())
        {
            livingCount++;
        }
        populationRecord<<i<<","<<population[i].getIterationBorn()<<","<<population[i].getIterationDied()<<","<<population[i].getLifeSpan()<<","<<population[i].getGenerationNumber()<<","<<population[i].getParentOrganism()<<","<<population[i].getNumberOffspring()<<","<<population[i].getStatusAlive()<<"\n";
    }
    std::cout<<"Living: "<<livingCount;

    /*Keep a record of the population throughout each iteration for this case study*/
    populationHistory<<"Iteration, Population\n";
    for(i = 0; i < maxIterations; i++)
    {
        populationHistory<<i<<","<<populationVsIteration[i]<<"\n";
    }

    return 0;
}
