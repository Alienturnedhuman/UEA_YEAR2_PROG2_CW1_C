/*****************************************************************************

File        : moviedatabase.h

Date        : Autumn 2016

Description : Header file for the movie database

Author      : Benjamin Dickson

History     : modified from linkedlist by Dr Gavin Cawley

******************************************************************************/


/*
 * I decided to use the linked list code provided as a template for this
 * project, as the core functionality was identical I was going to end up
 * duplicating a lot of it, so it seemed a logical decision to make use of
 * an existing, and functioning, linked list library, and add the bespoke
 * features to it, as all writing the same code from scratch is going to achieve
 * differently is the probability of bugs and typos being added!
 */


#ifndef MOVIEDATABASE_H
#define	MOVIEDATABASE_H

#include "film.h"

typedef struct _Node
{
    Film* film;
    
    struct _Node* next;
}
Node;

typedef struct _List
{
    Node* first;
    
    Node* last;
} 
List;

typedef Node* Iterator;

static inline Iterator list_begin(const List *list)
{
   return list->first;
}

static inline Iterator list_end(const List *list)
{
   return NULL;
}

static inline Iterator iterator_next(const Iterator i)
{
   return i->next;
}

static inline Film* iterator_value(const Iterator i)
{
    return i->film;
}
/*
static inline Iterator iterator_set(Iterator i, Film film)
{
    i->film = film;
}
*/

/*****************************************************************************

Procedure   : list_new

Parameters  : none

Returns     : List* - pointer to newly created list
 
Description : Allocate memory for a new linked list of integer values and
              initialise it.  Generates an error message and the program
              terminates if insufficient memory is available.

 *****************************************************************************/

List* list_new();




/*****************************************************************************

Procedure   : void list_delete_matches(List *list,Film* match, int field, int compareType)


Parameters  :  List* list - pointer to list to which value is added
              Film match   - film object containing matching
              int   field being compared
              int   comparison type

Returns     : none
 
Description : Deletes any matching films

 *****************************************************************************/


void list_delete_matches(List *list,Film* match, int field, int compareType);

/*****************************************************************************

Procedure   : list_add

Parameters  : List* list - pointer to list to which value is added
              int   value - value to be added to the list
  
Returns     : none
 
Description : Appends an integer value to the tail of the list. Generates an 
              error message and the program terminates if insufficient memory 
              is available.

 *****************************************************************************/

void list_add(List* list, Film* film);

/*****************************************************************************

Procedure   : list_insert

Parameters  : List* list - pointer to list to which value is added
              int   value - value to be added to the list

Returns     : none
 
Description : Inserts an integer value to the head of a list.  Generates an 
              error message and the program terminates if insufficient memory 
              is available.

 *****************************************************************************/

void list_insert(List* list, Film* film);

/*****************************************************************************

Procedure   : list_length

Parameters  : List* list - pointer to a lined list structure.

Returns     : int - number of elements comprising the list.
 
Description : Determines the number of integer values currently stored in a
              linked list structure.

 *****************************************************************************/

int list_length(List* list);

/*****************************************************************************

Procedure   : list_head

Parameters  : List* list - pointer to a linked list structure.

Returns     : int - value of the first element of the list.
 
Description : Removes the first element of a linked list structure and 
              returns its value.  If the list is empty, an error message is
              generated and the program terminates. 

 *****************************************************************************/

Film* list_head(List* list);

/*****************************************************************************

Procedure   : list_tail

Parameters  : List* list - pointed to a linked list structure.

Returns     : Film - Film pointer of the last film of the list.
 
Description : Removes the last item of a linked list structure and returns 
              its value.  If the list is empty, an error message is generated
              and the program terminates.

 *****************************************************************************/

Film* list_tail(List* list);

/*****************************************************************************

Procedure   : list_sort

Parameters  : List* list - pointer to a linked list structure.
              int filmField - an integer relating to the field to be sorted by


Returns     : none
 
Description : Sorts the elements of a linked list structure into ascending
              order, using the bubble sort algorithm (not very efficient).

 *****************************************************************************/

void list_sort(List* list, int filmField, int compareType);
/*****************************************************************************

Procedure   : list_max

Parameters  : List* list - pointer to a linked list structure.
              int filmField - an integer relating to the field to be sorted by


Returns     : Film
 
Description : Returns the film with the highest value for a given field

 *****************************************************************************/

Film* list_max(List* list, int filmField);

/*****************************************************************************

Procedure   : list_min

Parameters  : List* list - pointer to a linked list structure.
              int filmField - an integer relating to the field to be sorted by


Returns     : Film
 
Description : Returns the film with lowest value for a given field

 *****************************************************************************/

Film* list_min(List* list, int filmField);

/*****************************************************************************

Procedure   : list_extreme

Parameters  : List* list - pointer to a linked list structure.
              int filmField - an integer relating to the field to be sorted by
              int filmcompareType - an integer relating to the comparison type


Returns     : Film
 
Description : Returns the film with most extreme value for a given field for
              the comparison type
 

 *****************************************************************************/

Film* list_extreme(List* list, int filmField, int compareType);

/*****************************************************************************

Procedure   : list_partial

Parameters  : List* list - pointer to a linked list structure.
              int filmField - an integer relating to the field to be compared by
              int compareType - integer relating to comparison type


Returns     : none
 
Description : Sorts the elements of a linked list structure into ascending
              order, using the bubble sort algorithm (not very efficient).

 *****************************************************************************/

List* list_partial(List* list, int filmField, char* compareString, int compareType);

/*****************************************************************************

Procedure   : list_clear

Parameters  : List* list - pointer to a linked list structure

Returns     : none
 
Description : Delete all nodes from a linked list structure.

 *****************************************************************************/

void list_clear(List *list);

/*****************************************************************************

Procedure   : list_clear

Parameters  : List* list - pointer to a linked list structure

Returns     : none
 
Description : Delete all nodes from a linked list structure, and the films
              being pointed to

 *****************************************************************************/

void list_clear_and_delete(List *list);

/*****************************************************************************

Procedure   : list_fprint

Parameters  : List* list - pointer to a linked list structure.
              FILE* fd   - pointer to a file stream descriptor structure.

Returns     : none
 
Description : Prints a linked list of integer values to the specified output
              stream (typically stdout), as a set of comma separated values
              enclosed in parentheses.

 *****************************************************************************/

void list_fprint(List* list, FILE* fd, int* outputList, int outputCount);

/*****************************************************************************

Procedure   : list_getIndex

Parameters  : List* list - pointer to a linked list structure.
              int index   - pointer to a file stream descriptor structure.

Returns     : List*
 
Description : returns the nth index of a list, or NULL if it does not exist

 *****************************************************************************/

Film* list_getIndex(List *list, int index);

/*****************************************************************************

Procedure   : list_fprint

Parameters  : List* list - pointer to a linked list structure.
              FILE* fd   - pointer to a file stream descriptor structure.

Returns     : none
 
Description : Prints a linked list of integer values to the specified output
              stream (typically stdout), as a set of comma separated values
              enclosed in parentheses.

 *****************************************************************************/

void list_print(List* list, int outputList[], int outputCount);

/****************************************************************************/

#endif	/* MOVIEDATABASE_H */