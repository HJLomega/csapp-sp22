/**
 * @file queue.c
 * @brief Implementation of a queue that supports FIFO and LIFO operations.
 *
 * This queue implementation uses a singly-linked list to represent the
 * queue elements. Each queue element stores a string value.
 *
 * Assignment for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Extended to store strings, 2018
 *
 * TODO: fill in your name and Andrew ID
 * @author XXX <XXX@andrew.cmu.edu>
 */

#include "queue.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**
 * @brief Allocates a new queue
 * @return The new queue, or NULL if memory allocation failed
 */
queue_t *queue_new(void) {
    queue_t *q = malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if (q == NULL) {
        return NULL;
    }
    q->head = NULL;
    q->end = NULL;
    q->size = 0;
    return q;
}

/**
 * @brief Frees all memory used by a queue
 * @param[in] q The queue to free
 */
void queue_free(queue_t *q) {
    /* How about freeing the list elements and the strings? */
    list_ele_t *ele = q->head;
    while (ele) {
        free(ele->value);
        ele = ele->next;
    }
    /* Free queue structure */
    free(q);
}

/**
 * @brief Attempts to insert an element at head of a queue
 *
 * This function explicitly allocates space to create a copy of `s`.
 * The inserted element points to a copy of `s`, instead of `s` itself.
 *
 * @param[in] q The queue to insert into
 * @param[in] s String to be copied and inserted into the queue
 *
 * @return true if insertion was successful
 * @return false if q is NULL, or memory allocation failed
 */
bool queue_insert_head(queue_t *q, const char *s) {
    list_ele_t *newh;
    /* What should you do if the q is NULL? */
    if (!q) {
        return false;
    }
    newh = malloc(sizeof(list_ele_t));
    if (!newh) {
        return false;
    }
    /* Don't forget to allocate space for the string and copy it */
    char *string;
    string = malloc(sizeof(char) * (1 + strlen(s)));
    /* What if either call to malloc returns NULL? */
    if (!string) {
        free(newh);
        return false;
    }
    strcpy(string, s);
    newh->value = string;

    newh->next = q->head;
    q->head = newh;
    if (q->size == 0) {
        q->end = newh;
    }
    q->size += 1;
    return true;
}

/**
 * @brief Attempts to insert an element at tail of a queue
 *
 * This function explicitly allocates space to create a copy of `s`.
 * The inserted element points to a copy of `s`, instead of `s` itself.
 *
 * @param[in] q The queue to insert into
 * @param[in] s String to be copied and inserted into the queue
 *
 * @return true if insertion was successful
 * @return false if q is NULL, or memory allocation failed
 */
bool queue_insert_tail(queue_t *q, const char *s) {
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    list_ele_t *newh;
    /* What should you do if the q is NULL? */
    if (!q) {
        return false;
    }
    newh = malloc(sizeof(list_ele_t));
    if (!newh) {
        return false;
    }
    /* Don't forget to allocate space for the string and copy it */
    char *string;
    string = malloc(sizeof(char) * (1 + strlen(s)));
    /* What if either call to malloc returns NULL? */
    if (!string) {
        free(newh);
        return false;
    }
    strcpy(string, s);
    newh->value = string;
    newh->next = NULL;

    if (q->size == 0) {
        q->end = newh;
        q->head = newh;
        return true;
    }
    q->end->next = newh;
    q->end = q->end->next;
    q->size += 1;
    return true;
}

/**
 * @brief Attempts to remove an element from head of a queue
 *
 * If removal succeeds, this function frees all memory used by the
 * removed list element and its string value before returning.
 *
 * If removal succeeds and `buf` is non-NULL, this function copies up to
 * `bufsize - 1` characters from the removed string into `buf`, and writes
 * a null terminator '\0' after the copied string.
 *
 * @param[in]  q       The queue to remove from
 * @param[out] buf     Output buffer to write a string value into
 * @param[in]  bufsize Size of the buffer `buf` points to
 *
 * @return true if removal succeeded
 * @return false if q is NULL or empty
 */
bool queue_remove_head(queue_t *q, char *buf, size_t bufsize) {
    /* You need to fix up this code. */
    list_ele_t *removed = q->head;
    if (buf) {
        strncpy(buf, removed->value, bufsize - 1);
        buf[bufsize - 1] = '\0';
    }
    q->head = q->head->next;
    free(removed->value);
    free(removed);
    return true;
}

/**
 * @brief Returns the number of elements in a queue
 *
 * This function runs in O(1) time.
 *
 * @param[in] q The queue to examine
 *
 * @return the number of elements in the queue, or
 *         0 if q is NULL or empty
 */
size_t queue_size(queue_t *q) {
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    return (size_t)q->size;
}

/**
 * @brief Reverse the elements in a queue
 *
 * This function does not allocate or free any list elements, i.e. it does
 * not call malloc or free, including inside helper functions. Instead, it
 * rearranges the existing elements of the queue.
 *
 * @param[in] q The queue to reverse
 */
void queue_reverse(queue_t *q) {
    /* You need to write the code for this function */
    if (q == NULL) {
        return;
    }
    if (q->size == 0 || q->size == 1) {
        return;
    }
    q->end = q->head;

    list_ele_t *reversed_first = q->head;
    list_ele_t *remained_first = q->head->next;
    list_ele_t *ele_to_add;
    while (remained_first) {
        ele_to_add = remained_first;
        remained_first = remained_first->next;
        ele_to_add->next = reversed_first;
        reversed_first = ele_to_add;
    }
    q->head = reversed_first;
    q->end->next = NULL;
}

/*int main (void){
        queue_t *q = queue_new();
        printf("%d\n",queue_size(q));
        queue_insert_head(q,"a");
        printf("%d\n",queue_size(q));
        queue_insert_head(q,"b");
        printf("%d\n",queue_size(q));
        queue_insert_head(q,"c");
        printf("%d\n",queue_size(q));
        char buf[2];
        queue_remove_head(q,buf,2);
        printf("%s\n",buf);
        queue_remove_head(q,buf,2);
        printf("%s\n",buf);
        queue_remove_head(q,buf,2);
        printf("%s\n",buf);
}
*/
