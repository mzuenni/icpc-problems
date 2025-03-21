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
 * Loop over all values of a*b and c*d
 * The number of coprime pairs (a,b) that multiply to a*b is 2^k
 *   where k is the number of distinct prime factors of a*b.
 * Subtract the ones with the disallowed relations between {a,b} and {c,d}.
 *
 * Time: O(n^(1/3) log n)
 * Memory: O(n^(1/3))
 */

#include <cmath>
#include <cstdio>
#include <cstring>
using namespace std;

const int CUBIC_ROOT_NMAX = 1000000;

const long double eps = 1e-3; // long double required, cbrt of double not accurate enough
const int M = CUBIC_ROOT_NMAX;

int SPF[M+1]; // Smallest prime factor
int CFC[M+1]; // Coprime factorization count

int PSC[M+1]; // Primitive square count
int TSC[M+1]; // Total square count
long long CSC[M+1]; // Cumulative square count

int main()
{
	// Prime sieve
	memset(SPF, 0, sizeof(SPF));
	for (int p = 2; p*p <= M; p++)
		if (SPF[p] == 0)
			for (int q = p*p; q <= M; q += p)
				if (SPF[q] == 0)
					SPF[q] = p;
	for (int p = 1; p <= M; p++)
		if (SPF[p] == 0)
			SPF[p] = p;
	// Coprime factorizations
	CFC[1] = 1;
	for (int m = 2; m <= M; m++) {
		int p = SPF[m];
		CFC[m] = CFC[m/p] * (m % (p*p) == 0 ? 1 : 2);
	}

	// Count all squares with k = 1 and coprime restrictions
	memset(PSC, 0, sizeof(PSC));
	for (int ab = 2; ab*2 <= M; ab++)
		for (int cd = 2; ab*cd <= M; cd++)
			PSC[ab*cd] += CFC[ab] * CFC[cd];
	// Subtract squares with {a,b} = {c,d}
	for (int ab = 2; ab*ab <= M; ab++)
		PSC[ab*ab] -= 2*CFC[ab];
	// Subtract squares with {a^2,b^2} = {c,d} or {a,b} = {c^2,d^2}
	for (int ab = 2; ab*ab*ab <= M; ab++)
		PSC[ab*ab*ab] -= 4*CFC[ab];

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
