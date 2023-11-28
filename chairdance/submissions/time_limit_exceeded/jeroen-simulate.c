#include <stdio.h>
#include <stdlib.h>

#define MAXN 500000

int person[2][MAXN];
int dist[MAXN];

int main() {
  int n, q;
  scanf("%d %d\n", &n, &q);
  person[0][0] = n;
  for(int i = 1; i < n; i++)
    person[0][i] = i;

  int bit = 0;
  for(int qs = 0; qs < q; qs++) {
    char c; int x;
    scanf("%c %d\n", &c, &x);
    switch(c) {
    case '+':
      for(int i = 0; i < n; i++)
	person[1-bit][(i+x)%n] = person[bit][i];
      bit ^= 1;
      break;
    case '*':
      for(int i = 0; i < n; i++)
	person[1-bit][i] = dist[i] = -1;
      for(int i = 0; i < n; i++) {
	if(person[bit][i] == -1) continue;
	int to = ((long long)i*x)%n;
	int d = (to - i + n) % n;
	if(dist[to] == -1 || d < dist[to]) {
	  person[1-bit][to] = person[bit][i];
	  dist[to] = d;
	}
      }
      bit ^= 1;
      break;
    case '?':
      printf("%d\n", person[bit][x%n]);
      break;
    }
  }

  return 0;
}
