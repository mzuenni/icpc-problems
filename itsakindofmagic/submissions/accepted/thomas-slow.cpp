/**
 * Author: Thomas Beuman
 *
 * All solutions have the following form:
 *
 * ( kaacd  kbbdd  kabcc )
 * ( kbbcc  kabcd  kaadd )
 * ( kabdd  kaacc  kbbcd )
 *
 * where:
 * - a and b are coprime and not both 1
 * - c and d are coprime and not both 1
 * - {a,b} and {c,d} are not the same
 * - {a^2,b^2} != {c,d}
 * - {a,b} != {c^2,d^2}
 * - kabcd <= n^(1/3)
 *
 * First, for all m, count all magic squares with k = 1 and abcd = m.
 * Then, use these to count all squares with kabcd = m.
 * Finally, sum these together to count all squares with kabcd <= m.
 *
 * Method for step 1:
 * Loop over all values of a, b, c and d with a<b, c<d and a<c,
 *   checking that (a,b) and (c,d) are coprime.
 *
 * Time: O(n^(1/3) (log n)^3) ?
 * Memory: O(n^(1/3))
 */

#include <cmath>
#include <cstdio>
#include <cstring>
using namespace std;

const int CUBIC_ROOT_NMAX = 1000000;

const long double eps = 1e-3; // long double required, cbrt of double not accurate enough
const int M = CUBIC_ROOT_NMAX;

int PSC[M+1]; // Primitive square count
int TSC[M+1]; // Total square count
long long CSC[M+1]; // Cumulative square count

int gcd (int a, int b)
{
	return b ? gcd(b, a%b) : a;
}

int main()
{
	memset(PSC, 0, sizeof(PSC));
	for (int a = 1; a*a*a*a <= M; a++)
		for (int b = a+1; a*b*a*a <= M; b++)
			if (gcd(a,b) == 1)
				for (int c = a; a*b*c*c <= M; c++)
					for (int d = c+1; a*b*c*d <= M; d++)
						if (gcd(c,d) == 1) {
							if ((a < c || b < d) && a*a*d != b*b*c)
								PSC[a*b*c*d] += 8;
						}

	// Count non-primitive squares
	memset(TSC, 0, sizeof(TSC));
	for (int k = 1; k <= M; k++)
		for (int m = 1; k*m <= M; m++)
			TSC[k*m] += PSC[m];
	// Accumulate
	CSC[0] = 0;
	for (int m = 1; m <= M; m++)
		CSC[m] = CSC[m-1] + TSC[m];

	// Process queries
	int t;
	scanf("%d", &t);
	for (int i = 0; i < t; i++) {
		long long n;
		scanf("%lld", &n);
		int m = cbrt(n+eps);
		printf("%lld\n", CSC[m]);
	}
	return 0;
}
