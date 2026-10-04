/*
 * File: mylinkedlist.c
 *   ...
 * YOU NEED TO IMPLEMENT THE FUNCTIONS  here
 * ....
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mylinkedlist.h"

/*
 * Function: NewStudentCell
 * Usage: student_cell_T *element;
 *        element = NewStudentCell(int id, double gpa, char *name);
 * --------------------------
 * This function allocates space for a student cell and intilize its fileds
 */
student_cell_T *NewStudentCell(char *id, double gpa, char *name)
{
    student_cell_T *element;
  
    element = (student_cell_T *) malloc(sizeof(student_cell_T) );
    if (!element)
    {
        fprintf(stderr,"NewStudentCell cannot allocate memory\n");
        return NULL;
    }

    element->id = strdup(id);
    if (element->id == NULL)
    {
        fprintf(stderr, "Error: strdup failed for id\n");
        free(element);
        return NULL;
    }

    element->gpa = gpa;
    element->name = strdup(name);
    if (element->name == NULL)
    {
        fprintf(stderr, "Error: strdup failed for name\n");
        free(element->id);
        free(element);
        return NULL;
    }
    element->next = NULL;
    return element;

}


/*
 * Function: NewLinkedList
 * Usage: linked_list_T *list;
 *        list = NewLinkedList();
 * --------------------------
 * This function allocates and returns an empty linked list.
 */
linked_list_T *NewLinkedList(void)
{
    linked_list_T *list;
  
    list = (linked_list_T *) malloc(sizeof(linked_list_T) );
    if ( !list) {
        fprintf(stderr,"NewLinkedList cannot allocate memory\n");
        return NULL;
    }

    list->head = NULL;
    list->tail = NULL;

    return list;
}


/*
 * Function: FreeLinkedList
 * Usage: FreeLinkedList(list);
 * ------------------------
 * This function frees the storage associated with list.
 */
void FreeLinkedList(linked_list_T *list)
{
    if (list == NULL)
        return;
    student_cell_T *current = list->head;
    while (current != NULL)
    {
        student_cell_T *temp = current;
        current = current->next;
        free(temp->id);
        free(temp->name);
        free(temp);
    }
    free(list);
}

/*
 * Function: Enlist
 * Usage: Enlist(list, element);
 * -------------------------------
 * This function adds a student cell pointed by element to the end of the list.
 */
void Enlist(linked_list_T *list, student_cell_T *element)
{
    if (list == NULL || element == NULL)
        return;
    element->next = NULL;
    if (list->head == NULL)

    {
        list->head = element;
        list->tail = element;
    } else
    {
        list->tail->next = element;
        list->tail = element;
    }
}

/*
 * Function: Delist
 * Usage: element = Delist(list);
 * --------------------------------
 * This function removes the student cell at the head of the list
 * and returns its address to the caller (client).  If the list is empty, Delist
 * prints an Error with an appropriate message and returns NULL.
 */
student_cell_T *Delist(linked_list_T *list)
{
    if (list == NULL || list->head == NULL)
    {
        fprintf(stderr, "Error: Cannot delist from an empty list.\n");
        return NULL;
    }
    student_cell_T *removed = list->head;
    list->head = removed->next;
    if (list->head == NULL)
    {
        list->tail = NULL;
    }
    removed->next = NULL;
    return removed;
}

/*
 * Functions: LinkedListIsEmpty, LinkedListIsFull
 * Usage: if (LinkedListIsEmpty(list)) . . .
 *        if (LinkedListIsFull(list)) . . .
 * -------------------------------------
 * These functions test whether the list is empty or full.
 */
int LinkedListIsEmpty(linked_list_T *list)
{
    return (list == NULL || list->head == NULL);
}

int LinkedListIsFull(linked_list_T *list)
{
    return 0; // because we have linked list
}

/*
 * Function: LinkedListLength
 * Usage: n = LinkedListLength(list);
 * ------------------------------
 * This function returns the number of elements in the list.
 */
int LinkedListLength(linked_list_T  *list)
{
    int count = 0;
    student_cell_T *current = (list ? list->head : NULL);
    while (current != NULL)
    {
        count++;
        current = current->next;
    }
    return count;
}

/*
 * Function: GetLinkedListElement
 * Usage: element = GetLinkedListElement(list, index);
 * -----------------------------------------------
 * This function returns the element at the specified index in the
 * list, where the head of the list is defined as index 0. For
 * example, calling GetLinkedListElement(list, 0) returns the initial
 * element from the list without removing it.  If the caller tries
 * to select an element that is out of range, GetLinkedListElement prints
 * Error and returns NULL.  Note: This function is not a fundamental list operation
 * and is instead provided mainly to facilitate debugging.
 */
student_cell_T *GetLinkedListElement(linked_list_T *list, int index)
{
    if (list == NULL || index < 0)
    {
        fprintf(stderr, "Error: Invalid list or index.\n");
        return NULL;
    }
    student_cell_T *current = list->head;
    int currentIndex = 0;
    while (current != NULL && currentIndex < index)
    {
        current = current->next;

        currentIndex++;
    }
    if (current == NULL)
    {
        fprintf(stderr, "Error: Index %d out of range.\n", index);
        return NULL;
    }

    return current;
}



/* OTHER FUNCTIONS YOU WOULD NEED....
 * EXPORT THEM HERE, BUT IMPLMENT THEM in mylinkedlist.c
 */