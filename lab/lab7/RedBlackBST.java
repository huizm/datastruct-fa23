import java.util.LinkedList;
import java.util.Queue;

public class RedBlackBST<Key extends Comparable<Key>, Value> implements BST<Key, Value> {
    
    private static final boolean RED = true;
    private static final boolean BLACK = false;
    private Node root;

    private class Node {

        private boolean color;
        private Node left, right;
        private Key key;
        private Value val;
        private int n; // node count in subtree rooted here

        private Node(Key key, Value val, int n, boolean color) {
            this.key = key;
            this.val = val;
            this.n = n;
            this.color = color;
        }
    }

    public RedBlackBST() {
        root = null;
    }

    private boolean isRed(Node h) {
        if (h == null) return false; // default black
        return h.color;
    }

    /** rotate right leaning red link to left leaning */
    private Node rotateLeft(Node h) {
        Node x = h.right;
        h.right = x.left;
        x.left = h;

        x.color = h.color;
        h.color = RED;

        x.n = h.n;
        h.n = size(h.left) + size(h.right) + 1;
        return x;
    }

    /** rotate left leaning red link to right leaning */
    private Node rotateRight(Node h) {
        Node x = h.left;
        h.left = x.right;
        x.right = h;

        x.color = h.color;
        h.color = RED;

        x.n = h.n;
        h.n = size(h.left) + size(h.right) + 1;
        return x;
    }

    private void flipColors(Node h) {
        h.color = !h.color;
        h.left.color = !h.left.color;
        h.right.color = !h.right.color;
    }

    @Override
    public void put(Key key, Value val) {
        root = put(root, key, val);
        root.color = BLACK;
    }

    private Node put(Node h, Key key, Value val) {
        // create and insert new node at the bottom
        if (h == null) return new Node(key, val, 1, RED);

        // way down the tree
        int cmp = key.compareTo(h.key);
        if (cmp < 0)      h.left = put(h.left, key, val);
        else if (cmp > 0) h.right = put(h.right, key, val);
        else              h.val = val;

        // way up the tree, update `color` and `n` on the path
        if (isRed(h.right) && !isRed(h.left)) h = rotateLeft(h);
        if (isRed(h.left) && isRed(h.left.left)) h = rotateRight(h);
        if (isRed(h.left) && isRed(h.right)) flipColors(h);

        h.n = size(h.left) + size(h.right) + 1;
        return h;
    }

    @Override
    public void delete(Key key) {
        if (!isRed(root.left) && !isRed(root.right)) root.color = RED;
        root = delete(root, key);
        if (!isEmpty()) root.color = BLACK;
    }

    private Node delete(Node h, Key key) {
        if (key.compareTo(h.key) < 0) {
            if (!isRed(h.left) && !isRed(h.left.left)) h = moveRedLeft(h);
            h.left = delete(h.left, key);
        } else {
            if (isRed(h.left)) h = rotateRight(h);
            if (key.compareTo(h.key) == 0 && h.right == null) return null;
            if (!isRed(h.right) && !isRed(h.right.left)) h = moveRedRight(h);
            if (key.compareTo(h.key) == 0) {
                h.val = get(h.right, min(h.right).key);
                h.key = min(h.right).key;
                h.right = deleteMin(h.right);
            } else h.right = delete(h.right, key);
        }
        return balance(h);
    }

    @Override
    public void deleteMin() {
        if (!isRed(root.left) && !isRed(root.right)) root.color = RED;
        root = deleteMin(root);
        if (!isEmpty()) root.color = BLACK;
    }

    private Node deleteMin(Node h) {
        if (h.left == null) return null;

        if (!isRed(h.left) && !isRed(h.left.left)) h = moveRedLeft(h);
        h.left = deleteMin(h.left);
        return balance(h);
    }

    private Node moveRedLeft(Node h) {
        flipColors(h);
        if (isRed(h.right.left)) {
            h.right = rotateRight(h.right);
            h = rotateLeft(h);
        }
        return h;
    }

    private Node balance(Node h) {
        if (isRed(h.right)) h = rotateLeft(h);

        // way up the tree, update `color` and `n` on the path
        if (isRed(h.right) && !isRed(h.left)) h = rotateLeft(h);
        if (isRed(h.left) && isRed(h.left.left)) h = rotateRight(h);
        if (isRed(h.left) && isRed(h.right)) flipColors(h);

        h.n = size(h.left) + size(h.right) + 1;
        return h;
    }

    @Override
    public void deleteMax() {
        if (!isRed(root.left) && !isRed(root.right)) root.color = RED;
        root = deleteMax(root);
        if (!isEmpty()) root.color = BLACK;
    }

    private Node deleteMax(Node h) {
        if (isRed(h.left)) h = rotateRight(h);
        if (h.right == null) return null;
        if (!isRed(h.right) && !isRed(h.right.left)) h = moveRedRight(h);
        h.right = deleteMax(h.right);
        return balance(h);
    }

    private Node moveRedRight(Node h) {
        flipColors(h);
        if (isRed(h.left.left)) {
            h = rotateRight(h);
        }
        return h;
    }

    @Override
    public Value get(Key key) {
        return get(root, key);
    }

    private Value get(Node x, Key key) {
        if (x == null) return null;

        // way down the tree
        int cmp = key.compareTo(x.key);
        if (cmp < 0)      return get(x.left, key);
        else if (cmp > 0) return get(x.right, key);
        else              return x.val;
    }

