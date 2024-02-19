#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <fstream>
#include <pthread.h>

using namespace std::chrono;

const int MATRIX_SIZE = 200;
#define MAX_THREADS 16

int firstMatrix[MATRIX_SIZE][MATRIX_SIZE];
int secondMatrix[MATRIX_SIZE][MATRIX_SIZE];
int resultMatrix[MATRIX_SIZE][MATRIX_SIZE];
int threadNumber = 0;
int partitionSize = MATRIX_SIZE / MAX_THREADS;

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

void *matrixMultiplication(void *args)
{
    int threadID = threadNumber++;
    for (int i = threadID * partitionSize; i < (threadID + 1) * partitionSize; ++i)
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
    return NULL;
}

int main()
{
    srand(time(nullptr));
    populateRandomMatrix(firstMatrix);
    populateRandomMatrix(secondMatrix);
    auto start = high_resolution_clock::now();
    pthread_t matrixThreads[MAX_THREADS];
    for (int i = 0; i < MAX_THREADS; ++i)
    {
        pthread_create(&matrixThreads[i], NULL, &matrixMultiplication, NULL);
    }
    for (int i = 0; i < MAX_THREADS; ++i)
    {
        pthread_join(matrixThreads[i], NULL);
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    printf("Execution time: %d microseconds", duration.count());
    std::ofstream outputFile("PThread_Results.txt");
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
