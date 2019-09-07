
% THIS IS A SCRIPT
printf("setup_functions.m script called.\n");

%----------------------------------------
% POINT FUNCTIONS:
%----------------------------------------

function p = point(t) % [0,1] -> (-inf,+inf)^2
    global point_0;
    global point_velocity;
    
    p = point_0 + point_velocity * t;    
endfunction

%----------------------------------------
% RECTANGLE FUNCTIONS:
%----------------------------------------

function l = rectangle_left(t)   % [0,1] -> (-inf,+inf)
    global rectangle_bottom_left_corner;
    global rectangle_velocity;
    
    l = rectangle_bottom_left_corner(1) + rectangle_velocity(1) * t;
endfunction

function r = rectangle_right(t)  % [0,1] -> (-inf,+inf)
    global rectangle_bottom_left_corner;
    global rectangle_size;
    global rectangle_velocity;
    
    r = rectangle_bottom_left_corner(1) + rectangle_size(1) + rectangle_velocity(1) * t;
endfunction

function b = rectangle_bottom(t) % [0,1] -> (-inf,+inf)
    global rectangle_bottom_left_corner;
    global rectangle_velocity;
    
    b = rectangle_bottom_left_corner(2) + rectangle_velocity(2) * t;
endfunction

function t = rectangle_top(t)    % [0,1] -> (-inf,+inf)
    global rectangle_bottom_left_corner;
    global rectangle_size;
    global rectangle_velocity;
    
    t = rectangle_bottom_left_corner(2) + rectangle_size(2) + rectangle_velocity(2) * t;
endfunction

%--------------------------------------------------------------------------
% CLOSEST POINT INSIDE THE MOVING RECTANGLE TO THE MOVING POINT FUNCTION:
%--------------------------------------------------------------------------

function rcp = rectangle_closest_point(t) % [0,1] -> (-inf,+inf)^2
    rcp = zeros(1, 2);
    
    if (point(t)(1) > rectangle_right(t))
        rcp(1) = rectangle_right(t);
    elseif (point(t)(1) < rectangle_left(t))
        rcp(1) = rectangle_left(t);
    else % rectangle_left(t) <= point(t)(1) && point(t)(1) <= rectangle_right(t)
        rcp(1) = point(t)(1);
    endif 
    
    if (point(t)(2) > rectangle_top(t))
        rcp(2) = rectangle_top(t);
    elseif (point(t)(2) < rectangle_bottom(t));
        rcp(2) = rectangle_bottom(t);
    else % rectangle_bottom(t) <= point(t)(2) && point(t)(2) <= rectangle_top(t)
        rcp(2) = point(t)(2);
    endif
endfunction

%-----------------------------------------------------------------------
% DISTANCE BETWEEN THE MOVING POINT AND THE MOVING RECTANGLE FUNCTION:
%-----------------------------------------------------------------------

function d = point_rectangle_distance(t) % [0,1] -> [0,+inf)
    d = norm(rectangle_closest_point(t) - point(t));
endfunction

%----------------------------------------------------------------------------------------------

% 'num_sln' will indicate how many solutions for the general quadratic equation are there, And will hold either:
% 0 for 'no solutions', 1 for 'exactly one solution', 2 for 'exactly two solutions', And 3 for 'an infinite number of solutions'.
% The solutions will be held in the variables 'x1' and 'x2', such that 'x1' is strictly less than 'x2', Now:
% If there is no solution, 'x1' and 'x2' will hold some junk values.
% If there is exactly one solution, It will be held in 'x1' and 'x2' will hold some junk value.
% If there are exactly two solutions, They will be held in 'x1' and 'x2' respectivley, Such that 'x1' is strictly less than 'x2'.
% If there are infinitely many solutions, 'x1' and 'x2' will hold some junk values.

function [num_sln, x1, x2] = solve_general_quadratic_equation(a, b, c)
    x1 = x2 = 0;
    if (a == 0)
        if (b != 0)
            num_sln = 1;
            x1 = -c/b;
        else % b == 0
            if (c == 0)
                num_sln = 3;
            else % c != 0
                num_sln = 0;
            endif
        endif
    else % a != 0
        disc = b*b-4*a*c;
        if (disc < 0)
            num_sln = 0;
        elseif (disc == 0)
            num_sln = 1;
            x1 = -b/(2*a);
        else % disc > 0
            num_sln = 2;
            sqrt_disc = sqrt(disc);
            x1 = (-b - sqrt_disc)/(2*a);
            x2 = (-b + sqrt_disc)/(2*a);
        endif
    endif