    @Override
    public boolean contains(Key key) {
        return get(key) != null;
    }

    @Override
    public boolean isEmpty() {
        return root == null;
    }

    @Override
    public int size() {
        return size(root);
    }

    private int size(Node x) {
        if (x == null) return 0;
        return x.n;
    }

    @Override
    public Key min() {
        if (root == null) return null;
        return min(root).key;
    }

    private Node min(Node x) {
        if (x.left == null) return x;
        else                return min(x.left);
    }

    @Override
    public Key max() {
        if (root == null) return null;
        return max(root).key;
    }

    private Node max(Node x) {
        if (x.right == null) return x;
        else                 return max(x.right);
    }

    @Override
    public Key floor(Key key) {
        Node flNode = floor(root, key);
        if (flNode == null) return null;
        else return flNode.key;
    }

    private Node floor(Node x, Key key) {
        if (x == null) return null;

        // way down the tree
        int cmp = key.compareTo(x.key);
        if (cmp == 0)     return x;
        else if (cmp < 0) return floor(x.left, key);
        else {
            // if `floor` not found in right subtree, return `x`
            Node t = floor(x.right, key);
            if (t == null) return x;
            else return t;
        }
    }

    @Override
    public Key ceiling(Key key) {
        Node clNode = ceiling(root, key);
        if (clNode == null) return null;
        else return clNode.key;
    }

    private Node ceiling(Node x, Key key) {
        if (x == null) return null;

        int cmp = key.compareTo(x.key);
        if (cmp == 0)     return x;
        else if (cmp > 0) return ceiling(x.right, key);
        else {
            Node t = ceiling(x.left, key);
            if (t == null) return x;
            else return t;
        }
    }

    @Override
    public int rank(Key key) {
        return rank(root, key);
    }

    private int rank(Node x, Key key) {
        if (x == null) return 0;

        int cmp = key.compareTo(x.key);
        if (cmp == 0)     return size(x.left);
        else if (cmp < 0) return rank(x.left, key);
        else              return size(x.left) + 1 + rank(x.right, key);
    }

    @Override
    public Key select(int k) {
        return select(root, k).key;
    }

    private Node select(Node x, int k) {
        if (x == null) return null;

        int r = size(x.left);
        if (k == r)     return x;
        else if (k < r) return select(x.left, k);
        else            return select(x.right, k - r - 1);
    }

    @Override
    public int size(Key lo, Key hi) {
        Iterable<Key> keys = keys(lo, hi);
        int count = 0;
        for (Key key : keys) count++;
        return count;
    }

    @Override
    public Iterable<Key> keys() {
        return keys(min(), max());
    }

    @Override
    public Iterable<Key> keys(Key lo, Key hi) {
        Queue<Key> q = new LinkedList<Key>();
        keys(root, q, lo, hi);
        return q;
    }

    private void keys(Node x, Queue<Key> q, Key lo, Key hi) {
        if (x == null) return;

        int cmplo = lo.compareTo(x.key);
        int cmphi = hi.compareTo(x.key);
        if (cmplo < 0) keys(x.left, q, lo, hi);
        if (cmplo <= 0 && cmphi >= 0) q.add(x.key);
        if (cmphi > 0) keys(x.right, q, lo, hi);
    }

    public Iterable<Key> preOrderKeys() {
        return preOrderKeys(min(), max());
    }

    public Iterable<Key> preOrderKeys(Key lo, Key hi) {
        Queue<Key> q = new LinkedList<Key>();
        preOrderKeys(root, q, lo, hi);
        return q;
    }

    private void preOrderKeys(Node x, Queue<Key> q, Key lo, Key hi) {
        if (x == null) return;

        int cmplo = lo.compareTo(x.key);
        int cmphi = hi.compareTo(x.key);
        if (cmplo <= 0 && cmphi >= 0) q.add(x.key);
        if (cmplo < 0) preOrderKeys(x.left, q, lo, hi);
        if (cmphi > 0) preOrderKeys(x.right, q, lo, hi);
    }

    public Iterable<Key> postOrderKeys() {
        return postOrderKeys(min(), max());
    }

    public Iterable<Key> postOrderKeys(Key lo, Key hi) {
        Queue<Key> q = new LinkedList<Key>();
        postOrderKeys(root, q, lo, hi);
        return q;
    }

    private void postOrderKeys(Node x, Queue<Key> q, Key lo, Key hi) {
        if (x == null) return;

        int cmplo = lo.compareTo(x.key);
        int cmphi = hi.compareTo(x.key);
        if (cmplo < 0) postOrderKeys(x.left, q, lo, hi);
        if (cmphi > 0) postOrderKeys(x.right, q, lo, hi);
        if (cmplo <= 0 && cmphi >= 0) q.add(x.key);
    }

    @Override
    public void preOrderPrint() {
        Iterable<Key> keys = preOrderKeys();
        for (Key key : keys) System.out.printf("%s ", key.toString());
    }

    @Override
    public void inOrderPrint() {
        Iterable<Key> keys = keys();
        for (Key key : keys) System.out.printf("%s ", key.toString());
    }

    @Override
    public void postOrderPrint() {
        Iterable<Key> keys = postOrderKeys();
        for (Key key : keys) System.out.printf("%s ", key.toString());
    }
}
