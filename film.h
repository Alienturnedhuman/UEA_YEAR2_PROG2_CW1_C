/*****************************************************************************

File        : film.h

Date        : Autumn 2016

Description : Header file for the film struct

Author      : Benjamin Dickson

History     : created from new

******************************************************************************/


#ifndef FILM_H
#define FILM_H

extern const int FILM_FIELD_YEAR_MIN;
extern const int FILM_FIELD_YEAR_MAX;
extern const int FILM_FIELD_MINUTES_MIN;
extern const int FILM_FIELD_MINUTES_MAX;


// some final variables for comparison
extern const int FILM_COMPARE_NOT_EQUAL_TO;
extern const int FILM_COMPARE_EQUAL_TO;
extern const int FILM_COMPARE_GREATER_THAN;
extern const int FILM_COMPARE_GREATER_OR_EQUAL_TO;
extern const int FILM_COMPARE_LESS_THAN;
extern const int FILM_COMPARE_LESS_OR_EQUAL_TO;
extern const int FILM_COMPARE_STRING_LENGTH_NOT_EQUAL;
extern const int FILM_COMPARE_STRING_LENGTH_EQUAL;
extern const int FILM_COMPARE_STRING_LONGER;
extern const int FILM_COMPARE_STRING_SHORTER;
extern const int FILM_COMPARE_STRING_CONTAINS;


// some final variables for fields
extern const int FILM_FIELD_TITLE;
extern const int FILM_FIELD_YEAR;
extern const int FILM_FIELD_CERT;
extern const int FILM_FIELD_GENRE;
extern const int FILM_FIELD_MINUTES;
extern const int FILM_FIELD_RATING;

typedef struct _Film
{
    char* filmTitle;   // Film title
    int filmYear;       // Release year of the film
    char* filmCert;  // Film certification rating
    char* filmGenre;   // Film genre   
    int filmMinutes;    // Film runtime in minutes
    
    int filmRating;   // Film IMDB rating out of 10
                    // stored as an integer value from 0 - 100, and will be 
                    // processed and divided by 10 before returned to ensure
                    // 1 decimal place
}
Film;


/*****************************************************************************

Function    : film_new

Parameters  : char[] title   - film title
              int    year    - year
              char[] cert    - film certification ration
              char[] genre   - film genre
              int minutes - film runtime in minutes
              double rating - film rating out of ten

 
Returns     : Film * - pointer to dynamically allocated Film structure.

Description : Dynamically allocate the memory for a Film structure and 
              initialise to the data given by the arguments.  
  
*****************************************************************************/

Film *film_new(char title[], int year, char cert[], char genre[], 
        int minutes, double rating);

/*****************************************************************************

Function    : film_free

Parameters  : Film *film - pointer to dynamically allocated Film structure.
 
Returns     : void

Description : Free dynamically allocated memory used for a Film structure.
  
*****************************************************************************/

void film_free(Film *film);


/*****************************************************************************

Function    : film_string_into_field

Parameters  : Film *film - pointer to dynamically allocated Film structure.
              int field - number of the field being input to
              char[] str - string of the data
 
Returns     : void

Description : updates the relevant field with the data (converting from string
              if necessary.
  
*****************************************************************************/

void film_string_into_field(Film *film, int field, char str[]);





/*****************************************************************************

Function    : film_getTitle

Parameters  : const Film *film - pointer to a Film structure (n.b. const)
 
Returns     : char[] - title of the film

Description : Accessor method returning the title of the film for a Film
              struct.
  
*****************************************************************************/

char* film_getTitle(const Film *film);

/*****************************************************************************

Function    : film_setTitle

Parameters  : const Film *film    - pointer to a Film structure 
              char[]     title    - title of the film
  
Returns     : void

Description : Mutator/setter function used to alter the film title.
  
*****************************************************************************/

void film_setTitle(Film *film, char title[]);

/*****************************************************************************

Function    : film_getYear

Parameters  : const Film *film - pointer to a Film structure (n.b. const)
 
Returns     : int - year of film

Description : Accessor method returning the year the film was released for a
              Film struct.
  
*****************************************************************************/

int film_getYear(const Film *film);

/*****************************************************************************

Function    : film_setYear

Parameters  : const Film *film    - pointer to a Film structure 
              int        year     - year of the film
  
Returns     : void

Description : Mutator/setter function used to alter the film year.
  
*****************************************************************************/

void film_setYear(Film *film, int year);


