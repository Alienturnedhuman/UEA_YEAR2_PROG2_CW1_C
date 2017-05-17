/*****************************************************************************

File        : film.c

Date        : Autumn 2016

Description : Source file for the film struct

Author      : Benjamin Dickson

History     : created from new

******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



#include "film.h"

const int FILM_FIELD_YEAR_MIN = 1870;
const int FILM_FIELD_YEAR_MAX = 2100;
const int FILM_FIELD_MINUTES_MIN = 0;
const int FILM_FIELD_MINUTES_MAX = 1440;


// some final variables for comparison
const int FILM_COMPARE_NOT_EQUAL_TO = 0;
const int FILM_COMPARE_EQUAL_TO = 1;
const int FILM_COMPARE_GREATER_THAN = 2;
const int FILM_COMPARE_GREATER_OR_EQUAL_TO = 3;
const int FILM_COMPARE_LESS_THAN = 4;
const int FILM_COMPARE_LESS_OR_EQUAL_TO = 5;
const int FILM_COMPARE_STRING_LENGTH_NOT_EQUAL = 32;
const int FILM_COMPARE_STRING_LENGTH_EQUAL = 33;
const int FILM_COMPARE_STRING_LONGER = 34;
const int FILM_COMPARE_STRING_SHORTER = 35;
const int FILM_COMPARE_STRING_CONTAINS = 36;


// some final variables for fields
const int FILM_FIELD_TITLE = 0;
const int FILM_FIELD_YEAR = 1;
const int FILM_FIELD_CERT = 2;
const int FILM_FIELD_GENRE = 3;
const int FILM_FIELD_MINUTES = 4;
const int FILM_FIELD_RATING = 5;

/*
 * 
 */
Film *film_new(char title[], int year, char cert[], char genre[], 
        int minutes, double rating)
{
    Film *film = (Film*)malloc(sizeof(Film));
    
    if (film == NULL)
    {
       fprintf(stderr, "Error: Unable to allocate memory in film_new()\n");

       exit(EXIT_FAILURE);
    }
    
    film_setTitle(film,title);
    film_setYear(film,year);
    film_setCert(film,cert);
    film_setGenre(film,genre);
    film_setMinutes(film,minutes);
    film_setRating(film,rating);
    
    return film;
}


void film_free(Film *film)
{
    free(film);
}


void film_string_into_field(Film *film, int field, char str[])
{
    // I realised I could have, and probably should have, done this with
    // enums rather than switch/case on integers - although the effective result
    // is the same.
    switch(field)
    {
        case FILM_FIELD_TITLE:
            film_setTitle(film,str);
            break;
        case FILM_FIELD_YEAR:
            film_setYear(film,(int)(film_stringToNumber(str)));
            break;
        case FILM_FIELD_CERT:
            film_setCert(film,str);
            break;
        case FILM_FIELD_GENRE:
            film_setGenre(film,str);
            break;
        case FILM_FIELD_MINUTES:
            film_setMinutes(film,(int)(film_stringToNumber(str)));
            break;
        case FILM_FIELD_RATING:
            film_setRating(film,film_stringToNumber(str));
            break;
    }
}
char* film_getTitle(const Film *film)
{
    return film->filmTitle;
}

void film_setTitle(Film *film, char title[])
{
    char* temp = calloc(strlen(title)+1,sizeof(char));
    strcpy(temp,title);
    film->filmTitle = temp;
}


int film_getYear(const Film *film)
{
    return film->filmYear;
}
void film_setYear(Film *film, int year)
{
    int temp = year;
    
    // ensure year is within correct bounds
    // alternatively this could throw an error, but for now, just set to closest
    // value
    if(temp>=FILM_FIELD_YEAR_MAX)
    {
        temp = FILM_FIELD_YEAR_MAX;
    }
    if(temp<=FILM_FIELD_YEAR_MIN)
    {
        temp = FILM_FIELD_YEAR_MIN;
    }
    
    film->filmYear = temp;
}

char * film_getCert(const Film *film)
{
    return film->filmCert;
}


void film_setCert(Film *film, char cert[])
{
    char* temp = calloc(strlen(cert)+1,sizeof(char));
    strcpy(temp,cert);
    film->filmCert = temp;
}

char * film_getGenre(const Film *film)
{
    return film->filmGenre;
}

void film_setGenre(Film *film, char genre[])
{
    //film->filmGenre = genre;
    int i =-1;
    int ii = strlen(genre);
    char* tmp = calloc(ii+1,sizeof(char));
    
    
    // for some reason strcpy caused an error, despite being identical to all
    // other implementations
    //strcpy(tmp,genre);
    while(++i<ii)
    {
        tmp[i]=genre[i];
    }
    
    
    film->filmGenre = tmp;
}

