import java.util.*;

public class Paul {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt();
		long res = 0;
		while (n --> 0) {
			int a = sc.nextInt();
			int b = sc.nextInt();
			res = Math.max(res, (long) a * b * Math.min(a, b));
		}
		System.out.println(res);
	}
}
