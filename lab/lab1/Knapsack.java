import java.util.List;
import java.util.ArrayList;

public class Knapsack {

    private final int T;
    private final int[] weights;
    private final int[] values;
    private List<List<Integer>> results;

    public Knapsack(int t, int[] weights) {
        this.T = t;
        this.weights = weights;
        this.values = null;
        this.results = new ArrayList<List<Integer>>();
    }

    public Knapsack(int t, int[] weights, int[] values) {
        this.T = t;
        this.weights = weights;
        this.values = values;
        this.results = new ArrayList<List<Integer>>();
    }

    public List<List<Integer>> solve() {
        List<Integer> result = new ArrayList<Integer>();
        solve(result, weights, T, 0);
        return results;
    }

    private void solve(List<Integer> result, int[] weights, int target, int start) {
        // add copy of current result
        if (target == 0) results.add(new ArrayList<Integer>(result));
        else {
            for (int i = start; i < weights.length; i++) {
                if (weights[i] <= target) {
                    // way down, recursively find all solutions
                    result.add(weights[i]);
                    solve(result, weights, target - weights[i], i + 1);

                    // way up, backtracking
                    result.remove(result.size() - 1);
                }
            }
        }
    }

    // public long[][] solve(long[] volume, long[] value) {
    //     return null;
    // }

    public static void main(String[] args) {
        int[] weights = { 1, 8, 4, 3, 5, 2 };
        int T = 10;
        Knapsack knapsack = new Knapsack(T, weights);
        System.out.println(knapsack.solve());
    }
}