int film_getMinutes(const Film *film)
{
    return film->filmMinutes;
}

void film_setMinutes(Film *film, int minutes)
{
    int temp = minutes;
    
    // ensure year is within correct bounds
    // alternatively this could throw an error, but for now, just set to closest
    // value
    if(temp>=FILM_FIELD_MINUTES_MAX)
    {
        temp = FILM_FIELD_MINUTES_MAX;
    }
    if(temp<=FILM_FIELD_MINUTES_MIN)
    {
        temp = FILM_FIELD_MINUTES_MIN;
    }
    
    film->filmMinutes = temp;
}

void film_setRating(Film *film, double rating)
{
    // rating is stored as integer 0 to 100 to save on memory used
    int temp = (int)((rating * 10)+0.5);
   
    // ensure rating is not outside the 0 (0.0) to 100 (10.0) boundaries
    if(temp>100)
    {
        temp=100;
    }
    if(temp<0)
    {
        temp=0;
    }
    film->filmRating = temp;
}

double film_getRating(const Film *film)
{
    double rating = ((double)(film->filmRating));
    return rating/10;
}


int film_compare(Film *filmA, Film *filmB, int compareType, int compareField)
{
    // start with false condition, and change to true if required
    int r=0;
    
    // could have done this with an enum, as explained before
    switch (compareField)
    {
        case FILM_FIELD_RATING:
            r = film_compare_int(filmA->filmRating , filmB->filmRating ,
                    compareType);
            break;
        case FILM_FIELD_MINUTES:
            r = film_compare_int(filmA->filmMinutes , filmB->filmMinutes ,
                    compareType);
            break;
        case FILM_FIELD_GENRE:
            r = film_compare_string(filmA->filmGenre , filmB->filmGenre ,
                    compareType);
            break;
        case FILM_FIELD_CERT:
            r = film_compare_string(filmA->filmCert , filmB->filmCert ,
                    compareType);
            break;
        case FILM_FIELD_YEAR:
            r = film_compare_int(filmA->filmYear , filmB->filmYear ,
                    compareType);
            break;
        // comparing title is the default behavior if no/invalid field
        // is provided. Again, alternatively, an error could be thrown
        // for this, depending on the requirements. For now we'll assume by
        // default people would want to compare on title
        case FILM_FIELD_TITLE:
        default:
            r = film_compare_string(filmA->filmTitle , filmB->filmTitle ,
                    compareType);
            break;
    }
    return r;
}


int film_compare_int(int intA,int intB,int compareType)
{
    // default return is a fail
    int r=0;
    
    // switch through different comparison types and perform on the two ints
    switch(compareType)
    {
        case FILM_COMPARE_LESS_OR_EQUAL_TO:
            if(intA<=intB)
            {
                r=1;
            }
            break;
        case FILM_COMPARE_LESS_THAN:
            if(intA<intB)
            {
                r=1;
            }
            break;
        case FILM_COMPARE_GREATER_OR_EQUAL_TO:
            if(intA>=intB)
            {
                r=1;
            }
            break;
        case FILM_COMPARE_GREATER_THAN:
            if(intA>intB)
            {
                r=1;
            }
            break;
        case FILM_COMPARE_NOT_EQUAL_TO:
            if(intA!=intB)
            {
                r=1;
            }
            break;
        case FILM_COMPARE_EQUAL_TO:
        default:
            if(intA==intB)
            {
                r=1;
            }
    }
    return r;
}

char* film_comparify_string(char str[])
{
    // strings will be converted to blockCAPS with non alpha numerical
    // characters converted into single characters of whitespace.
    // eg: "Hello world!" -> "HELLO WORLD"
    // eg: "I'm Fred, the 2nd dog!!!" -> "I M FRED THE 2ND DOG "
    char* tStr = malloc(strlen(str));
    
    int rStrSize = 0;
    int lastChar = 0;
    char currentChar;
    int i=0;
    int ii = strlen(str);
    for(i=0; i<ii; i++)
    {
        currentChar = str[i];
        if(
            (currentChar>47&&currentChar<58)
            ||
            (currentChar>64&&currentChar<91)
        )
        {
            // first condition is capital letters or numbers
            tStr[rStrSize++]=currentChar;
            lastChar=currentChar;
        }
        else if(currentChar>96&&currentChar<123)
        {
            // second condition is lowercase letters, which are converted
            // to uppercase
            tStr[rStrSize++]=currentChar-32;
            lastChar=currentChar-32;
        }
        else if(lastChar!=32)
        {
            // if neither of the above, and the previous character was not
            // space, add a space character
            tStr[rStrSize++]=32;
            lastChar=32;
        }
    }
    
    // allocate memory for reduced string size
    char* rStr = malloc(rStrSize);
    
    // pass characters into that new string
    i = 0;
    for(i=0; i<rStrSize; i++)
    {
        rStr[i] = tStr[i];
    }
    
    // free temporary String;
    free(tStr);
    
    return rStr;
}


