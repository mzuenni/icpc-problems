import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.*;

public class b_va_tl_takenbitmap_brute3 {
    public static void main(String[] args) {
        new b_va_tl_takenbitmap_brute3().run();
    }

    BufferedReader br;
    StringTokenizer st;
    PrintWriter out;

    public String nextToken() throws IOException {
        while (st == null || !st.hasMoreTokens()) {
            st = new StringTokenizer(br.readLine());
        }
        return st.nextToken();
    }

    public int nextInt() throws IOException {
        return Integer.parseInt(nextToken());
    }

    public static final int lim = 300007;
    public static long[] dp = new long[lim / 64 + 7];

    public static boolean getDp(int i) {
        return ((dp[i / 64] >>> (i & 63)) & 1L) != 0L;
    }

    public static void clearDp(int i) {
        dp[i / 64] &= ~(1L << (i & 63));
    }

    public static void orDp(int i, boolean value) {
        if (value) dp[i / 64] |= 1L << (i & 63);
    }

    public ArrayList<Integer> restore(int w, int brick, int[] ws) {
        ArrayList<Integer> result = new ArrayList<>();
        result.add(brick);
        w -= brick;

        for (int i = ws.length - 1; i >= 0; i--) {
            while (w >= ws[i] && getDp(w - ws[i])) {
                w -= ws[i];
                result.add(ws[i]);
            }
        }

        return result;
    }

    public ArrayList<Integer> shift(ArrayList<Integer> row, int dir) {
        ArrayList<Integer> nr = new ArrayList<>();
        int id = (row.size() + dir) % row.size();
        for (int j = 0; j < row.size(); j++) {
            nr.add(row.get(id));
            id = (id + 1) % row.size();
        }
        return nr;
    }

    public boolean check(ArrayList<Integer> row, boolean[] can) {
        int sum2 = 0;
        boolean good = true;
        for (int brick : row) {
            good &= !can[sum2];
            sum2 += brick;
        }
        return good;
    }

    public void print(ArrayList<Integer> row1, ArrayList<Integer> row2) {
        out.println(row1.size());
        for (int brick : row1) {
            out.print(brick + " ");
        }
        out.println();
        out.println(row2.size());
        for (int brick : row2) {
            out.print(brick + " ");
        }
    }

    public void solve() throws IOException {
        int n = nextInt();
        int w = nextInt();

        int[] ws = new int[n];
        for (int i = 0; i < n; i++) {
            ws[i] = nextInt();
        }
        long start = System.nanoTime();

        Arrays.sort(ws);
        int l = 0;
        for (int i = 1; i < ws.length; i++) {
            if (ws[l] != ws[i]) {
                ws[++l] = ws[i];
            }
        }
        ws = Arrays.copyOfRange(ws, 0, l + 1);

        dp[0] = 1;
        for (int x : ws) {
            if (getDp(w)) break;
            boolean neq = false;
            for (int i = x; i <= w; i += x) neq |= getDp(i);
            if (x < 64) {//multiple set operations for same long
                for (int i = x; i < w; i++) orDp(i, getDp(i - x));
            } else {
                int ia = x / 64;
                int ib = x & 63;
                for (int i = 0; 64*i+x < w; i++) {
                    dp[i + ia] |= dp[i] << ib;
                    if (ib != 0) dp[i + ia + 1] |= dp[i] >>> (64 - ib);
                }
                clearDp(w);//we know it wasnt set before
            }
            if (x == w || w % x != 0 || neq) orDp(w, getDp(w - x));
        }

        ArrayList<Integer> bricks = new ArrayList<>();
        for (int i = 0; i < ws.length; i++) {
            if (getDp(w - ws[i])) {
                bricks.add(ws[i]);
            }
        }

        if (bricks.size() <= 1) {
            if (bricks.size() > 0 && w == bricks.get(0)) {
                out.println("possible");
                out.print(1 + "\n" + w + "\n" + 1 + "\n" + w);
                return;
            }
            out.println("impossible");
            return;
        }

        out.println("possible");

        Random rnd = new Random(239);

        boolean[] can = new boolean[w + 1];
        while (true) {
            int id1 = rnd.nextInt(bricks.size());
            ArrayList<Integer> row1 = restore(w, bricks.get(id1), ws);
            if (row1.get(row1.size() - 1).equals(row1.get(0))) {
                row1 = shift(row1, -1);
            }
            Collections.shuffle(row1);

            Arrays.fill(can, false);
            int sum = 0;
            for (int brick : row1) {
                can[sum += brick] = true;
            }
            can[0] = false;

            int id2 = rnd.nextInt(bricks.size());
            ArrayList<Integer> row2 = restore(w, bricks.get(id2), ws);
            if (row2.get(row2.size() - 1).equals(row2.get(0))) {
                row2 = shift(row2, -1);
            }

            for (int i = 0; i < 1000; i++) {
                if (i < 20) {
                    int shift = 0;
                    while (shift < row2.size() && row2.get(shift).equals(row2.get(0))) {
                        shift++;
                    }
                    row2 = shift(row2, shift);
                    if (check(row2, can)) {
                        print(row1, row2);
                        return;
                    }
                } else {
                    Collections.shuffle(row2);
                }

                if (check(row2, can)) {
                    print(row1, row2);
                    return;
                }
            }
        }
    }

    public void run() {
        try {
            br = new BufferedReader(new InputStreamReader(System.in));
            out = new PrintWriter(System.out);

            solve();

            out.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}