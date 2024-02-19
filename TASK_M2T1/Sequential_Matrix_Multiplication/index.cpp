#include <iostream>
#include <cstdlib>  // For rand() and srand()
#include <ctime>    // For time()
#include <chrono>   // For high_resolution_clock
#include <fstream>  // For file I/O

using namespace std::chrono;

const int MATRIX_SIZE = 200;

// Function to fill a matrix with random values
void populateMatrix(int matrix[][MATRIX_SIZE])
{
    for (int row = 0; row < MATRIX_SIZE; ++row)
    {
        for (int col = 0; col < MATRIX_SIZE; ++col)
        {
            // Generate random values between 0 and 99
            matrix[row][col] = rand() % 100;
        }
    }
}

// Function to multiply two matrices
void multiplyMatrices(const int firstMatrix[][MATRIX_SIZE], const int secondMatrix[][MATRIX_SIZE], int resultMatrix[][MATRIX_SIZE])
{
    for (int row = 0; row < MATRIX_SIZE; ++row)
    {
        for (int col = 0; col < MATRIX_SIZE; ++col)
        {
            resultMatrix[row][col] = 0;
            for (int k = 0; k < MATRIX_SIZE; ++k)
            {
                // Perform matrix multiplication
                resultMatrix[row][col] += firstMatrix[row][k] * secondMatrix[k][col];
            }
        }
    }
}

int main()
{
    srand(time(nullptr)); // Seed the random number generator with current time

    int firstMatrix[MATRIX_SIZE][MATRIX_SIZE];
    int secondMatrix[MATRIX_SIZE][MATRIX_SIZE];
    int resultMatrix[MATRIX_SIZE][MATRIX_SIZE];

    // Fill matrices with random values
    populateMatrix(firstMatrix);
    populateMatrix(secondMatrix);

    auto startTime = high_resolution_clock::now();

    // Perform matrix multiplication
    multiplyMatrices(firstMatrix, secondMatrix, resultMatrix);

    auto stopTime = high_resolution_clock::now();

    // Calculate duration
    auto duration = duration_cast<microseconds>(stopTime - startTime);

    // Output the duration of multiplication
    std::cout << "Multiplication completed in: " << duration.count() << " microseconds" << std::endl;

    // Write result to file
    std::ofstream outputFile("Sequential_Matrix_Multiplication_Result.txt");
    for (int row = 0; row < MATRIX_SIZE; ++row)
    {
        for (int col = 0; col < MATRIX_SIZE; ++col)
        {
            // Write each element of the result matrix to file
            outputFile << resultMatrix[row][col] << "\t";
        }
        outputFile << std::endl; // Newline after each row
    }
    // Write execution time to file
    outputFile << "Execution time: " << duration.count() << " microseconds";
    outputFile.close(); // Close the file

    return 0;
}
