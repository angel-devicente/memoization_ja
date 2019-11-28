!!$ * Copyright (C) 2019 by Angel de Vicente, angel.de.vicente@iac.es 
!!$    https://github.com/angel-devicente/                     
!!$ 
!!$ ******************************************************************
!!$ * Angel de Vicente 
!!$ *
!!$ * A simple program to perform memoization with dynamic jagged arrays
!!$ * 
!!$ ******************************************************************
!!$ * TO DO: 
!!$ *   + add proper description
!!$ *   + add error handling to code
!!$ ******************************************************************/

module memoization_ja

  type scalar
     double precision, pointer :: d
  end type scalar
  
  type a1D
     type(scalar), dimension(:), pointer :: d
  end type a1D

  type a2D
     type(a1D), dimension(:), pointer :: d
  end type a2D

  type a3D
     type(a2D), dimension(:), pointer :: d
  end type a3D

  type a4D
     type(a3D), dimension(:), pointer :: d
  end type a4D
  
  type a5D
     type(a4D), dimension(:), pointer :: d
  end type a5D

  type a6D
     type(a5D), dimension(:), pointer :: d
  end type a6D

contains

!************************************************************** 
!
! Inserting functions for 1D-6D memoization jagged arrays 
!
!***************************************************************
  
  subroutine insert_scalar(val, A)
    double precision :: val
    type(scalar) :: A

    if (associated(A%d)) then
       print*, "---> Repeated element. Ignoring: ", val
    else
       allocate(A%d)
       A%d = val
    end if
  end subroutine insert_scalar


  subroutine insert1D(l1, val, A)
    integer :: l1
    double precision :: val
    type(a1D) :: A

    integer :: d_size,i
    type(scalar), dimension(:), pointer :: d_t
    
    if (associated(A%d)) then
       if (l1 < size(A%d)) then
          call insert_scalar(val,A%d(l1))
       else   ! not big enough: we need to realloc and place value
          d_size = size(A%d)
          allocate(d_t(0:l1))
          do i=0,d_size-1
             d_t(i)%d => A%d(i)%d
          end do
          do i=d_size,l1
             d_t(i)%d => null()
          end do
          deallocate(A%d)
          A%d => d_t
          call insert_scalar(val,A%d(l1))
       end if

    else
       ! dimension does not exist yet: create and place value
       allocate(A%d(0:l1))
       do i=0,l1
          A%d(i)%d => null()
       end do
       call insert_scalar(val,A%d(l1))
    end if
  end subroutine insert1D


  subroutine insert2D(l1, l2, val, A)
    integer :: l1, l2
    double precision :: val
    type(a2D) :: A
    
    integer :: d_size
    type(a1D), dimension(:), pointer :: d_t
    
    if (associated(A%d)) then
       if (l1 < size(A%d)) then
          call insert1D(l2,val,A%d(l1))
       else   ! not big enough: we need to realloc and place value
          d_size = size(A%d)
          allocate(d_t(0:l1))
          do i=0,d_size-1
             d_t(i)%d => A%d(i)%d
          end do
          do i=d_size,l1
             d_t(i)%d => null()
          end do
          deallocate(A%d)
          A%d => d_t
          call insert1D(l2,val,A%d(l1))
       end if

    else
       ! dimension does not exist yet: create and place value
       allocate(A%d(0:l1))
       do i=0,l1
          A%d(i)%d => null()
       end do
       call insert1D(l2,val,A%d(l1))
    end if
  end subroutine insert2D


  subroutine insert3D(l1, l2, l3, val, A)
    integer :: l1,l2,l3
    double precision :: val
    type(a3D) :: A
    
    integer :: d_size
    type(a2D), dimension(:), pointer :: d_t
    
    if (associated(A%d)) then
       if (l1 < size(A%d)) then
          call insert2D(l2,l3,val,A%d(l1))
       else   ! not big enough: we need to realloc and place value
          d_size = size(A%d)
          allocate(d_t(0:l1))
          do i=0,d_size-1
             d_t(i)%d => A%d(i)%d
          end do
          do i=d_size,l1
             d_t(i)%d => null()
          end do
          deallocate(A%d)
          A%d => d_t
          call insert2D(l2,l3,val,A%d(l1))
       end if

    else
       ! dimension does not exist yet: create and place value
       allocate(A%d(0:l1))
       do i=0,l1
          A%d(i)%d => null()
       end do
       call insert2D(l2,l3,val,A%d(l1))
    end if
  end subroutine insert3D


  subroutine insert4D(l1, l2, l3, l4, val, A)
    integer :: l1,l2,l3,l4
    double precision :: val
    type(a4D) :: A
    
    integer :: d_size
    type(a3D), dimension(:), pointer :: d_t
    
    if (associated(A%d)) then
       if (l1 < size(A%d)) then
          call insert3D(l2,l3,l4,val,A%d(l1))
       else   ! not big enough: we need to realloc and place value
          d_size = size(A%d)
          allocate(d_t(0:l1))
          do i=0,d_size-1
             d_t(i)%d => A%d(i)%d
          end do
          do i=d_size,l1
             d_t(i)%d => null()
          end do
          deallocate(A%d)
          A%d => d_t
          call insert3D(l2,l3,l4,val,A%d(l1))
       end if

    else
       ! dimension does not exist yet: create and place value
       allocate(A%d(0:l1))
       do i=0,l1
          A%d(i)%d => null()
       end do
       call insert3D(l2,l3,l4,val,A%d(l1))
    end if
  end subroutine insert4D


  subroutine insert5D(l1, l2, l3, l4, l5, val, A)
    integer :: l1,l2,l3,l4,l5
    double precision :: val
    type(a5D) :: A
    
    integer :: d_size
    type(a4D), dimension(:), pointer :: d_t
    
    if (associated(A%d)) then
       if (l1 < size(A%d)) then
          call insert4D(l2,l3,l4,l5,val,A%d(l1))
       else   ! not big enough: we need to realloc and place value
          d_size = size(A%d)
          allocate(d_t(0:l1))
          do i=0,d_size-1
             d_t(i)%d => A%d(i)%d
          end do
          do i=d_size,l1
             d_t(i)%d => null()
          end do
          deallocate(A%d)
          A%d => d_t
          call insert4D(l2,l3,l4,l5,val,A%d(l1))
       end if

    else
       ! dimension does not exist yet: create and place value
       allocate(A%d(0:l1))
       do i=0,l1
          A%d(i)%d => null()
       end do
       call insert4D(l2,l3,l4,l5,val,A%d(l1))
    end if
  end subroutine insert5D
  

  subroutine insert6D(l1, l2, l3, l4, l5, l6,val, A)
    integer :: l1,l2,l3,l4,l5,l6
    double precision :: val
    type(a6D) :: A
    
    integer :: d_size
    type(a5D), dimension(:), pointer :: d_t
    
    if (associated(A%d)) then
       if (l1 < size(A%d)) then
          call insert5D(l2,l3,l4,l5,l6,val,A%d(l1))
       else   ! not big enough: we need to realloc and place value
          d_size = size(A%d)
          allocate(d_t(0:l1))
          do i=0,d_size-1
             d_t(i)%d => A%d(i)%d
          end do
          do i=d_size,l1
             d_t(i)%d => null()
          end do
          deallocate(A%d)
          A%d => d_t
          call insert5D(l2,l3,l4,l5,l6,val,A%d(l1))
       end if

    else
       ! dimension does not exist yet: create and place value
       allocate(A%d(0:l1))
       do i=0,l1
          A%d(i)%d => null()
       end do
       call insert5D(l2,l3,l4,l5,l6,val,A%d(l1))
    end if
  end subroutine insert6D
  


  

