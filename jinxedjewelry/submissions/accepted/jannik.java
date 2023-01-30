import java.util.*;

public class jannik {
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		for (int t = in.nextInt(); t-->0; ) {
			int n = in.nextInt();
			long[] a = new long[n];
			for (int i = 0; i < n; i++) a[i] = in.nextLong();
			Arrays.sort(a);

			int front = 0, back = n-1, res = 1;
			for ( ; back - front + 1 >= 3; res++) {
				back--;
				a[back] += a[back+1] + 1; // this is irrelevant
				if (--a[front] == 0) front++;
			}
			if (back - front + 1 == 2 && a[front] > 1)
				res++;
			System.out.println(res);
		}
	}
}
