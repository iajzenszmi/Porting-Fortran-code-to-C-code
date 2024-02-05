program array_test

  common xi,h
  common /jj/ xj,hj
  real xi(3),h(144),xj(3),hj(144)

  real :: A(10), x
  real, allocatable :: B1(:), B2(:)
  integer*8 :: gbyte = 2**30

  allocate ( B1(gbyte) )
  allocate ( B2(gbyte) )

  call report_memory ( 'xi', loc(xi), ' blank COMMON' )
  call report_memory ( 'xj', loc(xj), ' labeled COMMON jj' )
  call report_memory ( 'A ', loc(A), ' local stack array' )
  call report_memory ( 'B1', loc(B1), ' Allocated heap array' )
  call report_memory ( 'B2', loc(B2), ' Allocated heap array' )
  call report_memory ( 'x ', loc(x), ' local stack variable' )

  A = 0

 contains

    subroutine f(n, A)
     integer :: n
     real, intent(inout) :: A(n)
     A(n) = 1
    end subroutine

    subroutine report_memory ( variable_name, variable_loc, description )
     character*(*) :: variable_name, description
     integer*8 :: variable_loc, gb_address
     integer*8 :: gbyte = 2**30

     gb_address = variable_loc / gbyte
     write (*,*) variable_name, gb_address, variable_loc, description

    end subroutine report_memory 
    
end program
