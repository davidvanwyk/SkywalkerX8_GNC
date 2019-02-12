%% Control Design - Longitudinal %%

% The purpose of this script is to design the longitudinal control system
% for the SkywalkerX8 plant. One of the purposes of this script is to also
% determine if there is a need for gain-scheduling for each of the
% controllers, or if this requirement doesn't exist.

sys = 'SkywalkerX8_Longitudinal_Control';

ST0 = slTuner(sys);
ST0.Ts = 0; % We want continuous-time linearizations 

POI = {'SkywalkerX8_Longitudinal_Control/dt'
       'SkywalkerX8_Longitudinal_Control/de' 
       'SkywalkerX8_Longitudinal_Control/SkywalkerX8 Aircraft + Aerodynamics Longitudinal/Va' 
       'SkywalkerX8_Longitudinal_Control/SkywalkerX8 Aircraft + Aerodynamics Longitudinal/h' 
       'SkywalkerX8_Longitudinal_Control/SkywalkerX8 Aircraft + Aerodynamics Longitudinal/theta' 
       'SkywalkerX8_Longitudinal_Control/SkywalkerX8 Aircraft + Aerodynamics Longitudinal/q'};

ST0.addPoint(POI);

BlockSubs = struct('Name', {'SkywalkerX8_Longitudinal_Control/SkywalkerX8 Aircraft + Aerodynamics Longitudinal'}, 'Value', SkywalkerX8.Control.Longitudinal.LinearizedPlantBlockSub(:, :, 7));

ST0.BlockSubstitutions = BlockSubs;

ST0.addOpening('theta_c_h')

TunedBlocks = {'PID Controller theta' 'Kd_theta'};

ST0.addBlock(TunedBlocks);