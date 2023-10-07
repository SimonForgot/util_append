#include <iostream>

const int SIZE = 500;

void matrixMultiplication(int **matrixA, int **matrixB, int **result)
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            for (int k = 0; k < SIZE; k++)
            {
                result[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }
}

int main()
{
    int **matrixA = new int *[SIZE];
    int **matrixB = new int *[SIZE];
    int **result = new int *[SIZE];

    for (int i = 0; i < SIZE; i++)
    {
        matrixA[i] = new int[SIZE];
        matrixB[i] = new int[SIZE];
        result[i] = new int[SIZE];
    }

    // 初始化矩阵
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            matrixA[i][j] = i + j;
            matrixB[i][j] = i - j;
            result[i][j] = 0;
        }
    }

    matrixMultiplication(matrixA, matrixB, result);

    // 打印结果
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            // std::cout << result[i][j] << " ";
        }
        // std::cout << std::endl;
    }

    // 释放内存
    for (int i = 0; i < SIZE; i++)
    {
        delete[] matrixA[i];
        delete[] matrixB[i];
        delete[] result[i];
    }
    delete[] matrixA;
    delete[] matrixB;
    delete[] result;

    return 0;
}
