#include <bits/stdc++.h>
using namespace std;

#define M 3
#define N 3
#define ROW 4
#define COL 5
#define MAX_ALPHABET 26
#define MAX_CHAR 256 
#define CHESSBOARD_SIZE 8

string dictionary[] = {"GEEKS", "FOR", "QUIZ", "GO"};
int size_of_dict = sizeof(dictionary)/sizeof(dictionary[0]);

bool isWord(string word)
{
	for (int i = 0; i < size_of_dict; i++)
	{
		if(word.compare(dictionary[i]) == 0)
			return true;
	}
	return false;
}

bool isSafe (int row, int col, bool visited[][N])
{
	return (row >= 0) && (row < M) &&
			(col >= 0) && (col < N) &&
			(!visited[row][col]);
}

void DFS (char boggle[][N], int row, int col, bool visited[][N], string word)
{
	int rowNbr[] = {-1, 0, 1, 1, 1, 0, -1, -1};
	int colNbr[] = {-1, -1, -1, 0, 1, 1, 1, 0};
	
	word += boggle[row][col];
	if (isWord(word))
	{
		cout << word << endl;
	}
	visited[row][col] = true;
	
	for (int k = 0; k < 8; k++)
	{
		if (isSafe(row + rowNbr[k], col + colNbr[k], visited))
		{
			DFS (boggle, row + rowNbr[k], col + colNbr[k], visited, word);
		}
	}
	
	word.erase(word.size()-1);
	visited[row][col] = false;
	
}
void findWords (char boggle[][N])
{
	bool visited[M][N];
	memset(visited, 0, sizeof(visited));
	string word = "";
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			DFS(boggle, i, j, visited, word);
		}
	}
}

