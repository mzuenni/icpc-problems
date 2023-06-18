import java.util.*;

public class jannik {
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);

		int n = in.nextInt();
		int[] pos = new int[n];

		TreeSet<Integer> free = new TreeSet<>();
		for (int i = 1; i <= 2.1e6; i++)
			free.add(i);

		for (int i = 0; i < n; i++) {
			pos[i] = in.nextInt();
			free.remove(pos[i]);
		}

		for (int q = in.nextInt(); q-- > 0; ) {
			int i = in.nextInt() - 1;

			free.add(pos[i]);
			pos[i] = free.ceiling(pos[i]+1);
			free.remove(pos[i]);
			System.out.println(pos[i]);
		}
	}
}
