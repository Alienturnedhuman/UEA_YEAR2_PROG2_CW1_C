/*****************************************************************************

File        : moviedatabase.c

Date        : Autumn

Description : Source file for the movie database

Author      : Benjamin Dickson

History     : modified from linkedlist by Dr Gavin Cawley

******************************************************************************/


#include <stdio.h>
#include <stdlib.h>

#include "moviedatabase.h"

List* list_new()
{
   List* list = (List*)malloc(sizeof(List));
    
   if (list == NULL)
   {
      fprintf(stderr, "Error: Unable to allocate memory in list_new()\n");
      
      exit(EXIT_FAILURE);
   }
   
   list->first = NULL;
   list->last  = NULL;
   
   return list; 
}

void list_add(List* list, Film* film)
{
   Node* node = (Node*)malloc(sizeof(Node));
   
   if (node == NULL)
   {
      fprintf(stderr, "Error: Unable to allocate memory in list_add()\n");
      
      exit(EXIT_FAILURE);
   }
   
   node->film = film;
   node->next  = NULL;
    
   if (list->last == NULL)
   {
      list->first = list->last = node;
   }
   else
   {
      list->last = list->last->next = node;  
   }
}

void list_insert(List* list, Film* film)
{
   Node* node = (Node*)malloc(sizeof(Node));

   if (node == NULL)
   {
      fprintf(stderr, "Error: Unable to allocate memory in list_insert()\n");
      
      exit(EXIT_FAILURE);
   }
    
   node->film = film;
   node->next  = list->first;
   
   if (list->first == NULL)
   {
      list->first = list->last = node;
   }
   else
   {
      list->first = node;
   }
}

int list_length(List* list)
{
   int length = 0;
    
   for (Node* node = list->first; node != NULL; node = node->next)
   {
       length++;
   }
    
   return length;
}

Film* list_head(List* list)
{
   if (list->first == NULL)
   {
      fprintf(stderr, "Error: attempt to return the head of an empty list.");

      exit(EXIT_FAILURE);
   }
   
   Film* film = list->first->film;
   
   Node *node = list->first;
   
   if (list->first == list->last)
   {
      list->first = list->last = NULL;    
   }
   else
   {
      list->first = list->first->next;    
   }
   
   free(node);
   
   return film;
}

Film* list_tail(List* list)
{
   if (list->first == NULL)
   {
      fprintf(stderr, "Error: attempt to return the tail of an empty list.");

      exit(EXIT_FAILURE);       
   }
   
   Film* film = list->last->film;
   
   Node* tail = list->last;
   
   if (list->first == list->last)
   {
       list->first = list->last = NULL;
   }
   else
   {
       Node* node;
       
      for (node = list->first; node->next != tail; node = node->next);
      
      list->last       = node;
      list->last->next = NULL;
   }
   
   free(tail);
   
   return film;
}

List* list_partial(List *list , int filmField , char* compareString ,
        int compareType)
{
    // create a new blank list
    List *r = list_new();
    
    // create a temporary partial film, with one field set to the comparison
    Film* tempFilm = (Film*)malloc(sizeof(Film));
    
    film_string_into_field(tempFilm, filmField, compareString);
    
    // loop through each node, adding a successful comparison node to the list
    for (Node* node=list->first; node->next!=NULL; node=node->next)
    {
        if(film_compare((node->film), tempFilm, compareType, filmField)>0)
        {
            list_add(r,(node->film));
        }
    }
    free(tempFilm);
    return r;
}

// this is a modification of Gavin's list_sort method, only adapted to do
// a comparison on a field number, and using multiple comparison types
void list_sort(List *list , int filmField , int compareType)
{
   if (list->first != list->last)   // list contains two or more items
   {
      int sorted;
      do
      {
         sorted = 1; 
         
         for (Node* node=list->first; node->next!=NULL; node=node->next)
         {
            if (film_compare((node->film), (node->next->film),
                    compareType,filmField))
            {
               Film* temp = node->film;
               (node->film) = node->next->film;
               node->next->film = temp;
               sorted = 0;
               //film_free(temp);
            }
         }
      }
      while (!sorted);
   }
}

// list_max and list_min use the same method as list_extreme, but are preset
// for doing a maximum or minimum comparison - so please see comments on
// list extreme to explain the operation
Film* list_max(List* list, int filmField)
{
    Node* node=list->first;
    if(node!=NULL)
    {
        Film* rFilm = node->film;
        node=node->next;
        while(node!=NULL)
        {
            if(film_compare(rFilm,node->film,FILM_COMPARE_LESS_THAN,filmField))
            {
                rFilm=node->film;
            }
            node = node->next;
        }
        return rFilm;
    }
}

