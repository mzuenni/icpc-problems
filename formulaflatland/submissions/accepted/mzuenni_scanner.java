import java.util.Scanner;
import java.util.Queue;
import java.util.ArrayDeque;
import java.util.ArrayList;

import java.util.Scanner;
import java.util.Queue;
import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.StringTokenizer;
import java.util.Set;
import java.util.TreeSet;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;

public class mzuenni_scanner {

    public static class Vector extends ArrayList<Integer> {}
    public static class Pair implements Comparable<Pair> {
        int a, b;
        Pair(int a, int b) {
            this.a = a;
            this.b = b;
        }

        @Override
        public int compareTo(Pair other) {
            if (a != other.a) return Integer.compare(this.a, other.a);
            return Integer.compare(this.b, other.b);
        }
    }

    public static Vector[] orientate(Vector[] adj) {
        int n = adj.length;
        boolean[] seen = new boolean[n];
        int[] deg = new int[n];
        Queue<Integer> todo = new ArrayDeque<Integer>();
        for (int i = 0; i < n; i++) {
            deg[i] = adj[i].size();
            if (deg[i] <= 5) todo.add(i);
        }
        Vector[] res = new Vector[n];
        for (int i = 0; i < n; i++) res[i] = new Vector();
        while (!todo.isEmpty()) {
            int c = todo.poll();
            if (seen[c]) continue;
            seen[c] = true;
            for (int x : adj[c]) {
                if (seen[x]) continue;
                res[c].add(x);
                deg[x]--;
                if (deg[x] == 5) todo.add(x);
            }
        }
        return res;
    }

    public static int solve(Vector[] adj) {
        int n = adj.length;
        int res = 5;
        int[] dist = new int[n];
        for (int i = 0; i < n; i++) dist[i] = -1;
        for (int i = 0; i < n; i++) {
            Queue<Integer> todo = new ArrayDeque<Integer>();
            todo.add(i);
            Vector done = new Vector();
            dist[i] = 0;
            while (!todo.isEmpty()) {
                int c = todo.poll();
                done.add(c);
                for (int x : adj[c]) {
                    if (dist[x] < 0) {
                        if (dist[c] + 1 <= 3) { 
                            dist[x] = dist[c] + 1;
                            todo.add(x);
                        }
                    } else {
                        res = Math.min(res, dist[x] + dist[c] + 1);
                    }
                }
            }
            for (int x : done) dist[x] = -1;
        }
        if (res == 5) {
            Set<Pair> seen = new TreeSet<Pair>();
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < adj[i].size(); j++) {
                    for (int k = 0; k < j; k++) {
                        int a = adj[i].get(j);
                        int b = adj[i].get(k);
                        if (a > b) {
                            int c = a;
                            a = b;
                            b = c;
                        }
                        if (seen.contains(new Pair(a, b))) return 4;//found diam
                        else seen.add(new Pair(a, b));
                    }
                }
            }
        }
        return res;
    }

    public static void main(String args[]) throws IOException {
        Scanner s = new Scanner(System.in);
        int n = s.nextInt();
        int m = s.nextInt();
        for (int i = 0; i < 2*n; i++) s.nextInt();
        Vector[] adj = new Vector[n];
        for (int i = 0; i < n; i++) adj[i] = new Vector();
        for (int i = 0; i < m; i++) {
            int a = s.nextInt();
            int b = s.nextInt();
            a--;
            b--;
            adj[a].add(b);
            adj[b].add(a);
        }
        adj = orientate(adj);
        System.out.println(solve(adj));
    }
}
