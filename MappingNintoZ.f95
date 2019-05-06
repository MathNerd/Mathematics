! program to map N (the set of natural numbers) into Z (the set of whole numbers):

program map_N_into_Z

    do n = 1,30
        print *,h(n)
    end do
    
contains

function h(n) result(r)
    integer, intent(in) :: n
    integer :: r
    if (modulo(n,2)==1) then
        r = (1-n)/2
    else !modulo(n,2)==0
        r = n/2
    end if 
end function

end program map_N_into_Z
