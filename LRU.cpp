#include <bits/stdc++.h>

using namespace std;

class LRUCache
{
	private:
		list<int> l;
		map<int, list<int>::iterator> m;
		int csize;
		int curr_size;
	public:
		LRUCache(int size)
		{
			csize = size;
			curr_size = 0;
		}
		
		bool retrieve (int value)
		{
			map<int, list<int>::iterator>::iterator it = m.find(value);
			if (it != m.end()) // found
			{
				l.erase(it->second);
				l.push_front(value);
				m[value] = l.begin();
				return true;
			}
			else // not found
			{
				if (curr_size < csize) // not full
				{
					l.push_front(value);
					m[value] = l.begin();
					curr_size++;
					return false;
				}
				else // full
				{
					list<int>::iterator i = l.end();
					m.erase(*i);
					l.pop_back();
					l.push_front(value);
					m[value] = l.begin();
					return false;
				}
			}
		}
		
		void display()
		{
			for (list<int>::iterator i = l.begin(); i != l.end(); i++)
			{
				cout << *i << " ";
			}
			cout << endl;
		}
};
int main ()
{
	LRUCache LR (3);
	cout << LR.retrieve (1) << " ";
	cout << endl;
	LR.display ();
	cout << LR.retrieve (2) << " ";
	cout << endl;
	LR.display ();
	cout << LR.retrieve (1) << " ";
	cout << endl;
	LR.display ();
	cout << LR.retrieve (3) << " ";
	cout << endl;
	LR.display ();
	cout << LR.retrieve (1) << " ";
	cout << endl;
	LR.display ();
	cout << LR.retrieve (4) << " ";
	cout << endl;
	LR.display ();
	cout << LR.retrieve (5) << " ";
	cout << endl;
	LR.display ();
	return 0;
}