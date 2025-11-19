#include <stdio.h>
#include <limits.h>
#include <iostream>

#define INF 100000000
#define MAX 100

void floyd(int n, int W[MAX][MAX], int D[MAX][MAX]) {
	int i, j, k;
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			D[i][j] = W[i][j];

	for (k = 0; k < n; k++)
		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				if (D[i][k] + D[k][j] < D[i][j])
					D[i][j] = D[i][k] + D[k][j];
}