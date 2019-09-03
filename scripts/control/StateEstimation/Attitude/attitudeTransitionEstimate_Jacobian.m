function Ad = attitudeTransitionEstimate_Jacobian(x, u)

% u = (p, q, r, Va, alpha, dT)'
% x = (Phi, Theta)'

p = u(1);
q = u(2);
r = u(3);
Va = u(4);
dT = u(6);

Phi = x(1);
Theta = x(2);

A = [q*cos(Phi)*tan(Theta) - r*sin(Phi)*tan(Theta), (q*sin(Phi) + r*cos(Phi))/(cos(Theta)^2);...
     -q*sin(Phi) - r*cos(Phi)                     , 0                                       ];

Ad = eye(length(x)) + dT*A; %Conversion to discrete
 
end