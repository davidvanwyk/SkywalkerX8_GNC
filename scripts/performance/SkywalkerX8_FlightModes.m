function [lon_lat_A, lon_poles, lat_poles] = SkywalkerX8_FlightModes(op)

sys = 'SkywalkerX8_TrimAndLinearize';

linopts = linearizeOptions('BlockReduction', 'off', 'SampleTime', 0, ...
    'LinearizationAlgorithm', 'blockbyblock', 'UseFullBlockNameLabels', 'on');
stateSpace = linearize(sys, op, linopts);

%Longitudinal state matrix: 
% u, alpha, q, theta
A_lon = stateSpace.A([4, 13, 11, 8], [4, 13, 11, 8]);
%Lateral state matrix:
% beta, p, r, phi
A_lat = stateSpace.A([14, 10, 12, 7], [14, 10, 12, 7]);

%Constructed state matrix
% u, alpha, q, theta, beta, p, r, phi
lon_lat_A = stateSpace.A([4, 13, 11, 8, 14, 10, 12, 7], [4, 13, 11, 8, 14, 10, 12, 7]);


lon_poles = eig(A_lon);
lat_poles = eig(A_lat);

end