/* 
Code By: Sourov

Segment tree implementation with comments.

Here the solution of the "Sum of given range" problem has been implemented using segment tree.

Segment tree is a full binary tree, if there are not enough element in the array to make it a full binary tree,
we will add additional element with value 0 (for other problems it could be other value)

*/


#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>


using namespace std;



class segment_tree
{
private:

	// this will contain all the nodes, root at position 1 (0 for vector position),
	// we will represent the position as node_id
	// for a node with ndoe_id = i, its child's node_id will be 2*node_id and 2*node_id + 1
	// teh leaf will be the array elements, complete binary tree so total leaf will be always power of two
	vector<int> nodes;

	int total_leaf;

public:

	segment_tree()
	{
		nodes.clear();
		total_leaf = 0;
	}

	void build_tree(vector<int>& num)
	{
		int level = ceil(log2(num.size()));
		total_leaf = pow(2, level); // make it a complete binary tree

		int total_node = total_leaf + total_leaf - 1;

		nodes.resize(total_node); // total_node = internal_node + leaf
		fill(begin(nodes), end(nodes), 0); 

		// fill the nodes in a bottom up approach 
		// last elements will contain the values from array num
		// node_id of root is 1 (vector pos 0)
		construct_tree(num, 1, 0, total_leaf - 1);
	}

	// x, y contains the query range
	// every node of our segment tree has a range
	// root node contains the data for the whole array (range 0 - n)
	int query_sum(int x, int y)
	{
		
		return get_sum(1, 0, total_leaf - 1, x - 1, y - 1); // start search from the root, convert the search range to vector index 
	}

	// update the value of the array at pos to value
	// we need to update the parents's value since the child value has been changed
	// so we have to update the parent's value as the sum of left segment and right segment will be changed for all parent
	void update(int pos, int value)
	{
		int internal_node = nodes.size() - total_leaf;

		int node_id = internal_node + pos;

		nodes[node_id - 1] = value;

		// need to update it's parent since the value of this node has been changed
		update_parent(node_id);
	}


private:

	void update_parent(int node_id)
	{
		// we dont need to update the parent of the root
		if (node_id <= 1)
			return;

		// we can get the parent node by dividing the node id by 2
		int parent_node = node_id / 2;

		// update the value of parent node, the value = left child value + right child value
		nodes[parent_node - 1] = nodes[parent_node * 2 - 1] + nodes[parent_node * 2];

		// we need to update its parent, since the value of this node has been changed
		update_parent(parent_node);
	}

	// left, right contains the range of this node
	int get_sum(int node_id, int left, int right, int x, int y)
	{
		if (left == x && right == y)
			return nodes[node_id - 1];

		int mid = (left + right) / 2;

		int value = 0;

		// if both query range lies inside the left half of the range of current node
		if (x >= left & y <= mid)
			value += get_sum(2 * node_id, left, mid, x, y); // left and mid are the range of the left child
		else if (x > mid && y <= right) // if both query range lies inside the right half of the range of current node
			value += get_sum(2 * node_id + 1, mid + 1, right, x, y); // mid + 1 and right are the range of the right child
		else 
		{
			// the range has elements from both left side of the node and the right side of the node
			value += get_sum(2 * node_id, left, mid, x, mid); // now our search range is x to mid, sine rest will be searched in the right child
			value += get_sum(2 * node_id + 1, mid + 1, right, mid + 1, y);
		}

		return value;

	}

	// here left and right contains the range of this node
	void construct_tree(vector<int>& num, int node_id, int left, int right)
	{
		// we are at leaf of the tree
		if (left == right)
		{
			if (left < num.size()) // check the leaf index is out of range because of extending the leafs to make full binary tree 
				nodes[node_id - 1] = num[left];

			return;
		}

		int mid = (left + right) / 2;

		// fill the left subtree with the elements of left half of the tree
		// node_id of left sub tree is 2 * node_id
		construct_tree(num, 2 * node_id, left, mid);

		// fill the left subtree with the elements of left half of the tree
		// node_id of left sub tree is 2 * node_id
		construct_tree(num, 2 * node_id + 1, mid + 1, right);

		// add the value of left child and right child and store in the parent node
		// important: before stroing the value, convert the node_id to vector index pos
		nodes[node_id - 1] = nodes[2 * node_id - 1] + nodes[2 * node_id];
	}

};

int main()
{
	vector<int> value{ 1,2,3,4,5,6,7,8,9,10 };


	segment_tree s_tree;
	s_tree.build_tree(value);

	

	for (int i = 0; i < 5; i++)
	{
		int pos, value;
		cin >> pos >> value;

		s_tree.update(pos, value);
	}

	for (int i = 0; i < 5; i++)
	{
		int range_s, range_e;
		cin >> range_s >> range_e;

		cout << s_tree.query_sum(range_s, range_e) << endl;
	}

	return 0;

}