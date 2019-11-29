!!$ Copyright (C) 2019 by Angel de Vicente, angel.de.vicente@iac.es 
!!$    https://github.com/angel-devicente/                     
!!$
!!$ ******************************************************************
!!$ * Angel de Vicente 
!!$ *
!!$ * A simple test function for 6D memoizatioin_ja.c
!!$ * 
!!$ ******************************************************************
!!$ * TO DO: 
!!$ *   + add proper tests 
!!$ ******************************************************************

program memo_ja
  use SUFR_getopt
  use memoization_ja
  implicit none

  ! poistion and value in array
  integer :: l1,l2,l3,l4,l5,l6,rv
  real :: lr
  double precision :: v

  ! A:   jagged array
  ! val: pointer to result of search in array
  type(a6D) :: A
  double precision, pointer :: val
  
  ! command line argument default values 
  integer :: nvals=1000;
  integer :: nsearch=1000;
  integer :: maxc=40;
  integer :: d=0;

  !! timing
  integer :: t1,t2,tt=0,count_rate, count_max
  
  ! 
  character :: opt 

  !==================================================================

  ! Initialize Jagged Array
  nullify(A%d)

  ! Read command line arguments
  do
     opt = getopt("hdn:w:s:")
     select case(opt)
     case('h')
        print*, "Usage: memo_ja [-h] [-n nvals] [-w maxc] [-s nsearch]"
        print*, "  -h         : displays this help"
        print*, "  -d         : debug mode (will print all insertions, info on searches and state of the array)"
        print*, "  -n nvals   : nvals (default=1000) is the number of values to add to the array"
        print*, "  -w maxc    : maxc (default=40) is the maximum length of each of the array dimensions"
        print*, "  -s nsearch : nsearch (default=1000) is the number of elements to search for in the array"
        stop
     case('d')
        d=1
     case('n')
        read (optArg,*) nvals
     case('w')
        read (optArg,*) maxc
     case('s')
        read (optArg,*) nsearch
     case('>')
        exit
     case('!')
        print*, "Invalid argument ",trim(optArg)," (EXITING)"
     end select
  end do

  write(*,'(A)') NEW_LINE('A')//'Testing 6D memoization with Jagged Arrays'
  write(*,'(A)') "=========================================="

  write(*,'(A,I0,A,I0,A)') "Inserting ",nvals, &
       " random values in random positions of the array (max dimension value: ",maxc,")"
  print*, ""
  
  do rv=1,nvals
     call random_number(lr) ; l1 = FLOOR(lr*(2*maxc+1)) - maxc
     call random_number(lr) ; l2 = FLOOR(lr*(2*maxc+1)) - maxc
     call random_number(lr) ; l3 = FLOOR(lr*(2*maxc+1)) - maxc
     call random_number(lr) ; l4 = FLOOR(lr*(2*maxc+1)) - maxc
     call random_number(lr) ; l5 = FLOOR(lr*(2*maxc+1)) - maxc
     call random_number(lr) ; l6 = FLOOR(lr*(2*maxc+1)) - maxc
     call random_number(v)

     if (d == 1) write(*,'(A,F9.6,A,6I2)') "Inserting val: ",v," at positions: ",l1,l2,l3,l4,l5,l6
     call insert6D(l1,l2,l3,l4,l5,l6,v,A);

     if (d == 1) then
        write(*,*) "Jagged array:"
        call print_jA6D(A)
        print*, "" ; print*, ""
     end if
  end do
   
  write(*,'(A,I0,A,I0,A)') NEW_LINE('A')//"Checking for ",nsearch, &
       " random positions of the array (max dimension value: ",maxc,")"
  print*, ""

  do rv=1,nsearch
     call random_number(lr) ; l1 = FLOOR(lr*(2*maxc+1)) - maxc
     call random_number(lr) ; l2 = FLOOR(lr*(2*maxc+1)) - maxc
     call random_number(lr) ; l3 = FLOOR(lr*(2*maxc+1)) - maxc
     call random_number(lr) ; l4 = FLOOR(lr*(2*maxc+1)) - maxc
     call random_number(lr) ; l5 = FLOOR(lr*(2*maxc+1)) - maxc
     call random_number(lr) ; l6 = FLOOR(lr*(2*maxc+1)) - maxc
     call random_number(v)
    
     if (d == 1) write(*,'(A,6I2)') "Checking position: ",l1,l2,l3,l4,l5,l6

     call system_clock(t1, count_rate, count_max)
     val => elem6D(l1,l2,l3,l4,l5,l6,A);
     call system_clock(t2, count_rate, count_max)
     tt = tt + (t2-t1)

     if (d == 1 .and. associated(val)) print*, val
  end do

  if (nsearch > 0) write(*,'(I0,A,I0,A,F9.6,A)') nsearch," positions searched (see README.md for notes) in a 6D array of size ", &
       maxc," in ", tt*1.0/count_rate," seconds"

  call mem_free_6D()

end program memo_ja
