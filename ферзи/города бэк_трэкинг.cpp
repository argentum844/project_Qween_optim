#include <iostream>
#include <set>
#include <vector>
static const int maxN = 10;
typedef bool TMatr[maxN][maxN];
typedef std::set<int> TSet;
typedef std::vector<int> TPath;

TMatr roads;
int a, b;
TPath p;
int len;
TPath POpt;
int lenOpt;

bool findPath(int t, TSet& visited)
{
	if (t == b)
		return true;
	int i = 0;
	bool result = false;
	while ((i < maxN) && !result)
	{
		if (roads[t][i] && visited.find(i) == visited.end())
		{
			len++;
			p[len] = i;
			visited.insert(i);
			result = findPath(i, visited);
			if (!result)
			{
				visited.erase(i);
				len--;
				i++;
			}
		}
		else i++;
	}
	return result;
}

bool mainFind()//поиск первого пути
{
	TSet v;
	len = 0;
	p[len] = a;
	v.insert(a);
	return findPath(a, v);
}

void printPath(TPath p, int len)
{
	for (int i = 0; i < len; i++)
		std::cout << p[i] << " ";
}

//поиск всех путей
void findAllPath(int t, TSet& visited)
{
	for (int k = 0; k < maxN; k++)
	{
		if (roads[t][k] && visited.find(k) == visited.end())
		{
			len++;
			p[len] = k;
			visited.insert(k);
			if (k != b)
				findAllPath(k, visited);
			else
				printPath(p, len);
			visited.erase(k);
			len--;
		}
	}
}

void mainAllPath()
{
	TSet v;
	len = 0;
	p[len] = a;
	v.insert(a);
	findAllPath(a, v);
}

//поиск оптимального решения
void findShortPath(int from, int to, TSet& visited)
{
	if (roads[from][to] && visited.find(to) == visited.end())
	{
		len++;
		p[len] = to;
		visited.insert(to);
		if (to != b)
			findShortPath(to, 0, visited);
		else
		{
			if (len < lenOpt)
			{
				lenOpt = len;
				POpt = p;
			}
		}
		visited.erase(to);
		len--;
	}
	if (to < maxN - 1)
		findShortPath(from, to + 1, visited);
}

void mainShortPath()
{
	TSet v;
	len = 0;
	p[len] = a;
	lenOpt = maxN;
	v.insert(a);
	findShortPath(a, 0, v);
}

//ДЗ для текста абс прикрутить эту схему