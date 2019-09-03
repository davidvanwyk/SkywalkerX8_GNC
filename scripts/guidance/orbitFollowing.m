function [h_c, chi_c] = orbitFollowing(c, rho, lambda, p, chi, korbit)

%% Setup

% Inputs are all in inertial co-ordinates

% Variables

% c = center of the orbit we want to follow [cn, ce, cd] (m)
% rho = radius of the orbit we want to follow (m)
% lambda = direction of the orbin we want to follow (+1 clockwise, -1 counter-clockwise)
% p = current aircraft location [pn, pe, pd] (m)
% chi = current course angle (rad)

% Constants

% korbit = scalar for quickly we transition from moving toward the center
% of an orbit (the path we take when infinitely far from c) and to the
% ideal course angle command based on the orbit (ie. the course angle
% needed to maintain the orbit radius from the center)

% Splitting up inputs into constituent elements (in inertial NED frame)

cn = c(1);
ce = c(2);
cd = c(3);

pn = p(1);
pe = p(2);
pd = p(3);

%% Altitude Command (h_c)

% Our altitude command is simply the altitude of the orbit center

h_c = -cd;

%% Course Angle Command (chi_c)

d = sqrt((pn - cn)^2 + (pe - ce)^2);
phi = atan2( (pe - ce), (pn - cn) );

while (phi - chi) < -pi
   phi = phi + 2*pi; 
end

while (phi - chi) > pi
   phi = phi - 2*pi; 
end

chi_c = phi + lambda*(pi/2 + atan(korbit*(d - rho)/rho));

end