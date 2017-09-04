#ifndef ORGANISM_H_INCLUDED
#define ORGANISM_H_INCLUDED
#include <string>
#include <cstdlib>
#include <ctime>

/**<Organism is a class that tracks internal parameters for energy as well as meta data created throughout it's life cycle*/
class Organism
{
private:
    std::string organismDNA;/**< Unique code for organism that is shared with offspring (but may mutate) */
    int DNAlength;
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
    bool statusMutation;

public:
    Organism(std::string dna="XXXXXXXXXXXXXXXX",int length=16, bool status=false, int stored=4, int capacity=8, int waste=0, int metaRate=1,
             int bSize=2, int gNumber=1, int parent=0, int born=0, int died=0, int span=0,int brood=0, bool mutation=false):
        organismDNA(dna), DNAlength(length), statusAlive(status), energyStore(stored), energyCapacity(capacity), energyWaste(waste), metabolicRate(metaRate),
        biteSize(bSize), generationNumber(gNumber), parentOrganism(parent), iterationBorn(born), iterationDied(died),
        lifeSpan(span), numberOffspring(brood), statusMutation(mutation)
    {

    }

    void Reproduce();               /**< Make copies of itself every time it has sufficient resources */
    int Excrete();                  /**< Organism expels unabsorbed energy back into the environment */
    void Metabolize();              /**< Organism burns stored energy to perform standard life functions */
    void Struggle();                /**< Check fitness, energy store, and determine if organism survives to the next round */
    int Bite(int);                  /**< Organism takes a bite of energy out of the environment */
    void Move();                    /**< Move from location if unable to find resources (energy or materials) */
    void setDNA(std::string);
    std::string getDNA();
    void setEnergyStore(int);
    int getEnergyStore();
    void setEnergyCapacity(int);
    int getEnergyCapacity();
    void setBiteSize(int);
    void setGenerationNumber(int);
    int getGenerationNumber();
    void setStatusAlive(bool);
    bool getStatusAlive();
    bool getStatusMutation();
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


#endif // ORGANISM_H_INCLUDED
