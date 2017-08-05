#include <iostream>
#include <vector>

using namespace std;

// segment tree - lazy propagation
// range sum query
// update query is on a range
// then query to get the sum of a range

// 1 index based array
int arr[1000006];

long long seg_tree[4000009];
int propagate[4000009];


// make the tree from the arr array
void make_tree(int node_id, int left, int right)
{
	if (left == right)
	{
		seg_tree[node_id] = arr[left];
		return;
	}

	int mid = (left + right) / 2;

	make_tree(2 * node_id, left, mid);
	make_tree(2 * node_id + 1, mid + 1, right);

	seg_tree[node_id] = seg_tree[2 * node_id] + seg_tree[2 * node_id + 1];
}

void update(int node_id, int left, int right, int add_value, int arr_pos)
{
	if (left == right && left == arr_pos)
	{
		seg_tree[node_id] += add_value;
		return;
	}

	int mid = (left + right) / 2;

	if (arr_pos <= mid)
		update(2 * node_id, left, mid, add_value, arr_pos);
	else
		update(2 * node_id + 1, mid + 1, right, add_value, arr_pos);


	seg_tree[node_id] = seg_tree[2 * node_id] + seg_tree[2 * node_id + 1];
}

long long sum_range(int node_id, int left, int right, int x, int y, int parent_propagate)
{
	if (x > right || y < left)
		return 0;

	if (left == x && right == y)
		return seg_tree[node_id] + parent_propagate;

	int mid = (left + right) / 2;

	long long result = sum_range(2 * node_id, left, mid, x, y > mid ? mid : y, parent_propagate + propagate[node_id]);
	result += sum_range(2 * node_id + 1, mid + 1, right, x > (mid + 1) ? x : (mid + 1), y, parent_propagate + propagate[node_id]);

	return result;
}

void update_range(int node_id, int left, int right, int x, int y, int add_value)
{
	if (x > right || y < left)
		return;

	if (left == x && right == y)
	{
		propagate[node_id] += add_value;
		seg_tree[node_id] += ((right - left + 1) * add_value);
		return;
	}


	int mid = (left + right) / 2;

	update_range(2 * node_id, left, mid, x, y <= mid ? y : mid, add_value);
	update_range(2 * node_id + 1, mid + 1, right, x > (mid + 1) ? x : (mid + 1), y, add_value);

	seg_tree[node_id] = seg_tree[2 * node_id] + seg_tree[2 * node_id + 1];
}


int main()
{
	int N;
	cin >> N;
	for (int i = 1; i <= N; i++)
		cin >> arr[i];

	make_tree(1, 1, N);


	while (true)
	{
		int q_type;
		cin >> q_type;

		switch (q_type)
		{
		case 1:
		{
			int pos, add_value;
			cin >> pos >> add_value;
			update(1, 1, N, add_value, pos);
			break;
		}

		case 2:
		{
			int x, y, add_value;
			cin >> x >> y >> add_value;
			update_range(1, 1, N, x, y, add_value);
			break;
		}

		case 3:
		{
			int x, y;
			cin >> x >> y;
			long long res = sum_range(1, 1, N, x, y, 0);
			cout << res << endl;
			break;
		}

		default:
			cout << "Not a valid query!" << endl;
		}
	}

	return 0;
}