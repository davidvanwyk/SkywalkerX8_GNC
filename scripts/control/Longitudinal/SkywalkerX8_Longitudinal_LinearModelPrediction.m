%SKYWALKERX8_LONGITUDINAL_LINEARMODELPREDICTION Starting point for gain
%calculations for controller design based on linearized TF model

% This function takes in the SkywalkerX8 model and calculates the
% longitudinal transfer function from de to theta. It makes use of this and the
% inputs for the maximum de and maximum expected error to predict the
% maximum allowable proportional controller gain.

% It also outputs a prediction for the maximum possible bandwidth of the
% pitch loop using a second order approximation and then calculates kdtheta
% (the gain applied to the pitch rate, q, feedback term) based on the
% desired damping ratio. 

% These values can be used in subsequent control tuning methodologies as a
% starting point for the optimisation (although Kp will be fixed) process. 

% Pitch Control Loop

c = SkywalkerX8.Geometry.c;
S = SkywalkerX8.Geometry.S;
Jy = SkywalkerX8.System.InertiaTensor(2, 2);
Cmalpha = SkywalkerX8.Aerodynamics.Cm(2);
Cmq = SkywalkerX8.Aerodynamics.Cm(3);
Cmde = SkywalkerX8.Aerodynamics.Cm(4);

de_max = 15*pi/180;
zeta_theta = 1/sqrt(2);

% Altitude Control via Pitch

Wh = 3; % Bandwidth seperation between pitch control inner loop and altitude control outer loop
zeta_h = 1/sqrt(2);

% Va Control via Pitch

m = SkywalkerX8.System.Mass;
g = SkywalkerX8.System.Gravity;

CD0 = SkywalkerX8.Aerodynamics.CD(1);
CDalpha = SkywalkerX8.Aerodynamics.CD(2);
CDalpha2 = SkywalkerX8.Aerodynamics.CD(3);
CDde = SkywalkerX8.Aerodynamics.CD(4);

Sprop = SkywalkerX8.Propeller.Sprop;
Cprop = SkywalkerX8.Propeller.Cprop;

WV2 = 3; % Bandwidth seperation between pitch control inner loop and Va control outer loop
zeta_V2 = 1/sqrt(2);

% Va Control via Throttle

k = SkywalkerX8.Propeller.kmotor;
dt_max = 1;
eVa_max = 0.5*max(SkywalkerX8.Performance.Va) - min(SkywalkerX8.Performance.Va);

zeta_V = 1/sqrt(2);

