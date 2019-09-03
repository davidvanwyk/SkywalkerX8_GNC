%% Plant Linearization - SkywalkerX8.Control.Longitudinal %%

% The purpose of this section is to linearize the plant at various known
% operating points. This will allow one to determine if gain scheduling is
% needed on a controller-by-controller basis. 

% SkywalkerX8.Control.Longitudinal Linearization %

% The plant's SkywalkerX8.Control.Longitudinal dynamics from a control perspective require one
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

%% Aircraft SkywalkerX8.Control.Longitudinal Trim Setup %%

disp("Setup Started...")

SkywalkerX8.Control.Longitudinal.SchedulingVariables.VaArray = linspace(SkywalkerX8.Performance.Va(1)*1.1, SkywalkerX8.Performance.Va(end-1)*0.9, 10);
SkywalkerX8.Control.Longitudinal.SchedulingVariables.alphaArray = linspace(0, SkywalkerX8.Aerodynamics.alpha_0, 6);

SkywalkerX8.InitialConditions.XeYeZe = [0, 0, 0];
SkywalkerX8.InitialConditions.uvw = [0, 0, 0];
SkywalkerX8.InitialConditions.PhiThetaPsi = [0, 0, 0];
SkywalkerX8.InitialConditions.pqr = [0, 0, 0];

sys = 'SkywalkerX8_Longitudinal';

opspecAirframe = operspec(sys);
opt = findopOptions('OptimizerType', 'graddescent-elim', 'DisplayReport','off');

de_max = 2*15*pi/180; %x2 because our mixing matrix essentially halves this across 2 actuators

opspecAirframe.States(1).Known = [0; 0; 1; 1; 1; 1; 0; 0; 0; 0; 0; 0; 0; 0]; % Altitude will be varying and Va will be fully known 
opspecAirframe.States(1).SteadyState = [0; 0; 0; 1; 1; 1; 1; 0; 1; 1; 1; 1; 1; 1]; % We don't care if inertial positions are not in steady state
opspecAirframe.States(1).min = [-Inf; -Inf; -Inf; -Inf; -Inf; -Inf; -pi/2; -SkywalkerX8.Aerodynamics.alpha_0; -pi/2; -Inf; -Inf; -Inf; -pi/2; -pi/2];
opspecAirframe.States(1).max = opspecAirframe.States(1).min.*-1;

% Define known inputs and outputs

opspecAirframe.Inputs(1).Known = 0; % We don't know dt for trim
opspecAirframe.Inputs(2).Known = 0; % We don't know de for trim

opspecAirframe.Outputs(1).Known = 1; % We will always know expected Va (due to it being a trim condition) 
opspecAirframe.Outputs(2).Known = 1; % Force altitude = 0 for legal flight
opspecAirframe.Outputs(3).Known = 1; % Theta is alpha if one aligns earth and wind coordinates (which we force by doing this)
opspecAirframe.Outputs(4).Known = 1; % Know alpha (due to it being a trim condition)
opspecAirframe.Outputs(5).Known = 0; % Don't know q for trim 

% Define plant inputs

opspecAirframe.Inputs(1).min = 0;
opspecAirframe.Inputs(1).max = 1;

opspecAirframe.Inputs(1).u = 1;

opspecAirframe.Inputs(2).min = -de_max;
opspecAirframe.Inputs(2).max = de_max;

opspecAirframe.Inputs(2).u = 0;

% Altitude approx 0 for legal flight

opspecAirframe.Outputs(2).y = 0;

disp("Setup Complete")

%% Trim Calculation %%

disp("Trim Started...")

for i = 1:length(SkywalkerX8.Control.Longitudinal.SchedulingVariables.VaArray)
    
    Va = SkywalkerX8.Control.Longitudinal.SchedulingVariables.VaArray(i);
    opspecAirframe.Outputs(1).y = Va;
    
    for j = 1:length(SkywalkerX8.Control.Longitudinal.SchedulingVariables.alphaArray)
    
        alpha = SkywalkerX8.Control.Longitudinal.SchedulingVariables.alphaArray(j);

        u = Va*cos(alpha);
        v = 0;
        w = Va*sin(alpha);

        opspecAirframe.Outputs(3).y = alpha;
        opspecAirframe.Outputs(4).y = alpha;

        opspecAirframe.States(1).x = [0; 0; 0; u; v; w; 0; alpha; 0; 0; 0; 0; 0; 0];

        [op, opreport] = findop(sys, opspecAirframe, opt);

        SkywalkerX8.Control.Longitudinal.OpAirframe(i, j) = op;
    
        if (strcmp('Operating point specifications were successfully met.', opreport.TerminationString))
            SkywalkerX8.Control.Longitudinal.Success(i, j) = 1;
        else
            SkywalkerX8.Control.Longitudinal.Success(i, j) = 0;
        end
    
    end
       