struct Node
{
	int index_in_vec;
	int vector_index;
	int value;
};
struct compare
{
	int operator () (const Node& a, const Node& b)
	{
		return a.value > b.value;
	}
};
vector<int> mergeKArrays(vector<vector<int> > arr)
{
	priority_queue<Node, vector<Node>, compare> pq;
	vector<int> result;
	int size = arr.size();
	for (int i = 0; i < size; i++)
	{
		if (arr[i].size() > 0)
		{
			Node n;
			n.vector_index = i;
			n.index_in_vec = 0;
			n.value = arr[i][0];
			pq.push(n);
		}
	}
	
	while (!pq.empty())
	{
		Node ele = pq.top();
		pq.pop();
		result.push_back(ele.value);
		if (ele.index_in_vec + 1 < arr[ele.vector_index].size())
		{
			ele.index_in_vec++;
			ele.value = arr[ele.vector_index][ele.index_in_vec];
			pq.push(ele);
		}
	}
	
	return result;
}
int findMaximum (int arr[], int left, int right)
{
	if (left > right) return INT_MIN;
	if (left == right) return arr[left];
	if (left + 1 == right) return arr[left] < arr[right] ? arr[right] : arr[left];
	
	int mid = (left + right) / 2;
	
	if (arr[mid - 1] < arr[mid] && arr[mid] > arr[mid + 1]) return arr[mid];
	
	if (arr[mid - 1] < arr[mid]) return findMaximum(arr, mid, right);
	else						 return findMaximum(arr, left, mid - 1);	
}
int search (int arr[], int left, int right, int key)
{
	if (left > right) return -1;
	if (left == right) return arr[left] == key ? left : -1;
	if (left + 1 == right)
	{
		if (arr[left] == key) return left;
		else if (arr[right] == key) return right;
		else return -1;
	}
	
	int mid = (left + right) / 2;
	
	if (arr[mid] == key) return mid;
	if (arr[left] < arr[mid])
	{
		if (arr[left] <= key && key <= arr[mid])
		{
			return search (arr, left, mid, key);
		}
		return search (arr, mid + 1, right, key);
	}
	else
	{
		if (arr[mid] <= key && key <= arr[right])
		{
			return search (arr, mid, right, key);
		}
		return search (arr, left, mid - 1, key);
	}
	
}
int kadane (int arr[], int n)
{
	int max_so_far = 0;
	int sum = 0;
	for (int i = 0; i < n; i++)
	{
		sum += arr[i];
		if (sum > max_so_far)
		{
			max_so_far = sum;
		}
		else if (sum < 0)
		{
			sum = 0;
		}
	}
	return max_so_far;
}
int maxCircularSum(int arr[], int n)
{
	int max_kadane = kadane (arr, n);
	int sum = 0;
	for (int i = 0; i < n; i++)
	{
		sum += arr[i];
		arr[i] *= -1;
	}
	
	int max_wrap = sum + kadane (arr, n);
	return (max_wrap > max_kadane) ? max_wrap : max_kadane;
}
int maxRepeating (int arr[], int n, int k)  // k <= n
{
	for (int i = 0; i < n; i++)
	{
		arr[arr[i]%k] += k;
	}
	
	int max = INT_MIN;
	int max_index = -1;
	for (int i = 0; i < n; i++)
	{
		if (arr[i] > max)
		{
			max = arr[i];
			max_index = i;
		}
	}
	return max_index;
}
int kadane (int arr[], int *start, int *finish, int n)
{
	int max_so_far = 0, max_ending_here = 0;
	
	for (int i = 0; i < n; i++)
	{
		max_ending_here += arr[i];
		if (max_ending_here > max_so_far)
		{
			max_so_far = max_ending_here;
			*finish = i;
		}
		else if (max_ending_here < 0)
		{
			max_ending_here = 0;
			*start = i + 1;
		}
	}
	
	if (*finish != -1) return max_so_far;
	
	max_ending_here = arr[0];
	*start = *finish = 0;
	for (int i = 1; i < n; i++)
	{
		if (arr[i] > max_ending_here)
		{
			max_ending_here = arr[i];
			*start = *finish = i;
		}
	}
	return max_ending_here;
}
void findMaxSum (int arr[ROW][COL])
{
	int a[ROW];
	int maxResult = INT_MIN, currResult = INT_MIN;
	int resultLeft = -1, resultRight = -1, resultTop = -1, resultDown = -1;
	int start = 0, end = -1;
	for (int left = 0; left < COL; left++)
	{
		memset (a, 0, sizeof(a));
		for (int right = left; right < COL; right++)
		{
			for (int i = 0; i < ROW; i++)
			{
				a[i] += arr[i][right];
			}
			
			currResult = kadane (a, &start, &end, ROW);
			if (currResult > maxResult)
			{
				maxResult = currResult;
				resultLeft = left;
				resultRight = right;
				resultTop = start;
				resultDown = end;
			}
			
		}
	}
	
	cout << "Top left: " << resultTop << " " << resultLeft << endl;
	cout << "Bottom right: " << resultDown << " " << resultRight << endl;
	cout << "The maximum sum: " << maxResult << endl;
}
int max (int a, int b)
{
	return a > b ? a : b;
}
int getMaxArea (int arr[], int n)
{
	stack<int> s;
	int maxArea = 0;
	int i = 0;
	for (; i < n;)
	{
		if (s.empty() || arr[s.top()] <= arr[i])
		{
			s.push(i++);
		}
		else
		{
			int top = s.top();
			s.pop();
			maxArea = max (maxArea, s.empty() ? (arr[top] * i) : (arr[top] * (i - s.top() -1)));
		}
	}
	
	while (!s.empty())
	{
		int top = s.top();
		s.pop();
		maxArea = max (maxArea, s.empty() ? (arr[top] * i) : (arr[top] * (i - s.top() -1)));
	}
	return maxArea;
}
int maxRectangle (int arr[][ROW])
{
	int maxHist = getMaxArea (arr[0], ROW);
	for (int i = 1; i < ROW; i++)
	{
		for (int j = 0; j < ROW; j++)
		{
			if (arr[i][j])
			{
				arr[i][j] += arr[i - 1][j];
			}
		}
		
		maxHist = max (maxHist, getMaxArea(arr[i], ROW));
	}
	return maxHist;
}
bool isSafe (int arr[][ROW], int row, int col)
{
	return (row >= 0 && row < ROW) &&
			(col >= 0 && col < ROW)
	;		
}
int DFS1 (int arr[][ROW], int row, int col, int dp[][ROW])
{
	int rowNbr[] = {-1, 0, 1};
	int colNbr[] = {1, 1, 1};
	int currmax = 0;
	
	if (dp[row][col] != -1)
	{
		return dp[row][col];
	}
	
	for (int k = 0; k < 3; k++)
	{
		if (isSafe(arr, row + rowNbr[k], col + colNbr[k]))
		{
			currmax = max (currmax, DFS1 (arr, row + rowNbr[k], col + colNbr[k], dp));
		}
	}
	
	currmax += arr[row][col];
	dp[row][col] = currmax;
	return currmax;
}
int getMaxGold (int arr[][ROW], int m, int n)
{
	int dp[ROW][ROW];
	memset (dp, -1, sizeof(dp));
	int maxGold = 0;
	for (int i = 0; i < m; i++)
	{
		maxGold = max (maxGold, DFS1 (arr, i, 0, dp));
	}
	return maxGold;
}
void spiralPrint (int a[][ROW + 1], int row, int col)
{
	int k = 0, l = 0;
	cout << "The spiral print is: ";
	while (k < row && l < col)
	{
		for (int i = l; i < col; i++)
		{
			cout << a[k][i] << " ";
		}
		k++;
		
		for (int i = k; i < row; i++)
		{
			cout << a[i][col - 1] << " ";
		}
		col--;
		
		for (int i = col - 1; i >= l; i--)
		{
			cout << a[row - 1][i] << " ";
		}
		row--;
		
		for (int i = row - 1; i >= k; i--)
		{
			cout << a[i][l] << " ";
		}
		l++;	
	}
	cout << endl;
}

