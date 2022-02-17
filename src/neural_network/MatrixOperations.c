#include "MatrixOperations.h"

void Add_Matrix(double *A, double *B, int row, int col, double *res)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			res[i * col + j] = A[i * col + j] + B[i * col + j];
		}
	}
}

void Sub_Matrix(double *A, double *B, int row, int col, double *res)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			res[i * col + j] = A[i * col + j] - B[i * col + j];
		}
	}
}

void Mult_Matrix(double *A, double *B, int row1, int row2, int col1, int col2, double *res)
{
	// row1 x col1  row2 x col2
	for (int i = 0; i < row1; i++)
	{
		for (int j = 0; j < col1; j++)
		{
			double sum = 0;

			for (int k = 0; k < row2; k++)
			{
				sum += A[i * col1 + k] * B[k * col2 + j];
			}

			res[i * col2 + j] = sum;
		}
	}
}
