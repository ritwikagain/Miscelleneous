#include <bits/stdc++.h>

using namespace std;

struct Node 
{
	int data;
	int height;
	Node *left;
	Node *right;
};

Node *newNode (int value)
{
	Node *newNode = (Node *)malloc(sizeof(Node));
	newNode->data = value;
	newNode->height = 1;
	newNode->left = newNode->right = NULL;
	return newNode;
}
bool is_leaf (Node *root)
{
	return root && root->left ==  NULL && root->right == NULL;
}
int height (Node * root)
{
	if (root == NULL)
		return 0;
	return root->height;
}
int get_balance (Node * root)
{
	if (root == NULL || is_leaf (root))
		return 0;
	return height (root->left) - height (root->right);
}

Node *leftRotate (Node * root)
{
	cout << "\t\tInside leftRotate" << endl;
	Node *x = root->right;
	root->right = x->left;
	x->left = root;
	x->height = max (height (x->left), height (x->right)) + 1;
	root->height = max (height (root->left), height (root->right)) + 1;
	return x;
}

Node *rightRotate (Node * root)
{
	cout << "\t\tInside righttRotate" << endl;
	Node *y = root->left;
	root->left = y->right;
	y->right = root;
	y->height = max (height (y->left), height (y->right)) + 1;
	root->height = max (height (root->left), height (root->right)) + 1;
	return y;
}
Node *make_balance (Node * root)
{
	cout << "\tInside make_balance" << endl;
	int diff = get_balance (root);
	if (diff > 1)
	{
		if (get_balance (root->left) > 0) // L - L
		{
			root = rightRotate (root);
		}
		else // L - R
		{
			root->left = leftRotate (root->left);
			root = rightRotate (root);
		}
	}
	else if (diff < -1)
	{
		if (get_balance (root->right) < 0) // R - R
		{
			root = leftRotate (root);
		}
		else // R - L
		{
			root->right = rightRotate (root->right);
			root = leftRotate (root);
		}
	}
	
	return root;
}

Node *insert (Node *root, int value)
{
	cout << "Inserting: " << value << endl;
	if (root == NULL)
		return newNode (value);
	if (root->data > value)
		root->left = insert (root->left, value);
	else if (root->data == value)
		cout << "The value already exists." << endl;
	else 
		root->right = insert (root->right, value);
	
	root->height = max (height(root->left), height(root->right)) + 1;
	
	return make_balance (root);
}

bool search (Node *root, int value)
{
	if (root == NULL)
		return false;
	if (root->data > value)
		return search (root->left, value);
	else if (root->data == value)
		return true;
	else
		return search (root->right, value);
}

Node *find_min (Node *root)
{
	while (root->left)
		root = root->left;
	return root;
}
Node *deleteNode (Node *root, int value)
{
	cout << "Deleting: " << value << endl;
	if (root == NULL)
	{
		cout << "The data doesn't reside in tree!" << endl;
		return NULL;
	}
	
	if (root->data > value)
		root->left = deleteNode (root->left, value);
	else if (root->data < value)
		root->right = deleteNode (root->right, value);
	else
	{
		if (root->left && root->right)
		{
			Node * succ = find_min (root->right);
			root->data = succ->data;
			return deleteNode (succ, succ->data);
		}
		else if (root->left)
			root = root->left;
		else
			root = root->right;
	}
	
	return make_balance (root);
		
}

void inorder (Node * root)
{
	if (root)
	{
		inorder (root->left);
		cout << root->data << " ";
		inorder (root->right);
	}
}
int main ()
{
	Node *root = NULL;

	root = insert(root, 10);
	root = insert(root, 20);
	root = insert(root, 30);
	root = insert(root, 40);
	root = insert(root, 50);
	root = insert(root, 25);

	inorder(root);
	printf("\n");

	root = deleteNode(root, 40);
	root = deleteNode(root, 50);
	inorder(root);
	printf("\n");
	return 0;
}