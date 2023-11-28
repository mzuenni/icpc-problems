#include <stdio.h>
#include <stdlib.h>

#define MAXN 200000

int w[MAXN], v[MAXN];
int n, s;

int cmp(const void *a, const void *b) {
  int *x = (int *) a;
  int *y = (int *) b;
  return *x - *y;
}

int swapAdapter(int i) {
  int wi_mod_3 = v[i];
  for(int j = i - (i%2) - 2; j >= 0; j -= 2) {
    int c1 = v[j];
    int c2 = v[j+1];
    
    if(c1 + c2 == 2) {
      if(c1 == 0 || c2 == 0) {
        if(wi_mod_3 == 1) {
            w[j]++, v[j] = (v[j] + 1) % 3;
            w[i]--, v[i] = (v[i] + 2) % 3;
            return w[i];
        }
      }
      else {
        if(wi_mod_3 == 2) {
            w[j]++, v[j] = (v[j] + 1) % 3;
            w[i]--, v[i] = (v[i] + 2) % 3;
            return w[i];    
        }
      }
    }
    else if((c1 + c2 == 1 && wi_mod_3 == 2) || (c1 + c2 == 4 && wi_mod_3 == 1)) {
        w[j] += 2, v[j] = (v[j] + 2) % 3;
        w[i] -= 2, v[i] = (v[i] + 1) % 3;
        return w[i];
    }
  }
  return w[i];
}

int main() {
  scanf("%d %d\n", &n, &s);
  for(int i = 0; i < n; i++)
    scanf("%d", &w[i]);

  qsort(w, n, sizeof(int), cmp);
  for(int i = 0; i < n; ++i) v[i] = w[i] % 3;

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
