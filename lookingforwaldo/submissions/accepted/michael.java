import java.util.Scanner;

public class michael {
	
	public static final int inf = 0x3FFFFFFF;
	public static int[] val = new int[26];
	public static int[][] in;
	
	public static void solve(int h, int w) {
		int res = inf;
		for (int height = 1; height <= h; height++) {
			for (int row = 0; row + height <= h; row++) {
				int l = 0;
				int r = 0;
				int[] count = new int[5];
				while (r < w) {
					while (r < w && (count[0] == 0 ||
									 count[1] == 0 ||
									 count[2] == 0 ||
									 count[3] == 0 ||
									 count[4] == 0)) {
						for (int b = 0; b < 5; b++) {
							count[b] += (in[row][r] >> b) & 1;
						}
						r++;
					}
					while (count[0] > 0 &&
						   count[1] > 0 &&
						   count[2] > 0 &&
						   count[3] > 0 &&
						   count[4] > 0) {
						res = Math.min(res, height * (r - l));
						for (int b = 0; b < 5; b++) {
							count[b] -= (in[row][l] >> b) & 1;
						}
						l++;
					}
				}
				for (int i = 0; i < w; i++) {
					in[row][i] |= in[row + 1][i];
				}
			}
		}
		if (res == inf) System.out.println("impossible");
		else System.out.println(res);
	}

	public static void main(String[] args) {
		val['W' - 'A'] = 1;
		val['A' - 'A'] = 2;
		val['L' - 'A'] = 4;
		val['D' - 'A'] = 8;
		val['O' - 'A'] = 16;
		
		Scanner s = new Scanner(System.in);//dont do this...
		int h, w;
		h = s.nextInt();
		w = s.nextInt();
		in = new int[Math.min(h, w) + 1][Math.max(h, w)];
		for (int i = 0; i < h; i++) {
			String cur = s.next();
			for (int j = 0; j < w; j++) {
				if (h < w) in[i][j] = val[cur.charAt(j) - 'A'];
				else in[j][i] = val[cur.charAt(j) - 'A'];
			}
		}
		s.close();
		solve(Math.min(h, w), Math.max(h, w));
	}

}
