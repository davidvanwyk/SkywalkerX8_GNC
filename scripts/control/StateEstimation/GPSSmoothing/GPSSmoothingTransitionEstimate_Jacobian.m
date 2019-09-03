function Ad = GPSSmoothingTransitionEstimate_Jacobian(x, u)

% x = (pn, pe, Vg, Chi, wn, we, Psi)
% u = (Va, q, r, Phi, Theta)

% This makes the assumption that the flight path angle is 0, and that the
% wind and airspeed are constant (ie. d/dt = 0)

g = 9.81;

Va = u(1);
q = u(2);
r = u(3);
Phi = u(4);
Theta = u(5);
dT = u(6);

pn = x(1);
pe = x(2);
Vg = x(3);
Chi = x(4);
wn = x(5);
we = x(6);
Psi = x(7);

PsiDot = q*sin(Phi)/cos(Theta) + r*cos(Phi)/cos(Theta);

if (sqrt(Vg^2) < 1E-03)
    Vg = 1E-03;
end

VgDot = ( (Va*cos(Psi) + wn)*(-Va*PsiDot*sin(Psi)) + (Va*sin(Psi) + we)*(Va*PsiDot*cos(Psi)) )/Vg;
ChiDot = (g/Vg)*tan(Phi)*cos(Chi - Psi);

dVgDotdPsi = -PsiDot*Va*(wn*cos(Psi) + we*sin(Psi))/Vg;
dChiDotdVg = -(g/Vg^2)*tan(Phi)*cos(Chi - Psi);
dChiDotdChi = -(g/Vg)*tan(Phi)*sin(Chi - Psi);
dChiDotdPsi = (g/Vg)*tan(Phi)*sin(Chi - Psi);

A = [0, 0, cos(Chi)        , -Vg*sin(Chi)       , 0                       , 0                      , 0              ;
     0, 0, sin(Chi)        , Vg*cos(Chi)        , 0                       , 0                      , 0              ;
     0, 0, -VgDot/Vg       , 0                  , -PsiDot*Va*sin(Psi)     , PsiDot*Va*cos(Psi)     , dVgDotdPsi     ;
     0, 0, dChiDotdVg      , dChiDotdChi        , 0                       , 0                      , dChiDotdPsi    ;
     0, 0, 0               , 0                  , 0                       , 0                      , 0              ;
     0, 0, 0               , 0                  , 0                       , 0                      , 0              ;
     0, 0, 0               , 0                  , 0                       , 0                      , 0              ];

Ad = eye(length(x)) + dT*A; %Conversion to discrete
 
end