endfunction

%------------------ FORMULAS: ----------------------
%{ 

    % CX1 & CY1
    
    (r0lx-p0x)**2+(r0by-p0y)**2-pr**2+2*((r0lx-p0x)*(rvx-pvx)+(r0by-p0y)*(rvy-pvy))*t + ((rvx-pvx)**2+(rvy-pvy)**2)*t**2 = 0;
    
    % CX1 & CY2
    
    (r0lx-p0x)**2+(r0by+rsy-p0y)**2-pr**2+2*((r0lx-p0x)*(rvx-pvx)+(r0by+rsy-p0y)*(rvy-pvy))*t + ((rvx-pvx)**2+(rvy-pvy)**2)*t**2 = 0;
    
    % CX1 & CY3
    
    (r0lx-p0x)**2-pr**2+2*((r0lx-p0x)*(rvx-pvx))*t + ((rvx-pvx)**2)*t**2 = 0;
    
    % CX2 & CY1
    
    (r0lx+rsx-p0x)**2+(r0by-p0y)**2-pr**2+2*((r0lx+rsx-p0x)*(rvx-pvx)+(r0by-p0y)*(rvy-pvy))*t + ((rvx-pvx)**2+(rvy-pvy)**2)*t**2 = 0;
    
    % CX2 & CY2
    
    (r0lx+rsx-p0x)**2+(r0by+rsy-p0y)**2-pr**2+2*((r0lx+rsx-p0x)*(rvx-pvx)+(r0by+rsy-p0y)*(rvy-pvy))*t + ((rvx-pvx)**2+(rvy-pvy)**2)*t**2 = 0;
    
    % CX2 & CY3
    
    (r0lx+rsx-p0x)**2-pr**2+2*((r0lx+rsx-p0x)*(rvx-pvx))*t + ((rvx-pvx)**2)*t**2 = 0;
    
    % CX3 & CY1
    
    (r0by-p0y)**2-pr**2+2*((r0by-p0y)*(rvy-pvy))*t + ((rvy-pvy)**2)*t**2 = 0;
    
    % CX3 & CY2
    
    (r0by+rsy-p0y)**2-pr**2+2*((r0by+rsy-p0y)*(rvy-pvy))*t + ((rvy-pvy)**2)*t**2 = 0;
    
    % CX3 & CY3
    
    -pr**2 = 0;
%}

% point(t).x < rectangle_left(t)
function cx1 = condition_x_1(p0x, pvx, r0lx, rvx, t)
    cx1 = (p0x - r0lx < (rvx - pvx) * t);
endfunction

% rectangle_right(t) < point(t).x
function cx2 = condition_x_2(p0x, pvx, r0lx, rsx, rvx, t)
    cx2 = (r0lx + rsx - p0x < (pvx - rvx) * t);
endfunction

% rectangle_left(t) <= point(t).x <= rectangle_right(t)
% Note that 'condition_x_3' is satisfied if and only if BOTH 'condition_x_1' AND 'condition_x_2' are not satisfied.
function cx3 = condition_x_3(p0x, pvx, r0lx, rsx, rvx, t)
    cx3 = (r0lx - p0x <= (pvx - rvx) * t && (pvx - rvx) * t <= r0lx + rsx - p0x);
endfunction

% point(t).y < rectangle_bottom(t)
function cy1 = condition_y_1(p0y, pvy, r0by, rvy, t)
    cy1 = (p0y - r0by < (rvy - pvy) * t);
endfunction

% rectangle_top(t) < point(t).y
function cy2 = condition_y_2(p0y, pvy, r0by, rsy, rvy, t)
    cy2 = (r0by + rsy - p0y < (pvy - rvy) * t);
endfunction

% rectangle_bottom(t) <= point(t).y <= rectangle_top(t)
% Note that 'condition_y_3' is satisfied if and only if BOTH 'condition_y_1' AND 'condition_y_2' are not satisfied.
function cy3 = condition_y_3(p0y, pvy, r0by, rsy, rvy, t)
    cy3 = (r0by - p0y <= (pvy - rvy) * t && (pvy - rvy) * t <= r0by + rsy - p0y);
endfunction

