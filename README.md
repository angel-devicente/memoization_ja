
# Table of Contents

1.  [Memoization with Jagged Arrays](#orgb9ad14b)
    1.  [Compilation of test code](#org598f75d)
        1.  [C version](#orga171830)
        2.  [Fortran version](#org5a3ac63)
    2.  [Usage](#orgca15d34)
    3.  [Timing](#orgf05045c)



<a id="orgb9ad14b"></a>

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


<a id="org598f75d"></a>

## Compilation of test code

There are C and Fortran versions:


<a id="orga171830"></a>

### C version

The actual code that does the memoization and that can be adapted to arrays of
more than 6D is in \`memoization\_ja.c\` and \`memoization\_ja.h\`. \`memo\_ja.c\` is
just a simple code to test the memoization insertion and searching routines.

To compile the code just do:

    $ make
    gcc -Wall -O3 -c memoization_ja.c -o memoization_ja.o
    gcc -Wall -O3 -c memo_ja.c -o memo_ja.o
    gcc  memoization_ja.o  memo_ja.o -Wall -lm -o memo_ja


<a id="org5a3ac63"></a>

### Fortran version

The actual code that does the memoization and that can be adapted to arrays of
more than 6D is in \`memoization\_ja.f90\`. \`memo\_ja.f90\` is
just a simple code to test the memoization insertion and searching routines.

To compile the code just do:

    $ make
    gfortran -Wall -O3 getopt.f90 memoization_ja.f90 memo_ja.f90 -o memo_ja


<a id="orgca15d34"></a>

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


<a id="orgf05045c"></a>

## Timing

The information on the time taken to search items in the array has to be taken
with a pinch of salt. As it is, (let's call this V1) in Fortran we do (and
similarly in C, with the function *clock*):

    call system_clock(t1, count_rate, count_max)
    val => elem6D(l1,l2,l3,l4,l5,l6,A);
    call system_clock(t2, count_rate, count_max)
    tt = tt + (t2-t1)

but the time it takes to run elem6D is so small that the time differences
between *clock* and *system\_clock* in C and Fortran respectively introduce a lot
of noise to the measuring as we will see below. This should be the right way to
measure the time taken by only the function *elem6D*, but it is very
misleading. 

So, another way (let's call this V2) is to measure the whole *for* loop, doing
(this time in C), something like:

    t1 = clock();
    for (int rv=0 ; rv < nsearch ; rv++) {
      l1 = (rand() % (2*maxc+1)) - maxc;
      l2 = (rand() % (2*maxc+1)) - maxc;
      l3 = (rand() % (2*maxc+1)) - maxc;
      l4 = (rand() % (2*maxc+1)) - maxc;
      l5 = (rand() % (2*maxc+1)) - maxc;
      l6 = (rand() % (2*maxc+1)) - maxc;
      v = drand48();
    
      if (d) printf("Checking position: %d %d %d %d %d %d \n",l1,l2,l3,l4,l5,l6);
      val = elem6D(l1,l2,l3,l4,l5,l6,A);
      if (d && val) printf("%f \n",*val); 
    }
      t2 = clock();
      cpu_time += (t2-t1);

In this case, the problem is that the different costs of calculating random
numbers in C and Fortran also play a role in the measuring.

So, a third way (let's call this V3) is to move the selection of *l1,l2,..*
outside of the *for* searching loop, so that all searches will actually be to
the same position, but at least we are not measuring the time for the
calculation of random numbers. So, we could have (in C) something like: 

    t1 = clock();
    for (int rv=0 ; rv < nsearch ; rv++) {
      if (d) printf("Checking position: %d %d %d %d %d %d \n",l1,l2,l3,l4,l5,l6);
      val = elem6D(l1,l2,l3,l4,l5,l6,A);
      if (d && val) printf("%f \n",*val); 
    }
      t2 = clock();
      cpu_time += (t2-t1);

The problem with this method is that we are always looking in the same position, which
is not a realistic scenario, and it probably is too cache friendly. 

So, ideally I would like to have a V1 timing, but without the overhead produced
by *clock* or *system\_clock*.

In any case, sample timings for the versions above in may machine give:

<table border="2" cellspacing="0" cellpadding="6" rules="groups" frame="hsides">


<colgroup>
<col  class="org-left" />

<col  class="org-left" />

<col  class="org-left" />

<col  class="org-left" />
</colgroup>
<thead>
<tr>
<th scope="col" class="org-left">Version</th>
<th scope="col" class="org-left">Fortran</th>
<th scope="col" class="org-left">C</th>
<th scope="col" class="org-left">command used</th>
</tr>
</thead>

<tbody>
<tr>
<td class="org-left">V1</td>
<td class="org-left">0.41s</td>
<td class="org-left">4.5s</td>
<td class="org-left">./memo\_ja -n 100 -w 15  -s 10000000</td>
</tr>


<tr>
<td class="org-left">V2</td>
<td class="org-left">7.32s</td>
<td class="org-left">7.82s</td>
<td class="org-left">./memo\_ja -n 100 -w 15  -s 100000000</td>
</tr>


<tr>
<td class="org-left">V3</td>
<td class="org-left">8.95s</td>
<td class="org-left">4.7s</td>
<td class="org-left">./memo\_ja -n 100 -w 15  -s 1000000000</td>
</tr>
</tbody>
</table>

So it looks like C should be faster than Fortran here, but I need to get a more
reliable way to time this. 

