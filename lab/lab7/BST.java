package lab.lab7;

public interface BST<Key extends Comparable<Key>, Value> extends ST<Key, Value> {

    void preOrderPrint();

    void inOrderPrint();

    void postOrderPrint();
}
