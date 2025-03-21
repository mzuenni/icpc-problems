import java.util.*;
public class jannik {
  static class IntList extends ArrayList<Integer> {}

  static boolean[] deleted;
  static IntList[] adj;
  static IntList[] adji;
  static boolean drop(int i) {
    while (!adji[i].isEmpty() && deleted[adji[i].get(adji[i].size() - 1)]) {
      adj[i].remove(adj[i].size() - 1);
      adji[i].remove(adji[i].size() - 1);
    }
    return adj[i].isEmpty();
  }
  static IntList step;
  static int m;
  static void dfs(int i) {
    while (!drop(i)) {
      int j = adj[i].get(adj[i].size() - 1);
      int e = adji[i].get(adji[i].size() - 1);
      deleted[e] = true;
      dfs(j);
      if (e >= m) step.add(-1);
    }
    step.add(i);
  }
  public static void main(String[] args) {
    Scanner in = new Scanner(System.in);
    int n = in.nextInt();
    m = in.nextInt();
    for (int i = 0; i < 2 * n; i++) in.next();
    adj = new IntList[n];
    adji = new IntList[n];
    for (int i = 0; i < n; i++) {
      adj[i] = new IntList();
      adji[i] = new IntList();
    }
    for (int i = 0; i < m; i++) {
      int a = in.nextInt() - 1, b = in.nextInt() - 1;
      adj[a].add(b);
      adji[a].add(i);
      adj[b].add(a);
      adji[b].add(i);
    }

    int m2 = m;
    for (int pre = -1, i = 0; i < n; i++) {
      if (adj[i].size() % 2 == 0)
        continue;
      if (pre < 0) pre = i;
      else {
        adj[pre].add(i);
        adji[pre].add(m2);
        adj[i].add(pre);
        adji[i].add(m2);
        m2++;
        pre = -1;
      }
    }

    deleted = new boolean[m2];

    ArrayList<List<Integer>> res = new ArrayList<>();
    for (int i = 0; i < n; i++) {
      if (drop(i))
        continue;
      step = new IntList();
      dfs(i);
      int idx = step.indexOf(-1);
      if (idx != -1) {
        step.remove(step.size() - 1);
        Collections.rotate(step, step.size() - idx);
      }
      for (int it = 0, fst = 0; ; it++) {
        if (it == step.size() || step.get(it) < 0) {
          if (fst != it) res.add(step.subList(fst, it));
          if (it == step.size()) break;
          else fst = ++it;
        }
      }
    }
    System.out.println(res.size());
    for (List<Integer> v : res) {
      System.out.println(v.size());
      for (int x : v)
        System.out.print((x + 1) + " ");
      System.out.println();
    }
  }
}
