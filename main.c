/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: bendickson
 *
 * Created on November 14, 2016, 9:10 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "film.h"
#include "moviedatabase.h"

/*
 * I set up my code to read escape characters
 * 
 * eg: \n = new line, \" = " (contained within "" etc...
 * to do this I created an escape character struct, with the character that
 * appends in the string (find) and the character for \find to be replaced with
 * (replace) so, for example, find: 't' is matched with replace: (tab)
 * When analysing the string character by character, when the code finds a '\'
 * character, it then checks through all the escape characters for a match.
 * If a match is found, then both characters (the '\' and the escape character)
 *  are replaced with the replace character.
 * 
 * Originally I set up a global array of structs, however I found out this was
 * not possible to do in C. (at least according to my research online)
 * 
 * However, I needed a way of getting the Escape characters in multiple places
 * and functions in exactly the same order. Duplicating the code is not a good
 * idea for maintainability - so then I hit on the idea of using the
 * preprocessor - I can just define ESCAPE_CHARS as an array of EscapeCharacters
 * and define them in one place.
 * 
 * I can also do the same with the free statement at the end of the function.
 * 
 * So below are the two preprocessor definitions used to achieve that.
 */
#define ESCAPE_CHARS int ESCAPE_CHARACTER_COUNT = 11;\
EscapeCharacter *ESCAPE_CHARACTERS[] = {\
    escapecharacter_new(97,7)\
    ,\
    escapecharacter_new(98,8)\
    ,\
    escapecharacter_new(102,12)\
    ,\
    escapecharacter_new(110,10)\
    ,\
    escapecharacter_new(114,13)\
    ,\
    escapecharacter_new(116,9)\
    ,\
    escapecharacter_new(118,7)\
    ,\
    escapecharacter_new(92,92)\
    ,\
    escapecharacter_new(39,39)\
    ,\
    escapecharacter_new(34,34)\
    ,\
    escapecharacter_new(63,63)\
};

#define FREE_ESCAPE_CHARS int ESCAPE_CHAR=-1;\
while(++ESCAPE_CHAR<ESCAPE_CHARACTER_COUNT)\
{\
    free(ESCAPE_CHARACTERS[ESCAPE_CHAR]);\
}
//free(ESCAPE_CHARACTERS);

// this creates a struct for processing escape characters
typedef struct _EscapeCharacter
{
    int find;
    int replace;
}EscapeCharacter;

// this creates a new escape character
EscapeCharacter *escapecharacter_new(int eFind, int eReplace)
{
    EscapeCharacter *escapecharacter = (EscapeCharacter*)malloc(
            sizeof(EscapeCharacter));
    escapecharacter->find = eFind;
    escapecharacter->replace = eReplace;
    return escapecharacter;
    
}



// this are used for the lineread struct
const int LINEREAD_INT = 0;
const int LINEREAD_DOUBLE = 1;
const int LINEREAD_STRING = 2;

// some important charaters used in processing the file
const int COMMA = 44;
const int DELIMITER = 34;
const int ESCAPE_PREFIX = 92;

// this is the location of the input file
const char* INPUT_FILE_LOCATION = "/Users/bendickson/Desktop/input.txt";

// controller for alternative tasks to be done (outside scope of coursework)
const int DO_ALTERNATIVE_TASKS = 1;




typedef struct _LineRead
{
    int lrType;
    int lrField;
    int start;
    int end;
    int escapeCount;
}LineRead;

LineRead *lineread_new(int type , int field)
{
    LineRead *lineread = (LineRead*)malloc(sizeof(LineRead));
    lineread->lrType = type;
    lineread->lrField = field;
    lineread->escapeCount = 0;
    return lineread;
}

void lineread_setStart(LineRead *lineread,int start)
{
    lineread->start = start;
}
int lineread_getStart(LineRead *lineread)
{
    return lineread->start;
}

void lineread_setEnd(LineRead *lineread,int end)
{
    lineread->end = end;
}
int lineread_getEnd(LineRead *lineread)
{
    return lineread->end;
}
void lineread_addEscapeCharacter(LineRead *lineread)
{
    lineread->escapeCount = lineread->escapeCount+1;
}
int lineread_getEscapeCount(LineRead *lineread)
{
    return lineread->escapeCount;
}

int lineread_getType(LineRead *lineread)
{
    return lineread->lrType;
}

int lineread_getField(LineRead *lineread)
{
    return lineread->lrField;
}




