
%----------------------------------------
% FIGURE 1:

figure(1);

%----------------------------------------
% PLOT RECTANGLE:
%----------------------------------------

rx = [ rectangle_left(t)   rectangle_right(t)  rectangle_right(t) rectangle_left(t) rectangle_left(t)   ];
ry = [ rectangle_bottom(t) rectangle_bottom(t) rectangle_top(t)   rectangle_top(t)  rectangle_bottom(t) ];

plot(rx, ry, 'Color', 'green', 'LineStyle', '-');
hold on;

rcx = (rectangle_left(t) + rectangle_right(t)) / 2;
rcy = (rectangle_bottom(t) + rectangle_top(t)) / 2;
plot_vector([rcx, rcy], rectangle_velocity, 'black');
hold on;

%----------------------------------------
% PLOT POINT:
%----------------------------------------

plot(point(t)(1), point(t)(2), 'd');
hold on;

plot_vector(point(t), point_velocity, 'blue');
hold on;

theta = 0:pi/20:2*pi;
cx = point_radius * cos(theta);
cy = point_radius * sin(theta);
cx = cx + point(t)(1);
cy = cy + point(t)(2);
plot(cx, cy, 'Color', 'blue', 'LineStyle', '-');
hold on;

%----------------------------------------
% PLOT CLOSEST POINT:
%----------------------------------------

plot(rectangle_closest_point(t)(1), rectangle_closest_point(t)(2), 'd', 'Color', 'red');
hold on;

%----------------------------------------
% PLOT TEXT:
%----------------------------------------

%{
text(-5, 2, 
    sprintf("t = %g\npoint = (%g,%g)\nrectangle\\_left = %g\nrectangle\\_right = %g\nrectangle\\_bottom = %g\nrectangle\\_top = %g\nnum\\_sln = %g\nreq\\_t = %d", 
        t,
        point(t)(1), point(t)(2), 
        rectangle_left(t), 
        rectangle_right(t),
        rectangle_bottom(t),
        rectangle_top(t),
        num_sln,
        req_t
       ),
    'Color', 'red', 'FontSize', 15, 'HorizontalAlignment', 'left');
hold off;
%}

%----------------------------------------
% END PLOT:
%----------------------------------------

grid on;
xlim([-5 5]);
ylim([-5 5]);
hold off;

%----------------------------------------
% FIGURE 2:

figure(2);

%----------------------------------------
% PLOT DISTANCE GRAPH:
%----------------------------------------

gt = -MAX_T:0.01:MAX_T;
gd = zeros(1, length(gt));

for i = 1:length(gt)
    gd(i) = point_rectangle_distance(gt(i));
endfor;

plot(gt, gd, 'Color', 'black', 'LineStyle', '-');
hold on;

plot([-MAX_T MAX_T], [point_radius point_radius], 'Color', 'green', 'LineStyle', '--');
hold on;

plot([t t], [0 point_rectangle_distance(t)], 'Color', 'red', 'LineStyle', '-');
grid on;
hold off;


