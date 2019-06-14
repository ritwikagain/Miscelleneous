#include <bits/stdc++.h>

#define K 3

using namespace std;
struct Data
{
	int value;
	int vector_index;  // which vector in the array of vectors
	int index_in_vector; // which element in a particular vector
	
	Data() : value(-1), vector_index(-1), index_in_vector(-1) 
	{}
};
void swap (int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}
class MinHeap
{
	Data data[K];
	int size;
	int curr_size;
	public:
		MinHeap (int size_) : size(size_), curr_size(0)
		{}
		bool empty ()
		{
			return (curr_size == 0) ? true : false;
		}
		void push (Data d)
		{
			if (curr_size >= size) 
			{
				cout << "The size of the heap exceeds its maximum size!" << endl;
				return;
			}
			
			data[curr_size] = d;
			int local_current = curr_size;
			int parent = (curr_size - 1) / 2;
			cout << "\tcurrent: " << local_current << " parent: " << parent << endl;
			while (parent != local_current)
			{
				if (data[parent].value > data[local_current].value)
				{
					swap (&data[parent].value, &data[local_current].value);
					local_current = parent;
					parent = (local_current - 1) / 2;
					cout << "\tcurrent: " << local_current << " parent: " << parent << endl;
				}
				else
					break;
			}
			curr_size++;
		}
		Data pop ()
		{
			if (curr_size == 0)
			{
				cout << "The heap is empty!" << endl;
				return Data();
			}
			
			Data result = data[0];
			cout << "\tSaving top of the heap: " << result.value << endl;
			data[0] = data[--curr_size];
			cout << "\tReplacing top of the heap with the last value: " << data[0].value << endl;
			int local_current = 0;
			cout << "\tcurrent: " << local_current << endl;
			while (local_current < curr_size)
			{
				int l_child = local_current * 2 + 1;
				int r_child = local_current * 2 + 2;
				cout << "\tleft child: " << l_child << ", right child: " << r_child << endl;
				int smallest = local_current;
				if (l_child < curr_size && data[l_child].value < data[local_current].value)
					smallest = l_child;

				if (r_child < curr_size && data[smallest].value > data[r_child].value)
					smallest = r_child;
				
				if (local_current != smallest)
				{
					swap (&data[local_current].value, &data[smallest].value);
					swap (&data[local_current].vector_index, &data[smallest].vector_index);
					swap (&data[local_current].index_in_vector, &data[smallest].index_in_vector);
					local_current = smallest;
				}
				else
					break;
				cout << "\tcurrent: " << local_current << endl;
			}
			return result;
		}
};
vector<int> mergeKSortedArrays (vector<vector<int> > v)
{
	int no_of_arrays = K;
	MinHeap MH(K);
	vector<int> result;
	if (no_of_arrays == 0 || no_of_arrays != v.size()) return result;
	
	for (int i = 0; i < K; i++)
	{
		Data d;
		cout << "Adding " << v[i][0] << ", vector_index: " << i << ", index_in_vector: " << 0 <<endl;
		d.value = v[i][0];
		d.vector_index = i;
		d.index_in_vector = 0;
		MH.push (d);
	}
	
	while (!MH.empty())
	{
		cout << "Popping..." << endl;
		Data d = MH.pop();
		result.push_back (d.value);
		cout << "Popping: " << d.value << ", vector_index: " << d.vector_index << ", index_in_vector: " << d.index_in_vector <<endl;
		Data new_d;
		if (d.index_in_vector < v[d.vector_index].size() - 1)
		{
			new_d.index_in_vector = d.index_in_vector + 1;
		}
		else
			continue;
		new_d.vector_index = d.vector_index;
		new_d.value = v[new_d.vector_index][new_d.index_in_vector];
		cout << "Adding " << new_d.value << endl;
		MH.push (new_d);
	}
	return result;
}
int main ()
{
	vector<vector<int> > v(K);
	v[0] = {1, 5, 10, 15};
	v[1] = {2, 6, 11, 16};
	v[2] = {3, 7, 12, 17};
	vector<int> result = mergeKSortedArrays (v);
	int size = result.size();
	for (int i = 0; i < size; i++)
		cout << result[i] << " ";
	cout << endl;
 	return 0;
}