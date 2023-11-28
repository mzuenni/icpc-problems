import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.*;

public class b_va_tl_brute {
    public static void main(String[] args) {
        new b_va_tl_brute().run();
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

    public ArrayList<Integer> restore(int w, int brick, boolean[] dp, int[] ws) {
        ArrayList<Integer> result = new ArrayList<>();
        result.add(brick);
        w -= brick;

        for (int i = ws.length - 1; i >= 0; i--) {
            while (w >= ws[i] && dp[w - ws[i]]) {
                w -= ws[i];
                result.add(ws[i]);
            }
        }

        return result;
    }

    public void solve() throws IOException {
        int n = nextInt();
        int w = nextInt();

        int[] ws = new int[n];
        for (int i = 0; i < n; i++) {
            ws[i] = nextInt();
        }

        Arrays.sort(ws);
        int l = 0;
        for (int i = 1; i < ws.length; i++) {
            if (ws[l] != ws[i]) {
                ws[++l] = ws[i];
            }
        }
        ws = Arrays.copyOfRange(ws, 0, l + 1);

        boolean[] knapsack = new boolean[w + 1];
        knapsack[0] = true;
        for (int i = 0; i < ws.length; i++) {
            for (int j = ws[i]; j < knapsack.length; j++) {
                knapsack[j] |= knapsack[j - ws[i]];
            }
        }

        ArrayList<Integer> bricks = new ArrayList<>();
        for (int i = 0; i < ws.length; i++) {
            if (knapsack[w - ws[i]]) {
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
            ArrayList<Integer> row1 = restore(w, bricks.get(id1), knapsack, ws);
            Collections.shuffle(row1);

            int sum = 0;
            for (int brick : row1) {
                can[sum += brick] = true;
            }
            can[0] = false;

            int id2 = rnd.nextInt(bricks.size());
            ArrayList<Integer> row2 = restore(w, bricks.get(id2), knapsack, ws);

            for (int i = 0; i < 10; i++) {
                Collections.shuffle(row2);

                int sum2 = 0;
                boolean good = true;
                for (int brick : row2) {
                    good &= !can[sum2];
                    sum2 += brick;
                }
                if (good) {
                    out.println(row1.size());
                    for (int brick : row1) {
                        out.print(brick + " ");
                    }
                    out.println();
                    out.println(row2.size());
                    for (int brick : row2) {
                        out.print(brick + " ");
                    }
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