for i = 1:length(SkywalkerX8.Control.Longitudinal.SchedulingVariables.VaArray)
   
    alt = 0; % We assume altitude is small for this flight system.
    Va = SkywalkerX8.Control.Longitudinal.SchedulingVariables.VaArray(i);
    
    [~, ~, ~, rho] = atmoscoesa(alt);
    
    % Pitch Control Loop
    
    atheta_1 = -rho*(Va^2)*c*S*Cmq*c/(4*Jy*Va);
    atheta_2 = -rho*(Va^2)*c*S*Cmalpha/(2*Jy);
    atheta_3 = rho*(Va^2)*c*S*Cmde/(2*Jy);
    
    SkywalkerX8.Control.Longitudinal.AlgebraicDesign.De2qLinearizedModels(i) = tf([atheta_3 0], [1 atheta_1 atheta_2]);
    SkywalkerX8.Control.Longitudinal.AlgebraicDesign.De2ThetaLinearizedModels(i) = SkywalkerX8.Control.Longitudinal.AlgebraicDesign.De2qLinearizedModels(i)*tf(1, [1 0]);
    SkywalkerX8.Control.Longitudinal.AlgebraicDesign.De2AltLinearizedModels(i) = SkywalkerX8.Control.Longitudinal.AlgebraicDesign.De2ThetaLinearizedModels(i)*tf(Va, [1 0]);
    
    etheta_max = interp1([SkywalkerX8.Performance.Va(1) SkywalkerX8.Performance.Va(end-1)], [SkywalkerX8.Performance.maxPitchAngle(1) SkywalkerX8.Performance.maxPitchAngle(end-1)], Va);
    
    Kp_theta = (de_max/etheta_max)*sign(atheta_3);
    
    omega_n_theta = sqrt(atheta_2 + (de_max/etheta_max)*abs(atheta_3));
    Kd_theta = (2*zeta_theta*omega_n_theta - atheta_1)/atheta_3;
    
    KthetaDC = Kp_theta*atheta_3/(atheta_2 + Kp_theta*atheta_3);
    
    SkywalkerX8.Control.Longitudinal.AlgebraicDesign.KpTheta(i) = Kp_theta;
    SkywalkerX8.Control.Longitudinal.AlgebraicDesign.KdTheta(i) = Kd_theta;
    SkywalkerX8.Control.Longitudinal.AlgebraicDesign.KThetaDC(i) = KthetaDC;
    SkywalkerX8.Control.Longitudinal.AlgebraicDesign.NatFreqTheta(i) = omega_n_theta;
    
    % Altitude Control via Pitch
    
    omega_n_h = omega_n_theta/Wh;
    
    Ki_h = (omega_n_h^2)/(KthetaDC*Va);
    Kp_h = (2*zeta_h*omega_n_h)/(KthetaDC*Va);
    
    SkywalkerX8.Control.Longitudinal.AlgebraicDesign.KiAlt(i) = Ki_h;
    SkywalkerX8.Control.Longitudinal.AlgebraicDesign.KpAlt(i) = Kp_h;
    SkywalkerX8.Control.Longitudinal.AlgebraicDesign.NatFreqAlt(i) = omega_n_h;
    
    % Va Control via Pitch
    
    de = SkywalkerX8.Control.Longitudinal.OpAirframe(i).Inputs(2).u;
    u = SkywalkerX8.Control.Longitudinal.OpAirframe(i).States(2).x(4);
    w = SkywalkerX8.Control.Longitudinal.OpAirframe(i).States(2).x(6);
    alpha = atan2(w, u);
    
    aV_1 = (rho*Va*S/m)*(CD0 + CDalpha*alpha + CDalpha2*alpha^2 + CDde*de) + rho*Sprop*Cprop*Va/m;
    
    SkywalkerX8.Control.Longitudinal.AlgebraicDesign.Theta2VaLinearizedModels(i) = tf(-g, [1 aV_1]);
    
    omega_n_V2 = omega_n_theta/WV2;
    
    Ki_V2 = -(omega_n_V2^2)/(KthetaDC*g);
    Kp_V2 = (aV_1 - 2*zeta_V2*omega_n_V2)/(KthetaDC*g);
    
    SkywalkerX8.Control.Longitudinal.AlgebraicDesign.KiV2(i) = Ki_V2;
    SkywalkerX8.Control.Longitudinal.AlgebraicDesign.KpV2(i) = Kp_V2;
    SkywalkerX8.Control.Longitudinal.AlgebraicDesign.NatFreqV2(i) = omega_n_V2;
    
    % Va Control via Throttle
    
    dt = SkywalkerX8.Control.Longitudinal.OpAirframe(i).Inputs(1).u;
    theta = SkywalkerX8.Control.Longitudinal.OpAirframe(i).States(2).x(8);
    
    aV_2 = rho*Sprop*Cprop*(k^2)*dt/m;
    aV_3 = g*cos(theta);
    
    SkywalkerX8.Control.Longitudinal.AlgebraicDesign.Dt2VaLinearizedModels(i) = tf(aV_2, [1 aV_1]); 
    
    Kp_V = (dt_max/eVa_max)*sign(aV_2);
    
    omega_n_V = (aV_1 + aV_2*Kp_V)/(2*zeta_V);
    
    Ki_V = (omega_n_V^2)/aV_2;
    
    SkywalkerX8.Control.Longitudinal.AlgebraicDesign.KiV(i) = Ki_V;
    SkywalkerX8.Control.Longitudinal.AlgebraicDesign.KpV(i) = Kp_V;
    SkywalkerX8.Control.Longitudinal.AlgebraicDesign.NatFreqV(i) = omega_n_V;
    
end

clearvars -except SkywalkerX8