end

disp("Trim Complete");

%% Linearization %%

bodeFrequencyRange = {1E-02, 1E02};
minRealTolerance = 1E-04;

%% Linearizing de to Va, theta, altitude and q %%

% The purpose of this section is to linearize de to Va, theta, altitude and
% q across the flight
% envelope. These linearized models can be plotted on a singular value plot
% and compared to one another; should they all be similar across the
% frequency spectrum of interest - a single controller will be adequate. 
% However, if strong differences exist then a gain-scheduled controller
% will be required.

LinIOs = [...
linio('SkywalkerX8_Longitudinal/de',1,'input'),...
linio('SkywalkerX8_Longitudinal/SkywalkerX8 Aircraft + Aerodynamics Longitudinal',1,'output'),...
linio('SkywalkerX8_Longitudinal/SkywalkerX8 Aircraft + Aerodynamics Longitudinal',2,'output'),...
linio('SkywalkerX8_Longitudinal/SkywalkerX8 Aircraft + Aerodynamics Longitudinal',3,'output'),...
linio('SkywalkerX8_Longitudinal/SkywalkerX8 Aircraft + Aerodynamics Longitudinal',5,'output')];

LinOpt = linearizeOptions('SampleTime', 0, 'RateConversionMethod', 'tustin');  % seek continuous-time model
    
% Linearize

disp("de to Va, Alt, Theta and q Linearization Started...")

for i = 1:length(SkywalkerX8.Control.Longitudinal.SchedulingVariables.VaArray)
    
    for j = 1:length(SkywalkerX8.Control.Longitudinal.SchedulingVariables.alphaArray)
        
        de2altthetaq = linearize(sys, LinIOs, SkywalkerX8.Control.Longitudinal.OpAirframe(i, j), LinOpt);
        SkywalkerX8.Control.Longitudinal.LinearizedPlantModels.De2VaAltThetaqLinearizedModels(:, :, i, j) = minreal(de2altthetaq, minRealTolerance, false);
        SkywalkerX8.Control.Longitudinal.LinearizedPlantModels.De2VaLinearizedModels(:, :, i, j) = minreal(SkywalkerX8.Control.Longitudinal.LinearizedPlantModels.De2VaAltThetaqLinearizedModels(1, 1, i, j), minRealTolerance, false);
        SkywalkerX8.Control.Longitudinal.LinearizedPlantModels.De2AltLinearizedModels(:, :, i, j) = minreal(SkywalkerX8.Control.Longitudinal.LinearizedPlantModels.De2VaAltThetaqLinearizedModels(2, 1, i, j), minRealTolerance, false);
        SkywalkerX8.Control.Longitudinal.LinearizedPlantModels.De2ThetaLinearizedModels(:, :, i, j) = minreal(SkywalkerX8.Control.Longitudinal.LinearizedPlantModels.De2VaAltThetaqLinearizedModels(3, 1, i, j), minRealTolerance, false);
        SkywalkerX8.Control.Longitudinal.LinearizedPlantModels.De2qLinearizedModels(:, :, i, j) = minreal(SkywalkerX8.Control.Longitudinal.LinearizedPlantModels.De2VaAltThetaqLinearizedModels(4, 1, i, j), minRealTolerance, false);
        
    end
       
end

disp("de to Va, Alt, Theta and q Linearization Complete")

% End Linearize

figure(1);
bode(SkywalkerX8.Control.Longitudinal.LinearizedPlantModels.De2AltLinearizedModels, bodeFrequencyRange);

figure(2);
bode(SkywalkerX8.Control.Longitudinal.LinearizedPlantModels.De2ThetaLinearizedModels, bodeFrequencyRange);

