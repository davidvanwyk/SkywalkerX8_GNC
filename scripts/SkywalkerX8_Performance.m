function [phi_max, r_max, min_R, q_max, p_max] = SkywalkerX8_Performance(opreport)

%% Aerodynamic Inputs %%

load('SkywalkerX8.mat');

% Max Possible Inputs due to Actuator Limits%

de_max = 15*pi/180;
da_max = 15*pi/180;

CD = SkywalkerX8.Aerodynamics.CD;
CL = SkywalkerX8.Aerodynamics.CL;
CI = SkywalkerX8.Aerodynamics.Cl;
Cm = SkywalkerX8.Aerodynamics.Cm;

b = SkywalkerX8.Geometry.b;
c = SkywalkerX8.Geometry.c;

de = -de_max;
da = -da_max;
m = SkywalkerX8.System.Mass;
g = SkywalkerX8.System.Gravity;

CD0 = CD(1);
CDalpha = CD(2);
CDalpha2 = CD(3);
CDde = CD(7);

CL0 = CL(1);
CLalpha = CL(2);
CLde = CL(4);

Cl0 = CI(1);
Clr = CI(4);
Clda = CI(5);

Cm0 = Cm(1);
Cmalpha = Cm(2);
Cmq = Cm(3);
Cmde = Cm(4);

S = SkywalkerX8.Geometry.S;

%% System Trim State %%

alpha = opreport.Outputs(4).y;
Va = opreport.Outputs(3).y;
alt = opreport.Outputs(1).y;

[T, a, P, rho] = atmoscoesa(alt);

%% Calculations %%

alpha = -(Cm(1) + Cm(end)*de)/Cm(2);

if alpha >= SkywalkerX8.Aerodynamics.alpha_0
    alpha = SkywalkerX8.Aerodynamics.alpha_0;
    de = -(Cm(1) + Cm(2)*alpha)/Cm(end);
end

aerodynamicMultiple = 0.5*rho*Va^2*S;

CDCalc = CD0 + CDalpha*alpha + CDalpha2*(alpha^2) + CDde*(de^2);
CLAlpha = CL0 + CLalpha*alpha;

CLCalc = CLAlpha + CLde*de;

CXCZ = [cos(alpha), -sin(alpha); sin(alpha), cos(alpha)]*[CDCalc; CLCalc];

CZ = -CXCZ(2);

Fz = -aerodynamicMultiple*CZ;

phi_max = acos(m*g/Fz);

r_max = g*tan(phi_max)/Va;

min_R = Va/r_max;

alpha = SkywalkerX8.Aerodynamics.alpha_0;
de = de_max; % Since the following are in the transient, we don't need moment balance

q_max = -(Cm0 + Cmalpha*alpha + Cmde*de)*2*Va/(Cmq*c);
p_max = -(Cl0 + Clda*da)*2*Va/(b*Clr);

end