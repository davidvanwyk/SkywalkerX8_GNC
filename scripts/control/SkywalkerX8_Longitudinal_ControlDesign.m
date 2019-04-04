%% Control Design - Longitudinal %%

% The purpose of this script is to design the longitudinal control system
% for the SkywalkerX8 plant. 

sys = 'SkywalkerX8_Longitudinal_Control';
theta_c_Selector = 2;

LinOpt = linearizeOptions('SampleTime',0,'RateConversionMethod','tustin');  % seek continuous-time model

%% System Setup %%

% We know we have a gain scheduled controller as a function of Va and
% alpha. As such we create our tuning grids and parameterized gain surfaces
% as a function of the Va and alpha arrays that were used in the
% linearization process.

[Va, alpha] = ndgrid(SkywalkerX8.Control.Longitudinal.SchedulingVariables.VaArray,... 
    SkywalkerX8.Control.Longitudinal.SchedulingVariables.alphaArray);

TuningGrid = struct('alpha', alpha, 'Va', Va);
ShapeFcn = @(Va, alpha)[Va, alpha, Va*alpha];

nVa = length(SkywalkerX8.Control.Longitudinal.SchedulingVariables.VaArray);
nalpha = length(SkywalkerX8.Control.Longitudinal.SchedulingVariables.alphaArray);

% We will also need to block substitute our plant model to our linearized
% version to do controller tuning. This will be true for all controller
% designs so is defined once in the beginning. 

% It should be noted that the outputs need to be padded on output 4 (which
% is alpha in the model) because otherwise our linearized model wouldn't
% have the correct IO dimensions. 

plantSubValue = [SkywalkerX8.Control.Longitudinal.LinearizedPlantModels.LinearizedPlantBlockSub(1:3, :); 0, 0; SkywalkerX8.Control.Longitudinal.LinearizedPlantModels.LinearizedPlantBlockSub(end, :)];
plantSubName = [sys '/SkywalkerX8 Aircraft + Aerodynamics Longitudinal'];

plantSub = struct('Name', plantSubName, 'Value', plantSubValue);

%% Theta Controller %%

% The first controller we'd like to tune will be the combination of the rate 
% feedback loop and proportional pitch controller. Thus we have 2 gains 
% (ie. theta Controller Kd_theta 2D Lookup Table and PID Controller theta
% Kp 2D Lookup Table in the model). As such, we create a 2D tunable surface 
% and initialise the values based on our algebraic design (which is only a 
% function of Va). 

KpInit = SkywalkerX8.Control.Longitudinal.AlgebraicDesign.KpTheta(round(nVa/2));
KdInit = SkywalkerX8.Control.Longitudinal.AlgebraicDesign.KdTheta(round(nVa/2));

Kp = tunableSurface('Kp', KpInit, TuningGrid, ShapeFcn);
Kd = tunableSurface('Kd', KdInit, TuningGrid, ShapeFcn);

tunedBlocks = {'theta Controller Kd_theta 2D Lookup Table', 'PID Controller theta Kp 2D Lookup Table'};

% Remove all other blocks not relevant to this calculation 

controllerSub = [tf(0) tf(0) tf(0)];
switchSub = [tf(0) tf(0) tf(0)];

controllerVaDtName = [sys '/Gain Scheduled PI Controller Va_dt'];
controllerVaDtValue = controllerSub;

controllerVaDtSub = struct('Name', controllerVaDtName, 'Value', controllerVaDtValue);

controllerVaThetaName = [sys '/Gain Scheduled PIDF Controller Va_theta'];
controllerVaThetaValue = controllerSub;

controllerVaThetaSub = struct('Name', controllerVaThetaName, 'Value', controllerVaThetaValue);

controllerHThetaName = [sys '/Gain Scheduled PIDF Controller h_theta'];
controllerHThetaValue = controllerSub;

controllerHThetaSub = struct('Name', controllerHThetaName, 'Value', controllerHThetaValue);

controllerSwitchName = [sys '/Switch'];
controllerSwitchValue = switchSub;

controllerSwitchSub = struct('Name', controllerSwitchName, 'Value', controllerSwitchValue);

BlockSubs = [plantSub;...
    controllerVaDtSub;...
    controllerVaThetaSub;...
    controllerHThetaSub;...
    controllerSwitchSub];

ST0 = slTuner(sys, tunedBlocks, BlockSubs, LinOpt);

ST0.Ts = 0; % We want continuous-time linearizations 

POI = {'SkywalkerX8_Longitudinal_Control/dt'
       'SkywalkerX8_Longitudinal_Control/de' 
       'SkywalkerX8_Longitudinal_Control/SkywalkerX8 Aircraft + Aerodynamics Longitudinal/Va' 
       'SkywalkerX8_Longitudinal_Control/SkywalkerX8 Aircraft + Aerodynamics Longitudinal/h' 
       'SkywalkerX8_Longitudinal_Control/SkywalkerX8 Aircraft + Aerodynamics Longitudinal/theta'
       'SkywalkerX8_Longitudinal_Control/SkywalkerX8 Aircraft + Aerodynamics Longitudinal/alpha'
       'SkywalkerX8_Longitudinal_Control/SkywalkerX8 Aircraft + Aerodynamics Longitudinal/q'};

ST0.addPoint(POI);
ST0.addPoint('theta_e');
ST0.addPoint(['SkywalkerX8_Longitudinal_Control/2DOF Controller Theta + Rate Damping/'...
'Gain Scheduled P Controller Theta/PID Controller theta']);

ST0.addOpening('theta_c')

R1 = TuningGoal.LoopShape('theta', 7.5);
R2 = TuningGoal.Gain('theta_e', ['SkywalkerX8_Longitudinal_Control/2DOF Controller Theta + Rate Damping/'...
'Gain Scheduled P Controller Theta/PID Controller theta'], 0.2777);

ST0.setBlockParam('PID Controller theta Kp 2D Lookup Table', Kp, 'theta Controller Kd_theta 2D Lookup Table', Kd);

ST = systune(ST0, R1, R2);

% %% Alt Control Outer Loop %%
% 
% TunedBlocks = {'PID Controller h_theta'};
% 
% ST0.addPoint('h_e');
% ST0.addPoint('SkywalkerX8_Longitudinal_Control/Step1/1');
% ST0.addPoint('theta_c_h');
% ST0.addBlock(TunedBlocks);
% 
% R1 = TuningGoal.StepTracking('SkywalkerX8_Longitudinal_Control/Step1/1', 'h', 2*pi/1.1779);
% R2 = TuningGoal.Gain('h_e', 'theta_c_h', 0.8654);
% 
% ST = systune(ST0, R1, R2);
% 
% writeBlockValue(ST);