% LIMZO SHEM HADASH LAFUNKZIA !!!
function req_t = find_t_such_that_the_distance_from_the_point_to_the_rectangle_is_equal_to_a_given_distance(given_distance)
    global point_0;
    global point_velocity;
    global rectangle_bottom_left_corner;
    global rectangle_size;
    global rectangle_velocity;
    
    p0x = point_0(1);
    p0y = point_0(2);
    pvx = point_velocity(1);
    pvy = point_velocity(2);
    pr = given_distance;
    
    r0lx = rectangle_bottom_left_corner(1);
    r0by = rectangle_bottom_left_corner(2);
    rsx = rectangle_size(1);
    rsy = rectangle_size(2);
    rvx = rectangle_velocity(1);
    rvy = rectangle_velocity(2);
    
    MAX_T = 1;
    
    req_t = 0;
    
    valid_t_solutions_list = LinkedList([]);
    
    output_file_name = "output.txt";
    output_file = fopen(output_file_name, "w");

    % LESHPETZ ET HA 'num_sln' SHMUHZAR MIN HAFUNCZIA !!! OK !
    
    % CX1 & CY1
    % SOLVING THE EQUATION:
    %(r0lx-p0x)**2+(r0by-p0y)**2-pr**2+2*((r0lx-p0x)*(rvx-pvx)+(r0by-p0y)*(rvy-pvy))*t + ((rvx-pvx)**2+(rvy-pvy)**2)*t**2 = 0;
    
    [num_sln, t1, t2] = solve_general_quadratic_equation(
        (rvx-pvx)**2+(rvy-pvy)**2,
        2*((r0lx-p0x)*(rvx-pvx)+(r0by-p0y)*(rvy-pvy)),
        (r0lx-p0x)**2+(r0by-p0y)**2-pr**2);
        
    fprintf(output_file, "CX1 & CY1 --->\n");
    fprintf(output_file, "num_sln = %g\nt1 = %g\nt2 = %g\n", num_sln, t1, t2);
    fprintf(output_file, "t1--> CX1 = %d , CY1 = %d\n", condition_x_1(p0x, pvx, r0lx, rvx, t1), condition_y_1(p0y, pvy, r0by, rvy, t1));
    fprintf(output_file, "t2--> CX1 = %d , CY1 = %d\n", condition_x_1(p0x, pvx, r0lx, rvx, t2), condition_y_1(p0y, pvy, r0by, rvy, t2));
    
    if (num_sln == 0)
        valid_t_solutions_list.Add(MAX_T, inf);
    elseif (num_sln == 1)
        if (0 <= t1 && t1 <= MAX_T)
            if (condition_x_1(p0x, pvx, r0lx, rvx, t1) && condition_y_1(p0y, pvy, r0by, rvy, t1))
                valid_t_solutions_list.Add(t1, inf);
            endif
        endif
    elseif (num_sln == 2)
        if (0 <= t1 && t1 <= MAX_T)
            if (condition_x_1(p0x, pvx, r0lx, rvx, t1) && condition_y_1(p0y, pvy, r0by, rvy, t1))
                valid_t_solutions_list.Add(t1, inf);
            endif
        endif
        
        if (0 <= t2 && t2 <= MAX_T)
            if (condition_x_1(p0x, pvx, r0lx, rvx, t2) && condition_y_1(p0y, pvy, r0by, rvy, t2))
                valid_t_solutions_list.Add(t2, inf);
            endif
        endif
    else % num_sln == 3
        valid_t_solutions_list.Add(MAX_T, inf);
    endif
        
    % CX1 & CY2
    % SOLVING THE EQUATION:
    %(r0lx-p0x)**2+(r0by+rsy-p0y)**2-pr**2+2*((r0lx-p0x)*(rvx-pvx)+(r0by+rsy-p0y)*(rvy-pvy))*t + ((rvx-pvx)**2+(rvy-pvy)**2)*t**2 = 0;
    
    [num_sln, t1, t2] = solve_general_quadratic_equation(
        (rvx-pvx)**2+(rvy-pvy)**2,
        2*((r0lx-p0x)*(rvx-pvx)+(r0by+rsy-p0y)*(rvy-pvy)),
        (r0lx-p0x)**2+(r0by+rsy-p0y)**2-pr**2);
    
    fprintf(output_file, "CX1 & CY2 --->\n");
    fprintf(output_file, "num_sln = %g\nt1 = %g\nt2 = %g\n", num_sln, t1, t2);
    fprintf(output_file, "t1--> CX1 = %d , CY2 = %d\n", condition_x_1(p0x, pvx, r0lx, rvx, t1), condition_y_2(p0y, pvy, r0by, rsy, rvy, t1));
    fprintf(output_file, "t2--> CX1 = %d , CY2 = %d\n", condition_x_1(p0x, pvx, r0lx, rvx, t2), condition_y_2(p0y, pvy, r0by, rsy, rvy, t2));
    
    if (num_sln == 0)
        valid_t_solutions_list.Add(MAX_T, inf);
    elseif (num_sln == 1)
        if (0 <= t1 && t1 <= MAX_T)
            if (condition_x_1(p0x, pvx, r0lx, rvx, t1) && condition_y_2(p0y, pvy, r0by, rsy, rvy, t1))
                valid_t_solutions_list.Add(t1, inf);
            endif
        endif
    elseif (num_sln == 2)
        if (0 <= t1 && t1 <= MAX_T)
            if (condition_x_1(p0x, pvx, r0lx, rvx, t1) && condition_y_2(p0y, pvy, r0by, rsy, rvy, t1))
                valid_t_solutions_list.Add(t1, inf);
            endif
        endif
        
        if (0 <= t2 && t2 <= MAX_T)
            if (condition_x_1(p0x, pvx, r0lx, rvx, t2) && condition_y_2(p0y, pvy, r0by, rsy, rvy, t2))
                valid_t_solutions_list.Add(t2, inf);
            endif
        endif
    else % num_sln == 3
        valid_t_solutions_list.Add(MAX_T, inf);
    endif
    
    % CX1 & CY3
    % SOLVING THE EQUATION:
    %(r0lx-p0x)**2-pr**2+2*((r0lx-p0x)*(rvx-pvx))*t + ((rvx-pvx)**2)*t**2 = 0;
    
    [num_sln, t1, t2] = solve_general_quadratic_equation(
        (rvx-pvx)**2,
        2*((r0lx-p0x)*(rvx-pvx)),
        (r0lx-p0x)**2-pr**2);
    
    fprintf(output_file, "CX1 & CY3 --->\n");
    fprintf(output_file, "num_sln = %g\nt1 = %g\nt2 = %g\n", num_sln, t1, t2);
    fprintf(output_file, "t1--> CX1 = %d , CY3 = %d\n", condition_x_1(p0x, pvx, r0lx, rvx, t1), condition_y_3(p0y, pvy, r0by, rsy, rvy, t1));
    fprintf(output_file, "t2--> CX1 = %d , CY3 = %d\n", condition_x_1(p0x, pvx, r0lx, rvx, t2), condition_y_3(p0y, pvy, r0by, rsy, rvy, t2));
    
    if (num_sln == 0)
        valid_t_solutions_list.Add(MAX_T, inf);
    elseif (num_sln == 1)
        if (0 <= t1 && t1 <= MAX_T)
            if (condition_x_1(p0x, pvx, r0lx, rvx, t1) && condition_y_3(p0y, pvy, r0by, rsy, rvy, t1))
                valid_t_solutions_list.Add(t1, inf);
            endif
        endif
    elseif (num_sln == 2)
        if (0 <= t1 && t1 <= MAX_T)
            if (condition_x_1(p0x, pvx, r0lx, rvx, t1) && condition_y_3(p0y, pvy, r0by, rsy, rvy, t1))
                valid_t_solutions_list.Add(t1, inf);
            endif
        endif
        
        if (0 <= t2 && t2 <= MAX_T)
            if (condition_x_1(p0x, pvx, r0lx, rvx, t2) && condition_y_3(p0y, pvy, r0by, rsy, rvy, t2))
                valid_t_solutions_list.Add(t2, inf);
            endif
        endif
    else % num_sln == 3
        valid_t_solutions_list.Add(MAX_T, inf);
    endif
    
    % CX2 & CY1
    % SOLVING THE EQUATION:
    %(r0lx+rsx-p0x)**2+(r0by-p0y)**2-pr**2+2*((r0lx+rsx-p0x)*(rvx-pvx)+(r0by-p0y)*(rvy-pvy))*t + ((rvx-pvx)**2+(rvy-pvy)**2)*t**2 = 0;
    
    [num_sln, t1, t2] = solve_general_quadratic_equation(
        (rvx-pvx)**2+(rvy-pvy)**2,
        2*((r0lx+rsx-p0x)*(rvx-pvx)+(r0by-p0y)*(rvy-pvy)),
        (r0lx+rsx-p0x)**2+(r0by-p0y)**2-pr**2);
    
    fprintf(output_file, "CX2 & CY1 --->\n");
    fprintf(output_file, "num_sln = %g\nt1 = %g\nt2 = %g\n", num_sln, t1, t2);
    fprintf(output_file, "t1--> CX2 = %d , CY1 = %d\n", condition_x_2(p0x, pvx, r0lx, rsx, rvx, t1), condition_y_1(p0y, pvy, r0by, rvy, t1));
    fprintf(output_file, "t2--> CX2 = %d , CY1 = %d\n", condition_x_2(p0x, pvx, r0lx, rsx, rvx, t2), condition_y_1(p0y, pvy, r0by, rvy, t2));
    
    if (num_sln == 0)
        valid_t_solutions_list.Add(MAX_T, inf);
    elseif (num_sln == 1)
        if (0 <= t1 && t1 <= MAX_T)
            if (condition_x_2(p0x, pvx, r0lx, rsx, rvx, t1) && condition_y_1(p0y, pvy, r0by, rvy, t1))
                valid_t_solutions_list.Add(t1, inf);
            endif
        endif
    elseif (num_sln == 2)
        if (0 <= t1 && t1 <= MAX_T)
            if (condition_x_2(p0x, pvx, r0lx, rsx, rvx, t1) && condition_y_1(p0y, pvy, r0by, rvy, t1))
                valid_t_solutions_list.Add(t1, inf);
            endif
        endif
        
        if (0 <= t2 && t2 <= MAX_T)
            if (condition_x_2(p0x, pvx, r0lx, rsx, rvx, t2) && condition_y_1(p0y, pvy, r0by, rvy, t2))
                valid_t_solutions_list.Add(t2, inf);
            endif
        endif
    else % num_sln == 3
        valid_t_solutions_list.Add(MAX_T, inf);
    endif
    
    % CX2 & CY2
    % SOLVING THE EQUATION:
    %(r0lx+rsx-p0x)**2+(r0by+rsy-p0y)**2-pr**2+2*((r0lx+rsx-p0x)*(rvx-pvx)+(r0by+rsy-p0y)*(rvy-pvy))*t + ((rvx-pvx)**2+(rvy-pvy)**2)*t**2 = 0;
    
    [num_sln, t1, t2] = solve_general_quadratic_equation(
        (rvx-pvx)**2+(rvy-pvy)**2,
        2*((r0lx+rsx-p0x)*(rvx-pvx)+(r0by+rsy-p0y)*(rvy-pvy)),
        (r0lx+rsx-p0x)**2+(r0by+rsy-p0y)**2-pr**2);
    
    fprintf(output_file, "CX2 & CY2 --->\n");
    fprintf(output_file, "num_sln = %g\nt1 = %g\nt2 = %g\n", num_sln, t1, t2);
    fprintf(output_file, "t1--> CX2 = %d , CY2 = %d\n", condition_x_2(p0x, pvx, r0lx, rsx, rvx, t1), condition_y_2(p0y, pvy, r0by, rsy, rvy, t1));
    fprintf(output_file, "t2--> CX2 = %d , CY2 = %d\n", condition_x_2(p0x, pvx, r0lx, rsx, rvx, t2), condition_y_2(p0y, pvy, r0by, rsy, rvy, t2));
    
    if (num_sln == 0)
        valid_t_solutions_list.Add(MAX_T, inf);
    elseif (num_sln == 1)
        if (0 <= t1 && t1 <= MAX_T)
            if (condition_x_2(p0x, pvx, r0lx, rsx, rvx, t1) && condition_y_2(p0y, pvy, r0by, rsy, rvy, t1))
                valid_t_solutions_list.Add(t1, inf);
            endif
        endif
    elseif (num_sln == 2)
        if (0 <= t1 && t1 <= MAX_T)
            if (condition_x_2(p0x, pvx, r0lx, rsx, rvx, t1) && condition_y_2(p0y, pvy, r0by, rsy, rvy, t1))
                valid_t_solutions_list.Add(t1, inf);
            endif
        endif
        
        if (0 <= t2 && t2 <= MAX_T)
            if (condition_x_2(p0x, pvx, r0lx, rsx, rvx, t2) && condition_y_2(p0y, pvy, r0by, rsy, rvy, t2))
                valid_t_solutions_list.Add(t2, inf);
            endif
        endif
    else % num_sln == 3
        valid_t_solutions_list.Add(MAX_T, inf);
    endif
    
    % CX2 & CY3
    % SOLVING THE EQUATION:
    %(r0lx+rsx-p0x)**2-pr**2+2*((r0lx+rsx-p0x)*(rvx-pvx))*t + ((rvx-pvx)**2)*t**2 = 0;
    
    [num_sln, t1, t2] = solve_general_quadratic_equation(
        (rvx-pvx)**2,
        2*((r0lx+rsx-p0x)*(rvx-pvx)),
        (r0lx+rsx-p0x)**2-pr**2);
    
    fprintf(output_file, "CX2 & CY3 --->\n");
    fprintf(output_file, "num_sln = %g\nt1 = %g\nt2 = %g\n", num_sln, t1, t2);
    fprintf(output_file, "t1--> CX2 = %d , CY3 = %d\n", condition_x_2(p0x, pvx, r0lx, rsx, rvx, t1), condition_y_3(p0y, pvy, r0by, rsy, rvy, t1));
    fprintf(output_file, "t2--> CX2 = %d , CY3 = %d\n", condition_x_2(p0x, pvx, r0lx, rsx, rvx, t2), condition_y_3(p0y, pvy, r0by, rsy, rvy, t2));
    
    if (num_sln == 0)
        valid_t_solutions_list.Add(MAX_T, inf);
    elseif (num_sln == 1)
        if (0 <= t1 && t1 <= MAX_T)
            if (condition_x_2(p0x, pvx, r0lx, rsx, rvx, t1) && condition_y_3(p0y, pvy, r0by, rsy, rvy, t1))
                valid_t_solutions_list.Add(t1, inf);
            endif
        endif
    elseif (num_sln == 2)
        if (0 <= t1 && t1 <= MAX_T)
            if (condition_x_2(p0x, pvx, r0lx, rsx, rvx, t1) && condition_y_3(p0y, pvy, r0by, rsy, rvy, t1))
                valid_t_solutions_list.Add(t1, inf);
            endif
        endif
            
        if (0 <= t2 && t2 <= MAX_T)
            if (condition_x_2(p0x, pvx, r0lx, rsx, rvx, t2) && condition_y_3(p0y, pvy, r0by, rsy, rvy, t2))
                valid_t_solutions_list.Add(t2, inf);
            endif
        endif
    else % num_sln == 3
        valid_t_solutions_list.Add(MAX_T, inf);
    endif

    % CX3 & CY1
    % SOLVING THE EQUATION:
    %(r0by-p0y)**2-pr**2+2*((r0by-p0y)*(rvy-pvy))*t + ((rvy-pvy)**2)*t**2 = 0;
    
    [num_sln, t1, t2] = solve_general_quadratic_equation(
        (rvy-pvy)**2,
        2*((r0by-p0y)*(rvy-pvy)),
        (r0by-p0y)**2-pr**2);
    
    fprintf(output_file, "CX3 & CY1 --->\n");
    fprintf(output_file, "num_sln = %g\nt1 = %g\nt2 = %g\n", num_sln, t1, t2);
    fprintf(output_file, "t1--> CX3 = %d , CY1 = %d\n", condition_x_3(p0x, pvx, r0lx, rsx, rvx, t1), condition_y_1(p0y, pvy, r0by, rvy, t1));
    fprintf(output_file, "t2--> CX3 = %d , CY1 = %d\n", condition_x_3(p0x, pvx, r0lx, rsx, rvx, t2), condition_y_1(p0y, pvy, r0by, rvy, t2));
    
    if (num_sln == 0)
        valid_t_solutions_list.Add(MAX_T, inf);
    elseif (num_sln == 1)
        if (0 <= t1 && t1 <= MAX_T)
            if (condition_x_3(p0x, pvx, r0lx, rsx, rvx, t1) && condition_y_1(p0y, pvy, r0by, rvy, t1))
                valid_t_solutions_list.Add(t1, inf);
            endif
        endif
    elseif (num_sln == 2)
        if (0 <= t1 && t1 <= MAX_T)
            if (condition_x_3(p0x, pvx, r0lx, rsx, rvx, t1) && condition_y_1(p0y, pvy, r0by, rvy, t1))
                valid_t_solutions_list.Add(t1, inf);
            endif
        endif
        
        if (0 <= t2 && t2 <= MAX_T)
            if (condition_x_3(p0x, pvx, r0lx, rsx, rvx, t2) && condition_y_1(p0y, pvy, r0by, rvy, t2))
                valid_t_solutions_list.Add(t2, inf);
            endif
        endif
    else % num_sln == 3
        valid_t_solutions_list.Add(MAX_T, inf);
    endif
    
    % CX3 & CY2
    % SOLVING THE EQUATION:
    %(r0by+rsy-p0y)**2-pr**2+2*((r0by+rsy-p0y)*(rvy-pvy))*t + ((rvy-pvy)**2)*t**2 = 0;
    
    [num_sln, t1, t2] = solve_general_quadratic_equation(
        (rvy-pvy)**2,
        2*((r0by+rsy-p0y)*(rvy-pvy)),
        (r0by+rsy-p0y)**2-pr**2);
    
    fprintf(output_file, "CX3 & CY2 --->\n");
    fprintf(output_file, "num_sln = %g\nt1 = %g\nt2 = %g\n", num_sln, t1, t2);
    fprintf(output_file, "t1--> CX3 = %d , CY2 = %d\n", condition_x_3(p0x, pvx, r0lx, rsx, rvx, t1), condition_y_2(p0y, pvy, r0by, rsy, rvy, t1));
    fprintf(output_file, "t2--> CX3 = %d , CY2 = %d\n", condition_x_3(p0x, pvx, r0lx, rsx, rvx, t2), condition_y_2(p0y, pvy, r0by, rsy, rvy, t2));
    
    if (num_sln == 0)
        valid_t_solutions_list.Add(MAX_T, inf);
    elseif (num_sln == 1)
        if (0 <= t1 && t1 <= MAX_T)
            if (condition_x_3(p0x, pvx, r0lx, rsx, rvx, t1) && condition_y_2(p0y, pvy, r0by, rsy, rvy, t1))
                valid_t_solutions_list.Add(t1, inf);
            endif
        endif
    elseif (num_sln == 2)
        if (0 <= t1 && t1 <= MAX_T)
            if (condition_x_3(p0x, pvx, r0lx, rsx, rvx, t1) && condition_y_2(p0y, pvy, r0by, rsy, rvy, t1))
                valid_t_solutions_list.Add(t1, inf);
            endif
        endif
        
        if (0 <= t2 && t2 <= MAX_T)
            if (condition_x_3(p0x, pvx, r0lx, rsx, rvx, t2) && condition_y_2(p0y, pvy, r0by, rsy, rvy, t2))
                valid_t_solutions_list.Add(t2, inf);
            endif
        endif
    else % num_sln == 3
        valid_t_solutions_list.Add(MAX_T, inf);
    endif

    % CX3 & CY3
    % SOLVING THE EQUATION:
    % -pr**2 = 0;
    
    [num_sln, t1, t2] = solve_general_quadratic_equation(
        0,
        0,
        -pr**2);
        
    fprintf(output_file, "CX3 & CY3 --->\n");
    fprintf(output_file, "num_sln = %g\nt1 = %g\nt2 = %g\n", num_sln, t1, t2);
    fprintf(output_file, "t1--> CX3 = %d , CY3 = %d\n", condition_x_3(p0x, pvx, r0lx, rsx, rvx, t1), condition_y_3(p0y, pvy, r0by, rsy, rvy, t1));
    fprintf(output_file, "t2--> CX3 = %d , CY3 = %d\n", condition_x_3(p0x, pvx, r0lx, rsx, rvx, t2), condition_y_3(p0y, pvy, r0by, rsy, rvy, t2));
    
    % CHECK WHAT TO DO BECAUSE ONLY ZERO OR INFINITE NUMBER OF SOLUTIONS IS POSSIBLE HERE!!!
    if (num_sln == 0)
        valid_t_solutions_list.Add(MAX_T, inf);
    else % num_sln == 3
        valid_t_solutions_list.Add(MAX_T, inf);
    endif
    
    %-------------------------------------------------------------------------------
    
    fclose(output_file);
    
    valid_t_solutions_list.Display();
    
    req_t = 1;
    for i = 1:valid_t_solutions_list.Length()
        if (req_t > valid_t_solutions_list.At(i))
            req_t = valid_t_solutions_list.At(i);
        endif
    endfor
endfunction
