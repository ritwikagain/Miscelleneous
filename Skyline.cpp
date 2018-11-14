#include <bits/stdc++.h>

using namespace std;

struct BuildingPoint
{
	int x;
	bool isStart;
	int height;
};
int compare (BuildingPoint b1, BuildingPoint b2)
{
	if (b1.x != b2.x)
	{
		return b1.x < b2.x;
	}
	else
	{
		if (b1.isStart == b2.isStart)
		{
			return b1.height < b2.height;
		}
		else if (b1.isStart == true)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
}
vector<pair<int, int>> getSkyline (int buildings[][3], int m, int n)
{
	vector<BuildingPoint> buildingPoints(m * 2);
	
	int index = 0;
	for (int i = 0; i < m; i++)
	{
		buildingPoints[index].x =  buildings[i][0]; 
		buildingPoints[index].isStart = true;
		buildingPoints[index].height = buildings[i][2];
		
		index += 1;
		
		buildingPoints[index].x =  buildings[i][1]; 
		buildingPoints[index].isStart = false;
		buildingPoints[index].height = buildings[i][2];
		
		index += 1;
	}
	
	sort (buildingPoints.begin(), buildingPoints.end(), compare);
	
	map<int, int> mymap;             // map<height,count> which is a balanced BST of <height,count> of y values
	mymap.insert (make_pair(0, 1));  // height 0, count 1
	int prevMaxHeight = 0;
	vector<pair<int, int>> result;
	
	for (int i = 0; i < 2 * m; i++)
	{
		map<int, int>:: iterator it;
		if (buildingPoints[i].isStart)
		{
			it = mymap.find(buildingPoints[i].height);
			if (it != mymap.end())
			{
				it->second++;
			}
			else
			{
				mymap.insert (make_pair(buildingPoints[i].height, 1));
			}
		}
		else
		{
			it = mymap.find(buildingPoints[i].height);
			if (it != mymap.end())
			{
				if (it->second == 1)
				{
					mymap.erase (it);
				}
				else
				{
					it->second--;
				}
			}
		}
		
		int currentMaxHeight = mymap.rbegin()->first;   // the largest value is at the right end of the balanced BST
		if (prevMaxHeight != currentMaxHeight)
		{
			result.push_back(make_pair(buildingPoints[i].x, currentMaxHeight));  // This point is critical because the point has changed the largest value in the BST. Now it can be either
			prevMaxHeight = currentMaxHeight;									// either an incoming or outgoing edge. If it is incoming, it's height must be the largest one. If it's outgoing,			
		}																		// must be the previous largest one.
	}
	
	return result;
}
int main ()
{
	int buildings[6][3] = {
		{1,3,4},
		{3,4,4},
		{2,6,2},
		{8,11,4},
		{7,9,3},
		{10,11,12}
	};
	
	vector<pair<int, int>> v = getSkyline (buildings, 6, 3);
	for (int i = 0; i < v.size(); i++)
	{
		cout << v[i].first << " " << v[i].second << endl;
	}
	return 0;
}