!************************************************************** 
!
! Basic printing functions for 1D-6D memoization jagged arrays 
!
!**************************************************************
  
  subroutine print_jA1D(A)
    type(a1D) :: A
    integer :: i
    
    print*, "-----------"

    do i=0,size(A%d)-1
       if (associated(A%d(i)%d)) write(*,'(A,I0,A,F9.6)') "A[",i,"] is: ",A%d(i)%d
    end do
  end subroutine print_jA1D


  subroutine print_jA2D(A)
    type(a2D) :: A
    integer :: i,j
    
    print*, "-----------"

    do i=0,size(A%d)-1
       if (.not. associated(A%d(i)%d)) cycle
       do j=0,size(A%d(i)%d)-1
          if (.not. associated(A%d(i)%d(j)%d)) cycle
          write(*,'(A,1(I0,A),I0,A,F9.6)') "A[",i,",",j,"] is: ",A%d(i)%d(j)%d
       end do
    end do
  end subroutine print_jA2D


  subroutine print_jA3D(A)
    type(a3D) :: A
    integer :: i,j,k
    
    print*, "-----------"

    do i=0,size(A%d)-1
       if (.not. associated(A%d(i)%d)) cycle
       do j=0,size(A%d(i)%d)-1
          if (.not. associated(A%d(i)%d(j)%d)) cycle
          do k=0,size(A%d(i)%d(j)%d)-1
             if (.not. associated(A%d(i)%d(j)%d(k)%d)) cycle
             write(*,'(A,2(I0,A),I0,A,F9.6)') "A[",i,",",j,",",k,"] is: ",A%d(i)%d(j)%d(k)%d
          end do
       end do
    end do
  end subroutine print_jA3D


  subroutine print_jA4D(A)
    type(a4D) :: A
    integer :: i,j,k,l
    
    print*, "-----------"

    do i=0,size(A%d)-1
       if (.not. associated(A%d(i)%d)) cycle
       do j=0,size(A%d(i)%d)-1
          if (.not. associated(A%d(i)%d(j)%d)) cycle
          do k=0,size(A%d(i)%d(j)%d)-1
             if (.not. associated(A%d(i)%d(j)%d(k)%d)) cycle
             do l=0,size(A%d(i)%d(j)%d(k)%d)-1
                if (.not. associated(A%d(i)%d(j)%d(k)%d(l)%d)) cycle
                write(*,'(A,3(I0,A),I0,A,F9.6)') "A[",i,",",j,",",k,",",l,"] is: ",A%d(i)%d(j)%d(k)%d(l)%d
             end do
          end do
       end do
    end do
  end subroutine print_jA4D


  subroutine print_jA5D(A)
    type(a5D) :: A
    integer :: i,j,k,l,m
    
    print*, "-----------"

    do i=0,size(A%d)-1
       if (.not. associated(A%d(i)%d)) cycle
       do j=0,size(A%d(i)%d)-1
          if (.not. associated(A%d(i)%d(j)%d)) cycle
          do k=0,size(A%d(i)%d(j)%d)-1
             if (.not. associated(A%d(i)%d(j)%d(k)%d)) cycle
             do l=0,size(A%d(i)%d(j)%d(k)%d)-1
                if (.not. associated(A%d(i)%d(j)%d(k)%d(l)%d)) cycle
                do m=0,size(A%d(i)%d(j)%d(k)%d(l)%d)-1
                   if (.not. associated(A%d(i)%d(j)%d(k)%d(l)%d(m)%d)) cycle
                   write(*,'(A,4(I0,A),I0,A,F9.6)') "A[",i,",",j,",",k,",",l,",",m,"] is: ",A%d(i)%d(j)%d(k)%d(l)%d(m)%d
                end do
             end do
          end do
       end do
    end do
  end subroutine print_jA5D
  

  subroutine print_jA6D(A)
    type(a6D) :: A
    integer :: i,j,k,l,m,n
    
    print*, "-----------"

    do i=0,size(A%d)-1
       if (.not. associated(A%d(i)%d)) cycle
       do j=0,size(A%d(i)%d)-1
          if (.not. associated(A%d(i)%d(j)%d)) cycle
          do k=0,size(A%d(i)%d(j)%d)-1
             if (.not. associated(A%d(i)%d(j)%d(k)%d)) cycle
             do l=0,size(A%d(i)%d(j)%d(k)%d)-1
                if (.not. associated(A%d(i)%d(j)%d(k)%d(l)%d)) cycle
                do m=0,size(A%d(i)%d(j)%d(k)%d(l)%d)-1
                   if (.not. associated(A%d(i)%d(j)%d(k)%d(l)%d(m)%d)) cycle
                   do n=0,size(A%d(i)%d(j)%d(k)%d(l)%d(m)%d)-1
                      if (.not. associated(A%d(i)%d(j)%d(k)%d(l)%d(m)%d(n)%d)) cycle
                      write(*,'(A,5(I0,A),I0,A,F9.6)') "A[" ,i,",", j,"," , &
                           k,"," , l,"," , m,"," , n,"] is: " , A%d(i)%d(j)%d(k)%d(l)%d(m)%d(n)%d
                   end do
                end do
             end do
          end do
       end do
    end do
  end subroutine print_jA6D