Film* list_min(List* list, int filmField)
{
    Node* node=list->first;
    if(node!=NULL)
    {
        Film* rFilm = node->film;
        node=node->next;
        while(node!=NULL)
        {
            if(film_compare(rFilm,node->film,FILM_COMPARE_GREATER_THAN,filmField))
            {
                rFilm=node->film;
            }
            node = node->next;
        }
        return rFilm;
    }
}

Film* list_extreme(List* list, int filmField, int compareType)
{
    // get the film from the first Node
    Node* node=list->first;
    if(node!=NULL)
    {
       // set the return Film (rFilm) to the first film, and swap if if a 
        // more extreme case is found
        Film* rFilm = node->film;
        node=node->next;
        while(node!=NULL)
        {
            if(film_compare(node->film,rFilm,compareType,filmField))
            {
                // more extreme case found - set rFilm to it
                rFilm=node->film;
            }
            node = node->next;
        }
        // return rFilm
        return rFilm;
    }
}


void list_delete_matches(List *list,Film* match, int field, int compareType)
{
    Node* nodeFirst = list->first;
    Node* nodeLast = list->last;
    
    if(nodeFirst==NULL)
    {
        // this is the case where the list is empty, so nothing needs to be done
        // but if in the future it does - such as throwing an error, it will
        // go here
    }
    else if(nodeFirst==nodeLast)
    {
        // for single entity lists
        // only need to check one film
        if(film_compare(nodeFirst->film,match,compareType,field))
        {
            // if it matches, free the film inside, and then the film and set
            // list to null
            free(nodeFirst->film);
            list->first=NULL;
            list->last=NULL;
            nodeLast=NULL;
            free(nodeFirst);
        }
    }
    else
    {
        // finally, multiple entry lists
        
        // this is just creating a pointer for the nextNode before the loop
        Node* nextNode = nodeFirst;
        
        // first we need to make sure the ->first pointer is preserved
        // so keep looping through, deleting firsts that match
        while(nodeFirst != NULL && 
                film_compare(nodeFirst->film,match,compareType,field)!=0)
        {
            nextNode = nodeFirst->next; // get the next node
            free(nodeFirst->film); // free film in nodeFirst
            free(nodeFirst); // free nodeFirst
            nodeFirst=nextNode; // move nodeFirst to nextNode pointer
            
        }
        
        // now set list-> first to new nodeFirst
        list->first=nodeFirst;
        
        if(nodeFirst==NULL)
        {
            // if it is NULL then the list is empty so last is also NULL
            list->last=NULL;
        }
        else
        {
            // now iterate through remaining nodes, deleting matches
            
            Node* node=nodeFirst->next; // node is the current Node
            Node* lastNode = nodeFirst; // lastNode is the last undeleted Node
            while(node!=NULL)
            {
                nextNode = node->next; // get the nextNode ready
                if(film_compare(node->film,match,compareType,field)==1)
                {
                    // if the film matches the delete requirements
                    lastNode->next = nextNode; // set the next of the last good
                        // node to the next node
                    free(node->film);   // free the film in the deleted node
                    free(node); // free the deleted node
                }
                else
                {
                    lastNode = node;    // as node is not deleted, this is now
                        // the last good node
                }
                node = nextNode;    // iterate to next node...
            }
            list->last = lastNode;  // set the list last to the last good Node
        }
    }
    
}


Film* list_getIndex(List *list, int index)
{
    Node* node=list->first;
    // loops through list until i reaches index and returns the film there
    int i = -1;
    while(node != NULL)
    {
        if(++i==index)
        {
            return node->film;
        }
        node=node->next;
    }
    // i is greater than the list size, so return NULL
    return NULL;
}

void list_clear(List *list)
{
   while (list->first != NULL)
   {
      Node* node = list->first;
      list->first = node->next;
      free(node);
   }
    
   list->last = NULL;
}

void list_clear_and_delete(List *list)
{
   while (list->first != NULL)
   {
      Node* node = list->first;
      list->first = node->next;
      free(node->film);
      free(node);
   }
    
   list->last = NULL;
}

void list_fprint(List* list, FILE* fd, int* outputList, int outputCount)
{
    
   for (Node *node = list->first; node != NULL; node = node->next)
   {
       fprintf(fd, (node->next == NULL ? "%s" : "%s\n"), 
               film_toString((node->film),outputList,outputCount));
   }
   
}



void list_print(List* list, int outputList[], int outputCount)
{
   for (Node *node = list->first; node != NULL; node = node->next)
   {
       printf("%s \n", film_toString((node->film),outputList,outputCount));
   }
}


/****************************************************************************/
