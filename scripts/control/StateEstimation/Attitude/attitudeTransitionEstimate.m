function xNext = attitudeTransitionEstimate(x, u)

% u = (p, q, r, Va, alpha, dT)'
% x = (Phi, Theta)'

xNext = zeros(2, 1);
xDot = zeros(2, 1);

% PhiDotMax = 2;
% PhiDotMin = -2;
% 
% ThetaDotMax = 5;
% ThetaDotMin = -5;

p = u(1);
q = u(2);
r = u(3);
Va = u(4);
dT = u(6);

Phi = x(1);
Theta = x(2);

xDot(1) = p + q*sin(Phi)*tan(Theta) + r*cos(Phi)*tan(Theta);
xDot(2) = q*cos(Phi) - r*sin(Phi);

% if xDot(1) > PhiDotMax
%    xDot(1) = PhiDotMax; 
% end
% 
% if xDot(1) < PhiDotMin
%    xDot(1) = PhiDotMin; 
% end
% 
% if xDot(2) > ThetaDotMax
%    xDot(2) = ThetaDotMax; 
% end
% 
% if xDot(2) < ThetaDotMin
%    xDot(2) = ThetaDotMin; 
% end

xNext(1) = asin(sin(Phi + xDot(1)*dT));
xNext(2) = asin(sin(Theta + xDot(2)*dT));

end