// give a character, returns for the escape character substitution or -1 for
// no match
int escapecharacter_check(int chr)
{
    ESCAPE_CHARS
    int i=-1;
    int r=-1; 
    while(++i<ESCAPE_CHARACTER_COUNT && r==-1)
    {
        if(ESCAPE_CHARACTERS[i]->find==chr)
        {
            r = ESCAPE_CHARACTERS[i]->replace;
        }
    }
    
    
    FREE_ESCAPE_CHARS
    return r;
}

Film *filmFromLine(char line[])
{
    // debug line here
    printf("filmFromLine | %s\n",line);
    
    ESCAPE_CHARS
    
            
    // allocate memory for Film struct
    Film *r = (Film*)malloc(sizeof(Film));
    
    //create array of inputFields (and int for number)
    // these are the fields per line, in the order they appear
    
    // "Memento",2000,"R","Mystery/Thriller",113,8.5
    int inputFieldsLength = 6;
    LineRead *inputFields[] = {
        lineread_new(LINEREAD_STRING,FILM_FIELD_TITLE)
        ,
        lineread_new(LINEREAD_INT,FILM_FIELD_YEAR)
        ,
        lineread_new(LINEREAD_STRING,FILM_FIELD_CERT)
        ,
        lineread_new(LINEREAD_STRING,FILM_FIELD_GENRE)
        ,
        lineread_new(LINEREAD_INT,FILM_FIELD_MINUTES)
        ,
        lineread_new(LINEREAD_DOUBLE,FILM_FIELD_RATING)
    };
   
    
    // now scan through the line character by character until all fields are
    // found, and record the start and end position of the data, assigning it
    // to the inputFields lineread structs 
    int i = -1;
    int ii = strlen(line);
    int searching=0;
    int scanning=-1;
    int decimalPoint=1;
    while(
        ++i<ii
        &&
        searching<inputFieldsLength
    )
    {
        if(scanning<searching)
        {
            // still searching for start
            
            switch(lineread_getType(inputFields[searching]))
            {
                case LINEREAD_STRING:
                    // scan until I find the string delimiter character
                    // or am too close to the end of the string to have a
                    // delimited string
                    if(line[i]==DELIMITER && i<ii-1)
                    {
                        // set scanning to the same value as searching means
                        // the loop will now start looking for an end
                        // delimiter
                        scanning=searching;
                        lineread_setStart(inputFields[scanning],i+1);
                    }
                    break;
                case LINEREAD_INT:
                case LINEREAD_DOUBLE:
                    // this project only deals with positive numbers, so only
                    // have to scan until I find a numberical character
                    if(line[i]>47 && line[i]<58)
                    {
                        scanning=searching;
                        lineread_setStart(inputFields[scanning],i);
                        decimalPoint=1;
                    }
                    break;
            }
        }   
        else
        {
            switch(lineread_getType(inputFields[searching]))
            {
                case LINEREAD_STRING:
                    if(line[i]==DELIMITER)
                    {
                        searching++;
                        lineread_setEnd(inputFields[scanning],i);
                    }
                    else if(line[i]==ESCAPE_PREFIX && i<ii-1 && 
                            escapecharacter_check(line[i+1])>-1)
                    {
                        i++;
                        lineread_addEscapeCharacter(inputFields[scanning]);
                    }
                    break;
                case LINEREAD_INT:
                case LINEREAD_DOUBLE:
                    if(!(
                        (line[i]>47 && line[i]<58)
                        ||
                        (decimalPoint && line[i]==46)
                    ))
                    {
                        searching++;
                        lineread_setEnd(inputFields[scanning],i);
                        while(i<ii && line[i]!=COMMA)
                        {
                            i++;
                        }
                        
                    }
                    if(line[i]==46)
                    {
                        decimalPoint=0;
                    }
                    if(i+1==ii)
                    {
                        lineread_setEnd(inputFields[scanning],i+1);
                    }
                    break;
            }
        }
    }
    int j = -1;
    int escapeCounter;
    int s;
    
    while(++j<inputFieldsLength)
    {
        if(lineread_getEnd(inputFields[j])>-1)
        {
            i = lineread_getStart(inputFields[j])-1;
            ii = lineread_getEnd(inputFields[j]);
            int strSize = (ii -  i - lineread_getEscapeCount(inputFields[j]));
            char* str = malloc(strSize+1);
            s=-1;
            
            while(++s<=strSize)
            {
                str[s]=0;
            }
            s=-1;
            while(++i<ii&&++s<strSize)
            {
                if(
                    i<ii-1
                    &&
                    line[i] == ESCAPE_PREFIX
                    &&
                    escapecharacter_check(line[i+1])>-1
                )
                {
                    i++;
                    str[s] = escapecharacter_check(line[i]);
                }
                else if(line[i]==EOF)
                {
                    strSize=i;
                    i=ii;
                }
                else
                {
                    str[s] = line[i];
                }
                if(str[s]>127||str[s]<32)
                {
                    printf(">>>>>> FOUND CHARACTER %d\n",str[s]);
                }
            }
            film_string_into_field(r,lineread_getField(inputFields[j]),str);
            printf("adding %s and title is %s \n",str,film_getTitle(r));
            free(str);
        }
    }
    
    printf("FILM COMPLETE:\nTitle: %s %s",film_getTitle(r), "<<< is that!");
    printf("\nYear: %d",film_getYear(r));
    printf("\nCert: %s",film_getCert(r));
    printf("\nGenre: %s",film_getGenre(r));
    printf("\nMinutes: %d",film_getMinutes(r));
    printf("\nRating: %.1f \n\n",film_getRating(r));
    
    FREE_ESCAPE_CHARS
    return r;
    
    
}

