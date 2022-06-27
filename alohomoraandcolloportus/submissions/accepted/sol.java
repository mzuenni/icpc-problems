import java.util.Scanner;
import java.lang.Math;
import java.util.ArrayList;

public class sol {

	public static class Vector extends ArrayList<Integer> {}

	public static int n;
	public static int m;
	public static Vector[] adj;
	public static int[] unions;

	public static void init() { //Initialisieren
		unions = new int[n];
		for (int i = 0; i < n; i++) unions[i] = -1;
	}

	public static int findSet(int n) { // Pfadkompression
		if (unions[n] < 0) return n;
		return unions[n] = findSet(unions[n]);
	}

	public static void linkSets(int a, int b) { // Union by rank.
		if (unions[a] > unions[b]) unions[a] = b;
		else if (unions[b] > unions[a]) unions[b] = a;
		else {
			unions[a] = b;
			unions[b]--;
	}}

	public static void unionSets(int a, int b) { // Diese Funktion aufrufen.
		if (findSet(a) != findSet(b)) linkSets(findSet(a), findSet(b));
	}

	public static void check(int x) {
		init();
		int edges = 0;
		for (int i = 0; i < n; i++) {
			if (i == x) continue;
			int deg = 0;
			for (int j : adj[i]) {
				if (j == x) continue;
				deg++;
				if (j > i) continue;
				if (findSet(i) == findSet(j)) return;
				unionSets(i, j);
				edges++;
			}
			if (deg > 2) return;
		}
		if (edges + 1 != n - 1) return;
		System.out.println("YES");
		System.exit(0);
	}

	public static void main(String[] args) {
		Scanner s = new Scanner(System.in);//dont do this...
		n = s.nextInt();
		m = s.nextInt();
		adj = new Vector[n];
		for (int i = 0; i < n; i++) adj[i] = new Vector();
		for (int i = 0; i < m; i++) {
			int a = s.nextInt();
			int b = s.nextInt();
			a--;
			b--;
			adj[a].add(b);
			adj[b].add(a);
		}
		ArrayList<Vector> byDeg = new ArrayList<>();
		for (int i = 0; i < n; i++) {
			while (byDeg.size() <= adj[i].size()) byDeg.add(new Vector());
			byDeg.get(adj[i].size()).add(i);
		}
		if (byDeg.size() > 4) {//there is a vertex with degree > 3
			check(byDeg.get(byDeg.size() - 1).get(0));
		} else if (byDeg.size() == 4) {//there is a vertex with degree 3
			for (int i = 0; i < n; i++) {
				int deg3 = 0;
				if (adj[i].size() == 3) deg3++;
				for (int j : adj[i]) {
					if (adj[j].size() == 3) deg3++;
				}
				if (deg3 == byDeg.get(3).size()) {//vertex is adjacent to all degree 3 vertices
					check(i);
				}
			}
		} else if (!byDeg.get(0).isEmpty()) {//there is a vertex with degree 0
			check(byDeg.get(0).get(0));
		} else if (m > 0 && !byDeg.get(1).isEmpty()) {//there is a vertex with degree 1 (can only be a constant amount)
			check(byDeg.get(1).get(0));
		} else {//test any vertex
			check(0);
		}
		System.out.println("NO");
		s.close();
	}

}