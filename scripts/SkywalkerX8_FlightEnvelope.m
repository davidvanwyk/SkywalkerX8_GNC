%% Flight Envelope Calculation %%

% Written by: David van Wyk
% Date: 18/07/2018

% The purpose of this script is to calculate the flight envelope of the
% SkywalkerX8 aircraft. This is done by using the 6 DoF EoM and determining
% basic force balances to generate "1D" maximum and minimum Va values. With
% these values determined, the true trim condition can be calculated for
% each altitude with the full 6 DoF plant model. These two flight envelopes
% can then be compared.

%% User Input %%

altitude = linspace(0, 30000, 300); % Altitude vector of interest (20m tolerance)

de_max = 15*pi/180; % Maximum expected elevator angle available to the actuator
motor_power_max = 900; % Maximum expected power permissable to the motors

%% Lift Balance %%

% Looking purely in the y axis we calculate the maximum and minimum lift we
% can generate. The maximum will occur when alpha = alpha_0 (just prior to
% stall). This is the minimum when alpha = 0. 
% This will require a de to achieve pitch trim which we can calculate. 

deMaxLift = -(SkywalkerX8.Aerodynamics.Cm(1) + SkywalkerX8.Aerodynamics.Cm(2)*SkywalkerX8.Aerodynamics.alpha_0)/SkywalkerX8.Aerodynamics.Cm(end);
deMinLift = -(SkywalkerX8.Aerodynamics.Cm(1)/SkywalkerX8.Aerodynamics.Cm(end));

CLmax = SkywalkerX8.Aerodynamics.CL(1) + SkywalkerX8.Aerodynamics.CL(2)*SkywalkerX8.Aerodynamics.alpha_0 + SkywalkerX8.Aerodynamics.CL(4)*deMaxLift;
CDmax = SkywalkerX8.Aerodynamics.CD(1) + SkywalkerX8.Aerodynamics.CD(2)*SkywalkerX8.Aerodynamics.alpha_0 + SkywalkerX8.Aerodynamics.CD(3)*SkywalkerX8.Aerodynamics.alpha_0^2 + SkywalkerX8.Aerodynamics.CD(end)*deMaxLift^2;
CLmin = SkywalkerX8.Aerodynamics.CL(1) + SkywalkerX8.Aerodynamics.CL(4)*deMinLift;

Vasqrtrhomax = sqrt(2*SkywalkerX8.System.Mass*SkywalkerX8.System.Gravity/(SkywalkerX8.Geometry.S*CLmin));
Vasqrtrhomin = sqrt(2*SkywalkerX8.System.Mass*SkywalkerX8.System.Gravity/(SkywalkerX8.Geometry.S*(CLmax*cos(SkywalkerX8.Aerodynamics.alpha_0) + CDmax*sin(SkywalkerX8.Aerodynamics.alpha_0))));

%% Drag Balance %%

% Only looking at drag balance allows one to determine the absolute maximum
% velocity of the aircraft by assuming dt (propeller relative speed) is 1
% (maximum) and then balancing forces in x. This results in a fixed value
% which cannot be exceeded in trim conditions at any altitude (independent
% of rho).

VaMinDragMaxThrust = sqrt(SkywalkerX8.Propeller.Sprop*SkywalkerX8.Propeller.Cprop*SkywalkerX8.Propeller.kmotor^2/(SkywalkerX8.Geometry.S*(SkywalkerX8.Aerodynamics.CD(1) + SkywalkerX8.Aerodynamics.CD(end)*deMinLift) + SkywalkerX8.Propeller.Sprop*SkywalkerX8.Propeller.Cprop));
  
%% Initialising Non-Linear Model %%

fun = @SkywalkerX8_LinearFlightEnvelopeForceMomentBalance;
opts = optimoptions('lsqnonlin');
opts.Display = 'off';
opts.MaxIterations = 10000;
opts.MaxFunctionEvaluations = 10000;
lb = [0 0];
ub = [SkywalkerX8.Aerodynamics.alpha_0 1];

sys = 'SkywalkerX8_TrimAndLinearize';
opspec = operspec(sys);
opt = findopOptions('DisplayReport','off');

opspec.States.Known = [0; 0; 1; 0; 0; 0; 0; 0; 0; 0; 0; 0; 0; 0]; % Only altitude is known as a state
opspec.States.SteadyState = [0; 0; 1; 1; 1; 1; 1; 1; 1; 1; 1; 1; 1; 1]; % We don't care if inertial positions are not in steady state
opspec.States.min = [-Inf; -Inf; 0; 0; -Inf; -Inf; -pi/2; -SkywalkerX8.Aerodynamics.alpha_0; -pi/2; -Inf; -Inf; -Inf; -pi/2; pi/2];
opSpec.States.max = opspec.States.min.*-1;

opspec.Inputs(1).Known = 0; % We don't know propeller speed always
opspec.Inputs(2).Known = 0; % We don't know the exact elevator trim position
opspec.Inputs(3).Known = 1; % We will always know aileron position (always 0 for this analysis)

opspec.Inputs(1).u = 1;
opspec.Inputs(3).u = 0; % Set aileron input to 0

opspec.Inputs(1).min = 0;
opspec.Inputs(1).max = 1;
opspec.Inputs(2).min = -de_max;
opspec.Inputs(2).max = de_max;

opspec.Outputs(1).Known = 1;
opspec.Outputs(3).Known = 1;

opspec.Outputs(2).min = -pi/2*ones(3, 1);
opspec.Outputs(2).max = pi/2*ones(3, 1);

opspec.Outputs(4).min = -SkywalkerX8.Aerodynamics.alpha_0;
opspec.Outputs(4).max = SkywalkerX8.Aerodynamics.alpha_0;

