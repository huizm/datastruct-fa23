# datastruct-fa23

The better practice is to **design your data structure and algorithms on the paper before you start to write code**, otherwise your code will be messier and messier when you write it and it will also be less portable if you implement the "ds & a" specifically to one problem.

---

## hw

### hw 1 Linear list

1. Deletion in contiguous list
2. Insertion in contiguous list
3. Joseph's problem (linked list)
4. Classify commodities (linked list)

*hw1-1*, *hw1-2* use contiguous list and *hw1-3*, *hw1-4* use linked list. The generic implementation of linked list is in `LinkedList.c`, `LinkedList.h`.

However, due to the restrictions of the procedure-oriented nature of C, implementing a generic linked list that suits all kinds of data is next to impossible. Therefore, there are linked lists implemented inside those two solutions, respectively. And the "generic" version is just for learning purpose.
