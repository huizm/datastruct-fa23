import java.util.LinkedList;
import java.util.Queue;

public class Solution {
    
    private int[] pre = new int[16]; // previous state of current state, self indexed
    private boolean[] visited = new boolean[16];
    private Queue<Integer> queue = new LinkedList<Integer>();
    private String[] items =  {"白菜", "羊", "狼", "农夫"};

    public void solve() {
        pre[0] = -1;
        visited[0] = true;
        queue.add(0);

        while (!queue.isEmpty()) {
            int cur = queue.poll();

            if (cur == 15) {
                printResult();
                return;
            }

            for (int i = 0; i < 4; i++) {
                // let item `i` cross the river with peasant
                int next = cur ^ ((1 << i) | (1 << 3));

                // test whether is valid state, and not visited
                if (isValid(next) && !visited[next]) {
                    pre[next] = cur;
                    visited[next] = true;
                    queue.add(next);
                }
            }
        }
    }

    private boolean isValid(int state) {
        // (state >> 3) & 1 -> peasant
        // (state >> 2) & 1 -> wolf
        // (state >> 1) & 1 -> sheep
        // (state) & 1      -> cabbage
        if ((state & 1) == ((state >> 1) & 1) && (((state >> 3) & 1) != ((state >> 1) & 1))) return false;
        if (((state >> 1) & 1) == ((state >> 2) & 1) && (((state >> 3) & 1) != ((state >> 2) & 1))) return false;
        return true;
    }

    private void printResult() {
        int state = 15;
        LinkedList<String> result = new LinkedList<String>();
        while (state != -1) {
            result.addFirst(stateToString(state));
            state = pre[state];
        }
        for (String s : result) {
            System.out.println(s);
        }
    }

    private String stateToString(int state) {
        StringBuilder sb = new StringBuilder("南岸: ");
        for (int i = 3; i >= 0; i--) {
            if (((state >> i) & 1) == 0)
                sb.append(items[i]).append(" ");
        }
        sb.append(", 北岸: ");
        for (int i = 3; i >= 0; i--) {
            if (((state >> i) & 1) == 1)
                sb.append(items[i]).append(" ");
        }
        return sb.toString();
    }

    public static void main(String[] args) {
        Solution solution = new Solution();
        solution.solve();
    }
}
