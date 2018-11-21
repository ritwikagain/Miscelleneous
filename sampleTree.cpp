#include <bits/stdc++.h>
using namespace std;

#define V 4
#define MARKER '#'
#define MAX_VAL 100
#define MAX_ALPHABET 26

class TrieNode;
class BBSTNode
{
	public:
	int w_count;
	string word;
	TrieNode * trienode;
	
	BBSTNode (TrieNode * trienode, int w_count, string word)
	{
		this->trienode = NULL;
		this->w_count = 0;
		this->word = "";
	}
	
	bool operator < (const BBSTNode& bs) const
	{
		return this->w_count < bs.w_count;
	}
};
class TrieNode
{
	public:
	bool isLeaf;
	int w_count;
	set<BBSTNode>::iterator it;
	TrieNode *children [MAX_ALPHABET];

	TrieNode (multiset<BBSTNode> ms)
	{
		isLeaf = false;
		w_count = 0;
		it = ms.end();
		for (int i = 0; i < MAX_ALPHABET; i++)
			children[i] = nullptr;
	}
};

void insertInTrie (string s, TrieNode *root, multiset<BBSTNode>& ms, int K)
{
	// Trie insert
	int size = s.size();
	for (int i = 0; i < size; i++)
	{
		if (!root->children[s[i] - 'a'])
			root->children[s[i] - 'a'] = new TrieNode(ms);
		root = root->children[s[i] - 'a'];
	}
	if (!root->isLeaf)
	{
		root->isLeaf = true;
		root->w_count = 1;	
		if (ms.size() < K)
		{
			BBSTNode bs(root, 1, s);
			root->it = ms.insert(bs);
		}
	}
	else
	{
		root->w_count++;
		cout << root->w_count << endl;
		BBSTNode bs(root, root->w_count, s);		
		set<BBSTNode>::iterator it = ms.find(*(root->it));
		if (it != ms.end())   // the word already exists in trie
		{	
			ms.erase(it);
			root->it = ms.insert(bs);
		}
		else  // the word doesn't exist in trie
		{
			if (ms.size() < K)  // and BBST size < K, just insert
			{
				root->it = ms.insert(bs);
			}
			else // BBST size = k
			{
				if (bs.w_count > (ms.begin())->w_count)
				{
					ms.erase (ms.begin());
					root->it = ms.insert(bs);
				}
			}
		}
	}
}
void traverseTrie (TrieNode *root, string buffer)
{
	if (!root) return;
	if (root->isLeaf) 
	{
		cout << buffer << endl;
	}
	
	for (int i = 0; i < MAX_ALPHABET; i++)
	{
		if (root->children[i])
		{
			buffer += i + 'a';
			traverseTrie (root->children[i], buffer);
		}
	}
}
void kMaxFreq (ifstream& fp, int K)
{
	string buffer;
	multiset<BBSTNode> ms;
	TrieNode *root = new TrieNode (ms);
	
	while (getline(fp, buffer))
	{
		//cout << buffer << endl;
		istringstream iss(buffer);
		do
		{
			string word;
			iss >> word;
			//cout << word << endl;
			insertInTrie (word, root, ms, K);
		} while (iss);
	}
	
	buffer = "";
	traverseTrie (root, buffer);
	
	for (multiset<BBSTNode>::iterator it = ms.begin(); it != ms.end(); it++)
	{
		cout << (*it).word << " " << (*it).w_count << endl;
	}
}