// below (commented out) is a read line function I started to write when
// I couldn't get the getline method to work correctly - however when I realised
// why it wasn't working, I stopped writing this method, but left the code in
// in case I decided to one day go back and have a look at it.
/*

char* readNextLine(FILE *file)
{
    char *tStr = malloc( sizeof(char) * ( 1024 ) );
    int tLen = 0;
    
    int rChr = fgetc(file);
    if(rChr==EOF)
    {
        free(tStr);
        return "";
    }
    while(rChr==13||rChr==10)
    {
        rChr = fgetc(file);
        if(rChr==EOF)
        {
            free(tStr);
            return "";
        }
    }
    while(rChr!=13||rChr!=10||rChr==EOF)
    {
        tStr[tLen++]=rChr;
        rChr = fgetc(file);
    }
    int i=-1;
    char *r = malloc( sizeof(char) * ( tLen ) );
    while(++i<tLen)
    {
        r[i]=tStr[i];
    }
    free(tStr);
    return r;
}*/



// modification of function described on the following URL by user mbaitoff
// http://stackoverflow.com/questions/3501338/c-read-file-line-by-line
List *listFromFile(char file_path[])
{
    int output[]={0,1,2,3,4,5};
    int outputCount = 6;
    
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    int read;

    fp = fopen(file_path, "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);
    
    List *r = list_new();
    
    while ((read = getline(&line, &len, fp)) != -1) {
        Film *newFilm = filmFromLine(line);
        list_add(r,newFilm);
    }

    fclose(fp);
    if (line)
        free(line);
    
    return r;
}


int main(int argc, char** argv) {
    
    
    // Generate a new list from the file
    List *movies = listFromFile(INPUT_FILE_LOCATION);
    
    // this is a list of the fields to be passed to the toString method
    // is uses the numbers from the identifiers, so I could put
    // FILM_FIELD_TITLE etc instead of the numbers for readability
    // however, in this case I want all of them (and there are 6) so I am
    // just going to write them down as the integer values
    int output[]={0,1,2,3,4,5};
    int outputCount = 6;
    
    // Task 1 - Sort lists chronologically by release date and output to console
    // this is a simple sort by integer task:
    
    printf("TASK 1:\nSort list chronological and output to console:\n\n");
    
    
    // step 1 - sort the list by year, ascending
    list_sort(movies, FILM_FIELD_YEAR,FILM_COMPARE_GREATER_THAN);
    
    // step 2 - output to console
    list_print(movies,output,outputCount);
    
    
    printf("\nTASK 1 Complete!:\n\n");
    
    
    // Task 1 alternatives
    if(DO_ALTERNATIVE_TASKS>0)
    {
        // a) sort list by longest Title
        printf("\nTASK 1a:\n");
        
        list_sort(movies, FILM_FIELD_TITLE,FILM_COMPARE_STRING_SHORTER);
        list_print(movies,output,outputCount);

        // b) sort list reverse chronologically, then by Title, then by run time
        printf("\nTASK 1b:\n");
        
        list_sort(movies, FILM_FIELD_MINUTES,FILM_COMPARE_GREATER_THAN);
        list_sort(movies, FILM_FIELD_TITLE,FILM_COMPARE_GREATER_THAN);
        list_sort(movies, FILM_FIELD_YEAR,FILM_COMPARE_LESS_THAN);
        // note, needs performed in reverse order, as most recent search is most
        // important
        list_print(movies,output,outputCount);
    }
    
    // Task 2 - Display Third Longest Film-Noir
    
    printf("TASK 2:\nDisplay the Third Longest Film Noir:\n\n");
    // step 1 - create a list of the Film-Noir
    List *tempList = list_partial(movies,FILM_FIELD_GENRE,
            "Film-Noir",FILM_COMPARE_STRING_CONTAINS);
    
    // step 2 - order by length
    list_sort(tempList, FILM_FIELD_MINUTES,FILM_COMPARE_GREATER_THAN);
    
    // step 3 - get the third film (not, zero indexed, so this is 2 not 3)
    Film* tempFilm = list_getIndex(tempList,2);
    
    // step 4 - check it is a valid result
    if(tempFilm==NULL)
    {
        printf("No Third Film Noir Film");
    }
    else
    {
        printf("Third longest Film-Noir Film:\n\n%s\n\n",
                film_toString(tempFilm,output,outputCount));
    }
    // tempFilm does not need to be freed as it is still in use in the main
    // movie list
    list_clear(tempList);
    free(tempList);
    
    printf("\nTASK 2 Complete!:\n\n");
    
    // Task 3 - Display Highest Rated Sci Fi Film
    
    printf("TASK 3:\nDisplay the tenth highest rated sci fi film:\n\n");
    // step 1 - create a list of the Sci-Fi
    tempList = list_partial(movies,FILM_FIELD_GENRE,
            "Sci-Fi",FILM_COMPARE_STRING_CONTAINS);
    
    // step 2 - order by rating
    list_sort(tempList, FILM_FIELD_RATING,FILM_COMPARE_GREATER_THAN);
    
    // step 3 - get the tenth film (note, zero indexed, so this is 9 not 10)
    tempFilm = list_getIndex(tempList,9);
    
    // step 4 - check it is a valid result
    if(tempFilm==NULL)
    {
        printf("No Tenth Rated Sci Fi Film");
    }
    else
    {
        printf("Tenth Highest Rated Sci-Fi Film:\n\n%s\n\n",
                film_toString(tempFilm,output,outputCount));
    }
    // tempFilm does not need to be freed as it is still in use in the main
    // movie list
    free(tempList);
    
    printf("\nTASK 3 Complete!:\n\n");
    
    // Task 2/3 alternative
    if(DO_ALTERNATIVE_TASKS>0)
    {
        printf("\nTASK 3a:\n");
        // a) Display the sixth highest rated movie released before 1940
        tempList = list_partial(movies,FILM_FIELD_YEAR,
            "1940",FILM_COMPARE_LESS_THAN);
        list_sort(tempList, FILM_FIELD_RATING,FILM_COMPARE_LESS_THAN);
        tempFilm = list_getIndex(tempList,5);
        if(tempFilm==NULL)
        {
            printf("No Sixth Highest Film released before 1940");
        }
        else
        {
            printf("Sixth Highest Film released before 1940:\n\n%s\n\n",
                    film_toString(tempFilm,output,outputCount));
        }
    }
    
    // Task 4 - Display the highest rated film
    
    printf("TASK 4:\nDisplay the highest rated film:\n\n");
    
    // Step 1 - extract the highest rated film
    tempFilm = list_max(movies, FILM_FIELD_RATING);
    
    // Step 2 - output to console
    printf("Highest rated film:\n\n%s\n\n",
                    film_toString(tempFilm,output,outputCount));
    
    
    printf("\nTASK 4 Complete!:\n\n");
    
    // Task 5 - Display the highest rated film
    
    printf("TASK 5:\nDisplay the film with the shortest name:\n\n");
    
    // Step 1 - extract the highest rated film
    tempFilm = list_extreme(movies, FILM_FIELD_TITLE,
            FILM_COMPARE_STRING_SHORTER);
    
    // Step 2 - output to console
    printf("Film with shortest name:\n\n%s\n\n",
                    film_toString(tempFilm,output,outputCount));
    
    
    printf("\nTASK 5 Complete!:\n\n");
    
    // Task 6 - 
    
    printf("TASK 6:\nRemove all R rated films and output remaining count:\n\n");
    
    // Step 1 - for ease of modification, set delete field here:
    int deleteField = FILM_FIELD_CERT;
    
    // Step 2 - create a partial film object with the property required
    Film* delFilm = (Film*)malloc(sizeof(Film));
    film_string_into_field(delFilm, deleteField, "R");
    
    // Step 3 - delete matches for this film
    list_delete_matches(movies,delFilm,deleteField,FILM_COMPARE_EQUAL_TO);
    
    // Step 4 - free memory for partial film object
    free(delFilm);
    
    // Step 5 - output to console
    printf("Remaining count: %d films",list_length(movies));
    
    printf("\nTASK 6 Complete!:\n\n");
    
    // Task 6 alternative
    if(DO_ALTERNATIVE_TASKS>0)
    {
        // a) Delete all films released before the film with the longest name
        printf("\nTASK 6a:\n");
        
        // Step 1 - select delete field
        deleteField = FILM_FIELD_YEAR;
        
        // Step 2 - get the film with the longest name
        delFilm = list_extreme(movies, FILM_FIELD_TITLE,
            FILM_COMPARE_STRING_LONGER);
        
        // Step 3 - delete the film released before that film
        list_delete_matches(movies,delFilm,deleteField,
                FILM_COMPARE_GREATER_THAN);
        
        // Step 4 - output list
        list_print(movies,output,outputCount);
    }
}






/*
 * Below are old methods used to test various functions of the code prior
 * to getting the code ready for submission
 */
int randomTesting()
{
  
    printf("hello world\n");
    
    Film* testA = film_new("test, film 123",1988,"12","Sci Fi",120,8.5);
    Film* testB = film_new("another test film $%#$% 123 hi     ",1986,"15",
            "Sci Fi",121,8.0);
    
    //printf("testA name: %s\n`n",&testA->);
    
    printf(film_compare(testA,testB,FILM_COMPARE_GREATER_THAN,
            FILM_FIELD_CERT)?"A":"B");
    
    
    free(testA);
    free(testB);
    return 0;
}

int oldMain(int argc, char** argv) {
    randomTesting();
    
    
    List *theList = listFromFile("/Users/bendickson/Desktop/input.txt");
    
    //list_sort(theList, 0,FILM_COMPARE_STRING_SHORTER);
    int output[]={0,1,2,3,4,5};
    int outputCount = 6;
    list_print(theList,output,outputCount);
    
    FILE *f = fopen("/Users/bendickson/Desktop/output.txt", "w");
    list_fprint(theList,f,output,outputCount);
    fclose(f);
    
    printf("\n\nPARTIAL LIST\n");
    List *tList = list_partial(theList,FILM_FIELD_GENRE,"Sci-Fi",
                FILM_COMPARE_STRING_CONTAINS);
    
    
    list_sort(tList, FILM_FIELD_RATING,FILM_COMPARE_LESS_THAN);
    
    list_print(tList,output,outputCount);
    
    printf("output = %d/%d=%d\n",sizeof(output),sizeof(int),
            sizeof(output)/sizeof(int));
    
    Film* sciFi = list_getIndex(tList,9);
    
    printf("got, now output\n");
    if(sciFi==NULL)
    {
        printf("NO TENTH SCIFI");
    }
    else
    {
        printf("Tenth Sci Fi Film:\n\n%s\n\n",
                film_toString(sciFi,output,outputCount));
    }
    
    
    Film* maxTitle = list_max(theList, FILM_FIELD_RATING);
    
    printf("got maxTitle, now output\n");
    if(maxTitle==NULL)
    {
        printf("NO TENTH MAx Title");
    }
    else
    {
        printf("Max Film Title Film:\n\n%s\n\n",
                film_toString(maxTitle,output,outputCount));
    }
    
    
    Film* maxTitleLen = list_extreme(theList, FILM_FIELD_TITLE,
            FILM_COMPARE_STRING_SHORTER);
    
    printf("got maxTitle, now output\n");
    if(maxTitleLen==NULL)
    {
        printf("MAx Title Length");
    }
    else
    {
        printf("Max Film Title Length Film:\n\n%s\n\n",
                film_toString(maxTitleLen,output,outputCount));
    }
    
    
    
    printf("Starting delFilm on %d films\n",list_length(theList));
    
    Film* delFilm = (Film*)malloc(sizeof(Film));
    
    int deleteField = FILM_FIELD_MINUTES;
    
    film_string_into_field(delFilm, deleteField, "110");
    
    printf("doing list delete delFilm\n");
    
    list_delete_matches(theList,delFilm,deleteField,FILM_COMPARE_GREATER_THAN);
    
    printf("Remaining: %d films\n",list_length(theList));
    
    
    FILE *ff = fopen("/Users/bendickson/Desktop/output2.txt", "w");
    list_fprint(theList,ff,output,outputCount);
    fclose(ff);
    
    
    return (EXIT_SUCCESS);
}