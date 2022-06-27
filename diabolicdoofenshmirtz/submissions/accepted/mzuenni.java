import java.util.Scanner;

public class mzuenni {
    public static void main(String args[]) {
        Scanner s = new Scanner(System.in);
        for (long x = 2;; x *= 2) {
            System.out.println("? " + (x-1));
		    System.out.flush();
    		long res = s.nextLong();
    		if (res != x-1) {
                System.out.println("! " + (x-1-res));
    		    System.out.flush();
    			return;
    		}
    	}
    }
}
