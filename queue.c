#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
 * Create empty queue.
 * Return NULL if could not allocate space.
 */
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    /* If malloc returned NULL, then the allocating is not successful and need
     * to return NULL */
    if (q == NULL) {
        printf("Can not create empty queue, malloc failed!\n");
        return NULL;
    }
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /*To free all the list elements and the strings that they contain, free the
     * string then the element one by one*/
    if (q == NULL) {
        printf("Can not free, it's NULL pointer!\n");
        return;
    }
    // In other situation, free value, save next pointer then free the list
    // element
    list_ele_t *ptr;
    ptr = q->head;  // from beginning
    while (ptr != NULL) {
        free(ptr->value);
        list_ele_t *tmp = ptr;
        ptr = ptr->next;
        free(tmp);
    }
    /* Free queue structure */
    free(q);
}

/*
 * Attempt to insert element at head of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    long int len = strlen(s) + 1;
    list_ele_t *newh;
    if (q == NULL) {
        printf("Could not insert element, it's NULL pointer!\n");
        return false;
    }
    /* Allocate space for the string and copy it */
    newh = malloc(sizeof(list_ele_t));
    if (newh == NULL) {
        printf("Allocating space for element failed!\n");
        return false;
    }
    newh->value = malloc(len);
    if (newh->value == NULL) {
        printf("Allocating space for string value failed!\n");
        free(newh);
        return false;
    }
    memcpy(newh->value, s, len);
    newh->next = q->head;
    q->head = newh;
    // If it's the first element, then this element is both the head and also
    // the tail
    if (q->size == 0)
        q->tail = newh;
    q->size++;
    return true;
}

/*
 * Attempt to insert element at tail of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    long int len = strlen(s) + 1;
    list_ele_t *newt;
    if (q == NULL) {
        printf("Could not insert element, it's NULL pointer!\n");
        return false;
    }
    /* Allocate space for the string and copy it */
    newt = malloc(sizeof(list_ele_t));
    if (newt == NULL) {
        printf("Allocating space for element failed!\n");
        return false;
    }
    newt->value = malloc(len);
    if (newt->value == NULL) {
        printf("Allocating space for string value failed!\n");
        free(newt);
        return false;
    }
    memcpy(newt->value, s, len);
    newt->next = NULL;
    // Check whether there was element in the queue or not
    if (q->size != 0)
        q->tail->next = newt;
    else
        q->head = newt;
    q->tail = newt;
    q->size++;
    return true;
}

/*
 * Attempt to remove element from head of queue.
 * Return true if successful.
 * Return false if queue is NULL or empty.
 * If sp is non-NULL and an element is removed, copy the removed string to *sp
 * (up to a maximum of bufsize-1 characters, plus a null terminator.)
 * The space used by the list element and the string should be freed.
 */
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    char *value;
    long int l_value;
    list_ele_t *ele;

    if (q == NULL) {
        printf("The queue doesn't exist!\n");
        return false;
    } else if (q->size == 0) {
        printf("No element in the queue!\n");
        return false;
    }
    ele = q->head;
    value = ele->value;
    l_value = strlen(value) + 1;
    if (sp != NULL) {
        if (l_value < bufsize) {
            memcpy(sp, value, l_value);
        } else {
            memcpy(sp, value, bufsize - 1);
            sp[bufsize - 1] = '\0';
        }
    }
    q->head = ele->next;
    /* Free the element and the string value of it.*/
    free(ele->value);
    free(ele);
    return true;
}

/*
 * Return number of elements in queue.
 * Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    if (q == NULL)
        return 0;
    return q->size;
}

/*
 * Reverse elements in queue
 * No effect if q is NULL or empty
 * This function should not allocate or free any list elements
 * (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
 * It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    if (q == NULL) {
        printf("Pointer of the queue is NULL. Couldn't reverse!\n");
        return;
    } else if (q->size == 0) {
        printf("Queue is empty. Couldn't reverse!\n");
        return;
    }
    list_ele_t *ele, *ele_next, *tmp;
    ele = q->head;
    ele_next = ele->next;
    while (ele_next != NULL) {
        tmp = ele_next->next;
        ele_next->next = ele;
        ele = ele_next;
        ele_next = tmp;
    }
    tmp = q->head;
    q->head = q->tail;
    q->tail = tmp;
    tmp->next = NULL;
}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
void q_sort(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
}