/*****************************************************************************

Function    : film_getCert

Parameters  : const Film *film - pointer to a Film structure (n.b. const)
 
Returns     : char[] - certificate of film

Description : Accessor method returning the certificate of a film for a
              Film struct.
  
*****************************************************************************/

char * film_getCert(const Film *film);

/*****************************************************************************

Function    : film_setCert

Parameters  : const Film *film    - pointer to a Film structure 
              char[]      cert    - certificate of the film
  
Returns     : void

Description : Mutator/setter function used to alter the film certificate.
  
*****************************************************************************/

void film_setCert(Film *film, char cert[]);


/*****************************************************************************

Function    : film_getGenre

Parameters  : const Film *film - pointer to a Film structure (n.b. const)
 
Returns     : char[] - genre of film

Description : Accessor method returning the genre of a film for a
              Film struct.
  
*****************************************************************************/

char * film_getGenre(const Film *film);

/*****************************************************************************

Function    : film_setGenre

Parameters  : const Film *film    - pointer to a Film structure 
              char[]      genre   - genre of the film
  
Returns     : void

Description : Mutator/setter function used to alter the film genre.
  
*****************************************************************************/

void film_setGenre(Film *film, char genre[]);

/*****************************************************************************

Function    : film_getMinutes

Parameters  : const Film *film - pointer to a Film structure (n.b. const)
 
Returns     : int - minutes of film

Description : Accessor method returning the runtime in minutes of a film for a
              Film struct.
  
*****************************************************************************/

int film_getMinutes(const Film *film);

/*****************************************************************************

Function    : film_setMinutes

Parameters  : const Film *film    - pointer to a Film structure 
              int        minutes     - year of the film
  
Returns     : void

Description : Mutator/setter function used to alter the film minutes.
  
*****************************************************************************/

void film_setMinutes(Film *film, int minutes);



/*****************************************************************************

Function    : film_getRating

Parameters  : const Film *film - pointer to a Film structure (n.b. const)
 
Returns     : double - rating of film

Description : Accessor method returning the rating of a film for a
              Film struct.
  
*****************************************************************************/

double film_getRating(const Film *film);

/*****************************************************************************

Function    : film_setRating

Parameters  : const Film *film    - pointer to a Film structure 
              double      rating  - rating of the film
  
Returns     : void

Description : Mutator/setter function used to alter the film rating.
  
*****************************************************************************/

void film_setRating(Film *film, double rating);

/*****************************************************************************

Function    : film_compare

Parameters  : const Film *filmA        - pointer to a Film structure 
              Film       *filmB        - pointer to another Film structure 
              int        compareType   - compareType
              int        compareField  - field to compare
  
Returns     : 1 for true, 0 for false

Description : Compares two films based on the selected field
  
*****************************************************************************/

int film_compare(Film *filmA, Film *filmB, int compareType, int compareField);

/*****************************************************************************

Function    : film_compare_int

Parameters  : int intA[]               - int A being compared
              int intB[]               - int B being compared 
              int        compareType   - compareType
  
Returns     : converted string

Description : formats a string ready for comparison
  
*****************************************************************************/

int film_compare_int(int intA,int intB,int compareType);

/*****************************************************************************

Function    : film_compare_string

Parameters  : char strA[]              - string A being compared
              char strB[]              - string B being compared 
              int        compareType   - compareType
  
Returns     : converted string

Description : formats a string ready for comparison
  
*****************************************************************************/

int film_compare_string(char strA[],char strB[],int compareType);

/*****************************************************************************

Function    : film_comparify_string

Parameters  : char str[]        - string to be converted
  
Returns     : converted string

Description : formats a string ready for comparison
  
*****************************************************************************/

char* film_comparify_string(char str[]);

/*****************************************************************************

Function    : film_numberToString

Parameters  : double number        - double containing number 
  
Returns     : a string representation of the number

Description : for turning a number (int or double) into a string
  
*****************************************************************************/

char* film_numberToString(double number,int dp);

/*****************************************************************************

Function    : film_stringToNumber

Parameters  : double number        - double containing number 
  
Returns     : a string representation of the number

Description : for turning a string into a double
  
*****************************************************************************/

double film_stringToNumber(char str[]);

/*****************************************************************************

Function    : film_toString

Parameters  : const Film *film        - pointer to a Film structure 
  
Returns     : string of the film struct as a string

Description : creates a string representation for the film
  
*****************************************************************************/

char* film_toString(Film *film , int filmFields[],int filmFieldsCount);

#endif /* FILM_H */

