import java.util.*;
import java.math.*;
import java.io.*;

class Stack {
    int count;
    int[] data;
    Stack(int capacity) {
        count = 0;
        data = new int[capacity];
    }
    int getCount() {
        return count;
    }
    boolean isEmpty() {
        return count == 0;
    }
    int peek() {
        return data[count - 1];
    }
    int pop() {
        count--;
        return data[count];
    }
    void push(int element) {
        data[count] = element;
        count++;
    }
}

class UnionFind {
    int[] parent;
    UnionFind(int size) {
        parent = new int[size];
        for (int i = 0; i < size; i++) {
            parent[i] = i;
        }
    }
    int find(int x) {
        if (parent[x] == x) {
            return x;
        }
        parent[x] = find(parent[x]);
        return parent[x];
    }
    boolean unite(int x, int y) {
        int px = find(x);
        int py = find(y);
        if (px == py) {
            return false;
        }
        parent[px] = py;
        return true;
    }
}

public class arnar {
  public static void main(String[] args) throws Exception {
    Scanner in = new Scanner(System.in);
    PrintWriter out = new PrintWriter(System.out, false);
    
    long infinity = 1_000_000_000_000_000_000L;

    int n = in.nextInt();
    int q = in.nextInt();
    
    int sink = n;
    
    long[] capacities = new long[n + 1];
    long[] amount = new long[n + 1];
    int[] nextGreater = new int[n + 1];
    
    Stack stack = new Stack(n + 1);
    stack.push(sink);
    
    UnionFind uf = new UnionFind(n + 1);

    for (int i = 0; i < n; i++) {
        capacities[i] = in.nextInt();
    }
    capacities[sink] = infinity;
    nextGreater[sink] = -1;

    for (int i = n - 1; i >= 0; i--) {
        while (capacities[stack.peek()] <= capacities[i]) {
            stack.pop();
        }
        nextGreater[i] = stack.peek();
        stack.push(i);
    }

    
    for (int i = 0; i < q; i++) {
        String s = in.next();
        if (s.equals("+")) {
            int level = uf.find(in.nextInt() - 1);
            long water = in.nextLong();
            while (water > 0) {
                long take = Math.min(capacities[level] - amount[level], water);
                water -= take;
                amount[level] += take;
                if (amount[level] == capacities[level]) {
                    assert nextGreater[level] != -1;
                    uf.unite(level, nextGreater[level]);
                }
                level = uf.find(level);
            }
        }
        else {
            int level = in.nextInt() - 1;
            out.println(amount[level]);
        }
    }
    

    out.flush(); 
  }
}
