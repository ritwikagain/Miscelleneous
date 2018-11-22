#include <bits/stdc++.h>
using namespace std;

#define MAX_CHAR 26

struct Trie
{
	bool isLeaf;
	struct Trie *child[MAX_CHAR];
	vector<int> index;
};
Trie * newNode()
{
	Trie * node = new Trie;
	node->isLeaf = false;
	for (int i = 0; i < MAX_CHAR; i++)
	{
		node->child[i] = nullptr;
	}
	return node;
}
void insert (Trie *node, string buffer, int index)
{
	int size = buffer.size();
	for (int i = 0; i < size; i++)
	{
		if (node->child[buffer[i] - 'a'] == nullptr)
		{
			node->child[buffer[i] - 'a'] = newNode();
		}
		
		node = node->child[buffer[i] - 'a'];
	}
	node->isLeaf = true;
    (node->index).push_back(index);
}
void traverse (string wordArr[], Trie *node)
{
	if (node == nullptr) return;
	if (node->isLeaf)
	{
		int size = (node->index).size();
		for (int i = 0; i < size; i++)
		{
			cout << wordArr[node->index[i]] << endl;
		}
	}
	for (int i = 0; i < MAX_CHAR; i++)
	{
		if (node->child[i])
		{
			traverse (wordArr, node->child[i]);
		}
	}
}
void printAnagramsTogether(string wordArr[], int size)
{
	Trie *node = newNode();
	for (int i = 0; i < size; i++)
	{
		string buffer = wordArr[i];
		sort(buffer.begin(), buffer.end());
		insert (node, buffer, i);
	}
	
	traverse (wordArr, node);
}
int main()
{
    string wordArr[] = {"cat", "dog", "tac", "god", "act", "gdo"};
	int size = sizeof(wordArr)/sizeof(wordArr[0]);
    printAnagramsTogether(wordArr, size);
    return 0;
}