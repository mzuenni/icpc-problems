import java.io.*;
import java.util.*;
public class BalBinTreePK{


   public static void main (String [] args){
      run(readTest());
   }

   public static int [][] readTest(){
      int [][] testcase = null;
      try{
         BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
         String line = in.readLine();
         Scanner ir = new Scanner(line);
         int n = ir.nextInt();
         testcase = new int[n][2];
         for (int k = 1; k < n; k++){  
            line = in.readLine();
            String [] words = line.split(" ");
            testcase[k][0] = Integer.parseInt(words[0]);
            testcase[k][1] = Integer.parseInt(words[1]);
         }
      }
      catch (IOException iox){System.out.println( iox);}
      return testcase;
   }

   static void run (int [][] testcase){
      int n = 1 + testcase.length;
      BalBinTreePK tree = new BalBinTreePK(n);
      for (int [] pair : testcase)
         tree.addVertex(pair[0], pair[1]);
      tree.makeTree();
      System.out.println(tree.balance());
   }

/////////////////////////////////////////

   int size;
   Node [] nodes;
   Node root;

   public BalBinTreePK(int sizeIn){
      size = sizeIn;
      nodes = new Node[size + 1];
      for (int k = 0; k <= size; k++)
         nodes[k] = new Node(k);
      root = nodes[1];
   }
   
   void addVertex(int n1, int n2){
      nodes[n1].addNeighbour(nodes[n2]);
      nodes[n2].addNeighbour(nodes[n1]);
   }

   void makeTree(){
      root.setParent(null);
   }

   int balance(){
      return Node.removed;
   }
   
   void show(){
      for (Node n : nodes)
      System.out.println(n);
   }
}
class Node{
   static int removed = 0;

   int num;
   int depth;
   int size;
   Node left;
   Node right;

   Node [] neighbour = new Node[3]; // neighbour[0] should be the parent

   public Node(int numIn){
      num = numIn;
   }

   void addNeighbour(Node n){
      int k = 0;
      while (neighbour[k] != null)
        k++;
      neighbour[k] = n;
   }

  void setParent(Node n){
     int k = 0;
     while (neighbour[k] != n)
        k++;
     neighbour[k] = neighbour[0];
     neighbour[0] = n;
     left = neighbour[1];
     right = neighbour[2];
     neighbour = null;

     if (left != null)
        left.setParent(this);
     if (right != null)
        right.setParent(this);
     setDepth();
     setSize();

     balance();

   }
   
   void prune(int k){
     //System.out.println("pruning :  " + num + " at " + k);
      if (k > 0){
         if (left != null)
            left.prune(k-1);
         if (right != null)
            right.prune(k-1);
      }
      else{ // k == 0
         if (left != null){
            left.remove();
            left = null;
         }
         if (right != null){
            right.remove();
            right = null;
         }
      }
      setSize();
      setDepth();
   }

   void remove(){
      //System.out.println("removing : "+ num);
      setSize();
      removed+= size;
      //System.out.println(removed);
   }

   private void setSize(){
      size = 1;
      if (left != null)
         size += left.size;
      if (right != null)
         size += right.size;
   }

   private void setDepth(){
      depth = 1 + Math.max(depthLeft(), depthRight());
   }

   private int depthLeft(){
      if (left != null)
         return left.depth;
      else
         return -1;
   }

   private int depthRight(){
      if (right != null)
         return right.depth;
      else
         return -1;
   }


   void balance(){
      //System.out.println("balancing :  " + num);
      int depthLeft  = depthLeft();
      int depthRight = depthRight();
     // System.out.println("depthLeft = " + depthLeft);
     // System.out.println("depthRight = " + depthRight);
      if (depthLeft > depthRight + 1){
         left.prune(depthRight + 1);
      } 
      if (depthRight > depthLeft + 1){
         right.prune(depthLeft + 1);
      }
      setDepth();
      setSize();
   }


   public String toString(){
      String answer = "" + num; 
      if (left != null)
         answer += "  left = "+ left.num;
      if (right != null)
         answer += "  right =  "+ right.num;
      answer += " size = " + size;
      answer += " depth = " + depth;
      return answer;
   }

}