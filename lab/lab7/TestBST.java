import org.junit.Before;
import org.junit.After;
import org.junit.Test;
import static org.junit.Assert.*;

import java.io.ByteArrayOutputStream;
import java.io.PrintStream;

public class TestBST {

    private BST<Integer, String> bst;
    private final PrintStream systemOut = System.out;

    @Before
    public void setup() {
        // bst = new LinkedListBST<Integer, String>();
        bst = new ArrayBST<Integer, String>();
        // bst = new RedBlackBST<Integer, String>();
        // bst = new ArrayBalancedST<Integer, String>();
        bst.put(3, "Three");
        bst.put(1, "One");
        bst.put(2, "Two");
        bst.put(5, "Five");
        bst.put(4, "Four");
    }

    @After
    public void restoreStreams() {
        System.setOut(systemOut);
    }

    @Test
    public void testPutAndGet() {
        assertEquals("One", bst.get(1));
        assertEquals("Two", bst.get(2));
        assertEquals("Three", bst.get(3));
        assertEquals("Four", bst.get(4));
        assertEquals("Five", bst.get(5));
    }

    @Test
    public void testSize() {
        assertEquals(5, bst.size());
    }

    @Test
    public void testDelete() {
        bst.delete(1);
        assertNull(bst.get(1));
        assertEquals(4, bst.size());
    }

    @Test
    public void testContains() {
        assertTrue(bst.contains(1));
        assertFalse(bst.contains(6));
    }

    @Test
    public void testIsEmpty() {
        assertFalse(bst.isEmpty());
        bst.delete(1);
        bst.delete(2);
        bst.delete(3);
        bst.delete(4);
        bst.delete(5);
        assertTrue(bst.isEmpty());
    }

    @Test
    public void testKeys() {
        int lastKey = Integer.MIN_VALUE;
        for (int key : bst.keys()) {
            assertTrue(key > lastKey);
            lastKey = key;
        }
    }

    @Test
    public void testMinMax() {
        assertEquals((Integer)1, bst.min());
        assertEquals((Integer)5, bst.max());
    }

    @Test
    public void testFloorCeiling() {
        assertEquals((Integer)3, bst.floor(3));
        assertEquals((Integer)3, bst.ceiling(3));
        assertNull(bst.floor(0));
        assertNull(bst.ceiling(6));
    }

    @Test
    public void testRankAndSelect() {
        assertEquals(0, bst.rank(1));
        assertEquals(4, bst.rank(5));
        assertEquals((Integer)1, bst.select(0));
        assertEquals((Integer)5, bst.select(4));
    }

    @Test
    public void testDeleteMinAndMax() {
        bst.deleteMin();
        bst.deleteMax();
        assertEquals((Integer)2, bst.min());
        assertEquals((Integer)4, bst.max());
        assertEquals(3, bst.size());
    }

    @Test
    public void testSizeBetweenKeys() {
        assertEquals(3, bst.size(2, 4));
    }

    @Test
    public void testKeysBetweenKeys() {
        int lastKey = 1;
        for (int key : bst.keys(2, 4)) {
            assertTrue(key > lastKey);
            assertTrue(key >= 2 && key <= 4);
            lastKey = key;
        }
    }

    @Test
    public void testPreOrderPrint() {
        ByteArrayOutputStream outContent = new ByteArrayOutputStream();
        System.setOut(new PrintStream(outContent));
        bst.preOrderPrint();
        assertEquals("3 1 2 5 4 ", outContent.toString());
    }

    @Test
    public void testInOrderPrint() {
        ByteArrayOutputStream outContent = new ByteArrayOutputStream();
        System.setOut(new PrintStream(outContent));
        bst.inOrderPrint();
        assertEquals("1 2 3 4 5 ", outContent.toString());
    }

    @Test
    public void testPostOrderPrint() {
        ByteArrayOutputStream outContent = new ByteArrayOutputStream();
        System.setOut(new PrintStream(outContent));
        bst.postOrderPrint();
        assertEquals("2 1 4 5 3 ", outContent.toString());
    }
}
