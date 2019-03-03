%% Control Design - Longitudinal %%

% The purpose of this script is to design the longitudinal control system
% for the SkywalkerX8 plant. One of the purposes of this script is to also
% determine if there is a need for gain-scheduling for each of the
% controllers, or if this requirement doesn't exist.

sys = 'SkywalkerX8_Longitudinal_Control';
theta_c_Selector = 2;

ST0 = slTuner(sys);
ST0.Ts = 0; % We want continuous-time linearizations 

POI = {'SkywalkerX8_Longitudinal_Control/dt'
       'SkywalkerX8_Longitudinal_Control/de' 
       'SkywalkerX8_Longitudinal_Control/SkywalkerX8 Aircraft + Aerodynamics Longitudinal/Va' 
       'SkywalkerX8_Longitudinal_Control/SkywalkerX8 Aircraft + Aerodynamics Longitudinal/h' 
       'SkywalkerX8_Longitudinal_Control/SkywalkerX8 Aircraft + Aerodynamics Longitudinal/theta' 
       'SkywalkerX8_Longitudinal_Control/SkywalkerX8 Aircraft + Aerodynamics Longitudinal/q'};

ST0.addPoint(POI);
ST0.addPoint('theta_e');
ST0.addPoint('PID Controller theta');

BlockSubs = struct('Name', {'SkywalkerX8_Longitudinal_Control/SkywalkerX8 Aircraft + Aerodynamics Longitudinal'}, 'Value', SkywalkerX8.Control.Longitudinal.LinearizedPlantModels.LinearizedPlantBlockSub(:, :, 1));

ST0.BlockSubstitutions = BlockSubs;

%% Theta Control Inner Loop %%

TunedBlocks = {'PID Controller theta' 'Kd_theta'};

ST0.addOpening('theta_c_h')
ST0.addBlock(TunedBlocks);

R1 = TuningGoal.LoopShape('theta', 3.5336);
R2 = TuningGoal.Gain('theta_e', 'PID Controller theta', 0.667);

ST = systune(ST0, R1, R2);

writeBlockValue(ST);

ST0.removeBlock(TunedBlocks);
ST0.removeOpening('theta_c_h');

%% Alt Control Outer Loop %%

TunedBlocks = {'PID Controller h_theta'};

ST0.addPoint('h_e');
ST0.addPoint('SkywalkerX8_Longitudinal_Control/Step1/1');
ST0.addPoint('theta_c_h');
ST0.addBlock(TunedBlocks);

R1 = TuningGoal.StepTracking('SkywalkerX8_Longitudinal_Control/Step1/1', 'h', 2*pi/1.1779);
R2 = TuningGoal.Gain('h_e', 'theta_c_h', 0.8654);

ST = systune(ST0, R1, R2);

writeBlockValue(ST);