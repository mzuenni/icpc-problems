import java.awt.*;
import java.io.*;
import java.util.*;

public class MZuenniTranscribed {
    public static void main(String[] args) throws IOException {
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(System.in))) {
            new MZuenniTranscribed().run(new Scanner(reader));
        }
    }

    public void run(Scanner sc) throws IOException {
        int n = sc.nextInt();
        Map<Point, Integer> in = new HashMap<>();
        for (int i = 0; i < 2 * n; i++) {
            Point p = new Point(sc.nextInt(), sc.nextInt());
            in.put(p, in.getOrDefault(p, 0) + 1);
        }
        for (long c : in.values()) {
            if (c % 2 != 0) {
                System.out.println("yes");
                return;
            }
        }
        System.out.println("no");
    }
}
