// @EXPECTED_RESULTS@: ACCEPTED, TIME_LIMIT_EXCEEDED
#include <cstdio>
#include <cstring>
#include <map>
#include <set>

// highly inspired by ragnar.py

#define MAXLEN 18
#define PRIME 1000000007LL

char va[MAXLEN+1];
char vb[MAXLEN+1];

using namespace std;

map<multiset<char>, set<long long>> cancels(char *num) {
  map<multiset<char>, set<long long>> ret;
  int n = strlen(num);
  for(long long mask = 1; mask < (1LL << n); mask++) {
    multiset<char> del;
    long long x = 0;
    bool ok = true;
    for(long long i = 0; i < n; i++) {
      if((1LL << i) & mask) {
	if(x == 0 && num[i] == '0') {
	  ok = false;
	  break;
	}
	x = x * 10 + (num[i] - '0');
      } else del.insert(num[i]);
    }
    if(!ok) continue;
    if(ret.find(del) == ret.end()) {
      set<long long> s;
      ret[del] = s;
    }
    ret.find(del)->second.insert(x);
  }

  return ret;
}
long long gcd(long long a, long long b) {
  return b == 0 ? a : gcd(b, a % b);
}

bool check_eq(long long a, long long b, long long c, long long d) {
  return a * d == b * c && ((a % PRIME) * (d % PRIME)) % PRIME == ((b % PRIME) * (c % PRIME)) % PRIME;
}

int main() {
  long long c, d;
  scanf("%s %s %lld %lld\n", va, vb, &c, &d);
  long long g = gcd(c, d);
  c /= g;
  d /= g;
  auto top = cancels(va);
  auto bot = cancels(vb);
  for(auto adrop = top.begin(); adrop != top.end(); adrop++) {
    auto bdrop = bot.find(adrop->first);
    if(bdrop != bot.end()) {
      for(auto va = adrop->second.begin(); va != adrop->second.end(); va++) {
	for(auto vb = bdrop->second.begin(); vb != bdrop->second.end(); vb++) {
	  if(check_eq(*va, *vb, c, d)) {
	    printf("possible\n%lld %lld\n", *va, *vb);
	    return 0;
	  }
	}
      }
    }
  }

  printf("impossible\n");
  return 0;
}
