import java.util.*;
import java.io.*;

public class Main {
  public static void main(String[] args) {
    String fileName = args[0];
    BufferedReader b = null;

    try {
      b = new BufferedReader(new FileReader(fileName));
    } catch (Exception e) {
      System.out.println(e.getLocalizedMessage());
      System.exit(0);
    }

    int nodeNumber = -1;
    try {
      nodeNumber = Integer.parseInt(b.readLine());
    } catch (Exception e) {
      System.exit(0);
    }

    Graph g = new Graph(nodeNumber);

    //read of input.txt
    String ln;
    try {
      int i = 0;
      while (i < nodeNumber - 1) {
        ln = b.readLine();

        String[] parameters = ln.split(" ");
        int x = Integer.parseInt(parameters[0]);
        int y = Integer.parseInt(parameters[1]);
        int w = Integer.parseInt(parameters[2]);

        if(g.vertices.putIfAbsent(x, new HashMap<Integer, Integer>())==null)
          g.cenTree[x] = new NodeUtil();
        
        if(g.vertices.putIfAbsent(y, new HashMap<Integer, Integer>())==null)
          g.cenTree[y] = new NodeUtil();
        
        g.vertices.get(x).put(y, w);
        g.vertices.get(y).put(x, w);
       
        i++;
      }
    } catch (Exception e) {
      System.out.println(e.toString());
      System.exit(0);
    }

    g.decompose(1, -1, 1);

    //read and solve query
    try {
      BufferedWriter bw = new BufferedWriter(new FileWriter(fileName.replace("input.txt", "output.txt"))); //substitution in args[0]
      int queryN = Integer.parseInt(b.readLine());
      int i = 0;

      while (i < queryN) {
        ln = b.readLine();
        String[] parameters = ln.split(" ");
        
        if (g.query(Integer.parseInt(parameters[0]), Integer.parseInt(parameters[1])) > Integer.parseInt(parameters[2])) {
          bw.write("YES");   
        } else {
          bw.write("NO");
        }
        bw.newLine();
        i++;
      }
      bw.close();
    } catch (Exception e) {
      System.out.println(e.getLocalizedMessage());
      System.exit(0);
    }
  }
}
