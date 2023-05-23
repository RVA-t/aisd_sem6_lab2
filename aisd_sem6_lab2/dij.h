#include "fib.h"

class Dij {
public:
	int* dij(int** graph, int N, int start, int choice)
	{
		if (choice == 1) {
			int* dist = new int[N];
			BinaryHeap q;
			for (int i = 0; i < N; i++)
			{
				dist[i] = INT_MAX;
			}
			dist[start] = 0;
			q.push(dist[start], start);
			while (!q.empty())
			{
				pair<int, int> u = q.top();
				q.pop();
				for (int i = 0; i < N; i++)
				{
					int temp = graph[u.second][i];
					if (graph[u.second][i] && dist[u.second] + graph[u.second][i] < dist[i])
					{
						{
							dist[i] = dist[u.second] + graph[u.second][i];
							q.push(dist[i], i);
						}
					}
				}
			}
			return dist;
		}
		else if (choice == 2) {
			int* dist = new int[N];
			FibonacciHeap<int> q;
			for (int i = 0; i < N; i++)
			{
				dist[i] = INT_MAX;
			}
			dist[start] = 0;
			q.insert(dist[start], start);
			while (!q.isEmpty())
			{
				int u_dist = q.getMinimum();
				int u = q.getMinimum_dij_node();
				q.removeMinimum();
				for (int i = 0; i < N; i++)
				{
					if (graph[u][i] && dist[u] + graph[u][i] < dist[i])
					{
						{
							dist[i] = dist[u] + graph[u][i];
							q.insert(dist[i], i);
						}
					}
				}
			}
			return dist;
		}
	}
};