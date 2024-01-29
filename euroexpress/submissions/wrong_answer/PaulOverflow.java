import java.util.*;

public class PaulOverflow {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt();
		int res = 0;
		while (n --> 0) {
			int a = sc.nextInt();
			int b = sc.nextInt();
			res = Math.max(res, a * b * Math.min(a, b));
		}
		System.out.println(res);
	}
}
