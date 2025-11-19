int main() {
	int n = 4;

	int W[MAX][MAX] =
	{ 0, 3, INF, 7 },
	{ 8,0,2,INF },
	{ 5, INF, 0,1 }
	{ 2, INF, INF, 0 }
};


	int D[MAX][MAX];
	floyd(n, W, D);

	int i, j;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if (D[i][j] >= INF)
				printf("INF ");
			else
				printf("%3d ", D[i][j]);
		}
		printf("\n");
	}
	return 0;
}