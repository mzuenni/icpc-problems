import java.util.*;

public class jannik {
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		int n = in.nextInt(), w = in.nextInt();
		String res = "";
		for (int i = 0; i < n; i++) {
			if (i > 0) res += " ";
			res += in.next();
		}
		int i = 0;
		while (i < res.length()) {
			for (int k = 0; k < w && i < res.length(); k++, i++)
				System.out.print(res.charAt(i));
			System.out.println();
		}
	}
}
