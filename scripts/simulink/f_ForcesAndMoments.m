function [Fxyz, Mxyz] = f_ForcesAndMoments(Va, alpha, beta, rho, de, da, dt, PhiThetaPsi, omega_b, CD, CY, CL, CI, Cm, Cn, m, g, S, b, c, Sprop, Cprop, kmotor, kTp, kOmega, Cmfp, M_trans, alpha_0)

%% Variable Assignment %%

phi = PhiThetaPsi(1);
theta = PhiThetaPsi(2);

p = omega_b(1);
q = omega_b(2);
r = omega_b(3);

CD0 = CD(1);
CDalpha = CD(2);
CDalpha2 = CD(3);
CDq = CD(4);
CDbeta2 = CD(5);
CDbeta = CD(6);
CDde = CD(7);

CY0 = CY(1);
CYbeta = CY(2);
CYp = CY(3);
CYr = CY(4);
CYda = CY(5);

CL0 = CL(1);
CLalpha = CL(2);
CLq = CL(3);
CLde = CL(4);

Cl0 = CI(1);
Clbeta = CI(2);
Clp = CI(3);
Clr = CI(4);
Clda = CI(5);

Cm0 = Cm(1);
Cmalpha = Cm(2);
Cmq = Cm(3);
Cmde = Cm(4);

Cn0 = Cn(1);
Cnbeta = Cn(2);
Cnp = Cn(3);
Cnr = Cn(4);
Cnda = Cn(5);

%% Common Multiplication Factors %%

aerodynamicMultiple = 0.5*rho*(Va^2)*S; %1/2*rho*V^2*S term used in most aerodynamic equations
propellerMultiple = 0.5*rho*Sprop*Cprop; %Similar to aerodynamic multiple, but for a propeller

if (Va ~= 0)
    
    bOver2Va = b/(2*Va); %This multiple occurs in both force and moment calculations
    cOver2Va = c/(2*Va); %This multiple only occurs in force calculations

else
    
    bOver2Va = 0;
    cOver2Va = 0;
    
end
%% Drag and Lift Coefficient Calculation %%

CDCalc = CD0 + CDalpha*alpha + CDalpha2*(alpha^2) + CDde*(de^2) + CDq*cOver2Va*q + CDbeta2*(beta^2) + CDbeta*beta;
CLAlpha = CL0 + CLalpha*alpha;

%% Flat Plate Stall Model %%

sigma_alpha = (1 + exp(-M_trans*(alpha - alpha_0)) + exp(M_trans*(alpha + alpha_0)))/((1 + exp(-M_trans*(alpha - alpha_0)))*(1 + exp(M_trans*(alpha+alpha_0))));
CLAlpha = (1-sigma_alpha)*CLAlpha + sigma_alpha*(2*sign(alpha)*(sin(alpha)^2)*cos(alpha));

%% Conversion of Drag and Lift Coeffecients in vehicle frame, CD and CL, to body frame, CX and CZ %%

CLCalc = CLAlpha + CLq*cOver2Va*q + CLde*de;

CXCZ = [cos(alpha), -sin(alpha); sin(alpha), cos(alpha)]*[CDCalc; CLCalc];

CX = -CXCZ(1);
CZ = -CXCZ(2);

%% Calculating Remaining Body Frame Aerodynamic Coefficients

CY = CY0 + CYbeta*beta + CYp*bOver2Va*p + CYr*bOver2Va*r + CYda*da;

CI = Cl0 + Clbeta*beta + Clp*bOver2Va*p + Clr*bOver2Va*r + Clda*da;
CmAlpha = Cm0 + Cmalpha*alpha;
Cn = Cn0 + Cnbeta*beta + Cnp*bOver2Va*p + Cnr*bOver2Va*r + Cnda*da;

%% Flat Plate Stall Model %%

CmAlpha = (1 - sigma_alpha)*CmAlpha + sigma_alpha*(Cmfp*sign(alpha)*sin(alpha)^2);

%% Calculating Forces %%

Cm =  CmAlpha + Cmq*cOver2Va*q + Cmde*de;

fx = -m*g*sin(theta) + aerodynamicMultiple*CX + propellerMultiple*((kmotor*dt)^2 - Va^2);
fy = m*g*cos(theta)*sin(phi) + aerodynamicMultiple*CY;
fz = m*g*cos(theta)*cos(phi) + aerodynamicMultiple*CZ;

l = aerodynamicMultiple*b*CI + -kTp*(kOmega*dt)^2;
m = aerodynamicMultiple*c*Cm;
n = aerodynamicMultiple*b*Cn;

%% Assigning forces to output %%

Fxyz = [fx, fy, fz];
Mxyz = [l, m, n];

end