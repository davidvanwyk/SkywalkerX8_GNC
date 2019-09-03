function y = GPSSmoothingMeasurementEstimate(x, u)

% x = (pn, pe, Vg, Chi, wn, we, Psi)
% u = (Va, q, r, Phi, Theta)
% y = (yGPSN, yGPSE, yGPSVg, yGPSChi, yWindN, yWindE)

% This makes the assumption that the flight path angle is 0, and that the
% wind and airspeed are constant (ie. d/dt = 0)

% We use pseudo-measurements ywindn and ywinde, where the measurement
% values are always to be zero. This is to capture the effect of our states
% not being independent of one another.

Va = u(1);
q = u(2);
r = u(3);
Phi = u(4);
Theta = u(5);

pn = x(1);
pe = x(2);
Vg = x(3);
Chi = x(4);
wn = x(5);
we = x(6);
Psi = x(7);

y = [pn;
     pe;
     Vg;
     Chi;
     Va*cos(Psi) + wn - Vg*cos(Chi);
     Va*sin(Psi) + we - Vg*sin(Chi)];

end