// main.cpp for CambrianExplosion

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include "Organism.h"
#include <vector>

int main()
{
    int organismCounter;
    int livingCount = 0;
    int i;
    int iterationPopulationSize = 1;
    int iRandom;                    /**< Integer for holding randomized values */
    srand(time(0));                 /**< Seed variable for random death events */
    int iterationCounter = 0;       /**< The current iteration */
    int maxIterations = 100;        /**< Limit number of iterations possible (to save resources) */
    int populationVsIteration[maxIterations]; /**< Track population at given iteration */
    int environmentEnergy = 500;    /**< Starting environment energy */
    int externalEnergy = 500;       /**< Energy is introduced to environment by external source at a fix rate */
    int organismID = 0;             /**< Start with a single bacterium */
    int maxPopulation = 1000;       /**< Limit the total number of bacteria that can be created (for memory purposes) */
    std::ofstream populationHistory;     /**< Record population during each iteration */
    std::ofstream populationRecord;      /**< Record meta data for every organism created */

    /*Keep a record of the population throughout each iteration for this case study*/
    populationHistory.open ("history.csv");
    populationHistory<<"Iteration, Population\n";

    /*Keep a record of each organism's meta data throughout the case study*/
    populationRecord.open ("record.csv");
    populationRecord<<"Bacterium, DNA, Iteration Born, Iteration Died, Life Span, Generation, Parent Bacterium, Number of Offspring, Alive at End\n"; // Header for data

//    Organism vectorOfBacteria[maxPopulation];
    std::vector<Organism> vectorOfBacteria(1); //start with a single bacteria
    Organism bacteria;
    std::cout << "Welcome to the Cambrian world!\n";
    vectorOfBacteria[0].setIdNumber(organismID);
    vectorOfBacteria[0].setStatusAlive(true);           /**< First organism is born */
    vectorOfBacteria[0].setDNA("ACGTCGAATCTAGGGA");   /**< Organism is assigned a fixed DNA code */
    std::cout<<environmentEnergy<<"\n";

    while(iterationCounter < maxIterations)
    {
        environmentEnergy += externalEnergy;

        iterationPopulationSize = vectorOfBacteria.size();

        /*ORGANISM ACTION PHASES*/
        for(organismCounter = 0; organismCounter < iterationPopulationSize; organismCounter++)
        {
            /*RANDOM DEATH PHASE*/
            /*If the organism is killed during the Random Death Phase, skip the Life Cycle Phase*/
            if(vectorOfBacteria[organismCounter].getStatusAlive())
            {

                iRandom = rand() % 100;
                if(iRandom < 10)
                {
                    vectorOfBacteria[organismCounter].setStatusAlive(false); //organism died due to random event
                    vectorOfBacteria[organismCounter].setIterationDied(iterationCounter);
                }
            }

            /*LIFE CYCLE PHASE*/
            /*If the organism in the population array is not alive, skip the Life Cycle Phase*/
            if(vectorOfBacteria[organismCounter].getStatusAlive())
            {
                /*METABOLISM PHASE*/
                /*The organism will first metabolize energy to search for food and mates*/
                vectorOfBacteria[organismCounter].Metabolize();

                /*If organisms energy store has reaches zero during the metabolism phase, it dies*/
                if(vectorOfBacteria[organismCounter].getEnergyStore() == 0)
                {
                    vectorOfBacteria[organismCounter].setStatusAlive(false); // organism starved to death
                    vectorOfBacteria[organismCounter].setIterationDied(iterationCounter);
                    environmentEnergy = environmentEnergy + 5; // organism's body becomes energy
                }

                /*CONSUMPTION PHASE*/
                /*If environment energy is zero - skip consumption phase (not possible to eat, yet)*/
                if (environmentEnergy > 0)
                {
                    /*Two separate sub-phases. (1) Consume energy form environment (2) Return unabsorbed energy to environment*/
                    environmentEnergy = environmentEnergy - vectorOfBacteria[organismCounter].Bite(environmentEnergy);
                    environmentEnergy = environmentEnergy + vectorOfBacteria[organismCounter].Excrete();
                }

                /*REPRODUCTION PHASE*/
                /*If population limit has been reached - skip reproduction phase (not possible to reproduce)*/
                if (int(vectorOfBacteria.size()) < maxPopulation)
                {
                    /*If organism has enough energy, the organism reproduces*/
                    if(vectorOfBacteria[organismCounter].getEnergyStore() == vectorOfBacteria[organismCounter].getEnergyCapacity())
                    {
                        organismID++;
                        vectorOfBacteria[organismCounter].setEnergyStore(vectorOfBacteria[organismCounter].getEnergyStore() - 3);
                        vectorOfBacteria[organismCounter].incrementNumberOffspring();
                        vectorOfBacteria.push_back(Organism()); // increase population of bacteria by one

                        // set parameters of new offspring
                        vectorOfBacteria[vectorOfBacteria.size() - 1].setIdNumber(organismID);
                        vectorOfBacteria[vectorOfBacteria.size() - 1].setDNA(vectorOfBacteria[organismCounter].getDNA());
                        vectorOfBacteria[vectorOfBacteria.size() - 1].setStatusAlive(true);
                        vectorOfBacteria[vectorOfBacteria.size() - 1].setIterationBorn(iterationCounter);
                        vectorOfBacteria[vectorOfBacteria.size() - 1].setIterationDied(maxIterations);
                        vectorOfBacteria[vectorOfBacteria.size() - 1].setGenerationNumber(vectorOfBacteria[organismCounter].getGenerationNumber()+ 1); // Relative distance from Original Ancestor
                        vectorOfBacteria[vectorOfBacteria.size() - 1].setParentOrganism(vectorOfBacteria[organismCounter].getIdNumber());
                    }
                }
            }
            else
            {
               // vectorOfBacteria.erase(vectorOfBacteria.begin() + organismCounter);
                //organismCounter--;
            }

            if(vectorOfBacteria[organismCounter].getStatusAlive() == 0)
            {
                if(vectorOfBacteria.size() > 1)
                {
                    populationRecord<<vectorOfBacteria[organismCounter].getIdNumber()<<","<<vectorOfBacteria[organismCounter].getDNA()<<","<<vectorOfBacteria[organismCounter].getIterationBorn()<<","<<vectorOfBacteria[organismCounter].getIterationDied()<<","<<vectorOfBacteria[organismCounter].getLifeSpan()<<","<<vectorOfBacteria[organismCounter].getGenerationNumber()<<","<<vectorOfBacteria[organismCounter].getParentOrganism()<<","<<vectorOfBacteria[organismCounter].getNumberOffspring()<<","<<vectorOfBacteria[organismCounter].getStatusAlive()<<"\n";
                    vectorOfBacteria.erase(vectorOfBacteria.begin() + organismCounter);
                    organismCounter--;
                    iterationPopulationSize--;
                }
            }

        }

        /*Track the population at each iteration to show population growth and decline over time(iteration)*/
        populationVsIteration[iterationCounter] = int(vectorOfBacteria.size());
        iterationCounter++;
    }


    for(i = 0; i < int(vectorOfBacteria.size()); i++)
    {
        if(vectorOfBacteria[i].getStatusAlive())
        {
            livingCount++;
        }
        populationRecord<<vectorOfBacteria[i].getIdNumber()<<","<<vectorOfBacteria[i].getDNA()<<","<<vectorOfBacteria[i].getIterationBorn()<<","<<vectorOfBacteria[i].getIterationDied()<<","<<vectorOfBacteria[i].getLifeSpan()<<","<<vectorOfBacteria[i].getGenerationNumber()<<","<<vectorOfBacteria[i].getParentOrganism()<<","<<vectorOfBacteria[i].getNumberOffspring()<<","<<vectorOfBacteria[i].getStatusAlive()<<"\n";
    }
    std::cout<<"Living: "<<livingCount;

    std::cout<<"maxIterations "<<maxIterations<<" , populationVsIteration Array "<<sizeof(populationVsIteration)/sizeof(populationVsIteration[0])<<"\n";
    // Write to History File
    for(i = 0; i < (maxIterations - 1); i++)
    {
        populationHistory<<i<<","<<populationVsIteration[i]<<"\n";
    }

    return 0;
}