%% Calculation %%

VaMinMaxLinear = zeros(length(altitude), 2);
VaMinMaxNonLinear = zeros(length(altitude), 2);
exitflag = zeros(length(altitude), 2);

for i = 1:length(altitude)
    
    % Calculating density at specific altitude
    alt = altitude(i);
    
    [T, a, P, rho] = atmoscoesa(alt); % Note that ISA couldn't be used due to altitude limits
    
    % Calculating max and min velocities based on lift balance (stall for
    % min and without climbing for max)
    
    Vamax = (1/sqrt(rho))*Vasqrtrhomax;
    Vamin = (1/sqrt(rho))*Vasqrtrhomin;
    
    % Forcing Vamax to be lower than the absolute maximum defined by drag
    % balance with maximum propeller speed 
    
    if Vamax > VaMinDragMaxThrust
        
        Vamax = VaMinDragMaxThrust;
        
    end
    
    % Ensuring that the motor driving the propeller can provide the
    % required power, otherwise scaling down to acceptable power level for
    % motor.
    
    Power = 0.5*rho*Vamax^3*SkywalkerX8.Geometry.S*SkywalkerX8.Aerodynamics.CD(1);
    
    if Power > motor_power_max
       
        Vamax = (motor_power_max/(0.5*rho*SkywalkerX8.Geometry.S*SkywalkerX8.Aerodynamics.CD(1)))^(1/3);
        
    end
    
    opspec.Outputs(1).y = alt;
    
    VaMinMaxLinear(i, 1) = Vamin;
    VaMinMaxLinear(i, 2) = Vamax;
    
    Vamax = round(Vamax*1.25, 0);
    Vamin = round(Vamin*0.75, 0);
    
    SkywalkerX8.Solver.alt = alt;
    
    exitflag(i, 1) = 0;
    
%     while exitflag(i, 1) <= 0
%         
%         Vamax = Vamax - 0.1;
%         
%         if Vamax <= Vamin
%             break
%         end
%         
%         x0 = [0.05, 0.9];
%         SkywalkerX8.Solver.Va = Vamax;
%         save('SkywalkerX8.mat', 'SkywalkerX8');
%         
%         [x,resnorm,residual,exitflag(i, 1),output] = lsqnonlin(fun, x0, lb, ub, opts);
%         
%     end
%     
%     exitflag(i, 2) = 0;
%     
%     while exitflag(i, 2) <= 0
%         
%         Vamin = Vamin + 0.1;
%         
%         if Vamin >= Vamax
%             break
%         end
%         
%         x0 = [0.2, 0.5];
%         SkywalkerX8.Solver.Va = Vamin;
%         save('SkywalkerX8.mat', 'SkywalkerX8');
%         
%         [x,resnorm,residual,exitflag(i, 2),output] = lsqnonlin(fun, x0, lb, ub, opts);
%         
%     end
    
    while true
        
        Vamax = Vamax - 0.1;
        
        if Vamax <= Vamin
           break 
        end
        
        opspec.States.x = [0; 0; -alt; Vamax; 0; 0; 0; 0; 0; 0; 0; 0; 0; 0]; % Only altitude is known as a state
        opspec.Outputs(1).y = alt;
        opspec.Outputs(3).y = Vamax;
        
        [op, opreport] = findop(sys, opspec, opt);     
        
        if strcmp(opreport.TerminationString, 'Operating point specifications were successfully met.')
            break
        end
        
    end
    
    opreport = [];
    
    while true

        Vamin = Vamin + 0.1;
        
        if Vamin >= Vamax
           break 
        end

        opspec.States.x = [0; 0; -alt; Vamin; 0; 0; 0; 0; 0; 0; 0; 0; 0; 0]; % Only altitude is known as a state
        opspec.Outputs(1).y = alt;
        opspec.Outputs(3).y = Vamin;

        [op, opreport] = findop(sys, opspec, opt);
        
        if strcmp(opreport.TerminationString, 'Operating point specifications were successfully met.')
            break
        end
        
    end
    
    VaMinMaxNonLinear(i, 1) = Vamin;
    VaMinMaxNonLinear(i, 2) = Vamax;
    
    switch i
        case round(length(altitude)/4, 0)
            disp('Flight envelope calculation 25% complete')
        case round(length(altitude)/2, 0)
            disp('Flight envelope calculation 50% complete')
        case round(3*length(altitude)/4, 0)
            disp('Flight envelope calculation 75% complete')
        case length(altitude)
            disp('Flight envelope calculation 100% complete')
    end
    
end

% %% 1D Model Flight Envelope in x/y/m trim %%
% 
% VaMinLinear = VaMinMaxLinear(1:(sum((VaMinMaxLinear(:, 1) < max(VaMinMaxLinear(:, 2))))+1), 1);
% altitudeLinear = altitude(1:(sum((VaMinMaxLinear(:, 1) < max(VaMinMaxLinear(:, 2))))+1));
% VaMaxLinear = VaMinMaxLinear(1:length(altitudeLinear), 2);
% 
% %% 6DoF Model Flight Envelope in full trim %%
% 
% VaMinNonLinear = VaMinMaxNonLinear(1:(sum((VaMinMaxNonLinear(:, 1) < max(VaMinMaxNonLinear(:, 2))))+1), 1);
% altitudeNonLinear = altitude(1:(sum((VaMinMaxNonLinear(:, 1) < max(VaMinMaxNonLinear(:, 2))))+1));
% VaMaxNonLinear = VaMinMaxNonLinear(1:length(altitudeNonLinear), 2);

clearvars -except SkywalkerX8

