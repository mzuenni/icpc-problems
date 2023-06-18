import java.util.*;
import java.io.*;

public class jannik_fast_io {
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		BufferedWriter out = new BufferedWriter(new OutputStreamWriter(System.out));

		int n = Integer.parseInt(br.readLine());

		TreeSet<Integer> free = new TreeSet<>();
		for (int i = 1; i <= 2.1e6; i++)
			free.add(i);

		int[] pos = new int[n];
		StringTokenizer st = new StringTokenizer(br.readLine());
		for (int i = 0; i < n; i++) {
			pos[i] = Integer.parseInt(st.nextToken());
			free.remove(pos[i]);
		}

		for (int q = Integer.parseInt(br.readLine()); q-- > 0; ) {
			int i = Integer.parseInt(br.readLine()) - 1;

			free.add(pos[i]);
			pos[i] = free.ceiling(pos[i]+1);
			free.remove(pos[i]);
			out.write(pos[i] + "\n");
		}

		out.flush();
	}
}
