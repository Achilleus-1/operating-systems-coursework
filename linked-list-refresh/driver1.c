/*
 * File: driver1.c
 *   ... YOU NEED TO IMPLEMENT THE main() + additional functions if needed
 *
 * ....
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mylinkedlist.h"

/*
 * Function: ReadLine
 * Usage: s = ReadLine();
 * ---------------------
 * ReadLine reads a line of text from standard input and returns
 * the line as a string.  The newline '\n' character that terminates
 * the input is not stored as part of the string.
 */
char *ReadLine(void);




void ClearInputBuffer(void)
{
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF);
}

/*
 * StudentExists
 *   returns 1 if a student with the given three letters followed by three digits is already present in lsit
 *   else return 0
 */
int StudentExists(linked_list_T *list, char *id)
{

    student_cell_T *current = list->head;
    while (current != NULL) {
        if (strcmp(current->id, id) == 0)
            return 1;
        current = current->next;
    }

    return 0;
}

/*
 * PrintStudent
 *     prints the info from picked name.
 */
void PrintStudent(student_cell_T *student)
{
    if (student != NULL)
    {
        printf("ID: %s, GPA: %.2f, Name: %s\n", student->id, student->gpa, student->name);
    }

}

/*
 * PrintAllStudents
 *   goes over the list and prints the info from each student cell
 */
void PrintAllStudents(linked_list_T *list)
{
    if (list == NULL || list->head == NULL)
    {
        printf("The list is empty.\n");
        return;
    }
    student_cell_T *current = list->head;
    while (current != NULL) {
        PrintStudent(current);
        current = current->next;
    }
}

/*
 * PrintGpaStats
 *   reads through list and prints min, avg ,and max(mag according to typo in instructions.. I assume it means max),GPA
 *   then prints results
 */

void PrintGpaStats(linked_list_T *list)

{
     if (list == NULL || list->head == NULL)
     {
         printf("The list is empty. No GPA stats to compute.\n");
        return;

    }
    double min = list->head->gpa;
    double max = list->head->gpa;
    double sum = 0.0;

    int count = 0;

    student_cell_T *current = list->head;

    while (current != NULL)
    {
        double gpa = current->gpa;
        if (gpa < min)
            min = gpa;
        if (gpa > max)
            max = gpa;
        sum += gpa;
        count++;
        current = current->next;

    }
    double avg = sum / count;

    printf("GPA Stats:\n");
    printf("Min GPA: %.2f\n", min);
    printf("Average GPA: %.2f\n", avg);
    printf("Max GPA: %.2f\n", max);
}

/*
 * RemoveHighestGpa
 *   finds highest student GPA, removes it, returns
 *   ties, then removes first try
 */


student_cell_T *RemoveHighestGpa(linked_list_T *list)

{

    if (list == NULL || list->head == NULL)
    {
        printf("The list is empty. Cannot remove highest GPA student.\n");
        return NULL;

    }
    student_cell_T *maxStudent = list->head;
    student_cell_T *prevMax = NULL;
    student_cell_T *current = list->head;
    student_cell_T *prev = NULL;
    
    while (current != NULL)
    {
        if (current->gpa > maxStudent->gpa)
        {
            maxStudent = current;
            prevMax = prev;
        }
        prev = current;
        current = current->next;
    }
    
    /* Remove maxStudent from the list */
    if (prevMax == NULL) {
        maxStudent = Delist(list);
        return maxStudent;
    } else
    {
        prevMax->next = maxStudent->next;
        if (maxStudent == list->tail) {
            list->tail = prevMax;
        }
        maxStudent->next = NULL;
        return maxStudent;
    }
}

