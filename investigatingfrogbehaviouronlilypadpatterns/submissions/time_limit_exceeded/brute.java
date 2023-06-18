import java.util.*;
import java.io.*;

public class brute {
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

		int n = Integer.parseInt(br.readLine());
		int[] pos = new int[n];
		boolean[] free = new boolean[2000007];
		for (int i = 0; i < free.length; i++) free[i] = true;

		StringTokenizer st = new StringTokenizer(br.readLine());
		for (int i = 0; i < n; i++) {
			pos[i] = Integer.parseInt(st.nextToken());
			free[pos[i]] = false;
		}

		for (int q = Integer.parseInt(br.readLine()); q-- > 0; ) {
			int i = Integer.parseInt(br.readLine()) - 1;

			free[pos[i]] = true;
			while (!free[++pos[i]]) {}
			free[pos[i]] = false;
			System.out.println(pos[i]);
		}
	}
}
