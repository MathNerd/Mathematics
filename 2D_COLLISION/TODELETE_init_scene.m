
% THIS IS A SCRIPT
printf("init_scene.m script called.\n");

%----------------------------------------
% GLOBALS:
%----------------------------------------

clear global;

global MAX_T = 10;       % in [0, +inf)

% ????????????????????
global t = 0;            % in [0, MAX_T]

%----------------------------------------
% MOVING POINT:
%----------------------------------------

global point_0 = [0 4];            % in (-inf,+inf)^2

% [0.5 -0.5]
% rand(1,2)*2-1
global point_velocity = rand(1,2)*2-1;  % in (-inf,+inf)^2

global point_radius = 0.5; % in (0, +inf)

%----------------------------------------
% MOVING RECTANGLE:
%----------------------------------------

global rectangle_bottom_left_corner = [-1 0];   % in (-inf,+inf)^2
global rectangle_size = [1 2];                  % in (0,+inf)^2

% [1 1]
% rand(1,2)*2-1
global rectangle_velocity = rand(1,2)*2-1;           % in (-inf,+inf)^2