int main(int argc, char *argv[])
{
    linked_list_T *list = NewLinkedList();
    if (list == NULL)
    {
        fprintf(stderr, "Failed to create a new linked list.\n");
        return 1;
    }
    
    int choice;
    while (1)
    {
        /* prints menu options  */
        printf("\nMenu:\n");
        printf("1 - Add a new student\n");
        printf("2 - Remove the first student\n");
        printf("3 - Print the number of students\n");
        printf("4 - Print student at a specific index\n");
        printf("5 - Print all students\n");
        printf("6 - Print GPA stats (min, average, max)\n");
        printf("7 - Remove the student with highest GPA\n");
        printf("8 - Exit\n");
        printf("Enter your choice: ");
        
        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input. Exiting.\n");
            break;
        }
        ClearInputBuffer();  // remove any leftover newlines
        
        if (choice == 1)
        {

            char *id;
            double gpa;
            char *name;
            
            printf("Enter student's id (format three letters followed by three digits): ");
            id = ReadLine();
            if (id == NULL) {
                printf("Error reading id.\n");
                continue;
            }
            
            printf("Enter student's gpa: ");
            if (scanf("%lf", &gpa) != 1)
            {
                printf("Invalid gpa input.\n");
                free(id);
                ClearInputBuffer();
                continue;
            }
            ClearInputBuffer();
            
            printf("Enter student's name: ");
            name = ReadLine();
            if (name == NULL)
            {
                printf("Error reading name.\n");
                free(id);
                continue;
            }
            
            /* Check for duplicate student id */
            if (StudentExists(list, id))
            {
                printf("Error: A student with id %s already exists. Not adding duplicate.\n", id);
                free(id);
                free(name);
                continue;
            }
            
            student_cell_T *newStudent = NewStudentCell(id, gpa, name);
            /* NewStudentCell makes copies of id and person name. so frees the originals */
            free(id);
            free(name);
            
            if (newStudent == NULL)
            {
                printf("Error: Could not create new student cell.\n");
                continue;
            }

            Enlist(list, newStudent);
            printf("Student added successfully.\n");
        }
        else if (choice == 2) {
            /* Remove (delist) the first student */
            student_cell_T *removed = Delist(list);
            if (removed == NULL) {
                printf("The list is empty. Nothing to remove.\n");
            }
            else {
                printf("Removed student:\n");
                PrintStudent(removed);
                free(removed->id);
                free(removed->name);
                free(removed);
            }
        }
        else if (choice == 3)
        {
            /* prints the number of all students */
            int len = LinkedListLength(list);
            printf("The number of students in the list: %d\n", len);
        }
        else if (choice == 4)
        {
            /* prints the student at the index  */
            int index;
            printf("Enter the index (0-based): ");
            if (scanf("%d", &index) != 1) {
                printf("Invalid index input.\n");
                ClearInputBuffer();
                continue;
            }
            ClearInputBuffer();
            student_cell_T *student = GetLinkedListElement(list, index);
            if (student == NULL)
            {
                printf("No student found at index %d.\n", index);
            } else
            {
                PrintStudent(student);
            }
        }
        else if (choice == 5)
        {
            /* prints all students in list */
            PrintAllStudents(list);
        }

        else if (choice == 6)
        {
            /* print GPA stats */
            PrintGpaStats(list);
        }
        else if (choice == 7)
        {
            /* rmoves the student with thehighest GPA */
            student_cell_T *removed = RemoveHighestGpa(list);
            if (removed != NULL)
            {
                printf("Removed student with highest GPA:\n");
                PrintStudent(removed);
                free(removed->id);
                free(removed->name);
                free(removed);
            }
        }
        else if (choice == 8)
        {
            /* exits all */

            printf("Exiting program...\n");
            FreeLinkedList(list);
            break;
        }
        else
        {
            printf("Invalid choice. Please try again.\n");
        }
    }
    
    return 0;
}

/*
 * IMPLEMENTATION of ReadLine();
 * Function: ReadLine
 * Usage: s = ReadLine();
 * ---------------------
 * ReadLine reads a line of text from standard input and returns
 * the line as a string.  The newline '\n' character that terminates
 * the input is not stored as part of the string.
 *
 * In contrast to standard I/O functions (e.g., scanf with "%s", fgets)
 * that can read strings into a given static size buffer, ReadLine function
 * should read the given input line of characters terminated by a newline
 * character ('\n') into a dynamically allocated and resized buffer based on
 * the length of the given input line.
 *
 * When implementing this function you can use standard I/O functions.
 * We just want you to make sure you allocate enough space for the entered data.
 * So don't simply allocate 100 or 1000 bytes every time.
 * If the given input has 5 characters, you need to allocate space for 6 characters.
 *
 * Hint: initially dynamically allocate an array of char with size 10.
 * Then, read data into that array character by charecter (e.g, you can use getchar()).
 * If you see '\n' char before reading 10th character, you are done. And you know the
 * exact length of the input string. So, accordingly allocate enough space and copy the
 * data into new char array, insert '\0' instead of '\n' and free the original array.
 * Then return the new string. However, if you DO NOT see '\n' char after 10th character,
 * then you need larger space. Accordingly, resize your original array and double its size
 * and continue reading data character by character as in the first step...
 * Hope you got the idea!
 *
 * Also please check for possible errors (e.g., no memory etc.) and appropriately handle
 * them. For example, if malloc returns NULL, free partially allocated space and return
 * NULL from this function. The program calling this function may take other actions,
 * e.g., stop the program!
 */
char *ReadLine()
{
    int capacity = 10;
    int length = 0;
    int c;
    char *buffer = malloc(capacity * sizeof(char));
    if (buffer == NULL) {
        fprintf(stderr, "Error: malloc failed\n");
        return NULL;
    }
    while ((c = getchar()) != EOF && c != '\n')
    {
        buffer[length++] = (char)c;
        if (length >= capacity) {
            capacity *= 2;
            char *newBuffer = realloc(buffer, capacity * sizeof(char));
            if (newBuffer == NULL) {
                free(buffer);
                fprintf(stderr, "Error: realloc failed\n");
                return NULL;
            }
            buffer = newBuffer;
        }
    }
    buffer[length] = '\0';
    char *result = malloc((length + 1) * sizeof(char));
    if (result == NULL)
    {
        free(buffer);
        fprintf(stderr, "Error: malloc failed for result\n");
        return NULL;
    }
    for (int i = 0; i <= length; i++)
    {
        result[i] = buffer[i];
    }
    free(buffer);
    return result;


    return(NULL);   // if there is any error!
}




