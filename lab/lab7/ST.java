package lab.lab7;

public interface ST<Key extends Comparable<Key>, Value> {
    
    void put(Key key, Value val);

    Value get(Key key);

    void delete(Key key);

    boolean contains(Key key);

    boolean isEmpty();

    int size();

    Key min();

    Key max();

    /** largest key that is at most `key` */
    Key floor(Key key);

    /** smallest key that is at least `key` */
    Key ceiling(Key key);

    /** number of keys less than `key` */
    int rank(Key key);

    /** key of rank `k` */
    Key select(int k);

    void deleteMin();

    void deleteMax();

    /** number of keys between `lo` and `hi` */
    int size(Key lo, Key hi);

    /** all keys between `lo` and `hi` in sorted order */
    Iterable<Key> keys(Key lo, Key hi);

    /** all keys in sorted order */
    Iterable<Key> keys();
}
