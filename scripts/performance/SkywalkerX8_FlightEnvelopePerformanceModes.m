%% Flight Envelope Performance and Modes Calculation %%

% The purpose of this file is to calculate performance characteristics, as
% well as aerodynamic modes of the aircraft at various trim conditions
% around the flight envelope. This is primarily to review plant dynamics
% across the operating envelope.

%% User Inputs: Flight Envelope Points to Review %%

% We input which points on the flight envelope we would like to review.
% This will look at the "corner points" of the envelope, as well as a
% central point and is aimed at illustrating the trends in system
% performance as a function of altitude and Va (and the associated trim
% parameters for each altitude/Va combination).

% Note: We scale the Va and Altitude points slightly so that they are 100%
% within the flight envelope and aren't marginal in terms of trim.

VaPoints = zeros(7, 1);
altitudePoints = zeros(7, 1);

VaPointsScalingFraction = 0.0001;
altitudePointsScalingFraction = 0.0001;
maxSpeedTolerance = 0.9999;

% The first point to consider is the lowest altitude, lowest velocity
VaPoints(1) = SkywalkerX8.FlightEnvelope.VaMin(1)*(1+VaPointsScalingFraction);
altitudePoints(1) = SkywalkerX8.FlightEnvelope.altitude(1)*(1+altitudePointsScalingFraction);

% We next look at the highest altitude, lowest velocity
VaPoints(2) = min(SkywalkerX8.FlightEnvelope.VaMin(SkywalkerX8.FlightEnvelope.altitude == max(SkywalkerX8.FlightEnvelope.altitude)))*(1+VaPointsScalingFraction);
altitudePoints(2) = max(SkywalkerX8.FlightEnvelope.altitude)*(1-altitudePointsScalingFraction);

% Highest altitude, highest velocity
VaPoints(3) = max(SkywalkerX8.FlightEnvelope.VaMax(SkywalkerX8.FlightEnvelope.altitude == max(SkywalkerX8.FlightEnvelope.altitude)))*(1-VaPointsScalingFraction);
altitudePoints(3) = max(SkywalkerX8.FlightEnvelope.altitude)*(1-altitudePointsScalingFraction);

% Maximum altitude for approximately absolute maximum speed (within 1%)
altitudePoints(4) = max(SkywalkerX8.FlightEnvelope.altitude(SkywalkerX8.FlightEnvelope.VaMax >= max(SkywalkerX8.FlightEnvelope.VaMax)*maxSpeedTolerance))*(1-altitudePointsScalingFraction);
VaPoints(4) = SkywalkerX8.FlightEnvelope.VaMax(SkywalkerX8.FlightEnvelope.altitude == max(SkywalkerX8.FlightEnvelope.altitude(SkywalkerX8.FlightEnvelope.VaMax >= max(SkywalkerX8.FlightEnvelope.VaMax))))*(1-VaPointsScalingFraction);

% Minimum altitude for approximately absolute maximum speed (within 1%)
altitudePoints(5) = min(SkywalkerX8.FlightEnvelope.altitude(SkywalkerX8.FlightEnvelope.VaMax >= max(SkywalkerX8.FlightEnvelope.VaMax)*maxSpeedTolerance))*(1+altitudePointsScalingFraction);
VaPoints(5) = SkywalkerX8.FlightEnvelope.VaMax(SkywalkerX8.FlightEnvelope.altitude == min(SkywalkerX8.FlightEnvelope.altitude(SkywalkerX8.FlightEnvelope.VaMax >= max(SkywalkerX8.FlightEnvelope.VaMax))))*(1-VaPointsScalingFraction);

% Lowest altitude, max velocity
VaPoints(6) = SkywalkerX8.FlightEnvelope.VaMax(1)*(1-VaPointsScalingFraction);
altitudePoints(6) = SkywalkerX8.FlightEnvelope.altitude(1)*(1+altitudePointsScalingFraction);

% Mid point of the flight envelope
altitudePoints(7) = SkywalkerX8.FlightEnvelope.altitude(end)/2;
VaPoints(7) = (min(SkywalkerX8.FlightEnvelope.VaMin) + max(SkywalkerX8.FlightEnvelope.VaMax))/2;

SkywalkerX8.Performance.altitude = altitudePoints;
SkywalkerX8.Performance.Va = VaPoints;

%% Trim Setup %%

sys = 'SkywalkerX8_TrimAndLinearize';
opspec = operspec(sys);
opt = findopOptions('DisplayReport','off');

de_max = 15*pi/180;

