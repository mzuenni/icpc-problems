/**
 * Author: Thomas Beuman
 *
 * Group the levels into groups of sqrt(n).
 * For each group, store the largest capacity and the largest not-full level
 *   and update the latter upon each complete fill.
 * Filling up a level and finding the next one can then be done in O(sqrt n).
 *
 * Time: O(n sqrt n)
 */

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
using namespace std;

const int NMAX = 300000;
const int M = 600; // > sqrt(NMAX)

int n, m; // m = group size

int Capacity[NMAX];
int Amount[NMAX];

int MaxCapacity[M]; // Maximum capacity of all levels in this group
int MaxUnfilled[M]; // Capacity of largest not-full level
                    // (not shielded by larger level in this group)

void update_unfilled (int k)
{
	int maxUnfilled = 0;
	int maxCapacity = 0;
	for (int i = k*m; i < (k+1)*m && i < n; i++) {
		int cap = Capacity[i];
		if (cap > maxCapacity && Amount[i] < cap)
			maxUnfilled = max(maxUnfilled, cap);
		maxCapacity = max(maxCapacity, cap);
	}
	MaxUnfilled[k] = maxUnfilled;
}

// Find the next level that will collect overflow
int getnext (int i)
{
	int k = i/m;
	int capacity = Capacity[i];
	// Check the remaining levels in this group
	for (i++; i < (k+1)*m && i < n; i++) {
		int cap = Capacity[i];
		if (cap > capacity && Amount[i] < cap)
			return i;
		capacity = max(capacity, cap);
	}
	// Check the remaining groups
	for (k++; k*m < n; k++) {
		if (MaxUnfilled[k] > capacity)
			break;
		capacity = max(capacity, MaxCapacity[k]);
	}
	if (k*m >= n)
		return -1;
	// There is an unfilled level with enough capacity in this group;
	// Find the first such level
	for (i = k*m; true; i++) {
		int cap = Capacity[i];
		if (cap > capacity && Amount[i] < cap)
			return i;
		capacity = max(capacity, cap);
	}
}

int main()
{
	int q;
	scanf("%d %d", &n, &q);
	for (int i = 0; i < n; i++)
		scanf("%d ", &Capacity[i]);

	m = sqrt(n);
	memset(Amount, 0, sizeof(Amount));
	for (int i = 0; i < n; i++)
		MaxCapacity[i/m] = max(MaxCapacity[i/m], Capacity[i]);
	for (int k = 0; k*m < n; k++)
		MaxUnfilled[k] = MaxCapacity[k];

	for (int j = 0; j < q; j++) {
		char t;
		scanf("%c", &t);
		if (t == '+') {
			int i, x;
			scanf("%d %d ", &i, &x);
			i--;
			while (i >= 0 && Amount[i] + x >= Capacity[i]) {
				// Fill up level and go to next level
				x -= Capacity[i] - Amount[i];
				Amount[i] = Capacity[i];
				update_unfilled(i/m);
				i = getnext(i);
			}
			if (i >= 0)
				Amount[i] += x;
		}
		else {
			int i;
			scanf("%d ", &i);
			i--;
			printf("%d\n", Amount[i]);
		}
	}
	return 0;
}
