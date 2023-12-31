# datastruct-fa23

The better practice is to **design your data structure and algorithms on the paper before you start to write code**, otherwise your code will be messier and messier when you write it and it will also be less portable.

---

## hw

### hw 1 Linear list

1. Deletion in contiguous list
2. Insertion in contiguous list
3. Josephus problem (linked list)
4. Classify commodities (linked list)

*hw1-1*, *hw1-2* use contiguous list and *hw1-3*, *hw1-4* use linked list. The generic implementation of linked list is in `LinkedList.c`, `LinkedList.h`.

However, due to the restrictions of the procedure-oriented nature of C, implementing a generic linked list that suits all kinds of data is next to impossible. Therefore, there are linked lists implemented inside those two solutions, respectively. And the "generic" version is just for learning purpose.

### hw 2 Linear list with restricted operations

1. Bracket matching (stack)
2. Pascal's triangle (queue)
3. Train coach rearrangement (queue)
4. Knuth-Morris-Pratt algorithm for pattern searching

### hw 3 Tree and binary tree

1. Traverse thru binary tree
2. Huffman coding
3. Balanced binary search tree
4. Max heap

### hw 4 Graph

1. Traverse thru graph
2. Shortest paths
3. Minimum spanning tree

### hw 5 Sorting

1. Shellsort
2. 2-way mergesort
3. Quicksort
4. Radix sort

*This part is especially extremely annoying. On the one hand, you have to record the state of each "round", however, those recursive algorithms don't work that way. On the other hand, you can't use any of the variants but only to reproduce a given implementation. Not to mention you spend more time reinventing the wheel than developing the algorithm.*

## (selected) proj

The course offered 13 projects out of which it requires each student to choose 5 (at least 2 with an asterisk).

1. Knapsack problem
2. Wolf, goat and cabbage problem
3. Design a simple spreadsheet
4. Eight queens problem
5. Josephus problem
6. Lesson planning (*)
7. Binary search tree and balanced binary tree (*)
8. Parking lot challenge
9. Score analysis
10. Unary sparse polynomial calculator
11. Huffman coding (*)
12. Traffic consulting system (*)
13. Maze experiment (*)