/*Tree * removeNodes(Tree *root, int sum, int K)
{
	if (root)
	{
		sum += root->data;
		root->left = removeNodes(root->left, sum, K);
		root->right = removeNodes(root->right, sum, K);
		if(!root->left && !root->right)
		{
			if (sum >= K)
			{
				free(root);
				return NULL;
			}
		}
		
		return root;
	
	}
	else
	{
		return NULL;
	}
}

void findSum(Tree *root, int *maxsum, int sum)
{
	if (root)
	{
		sum = (sum)*10 + root->data;
		
		if (root->left == NULL && root->right == NULL)
		{
			*maxsum += sum;
		}
		
		findSum(root->left, maxsum, sum);
		findSum(root->right, maxsum, sum);
	}
}
void inorder_read(Tree *root, int *aux, int *index, int level)
{
	if (root)
	{
		inorder_read(root->left, aux, index, 1 - level);
		if (level == 1)
		{
			aux[*index] = root->data;
			(*index)++;
		}
		inorder_read(root->right, aux, index, 1 - level);
	}
}

void inorder_write(Tree *root, int *aux, int *index, int level)
{
	if (root)
	{
		inorder_write(root->left, aux, index, 1 - level);
		if (level == 1 && index >= 0)
		{
			root->data = aux[*index];
			(*index)--;
		}
		inorder_write(root->right, aux, index, 1 - level);
	}
}
void changealternatenodeBT(Tree *root)
{
	int count = 0, level = 0, index = 0;
	printf("\n");
	inorder(root);
	
	countNodesInBT(root, &count);
	int *aux = new int [count];
	for (int i = 0; i < count; i++)
	{
		aux[i] = 0;
	}
	
	inorder_read(root, aux, &index, level);
	
	level = 0;
	index--;
	inorder_write(root, aux, &index, level);
	printf("\n");
	inorder(root);
}

void iterativePostOrder (Tree *root)
{
	stack<Tree *> s;
	if (root == NULL) return;

	do
	{
		while (root)
		{
			if (root->right)
			{
				s.push(root->right);
			}
			s.push(root);
			root = root->left;
		}
		
		Tree *temp = s.top();
		s.pop();
		if (!s.empty() && temp->right == s.top())
		{
			s.pop();
			s.push(temp);
			root = temp->right;
		}
		else
		{
			cout << temp->data << " ";
			root = NULL;
		}
	} while (!s.empty());
}

bool printPath (Tree *root, Tree *targetLeaf)
{
	if (root == NULL) return false;
	if ((root == targetLeaf) || printPath(root->left, targetLeaf) || printPath(root->right, targetLeaf))
	{
		cout << root->data << " ";
		return true;
	}
	return false;
}
void maxSumRootToLeafPath (Tree *root, int sum, int *maxsum, Tree **targetLeaf)
{
	if (root == NULL) return;
	
	sum += root->data;
	
	if (!root->left && !root->right)
	{
		if (*maxsum < sum)
		{
			*maxsum = sum;
			*targetLeaf = root;
		}
	}
	
	maxSumRootToLeafPath (root->left, sum, maxsum, targetLeaf);
	maxSumRootToLeafPath (root->right, sum, maxsum, targetLeaf);
}

void pairWithSum (Tree *root, int target)
{
	int val1, val2;
	bool is_done1, is_done2;
	Tree * head1;
	Tree * head2;
	Tree * temp1;
	Tree * temp2;
	stack<Tree *> in1;
	stack<Tree *> in2;
	
	val1 = INT_MIN;
	val2 = INT_MAX;
	
	is_done1 = is_done2 = false;
	
	head1 = head2 = root;
	
	if (root == NULL) return;
	
	while (val1 < val2)
	{
		if (!is_done1)
		{
			while (head1)
			{
				in1.push(head1);
				head1 = head1->left;
			}
			
			if (in1.size()> 0)
			{
				temp1 = in1.top();
				in1.pop();
				val1 = temp1->data;
				is_done1 = true;
				
				if (temp1->right)
				{
					head1 = temp1->right;
				}
			}	
		}
	
		if (!is_done2)
		{
			//if (head2)
			//	cout << "\nhead2->data: " << head2->data << endl;
		    while (head2)
			{
				in2.push(head2);
				head2 = head2->right;
			}
			
			if (in2.size() > 0)
			{
				temp2 = in2.top();
				in2.pop();
				val2 = temp2->data;
				//cout << "temp2->data: " << temp2->data << endl;
				is_done2 = true;
				
				if (temp2->left)
				{
					head2 = temp2->left;
				}
			}
		}
	
		//cout << "\nval1: " << val1 << " val2: " << val2 << endl;
		if (val1 != INT_MIN && val2 != INT_MAX)
		{
			if (val1 + val2 == target)
			{
				cout << "\nThe values are: " << val1 << " " << val2 << endl;
				is_done1 = false;
				is_done2 = false;
			}
			else if (val1 + val2 > target)
			{
				is_done2 = false;
			}
			else
			{
				is_done1 = false;
			}
		}
		else
		{
			return;
		}
	}
}

int maxPathSumBetweenTwoLeaves (Tree *root, int *res)
{
	int ls = 0, rs = 0;
	
	if (root == NULL) return 0;
	if (!root->left && !root->right)
	{
		return root->data;
	}
	
	if (root->left)
	{
		ls = maxPathSumBetweenTwoLeaves (root->left, res);
	}
	
	if (root->right)
	{
		rs = maxPathSumBetweenTwoLeaves (root->right, res);
	}
	
	if (ls && rs)
	{
		*res = max (*res, ls + rs + root->data);
		return max(ls, rs) + root->data;
	}
	
	if (ls)
	{
		return ls + root->data;
	}
	else
	{
		return rs + root->data;
	}
	
}

int maxPathSum (Tree *root, int *res)
{
	int ls = 0, rs = 0;
	
	if (root == NULL) return 0;
	

	ls = maxPathSum (root->left, res);
	rs = maxPathSum (root->right, res);

	int max_single = max (root->data, max(ls,rs) + root->data);
	int max_top = max (max_single, ls + rs + root->data);
	//cout << "Current node: " << root->data << " max_single: " << max_single << " max_top: " << max_top << endl;
	*res = max (*res, max_top);
	
	return max_single;
}

// to determine if a binary tree is height balanced
int height (Tree * root)
{
	if (root == NULL)
	{
		return 0;
	}
	
	int l = height (root->left);
	int r = height (root->right);
	
	return max (l, r) + 1;
}
bool isBalanced (Tree *root)
{
	if (root == NULL)
	{
		return true;
	}
	
	int lh = height (root->left);
	int rh = height (root->right);
	
	return ((abs(lh-rh) <= 1) && isBalanced(root->left) && isBalanced(root->right));
}

// to serialize and a deserialize a binary tree
void serialize (Tree *root, int arr[], int *index)
{
	if (root == NULL)
	{
		arr[(*index)++] = MARKER;
		return;
	}
	
	arr[(*index)++] = root->data;
	serialize (root->left, arr, index);
	serialize (root->right, arr, index);
}
void deserialize (Tree **root, int arr[], int *index)
{
	if (arr[*index] == '\0')
	{
		return;
	}
	
	if (arr[*index] == '#')
	{
		(*index)++;
		return;
	}
	
	*root = newTreeNode(arr[(*index)++]);
	deserialize (&((*root)->left), arr, index);
	deserialize (&((*root)->right), arr, index);
}*/
//tranforming left-right binary tree to down-right binary tree

