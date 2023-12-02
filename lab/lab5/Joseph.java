import java.util.Queue;
import java.util.LinkedList;

public class Joseph {

    private static Joseph joseph = new Joseph();

    private class Node {

        private final int number;
        private final int code;
        private Node next;

        public Node(int number, int code) {
            this.number = number;
            this.code = code;
        }
    }

    public static Iterable<Integer> play(int M, int[] codes) {
        if (codes.length == 0) return null;

        Queue<Integer> seq = new LinkedList<Integer>();

        // construct ring
        Node sentinel = joseph.new Node(0, 0);
        Node prev = sentinel;
        int i = 0;
        for (int code : codes) {
            prev.next = joseph.new Node(++i, code);
            prev = prev.next;
        }
        prev.next = sentinel.next;

        // play the game
        Node current = sentinel;
        int count = 0;
        while (seq.size() < codes.length) {
            Node last = current;
            current = current.next;
            count++;

            if (count == M) {
                seq.add(current.number);
                M = current.code;
                last.next = current.next;
                current = last;
                count = 0;
            }
        }

        return seq;
    }

    public static void main(String[] args) {
        int m = 20;
        int[] codes = { 3, 1, 7, 2, 4, 8, 4 };
        Iterable<Integer> seq = play(m, codes);
        for (int n : seq) {
            System.out.printf("%d ", n);
        }
    }
}
