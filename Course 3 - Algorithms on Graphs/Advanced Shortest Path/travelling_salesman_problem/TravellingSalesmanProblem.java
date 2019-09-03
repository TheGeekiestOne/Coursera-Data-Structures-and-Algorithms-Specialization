import java.util.Scanner;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.PriorityQueue;

public class TravellingSalesmanProblem {
    private static class Impl {
        // See the descriptions of these fields in the starter for friend_suggestion
        int n;
        ArrayList<Integer>[][] adj;
        ArrayList<Long>[][] cost;
        Long[][] distance;
        ArrayList<PriorityQueue<Entry>> queue;
        boolean[] visited;
        ArrayList<Integer> workset;
        final Long INFINITY = Long.MAX_VALUE / 4;
 
        // Position of the node in the node ordering
        Integer[] rank;
        // Level of the node for level heuristic in the node ordering
        Long[] level;

        Impl(int n) {
            this.n = n;
            visited = new boolean[n];
            Arrays.fill(visited, false);
            workset = new ArrayList<Integer>();
            rank = new Integer[n];
            level = new Long[n];
            distance = new Long[][] {new Long[n], new Long[n]};
            for (int i = 0; i < n; ++i) {
                distance[0][i] = distance[1][i] = INFINITY;
                level[i] = 0L;
                rank[i] = 0;
            }
            queue = new ArrayList<PriorityQueue<Entry>>();
            queue.add(new PriorityQueue<Entry>(n));
            queue.add(new PriorityQueue<Entry>(n));
        }

        // Preprocess the graph
        void preprocess() {
            // This priority queue will contain pairs (importance, node) with the least important node in the head
            PriorityQueue<Entry> q = new PriorityQueue<Entry>(n);
            // Implement this method yourself
        }

        void add_edge(int side, int u, int v, Long c) {
            for (int i = 0; i < adj[side][u].size(); ++i) {
                int w = adj[side][u].get(i);
                if (w == v) {
                    Long cc = min(cost[side][u].get(i), c);
                    cost[side][u].set(i, cc);
                    return;
                }
            }
            adj[side][u].add(v);
            cost[side][u].add(c);
        }

        void apply_shortcut(Shortcut sc) {
            add_edge(0, sc.u, sc.v, sc.cost);
            add_edge(1, sc.v, sc.u, sc.cost);
        }

        void clear() {
            for (int v : workset) {
                distance[0][v] = distance[1][v] = INFINITY;
                visited[v] = false;
            }
            workset.clear();
            queue.get(0).clear();
            queue.get(1).clear();
        }

        void mark_visited(int u) {
            visited[u] = true;
            workset.add(u);
        }

        // See the description of this method in the starter for friend_suggestion
        boolean visit(int side, int v, Long dist) {
            // Implement this method yourself
            return false;
        }                

        // Add the shortcuts corresponding to contracting node v. Return v's importance.
        Long shortcut(int v) {
            // Implement this method yourself

            // Compute the node importance in the end
            Long shortcuts = 0;
            Long vlevel = 0L;
            Long neighbors = 0L;
            Long shortcutCover = 0L;
            // Compute the correct values for the above heuristics before computing the node importance
            Long importance = (shortcuts - adj[0][v].size() - adj[1][v].size()) + neighbors + shortcutCover + vlevel;
            return importance;
        }

        // Returns the distance from s to t in the graph
        Long query(int s, int t) {
            if (s == t) {
                return 0L;
            }
            visit(0, s, 0L);
            visit(1, t, 0L);
            Long estimate = INFINITY;
            // Implement the rest of the algorithm yourself
            return estimate == INFINITY ? -1 : estimate;            
        }

        class Entry implements Comparable<Entry>
        {
            Long cost;
            int node;
          
            public Entry(Long cost, int node)
            {
                this.cost = cost;
                this.node = node;
            }
         
            public int compareTo(Entry other)
            {
                if (cost == other.cost) {
                    return node < other.node ? -1 : node > other.node ? 1: 0;
                }
                return cost < other.cost ? -1 : cost > other.cost ? 1 : 0;
            }
        }

        class Shortcut
        {
            int u;
            int v;
            Long cost;

            public Shortcut(int u, int v, Long c)
            {
                this.u = u;
                this.v = v;
                cost = c;
            }
        }
    }

    private static FastScanner in;
    private static int INF = 1000 * 1000 * 1000;

    static class FastScanner {
        private BufferedReader reader;
        private StringTokenizer tokenizer;

        public FastScanner() {
            reader = new BufferedReader(new InputStreamReader(System.in));
            tokenizer = null;
        }

        public String next() throws IOException {
            while (tokenizer == null || !tokenizer.hasMoreTokens()) {
                tokenizer = new StringTokenizer(reader.readLine());
            }
            return tokenizer.nextToken();
        }

        public int nextInt() throws IOException {
            return Integer.parseInt(next());
        }
        public Long nextLong() throws IOException {
            return Long.parseLong(next());
        }
    }

    // Returns the length of the shortest circular path visiting all the nodes of the graph at least once
    static int optimalPath(int[][] graph) {
        // Implement this method yourself
        return -1;
    }

    
    // Reads the road network and returns the adjacency matrix of the graph on the nodes we are interested in
    // with edge lengths equal to the distances between those nodes in the initial road network
    static int[][] readData(Impl ch) {
        try {
            int n = in.nextInt();
            int[] vertices = new int[n];
            int[][] graph = new int[n][n];

            for (int i = 0; i <n; ++i) {
                int u = in.nextInt();
                vertices[i] = u - 1;
            }

            for (int i = 0; i <n; ++i) {
                for (int j = 0; j < n; ++j) {
                    int l = (int) (long) ch.query(vertices[i], vertices[j]);
                    graph[i][j] = l == -1 ? INF : l;
                }
            }
            return graph;
        } catch (IOException exception) {
            System.err.print("Error during reading: " + exception.toString());
            return null;
        }
    }

    public static void main(String args[]) {
        try {
            in = new FastScanner();
            int n = in.nextInt();
            int m = in.nextInt();
            Impl ch = new Impl(n);
            ch.adj = (ArrayList<Integer>[][])new ArrayList[2][];
            ch.cost = (ArrayList<Long>[][])new ArrayList[2][];
            for (int side = 0; side < 2; ++side) {
                ch.adj[side] = (ArrayList<Integer>[])new ArrayList[n];
                ch.cost[side] = (ArrayList<Long>[])new ArrayList[n];
                for (int i = 0; i < n; i++) {
                    ch.adj[side][i] = new ArrayList<Integer>();
                    ch.cost[side][i] = new ArrayList<Long>();
                }
            }

            for (int i = 0; i < m; i++) {
                int x, y;
                Long c;
                x = in.nextInt();
                y = in.nextInt();
                c = in.nextLong();
                ch.adj[0][x - 1].add(y - 1);
                ch.cost[0][x - 1].add(c);
                ch.adj[1][y - 1].add(x - 1);
                ch.cost[1][y - 1].add(c);
            }

            ch.preprocess();
            System.out.println("Ready");

            int t = in.nextInt();

            for (int i = 0; i < t; i++) {
                int[][] graph = readData(ch);
                System.out.println(optimalPath(graph));
            }
        } catch (IOException exception) {
            System.err.print("Error during reading: " + exception.toString());
        }
    }
}
