#ifndef DATASTRUCTFA23_LINKEDLIST_H
#define DATASTRUCTFA23_LINKEDLIST_H

typedef struct node {
    void *data;
    struct node *next;
} Node;

typedef struct list {
    Node *head;
    long Size;
} List;

List *InitList(void);
void DestroyList(List * restrict l);
void InsertToList(List * restrict l, void * data, long pos);
void *RemoveFromList(List * restrict l, long pos);
// void ShowList(const List * restrict l); // leave the implementation to client

#endif
