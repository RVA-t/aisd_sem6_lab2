#include "dij.h"

int main()
{

	int start_point = 1, end_point, N = 0;
	Dij dij;
	cout << "Enter vertex: ";
	cin >> N;
	int** Graph = new int* [N];
	for (int i = 0; i < N; i++)
	{
		Graph[i] = new int[N];
	}


	cout << "Enter the lengths of the paths between the vertices." << endl;
	for (int i = 0; i < N; i++)
	{
		cout << "from " << i + 1;
		for (int j = 0; j < N; j++)
		{
			cout << " in " << j + 1 << ": ";
			cin >> Graph[i][j];
		}
	}
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
			cout << Graph[i][j] << " ";
		cout << endl;
	}
	cout << endl;
	auto st = chrono::high_resolution_clock::now();
	auto end = chrono::high_resolution_clock::now();
	chrono::duration<double, milli> duration = end - st;
	double time = 0;

	int* dist = new int[N];
	int M = 15000;
	for (int i = 0; i < M; i++)
	{
		st = chrono::high_resolution_clock::now();
		dij.dij(Graph, N, start_point - 1, 1);
		end = chrono::high_resolution_clock::now();
		duration = end - st;
		time += duration.count();
	}
	cout << "binary heap time: " << time / M << endl;
	dist = dij.dij(Graph, N, start_point - 1, 1);

	time = 0;

	for (int i = 0; i < M; i++)
	{
		st = chrono::high_resolution_clock::now();
		dij.dij(Graph, N, start_point - 1, 2);
		end = chrono::high_resolution_clock::now();
		duration = end - st;
		time += duration.count();
	}
	cout << "fib heap time: " << time / M << endl;
	dist = dij.dij(Graph, N, start_point - 1, 2);

	system("pause");
}