int film_compare_string(char strA[],char strB[],int compareType)
{
    // default return value to 0
    int r=0;
    
    
    // make comparable versions of strings
    char* cStrA = film_comparify_string(strA);
    char* cStrB = film_comparify_string(strB);
    
    
    // get lengths of these strings
    int cLenStrA = strlen(cStrA);
    int cLenStrB = strlen(cStrB);
    
    // relative difference between strings
    int sDiff=0;    // -1 = less than, 0 = equal, 1 = greater than
    
    // iterate through each character of the strings and compare
    int shortest = (cLenStrA<cLenStrB)?cLenStrA:cLenStrB;
    int i=-1;
    int stillEqual=1;
    while(++i<shortest && stillEqual)
    {
        if(cStrA[i]<cStrB[i])
        {
            sDiff=-1;
            stillEqual=0;
        }
        else if(cStrA[i]>cStrB[i])
        {
            sDiff=1;
            stillEqual=0;
        }
    }
    if(stillEqual && cLenStrA!=cLenStrB)
    {
        // longest string is 'greater'
        sDiff = cLenStrA>cLenStrB?1:-1;
    }
    
    // switch through comparison types
    switch(compareType)
    {
        case FILM_COMPARE_STRING_CONTAINS:
            // searches for a strB in strA
            if(strlen(strA)<strlen(strB))
            {
                // strA is longer, can't contain strB
                return 0;
            }
            else
            {
                i = -1;
                int startPos = -1;
                int searchCheck = 0;
                int ii = strlen(strA);
                while(++i<ii)
                {
                    if(startPos==-1)
                    {
                        if(strA[i]==strB[0])
                        {
                            startPos = i;
                            searchCheck = 1;
                        }
                    }
                    else
                    {
                        if(strA[i]==strB[i-startPos])
                        {
                            if(++searchCheck>=strlen(strB))
                            {
                                return 1;
                            }
                        }
                        else if(strA[i]==strB[0])
                        {
                            startPos = i;
                            searchCheck = 1;
                        }
                        else
                        {
                            startPos = -1;
                            searchCheck = 0;
                        }
                    }
                }
                return 0;
            }
            break;
        case FILM_COMPARE_STRING_LENGTH_NOT_EQUAL:
            if(strlen(strA)!=strlen(strB))
            {
                r=1;
            }
            break;
        case FILM_COMPARE_STRING_LENGTH_EQUAL:
            if(strlen(strA)==strlen(strB))
            {
                r=1;
            }
            break;
        case FILM_COMPARE_STRING_LONGER:
            if(strlen(strA)>strlen(strB))
            {
                r=1;
            }
            break;
        case FILM_COMPARE_STRING_SHORTER:
            if(strlen(strA)<strlen(strB))
            {
                r=1;
            }
            break;
        case FILM_COMPARE_LESS_OR_EQUAL_TO:
            if(sDiff<=0)
            {
                r=1;
            }
            break;
        case FILM_COMPARE_LESS_THAN:
            if(sDiff<0)
            {
                r=1;
            }
            break;
        case FILM_COMPARE_GREATER_OR_EQUAL_TO:
            if(sDiff>=0)
            {
                r=1;
            }
            break;
        case FILM_COMPARE_GREATER_THAN:
            if(sDiff>0)
            {
                r=1;
            }
            break;
        case FILM_COMPARE_NOT_EQUAL_TO:
            if(sDiff!=0)
            {
                r=1;
            }
            break;
        case FILM_COMPARE_EQUAL_TO:
        default:
            if(sDiff==0)
            {
                r=1;
            }
    }
    
    free(cStrA);
    free(cStrB);
    return r;
}

double film_stringToNumber(char str[])
{
    // note, this only deals with positive numbers or zero as those are the 
    // only types of numbers found in this project
    // it could be updated for negative numbers quite easily though, by checking
    // if the first digit is a minus sign
    double r = 0;
    int s=0;
    int ss=strlen(str);
    char chr = str[s];
    
    
    // do the integer part of the number
    while((chr>47&&chr<58))
    {
        r = (r*10)+(chr-48);
        chr=str[++s];
    }
    // if the next character is a decimal point, continue for remaining digits
    if(chr==46)
    {
        chr=str[++s];
        double f=0.1;
        while((chr>47&&chr<58))
        {
            r=r+(f*(chr-48));
            f=f/10;
            chr=str[++s];
        }
    }
    return r;
}

