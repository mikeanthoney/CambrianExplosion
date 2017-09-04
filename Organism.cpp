#include "Organism.h"

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