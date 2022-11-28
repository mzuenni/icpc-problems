import java.io.*;
import java.util.*;

public class RagnarRTranscribedByMaarten {
    public static void main(String[] args) throws IOException {
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(System.in))) {
            new RagnarRTranscribedByMaarten().run(reader);
        }
    }

    public void run(BufferedReader reader) throws IOException {
        int n = Integer.parseInt(reader.readLine());

        S[] ps = new S[n];
        for (int i = 0; i < n; i++) {
            String[] split = reader.readLine().split(" ");
            ps[i] = new S(Integer.parseInt(split[0]), Integer.parseInt(split[1]), i);
        }

        TreeMap<Integer, Integer> best = new TreeMap<>();
        best.put(-1, 0);

        Arrays.sort(ps);
        int[] ans = new int[n];
        for (S s : ps) {
            // s.ans   = prev(best.upper_bound(s.l))->second + 1;
            Integer key = best.higherKey(s.l);
            ans[s.i] = (key == null ? best.lastEntry() : best.lowerEntry(key)).getValue() + 1;
            // auto it = best.insert_or_assign(s.l, s.ans).first;
            best.put(s.l, ans[s.i]);
            Map.Entry<Integer, Integer> it = best.ceilingEntry(s.l);
            // if(next(it) != best.end() && next(it)->second <= s.ans) best.erase(next(it));
            if (it != null) {
                Map.Entry<Integer, Integer> next = best.higherEntry(it.getKey());
                if (next != null && next.getValue() <= ans[s.i]) {
                    best.remove(next.getKey());
                }
            }
        }

        for (int x : ans) System.out.print(x - 1 + " ");
    }

    static class S implements Comparable<S> {
        int l, r, i;

        public S(int l, int r, int i) {
            this.l = l;
            this.r = l + r;
            this.i = i;
        }

        public int compareTo(S o) {
            if (r != o.r) return o.r - r;
            return l - o.l;
        }
    }
}
