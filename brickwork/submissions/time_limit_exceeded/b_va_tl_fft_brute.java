import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.*;

public class b_va_tl_fft_brute {
    public static void main(String[] args) {
        new b_va_tl_fft_brute().run();
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

    public class Complex {
        double re, im;

        public Complex(double re, double im) {
            this.re = re;
            this.im = im;
        }

        Complex multiply(Complex x) {
            return new Complex(x.re * re - x.im * im, x.re * im + x.im * re);
        }

        Complex sum(Complex x) {
            return new Complex(re + x.re, im + x.im);
        }

        Complex multiply(double x) {
            return new Complex(re * x, im * x);
        }

        public String toString() {
            return "(" + re + ", " + im + ")";
        }
    }

    public Complex ZERO = new Complex(0, 0);
    public Complex ONE = new Complex(1, 0);

    public void fft(Complex[] a, boolean invert) {
        int n = a.length;
        if (n == 1) return;

        Complex[] a0 = new Complex[n / 2];
        Complex[] a1 = new Complex[n / 2];
        for (int i = 0, j = 0; i < n; i += 2, ++j) {
            a0[j] = a[i];
            a1[j] = a[i + 1];
        }
        fft(a0, invert);
        fft(a1, invert);

        double ang = 2 * Math.PI / n * (invert ? -1 : 1);
        Complex w = new Complex(1, 0);
        Complex wn = new Complex(Math.cos(ang), Math.sin(ang));
        for (int i = 0; i < n / 2; ++i) {
            a[i] = a0[i].sum(w.multiply(a1[i]));
            a[i + n / 2] = a0[i].sum(w.multiply(a1[i]).multiply(-1));
            if (invert) {
                a[i] = a[i].multiply(0.5);
                a[i + n / 2] = a[i + n / 2].multiply(0.5);
            }
            w = w.multiply(wn);
        }
    }

    public boolean[] multiply(boolean[] a, boolean[] b) {
        int n = 1;
        while (n < a.length) {
            n <<= 1;
        }
        n <<= 1;

        Complex[] fa = new Complex[n];
        Arrays.fill(fa, ZERO);
        for (int i = 0; i < a.length; i++) {
            fa[i] = a[i] ? ONE : ZERO;
        }

        Complex[] fb = new Complex[n];
        Arrays.fill(fb, ZERO);
        for (int i = 0; i < b.length; i++) {
            fb[i] = b[i] ? ONE : ZERO;
        }

        fft(fa, false);
        fft(fb, false);
        for (int i = 0; i < fa.length; i++) {
            fa[i] = fa[i].multiply(fb[i]);
        }
        fft(fa, true);

        boolean[] result = new boolean[a.length];
        for (int i = 0; i < result.length; i++) {
            result[i] = fa[i].re > 0.5;
        }
        return result;
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
        for (int x : ws) {
            knapsack[x] = true;
        }

        for (int i = 0; i < 20; i++) {
            knapsack = multiply(knapsack, knapsack);
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

            Arrays.fill(can, false);
            int sum = 0;
            for (int brick : row1) {
                can[sum += brick] = true;
            }
            can[0] = false;

            int id2 = rnd.nextInt(bricks.size());
            ArrayList<Integer> row2 = restore(w, bricks.get(id2), knapsack, ws);

            for (int i = 0; i < 100; i++) {
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