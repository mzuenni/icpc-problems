import java.util.*;
import java.io.*;

public class jannik_fastio {
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		for (int t = Integer.parseInt(st.nextToken()); t-->0; ) {
			st = new StringTokenizer(br.readLine());
			int n = Integer.parseInt(st.nextToken());
			st = new StringTokenizer(br.readLine());
			long[] a = new long[n];
			for (int i = 0; i < n; i++) a[i] = Long.parseLong(st.nextToken());
			Arrays.sort(a);

			int front = 0, back = n-1, res = 1;
			for ( ; back - front + 1 >= 3; res++) {
				back--;
				a[back] += a[back+1] + 1;
				if (--a[front] == 0) front++;
			}
			if (back - front + 1 == 2 && a[front] > 1)
				res++;
			System.out.println(res);
		}
	}
}
