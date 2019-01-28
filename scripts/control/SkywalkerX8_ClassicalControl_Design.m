%% Plant Linearization %%

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

%% Trim Setup %%

sys = 'SkywalkerX8_Longitudinal';
opspec = operspec(sys);
opt = findopOptions('DisplayReport','on');

de_max = 15*pi/180;

opspec.States(1).Known = [0; 0; 1; 0; 0; 0; 0; 0; 0; 0; 0; 0; 0; 0]; % Only altitude is known as a state
opspec.States(1).SteadyState = [0; 0; 1; 1; 1; 1; 1; 1; 1; 1; 1; 1; 1; 1]; % We don't care if inertial positions are not in steady state
opspec.States(1).min = [-Inf; -Inf; 0; 0; -Inf; -Inf; -pi/2; -SkywalkerX8.Aerodynamics.alpha_0; -pi/2; -Inf; -Inf; -Inf; -pi/2; -pi/2];
opspec.States(1).max = opspec.States(1).min.*-1;
opspec.States(1).max(3:4) = Inf;

% Constrain the actuator outputs 

opspec.Inputs(1).min = 0; 
opspec.Inputs(1).max = 1;

opspec.Inputs(2).min = -de_max;
opspec.Inputs(2).max = de_max;

% Define known inputs and outputs

opspec.Inputs(1).Known = 0; % Unsure of dt for trim
opspec.Inputs(1).u = 1;
opspec.Inputs(2).Known = 0; % Unsure of de for trim
opspec.Inputs(2).u = 0.01;

opspec.Outputs(1).Known = 1; % We will always know expected Va (due to it being a trim condition) 
opspec.Outputs(2).Known = 1; % We will always know expected h (due to it being a trim condition)
opspec.Outputs(3).Known = 0; % Don't know theta for trim

%% Trim Calculation %%

for i = 1:length(SkywalkerX8.Performance.altitude)
    
    alt = SkywalkerX8.Performance.altitude(i);
    Va = SkywalkerX8.Performance.Va(i);
    
    opspec.States(1).x = [0; 0; -alt; Va; 0; 0; 0; 0; 0; 0; 0; 0; 0; 0];
    opspec.Outputs(1).y = Va;
    opspec.Outputs(2).y = alt;
    
    [op, opreport] = findop(sys, opspec, opt);
       
    SkywalkerX8.Control.Longitudinal.OpSpec(i) = op;
    
end

%% Linearization %%

%% Linearizing de to theta %%

% The purpose of this section is to linearize de to theta across the flight
% envelope. These linearized models can be plotted on a singular value plot
% and compared to one another; should they all be similar across the
% frequency spectrum of interest - a single controller will be adequate. 
% However, if strong differences exist then a gain-scheduled controller
% will be required.

figure(1);
hold on;

for i = 1:length(SkywalkerX8.Performance.altitude)
       
    LinIOs = [...
    linio('SkywalkerX8_Longitudinal/PID Controller (2DOF) theta_de',1,'openinput'),...
    linio('SkywalkerX8_Longitudinal/PID Controller (2DOF) Va_dt',1,'openinput'),...
    linio('SkywalkerX8_Longitudinal/SkywalkerX8 Aircraft + Aerodynamics Longitudinal',1,'output'),...
    linio('SkywalkerX8_Longitudinal/SkywalkerX8 Aircraft + Aerodynamics Longitudinal',2,'output'),...
    linio('SkywalkerX8_Longitudinal/SkywalkerX8 Aircraft + Aerodynamics Longitudinal',3,'output')];

    LinOpt = linearizeOptions('SampleTime',0);  % seek continuous-time model
    
    G = linearize(sys,LinIOs,SkywalkerX8.Control.Longitudinal.OpSpec,LinOpt);
    
    ST = slTuner(sys, SkywalkerX8.Control.Longitudinal.OpSpec(i));
    addOpening(ST, {'de', 'theta', 'h', 'SkywalkerX8_Longitudinal/SkywalkerX8 Aircraft + Aerodynamics Longitudinal/Va', 'theta_c', 'Va_c'});
    addPoint(ST, {'de', 'theta'});
    de2theta = getIOTransfer(ST, 'de', 'theta');
    
    SkywalkerX8.Control.Longitudinal.De2ThetaLinearizedModels(i) = de2theta;
    
    sigma(SkywalkerX8.Control.Longitudinal.De2ThetaLinearizedModels(i), {10E-04, 10E02});
    
end

%% Linearizing dt to Va %%

% The purpose of this section is to linearize the plant from dt to Va
% across the flight envelope where dt will be used to control Va (ie. when
% alt <= alt_high and alt >= alt_low in the flight regime). These 
% linearized models can be plotted on a singular value plot and compared to 
% one another; should they all be similar across the frequency spectrum of 
% interest - a single controller will be adequate. However, if strong 
% differences exist then a gain-scheduled controller will be required.

figure(2);
hold on;

for i = 1:length(SkywalkerX8.Performance.altitude)
    
    alt = SkywalkerX8.Performance.altitude(i);
    
    if ((alt <= alt_high) && (alt >= alt_low))
        
        ST = slTuner(sys, SkywalkerX8.Control.Longitudinal.OpSpec(i));
        
        addOpening(ST, {'theta_c', 'theta', 'h'});
        addPoint(ST, {'dt', 'SkywalkerX8_Longitudinal/SkywalkerX8 Aircraft + Aerodynamics Longitudinal/Va'});
        dt2Va = getIOTransfer(ST, 'dt', 'SkywalkerX8_Longitudinal/SkywalkerX8 Aircraft + Aerodynamics Longitudinal/Va');

        SkywalkerX8.Control.Longitudinal.Dt2VaLinearizedModels(i) = dt2Va;

        sigma(SkywalkerX8.Control.Longitudinal.Dt2VaLinearizedModels(i), {10E-04, 10E02});
        
    end
    
end