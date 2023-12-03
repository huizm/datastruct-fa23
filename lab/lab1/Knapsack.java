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
        if (values == null) {
            List<Integer> result = new ArrayList<Integer>();
            solve(result, weights, T, 0);
        } else {
            findMaxValue();
        }
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

    public List<List<Integer>> findMaxValue() {
        int n = weights.length;
        int[][] dp = new int[n + 1][T + 1]; // max value for selected items from first `i` with weight no more than `j`
        boolean[][] path = new boolean[n + 1][T + 1]; // whether current item chosen at state `i`

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= T; j++) {
                if (weights[i - 1] <= j && dp[i - 1][j] < dp[i - 1][j - weights[i - 1]] + values[i - 1]) {
                    dp[i][j] = dp[i - 1][j - weights[i - 1]] + values[i - 1];
                    path[i][j] = true;  // item `i` added 
                } else {
                    dp[i][j] = dp[i - 1][j];
                }
            }
        }

        int maxWeight = T;
        List<Integer> result = new ArrayList<Integer>();

        for (int i = n; i > 0; i--) {
            if (path[i][maxWeight]) {
                result.add(weights[i-1]);
                maxWeight -= weights[i-1];
            }
        }
        results.add(result);
        return results;
    }

    public static void main(String[] args) {
        int[] weights = { 1, 8, 4, 3, 5, 2 };
        int[] values = { 2, 5, 3, 4, 8, 1 };
        int T = 10;
        // Knapsack knapsack = new Knapsack(T, weights);
        Knapsack knapsack = new Knapsack(T, weights, values);
        System.out.println(knapsack.solve());
    }
}
