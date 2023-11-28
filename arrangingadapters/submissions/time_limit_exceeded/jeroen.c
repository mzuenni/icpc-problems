#include <stdio.h>
#include <stdlib.h>

#define MAXN 200000

int w[MAXN];
int n, s;

int cmp(const void *a, const void *b) {
  int *x = (int *) a;
  int *y = (int *) b;
  return *x - *y;
}

int swapAdapter(int i) {
  // Linear search for gaps
  int gap10 = 0;
  int gap11 = 0;
  int gap20 = 0;
  int gap22 = 0;
  for(int j = i - (i%2) - 2; j >= 0; j -= 2) {
    int c1 = w[j];
    int c2 = w[j+1];
    
    if((c1 % 3) + (c2 % 3) == 2) {
      if((c1 % 3) == 0 || (c2 % 3) == 0) {
	if(w[i] % 3 == 1) {
	  w[j] += 1;
	  w[i] -= 1;
	  return w[i];
	}
      }
      else {
	if(w[i] % 3 == 2) {
	  w[j] += 1;
	  w[i] -= 1;
	  return w[i];
	}
      }
    } else if((c1 % 3) + (c2 % 3) == 1) {
      if(w[i] % 3 == 2) {
	w[j] += 2;
	w[i] -= 2;
	return w[i];
      }
    } else if((c1 % 3) + (c2 % 3) == 4) {
      if(w[i] % 3 == 1) {
	w[j] += 2;
	w[i] -= 2;
	return w[i];
      }
    }
  }
  return w[i];
}

int main() {
  scanf("%d %d\n", &n, &s);
  for(int i = 0; i < n; i++)
    scanf("%d", &w[i]);

  qsort(w, n, sizeof(int), cmp);

  if (n == 1 || s == 1) {
    printf("1\n");
    return 0;
  }
  
  int res = 2;
  n -= 2;
  s -= 2;

  for(int i = 0; i < n; i += 2) {
    int c1 = swapAdapter(i);
    int s1 = (c1 + 2) / 3;
    
    // Check if this plug still fits
    if(s1 > s) break;
    res++;
    s -= s1;
    
    // Now place the next one opposite
    if(i + 1 < n) {
      int c2 = swapAdapter(i+1);
      int s2 = (c1 + c2 + 2) / 3 - s1;
      
      if(s2 > s) break;
      s -= s2;
      res++;
    }
  }
  printf("%d\n", res);
  return 0;
}
