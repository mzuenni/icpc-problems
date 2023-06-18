import java.util.*;
public class jannik {
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		String s = in.next();

		int o = 1, l = 1;
		for (; o > 0; l++)
			o += (s.charAt(l) == '(' ? 1 : -1);

		String ns = s.substring(l) + s.substring(0, l);
		System.out.println(s.equals(ns) ? "No" : ns);
	}
}
