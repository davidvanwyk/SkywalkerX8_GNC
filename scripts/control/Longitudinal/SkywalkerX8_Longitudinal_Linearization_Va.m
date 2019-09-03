%% Wings Level Trim (ie. Va Scheduling) %%

% The purpose of this script is to linearize the plant in wings level trim,
% this will make flight system testing a lot easier because we can start
% the system in a steady state condition. This is unlikely Va, alpha trim
% whereby the system generally will have a pitch rate.

disp("Setup Started...")

sys = 'SkywalkerX8_Longitudinal';

opspecAirframe = operspec(sys);
opt = findopOptions('OptimizerType', 'graddescent-elim', 'DisplayReport','off');

de_max = 2*15*pi/180; %x2 because our mixing matrix essentially halves this across 2 actuators

opspecAirframe.States(1).Known = [0; 0; 1; 0; 1; 0; 1; 0; 1; 1; 1; 1; 0; 0]; 
opspecAirframe.States(1).SteadyState = [0; 0; 1; 1; 1; 1; 1; 1; 1; 1; 1; 1; 1; 1]; % We don't care if inertial positions are not in steady state
opspecAirframe.States(1).min = [-Inf; -Inf; -Inf; -Inf; -Inf; -Inf; -pi/2; -SkywalkerX8.Aerodynamics.alpha_0; -pi/2; -Inf; -Inf; -Inf; -pi/2; -pi/2];
opspecAirframe.States(1).max = opspecAirframe.States(1).min.*-1;

% Define known inputs and outputs

opspecAirframe.Inputs(1).Known = 0; % We don't know dt for trim
opspecAirframe.Inputs(2).Known = 0; % We don't know de for trim

opspecAirframe.Outputs(1).Known = 1; % We don't know Va for wings-level flight
opspecAirframe.Outputs(2).Known = 1; % Force altitude = 0 for legal flight
opspecAirframe.Outputs(3).Known = 0; % Don't know theta
opspecAirframe.Outputs(4).Known = 0; % Don't know alpha (due to it being a trim condition)
opspecAirframe.Outputs(5).Known = 1; % Know q for trim (0)

% Define plant inputs

opspecAirframe.Inputs(1).min = 0;
opspecAirframe.Inputs(1).max = 1;

opspecAirframe.Inputs(1).u = 1;

opspecAirframe.Inputs(2).min = -de_max;
opspecAirframe.Inputs(2).max = de_max;

opspecAirframe.Inputs(2).u = 0;

% Altitude approx 0 for legal flight

opspecAirframe.Outputs(2).y = 0;
opspecAirframe.Outputs(3).y = 0;
opspecAirframe.Outputs(4).y = 0;
opspecAirframe.Outputs(5).y = 0;

disp("Setup Complete")

%% Trim Calculation %%

disp("Setting Model To Hold Theta Constant")

open('SkywalkerX8_AircraftModel');
set_param('SkywalkerX8_AircraftModel/Skywalker X8/6DoF Body Kinematics Euler',...
              'FunctionName',... 
              'ms_sixdof_thetaConst');

disp("Trim Started...")

for i = 1:length(SkywalkerX8.Control.Longitudinal.SchedulingVariables.VaArray)
    
    Va = SkywalkerX8.Control.Longitudinal.SchedulingVariables.VaArray(i);

    opspecAirframe.Outputs(1).y = Va;

    opspecAirframe.States(1).x = [0; 0; 0; Va; 0; 0; 0; 0; 0; 0; 0; 0; 0; 0];

    [op, opreport] = findop(sys, opspecAirframe, opt);
    
    SkywalkerX8.Control.Longitudinal.WingsLevelTrim.OpAirframe(i) = op;
    
    if (strcmp('Operating point specifications were successfully met.', opreport.TerminationString))
        SkywalkerX8.Control.Longitudinal.WingsLevelTrim.Success(i) = 1;
    else
        SkywalkerX8.Control.Longitudinal.WingsLevelTrim.Success(i) = 0;
    end
    
end

disp("Trim Complete");

%% Linearizing dt to Va %%

% The purpose of this section is to linearize the plant from dt to Va
% across the flight envelope where dt will be used to control Va (ie. when
% alt <= alt_high and alt >= alt_low in the flight regime). These 
% linearized models can be plotted on a singular value plot and compared to 
% one another; should they all be similar across the frequency spectrum of 
% interest - a single controller will be adequate. However, if strong 
% differences exist then a gain-scheduled controller will be required.

bodeFrequencyRange = {1E-02, 1E02};
minRealTolerance = 1E-04;

disp("Linearization Started...")

figure(1);
hold on;

LinIOs = [...
linio('SkywalkerX8_Longitudinal/dt',1,'input'),...
linio('SkywalkerX8_Longitudinal/SkywalkerX8 Aircraft + Aerodynamics Longitudinal',1,'output')];

LinOpt = linearizeOptions('SampleTime', 0, 'RateConversionMethod', 'tustin');  % seek continuous-time model
       
% Linearize

disp("dt to Va Linearization Started...")

for i = 1:length(SkywalkerX8.Control.Longitudinal.SchedulingVariables.VaArray)
         
    dt2Va = linearize(sys, LinIOs, SkywalkerX8.Control.Longitudinal.WingsLevelTrim.OpAirframe(i), LinOpt);
    dt2Va = minreal(dt2Va, minRealTolerance, false);
    SkywalkerX8.Control.Longitudinal.LinearizedPlantModels.Dt2VaLinearizedModels(:, :, i) = dt2Va;

end

bode(SkywalkerX8.Control.Longitudinal.LinearizedPlantModels.Dt2VaLinearizedModels, bodeFrequencyRange);

disp("dt to Va Linearization Complete")

disp("Removing Theta Hold Model")

set_param('SkywalkerX8_AircraftModel/Skywalker X8/6DoF Body Kinematics Euler',...
              'FunctionName',... 
              'ms_sixdof');

% Reducing Models %

% dt 2 Va is already reduced due to having made the constant theta
% assumption. As such, we just set the reduced models to be the same as the
% linearized ones for the sake of consistency.

SkywalkerX8.Control.Longitudinal.LinearizedPlantModels.Dt2VaReducedModels = SkywalkerX8.Control.Longitudinal.LinearizedPlantModels.Dt2VaLinearizedModels;
          
% End Linearize

hold off;