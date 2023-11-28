import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.math.BigInteger;
import java.util.HashMap;
import java.util.Map;
import java.util.StringTokenizer;

public class c_va_tl {
    public static void main(String[] args) {
        new c_va_tl().run();
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

    public int gcd(int a, int b) {
        return b == 0 ? a : gcd(b, a % b);
    }

    public long inv(long a, long mod) {
        return BigInteger.valueOf(a).modInverse(BigInteger.valueOf(mod)).intValue();
    }

    public void solve() throws IOException {
        int n = nextInt();
        int q = nextInt();

        HashMap<Long, Long> chairToPerson = new HashMap<>();
        for (long i = 0; i < n; i++) {
            chairToPerson.put(i, i == 0 ? n : i);
        }

        long add = 0;
        long mul = 1;
        for (int it = 0; it < q; it++) {
            switch (nextToken()) {
                case "?":
                    long place = nextInt() % n;
                    long xxx = -1;
                    for (long i = 0; i < n; i++) {
                        if (place == (i * mul + add) % n) {
                            if (chairToPerson.get(i) != null) {
                                xxx = i;
                            }
                        }
                    }
                    Long ans = chairToPerson.get(xxx);
                    out.println(ans == null ? -1 : ans);
                    break;
                case "+":
                    add += nextInt();
                    add %= n;
                    break;
                case "*":
                    int x = nextInt();
                    if (gcd(x, chairToPerson.size()) == 1) {
                        add = (add * x) % n;
                        mul = (mul * x) % n;
                        break;
                    }

                    HashMap<Long, Long> new_chair = new HashMap<>();
                    HashMap<Long, Long> current_cost = new HashMap<>();
                    for (Map.Entry<Long, Long> entry : chairToPerson.entrySet()) {
                        long chair = entry.getKey();
                        long person = entry.getValue();

                        long cc = (chair * mul + add) % n;
                        long nc = (cc * x) % n;
                        long ncost = (nc - cc + n) % n;
                        if (new_chair.containsKey(nc)) {
                            long cost = current_cost.get(nc);
                            if (cost > ncost) {
                                new_chair.put(nc, person);
                                current_cost.put(nc, ncost);
                            }
                        } else {
                            new_chair.put(nc, person);
                            current_cost.put(nc, ncost);
                        }
                    }
                    add = 0;
                    mul = 1;
                    chairToPerson = new_chair;
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