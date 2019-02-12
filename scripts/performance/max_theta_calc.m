function [theta] = max_theta_calc(system, alt, Va)
%MAX_THETA_CALC Calculating the maximum possible pitch angle for various
%altitude and Va combinations

% The purpose of this function is to calculate the maximum permissable
% pitch angle of the flight system at a particular flight condition.

% If we want to climb, we want to hold the airspeed constant and use all
% excess power to increase our potential energy (as opposed to our
% kinetic). As such, if we assume that we keep the airspeed approximately
% constant (quasy-steady state) - then the force balance in x becomes:

% Fx = ma = 0 = -mg*sin(theta) + 0.5*rho*Va^2*S*(CX(alpha) + CXq(alpha) +
% CXde(alpha)*de + 0.5*rho*Sprop*Cprop*( (kmotor*dt)^2 - Va^2 )

% We make the assumption that we have approximately straight flight. As
% such, u ~= Va, v ~= 0, w ~= 0. As such, alpha = 0; 

% We know our pitching moment must be 0, so: 
% de = (Cm0 + Cmalpha*alpha_0)/Cmde

% We know that for maximum climb angle, dt must be 1 (maximum thrust)

% With this we can rearrange the equation for Fx and calculate the maximum
% pitch angle for a given airspeed.

Cm0 = system.Aerodynamics.Cm(1);
Cmalpha = system.Aerodynamics.Cm(2);
Cmde = system.Aerodynamics.Cm(4);

m = system.System.Mass;
g = system.System.Gravity;

alpha = 0;
beta = 0;
de = (Cm0 + Cmalpha*alpha)/Cmde;
dt = 1;

[T, a, P, rho] = atmoscoesa(alt);

q = 0;

CD0 = system.Aerodynamics.CD(1);
CDalpha = system.Aerodynamics.CD(2);
CDalpha2 = system.Aerodynamics.CD(3);
CDq = system.Aerodynamics.CD(4);
CDbeta2 = system.Aerodynamics.CD(5);
CDbeta = system.Aerodynamics.CD(6);
CDde = system.Aerodynamics.CD(7);

CL0 = system.Aerodynamics.CL(1);
CLalpha = system.Aerodynamics.CL(2);
CLq = system.Aerodynamics.CL(3);
CLde = system.Aerodynamics.CL(4);

%% Common Multiplication Factors %%

aerodynamicMultiple = 0.5*rho.*(Va.^2)*system.Geometry.S; %1/2*rho*V^2*S term used in most aerodynamic equations
propellerMultiple = 0.5*rho.*system.Propeller.Sprop*system.Propeller.Cprop; %Similar to aerodynamic multiple, but for a propeller

if (Va ~= 0)
    
    cOver2Va = system.Geometry.c./(2*Va); %This multiple only occurs in force calculations

else
    
    cOver2Va = 0;
    
end
%% Drag and Lift Coefficient Calculation %%

CDCalc = CD0 + CDalpha*alpha + CDalpha2*(alpha^2) + CDde*(de^2) + CDq*cOver2Va*q + CDbeta2*(beta^2) + CDbeta*beta;
CLAlpha = CL0 + CLalpha*alpha;

%% Conversion of Drag and Lift Coeffecients in vehicle frame, CD and CL, to body frame, CX and CZ %%

CLCalc = CLAlpha + CLq*cOver2Va*q + CLde*de;

CXCZ = [cos(alpha), -sin(alpha); sin(alpha), cos(alpha)]*[CDCalc; CLCalc];

CX = -CXCZ(1);

theta = asin( ( aerodynamicMultiple*CX + propellerMultiple*((system.Propeller.kmotor*dt)^2 - Va.^2) )/(m*g) );

if ~isreal(theta)

    theta = pi/2;
    
end

end

