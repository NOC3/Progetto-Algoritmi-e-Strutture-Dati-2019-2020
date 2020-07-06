import java.util.*;

public class Graph {
  public Map<Integer, Map<Integer, Integer>> vertices;
  public NodeUtil[] cenTree;
  private Map<Pair, Integer> maxW;

  public Graph(int nodeNumber) {
    vertices = new HashMap<Integer, Map<Integer, Integer>>(nodeNumber); // representation of graph
    cenTree = new NodeUtil[nodeNumber + 1]; // data structure used to save ith-node useful informations
    maxW = new HashMap<Pair, Integer>((int)(Math.log(nodeNumber)/Math.log(2))); // data structure used to store centroid
                                                                            // decomposition result
  }

  // depth first search
  private void dfs(int u, int p, int lvl, int maxans) {
    Integer mW = maxW.get(new Pair(lvl, u));
    if (mW == null) { // [lvl][u] is still undefined
      mW = 0;
    }

    // insert max between current and previous call weight
    maxW.put(new Pair(lvl, u), (mW > maxans ? mW : maxans));

    for (Integer i : vertices.get(u).keySet()) {
      if (i == p)
        continue;

      // weight of u->i edge
      int e = vertices.get(u).get(i);
      // passing the maximum value
      dfs(i, u, lvl, (maxans > e ? maxans : e));
    }
  }

  // initialization of dfs, store subnodes number of each node
  private void dfsinit(int u, int p) {

    for (Integer i : vertices.get(u).keySet()) {
      if (i == p)
        continue;

      dfsinit(i, u);
      cenTree[u].subNodes += cenTree[i].subNodes;
    }
  }

  // centroid decomposition
  protected void decompose(int u, int p, int lvl) throws StackOverflowError {
    dfsinit(u, -1);
    int centroid = findCentroid(u, -1, u);

    // save node information (parent and level)
    cenTree[centroid].parent = p;
    cenTree[centroid].level = lvl;

    // start of dfs, -1 and 0 are fictitious numbers
    dfs(centroid, -1, lvl, 0);

    for (int i : vertices.get(centroid).keySet()) {
      int cenW = vertices.get(i).get(centroid); // used to avoid the loss of i->centroid edge weight
      vertices.get(i).remove(centroid);
      decompose(i, centroid, lvl + 1); // incrase level for each tree decomposition
      vertices.get(i).put(centroid, cenW); // re-link i->centroid
    }
  }

  // find actual centroid for given root
  private int findCentroid(int u, int p, int root) {
    int ret = u;
    for (Integer i : vertices.get(u).keySet()) {
      if (i == p)
        continue;
      if (cenTree[i].subNodes > (cenTree[root].subNodes / 2))
        ret = findCentroid(i, u, root);
    }
    return ret;
  }

  // O(logn) search of maximum weight between node a and b
  // solve queries by comparing to given candidate edge weight in Main
  protected int query(int a, int b) {
    int ta = a;
    int tb = b;

    if (cenTree[ta].level > cenTree[tb].level) {
      int tmp = ta;
      ta = tb;
      tb = tmp;
    }

    // match of parent (LCA(a,b))
    while (cenTree[ta].level < cenTree[tb].level)
      tb = cenTree[tb].parent;
    
    while (ta != tb) {
      ta = cenTree[ta].parent;
      tb = cenTree[tb].parent;
    }
    // return the max weight from a to LCA and b to LCA
    int Wa = maxW.get(new Pair(cenTree[ta].level, a));
    int Wb = maxW.get(new Pair(cenTree[ta].level, b));
    return (Wa > Wb ? Wa : Wb);
  }
}

// class used to store node data
class NodeUtil {
  int parent;
  int level; // level in centroid decomposition, used in maxW
  int subNodes; // number of subnodes

  public NodeUtil() {
    this.subNodes = 1;
  }
}

// class needed to link <levelInCentroidTree, node>
class Pair {
  int lvl; // level inside centroid tree
  int v; // node

  public Pair(int lvl, int v) {
    this.lvl = lvl;
    this.v = v;
  }

  @Override
  public boolean equals(Object o) {
    if (this == o) {
      return true;
    }
    if (!(o instanceof Pair)) {
      return false;
    }
    Pair pair = (Pair) o;
    if (lvl != pair.lvl || v != pair.v) {
      return false;
    }
    return true;
  }

  @Override
  public int hashCode() {
    return (lvl * 31) + v;
  }
}
