import java.util.*;
import java.io.*;

public class bitset {
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));

		int n = Integer.parseInt(br.readLine());

		int[] pos = new int[n];
		BitSet occupied = new BitSet(2000007);
		StringTokenizer st = new StringTokenizer(br.readLine());
		for (int i = 0; i < n; i++) {
			pos[i] = Integer.parseInt(st.nextToken());
			occupied.set(pos[i]);
		}
		for (int q = Integer.parseInt(br.readLine()); q-- > 0; ) {
			int id = Integer.parseInt(br.readLine()) - 1;

			occupied.clear( pos[id] );
			pos[id] = occupied.nextClearBit(pos[id]+1);
			occupied.set(pos[id]);

			bw.append(pos[id] + "\n");
		}

		bw.close();
	}
}
