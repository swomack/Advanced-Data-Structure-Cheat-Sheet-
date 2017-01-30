#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;



struct element
{
	int value;
	int rank;
	int total_element;
	element* parent;

	element(int val) : value(val), parent(this), rank(0), total_element(1)
	{
	}
};


element* make_set(int value)
{
	element* elem = new element(value);
	return elem;
}


element* find_set(element* x)
{
	if (x->parent != x)
		x->parent = find_set(x->parent);

	return x->parent;
}

int link_set(element* x, element* y)
{
	if (x == y)
		return x->total_element;
	if (x->rank > y->rank)
	{
		y->parent = x;
		x->total_element += y->total_element;
		return x->total_element;
	}
	else
	{
		x->parent = y;
		y->total_element += x->total_element;

		if (x->rank == y->rank)
			y->rank++;

		return y->total_element;
	}
}

int union_set(element* x, element* y)
{
	return link_set(find_set(x), find_set(y));
}

int main()
{
	
	return 0;
}