void rightShift (int a[], int left, int right)
{
	int temp = a[right];
	int i = right;
	while (i > left)
	{
		a[i] = a[i - 1];
		i--;
	}
	
	a[left] = temp;
}
void rearrange(int a[], int size)
{
	int outOfOrder = -1;
	for (int i = 0; i < size; i++)
	{
		if (outOfOrder != -1)  // already out of order element present
		{
			if ((a[i] >= 0 && a[outOfOrder] < 0) || (a[i] < 0 && a[outOfOrder] >= 0))
			{
				rightShift (a, outOfOrder, i);
				
				if (outOfOrder + 2 < i)
				{
					outOfOrder += 2;
				}
				else
				{
					outOfOrder = -1;
				}
			}
		}
		
		if (outOfOrder == -1)
		{
			if ((a[i] < 0 && (i % 2) == 0) || (a[i] >= 0 && (i % 2) != 0))
			{
				outOfOrder = i;
			}
		}
	}
	
	cout << "The rearranged array is: ";
	for (int i = 0; i < size; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
}
struct ele
{
	int freq;
	int first_index;
	
	ele() : freq(0), first_index(-1)
	{}
};
int cmp (const ele a, const ele b)
{
	return a.first_index < b.first_index;
}
int kthNonRepeating (string s, int k)
{
	int size = s.size();
	vector<ele> v(MAX_CHAR);
	
	for (int i = 0; i < size; i++)
	{
		if (v[s[i]].first_index < 0)
		{
			v[s[i]].first_index = i;
		}
		v[s[i]].freq++;
	}
	
	sort (v.begin(), v.end(), cmp);
	
	int index = -1;
	int count = 0;
	for (int i = 0; i < MAX_CHAR; i++)
	{
		if (v[i].freq == 1)
		{
			count++;
			index = v[i].first_index;
			if (count == k)
			{
				break;
			}
		}
	}
	
	if (count == k)
	{
		return index;
	}
	else
	{
		return -1;
	}
}
void allSubseq (string s)
{
	int size = s.size();
	int counter = pow(2, size);
	
	for (int i = 0; i < counter; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if ((i >> j) & 1)
			{
				cout << s[j];
			}
		}
		cout << endl;
	}
	
}

void storeInMap (vector<string> v)
{
	map<string, vector<int>> m;
	int size = v.size();
	for (int i = 0; i < size; i++)
	{
		string temp = v[i];
		sort(temp.begin(), temp.end());
		m[temp].push_back(i);
	}
	
	for (map<string, vector<int>>:: iterator i = m.begin(); i != m.end(); i++)
	{
		if (i->second.size() > 1)
		{
			for (int j = 0; j < i->second.size(); j++)
			{
				cout << v[i->second[j]] << endl;
			}
		}
	}
}

