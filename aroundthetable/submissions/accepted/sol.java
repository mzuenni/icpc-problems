import java.util.Scanner;
import java.util.Locale;

public class sol {

	public static long sol(long l, long r) {
		long n = l + r;
		if (l < r || l > r + 2) return 2*n;
		if (n % 2 == 0) return n + n / 2;
		return n;
	}

	public static void main(String[] args) {
		Scanner s = new Scanner(System.in).useLocale(Locale.US);
		int l = s.nextInt();
		int r = s.nextInt();
		System.out.println(sol(l, r));
	}
}
