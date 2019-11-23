
# Table of Contents

1.  [Memoization with Jagged Arrays](#orgb71ba91)
    1.  [Compilation of test code](#orgc12ca41)
        1.  [C version](#orgad2462a)
        2.  [Fortran version](#orgb3c2364)
    2.  [Usage](#org7b42d44)



<a id="orgb71ba91"></a>

# Memoization with Jagged Arrays

Memoization is a useful technique in many codes, but an efficient implementation
is not always easy.

This code demonstrates how to use dynamic jagged arrays for memoization. My goal
in writing this was for a particular application in which I needed 6D array
memoization.

The idea is to dynamically create a jagged array as needed, when new data points
are added. On initialization, the jagged array will have a size of 0, then when
new elements are inserted, the jagged array will grow to accommodate the new data
point. 

(graphical explanation of the building up of the jagged array to be added)


<a id="orgc12ca41"></a>

## Compilation of test code

There are C and Fortran versions:


<a id="orgad2462a"></a>

### C version

The actual code that does the memoization and that can be adapted to arrays of
more than 6D is in \`memoization\\\_ja.c\` and \`memoization\\\_ja.h\`. \`memo\\\_ja.c\` is
just a simple code to test the memoization insertion and searching routines.

To compile the code just do:

    $ make
    gcc -Wall -O3 -c memoization_ja.c -o memoization_ja.o
    gcc -Wall -O3 -c memo_ja.c -o memo_ja.o
    gcc  memoization_ja.o  memo_ja.o -Wall -lm -o memo_ja


<a id="orgb3c2364"></a>

### Fortran version

The actual code that does the memoization and that can be adapted to arrays of
more than 6D is in \`memoization\\\_ja.f90\`. \`memo\\\_ja.f90\` is
just a simple code to test the memoization insertion and searching routines.

To compile the code just do:

    $ make
    gfortran -Wall -O3 getopt.f90 memoization_ja.f90 memo_ja.f90 -o memo_ja


<a id="org7b42d44"></a>

## Usage

To see the usage, just run:

    $ ./memo_ja -h
    Usage: ./memo_ja [-h] [-n nvals] [-w maxc] [-s nsearch]
      -h         : displays this help
      -d         : debug mode (will print all insertions, info on searches and state of the array)
      -n nvals   : nvals (default=1000) is the number of values to add to the array
      -w maxc    : maxc (default=40) is the maximum length of each of the array dimensions
      -s nsearch : nsearch (default=1000) is the number of elements to search for in the array

For example, to see how the array grows as needed and how diferent positions are
searched, we can run:

    $ ./memo_ja -n 4 -w 2 -s 4 -d
    
    Testing 6D memoization with Jagged Arrays 
    ========================================== 
    Inserting 4 random values in random positions of the array (max dimension value: 2)
    
    Inserting val: 0.000000 at positions: 1 1 0 1 2 1
    Jagged array:
    ----------- 
    A[1,1,0,1,2,1] is: 0.000000 
    
    
    Inserting val: 0.000985 at positions: 1 0 0 1 2 1
    Jagged array:
    ----------- 
    A[1,0,0,1,2,1] is: 0.000985 
    A[1,1,0,1,2,1] is: 0.000000 
    
    
    Inserting val: 0.041631 at positions: 2 1 2 1 0 0
    Jagged array:
    ----------- 
    A[1,0,0,1,2,1] is: 0.000985 
    A[1,1,0,1,2,1] is: 0.000000 
    A[2,1,2,1,0,0] is: 0.041631 
    
    
    Inserting val: 0.176643 at positions: 1 1 2 2 0 0
    Jagged array:
    ----------- 
    A[1,0,0,1,2,1] is: 0.000985 
    A[1,1,0,1,2,1] is: 0.000000 
    A[1,1,2,2,0,0] is: 0.176643 
    A[2,1,2,1,0,0] is: 0.041631 
    
    
    Checking for 4 random positions of the array (max dimension value: 2)
    
    Checking position: 2 2 2 1 1 1 
    Checking position: 2 0 0 0 2 0 
    Checking position: 1 1 1 1 0 0 
    Checking position: 0 2 2 1 2 2 
    4 positions searched in a 6D array of size 2 in 0.000002 seconds

A more interesting examaple would be the following, where we have a 6D array,
where each dimension has size 31 [0-30], we insert 100 values at random
positions in it, and then search for 1e6 elements in it. In my machine,
searching for this 1 million random positions in the array takes 0.47 seconds,
and the memory needed for it is only a few kilobytes, as opposed to the nearly
7GB that the full 31^6 array would take.

    $ ./memo_ja -n 100 -w 30 -s 1000000
    
    Testing 6D memoization with Jagged Arrays 
    ========================================== 
    Inserting 100 random values in random positions of the array (max dimension value: 30)
    
    Checking for 1000000 random positions of the array (max dimension value: 30)
    
    1000000 positions searched in a 6D array of size 30 in 0.470221 seconds

