import java.util.*;
import java.math.*;
import java.io.*;

class FastIO {
    static BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
    static StringTokenizer tokens = new StringTokenizer("");
    
    static boolean hasNext() throws IOException {
        while (!tokens.hasMoreTokens()) {
            String line = r.readLine();
            if (line == null) return false;
            tokens = new StringTokenizer(line);
        }
        return true;
    }

    static String next() throws IOException {
        hasNext();
        return tokens.nextToken();
    }
    
    static int nextInt() throws IOException {
        return Integer.parseInt(next());
    }

}

class UnionFind {
    int[] unions;
    UnionFind(int n) {
        unions = new int[n];
        for (int i = 0; i < n; i++) unions[i] = -1;
    }
    int findSet(int n) {
        if (unions[n] < 0) return n;
        return unions[n] = findSet(unions[n]);
    }
    void linkSets(int a, int b) { // Union by rank.
        if (unions[b] > unions[a]) {
            int c = a;
            a = b;
            b = c;
        }
        if (unions[b] == unions[a]) unions[b]--;
        unions[a] = b;
    }

    void unionSets(int a, int b) { // Diese Funktion aufrufen.
        if (findSet(a) != findSet(b)) linkSets(findSet(a), findSet(b));
    }
}

public class mzuenni {
    public static void main(String[] args) throws Exception {
        int n = FastIO.nextInt();
        int q = FastIO.nextInt();

        int[] lim = new int[n];
        int[] state = new int[n];
        int[] next = new int[n];
        int[] cur = new int[n];
        int[] tmp = new int[n];
        int nextTmp = 0;
        for (int i = 0; i < n; i++) {
            lim[i] = FastIO.nextInt();
            cur[i] = i;
            next[i] = -1;
        }
        for (int i = n - 1; i >= 0; i--) {
            while (nextTmp > 0 && lim[tmp[nextTmp - 1]] <= lim[i]) nextTmp--;
            if (nextTmp > 0) next[i] = tmp[nextTmp - 1];
            tmp[nextTmp] = i;
            nextTmp++;
        }
        UnionFind uf = new UnionFind(n);
        for (int i = 0; i < q; i++) {
            String t = FastIO.next();
            int p = FastIO.nextInt();
            p--;
            if ("+".equals(t)) {
                int x = FastIO.nextInt();
                while (x > 0 && p >= 0) {
                    p = cur[uf.findSet(p)];
                    int c = Math.min(x, lim[p] - state[p]);
                    state[p] += c;
                    x -= c;
                    if (lim[p] == state[p]) {
                        if (next[p] >= 0) {
                            int pp = cur[uf.findSet(next[p])];
                            uf.unionSets(p, pp);
                            cur[uf.findSet(pp)] = pp;
                        } else {
                            p = -1;
                        }
                    }
                }
            } else {
                System.out.print(state[p] + "\n");
            }
        }
    }
}