int main()
{	
	/*Tree * root = newTreeNode(1);
	root->left = newTreeNode(2);
	root->right = newTreeNode(3);
	root->left->left = newTreeNode(4);
	root->left->right = newTreeNode(5);
	root->right->left = newTreeNode(6);
	root->right->right = newTreeNode(7);
	root->left->left->left = newTreeNode(8);
	root->left->left->right = newTreeNode(9);
	root->left->right->left = newTreeNode(10);
	root->left->right->right = newTreeNode(11);
	root->right->left->left = newTreeNode(12);
	root->right->left->right = newTreeNode(13);
	root->right->right->left = newTreeNode(14);
	root->right->right->right = newTreeNode(15);
	
	//changealternatenodeBT(root);
	int maxsum = 0;
	//findSum(root, &maxsum, 0);
	printf("\nThe maximum sum is: %d\n", maxsum);
	inorder(root);
	printf("\n");
	//inorder(removeNodes(root, 0, 23));
	
	cout << "The result of iterative post order is: ";
	iterativePostOrder(root);
	cout << endl;
	
	Tree *targetLeaf = NULL;
	int sum = 0;
	maxsum = 0;
	maxSumRootToLeafPath (root, sum, &maxsum, &targetLeaf);
	cout << "The max sum of root to leaf path is: " << maxsum << endl;
	printPath (root, targetLeaf); cout << endl;

	int res = INT_MIN;
	maxPathSumBetweenTwoLeaves (root, &res);
	cout << "The max path sum between two leaves is: " << res << endl;
	
	Tree * root3 = newTreeNode(10);
	root3->left = newTreeNode(2);
	root3->right = newTreeNode(10);
	root3->left->left = newTreeNode(20);
	root3->left->right = newTreeNode(1);
	root3->right->right = newTreeNode(-25);
	root3->right->right->left = newTreeNode(3);
	root3->right->right->right = newTreeNode(4);
	res = INT_MIN;
	maxPathSum (root3, &res);
	cout << "The max path sum is: " << res << endl;	
	
	cout << "The balance status of the tree is: " << isBalanced(root3) << endl;
	
	int preorder_string [MAX_VAL];
	int index = 0;
	serialize (root3, preorder_string, &index);
	preorder_string[index] = '\0';
	cout << "The serialized array is: " << endl;
	for (int i = 0; i < index; i++)
	{
		cout << preorder_string[i] << " ";
	}
	Tree *root4 = NULL;
	index = 0;
	deserialize (&root4, preorder_string, &index);
	cout << "\nThe deserialized tree is: " << endl;
	preorder (root4);
	cout << endl;
	
	Tree * root2 = newTreeNode(15);
	root2->left = newTreeNode(10);
	root2->right = newTreeNode(20);
	root2->left->left = newTreeNode(8);
	root2->left->right = newTreeNode(12);
	root2->right->left = newTreeNode(16);
	root2->right->right = newTreeNode(25);
	int target = 20;
	pairWithSum(root2, target);*/
	
	
	ifstream fp ("file.txt");
	if (!fp.is_open())
	{
		cout << "Unable to open file." << endl;
	}
	else
	{
		kMaxFreq (fp, 4);
	}
	fp.close();
	
	
	return 0;
}