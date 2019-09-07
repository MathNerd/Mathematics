
%----------------------------------------
% FIND 't' SUCH THAT DISTANCE BETWEEN THE POINT AND THE RECTANGLE IS EQUAL TO A GIVEN DISTANCE:
%----------------------------------------

req_t = find_t_such_that_the_distance_from_the_point_to_the_rectangle_is_equal_to_a_given_distance(point_radius);

% 0 <= req_t <= 1

function [is_touch_left_edge, is_touch_right_edge, is_touch_bottom_edge, is_touch_top_edge] = resolve_touch()
    global rectangle_bottom_left_corner;
    global rectangle_size;

    r0lx = rectangle_bottom_left_corner(1);
    r0by = rectangle_bottom_left_corner(2);
    rsx = rectangle_size(1);
    rsy = rectangle_size(2);
    
    rcp = rectangle_closest_point(0);
    rcpx = rcp(1);
    rcpy = rcp(2);
    
    is_touch_left_edge = (rcpx == r0lx);
    is_touch_right_edge = (rcpx == r0lx + rsx);
    is_touch_bottom_edge = (rcpy == r0by);
    is_touch_top_edge = (rcpy == r0by + rsy);
endfunction

if (req_t != 0)
    point_0 = point(req_t);
    rectangle_bottom_left_corner = [rectangle_left(req_t), rectangle_bottom(req_t)];
    t = 0;
else % req_t == 0 MEANING "THOUCH":
    [is_touch_left_edge, is_touch_right_edge, is_touch_bottom_edge, is_touch_top_edge] = resolve_touch;
    
    %{
    % FLIPPING VELOCITIES:
    if (is_touch_left_edge)
        point_velocity(1) = -abs(point_velocity(1));
    elseif (is_touch_right_edge)
        point_velocity(1) = +abs(point_velocity(1));
    endif 
    
    if (is_touch_bottom_edge)
        point_velocity(2) = -abs(point_velocity(2));
    elseif (is_touch_top_edge)
        point_velocity(2) = +abs(point_velocity(2));
    endif
    %}
    
    pvx = point_velocity(1);
    pvy = point_velocity(2);
    pvxs = sign(pvx);
    pvys = sign(pvy);
    pavx = abs(pvx);
    pavy = abs(pvy);
    
    rvx = rectangle_velocity(1);
    rvy = rectangle_velocity(2);
    rvxs = sign(rvx);
    rvys = sign(rvy);
    ravx = abs(rvx);
    ravy = abs(rvy);
    
    if (is_touch_left_edge)
        if (rvx > 0)
            if (pvx > 0)
                if (pvx <= rvx)
                    point_0 = point(1);
                    rectangle_bottom_left_corner = [rectangle_left(1) , rectangle_bottom(1)];
                else % pvx > rvx
                    if (rectangle_drag_acceleration)
                        point_0 = point(1);
                        rectangle_bottom_left_corner = [point_0(1) + point_radius , rectangle_bottom(1)];
                    else
                        rectangle_bottom_left_corner = [rectangle_left(1) , rectangle_bottom(1)];
                        point_0 = [(rectangle_bottom_left_corner(1)-point_radius) , point(1)(2)];
                    endif
                endif
            else % pvx <= 0
                point_0 = point(1);
                rectangle_bottom_left_corner = [rectangle_left(1) , rectangle_bottom(1)];
            endif
        else % rvx <= 0
            if (pvx > 0)
                if (pvx < -rvx)
                    % rectanlge pushes the circle:
                    rectangle_bottom_left_corner = [ rectangle_bottom_left_corner(1) + rvx + pvx, rectangle_bottom(1) ];
                    point_0 = [ rectangle_bottom_left_corner(1) - point_radius , point(1)(2) ];
                else % pvx >= -rvx
                    % circle pushed the rectangle:
                    point_0 = [ point_0(1) + pvx + rvx, point_0(2) + pvy ];
                    rectangle_bottom_left_corner = [ point_0(1) + point_radius, rectangle_bottom_left_corner(2) + rvy ];
                endif
            else % pvx <= 0
            
            endif
        endif
    elseif (is_touch_right_edge)
        
    endif 
    
    if (is_touch_bottom_edge)
        
    elseif (is_touch_top_edge)
        if (rvys == pvys)
            if (ravy > pavy)
                point_0 = point(1);
                rectangle_bottom_left_corner = [rectangle_left(1), point_0(2) - point_radius - rectangle_size(2)];
            else % ravy <= pavy
                point_0 = point(1);
                rectangle_bottom_left_corner = [rectangle_left(1), rectangle_bottom(1)];
            endif
        endif
    endif
endif