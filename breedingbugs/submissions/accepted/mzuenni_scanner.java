import java.util.Scanner;
import java.util.Queue;
import java.util.ArrayDeque;
import java.util.ArrayList;

public class mzuenni_scanner {

    public static class Vector extends ArrayList<Integer> {}

    public static final int N = 20000007;
    public static boolean[] isNotPrime = new boolean[N];

    public static boolean isPrime(int x) {
        if (x < 2 || x % 2 == 0) return x == 2;
        else return !isNotPrime[x / 2];
    }

    public static  void primeSieve() {
        // i * i < N is enough for isPrime
        for (long i = 3; i < N; i += 2) {
            if (!isNotPrime[(int)(i / 2)]) {
                for (long j = i * i; j < N; j+= 2 * i) {
                    isNotPrime[(int)(j / 2)] = true;
                }
            }
        }
    }


    public static Vector[] adjlist;
    public static int[] pairs, dist; // pairs ist der gematchte Knoten oder -1

    public static boolean bfs(int n) {
        Queue<Integer> q = new ArrayDeque<Integer>();
        for(int i = 0; i < n; i++) {
            if (pairs[i] < 0) {dist[i] = 0; q.add(i);}
            else dist[i] = -1;
        }
        while(!q.isEmpty()) {
            int u = q.poll();
            for (int v : adjlist[u]) {
                if (pairs[v] < 0) return true;
                if (dist[pairs[v]] < 0) {
                    dist[pairs[v]] = dist[u] + 1;
                    q.add(pairs[v]);
        }}}
        return false;
    }

    public static boolean dfs(int u) {
        for (int v : adjlist[u]) {
            if (pairs[v] < 0 || (dist[pairs[v]] > dist[u] && dfs(pairs[v]))) { 
                pairs[v] = u; pairs[u] = v; 
                return true;
            }
        }
        dist[u] = -1;
        return false;
    }

    public static int hopcroft_karp(int n) { // n = #Knoten links
        int ans = 0;
        pairs = new int[adjlist.length];
        for (int i = 0; i < adjlist.length; i++) pairs[i] = -1;
        dist = new int[n];

        // Greedy Matching, optionale Beschleunigung.
        for (int i = 0; i < n; i++) {
            for (int w : adjlist[i]) {
                if (pairs[w] < 0) {
                    pairs[i] = w;
                    pairs[w] = i;
                    ans++;
                    break;
                }
            }
        }
        while(bfs(n)) {
            for(int i = 0; i < n; i++) {
                if (pairs[i] < 0 && dfs(i)) ans++;
            }
        }
        return ans;
    }

    public static void main(String args[]) {
        Scanner s = new Scanner(System.in);
        int n = s.nextInt();
        Vector[] in = new Vector[2];
        for (int i = 0; i < 2; i++) in[i] = new Vector();
        boolean seenOne = false;

        for (int i = 0; i < n; i++) {
            int x = s.nextInt();
            if (x != 1 || !seenOne) in[x % 2].add(x);
            seenOne |= x == 1;
        }

        primeSieve();
        adjlist = new Vector[n];
        for (int i = 0; i < n; i++) adjlist[i] = new Vector();
        for (int i = 0; i < in[0].size(); i++) {
            for (int j = 0; j < in[1].size(); j++) {
                if (isPrime(in[0].get(i) + in[1].get(j))) {
                    adjlist[i].add(in[0].size() + j);
                    adjlist[in[0].size() + j].add(i);
                }
            }
        }
        System.out.println(in[0].size() + in[1].size()-hopcroft_karp(in[0].size()));
    }
}
