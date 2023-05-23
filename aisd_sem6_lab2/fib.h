#include "bin.h" 

template <class V> class FibonacciHeap;

template <class V> struct node {
private:
	node<V>* prev;
	node<V>* next;
	node<V>* child;
	node<V>* parent;
	V value, dij_node;
	int degree;
	bool marked;
public:
	friend class FibonacciHeap<V>;
	node<V>* getPrev() { return prev; }
	node<V>* getNext() { return next; }
	node<V>* getChild() { return child; }
	node<V>* getParent() { return parent; }
	V getValue() { return value; }
	bool isMarked() { return marked; }

	bool hasChildren() { return child; }
	bool hasParent() { return parent; }
};

template <class V> class FibonacciHeap {
protected:
	node<V>* heap;
public:

	FibonacciHeap() {
		heap = _empty();
	}

	node<V>* insert(V value, V dij_node) {
		node<V>* ret = _singleton(value, dij_node);
		heap = _merge(heap, ret);
		return ret;
	}

	bool isEmpty() {
		return heap == NULL;
	}

	V getMinimum() {
		return heap->value;
	}
	V getMinimum_dij_node()
	{
		return heap->dij_node;
	}

	V removeMinimum() {
		node<V>* old = heap;
		heap = _removeMinimum(heap);
		V ret = old->value;
		delete old;
		return ret;
	}

	node<V>* find(V value) {
		return _find(heap, value);
	}

private:
	node<V>* _empty() {
		return NULL;
	}

	node<V>* _singleton(V value, V dij_node) {
		node<V>* n = new node<V>;
		n->value = value;
		n->prev = n->next = n;
		n->degree = 0;
		n->marked = false;
		n->child = NULL;
		n->parent = NULL;
		n->dij_node = dij_node;
		return n;
	}

	node<V>* _merge(node<V>* a, node<V>* b) {
		if (a == NULL)return b;
		if (b == NULL)return a;
		if (a->value > b->value) {
			node<V>* temp = a;
			a = b;
			b = temp;
		}
		node<V>* an = a->next;
		node<V>* bp = b->prev;
		a->next = b;
		b->prev = a;
		an->prev = bp;
		bp->next = an;
		return a;
	}


	void _addChild(node<V>* parent, node<V>* child) {
		child->prev = child->next = child;
		child->parent = parent;
		parent->degree++;
		parent->child = _merge(parent->child, child);
	}

	void _unMarkAndUnParentAll(node<V>* n) {
		if (n == NULL)return;
		node<V>* c = n;
		do {
			c->marked = false;
			c->parent = NULL;
			c = c->next;
		} while (c != n);
	}

	node<V>* _removeMinimum(node<V>* n) {
		_unMarkAndUnParentAll(n->child);
		if (n->next == n) {
			n = n->child;
		}
		else {
			n->next->prev = n->prev;
			n->prev->next = n->next;
			n = _merge(n->next, n->child);
		}
		if (n == NULL)return n;
		node<V>* trees[64] = { NULL };

		while (true) {
			if (trees[n->degree] != NULL) {
				node<V>* t = trees[n->degree];
				if (t == n)break;
				trees[n->degree] = NULL;
				if (n->value < t->value) {
					t->prev->next = t->next;
					t->next->prev = t->prev;
					_addChild(n, t);
				}
				else {
					t->prev->next = t->next;
					t->next->prev = t->prev;
					if (n->next == n) {
						t->next = t->prev = t;
						_addChild(t, n);
						n = t;
					}
					else {
						n->prev->next = t;
						n->next->prev = t;
						t->next = n->next;
						t->prev = n->prev;
						_addChild(t, n);
						n = t;
					}
				}
				continue;
			}
			else {
				trees[n->degree] = n;
			}
			n = n->next;
		}
		node<V>* min = n;
		node<V>* start = n;
		do {
			if (n->value < min->value)min = n;
			n = n->next;
		} while (n != start);
		return min;
	}

	node<V>* _find(node<V>* heap, V value) {
		node<V>* n = heap;
		if (n == NULL)return NULL;
		do {
			if (n->value == value)return n;
			node<V>* ret = _find(n->child, value);
			if (ret)return ret;
			n = n->next;
		} while (n != heap);
		return NULL;
	}
};