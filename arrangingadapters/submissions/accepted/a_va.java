import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.StringTokenizer;

public class a_va {
    public static void main(String[] args) {
        new a_va().run();
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

    public void solve() throws IOException {
        int n = nextInt();
        int s = nextInt();

        int[] x = new int[n];
        for (int i = 0; i < x.length; i++) {
            x[i] = nextInt();
        }

        Arrays.sort(x);

        if (s == 1) {
            out.println(1);
            return;
        }

        n -= 2;
        s -= 2;

        int[] count = new int[3];
        int sum_wo3 = 0;
        for (int i = 0; i < n; i++) {
            count[x[i] % 3]++;
            sum_wo3 += x[i] / 3;

            int[] cc = Arrays.copyOf(count, count.length);

            int pairs = Math.min(cc[1], cc[2]);
            cc[1] -= pairs;
            cc[2] -= pairs;
            int need = sum_wo3 + pairs + (cc[1] + 1) / 2 + (cc[2] + 1) / 2 * 2;
            if (need > s) {
                out.println(2 + i);
                return;
            }
        }
        out.println(2 + n);
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