package lab.lab7;

import java.util.Queue;
import java.util.LinkedList;

public class LinkedListBST<Key extends Comparable<Key>, Value> implements BST<Key, Value> {
    
    private Node root;

    private class Node {

        private Key key;
        private Value val;
        private Node left, right; // links to subtrees
        private int n; // node count in subtree rooted here

        public Node(Key key, Value val, int n) {
            this.key = key;
            this.val = val;
            this.n = n;
        }
    }

    public LinkedListBST() {
        root = null;
    }

    @Override
    public void put(Key key, Value val) {
        root = put(root, key, val);
    }

    private Node put(Node x, Key key, Value val) {
        if (x == null) return new Node(key, val, 1);

        // way down the tree
        int cmp = key.compareTo(x.key);
        if (cmp < 0)      x.left = put(x.left, key, val);
        else if (cmp > 0) x.right = put(x.right, key, val);
        else              x.val = val;

        // way up the tree, update `n`
        x.n = size(x.left) + size(x.right) + 1;
        return x;
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
    public void delete(Key key) {
        root = delete(root, key);
    }

    private Node delete(Node x, Key key) {
        if (x == null) return null;

        int cmp = key.compareTo(x.key);
        if (cmp < 0)      return delete(x.left, key);
        else if (cmp > 0) return delete(x.right, key);
        else {
            if (x.right == null)     return x.right;
            else if (x.left == null) return x.left;
            
            // replace `x` with its successor
            Node t = x;
            x = min(t.right);
            x.right = deleteMin(t.right); // remove successor from right subtree and point x to right subtree
            x.left = t.left;
        }

        // way up the tree, update number of nodes in the subtree
        x.n = size(x.left) + size(x.right) + 1;
        return x;
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
        return floor(root, key).key;
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
        return ceiling(root, key).key;
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
    public void deleteMin() {
        root = deleteMin(root);
    }

    private Node deleteMin(Node x) {
        if (x.left == null) return x.right;

        // way down the tree, find min node and delete
        // way up the tree, update subtree root and number of nodes in the subtree on the path
        x.left = deleteMin(x.left);
        x.n = size(x.left) + size(x.right) + 1;
        return x;
    }

    @Override
    public void deleteMax() {
        root = deleteMax(root);
    }

    private Node deleteMax(Node x) {
        if (x.right == null) return x.right;

        x.right = deleteMax(x.right);
        x.n = size(x.left) + size(x.right) + 1;
        return x;
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
        if (cmplo < 0) keys(x.left, q, lo, hi);
        if (cmphi > 0) keys(x.right, q, lo, hi);
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
        if (cmplo < 0) keys(x.left, q, lo, hi);
        if (cmphi > 0) keys(x.right, q, lo, hi);
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
