// main.cpp for CambrianExplosion

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include "Organism.h"

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
    std::ofstream populationHistory;     /**< Record population during each iteration */
    std::ofstream populationRecord;      /**< Record meta data for every organism created */
    populationHistory.open ("history.csv");
    populationRecord.open ("record.csv");
    Organism bacteria[maxPopulation];
    std::cout << "Welcome to the Cambrian world!\n";
    bacteria[0].setStatusAlive(true);           /**< First organism is born */
    bacteria[0].setDNA("ACGTCGAATCTAGGGA\n");   /**< Organism is assigned a fixed DNA code */
    std::cout<<environmentEnergy<<"\n";

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
