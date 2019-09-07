
% plots a vector:
function plot_vector(point, vector, color)
    quiver(point(1), point(2), vector(1), vector(2), 'Color', color);
end