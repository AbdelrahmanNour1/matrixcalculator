#include <iostream>
#include <cmath>
using namespace std;

int calcdet(int m[10][10], int order) {
	int det = 0;
	int matrix[10][10];
	int sign = 1;
	if (order == 1) {
		det = m[0][0];
	}
	else
	if (order == 2)
		return ((m[0][0] * m[1][1]) - (m[1][0] * m[0][1]));
	else {
		for (int i = 0; i < order; i++) {
			int row = 0;
			for (int j = 1; j < order; j++) {
				int col = 0;
				for (int k = 0; k < order; k++) {
					if (k == i)
						continue;
					matrix[row][col] = m[j][k];
					col++;
				}
				row++;

			}
			det = det + (sign * m[0][i] * calcdet(matrix, order - 1));
			sign = sign * -1;
		}
	}
	return det;
}
void cofactor(int m[10][10], int cof[10][10], int row, int col, int order)
{
	int r = 0, c= 0;
	for (int i = 0; i < order; i++)
	{
		for (int j = 0; j < order; j++)
		{
			if (i != row && j != col)
			{
				cof[r][c++] = m[i][j];

				if (c == order - 1)
				{
					c = 0;
					r++;
				}
			}
		}
	}
}
void adjoint(int m[10][10], int adj[10][10],int order)
{
	if (order == 1)
	{
		adj[0][0] = 1;
		return;
	}

	int sign = 1, cofmat[10][10];

	for (int i = 0; i < order; i++)
	{
		for (int j = 0; j < order; j++)
		{
			cofactor(m, cofmat, i, j, order);
			if ((i + j) % 2 == 0)
				sign = 1;
			else sign = -1;
			adj[i][j] = sign * (calcdet(cofmat, order - 1));
		}
	}
}
int main()
{
	int transpose[10][10];
	float invmat[10][10];
	int matrixA[10][10];
	int matrixB[10][10];
	float matrixequal[10][10];
	cout << "Please enter dimensions of Matrix A:\n";
	int a, b, c, d;
	cin >> a >> b;
	cout << "Please enter dimensions of Matrix B:\n";
	cin >> c >> d;
	cout << "Please enter values of Matrix A:\n";
	for (int i = 0; i < a; i++)
	{
		for (int j = 0; j < b; j++)
		{
			cin >> matrixA[i][j];
		}
	}
	cout << "Please enter values of Matrix B:\n";
	for (int i = 0; i < c; i++)
	{
		for (int j = 0; j < d; j++)
		{
			cin >> matrixB[i][j];
		}
	}
	bool exitfunc = true;
	while (exitfunc == true) {
		cout << "Please choose operation type(1: A+B, 2: A-B, 3: AxB, 4: A*inverse(B), 5: |A|, 6: |B|, 7: quit):\n";
		int op;
		cin >> op;
		switch (op) {
		case 1: {
			if (a == c && b == d)
			{
				for (int i = 0; i < a; i++)
				{
					for (int j = 0; j < b; j++) {
						matrixequal[i][j] = matrixA[i][j] + matrixB[i][j];
					}
				}
				for (int i = 0; i < a; ++i)
					for (int j = 0; j < b; ++j)
					{
						cout << matrixequal[i][j] << "  ";
						if (j == b - 1)
							cout << endl;
					}
			}
			else
				cout << "The operation you chose is invalid for the given matrices.\n";

		}
			  break;
		case 2: {
			if (a == c && b == d)
			{
				for (int i = 0; i < a; i++)
				{
					for (int j = 0; j < b; j++) {
						matrixequal[i][j] = matrixA[i][j] - matrixB[i][j];
					}
				}
				for (int i = 0; i < a; ++i)
					for (int j = 0; j < b; ++j)
					{
						cout << matrixequal[i][j] << "  ";
						if (j == b - 1)
							cout << endl;
					}
			}
			else
				cout << "The operation you chose is invalid for the given matrices.\n";

		}
			  break;
		case 3: {
			if (c == b)
			{
				for (int i = 0; i < a; ++i)
					for (int j = 0; j < d; ++j)
					{
						matrixequal[i][j] = 0;
					}
				for (int i = 0; i < a; i++)
					for (int j = 0; j < d; j++)
						for (int k = 0; k < b; k++)
						{
							matrixequal[i][j] += matrixA[i][k] * matrixB[k][j];
						}
				for (int i = 0; i < a; i++)
					for (int j = 0; j < d; j++)
					{
						cout << matrixequal[i][j] << "  ";
						if (j == d - 1)
							cout << endl;
					}
			}
			else
				cout << "The operation you chose is invalid for the given matrices.\n";
		}
			  break;
		case 4: {
			if (c == d && calcdet(matrixB, c) != 0 && b == c)
			{
				int adj[10][10];
				if (c == 1) {
					invmat[0][0] = 1 / float(calcdet(matrixB, 1));
				
					for (int i = 0; i < a; i++) {
						for (int j = 0; j < d; j++)
						{
							matrixequal[i][j] = 0;
						}
					}
					for (int i = 0; i < a; i++)
						for (int j = 0; j < c; j++)
							for (int k = 0; k < b; k++)
							{
								matrixequal[i][j] += matrixA[i][k] * invmat[k][j];
							}
				}
				else if (c == 2) {

					invmat[0][0] = matrixB[1][1] / float(calcdet(matrixB, c));
					invmat[1][0] = -matrixB[1][0] / float(calcdet(matrixB, c));
					invmat[0][1] = -matrixB[0][1] / float(calcdet(matrixB, c));
					invmat[1][1] = matrixB[0][0] / float(calcdet(matrixB, c));
					for (int i = 0; i < a; i++) {
						for (int j = 0; j < d; j++)
						{
							matrixequal[i][j] = 0;
						}
					}
					for (int i = 0; i < a; i++)
						for (int j = 0; j < c; j++)
							for (int k = 0; k < b; k++)
							{
								matrixequal[i][j] += matrixA[i][k] * invmat[k][j];
							}

				}
				else {
					adjoint(matrixB, adj, c);
				for (int i = 0; i < c; ++i)
					for (int j = 0; j < d; ++j) {
						transpose[j][i] = adj[i][j];
					}
				for (int i = 0; i < c; i++) {
					for (int j = 0; j < c; j++) {
						invmat[i][j] = transpose[i][j] / float(calcdet(matrixB, c));
					}

				}
				for (int i = 0; i < a; ++i)
					for (int j = 0; j < d; ++j) 
					{
						matrixequal[i][j] = 0;
					}
				for (int i = 0; i < a; i++)
					for (int j = 0; j < d; j++)
						for (int k = 0; k < b; k++)
						{
							matrixequal[i][j] += matrixA[i][k] * invmat[k][j];
						}
				
			}
				for (int i = 0; i < a; i++)
				{
					for (int j = 0; j < c; j++)
						if (matrixequal[i][j]<0 && matrixequal[i][j] > -0.5)
							cout << 0 << " ";
						else
						cout << round(matrixequal[i][j]) << " ";
					cout << endl;
				}
				
			}


			else
				cout << "The operation you chose is invalid for the given matrices.\n";
		}
			  break;
		case 5: {
			if (a == b)
			{
				cout << calcdet(matrixA, a) << endl;

			}
			else
				cout << "The operation you chose is invalid for the given matrices.\n";

		}
			  break;
		case 6: {
			if (c == d)
			{
				cout << calcdet(matrixB, c) << endl;

			}
			else
				cout << "The operation you chose is invalid for the given matrices.\n";
		}
			  break;
		case 7: {
			cout << "Thank you!";
			exitfunc = false;

		}
		default:
			break;

		}
	}
	return 0;
}