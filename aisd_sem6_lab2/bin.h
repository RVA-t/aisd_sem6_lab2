#include "includes.h" 

class BinaryHeap
{
private:
	vector<pair<int, int>> heap;

	int LEFT(int i)
	{
		return (2 * i + 1);
	}

	int RIGHT(int i)
	{
		return (2 * i + 2);
	}

	int PARENT(int i)
	{
		return (i - 1) / 2;
	}

	void heapify_down(int i)
	{
		int left = LEFT(i);
		int right = RIGHT(i);

		int smallest = i;

		if (left < heap.size() && heap[left].first < heap[i].first)
		{
			smallest = left;
		}

		if (right < heap.size() && heap[right].first < heap[smallest].first)
		{
			smallest = right;
		}

		if (smallest != i)
		{
			swap(heap[i], heap[smallest]);
			heapify_down(smallest);
		}
	}

	void heapify_up(int i)
	{

		if (i && heap[PARENT(i)].first > heap[i].first)
		{
			swap(heap[i], heap[PARENT(i)]);

			heapify_up(PARENT(i));
		}
	}

public:
	bool empty()
	{
		return heap.empty();
	}

	void push(int key, int ind)
	{

		heap.push_back({ key, ind });

		int index = heap.size() - 1;
		heapify_up(index);
	}

	void pop()
	{
		if (heap.size())
		{
			heap[0] = heap.back();
			heap.pop_back();
			heapify_down(0);
		}
		else
		{
			cout << "Куча пуста" << endl;
		}
	}

	pair<int, int> top()
	{
		if (heap.size())
		{
			return heap[0];
		}
		else
		{
			cout << "Куча пуста" << endl;
		}
	}
};
