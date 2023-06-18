import java.util.*;

public class jannik {
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		int w = in.nextInt(), h = in.nextInt();
		int top = h;
		while (w-- > 0 && top >= 0) {
			int x = in.nextInt();
			if (x > top) top = -5;
			top = Math.min(h, top + 1 - 2 * ((top - x)%2));
		}
		System.out.println(top == h ? "possible" : "impossible");
	}
}
