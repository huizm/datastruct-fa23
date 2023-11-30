package lab.lab7;

import java.util.Queue;
import java.util.LinkedList;

public class ArrayBST<Key extends Comparable<Key>, Value> implements BST<Key, Value> {

    private Key[] keys;
    private Value[] vals;
    private int len, cap;
    private int deepest; // largest array index

    public ArrayBST() {
        keys = (Key[]) new Object[8];
        vals = (Value[]) new Object[8];
        len = 0;
        cap = 8;
        deepest = 0;
    }

    private void resize(int cap) {
        Key[] keys = (Key[]) new Object[cap];
        Value[] vals = (Value[]) new Object[cap];
        for (int i = 1; i <= len; i++) {
            keys[i] = this.keys[i];
            vals[i] = this.vals[i];
        }
        this.keys = keys;
        this.vals = vals;
        this.cap = cap;
    }

    private int layerNumber(int a) {
        return (int) (Math.log(a) / Math.log(2)) + 1;
    }

    @Override
    public void put(Key key, Value val) {
        int root = 1;
        while (keys[root] != null) {
            int cmp = key.compareTo(keys[root]);
            if (cmp == 0) {
                vals[root] = val;
                break;
            } else if (cmp > 0) root = root * 2 + 1;
            else                root = root * 2;
        }
        keys[root] = key;
        vals[root] = val;
        if (root > deepest) deepest = root;

        if (layerNumber(deepest) >= layerNumber(cap - 1)) resize(cap * 2);
    }

    @Override
    public Value get(Key key) {
        int root = 1;
        while (keys[root] != null) {
            int cmp = key.compareTo(keys[root]);
            if (cmp == 0)     return vals[root];
            else if (cmp > 0) root = root * 2 + 1;
            else              root = root * 2;
        }
        return null;
    }

    @Override
    public void delete(Key key) {
        int root = 1;
        while (keys[root] != null) {
            int cmp = key.compareTo(keys[root]);
            if (cmp < 0)      root = root * 2;
            else if (cmp > 0) root = root * 2 + 1;
            else {
                if (keys[root * 2 + 1] == null)  upgrade(root * 2);
                else if (keys[root * 2] == null) upgrade(root * 2 + 1);

                // replace `root` with its successor
                int successor = min(root * 2 + 1);
                keys[root] = keys[successor];
                vals[root] = vals[successor];
                
                keys[successor] = null;
                vals[successor] = null;
                len--;
                if (successor >= deepest) {
                    while (keys[--successor] == null);
                    deepest = successor;
                }

                if (layerNumber(deepest) < layerNumber(cap - 1) && cap >= 16) resize(cap / 2);
            }
        }
    }

    private void upgrade(int i) {
        if (keys[i] == null) return;

        if (i % 2 == 0) {
            keys[i / 2] = keys[i];
            vals[i / 2] = vals[i];
            keys[i] = null;
            vals[i] = null;
        } else {
            keys[(i + 1) / 2] = keys[i];
            vals[(i + 1) / 2] = vals[i];
            keys[i] = null;
            vals[i] = null;
        }

        upgrade(i * 2);
        upgrade(i * 2 + 1);
    }

    private int min(int i) {
        int root = i;
        while (keys[root * 2] != null) root = root * 2;
        return root;
    }

    @Override
    public boolean contains(Key key) {
        return get(key) != null;
    }

    @Override
    public boolean isEmpty() {
        return len == 0;
    }

    @Override
    public int size() {
        return len;
    }

    @Override
    public Key min() {
        if (len == 0) return null;

        int root = 1;
        while (keys[root * 2] != null) root = root * 2;
        return keys[root];
    }

    @Override
    public Key max() {
        if (len == 0) return null;

        int root = 1;
        while (keys[root * 2 + 1] != null) root = root * 2 + 1;
        return keys[root];
    }

    @Override
    public Key floor(Key key) {
        int root = 1;
        Key rtn = null;
        while (keys[root] != null) {
            int cmp = key.compareTo(keys[root]);
            if (cmp == 0)     return keys[root];
            else if (cmp < 0) root = root * 2;
            else {
                rtn = keys[root];
                root = root * 2 + 1;
            }
        }
        return rtn;
    }