!************************************************************** 
!
! Search functions for 1D-6D memoization jagged arrays 
!
! Returns: NULL if element not in Jagged_Array.
!          Pointer to value if present in Jagged_Array
!
!**************************************************************
  function elem1D(l1,A)
    integer :: l1
    type(a1D) :: A
    double precision, pointer :: elem1D

    nullify(elem1D)
    if (size(A%d) > l1) elem1d => A%d(l1)%d
  end function elem1D


  function elem2D(l1,l2,A)
    integer :: l1,l2
    type(a2D) :: A
    double precision, pointer :: elem2D
    
    nullify(elem2D)
    if ((size(A%d) > l1) .and. associated(A%d(l1)%d)) elem2D => elem1D(l2,A%d(l1))
  end function elem2D

  function elem3D(l1,l2,l3,A)
    integer :: l1,l2,l3
    type(a3D) :: A
    double precision, pointer :: elem3D
    
    nullify(elem3D)
    if ((size(A%d) > l1) .and. associated(A%d(l1)%d)) elem3D => elem2D(l2,l3,A%d(l1))
  end function elem3D

  function elem4D(l1,l2,l3,l4,A)
    integer :: l1,l2,l3,l4
    type(a4D) :: A
    double precision, pointer :: elem4D
    
    nullify(elem4D)
    if ((size(A%d) > l1) .and. associated(A%d(l1)%d)) elem4D => elem3D(l2,l3,l4,A%d(l1))
  end function elem4D

  function elem5D(l1,l2,l3,l4,l5,A)
    integer :: l1,l2,l3,l4,l5
    type(a5D) :: A
    double precision, pointer :: elem5D
    
    nullify(elem5D)
    if ((size(A%d) > l1) .and. associated(A%d(l1)%d)) elem5D => elem4D(l2,l3,l4,l5,A%d(l1))
  end function elem5D

  function elem6D(l1,l2,l3,l4,l5,l6,A)
    integer :: l1,l2,l3,l4,l5,l6
    type(a6D) :: A
    double precision, pointer :: elem6D
    
    nullify(elem6D)
    if ((size(A%d) > l1) .and. associated(A%d(l1)%d)) elem6D => elem5D(l2,l3,l4,l5,l6,A%d(l1))
  end function elem6D
  
  
end module memoization_ja
