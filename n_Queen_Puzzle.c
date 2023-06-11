/* CEP.c:  Solving The n_Queens Problem Using Genetic Algorithm
-----------------------------------------------------------------------
This program finds solves the n-Queen Puzzle using Genetic Algorithm.
-----------------------------------------------------------------------
Written by Muhammad Rafay (m.rafaymct@gmail.com) on 2-Dec-2022.
IDE: Visual Studio Code 1.69.2
C Compiler: GCC (rev0, Built by MinGW-W64 project) 8.1.0 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Defining the macros for constants
#define n_Q 8
#define n_Pop 500
#define Iter_used 1500

// Functions to simplify the program.
void Check_Fitness(int random_population[n_Pop][n_Q], int FitVal[n_Pop]);
void RandomPopulation();
void Parent(int random_population[n_Pop][n_Q], int FitVal[n_Pop]);
void PopulationDisplay(int random_population[n_Pop][n_Q], int FitVal[n_Pop]);
void CrossOver(int random_population[n_Pop][n_Q]);
void Mutation(int random_population[n_Pop][n_Q]);
int Solution(int Fitness[n_Pop]);
void Board_Show(int random_population[n_Pop][n_Q], int SolIndex);

// Global Variables that will be used throughout.
int FitVal[n_Pop];
int random_population[n_Pop][n_Q];
int SolIndex = 0;

// Main Function that will call all programs.
int main()
{
    int check = 0, iteration = 0;
    RandomPopulation();
    Check_Fitness(random_population, FitVal);
    while (iteration < Iter_used && check == 0)   // Checking the loop to the maximum iterations to get generations.
    {
        Parent(random_population, FitVal);
        iteration++;
        CrossOver(random_population);
        Mutation(random_population);
        Check_Fitness(random_population, FitVal);
        check = Solution(FitVal);
    }

    if (check == 1)
    {
        printf("Number of generations = %d.\n", iteration);
        PopulationDisplay(random_population, FitVal);
        Board_Show(random_population, SolIndex);
    }
    else
    {
        printf("No solution is found.");
    }
    
    return 0;
}
// Generating Random Population
void RandomPopulation()
{
    srand(time(0));
    for (int i = 0; i < n_Pop; i++)
    {
        for (int j = 0; j < n_Q; j++)
        {
            random_population[i][j] = (rand() % n_Q) + 1;  // Generating random numbers from  1 to the Queens
        }
    }
}
// Checking the fitness of every random generation
void Check_Fitness(int random_population[n_Pop][n_Q], int FitVal[n_Pop])
{
    // Fitness For Row Operation.
    int attack = 0;
    for (int i = 0; i < n_Pop; i++)
    {
        for (int j = 0; j < n_Q; j++)
        {
            for (int k = j + 1; k < n_Q; k++)
            {
                if (random_population[i][j] == random_population[i][k])
                    attack++;
            }
        }

    // Fitness for diagonal operation.
    for (int j = 0; j < n_Pop; j++)
    {
        for (int k = j + 1; k < n_Q; k++)
        {
            if (abs(random_population[i][j] - random_population[i][k]) == abs(j-k))
                attack++;
        }
    }
        FitVal[i] = attack;  // Storing the attack as Fitness value
        attack = 0;
    }
}
// Sorting in an order the fitness and random Population
void Parent(int random_population[n_Pop][n_Q], int FitVal[n_Pop])
{
    int temp = 0;
    int Array_temp[n_Q];

    // Bubble Sorting of the Population Array
    for(int i = 0; i < n_Pop; i++)
    {
        for(int j = i+1; j < n_Pop; j++)
        {
            if(FitVal[j] < FitVal[i])
            {
                for(int k = 0; k < n_Q; k++)
                {
                    Array_temp[k] = random_population[i][k];
                }
                for(int k = 0; k < n_Q; k++)
                {
                    random_population[i][k] = random_population[j][k];
                }
                for(int k = 0; k < n_Q; k++)
                {
                    random_population[j][k] = Array_temp[k];
                }

            // Bubble sorting Fitness value
            // Lowest attack would be at higher position and arranged in assending order
                temp = FitVal[i];
                FitVal[i] = FitVal[j];
                FitVal[j] = temp;
            }
        }
    }
}
// Displaying Random Population
void PopulationDisplay(int random_population[n_Pop][n_Q], int FitVal[n_Pop])
{
        printf("[ ");
        for (int j = 0; j < n_Q; j++)
        {
            printf("%d  ", random_population[SolIndex][j]);
            if (j == n_Q - 1)
            {
                printf("\b]");
                printf("\t%d", FitVal[SolIndex]);
            }
        }
        printf("\n");
}
//  Crossing over the random population to reduce the fitness value
void CrossOver(int random_population[n_Pop][n_Q])
{
    srand(time(NULL));

    int CrossPoint = rand()%n_Q+1;
    // (n_Q % 2 == 0) ? (n_Q / 2) : ((n_Q - 1) / 2);
    int temparray[n_Q - CrossPoint];

    int k = 0;

    for (int i = 0; i < CrossPoint; i++)
    {
        for (int j = 0; j < n_Q; j++)
        {
            random_population[k + (n_Pop / 2)][j] = random_population[i][j];
        }
        k++;
    }
    k = 0;
    for (int i = (n_Pop / 2); i < n_Pop; i = i + 2)
    {
        for (int j = 0; j < (n_Q - CrossPoint); j++)
        {
            temparray[j] = random_population[i + 1][j + CrossPoint];
        }
        for (int j = 0; j < (n_Q - CrossPoint); j++)
        {

            random_population[i + 1][j + CrossPoint] = random_population[i][j + CrossPoint];
        }
        for (int j = 0; j < (n_Q - CrossPoint); j++)
        {

            random_population[i][j + CrossPoint] = temparray[j];
        }
    }
}
// Using mutation to randomise any of the Queen element
void Mutation(int random_population[n_Pop][n_Q])
{
    srand(time(0));

    for (int i = 0; i < n_Pop; i = i + 2)    // Mutating the Population by leaving one row and then other.
    {
        int index = rand() % n_Q;
        int val = rand() % n_Q + 1;
        random_population[i][index] = val;
    }
}
// Checking for the solution.
int Solution(int FitVal[n_Pop])
{

    for (int i = 0; i < n_Pop; i++)
    {
        if (FitVal[i] == 0)
        {
            SolIndex = i;
            return 1;
        }
    }
    return 0;
}
// Displaying the final Solved Table in a Board.
void Board_Show(int random_population[n_Pop][n_Q], int SolIndex)
{
    char board[n_Q][n_Q];
    for (int i = 0; i < n_Q; i++)
    {
        for (int j = 0; j < n_Q; j++)
        {
            if (random_population[SolIndex][j] == i + 1)
            {
                board[i][j] = 'Q';
            }
            else
            {
                board[i][j] = 'X';
            }
        }
    }
    for (int i = 0; i < n_Q; i++)
    {
        printf("  ");
        for (int j = 0; j < n_Q; j++)
        {
            printf("%c  ", board[i][j]);
        }
        printf("\n");
    }
}

// End of Program.