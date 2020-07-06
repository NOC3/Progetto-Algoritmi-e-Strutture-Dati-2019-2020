import java.util.*;

public class Node{
    public LinkedList<Edge> adj;
    public Edge counter;
    public long val;
    public Iterator<Edge> iter=null;
  //create node
  public Node(long val){
    this.val=val;
    this.adj=new LinkedList<Edge>();
  }
  //add the edge at adj list
  public void addEdge(Edge toAdd){
    this.adj.add(toAdd);
  }

  public void iterator(){
    if (iter==null){
      //initializzation
      this.iter = adj.iterator();
    }
  }

  public void removeIterator(){
    this.iter=null;
  }
}


class Edge{
    public int weight;
    public Edge next;
    public Node src;
    public Node dest;
    
    //create l'arco
    public Edge(int w, Node a, Node b){
      this.src = a;
      this.dest= b;
      this.weight = w;
      this.next = null;
    }
  
  }