opspec.States.Known = [0; 0; 1; 0; 0; 0; 0; 0; 0; 0; 0; 0; 0; 0]; % Only altitude is known as a state
opspec.States.SteadyState = [0; 0; 1; 1; 1; 1; 1; 1; 1; 1; 1; 1; 1; 1]; % We don't care if inertial positions are not in steady state
opspec.States.min = [-Inf; -Inf; 0; 0; -Inf; -Inf; -pi/2; -SkywalkerX8.Aerodynamics.alpha_0; -pi/2; -Inf; -Inf; -Inf; -pi/2; -pi/2];
opspec.States.max = opspec.States.min.*-1;

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

for i = 1:length(altitudePoints)
    
    alt = altitudePoints(i);
    Va = VaPoints(i);

    opspec.States.x = [0; 0; -alt; Va; 0; 0; 0; 0; 0; 0; 0; 0; 0; 0];
    opspec.Outputs(1).y = alt;
    opspec.Outputs(3).y = Va;
    [op, opreport] = findop(sys, opspec, opt);
    
    [lon_lat_A, lon_poles, lat_poles] = SkywalkerX8_FlightModes(op);
    [phi_max, r_max, min_R, q_max, p_max] = SkywalkerX8_Performance(opreport);
    
    SkywalkerX8.Performance.longitudinalPoles(:, i) = lon_poles;
    SkywalkerX8.Performance.longitudinalInstability(i) = (sum(lon_poles>1E-06)>=1);
    SkywalkerX8.Performance.lateralPoles(:, i) = lat_poles;
    SkywalkerX8.Performance.lateralInstability(i) = (sum(lat_poles>1E-06)>=1);
    
    SkywalkerX8.Performance.longLatStateMatrix(:, :, i) = lon_lat_A;
    
    SkywalkerX8.Performance.MaxBankAngle(i) = phi_max;
    SkywalkerX8.Performance.MinTurnRadius(i) = min_R;
    
    SkywalkerX8.Performance.maxRollRate(i) = p_max;
    SkywalkerX8.Performance.maxPitchRate(i) = q_max;
    SkywalkerX8.Performance.maxYawRate(i) = r_max;
    
end

%% Plotting 

createfigure(SkywalkerX8.FlightEnvelope.VaMin, SkywalkerX8.FlightEnvelope.altitude, 'V_a (m/s)', 'Altitude (m)');
hold on
plot(SkywalkerX8.FlightEnvelope.VaMax, SkywalkerX8.FlightEnvelope.altitude);
plot(SkywalkerX8.Performance.Va, SkywalkerX8.Performance.altitude, 'ro');

for i = 1:length(altitudePoints)
   
    txt = {['\phi_{max}: ', num2str(SkywalkerX8.Performance.MaxBankAngle(i)), ' rad'],...
           ['R_{min}: ', num2str(SkywalkerX8.Performance.MinTurnRadius(i)), ' m'],...
           ['p_{max}: ', num2str(SkywalkerX8.Performance.maxRollRate(i)), ' rad/s'],...
           ['q_{max}: ', num2str(SkywalkerX8.Performance.maxPitchRate(i)), ' rad/s'],...
           ['r_{max}: ', num2str(SkywalkerX8.Performance.maxYawRate(i)), ' rad/s']};
       
    switch i
        case 1
            text(SkywalkerX8.Performance.Va(i), SkywalkerX8.Performance.altitude(i),...
                txt, 'VerticalAlignment', 'bottom', 'HorizontalAlignment', 'right');
        case 2
            text(SkywalkerX8.Performance.Va(i), SkywalkerX8.Performance.altitude(i),...
                txt, 'VerticalAlignment', 'bottom', 'HorizontalAlignment', 'right');
        case 3
            text(SkywalkerX8.Performance.Va(i), SkywalkerX8.Performance.altitude(i),...
                txt, 'VerticalAlignment', 'bottom', 'HorizontalAlignment', 'left');
        case 4
            text(SkywalkerX8.Performance.Va(i), SkywalkerX8.Performance.altitude(i),...
                txt, 'VerticalAlignment', 'bottom', 'HorizontalAlignment', 'left');
        case 5
            text(SkywalkerX8.Performance.Va(i), SkywalkerX8.Performance.altitude(i),...
                txt, 'VerticalAlignment', 'top', 'HorizontalAlignment', 'left');
        case 6
            text(SkywalkerX8.Performance.Va(i), SkywalkerX8.Performance.altitude(i),...
                txt, 'VerticalAlignment', 'bottom', 'HorizontalAlignment', 'right');
        case 7
            text(SkywalkerX8.Performance.Va(i), SkywalkerX8.Performance.altitude(i),...
                txt, 'VerticalAlignment', 'top', 'HorizontalAlignment', 'left');
    end
    
end

axis([0 40 0 18000]);

%clearvars -except SkywalkerX8