# Coursework 1: Website Monitoring


## Requirements

Each web server routinely logs accesses from other web servers and browsers. The log is a text file in which each line contains a date and a hostname. Each date is logged in the format `dd/mm/yyyy`. Each hostname ends with a 2-letter country code such as `uk` or `fr` (or a 3-letter code such as `com`) preceded by a dot/period/full-stop ('`.`'). The final token in a hostname is usually called the **top level domain**, or TLD for short. The log might look like this:

```
        05/11/2018 www.intel.com
        12/12/2018 www.dcs.gla.ac.uk
        05/11/2019 www.mit.edu
        31/12/2018 www.cms.rgu.ac.uk
        25/12/2017 www.informatik.tum.de
        01/04/2018 www.wiley.co.uk
        01/01/2019 www.fiat.it
        14/02/2018 www.valentine.com
```

A new EU regulation requires that tracking access by country, being able to demonstrate the percentage of accesses from each country over a given time period. The politicians have allowed that tracking accesses by TLD is sufficient to satisfy the regulation. If the period of interest is `01/12/2017` to `31/12/2018`, given the above log, the output from the program should look like this:

```
        33.33 com
        16.67 de
        50.00 uk
```

Since the program is to execute on a Linux platform, there is no requirement that the summary statistics be output in any particular order, as we can pipe the output of the program into sort to yield the ordering desired.


## Specification

Given a start date, an end date and one or more log files, the program is to determine the percentage of access from each TLD during that period, outputting the final percentages on standard output, as shown above.

Hostnames, and therefore, top level domain names, are case-insensitive. Therefore, accesses by X.Y.UK and a.b.uk are both accesses from the same TLD.


## Design

The source file with `main()` - `tldmonitor.c` - and header files for two abstract data types - `date.h` and `tldlist.h` - are provided.

### `date.h`

```c
#ifndef _DATE_H_INCLUDED_
#define _DATE_H_INCLUDED_

typedef struct date Date;

Date *date_create(char *datestr);
Date *date_duplicate(Date *d);
int date_compare(Date *date1, Date *date2);
void date_destroy(Date *d);

#endif /* _DATE_H_INCLUDED_ */
```

* The `struct date`, and the corresponding `typedef Date`, define an opaque data structure.
* The constructor for this ADT is `date_create()`; it converts a `datestring` in the format `dd/mm/yyyy` to a `Date` structure. Use `malloc()` to allocate this `Date` structure to return to the user.
* `date_duplicate()` is known as a copy constructor; it duplicates the `Date` argument on the heap (using `malloc()`) and returns it to the user.
* `date_compare()` compares two `Date` structures, returning `<0`, `0`, `>0` if `date1<date2`, `date1==date2`, `date1>date2`, respectively.
* `date_destroy()` returns the heap storage associated with the `Date` structure.

### `tldlist.h`

```c
#ifndef _TLDLIST_H_INCLUDED_
#define _TLDLIST_H_INCLUDED_

#include "date.h"

typedef struct tldlist TLDList;
typedef struct tldnode TLDNode;
typedef struct tlditerator TLDIterator;

TLDList *tldlist_create(Date *begin, Date *end);
void tldlist_destroy(TLDList *tld);
int tldlist_add(TLDList *tld, char *hostname, Date *d);
long tldlist_count(TLDList *tld);
TLDIterator *tldlist_iter_create(TLDList *tld);
TLDNode *tldlist_iter_next(TLDIterator *iter);
void tldlist_iter_destroy(TLDIterator *iter);
char *tldnode_tldname(TLDNode *node);
long tldnode_count(TLDNode *node);

#endif /* _TLDLIST_H_INCLUDED_ */
```

* `TLDList`, `TLDIterator`, and `TLDNode` are opaque data structures that can only be manipulated using methods in this class.
* `tldlist_create()` creates a `TLDList` which can be used to store the counts of log entries against TLD strings; the begin and end date arguments enable filtering of added entries to be in the preferred date range.
* `tldlist_destroy()` returns the heap storage associated with the `TLDList` structure.
* `tldlist_add()` will count the log entry if the associated date is within the preferred data range.
* `tldlist_count()` returns the number of log entries that have been  counted in the list.
* `tldlist_iter_create()` creates an iterator to enable you to iterate over the entries, independent of the data structure chosen for representing the list.
* `tldlist_iter_next()` returns the next `TLDNode` in the list, or `NULL` if there are no more entries.
* `tldnode_tldname()` returns the string for the TLD represented by this node.
* `tldnode_count()` returns the number of log entries that were counted for that TLD.

### `tldmonitor.c`

* The main program is invoked as
```sh
        ./tldmonitor begin_date end_date [file]...
```

* If no file is present in the arguments, `stdin` will be processed. Additionally, if a filename is the string "`-`", the program will process `stdin` at that point.

* The mainline functionality of `tldmonitor.c` consists of the following pseudocode:
```
        process the arguments
        create a TLD list
        if no file args are provided
        process stdin
        else for each file in the argument list
        open the file
        process the file
        close the file
        create an iterator
        while there is another entry in the iterator
        print out the percentage associated with that TLD
        destroy the iterator
        destroy the Date structures
        destroy the TLDList
```

* A static function (`process`) is provided to process all of the log entries in a particular log file.


## Implementation

The implementations of `date.c` and `tldlist.c` must match the function prototypes in the headers listed above.

The program must work correctly with the clang compiler (without using any `--std` flags) on the school `stlinux02..08` systems, regardless of the development and testing platform.

For the implementation of `tldlist.c`, a binary search tree (BST) can be used but this limits the marks to 70%, or a balanced binary search tree (AVL) based upon the Adelson-Velskii and Landis algorithm can be used.

The marks for each source file would depend upon its design, implementation and its ability to perform correctly when executed. Memory leaks would be penalised. `tldmonitor` would be tested against some *very large*, *already sorted* log files. If the code does not compile, no marks would be awarded.