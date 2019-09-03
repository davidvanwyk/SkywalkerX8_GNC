function C = accelerometerMeasurementEstimate_Jacobian(x, u)

% x = (Phi, Theta)
% u = (p, q, r, Va, alpha)

% This assumes unaccelerated flight in order to remove the dependency on
% udot, vdot, wdot. We also assume that alpha ~ 0, and beta ~ 0.

g = 9.81;

Phi = x(1);
Theta = x(2);

p = u(1);
q = u(2);
r = u(3);
Va = u(4);
alpha = u(5);

C = [0                     , g*cos(Theta)         ;...
     -g*cos(Phi)*cos(Theta), g*sin(Phi)*sin(Theta);...
     g*sin(Phi)*cos(Theta) , g*cos(Phi)*sin(Theta)];

end