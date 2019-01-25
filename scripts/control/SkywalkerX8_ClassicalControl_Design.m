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

SkywalkerX8.Control.Longitudinal.ThetaCVaSelector = 1;
de_max = 15*pi/180;

alt_low = 0.01*max(SkywalkerX8.Performance.altitude);
alt_high = 0.9*max(SkywalkerX8.Performance.altitude);

sys = 'SkywalkerX8_Longitudinal';
opspec = operspec(sys);
opt = findopOptions('DisplayReport','on');

de_max = 15*pi/180;

opspec.States(9).Known = [0; 0; 1; 0; 0; 0; 0; 0; 0; 0; 0; 0; 0; 0]; % Only altitude and Va are known as a state
opspec.States(9).SteadyState = [0; 0; 1; 1; 1; 1; 1; 1; 1; 1; 1; 1; 1; 1]; % We don't care if inertial positions are not in steady state
opspec.States(9).min = [-Inf; -Inf; 0; 0; -Inf; -Inf; -pi/2; -SkywalkerX8.Aerodynamics.alpha_0; -pi/2; -Inf; -Inf; -Inf; -pi/2; pi/2];
opSpec.States(9).max = opspec.States(9).min.*-1;

% PIDF Controller Filter Outputs will be 0 during steady state %

opSpec.States(1).Known = 1;
opSpec.States(3).Known = 1;
opSpec.States(5).Known = 1;
opSpec.States(7).Known = 1;

opSpec.States(1).x = 0;
opSpec.States(3).x = 0;
opSpec.States(5).x = 0;
opSpec.States(7).x = 0;

% Will calculate controller outputs for steady state operating points % 

opSpec.States(2).Known = 0;
opSpec.States(4).Known = 0;
opSpec.States(6).Known = 0;
opSpec.States(8).Known = 0;

% Constrain the actuator outputs 

opSpec.States(2).min = 0; 
opSpec.States(2).max = 1;

opSpec.States(8).min = -de_max;
opSpec.States(8).max = de_max;

% Constrain the commanded theta to be within stall

opSpec.States(4).min = -SkywalkerX8.Aerodynamics.alpha_0; 
opSpec.States(4).max = SkywalkerX8.Aerodynamics.alpha_0;

opSpec.States(6).min = -SkywalkerX8.Aerodynamics.alpha_0; 
opSpec.States(6).max = SkywalkerX8.Aerodynamics.alpha_0;

% Define known inputs and outputs

opspec.Inputs(1).Known = 1; % We will always know commanded Va
opspec.Inputs(2).Known = 1; % We will always know commanded h

opspec.Outputs(2).Known = 1; % We will always know expected h (due to it being a trim condition) 
opspec.Outputs(1).Known = 1; % We will always know expected Va (due to it being a trim condition)

%% Trim Calculation %%

for i = 1:length(SkywalkerX8.Performance.altitude)
    
    alt = SkywalkerX8.Performance.altitude(i);
    Va = SkywalkerX8.Performance.Va(i);
    
    opspec.States(9).x = [0; 0; -alt; Va; 0; 0; 0; 0; 0; 0; 0; 0; 0; 0];
    opspec.Outputs(1).y = Va;
    opspec.Inputs(1).u = Va;
    opspec.Outputs(2).y = alt;
    opspec.Inputs(2).u = alt;
    
    % Operating point for when theta is being used to control airspeed
    
    if ( (alt > alt_high) || (alt < alt_low) )
        
        SkywalkerX8.Control.Longitudinal.ThetaCVaSelector = 1;

        [op, opreport] = findop(sys, opspec, opt);
        
    else
    
        % Operating point for when theta is being used to control altitude
        
        SkywalkerX8.Control.Longitudinal.ThetaCVaSelector = 0;

        [op, opreport] = findop(sys, opspec, opt);
        
    end
    
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
    
    G = linearize(sys,LinIOs,SkywalkerX8.Control.Longitudinal.OpSpec(i),LinOpt);
    
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