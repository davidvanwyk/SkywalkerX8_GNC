%% Wings Level Trim (ie. Va Scheduling) %%

% The purpose of this script is to linearize the plant in wings level trim,
% this will make flight system testing a lot easier because we can start
% the system in a steady state condition. 

disp("Setup Started...")

SkywalkerX8.Control.Lateral.SchedulingVariables.VaArray = SkywalkerX8.Control.Longitudinal.SchedulingVariables.VaArray;

sys = 'SkywalkerX8_Lateral';

opspecAirframe = operspec(sys);
opt = findopOptions('DisplayReport','off');

de_max = 2*15*pi/180; %x2 because our mixing matrix essentially halves this across 2 actuators
da_max = 2*15*pi/180; %x2 because our mixing matrix essentially halves this across 2 actuators

opspecAirframe.States(1).Known = [0; 0; 1; 0; 0; 0; 1; 0; 1; 1; 1; 1; 0; 0];  
opspecAirframe.States(1).SteadyState = [0; 0; 1; 1; 1; 1; 1; 0; 0; 1; 0; 0; 1; 1]; % We don't care if inertial positions are not in steady state
opspecAirframe.States(1).min = [-Inf; -Inf; -Inf; -Inf; -Inf; -Inf; -pi/2; -SkywalkerX8.Aerodynamics.alpha_0; -pi/2; -Inf; -Inf; -Inf; -pi/2; -pi/2];
opspecAirframe.States(1).max = opspecAirframe.States(1).min.*-1;

% Define known inputs and outputs

opspecAirframe.Inputs(1).Known = 0; % We don't know dt for trim
opspecAirframe.Inputs(2).Known = 0; % We don't know de for trim
opspecAirframe.Inputs(3).Known = 1; % We know da for wings-level trim

opspecAirframe.Outputs(1).Known = 1; % We know Va for wings-level flight
opspecAirframe.Outputs(2).Known = 0; % Know Chi (we're flying North, so Chi = 0 degrees; but we don't need to set this as a hard constraint)
opspecAirframe.Outputs(3).Known = 1; % Know Phi (0)
opspecAirframe.Outputs(4).Known = 1; % Know p (0)

% Define plant inputs

opspecAirframe.Inputs(1).min = 0;
opspecAirframe.Inputs(1).max = 1;

opspecAirframe.Inputs(1).u = 1;

opspecAirframe.Inputs(2).min = -de_max;
opspecAirframe.Inputs(2).max = de_max;

opspecAirframe.Inputs(3).min = -da_max;
opspecAirframe.Inputs(3).max = da_max;

opspecAirframe.Inputs(2).u = -0.1;
opspecAirframe.Inputs(3).u = 0;

% All outputs except Va 0 for wings-level trim

opspecAirframe.Outputs(2).y = 0;
opspecAirframe.Outputs(3).y = deg2rad(0);
opspecAirframe.Outputs(4).y = 0;

disp("Setup Complete")

%% Trim Calculation %%

disp("Trim Started...")

for i = 1:length(SkywalkerX8.Control.Lateral.SchedulingVariables.VaArray)
    
    Va = SkywalkerX8.Control.Lateral.SchedulingVariables.VaArray(i);

    opspecAirframe.Outputs(1).y = Va;
    
    opspecAirframe.States(1).x = [0; 0; 0; Va; 0; 0; opspecAirframe.Outputs(3).y; 0; 0; 0; 0; 0; 0; 0];

    [op, opreport] = findop(sys, opspecAirframe, opt);
    
    SkywalkerX8.Control.Lateral.WingsLevelTrim.OpAirframe(i) = op;
    
    if (strcmp('Operating point specifications were successfully met.', opreport.TerminationString))
        SkywalkerX8.Control.Lateral.WingsLevelTrim.Success(i) = 1;
    else
        SkywalkerX8.Control.Lateral.WingsLevelTrim.Success(i) = 0;
    end
    
end

disp("Trim Complete");

%% Linearizing da to p, Phi, Chi %%

% The purpose of this section is to linearize the plant from da to p, Phi
% and Chi for all the various Va's.

bodeFrequencyRange = {1E-02, 1E02};
minRealTolerance = 1E-04;

disp("Linearization Started...")

figure(1);
hold on;

% LinIOs = [...
% linio('SkywalkerX8_Lateral/da',1,'input'),...
% linio('SkywalkerX8_Lateral/SkywalkerX8 Aircraft + Aerodynamics Lateral',2,'output'),...
% linio('SkywalkerX8_Lateral/SkywalkerX8 Aircraft + Aerodynamics Lateral',3,'output'),...
% linio('SkywalkerX8_Lateral/SkywalkerX8 Aircraft + Aerodynamics Lateral',4,'output')];

