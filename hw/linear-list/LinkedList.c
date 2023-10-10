// generic implementation of linked list, for learning purpose only

#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"

/**
 * Initialize a linked list.
 * @return pointer to list
 */
List *InitList(void) {
    List *l = (List *)malloc(sizeof(List));
    l->head = NULL;
    l->Size = 0L;
    return l;
}

/**
 * Free the space used by linked list.
 * @param l
 */
void DestroyList(List * restrict l) {
    while (l->Size > 0) {
        RemoveFromList(l, 0);
    }
    free(l);
}

/**
 * Insert data to linked list `l` at position `pos`.
 * @param l
 * @param data MUST be `const restrict` (please see README.md for why)
 * @param pos starts from 0
 * @return
 */
void InsertToList(List * restrict l, void * data, const long pos) {
    if (pos >= l->Size || pos < 0) {
        perror("index out of bounds");
        exit(-1);
    }

    Node * newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;

    if (pos == 0) {
        newNode->next = l->head;
        l->head = newNode;
    } else {
        // locate to previous node
        Node *prev = l->head;
        for (int i=0; i<pos; i++) {
            prev = prev->next;
        }

        newNode->next = prev->next;
        prev->next = newNode;
    }

    l->Size++;
}

/**
 * Remove node from linked list `l` at position `pos`. Note that this function
 * removes node only and do not touch the data.
 * @param l
 * @param pos starts from 0
 * @return pointer to data removed
 */
void *RemoveFromList(List * restrict l, long pos) {
    if (pos >= l->Size || pos < 0) {
        perror("index out of bounds");
        exit(-1);
    }

    void *data;
    Node *temp;
    if (pos == 0) {
        temp = l->head;
        l->head = l->head->next;
        data = temp->data;
        free(temp);
    } else {
        // locate to previous node
        Node *prev = l->head;
        for (int i=0; i<pos; i++) {
            prev = prev->next;
        }

        temp = prev->next;
        prev->next = prev->next->next;
        data = temp->data;
        free(temp);
    }

    l->Size--;
    return data;
}
