function y = accelerometerMeasurementEstimate(x, u)

% x = (Phi, Theta)
% u = (p, q, r, Va, alpha)

% This assumes unaccelerated flight in order to remove the dependency on
% udot, vdot, wdot. We also assume that beta ~ 0.

g = 9.81;

Phi = x(1);
Theta = x(2);

p = u(1);
q = u(2);
r = u(3);
Va = u(4);
alpha = u(5);

y = [q*Va*sin(alpha) + g*sin(Theta)                            ;...
     r*Va*cos(alpha) - p*Va*sin(alpha) - g*cos(Theta)*sin(Phi) ;...
     -q*Va*cos(alpha) - g*cos(Theta)*cos(Phi)                  ];

end

