#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <fstream>
#include <omp.h>

using namespace std::chrono;

const int MATRIX_SIZE = 200;
int firstMatrix[MATRIX_SIZE][MATRIX_SIZE];
int secondMatrix[MATRIX_SIZE][MATRIX_SIZE];
int resultMatrix[MATRIX_SIZE][MATRIX_SIZE];

void populateRandomMatrix(int matrix[][MATRIX_SIZE])
{
    for (int i = 0; i < MATRIX_SIZE; ++i)
    {
        for (int j = 0; j < MATRIX_SIZE; ++j)
        {
            matrix[i][j] = rand() % 100;
        }
    }
}

int main()
{
    srand(time(0));
    populateRandomMatrix(firstMatrix);
    populateRandomMatrix(secondMatrix);
    auto startTime = high_resolution_clock::now();

#pragma omp parallel for
    for (int i = 0; i < MATRIX_SIZE; ++i)
    {
        for (int j = 0; j < MATRIX_SIZE; ++j)
        {
            resultMatrix[i][j] = 0;
            for (int k = 0; k < MATRIX_SIZE; ++k)
            {
                resultMatrix[i][j] += firstMatrix[i][k] * secondMatrix[k][j];
            }
        }
    }

    auto stopTime = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stopTime - startTime);
    printf("Execution time: %d microseconds\n", duration.count());
    
    std::ofstream outputFile("OpenMP_Parallel_Multiplication_Results.txt");
    for (int i = 0; i < MATRIX_SIZE; ++i)
    {
        for (int j = 0; j < MATRIX_SIZE; ++j)
        {
            outputFile << resultMatrix[i][j] << "\t";
        }
        outputFile << std::endl;
    }
    outputFile << "Execution time: " << duration.count() << " microseconds";
    outputFile.close();

    return 0;
}
