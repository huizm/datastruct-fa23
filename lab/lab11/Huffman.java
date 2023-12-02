import edu.princeton.cs.algs4.*;

public class Huffman {
    
    private static final int R = 256;

    private static class Node implements Comparable<Node> {

        private char ch;
        private int freq; // frequence of appearence, for building trie only
        private final Node left, right;

        public Node(char ch, int freq, Node left, Node right) {
            this.ch = ch;
            this.freq = freq;
            this.left = left;
            this.right = right;
        }

        public boolean isLeaf() {
            return left == null && right == null;
        }

        public int compareTo(Node that) {
            return this.freq - that.freq;
        }
    }

    public static void compress() {
        String s = BinaryStdIn.readString();
        char[] input = s.toCharArray();

        // construct frequency table, self-indexed
        int[] freq = new int[R];
        for (int i = 0; i < input.length; i++) freq[input[i]]++;

        // build Huffman trie
        Node root = buildTrie(freq);

        // build code table from trie, self-indexed
        String[] st = buildCode(root);

        // write trie to output
        writeTrie(root);

        // write number of chars to output
        BinaryStdOut.write(input.length);

        // write code string to output
        for (int i = 0; i < input.length; i++) {
            // get code from table
            String code = st[input[i]];

            for (int j = 0; j < code.length(); j++) {
                if (code.charAt(j) == '1') BinaryStdOut.write(true);
                else BinaryStdOut.write(false);
            }
        }

        BinaryStdOut.close();
    }

    public static void expand() {
        Node root = readTrie();
        int n = BinaryStdIn.readInt(); // number of chars
        for (int i = 0; i < n; i++) {
            Node x = root;
            while (!x.isLeaf()) {
                if (BinaryStdIn.readBoolean() == true) x = x.right;
                else x = x.left;
            }
            BinaryStdOut.write(x.ch);
        }
        BinaryStdOut.close();
    }

    private static Node buildTrie(int[] freq) {
        // maintain priority queue by minimum frequency
        MinPQ<Node> pq = new MinPQ<Node>();

        // build forest of singleton trees
        for (char c = 0; c < R; c++) {
            if (freq[c] > 0) pq.insert(new Node(c, freq[c], null, null));
        }

        // merge smallest two trees into one
        while (pq.size() > 1) {
            Node x = pq.delMin();
            Node y = pq.delMin();
            Node parent = new Node('\0', x.freq + y.freq, x, y);
            pq.insert(parent);
        }

        return pq.delMin();
    }

    /** build symble table from trie, for encoding */
    private static String[] buildCode(Node root) {
        String[] st = new String[R];
        buildCode(st, root, "");
        return st;
    }

    private static void buildCode(String[] st, Node x, String s) {
        if (x.isLeaf()) {
            st[x.ch] = s;
            return;
        }
        buildCode(st, x.left, s + '0');
        buildCode(st, x.right, s + '1');
    }

    private static void writeTrie(Node x) {
        // use a single bit to mark whether current node is leaf
        if (x.isLeaf()) {
            BinaryStdOut.write(true);
            BinaryStdOut.write(x.ch);
            return;
        }
        BinaryStdOut.write(false);
        writeTrie(x.left);
        writeTrie(x.right);
    }

    private static Node readTrie() {
        // reads a single bit to decide which type of node comes next
        if (BinaryStdIn.readBoolean() == true) {
            return new Node(BinaryStdIn.readChar(), 0, null, null);
        }

        // recursively read nodes if hit internal node
        return new Node('\0', 0, readTrie(), readTrie());
    }

    public static void main(String[] args) {
        if (args[0].equals("-")) compress();
        else if (args[0].equals("+")) expand();
    }
}
