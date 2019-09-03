%% Motor Setup %%

% Hacker A40-12S V2 14-Pole

SkywalkerX8.Actuators.Motor.TimeConstant = 0.2;

SkywalkerX8.Actuators.Motor.SS = ss(tf(1, [SkywalkerX8.Actuators.Motor.TimeConstant, 1]));

%% Servo Setup %%

% Team Corally - CS-3007 HV High Speed Mini Servo - High Voltage - Coreless Motor 
% - Titanium Gear - Ball Beared - Full Alloy Case

SkywalkerX8.Actuators.Servos.CutoffFrequency = 100;
SkywalkerX8.Actuators.Servos.zeta = sqrt(2)/2;

SkywalkerX8.Actuators.Servos.SS = ss(tf(SkywalkerX8.Actuators.Servos.CutoffFrequency^2,...
                                        [1, 2*SkywalkerX8.Actuators.Servos.CutoffFrequency*SkywalkerX8.Actuators.Servos.zeta, SkywalkerX8.Actuators.Servos.CutoffFrequency^2]));
SkywalkerX8.Actuators.Servos.TF = tf(SkywalkerX8.Actuators.Servos.SS);
% 0.08s for 60deg
SkywalkerX8.Actuators.Servos.RateLimit = deg2rad(60)/0.08;
SkywalkerX8.Actuators.Servos.UpperSaturation = deg2rad(30);
SkywalkerX8.Actuators.Servos.LowerSaturation = -deg2rad(30);