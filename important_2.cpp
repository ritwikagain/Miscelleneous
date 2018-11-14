#include <bits/stdc++.h>

using namespace std;

#define V 4

struct Node
{
	int data;
	struct Node * next;
	struct Node * random;
	Node (int x)
	{
		data = x;
		next = random = NULL;
	}
};
struct treeNode 
{ 
    int data; 
    struct treeNode *left; 
    struct treeNode *right; 
    struct treeNode *nextRight; 
}; 
void printAllSubarrays  (int a[], int n)
{
    unordered_map<int, vector<int> >m;
    vector<pair<int, int> >result;
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += a[i];
        if (sum == 0)
        {
            result.push_back (make_pair (0, i));
        }

        unordered_map<int, vector<int> >::iterator it;
        it = m.find (sum);
        if (it != m.end())
        {
            int size = it->second.size();
            for (int j = 0; j < size; j++)
            {
                result.push_back (make_pair (it->second[j] + 1, i));
            }
            m[sum].push_back (i);
        }
        else
        {
            m[sum].push_back (i);
        }
    }

    int size = result.size ();
    cout << "All the subarrays with 0 sum are:" << endl;
    for (int i = 0; i < size; i++)
    {
        cout << result[i].first << " " << result[i].second << endl;
    }
}
void maxPdtSubArrayOfSizeK (int a[], int n, int k)
{
    if (k > n) return;
    int mul = 1;
    int zero_count = 0;
    int maxPdt = 1;
    bool status = false; // to handle the condition where all elements are 0s

    for (int i = 0; i < k; i++)
    {
        if (a[i] == 0)
        {
            zero_count++;
            continue;
        }
        else
        {
            status = true;
        }
        mul *= a[i];
    }
    if (zero_count == 0)
    {
        maxPdt = max (maxPdt, mul);
    }

    int w_start = 0;
    int w_end = k - 1;
    for (int i = k; i < n; i++)
    {
        if (a[w_start] != 0)
        {
            status = true;
            mul /= a[w_start];
        }
        else
        {
            zero_count--;
        }
        w_start++;

        w_end++;
        if (a[w_end] != 0)
        {
            mul *= a[w_end];
        }
        else
        {
            zero_count++;
        }

        if (zero_count == 0)
        {
            maxPdt = max (maxPdt, mul);
        }
        cout << mul << endl;
    }

    if (status == false) // all values are 0s
    {
        maxPdt = 0;
    }
    cout << "The max product subarray of size " << k << " is: " <<  maxPdt << endl;
}
void swap (int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
void alternate (int a[], int n)
{
    // segregate
    int i = 0, j = n - 1;
    while (i < j)
    {
        while (a[i] >= 0) i++;
        while (a[j] < 0) j--;
        if (i < j)
            swap (&a[i], &a[j]);
    }
    // now -ve values start from index i
    // alternate
    j = i; i = 1;
    while (i < n && j < n)
    {
        swap (&a[i], &a[j]);
        i += 2;
        j++;
    }

    cout << "The modified array is : " << endl;
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";
    cout << endl;
}
void removeDuplicates (string s)
{
    int size = s.size();
    int w_index = 0;
    int i = 1;
    for (; i < size; i++)
    {
        if (s[i] != s[i - 1])
        {
            s[w_index++] = s[i - 1];
        }
        else
        {
            while (s[i] == s[i - 1])
                i++;
        }
    }
    s[w_index++] = s[i - 1];
    s.erase (w_index, size - w_index);
    if (w_index != size)
        removeDuplicates (s);
    else
        cout << "The string after removing all duplicates: " << s << endl;
}
bool dictionaryContains (string s)
{
    string dictionary[] = {"mobile", "samsung", "sam", "sung", "man", "mango", "icecream", "and",
                            "go", "i", "like", "ice", "cream"};
    int size = sizeof (dictionary) / sizeof (dictionary[0]);
    for (int i = 0; i < size; i++)
    {
        if (dictionary[i].compare (s) == 0)
        {
            return true;
        }
    }
    return false;
}
bool wordBreak (string s)
{
    int size = s.size ();
    bool wb[size + 1]; // wb[i] will tell if s[0 ... i - 1] can be transformed to valid words
    memset (wb, 0, sizeof (wb));
    for (int i = 0; i <= size; i++)
    {
        if (!wb[i] && dictionaryContains (s.substr (0, i)))
        {
            wb[i] = true;
            if (i == size)
                return true;
        }

        if (wb[i])
        {
            for (int j = i + 1; j <= size; j++)
            {
                if (!wb[j] && dictionaryContains (s.substr (i, j - i)))
                {
                    wb[j] = true;
                    if (j == size)
                        return true;
                }
            }
        }
    }
    return false;
}
int getPivot (int a[], int left, int right)
{
    if (left > right) return -1;
    if (left == right) return left;

    int mid = (left + right) / 2;
    if (mid < right && a[mid] > a[mid + 1])
        return mid;
    if (mid > left && a[mid] < a[mid - 1])
        return mid - 1;
    if (a[left] <= a[mid])
        return getPivot (a, left, mid - 1);
    else
        return getPivot (a, mid + 1, right);
}
int binSearch (int a[], int left, int right, int key)
{
    if (left > right) return -1;
    if (left == right)
        return a[left] == key ? true : false;
    int mid = (left + right) / 2;
    if (a[mid] == key)
        return true;
    else if (a[mid] < key)
        return binSearch (a, mid + 1, right, key);
    else
        return binSearch (a, left, mid - 1, key);
}
int searchRotated (int a[], int n, int k)
{
    int pivot = getPivot (a, 0, n - 1);
    cout << "pivot: " << a[pivot] << endl;
    if (a[0] <= k && k <= a[pivot])
        return binSearch (a, 0, pivot, k);
    else
        return binSearch (a, pivot + 1, n - 1, k);
}
bool isSafe (bool graph[][V], int nodeId, int color[], int colorIndex)
{
	for (int i = 0; i < V; i++)
	{
		if (graph[nodeId][i] && color[i] == colorIndex)
			return false;
	}
	return true;
}
bool graphColoringUtil (bool graph[][V], int M, int color[], int nodeId)
{
	if (nodeId == V)
		return true;
	
	for (int i = 1; i <= M; i++)
	{
		if (isSafe (graph, nodeId, color, i))
		{
			color[nodeId] = i;
			if (graphColoringUtil (graph, M, color, nodeId + 1))
				return true;
			color[nodeId] = 0;
		}
	}
	return false;
}
void graphColoring (bool graph[][V], int M)
{
	int color[V];
	memset (color, 0, sizeof (color));
	
	if (!graphColoringUtil (graph, M, color, 0))
		cout << "The graph can't be colored with M colors." << endl;
	else
	{
		cout << "The graph can be colored with " << M << " colors and the scheme is: ";
		for (int i = 0; i < V; i++)
		{
			cout << color[i] << " ";
		}
		cout << endl;
	}
}
void printLL (Node *head)
{
	while (head)
	{
		cout << "Data: " << head->data << " random: " << head->random->data << endl; 
		head = head->next;
	}
}
Node * clone (Node * head)
{
	// insert cloned nodes in the original LL
	Node * temp = head;
	while (temp)
	{
		Node * next = temp->next;
		temp->next = new Node (temp->data);
		temp->next->next = next;
		temp = next;
	}
	// set random pointers of cloned nodes
	temp = head;
	while (temp)
	{
		if (temp->next)
		{
			temp->next->random = temp->random->next;
			temp = temp->next->next;
		}
		else	
			temp = temp->next;
	}
	// separate original and cloned LL
	Node *original = head;
	Node * copy;
	if (head)
		copy = head->next;
	temp = copy;
	while (original && copy)
	{
		if (original->next)
			original->next = original->next->next;
		if (copy->next)
			copy->next = copy->next->next;
	}
	return temp;
}
void rotate90 (int m[][V - 1])
{
	int row = V;
	int col = V - 1;
	int res[row][col];
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			res[j][row - i - 1] = m[i][j]; 
		}
	}
	
	cout << "The rotated array is: " << endl;
	for (int i = 0; i < col; i++)
	{
		for (int j = 0; j < row; j++)
		{
			cout << res[i][j] << " ";
		}
		cout << endl;
	}
}
void rotateInPlace90 (int m[V][V])
{
	for (int i = 0; i < V / 2; i++)
	{
		for (int j = i; j < V - i - 1; j++)
		{
			int temp = m[i][j];
			m[i][j] = m[j][V - i -1];
			m[j][V - i -1] = m[V - i - 1][V - j - 1];
			m[V - i - 1][V - j - 1] = m[V - j - 1][i];
			m[V - j - 1][i] = temp;
		}
	}
	
	cout << "The rotated in-place array is: " << endl;
	for (int i = 0; i < V; i++)
	{
		for (int j = 0; j < V; j++)
		{
			cout << m[i][j] << " ";
		}
		cout << endl;
	}
}
int merge (int a[], int left, int mid, int right)
{
	int inv = 0;
	int temp[right - left + 1];
	int i = left, j = mid, index = 0;
	for (; i <= mid - 1 && j <= right; )
	{
		if (a[i] <= a[j])
		{
			temp[index++] = a[i++];
		}
		else
		{
			inv += mid - i;
			temp[index++] = a[j++];
		}
	}
	
	while (i <= mid - 1)
	{
		temp[index++] = a[i++];
	}
	
	while (j <= right)
	{
		temp[index++] = a[j++];
	}
	
	for (int k = 0; k < index; k++)
	{
		a[left + k] = temp[k];
	}
	return inv;
}
int mergeSort (int a[], int left, int right)
{
	int inv = 0;
	if (left < right)
	{
		int mid = (left + right) / 2;
		inv = mergeSort (a, left, mid);
		inv += mergeSort (a, mid + 1, right);
		inv += merge (a, left, mid + 1, right);
	}
	return inv;
}
bool issafe3 (bool m[][V], int x, int y, bool visited[][V])
{
	return (x >= 0 && x < V) &&
			(y >= 0 && y < V) &&
			(!visited[x][y]) &&
			(m[x][y] == 1);
}
void DFS3 (bool m[][V], int x, int y, bool visited[][V], int *count)
{
	int rowNbr[] = {0, 0, -1, 1, -1, -1, 1, 1};
	int colNbr[] = {1, -1, 0, 0, 1, -1, -1, 1};
	
	visited[x][y] = true;
	// count increase
	for (int i = 0; i < 4; i++)
	{
		int neighX = x + rowNbr[i];
		int neighY = y + colNbr[i];
		if ((neighX >= 0 && neighX < V) && (neighY >= 0 && neighY < V))
		{
			if (m[neighX][neighY] == 0)
			{
				(*count)++;
			}
		}
	}
	// corner element
	if ((x == 0 && (y == 0 || y == V - 1)) || (x == V - 1 && (y == 0 || y == V - 1)))
	{
		*count += 2;
	}
	else if (x == 0 || x == V - 1 || y == 0 || y == V - 1)
	{
		// element on the side
		*count += 1;
	}
	// recur for DFS
	for (int i = 0; i < 8; i++)
	{
		int neighX = x + rowNbr[i];
		int neighY = y + colNbr[i];
		if (issafe3 (m, neighX, neighY, visited))
		{
			DFS3 (m, neighX, neighY, visited, count);
		}
	}
}
int islandPerimeter (bool m[][V], int ROW, int COL)
{
	bool visited [V][V];
	int maxcount = 0;
	memset (visited, 0, sizeof (visited));
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			int count = 0;
			if (m[i][j] == 1 && !visited[i][j])
			{
				DFS3 (m, i, j, visited, &count);
			}
			if (count > maxcount)
			{
				maxcount = count;
			}
		}
	}
	return maxcount;
}
void printBrackets (int left, int right, int brackets[][V + 1], char& s)
{
	if (left == right)
	{
		cout << s++;
		return;
	}
	
	cout << "(";
	printBrackets (left, brackets[left][right], brackets, s);
	printBrackets (brackets[left][right] + 1, right, brackets, s);
	cout << ")";
}
void matrixChainOrder (int a[], int n) // there are n - 1 matrices  // n = v + 1
{
	int dp[V + 1][V + 1];
	int brackets[V + 1][V + 1];
	memset (brackets, -1, sizeof (brackets));
	
	for (int i = 1; i < n; i++)
	{
		dp[i][i] = 0;
	}
	
	for (int gap = 2; gap < n; gap++)
	{
		for (int i = 1; i < n - gap + 1; i++)
		{
			int j = i + gap - 1;
			dp[i][j] = INT_MAX;
			for (int k = i; k < j; k++)
			{
				int temp = dp[i][k] + dp[k + 1][j] + a[i - 1] * a[k] * a[j];
				if (temp < dp[i][j])
				{
					dp[i][j] = temp;
					brackets[i][j] = k;
				}
			}
		}
	}
	
	char s = 'A';
	printBrackets (1, n - 1, brackets, s);
	cout << endl;
}
vector <int> graph[V+ 1];
void add_edge (int source, int destination, int indegree[V + 1])
{
	graph[source].push_back (destination);
	indegree[destination]++;
}
vector<int> topological_sort (int indegree[], int N)
{
	queue<int> Q;
	vector<int> result;
	for (int i = 0; i < N; i++)
	{
		if (indegree[i] == 0)
		{
			Q.push(i);
		}
	}
	
	if (Q.empty())
	{
		cout << "There are no possible ways." << endl;
		return result;
	}
	
	int counter = 0;
	while (!Q.empty())
	{
		int node = Q.front();
		Q.pop();
		result.push_back(node);
		counter++;
		
		for (int j = graph[node].size() - 1; j >= 0; j--)
		{
			indegree[graph[node][j]]--;
			if (indegree[graph[node][j]] == 0)
			{
				Q.push(graph[node][j]);
			}
		}	
	}
	
	if (counter != N)
	{
		cout << "The graph has a cycle." << endl;
	}
	return result;
}
int numberofPaths (int source, int destination, int N, int indegree[])
{
	vector<int> v = topological_sort (indegree, N);
	int dp[N]; // dp[i] => no of ways to reach destination from i
	memset (dp, 0, sizeof(dp));
	dp[destination] = 1;
	for (int i = v.size() - 1; i >= 0; i--)
	{
		for (int j = graph[v[i]].size() - 1; j >= 0; j--)
		{
			dp[v[i]] += dp[graph[v[i]][j]];
		}
	}
	return dp[source];
}
int eggDrop (int n, int k) // n eggs, k floors
{
	int eggFloor[n + 1][k + 1];
	
	for (int i = 1; i <= k; i++)
	{
		eggFloor[1][i] = i;
	}
	
	for (int i = 1; i <= n; i++)
	{
		eggFloor[i][1] = 1;
		eggFloor[i][0] = 0;
	}
	
	for (int i = 2; i <= n; i++) // fixing eggs
	{
		for	(int j = 2; j <= k; j++) // fixing floors
		{
			eggFloor[i][j] = INT_MAX;
			for (int p = 2; p <= j; p++)
			{
				eggFloor[i][j] = min (eggFloor[i][j], max (eggFloor[i - 1][p - 1], eggFloor[i][j - p]));
			}
			eggFloor[i][j] += 1;
		}
	}
	return eggFloor[n][k];
}
int searchFirstOne (bool *a, int left, int right)
{
	if (left > right) return -1;
	if (left == right) 
	{
		if (a[left] == 1)
		{
			return left;
		}
		return -1;
	}
	
	int mid = (left + right) / 2;
	if (left < mid && a[mid] == 1 && a[mid - 1] == 0)
	{
		return mid;
	}
	if (mid < right && a[mid] == 0 && a[mid + 1] == 1)
	{
		return mid + 1;
	}
	if (a[mid] == 0)
	{
		return searchFirstOne (a, mid + 1, right);
	}
	return searchFirstOne (a, left, mid - 1);
}
int rowWithMax1s (bool m[V][V])
{
	int row_index = -1;
	int first = searchFirstOne (m[0], 0, V - 1);
	
	for (int i = 1; i < V; i++)
	{
		if (first == -1)
		{
			first = searchFirstOne (m[i], 0, V - 1);
			if (first != -1)
			{
				row_index = i;
			}
		}
		else
		{
			if (m[i][first] == 1)
			{
				first = searchFirstOne (m[i], 0, first);
				row_index = i;
			}
		}
	}
	return row_index;
}
treeNode* newnode(int data) 
{ 
    treeNode* node = (treeNode*) 
                        malloc(sizeof(treeNode)); 
    node->data = data; 
    node->left = NULL; 
    node->right = NULL; 
    node->nextRight = NULL; 
  
    return(node); 
} 
treeNode * getNextRight (treeNode * p)
{
	treeNode * q = p->nextRight;
	while (q != NULL)
	{
		if (q->left != NULL)
			return q->left;
		if (q->right != NULL)
			return q->right;
		q = q->nextRight;
	}
	return NULL;
}
void connect (treeNode * root)
{
	if (root == NULL) return;
	root->nextRight = NULL;
	
	while (root != NULL)
	{
		// traverse at each level
		treeNode * p = root;
		while (p != NULL)
		{
			if (p->left)
			{
				if (p->right)
					p->left->nextRight = p->right;
				else
					p->left->nextRight = getNextRight (p);
			}
			if (p->right)
				p->right->nextRight = getNextRight (p);
			p = p->nextRight;
		}
		
		// go to the next level
		if (root->left)
			root = root->left;
		else if (root->right)
			root = root->right;
		else
			root = root->nextRight;
	}
}
bool isSubsetSum (int a[], int n, int sum)
{
	bool dp[n + 1][sum + 1];
	
	for (int i = 0; i <= n; i++)
		dp[i][0] = true;
	for (int i = 0; i <= sum; i++)
		dp[0][i] = false;
	
	for (int i = 1; i <= n; i++) // traversing through all the elements
	{
		for (int j = 1; j <= sum; j++)
		{
			if (a[i - 1] > j)
				dp[i][j] = dp[i - 1][j];
			else
				dp[i][j] = dp[i - 1][j] || dp[i - 1][j - a[i - 1]];
		}
	}
	return dp[n][sum];
}
int main ()
{
    // print all subarrays of 0 sum
    int arr1[] = {6, 3, -1, -3, 4, -2, 2, 4, 6, -12, -7};
    int n1 = sizeof (arr1) / sizeof (arr1[0]);
    printAllSubarrays (arr1, n1);
    // max product subbarray of size k (0s included)
    int arr2[] = {0, 1, 2, 0, 0, 4, 5, 6, 0, 0, 7, 0};
    int n2 = sizeof (arr2) / sizeof (arr2[0]);
    int k2 = 3;
    maxPdtSubArrayOfSizeK (arr2, n2, k2);
    // alternating +ve -ve without maintaining order
    int arr3[] = {-5, -2, 5, 2, 4, 7, 1, 8, 0, -8};
    int n3 = sizeof (arr3) / sizeof (arr3[0]);
    alternate (arr3, n3);
    // recursively remove all adjacent duplicates
    string s1 = "azxxzy";
    removeDuplicates (s1);
    // word break problem
    string s2 = "ilikesamsung";
    if (wordBreak (s2))
        cout << s2 << " is a valid sentence." << endl;
    else
        cout << s2 << " is not a valid sentence." << endl;
    // search an element in a sorted and rotated array (with pivot)
    int arr4[] = {5, 6, 7, 8, 9, 10, 1, 2, 3};
    int n4 = sizeof (arr4) / sizeof (arr4[0]);
    int k4 = 6;
    cout << "The index of the searched element is: " << searchRotated (arr4, n4, k4) << endl;
	// M coloring problem
	bool graph5[V][V] = {{0, 1, 1, 1}, 
        {1, 0, 1, 0}, 
        {1, 1, 0, 1}, 
        {1, 0, 1, 0}, 
    }; 
    int m5 = 3; // Number of colors 
    graphColoring (graph5, m5);
	// clone linked list with next and random pointer with O(1) space
	Node* start = new Node(1); 
    start->next = new Node(2); 
    start->next->next = new Node(3); 
    start->next->next->next = new Node(4); 
    start->next->next->next->next = new Node(5); 
  
    // 1's random points to 3 
    start->random = start->next->next; 
  
    // 2's random points to 1 
    start->next->random = start; 
  
    // 3's and 4's random points to 5 
    start->next->next->random = 
                    start->next->next->next->next; 
    start->next->next->next->random = 
                    start->next->next->next->next; 
  
    // 5's random points to 2 
    start->next->next->next->next->random = 
                                      start->next; 
  
    cout << "Original list : \n"; 
    printLL(start); 
  
    cout << "\nCloned list : \n"; 
    //Node *cloned_list = clone(start); 
    //printLL(cloned_list); 
	
	// rotate an image by 90 degree
	int matrix1[V][V - 1] = {{1, 2, 3},
							{4, 5, 6},
							{7, 8, 9},
							{10, 11, 12}};
	rotate90 (matrix1);
	// rotate a square image in place by 90 degree
	int matrix2[V][V] = {{1, 2, 3, 4},{5, 6, 7, 8},{9, 10, 11, 12},{13, 14, 15, 16}};
	rotateInPlace90 (matrix2);
	
	// inversion count in an array via merge sort
	int arr5[] = {1, 20, 6, 4, 5};
	int n5 = sizeof (arr5) / sizeof (arr5[0]);
	cout << "Number of inversions are: " << mergeSort (arr5, 0, n5 - 1) << endl;
	
	// printing brackets in matrix chain order
	int arr6[] = {40, 20, 30, 10, 30};
	int n6 = sizeof (arr6) / sizeof (arr6[0]);
	matrixChainOrder (arr6, n6);
	// perimeter of the island
	bool matrix3[V][V] = {  {1, 0, 0, 0},
							{0, 1, 0, 0},
							{0, 0, 1, 0},
							{0, 0, 0, 1}};
	cout << "The perimeter of the island is: " << islandPerimeter (matrix3, V, V) << endl;
	
	// topological sort application : no of paths from source to destination in a DAG 
    int source = 0, destination = 4;  // total number of nodes: 5
    int indegree[V + 1];
	memset (indegree, 0, sizeof (indegree));
    add_edge(0, 1, indegree); 
    add_edge(0, 2, indegree); 
    add_edge(0, 3, indegree); 
    add_edge(0, 4, indegree); 
    add_edge(2, 3, indegree); 
    add_edge(3, 4, indegree); 
    cout << "The total number of paths from " << source << " to " << destination << " is: " << numberofPaths(source, destination, V + 1, indegree) << endl;
	
	// egg drop puzzle
	int n7 = 2, k7 = 36; 
    printf ("Minimum number of trials in worst case with %d eggs and "
             "%d floors is %d \n", n7, k7, eggDrop(n7, k7));
	// find 2 non repeating elements in array of repeating elements
	// maximum no of 1s in a row-wise sorted matrix of 0s and 1s
	bool matrix4[V][V] = { {0, 0, 0, 1}, 
                       {0, 1, 1, 1}, 
                       {1, 1, 1, 1}, 
                       {0, 0, 0, 0}}; 
  
    printf("Index of row with maximum 1s is %d "
                                , rowWithMax1s(matrix4)); 
	
	// conect nodes at same level in constant space in a binary tree
	treeNode *root = newnode(10); 
    root->left        = newnode(8); 
    root->right       = newnode(2); 
    root->left->left  = newnode(3); 
    root->right->right       = newnode(90); 
    connect(root); 
    printf("Following are populated nextRight pointers in the tree "
           "(-1 is printed if there is no nextRight) \n"); 
    printf("nextRight of %d is %d \n", root->data, 
           root->nextRight? root->nextRight->data: -1); 
    printf("nextRight of %d is %d \n", root->left->data, 
           root->left->nextRight? root->left->nextRight->data: -1); 
    printf("nextRight of %d is %d \n", root->right->data, 
           root->right->nextRight? root->right->nextRight->data: -1); 
    printf("nextRight of %d is %d \n", root->left->left->data, 
           root->left->left->nextRight? root->left->left->nextRight->data: -1); 
    printf("nextRight of %d is %d \n", root->right->right->data, 
           root->right->right->nextRight? root->right->right->nextRight->data: -1);
	// subset sum problem
	int arr8[] = {3, 34, 4, 12, 5, 2}; 
	int sum = 10; 
	int n8 = sizeof(arr8)/sizeof(arr8[0]); 
	if (isSubsetSum(arr8, n8, sum) == true) 
	 printf("Found a subset with given sum"); 
	else
	 printf("No subset with given sum"); 
	// print longest palindromic substring
	// backtracking: sudoku
	// union and intersection of unsorted linked lists
	// find pair of given sum in a sorted linked list
	// sort all 0s 1s and 2s in a LL
	// sorted insert in a circular LL
	// application of UNION FIND
	
	// check if a given binary tree is sum tree
	// complete binary tree from given preorder and postorder traversal
	// serialize and deserialize a tree
	
    return 0;
}