void printMedians (vector<float> v)
{
	int size = v.size();
	float median;
	int max_size = 0, min_size = 0;
	priority_queue<float> max;
	priority_queue<float, vector<float>, greater<float>> min;
	
	cout << "Median: " << " ";
	if (!v.empty())
	{
		max.push(v[0]);
		median = v[0];
		cout << median << " ";
	}
	else return;
	
	for (int i = 1; i < size; i++)
	{
		max_size = max.size();
		min_size = min.size();
		
		if (max_size > min_size)
		{
			if (v[i] < median)
			{
				min.push (max.top());
				max.pop ();
				max.push (v[i]);
			}
			else
			{
				min.push (v[i]);
			}
			
			median = (min.top() + max.top()) / 2.0;
		}
		else if (max_size == min_size)
		{
			if (v[i] < median)
			{
				max.push (v[i]);
				median = max.top ();
			}
			else
			{
				min.push (v[i]);
				median = min.top ();
			}
		}
		else // max_size < min_size
		{
			if (v[i] < median)
			{
				max.push (v[i]);
			}
			else
			{
				max.push (min.top());
				min.pop ();
				min.push (v[i]);
			}
			
			median = (min.top() + max.top()) / 2.0;
		}
		
		cout << median << " ";
	}
	cout << endl;
}
void reverse (char *a, char * b)
{
	while (a < b)
	{
		char temp = *a;
		*a = *b;
		*b = temp;
		
		a++;
		b--;
	}
}
void reverseWords (char *s)
{
	char* word_begin = NULL; 
    char* temp = s;
	
	while (*temp)
	{
		if (word_begin == NULL && *temp != ' ')
			word_begin = temp;
		if (word_begin && (*(temp + 1) == ' ' || *(temp + 1) == '\0'))
		{
			reverse (word_begin, temp);
			word_begin = NULL;
		}
		temp++;
	}
	reverse (s, temp - 1);
	cout << "The reversed sentence is: " << s << endl;
}
int longestUniqueSubsttr (char *s)
{
	int hash[MAX_ALPHABET];
	memset (hash, -1, sizeof(hash));
	int size = strlen(s);
	int longest = 0;
	int start = 0;
	int curr_len = 0;
	int prev = -1;
	
	for (int i = 0; i < size; i++)
	{
		prev = hash[s[i] - 'A'];
		if (prev == -1)
		{
			hash[s[i] - 'A'] = i;
			curr_len++;
			longest = max (longest, curr_len);
		}
		else
		{
			for (int j = start; j < prev + 1; j++)
			{
				hash[s[j] - 'A'] = -1;
			}
			start = prev + 1;
			curr_len = i - start + 1;
		}
	}		
	
	return longest;
}
void lps (string s)
{
	int size = s.size();
	int dp[size][size];
	
	for (int i = 0; i < size; i++)
		dp[i][i] = 1;
	
	for (int gap = 2; gap <= size; gap++)
	{
		for (int i = 0; i < size - gap + 1; i++)
		{
			int j = i + gap - 1;
			if (gap == 2) //&& s[i] == s[j])
			{
				if (s[i] == s[j])
					dp[i][j] = 2;
				else
					dp[i][j] = 1;
			}
			else
			{
				if (s[i] == s[j])
					dp[i][j] = dp[i + 1][j - 1] + 2;
				else
					dp[i][j] = max (dp[i + 1][j], dp[i][j - 1]);
			}
		}
	}
	
	int l = 0, r = size - 1;
	string result;
	result.reserve (dp[0][size - 1] + 1);
	int i = 0, j = dp[0][size - 1];
	for (; l < size && r >= 0;)
	{
		if (s[l] == s[r])
		{
			cout << s[l] << endl;
			result[i++] = s[l];
			result[j--] = s[l];
			l++;
			r--;
		}
		else
		{
			cout << s[l] << " " << s[r] << endl;
			if (dp[l + 1][r] > dp[l][r - 1])
			{
				l++;
			}
			else
			{
				r--;
			}
		}
	}
	
	for (int i = 0; i < size; i++)
		cout << result[i];
	
	cout << "The length of LPS is: " << dp[0][size - 1] << " and the subsequence is: " << result << endl;
}
int matrix_knights[M][CHESSBOARD_SIZE][CHESSBOARD_SIZE];
int matrix_king [CHESSBOARD_SIZE][CHESSBOARD_SIZE];
bool isSafePosition (int x, int y)
{
	return (x >= 0) && (x < CHESSBOARD_SIZE) &&
			(y >= 0) && (y < CHESSBOARD_SIZE);
}
void bfsForKnight (int x, int y, int I)
{
	int rowNbr[] = {-2, -1, 1, 2, -2, -1, 1, 2};
	int colNbr[] = {-1, -2, -2, -1, 1, 2, 2, 1};
	queue<pair<int, int> > Q;
	Q.push (make_pair (x, y));
	matrix_knights[I][x][y] = 0;
	
	while (!Q.empty())
	{
		pair<int, int> p = Q.front ();
		Q.pop ();
		x = p.first;
		y = p.second;
		for (int i = 0; i < 8; i++)
		{
			if (isSafePosition (x + rowNbr[i], y + colNbr[i]) && matrix_knights[I][x][y] != -1)
			{
				matrix_knights[I][x + rowNbr[i]][y + colNbr[i]] = matrix_knights[I][x][y] + 1;
				Q.push (make_pair (x + rowNbr[i], y + colNbr[i]));
			}
		}
	}
	
}
void bfsForKing (int x, int y)
{
	int rowNbr[] = {-1, 0, 1, 1, 1, 0, -1, -1};
	int colNbr[] = {-1, -1, -1, 0, 1, 1, 1, 0};
	queue<pair<int, int> > Q;
	Q.push (make_pair (x, y));
	matrix_king[x][y] = 0;
	
	while (!Q.empty())
	{
		pair<int, int> p = Q.front ();
		Q.pop ();
		x = p.first;
		y = p.second;
		for (int i = 0; i < 8; i++)
		{
			if (isSafePosition (x + rowNbr[i], y + colNbr[i]) && matrix_king[x][y] != -1)
			{
				matrix_king[x + rowNbr[i]][y + colNbr[i]] = matrix_king[x][y] + 1;
				Q.push (make_pair (x + rowNbr[i], y + colNbr[i]));
			}
		}
	}
}
int minMoves (int knights_x[], int knights_y[], int king_x, int king_y, int MKnights)
{
	memset (matrix_knights, -1, sizeof(matrix_knights));
	memset (matrix_king, -1, sizeof(matrix_king));
	for (int i = 0; i < MKnights; i++)
	{
	
		bfsForKnight (knights_x[i], knights_y[i], i);
	}
	bfsForKing (king_x, king_y);
	
	for (int k = 1; k < MKnights; k++)
	{
		for (int i = 0; i < CHESSBOARD_SIZE; i++)
		{
			for (int j = 0; j < CHESSBOARD_SIZE; j++)
			{
				matrix_knights[0][i][j] += matrix_knights[k][i][j];
			}
		}
	}

	int result_min = INT_MAX;
	for (int i = 0; i < CHESSBOARD_SIZE; i++)
	{
		for (int j = 0; j < CHESSBOARD_SIZE; j++)
		{
			matrix_knights[0][i][j] += matrix_king[i][j];
			if (result_min > matrix_knights[0][i][j])
			{
				result_min = matrix_knights[0][i][j];
			}
		}
	}
	
	return result_min;
}
int main ()
{
	// boggle backtracking
	char boggle[M][N] = {{'G','I','Z'},
                         {'U','E','K'},
                         {'Q','S','E'}};
 
    cout << "Following words of dictionary are present\n";
    findWords(boggle);
	
	// merging k sorted arrays
	vector<vector<int> > arr{ { 2, 6, 12 },
                              { 1, 9 },
                              { 23, 34, 90, 2000 } };
 
    vector<int> output = mergeKArrays(arr);
 
    cout << "Merged array is " << endl;
    for (auto x : output)
        cout << x << " ";
	cout << endl;
	
	// find maximum in an array which is first increasing then decreasing
	//int arr1[] = {1, 3, 50, 10, 9, 7, 6}; 
	int arr1[] = {2,2,2,2,1};
	int n1 = sizeof(arr1)/sizeof(arr1[0]); 
	printf("The maximum element is %d\n", findMaximum(arr1, 0, n1-1)); 
	
	// search an element in a sorted and rotated array
	int arr2[] = {4, 5, 6, 7, 8, 9, 1, 2, 3};
    int n2 = sizeof(arr2)/sizeof(arr[0]);
    int key = 6;
    int i = search(arr2, 0, n2-1, key);
 
    if (i != -1)
    cout << "Index: " << i << endl;
    else
    cout << "Key not found" << endl;

	// max circular subarray sum
	int arr3[] =  {11, 10, -20, 5, -3, -5, 8, -13, 10};
    int n3 = sizeof(arr3)/sizeof(arr3[0]);
    printf("Maximum circular sum is %d\n",
                              maxCircularSum(arr3, n3));
							  
	// find max repeating number in O(n) time and O(1) space
	int arr4[] = {2, 3, 3, 5, 3, 4, 1, 7};
    int n4 = sizeof(arr4)/sizeof(arr4[0]);
    int k1 = 8;
 
    cout << "The maximum repeating number is " <<
         maxRepeating(arr4, n4, k1) << endl;
		 
	// max rectangular sum in a 2D matrix
	int arr5[ROW][COL] = {{1, 2, -1, -4, -20}, 
                       {-8, -3, 4, 2, 1}, 
                       {3, 8, 10, 1, 3}, 
                       {-4, -1, 1, 7, -6} 
                      }; 
  
    findMaxSum(arr5);
	
	// max size rectangular binary submatrix with all 1s
	int arr6[][ROW] = { {0, 1, 1, 0},
						   {1, 1, 1, 1},  // 1 2 2 1
						   {1, 1, 1, 1},  // 2 3 3 2
						   {1, 1, 0, 0},  // 3 4 0 0
					};
 
    cout << "Area of maximum rectangle is "
         << maxRectangle(arr6) << endl;
		 
	// gold mine problem
	int gold[][ROW]= { {1, 3, 1, 5}, 
							{2, 2, 4, 1}, 
							{5, 0, 2, 3}, 
							{0, 6, 1, 2} 
						}; 
    cout << "Max gold accumulated: " << getMaxGold(gold, ROW, ROW) << endl; 
	
	// print matrix in spiral form
	int arr7[ROW][ROW + 1] = { {1,  2,  3, 4, 17}, 
			{5, 6, 7, 8, 18}, 
			{9, 10, 11, 12, 19},
			{13, 14, 15, 16, 20}
			}; 
  
    spiralPrint (arr7, ROW, ROW + 1); 
	
	// alternate -ve and +ve numbers with maintaining order
	int arr8[] = {-5, -2, 5, 2, 4, 7, 1, 8, 0, -8}; 
    int n8 = sizeof(arr8)/sizeof(arr8[0]);   
    rearrange(arr8, n8); 
	
	// Kth non-repeating char
	string str = "geeksforgeeks"; 
    int k = 3; 
    int res = kthNonRepeating(str, k); 
    (res == -1)? cout << "There are less than k non-"
                        "repeating characters"
              : cout << "k'th non-repeating character"
                       " is  "<< str[res]; 		
	// Print all subsequences
	string str2 = "abc";
	allSubseq (str2);
	
	// Print anagrams together
	vector<string> arr9; 
    arr9.push_back("geeksquiz"); 
    arr9.push_back("geeksforgeeks"); 
    arr9.push_back("abcd"); 
    arr9.push_back("forgeeksgeeks"); 
    arr9.push_back("zuiqkeegs"); 
    arr9.push_back("cat"); 
    arr9.push_back("act"); 
    arr9.push_back("tca");
	cout << "The anagrams are the following: " << endl;
    storeInMap(arr9);
	
	// Reverse words in a string
	char str3[] = "I like this program very much";
	reverseWords (str3);
	
	// Max window without repeating char
	char str4[] = "ABDEFGABEF"; 
    printf("The input string is %s: ", str4); 
    int len =  longestUniqueSubsttr(str4); 
    printf("\nThe length of the longest non-repeating "
           "character substring is %d\n", len);
	
	// lexicographic rank of a string
	
	// print string and length of longest palindromic subsequences
	string str5 = "AXBYAC";
	lps (str5);
	// min no of partitions to form a palindrome
	
	// median in a stream of integers
	vector<float> arr10;
	arr10.push_back(5); arr10.push_back(15); arr10.push_back(10); arr10.push_back(20); arr10.push_back(3);
	printMedians (arr10);
	
	// min moves to keep m knights and the king in the same location
	int knights_x[] = {2, 4, 6, 7};
	int knights_y[] = {1, 5, 3, 2};
	int m = sizeof (knights_x) / sizeof(knights_x[0]); 
	int king_x = 1;
	int king_y = 2;
	cout << "The min number of moves are: " << minMoves (knights_x, knights_y, king_x, king_y, m) << endl;
	
	return 0;
}