LinOpt = linearizeOptions('SampleTime', 0, 'LinearizationAlgorithm', 'numericalpert2', 'NumericalPertRel', 5E-02);  % seek continuous-time model

% Linearize

disp("da to p, Phi and Chi Linearization Started...")

for i = 1:length(SkywalkerX8.Control.Lateral.SchedulingVariables.VaArray)
         
    da2pPhiChi = linearize(sys, SkywalkerX8.Control.Lateral.WingsLevelTrim.OpAirframe(i), LinOpt);
    da2pPhiChi = minreal(da2pPhiChi, minRealTolerance, false);
    SkywalkerX8.Control.Lateral.LinearizedPlantModels.da2pPhiChiLinearizedModels(:, :, i) = da2pPhiChi(2:end, 3);
    SkywalkerX8.Control.Lateral.LinearizedPlantModels.Da2pLinearizedModels(:, :, i) = minreal(SkywalkerX8.Control.Lateral.LinearizedPlantModels.da2pPhiChiLinearizedModels(3, 1, i), minRealTolerance, false);
    SkywalkerX8.Control.Lateral.LinearizedPlantModels.Da2PhiLinearizedModels(:, :, i) = minreal(SkywalkerX8.Control.Lateral.LinearizedPlantModels.da2pPhiChiLinearizedModels(2, 1, i), minRealTolerance, false);
    SkywalkerX8.Control.Lateral.LinearizedPlantModels.Da2ChiLinearizedModels(:, :, i) = minreal(SkywalkerX8.Control.Lateral.LinearizedPlantModels.da2pPhiChiLinearizedModels(1, 1, i), minRealTolerance, false);

end

figure(1);
bode(SkywalkerX8.Control.Lateral.LinearizedPlantModels.Da2pLinearizedModels, bodeFrequencyRange);
figure(2)
bode(SkywalkerX8.Control.Lateral.LinearizedPlantModels.Da2PhiLinearizedModels, bodeFrequencyRange);
figure(3);
bode(SkywalkerX8.Control.Lateral.LinearizedPlantModels.Da2ChiLinearizedModels, bodeFrequencyRange);

disp("da to p, Phi and Chi Linearization Complete")

% End Linearize

%% Plant Linearization Reduction %%

% The purpose of this section is to reduce the order of the models we
% estimate by ensuring they are bandlimited to an area where the reduced
% order model matches the dynamics of the higher order model to the
% greatest extent possible. This will greatly simplify controller design
% and allow one to make use of classical control techniques. 

disp("Reducing Linearized Models...")

% Given that we will constrain our dynamics - we aren't concerned with high
% frequency dynamics and will focus on the lower frequency region. This
% means 0 -> 3 rad/s for Phi and 0 -> 0.5 rad/s for Chi.

boptPhi = balredOptions('StateElimMethod', 'Truncate', 'FreqIntervals', [0.001, 3]);
boptChi = balredOptions('StateElimMethod', 'Truncate', 'FreqIntervals', [0.001, 0.75]);

bodeFrequencyRange = {1E-02, 1E02};
minRealTolerance = 1E-04;

for i = 1:length(SkywalkerX8.Control.Lateral.SchedulingVariables.VaArray)
     
    SkywalkerX8.Control.Lateral.LinearizedPlantModels.Da2pReducedModels(:, :, i) = SkywalkerX8.Control.Lateral.LinearizedPlantModels.Da2pLinearizedModels(:, :, i); %Best we can do here is the actual model order (4) - so we leave as is
    SkywalkerX8.Control.Lateral.LinearizedPlantModels.Da2PhiReducedModels(:, :, i) = balred(SkywalkerX8.Control.Lateral.LinearizedPlantModels.Da2PhiLinearizedModels(:, :, i), 4);
    SkywalkerX8.Control.Lateral.LinearizedPlantModels.Da2ChiReducedModels(:, :, i) = balred(SkywalkerX8.Control.Lateral.LinearizedPlantModels.Da2ChiLinearizedModels(:, :, i), 4);

end

figure(1);
hold on;
bode(SkywalkerX8.Control.Lateral.LinearizedPlantModels.Da2pReducedModels, bodeFrequencyRange);
hold off;

figure(2);
hold on;
bode(SkywalkerX8.Control.Lateral.LinearizedPlantModels.Da2PhiReducedModels, bodeFrequencyRange);
hold off;

figure(3);
hold on;
bode(SkywalkerX8.Control.Lateral.LinearizedPlantModels.Da2ChiReducedModels, bodeFrequencyRange);
hold off;

disp("Linearized Models Reduced")

clearvars -except SkywalkerX8