    @Override
    public Key ceiling(Key key) {
        int root = 1;
        Key rtn = null;
        while (keys[root] != null) {
            int cmp = key.compareTo(keys[root]);
            if (cmp == 0)     return keys[root];
            else if (cmp > 0) root = root * 2 + 1;
            else {
                rtn = keys[root];
                root = root * 2;
            }
        }
        return rtn;
    }

    @Override
    public int rank(Key key) {
        int root = 1;
        int rank = 0;
        while (keys[root] != null) {
            int cmp = key.compareTo(keys[root]);
            if (cmp == 0) {
                rank += size(root * 2);
                break;
            } else if (cmp > 0) {
                rank += size(root * 2) + 1;
                root = root * 2 + 1;
            } else {
                root = root * 2;
            }
        }
        return rank;
    }

    /** return size of the subtree rooted at `keys[i]` */
    private int size(int i) {
        if (keys[i] == null) return 0;
        return size(i * 2) + size(i * 2 + 1) + 1;
    }

    @Override
    public Key select(int k) {
        int root = 1;
        int rank = 0;
        while (keys[root] != null) {
            int currentRank = rank + size(root * 2);
            if (currentRank == k)     return keys[root];
            else if (currentRank > k) root = root * 2;
            else {
                rank = currentRank + 1;
                root = root * 2 + 1;
            }
        }
        return null;
    }

    @Override
    public void deleteMin() {
        if (len == 0) return;

        int root = 1;
        while (keys[root * 2] != null) root = root * 2;
        keys[root] = null;
        vals[root] = null;
        len--;
        if (root >= deepest) {
            while (keys[--root] == null);
            deepest = root;
        }

        if (layerNumber(deepest) < layerNumber(cap - 1) && cap >= 16) resize(cap / 2);
    }

    @Override
    public void deleteMax() {
        if (len == 0) return;

        int root = 1;
        while (keys[root * 2 + 1] != null) root = root * 2 + 1;
        keys[root] = null;
        vals[root] = null;
        len--;
        if (root >= deepest) {
            while (keys[--root] == null);
            deepest = root;
        }

        if (layerNumber(deepest) < layerNumber(cap - 1) && cap >= 16) resize(cap / 2);
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
        keys(1, q, lo, hi);
        return q;
    }

    private void keys(int i, Queue<Key> q, Key lo, Key hi) {
        if (keys[i] == null) return;

        int cmplo = lo.compareTo(keys[i]);
        int cmphi = hi.compareTo(keys[i]);
        if (cmplo < 0) keys(i * 2, q, lo, hi);
        if (cmplo <= 0 && cmphi >= 0) q.add(keys[i]);
        if (cmphi > 0) keys(i * 2 + 1, q, lo, hi);
    }

    public Iterable<Key> preOrderKeys() {
        return preOrderKeys(min(), max());
    }

    public Iterable<Key> preOrderKeys(Key lo, Key hi) {
        Queue<Key> q = new LinkedList<Key>();
        preOrderKeys(1, q, lo, hi);
        return q;
    }

    private void preOrderKeys(int i, Queue<Key> q, Key lo, Key hi) {
        if (keys[i] == null) return;

        int cmplo = lo.compareTo(keys[i]);
        int cmphi = hi.compareTo(keys[i]);
        if (cmplo <= 0 && cmphi >= 0) q.add(keys[i]);
        if (cmplo < 0) preOrderKeys(i * 2, q, lo, hi);
        if (cmphi > 0) preOrderKeys(i * 2 + 1, q, lo, hi);
    }

    public Iterable<Key> postOrderKeys() {
        return postOrderKeys(min(), max());
    }

    public Iterable<Key> postOrderKeys(Key lo, Key hi) {
        Queue<Key> q = new LinkedList<Key>();
        postOrderKeys(1, q, lo, hi);
        return q;
    }

    private void postOrderKeys(int i, Queue<Key> q, Key lo, Key hi) {
        if (keys[i] == null) return;

        int cmplo = lo.compareTo(keys[i]);
        int cmphi = hi.compareTo(keys[i]);
        if (cmplo <= 0 && cmphi >= 0) q.add(keys[i]);
        if (cmplo < 0) postOrderKeys(i * 2, q, lo, hi);
        if (cmphi > 0) postOrderKeys(i * 2 + 1, q, lo, hi);
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