char* film_numberToString(double number,int dp)
{
    // note this only works for positive numbers or zero as there are no
    // negative numbers in this project
    
    if(dp==0)
    {
        number = number+0.5;
    }
    
    // first grab the integer part
    int integerPart = (int)(number);
    
    // calculate how many digits long it it
    int digits=1;
    int processInt = integerPart/10;
    while(processInt>0)
    {
        digits++;
        processInt = processInt/10;
    }
    
    // determine if the number is whole or not
    int isFraction=(dp==0||number-integerPart==0)?0:1;
    int fractionDigits=0;
    
    int strLength=digits+1;
    double fractionPart;
    
    // if it is not a whole number, determine the number of decimal places
    if(isFraction)
    {
        fractionPart = number-integerPart;
        if(dp==-1)
        {
            double iFractionPart = fractionPart;
            while(iFractionPart>0)
            {
                iFractionPart = (iFractionPart*10) - (int)(iFractionPart*10);
                fractionDigits++;
            }
        }
        else            
        {
            fractionDigits=dp;
            int fd = -1;
            double adjuster = 0.5;
            while(++fd<dp)
            {
                adjuster = adjuster/10;
            }
            fractionPart = fractionPart + adjuster;
        }
        strLength = digits + 2 + fractionDigits; // + 1 is for decimal point
    }
    
    char* r = malloc(strLength);
    
    
    int i=-1;
    while(++i<strLength)
    {
        r[i]=0;
    }
    
    i = -1;
    int thisDigit;
    processInt = integerPart;
    while(++i<digits)
    {
        thisDigit = 48 + processInt%10;
        r[digits-i-1]=thisDigit;
        processInt = processInt/10;
    }
    if(isFraction)
    {
        r[digits] = 46;
        i = -1;
        while(++i<fractionDigits)
        {
            thisDigit = 48 + (int)(fractionPart*10);
            r[digits+1+i]=thisDigit;
            fractionPart = (fractionPart*10)-(int)(fractionPart*10);
        }
    }
    
    return r;
}


char* film_toString(Film *film , int filmFields[],int filmFieldsCount)
{
    char *r;
 
    char* str_title = film_getTitle(film);
    char* str_minutes = film_numberToString((double)film_getMinutes(film),-1);
    char* str_year = film_numberToString((double)film_getYear(film),-1);
    char* str_cert = film_getCert(film);
    char* str_genre = film_getGenre(film);
    char* str_rating = film_numberToString(film_getRating(film),1);
    
    if(filmFieldsCount>0)
    {
        
        
        int i=-1;
        int ii=filmFieldsCount; 
        int rSize=0;
        while(++i<ii)
        {
            switch(filmFields[i])
            {
                case FILM_FIELD_RATING:
                    rSize = rSize + 1 + strlen(str_rating);
                    break;
                case FILM_FIELD_MINUTES:
                    
                    rSize = rSize + 1 + strlen(str_minutes);
                    break;
                case FILM_FIELD_GENRE:
                    rSize = rSize + 1 + strlen(str_genre);
                    break;
                case FILM_FIELD_CERT:
                    rSize = rSize + 1 + strlen(str_cert);
                    break;
                case FILM_FIELD_YEAR:
                    rSize = rSize + 1 + strlen(str_year);
                    break;
                case FILM_FIELD_TITLE:
                    rSize = rSize + 1 + strlen(str_title);
                    break;
            }
        }
        
        i=-1;
        r = (char *) malloc(rSize+1);
        
        while(++i<=rSize)
        {
            r[i]=0;
        }
        i=-1;
        
        int cpos = 0;
        char* temp_blank = "";
        char* thisField=temp_blank;
        
        while(++i<ii)
        {
            if(i>0)
            {
                r[cpos]=9;  // insert tab delimiter
                cpos++;
            }
            switch(filmFields[i])
            {
                case FILM_FIELD_RATING:
                    thisField = str_rating;
                    break;
                case FILM_FIELD_MINUTES:
                    
                    thisField = str_minutes;
                    break;
                case FILM_FIELD_GENRE:
                    thisField = str_genre;
                    break;
                case FILM_FIELD_CERT:
                    thisField = str_cert;
                    break;
                case FILM_FIELD_YEAR:
                    thisField = str_year;
                    break;
                case FILM_FIELD_TITLE:
                    thisField = str_title;
                    break;
            }
            int j=-1;
            int jj = strlen(thisField);
            while(++j<jj)
            {
                r[cpos+j]=thisField[j];
            }
            cpos = cpos + j;
            
        }
    }
    
    free(str_rating);
    free(str_minutes);
    free(str_year);
    return r;
}