figure(3);
bode(SkywalkerX8.Control.Longitudinal.LinearizedPlantModels.De2qLinearizedModels, bodeFrequencyRange);

figure(4);
bode(SkywalkerX8.Control.Longitudinal.LinearizedPlantModels.De2VaLinearizedModels, bodeFrequencyRange);

hold off;

disp("Linearization Complete")

%% Plant Linearization Reduction %%

% The purpose of this section is to reduce the order of the models we
% estimate by ensuring they are bandlimited to an area where the reduced
% order model matches the dynamics of the higher order model to the
% greatest extent possible. This will greatly simplify controller design
% and allow one to make use of classical control techniques. 

%% De -> q, theta, alt%%

% From considering all the corner cases, 
% (Va, alpha) =
% (1, 1)
% (1, 3)
% (1, 6)
% (5, 1)
% (5, 3)
% (5, 6)
% (10, 1)
% (10, 3)
% (10, 6)
% It has been established that a second order model is appropriate for
% modelling the system up until a bandwidth of approximately 3 rad/s. After
% this higher order dynamics start to become more dominant. As such, we can
% reduce our model order to 2 - with the provision that control is not
% attempted above approximately 1.5-2 rad/s so as to avoid the higher order
% dynamics we are ignoring by making this reduction.

% We also know that this holds true for De -> theta

% De -> alt is slightly slowed down due to the integrator, however, so this
% only holds true up until 1 rad/s. This means we will need to slow our
% altitude controller down to approximately 0.5 rad/s so that we roll off
% our plant prior to 1 rad/s and avoid the discrepency between the models.
% This isn't much of a problem because we are limited in our altitude loop
% primarily by our airspeed - so we can only expect, at best, response
% times of between 2-10 seconds for altitude steps (from 0 to max
% expected); or a crossover frequency of between approximatily 0.5 and 0.1.

disp("Reducing Linearized Models...")

minRealTolerance = 1E-05;

for i = 1:length(SkywalkerX8.Control.Longitudinal.SchedulingVariables.VaArray)
    
    for j = 1:length(SkywalkerX8.Control.Longitudinal.SchedulingVariables.alphaArray)
        
        SkywalkerX8.Control.Longitudinal.LinearizedPlantModels.De2VaReducedModels(:, :, i, j) = minreal(balred(SkywalkerX8.Control.Longitudinal.LinearizedPlantModels.De2VaLinearizedModels(:, :, i, j), 2), minRealTolerance, false);
        SkywalkerX8.Control.Longitudinal.LinearizedPlantModels.De2qReducedModels(:, :, i, j) = minreal(balred(SkywalkerX8.Control.Longitudinal.LinearizedPlantModels.De2qLinearizedModels(:, :, i, j), 2), minRealTolerance, false);
        SkywalkerX8.Control.Longitudinal.LinearizedPlantModels.De2ThetaReducedModels(:, :, i, j) = minreal(SkywalkerX8.Control.Longitudinal.LinearizedPlantModels.De2qReducedModels(:, :, i, j)*tf(1, [1 0]), minRealTolerance, false);
        SkywalkerX8.Control.Longitudinal.LinearizedPlantModels.De2AltReducedModels(:, :, i, j) = minreal(SkywalkerX8.Control.Longitudinal.LinearizedPlantModels.De2ThetaReducedModels(:, :, i, j)*tf(SkywalkerX8.Control.Longitudinal.SchedulingVariables.VaArray(i), [1 0]), minRealTolerance, false);
        
    end
       
end

figure(1);
hold on;
bode(SkywalkerX8.Control.Longitudinal.LinearizedPlantModels.De2AltReducedModels, bodeFrequencyRange);
hold off;

figure(2);
hold on;
bode(SkywalkerX8.Control.Longitudinal.LinearizedPlantModels.De2ThetaReducedModels, bodeFrequencyRange);
hold off;

figure(3);
hold on;
bode(SkywalkerX8.Control.Longitudinal.LinearizedPlantModels.De2qReducedModels, bodeFrequencyRange);
hold off;

figure(4);
hold on;
bode(SkywalkerX8.Control.Longitudinal.LinearizedPlantModels.De2VaReducedModels, bodeFrequencyRange);
hold off;

disp("Linearized Models Reduced")

clearvars -except SkywalkerX8