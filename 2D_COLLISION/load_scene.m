
% THIS IS A SCRIPT
printf("load_scene.m script called.\n");

%----------------------------------------
% GLOBALS:
%----------------------------------------

clear global;

%------------------------------------------
% SHOULD IT BE HERE??? I DONO = EYNENI YODEA !!!
global MAX_T = 10;      % in [0, +inf)
global t = 0;           % in [0, MAX_T]
%------------------------------------------

global point_0;         % in (-inf,+inf)^2
global point_velocity;  % in (-inf,+inf)^2
global point_radius;    % in (0, +inf)
global point_drag_acceleration % in {0,1}

global rectangle_bottom_left_corner;  % in (-inf,+inf)^2
global rectangle_size;                % in (0,+inf)^2
global rectangle_velocity;            % in (-inf,+inf)^2
global rectangle_drag_acceleration    % in {0,1}

file_path = fileparts(mfilename('fullpath'));
full_file_path = strcat(file_path, '/', scene_file_name);

RET_VALS = scene_parser_IMP(full_file_path);

point_0 = [RET_VALS(1,1) , RET_VALS(1,2)];
point_velocity = [RET_VALS(1,3) , RET_VALS(1,4)];
point_radius = RET_VALS(1,5);
point_drag_acceleration = RET_VALS(1,6);

rectangle_bottom_left_corner = [RET_VALS(1,7) , RET_VALS(1,8)];
rectangle_size = [RET_VALS(1,9) , RET_VALS(1,10)];
rectangle_velocity = [RET_VALS(1,11) , RET_VALS(1,12)];
rectangle_drag_acceleration = RET_VALS(1,13);