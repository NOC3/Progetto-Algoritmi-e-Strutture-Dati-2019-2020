import java.io.*;
import java.util.*;

public class Main {

  public static void main(String[] args) {
    FileReader f = null;
    BufferedReader b;
    PrintStream fileOut = null;
    String fileName = args[0];
    try {
      fileOut = new PrintStream(fileName.replace("input.txt", "output.txt"));
      System.setOut(fileOut);
      f = new FileReader(args[0]);
    } catch (Exception e) {
      printError(e);
    }
    b = new BufferedReader(f);

    HashMap<Integer, Node> graph = createGraph(b);// create graph

    solveQuery(b, fileOut, graph);// solve queries

  }

  static HashMap<Integer, Node> createGraph(BufferedReader b) {
    HashMap<Integer, Node> arrayNode = new HashMap<>();
    int nodeNumber = -1;
    try {
      nodeNumber = Integer.parseInt(b.readLine());
    } catch (Exception e) {
      printError(e);
    }
    for (int i = 0; i < nodeNumber - 1; i++) {
      String line = "";
      try {
        line = b.readLine();
      } catch (Exception e) {
        printError(e);
      }
      String[] parser = line.split(" ");
      Integer nodeNumberA = Integer.parseInt(parser[0]);
      Integer nodeNumberB = Integer.parseInt(parser[1]);
      Node A;
      Node B;
      if (arrayNode.containsKey(nodeNumberA)) {
        A = arrayNode.get(nodeNumberA);// A is in HashMap
      } else {
        A = new Node(nodeNumberA);// A isn't in HashMap
      }
      if (arrayNode.containsKey(nodeNumberB)) {
        B = arrayNode.get(nodeNumberB);// B is in HashMap
      } else {
        B = new Node(nodeNumberB);// B isn't in HashMap
      }
      Edge eA = new Edge(Integer.parseInt(parser[2]), A, B);
      Edge eB = new Edge(Integer.parseInt(parser[2]), B, A);
      A.addEdge(eA);
      B.addEdge(eB);
      arrayNode.putIfAbsent(nodeNumberA, A);// Edge A to B
      arrayNode.putIfAbsent(nodeNumberB, B);// Edge B to A
    }
    return arrayNode;
  }

  static int solveQuery(BufferedReader b, PrintStream fileOut, HashMap<Integer, Node> graph) {
    String[] answer = null;
    int queryNumber = 0;
    try {
      queryNumber = Integer.parseInt(b.readLine());
      answer = new String[queryNumber];
      for (int i = 0; i < queryNumber; i++) {// parsing query
        String line = b.readLine();
        String[] parser = line.split(" ");
        int nodeA = Integer.parseInt(parser[0]);
        int nodeB = Integer.parseInt(parser[1]);
        int newEdge = Integer.parseInt(parser[2]);
        answer[i] = computeQuery(fileOut, graph, nodeA, nodeB, newEdge);// solving query
      }

    } catch (Exception e) {
      printError(e);
    }
    return queryNumber;
  }

  static String computeQuery(PrintStream fileOut, HashMap<Integer, Node> graph, int newNodeA, int newNodeB, int newEdgeW) {
    String answer = "NO";
    try {
      Node A = graph.get(newNodeA);
      Node B = graph.get(newNodeB);

      for (HashMap.Entry<Integer, Node> element : graph.entrySet()) {
        
        element.getValue().removeIterator();

      }


      Stack<Integer> res = dfs(graph, A, B);
      if (res.peek() > newEdgeW) {
        answer = "YES";
      }
      System.out.println(answer);
    } catch (Exception e) {
      printError(e);
    }
    return answer;
  }

  // returns stack of weigths in path A->B
  static Stack<Integer> dfs(HashMap<Integer, Node> graph, Node sNode, Node fNode) {
    // from sNode ---> to fNode
    Stack<Integer> wStack = new Stack<Integer>();
    Stack<Node> nStack = new Stack<Node>();
    Node v = null;
    Edge e;
    nStack.push(sNode);
    wStack.push(0);
    while (nStack.peek() != fNode) {
      Node u = nStack.peek();
      u.iterator();
      if (u.iter.hasNext()) {
        e = u.iter.next();
        v = e.dest;
        if (!nStack.contains(v)) {
          nStack.push(v);
          wStack.push(Math.max(e.weight, wStack.peek()));
        }
      } else {// wrong path, pop elements
        nStack.pop();
        wStack.pop();
      }
    }
    return wStack;
  }

  // UTIL FUNCTION
  // Function for printing graph
  static void printGraph(HashMap<Integer, Node> graph) {
    System.out.println("\n---------------");
    for (HashMap.Entry<Integer, Node> element : graph.entrySet()) {
      Integer node = element.getKey();
      System.out.println("Vertice: " + node);
      LinkedList<Edge> e = element.getValue().adj;
      Object[] c = e.toArray();
      for (int i = 0; i < c.length; i++) {
        System.out.println(
            "Arco [" + ((Edge) c[i]).src.val + "]--(" + ((Edge) c[i]).weight + ")-->[" + ((Edge) c[i]).dest.val + "]");
      }
    }
    System.out.println("---------------\n");

  }

  // Print error function
  static void printError(Exception e) {
    System.out.println("errore: " + e.toString());
    System.exit(1);
  }
}