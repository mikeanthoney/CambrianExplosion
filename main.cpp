// main.cpp for CambrianExplosion

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>

/**<Organism is a class that tracks internal parameters for energy as well as meta data created throughout it's life cycle*/
class Organism
{
private:
    std::string organismDNA;/**< Unique code for organism that is shared with offspring (but may mutate) */
    bool statusAlive;       /**< Track whether organism is alive or not */
    int energyStore;        /**< Place for storing building blocks for survival and reproduction */
    int energyCapacity;     /**< The total amount of energy that can be contained in an organism */
    int energyWaste;        /**< Amount of energy expelled after consumption */
    int metabolicRate;      /**< Amount of energy burned by organism during metabolic phase */
    int biteSize;           /**< Amount of energy pulled out of environment during each consumption phase */
    int generationNumber;   /**< Relative distance from original ancestor */
    int parentOrganism;     /**< Organism that gave birth to this organism */
    int iterationBorn;      /**< Iteration that this organism was born */
    int iterationDied;      /**< Iteration that this organism died */
    int lifeSpan;           /**< Total number of iterations survived by this organism */
    int numberOffspring;    /**< Number of offspring produced by this organism */

public:
    Organism(std::string dna="XXXXXXXXXXXXXXXX", bool status=false, int stored=4, int capacity=8, int waste=0, int metaRate=1,
             int bSize=2, int gNumber=1, int parent=0, int born=0, int died=0, int span=0,int brood=0):
        organismDNA(dna), statusAlive(status), energyStore(stored), energyCapacity(capacity), energyWaste(waste), metabolicRate(metaRate),
        biteSize(bSize), generationNumber(gNumber), parentOrganism(parent), iterationBorn(born), iterationDied(died),
        lifeSpan(span), numberOffspring(brood)
    {

    }

    void Reproduce();               /**< Make copies of itself every time it has sufficient resources */
    int Excrete();                  /**< Organism expels unabsorbed energy back into the environment */
    void Metabolize();              /**< Organism burns stored energy to perform standard life functions */
    void Struggle();                /**< Check fitness, energy store, and determine if organism survives to the next round */
    int Bite(int);                  /**< Organism takes a bite of energy out of the environment */
    void Move();                    /**< Move from location if unable to find resources (energy or materials) */
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
    energyStore -= metabolicRate;
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
    int iRandom;                    /**< Integer for holding randomized values */
    srand(time(0));                 /**< Seed variable for random death events */
    int iterationCounter = 0;       /**< The current iteration */
    int maxIterations = 165;        /**< Limit number of iterations possible (to save resources) */
    int populationVsIteration[maxIterations]; /**< Track population at given iteration */
    int environmentEnergy = 500;    /**< Starting environment energy */
    int externalEnergy = 50;        /**< Energy is introduced to environment by external source at a fix rate */
    int populationLevel = 1;        /**< Start with a single bacterium */
    int runningPopulation = 1;      /**< Total population during a given iteration */
    int maxPopulation = 10000;      /**< Limit the total number of bacteria that can be created (for memory purposes) */
    ofstream populationHistory;     /**< Record population during each iteration */
    ofstream populationRecord;      /**< Record meta data for every organism created */
    populationHistory.open ("history.csv");
    populationRecord.open ("record.csv");
    Organism bacteria[maxPopulation];
    cout << "Welcome to the Cambrian world!" << endl;
    bacteria[0].setStatusAlive(true);           /**< First organism is born */
    bacteria[0].setDNA("ACGTCGAATCTAGGGA\n");   /**< Organism is assigned a fixed DNA code */
    cout<<environmentEnergy<<"\n";

    while(iterationCounter < maxIterations)
    {
        environmentEnergy += externalEnergy;
        for(organismCounter = 0; organismCounter < populationLevel; organismCounter++)
        {
            /*RANDOM DEATH PHASE*/
            /*If the organism is killed during the Random Death Phase, skip the Life Cycle Phase*/
            if(bacteria[organismCounter].getStatusAlive())
            {

                iRandom = rand() % 100;
                if(iRandom < 10)
                {
                    bacteria[organismCounter].setStatusAlive(false); //organism died due to random event
                    bacteria[organismCounter].setIterationDied(iterationCounter);
                    runningPopulation--;
                }
            }

            /*LIFE CYCLE PHASE*/
            /*If the organism in the population array is not alive, skip the Life Cycle Phase*/
            if(bacteria[organismCounter].getStatusAlive())
            {
                /*METABOLISM PHASE*/
                /*The organism will first metabolize energy to search for food and mates*/
                bacteria[organismCounter].Metabolize();

                /*If organisms energy store has reaches zero during the metabolism phase, it dies*/
                if(bacteria[organismCounter].getEnergyStore() == 0)
                {
                        bacteria[organismCounter].setStatusAlive(false); // organism starved to death
                        bacteria[organismCounter].setIterationDied(iterationCounter);
                        runningPopulation--;
                        environmentEnergy = environmentEnergy + 5; // organism's body becomes energy
                }

                /*CONSUMPTION PHASE*/
                /*If environment energy is zero - skip consumption phase (not possible to eat, yet)*/
                if (environmentEnergy > 0)
                {
                    /*Two separate sub-phases. (1) Consume energy form environment (2) Return unabsorbed energy to environment*/
                    environmentEnergy = environmentEnergy - bacteria[organismCounter].Bite(environmentEnergy);
                    environmentEnergy = environmentEnergy + bacteria[organismCounter].Excrete();
                }

                /*REPRODUCTION PHASE*/
                /*If population limit has been reached - skip reproduction phase (not possible to reproduce)*/
                if (populationLevel < maxPopulation)
                {
                    /*If organism has enough energy, the organism reproduces*/
                    if(bacteria[organismCounter].getEnergyStore() == bacteria[organismCounter].getEnergyCapacity())
                    {
                        runningPopulation++; // keep track of the total number of organisms created
                        bacteria[organismCounter].setEnergyStore(bacteria[organismCounter].getEnergyStore() - 3);
                        bacteria[organismCounter].incrementNumberOffspring();
                        bacteria[populationLevel].setStatusAlive(true);
                        bacteria[populationLevel].setIterationBorn(iterationCounter);
                        bacteria[populationLevel].setIterationDied(maxIterations);
                        bacteria[populationLevel].setDNA("ACGTCGAATCTAGGGA\n");
                        bacteria[populationLevel].setGenerationNumber(bacteria[organismCounter].getGenerationNumber()+ 1); // Relative distance from Original Ancestor
                        bacteria[populationLevel].setParentOrganism(organismCounter);
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
    populationRecord<<"Bacterium, Iteration Born, Iteration Died, Life Span, Generation, Parent Bacterium, Number of Offspring, Alive at End\n";
    for(i = 0; i < populationLevel; i++)
    {
        if(bacteria[i].getStatusAlive())
        {
            livingCount++;
        }
        populationRecord<<i<<","<<bacteria[i].getIterationBorn()<<","<<bacteria[i].getIterationDied()<<","<<bacteria[i].getLifeSpan()<<","<<bacteria[i].getGenerationNumber()<<","<<bacteria[i].getParentOrganism()<<","<<bacteria[i].getNumberOffspring()<<","<<bacteria[i].getStatusAlive()<<"\n";
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
