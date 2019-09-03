function [h_c, chi_c] = straightLineFollowing(r, q, p, chi, chi_inf, kpath)

%% Setup

% Inputs are all in inertial co-ordinates

% Variables

% r = origin of the path [rn, re, rd] (m)
% q = desired course path (unit vector) [qn, qe, qd] (m)
% p = current aircraft location [pn, pe, pd] (m)
% chi = current course angle (rad)

% Constants

% chi_inf = maximum course angle command magnitude when infinitely far from the path we want to follow (rad)
% kpath = relative path error scaling factor for course angle command
% transitions from chi_inf to chi_q (unitless 0->1)

% Splitting up inputs into constituent elements (in inertial NED frame)

rn = r(1);
re = r(2);
rd = r(3);

pn = p(1);
pe = p(2);
pd = p(3);

qn = q(1);
qe = q(2);
qd = q(3);

%% Altitude Command (h_c)

% Relative path error in the inertial frame

ei = p - r;
   
% Unit vector normal to q-k plane (k = unit vector in the inertial D
% direction; ie k = (0, 0, 1))

k = [0, 0, 1];

n = cross(q, k)'/norm(cross(q, k));

% Projection of relative path error in the path plane onto the vertical
% plane containing the path directon vector (ie. q-k plane)

si = ei - dot(ei, n)*n;

sn = si(1);
se = si(2);

if sqrt(qn^2 + qe^2) >= 1E-06

    h_c = -rd - sqrt(sn^2 + se^2)*(qd/(sqrt(qn^2 + qe^2)));
   
else
    
    h_c = -rd;
    
end

%% Course Angle Command (Chi_c)

% Course angle of straight line defined by unit vector q. We adjust this to
% ensure that -pi <= chi_q - chi <= pi

chi_q = atan2(qe, qn);

while (chi_q - chi) < -pi
   chi_q = chi_q + 2*pi; 
end

while (chi_q - chi) > pi
   chi_q = chi_q - 2*pi; 
end

% Inertial to path frame rotation matrix

Rip = [cos(chi_q) , sin(chi_q), 0;
       -sin(chi_q), cos(chi_q), 0;
       0          , 0         , 1];

% Relative path error expressed in the path frame
   
ep = Rip*ei;

% Calculating Chi_c by using a vector field that asymptotically decays to
% the desired course angle

epy = ep(2);

chi_c = chi_q - chi_inf*(2/pi)*atan(kpath*epy);

end