%% Plant Linearization - Longitudinal %%

% The purpose of this section is to linearize the plant at various known
% operating points. This will allow one to determine if gain scheduling is
% needed on a controller-by-controller basis. 

% Longitudinal Linearization %

% The plant's longitudinal dynamics from a control perspective require one
% to establish the following linearizations: 

% 1. de -> theta
% 2. dt -> Va 

% Once the controllers have been designed for theta_c and Va_c, additional
% linearizations will follow as:

% 1. theta_c -> Va
% 2. theta_c -> h

% Theta can be controller either by the airspeed controller, or the
% altitude controller, and this will determine where one is in the flight
% regime. 

%% Aircraft Longitudinal Trim Setup %%

sys = 'SkywalkerX8_Longitudinal';
opspecAirframe = operspec(sys);
opt = findopOptions('DisplayReport','on');

de_max = 15*pi/180;

opspecAirframe.States(1).Known = [0; 0; 1; 0; 0; 0; 0; 0; 0; 0; 0; 0; 0; 0]; % Only altitude is known as a state
opspecAirframe.States(1).SteadyState = [0; 0; 1; 1; 1; 1; 1; 1; 1; 1; 1; 1; 1; 1]; % We don't care if inertial positions are not in steady state
opspecAirframe.States(1).min = [-Inf; -Inf; -Inf; -Inf; -Inf; -Inf; -pi/2; -SkywalkerX8.Aerodynamics.alpha_0; -pi/2; -Inf; -Inf; -Inf; -pi/2; -pi/2];
opspecAirframe.States(1).max = opspecAirframe.States(1).min.*-1;

% Define known inputs and outputs

opspecAirframe.Inputs(1).Known = 0; % We don't know dt for trim
opspecAirframe.Inputs(2).Known = 0; % We don't know de for trim

opspecAirframe.Outputs(1).Known = 1; % We will always know expected Va (due to it being a trim condition) 
opspecAirframe.Outputs(2).Known = 1; % We will always know expected h (due to it being a trim condition)
opspecAirframe.Outputs(3).Known = 0; % Don't know theta for trim

% Define plant inputs

opspecAirframe.Inputs(1).min = 0;
opspecAirframe.Inputs(1).max = 1;

opspecAirframe.Inputs(1).u = 1;

opspecAirframe.Inputs(2).min = -de_max;
opspecAirframe.Inputs(2).max = de_max;

%% Trim Calculation %%

for i = 1:length(SkywalkerX8.Performance.altitude)
    
    alt = SkywalkerX8.Performance.altitude(i);
    Va = SkywalkerX8.Performance.Va(i);
    
    opspecAirframe.States(1).x = [0; 0; -alt; Va; 0; 0; 0; 0; 0; 0; 0; 0; 0; 0];
    opspecAirframe.Outputs(1).y = Va;
    opspecAirframe.Outputs(2).y = alt;
    
    [op, opreport] = findop(sys, opspecAirframe, opt);
       
    SkywalkerX8.Control.Longitudinal.OpAirframe(i) = op;
    
end

%% Linearization %%

aircraftModelBlockHandle = getSimulinkBlockHandle('SkywalkerX8_AircraftModel/Skywalker X8/6DoF Body Kinematics Euler', true);

%% Linearizing dt to Va %%

% The purpose of this section is to linearize the plant from dt to Va
% across the flight envelope where dt will be used to control Va (ie. when
% alt <= alt_high and alt >= alt_low in the flight regime). These 
% linearized models can be plotted on a singular value plot and compared to 
% one another; should they all be similar across the frequency spectrum of 
% interest - a single controller will be adequate. However, if strong 
% differences exist then a gain-scheduled controller will be required.

figure(1);
hold on;

% Force theta to be constant during linearization - this is just to aid in 
% the linearization process and to uncouple Va and Theta (theta impacts Va 
% and if allowed to vary during linearization causes some problems) %

set_param(aircraftModelBlockHandle, 'FunctionName', 'ms_sixdof_thetaConst');

LinIOs = [...
linio('SkywalkerX8_Longitudinal/dt',1,'input'),...
linio('SkywalkerX8_Longitudinal/SkywalkerX8 Aircraft + Aerodynamics Longitudinal',1,'output')];

LinOpt = linearizeOptions('SampleTime',0);  % seek continuous-time model
       
% Linearize

dt2Va = linearize(sys,LinIOs,SkywalkerX8.Control.Longitudinal.OpAirframe,LinOpt);

SkywalkerX8.Control.Longitudinal.Dt2VaLinearizedModels = dt2Va;
sigma(SkywalkerX8.Control.Longitudinal.Dt2VaLinearizedModels);

% End Linearize

set_param(aircraftModelBlockHandle, 'FunctionName', 'ms_sixdof');
hold off;

%% Linearizing de to theta, altitude and q %%

% The purpose of this section is to linearize de to theta across the flight
% envelope. These linearized models can be plotted on a singular value plot
% and compared to one another; should they all be similar across the
% frequency spectrum of interest - a single controller will be adequate. 
% However, if strong differences exist then a gain-scheduled controller
% will be required.

% de -> altitude and q are also established to assist with block subs for
% controller tuning at a later stage

% Force Va to be constant during linearization - see above%

set_param(aircraftModelBlockHandle, 'FunctionName', 'ms_sixdof_VaConst');

LinIOs = [...
linio('SkywalkerX8_Longitudinal/de',1,'input'),...
linio('SkywalkerX8_Longitudinal/SkywalkerX8 Aircraft + Aerodynamics Longitudinal',2,'output'),...
linio('SkywalkerX8_Longitudinal/SkywalkerX8 Aircraft + Aerodynamics Longitudinal',3,'output'),...
linio('SkywalkerX8_Longitudinal/SkywalkerX8 Aircraft + Aerodynamics Longitudinal',4,'output')];

LinOpt = linearizeOptions('SampleTime',0);  % seek continuous-time model
    
% Linearize

de2altthetaq = linearize(sys,LinIOs,SkywalkerX8.Control.Longitudinal.OpAirframe,LinOpt);

SkywalkerX8.Control.Longitudinal.De2AltThetaqLinearizedModels = de2altthetaq;
SkywalkerX8.Control.Longitudinal.De2AltLinearizedModels = SkywalkerX8.Control.Longitudinal.De2AltThetaqLinearizedModels(1, 1, :);
SkywalkerX8.Control.Longitudinal.De2ThetaLinearizedModels = SkywalkerX8.Control.Longitudinal.De2AltThetaqLinearizedModels(2, 1, :);
SkywalkerX8.Control.Longitudinal.De2qLinearizedModels = SkywalkerX8.Control.Longitudinal.De2AltThetaqLinearizedModels(3, 1, :);
    
% End Linearize

figure(2);
sigma(SkywalkerX8.Control.Longitudinal.De2AltLinearizedModels);

figure(3);
sigma(SkywalkerX8.Control.Longitudinal.De2ThetaLinearizedModels);

figure(4);
sigma(SkywalkerX8.Control.Longitudinal.De2qLinearizedModels);

set_param(aircraftModelBlockHandle, 'FunctionName', 'ms_sixdof');
hold off;

%% Creating SkywalkerX8_Longitudinal Initial Block Subs %%

% This generates an initial block-sub for the SkywalkerX8_Longitudinal
% model. 

SkywalkerX8.Control.Longitudinal.LinearizedPlantBlockSub = append(SkywalkerX8.Control.Longitudinal.Dt2VaLinearizedModels, SkywalkerX8.Control.Longitudinal.De2AltThetaqLinearizedModels);