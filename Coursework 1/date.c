#include "date.h"
#include <stdlib.h>
#include <string.h>


/*
 * Date as a structure including 3 integers (`long`) that
 * will be used to divide the string.
 * 
 * day   : day of the month
 * month : month of the year
 * year  : year of existence
 * 
 */
struct date{
    long day;
    long month;
    long year;
};


/*
 * Creates a Date structure from a string that is
 * in the form of "DD/MM/YYYY". 
 * 
 * parameters
 * -----------
 * datestr : date as string/char-pointer
 * 
 * 
 * returns
 * --------
 * Date structure if successfully created, else NULL
 * 
 */
Date *date_create(char *datestr){
    struct date *d;
    if((d = (struct date *)malloc(sizeof(struct date))) != NULL){
        char *token = datestr;
        int i = 0;
        for(token=strtok(datestr, "/"); token!=NULL; token=strtok(NULL, "/"), i++){
            if(i==0) d->day = atoi(token);
            if(i==1) d->month = atoi(token);
            if(i==2) d->year = atoi(token);
        }
    }
    return d;
}


/*
 * Creates a duplicate Date structure from
 * another Date structure.
 * 
 * parameters
 * -----------
 * d : date structure to duplicate
 * 
 * 
 * returns
 * --------
 * Date structure if successfully created, else NULL
 * 
 */
Date *date_duplicate(Date *d){
    struct date *dd;

    if((dd = (struct date *)malloc(sizeof(struct date))) != NULL){
        dd->day = d->day;
        dd->month = d->month;
        dd->year = d->year;
    }
    return dd;
}


/*
int date_compare(Date *date1, Date *date2){

    // This function follows checking for bigger values first.
    //
    // For example,
    // if the years are different, ignore the day and month of
    // the date and blindly return 1 or -1 according to which
    // date has the bigger year.

    if(date1->year!=date2->year){
        if(date1->year > date2->year){
            return 1;
        }
        else{
            return -1;
        }
    }
    else if(date1->month!=date2->month){
        if(date1->month > date2->month){
            return 1;
        }
        else{
            return -1;
        }
    }
    else if(date1->day!=date2->day){
        if(date1->day > date2->day){
            return 1;
        }
        else{
            return -1;
        }
    }
    else{
        return 0;
    }
}
*/

/*
int date_compare(Date *date1, Date *date2){

    // The only difference between this function and the one
    // above is that this doesn't have curly braces since all
    // if-conditions are single lines. Less lines.
    //
    // This function follows checking for bigger values first.
    //
    // For example,
    // if the years are different, ignore the day and month of
    // the date and blindly return 1 or -1 according to which
    // date has the bigger year.

    if(date1->year!=date2->year)
        if(date1->year > date2->year) return 1;
        else return -1;
    else if(date1->month!=date2->month)
        if(date1->month > date2->month) return 1;
        else return -1;
    else if(date1->day!=date2->day)
        if(date1->day > date2->day) return 1;
        else return -1;
    else return 0;
}
*/


/*
 * Compares two given dates and returns a result.
 * 
 * parameters
 * -----------
 * date1 : first date to compare
 * date2 : second date to compare with
 * 
 * 
 * returns
 * --------
 *  1  if date1 > date2
 *  0  if date1 == date2
 * -1  if date1 < date2
 * 
 */
int date_compare(Date *date1, Date *date2){
    /*
    * Function written as a single return statement...
    * ...cause that's how I like it.
    * 
    * However, I understand that code should be readable,
    * therefore there are two other definitions above
    * that are commented out. You may go through whichever.
    * 
    */
    return (
        (date1->year!=date2->year) ? (
            (date1->year > date2->year) ? 1 : -1
        ) : (
            (date1->month!=date2->month) ? (
                (date1->month > date2->month) ? 1 : -1
            ) : (
                (date1->day!=date2->day) ? (
                    (date1->day > date2->day) ? 1 : -1
                ) : 0
            )
        )
    );
}


/*
 * Deletes the pointer from heap since it was
 * created using `malloc` function.
 * 
 * parameters
 * -----------
 * d : Date structure to remove
 * 
 */
void date_destroy(Date *d){
    return (d != NULL) ? free(d) : NULL;
}