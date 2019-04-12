%% Control Design - Longitudinal %%

% The purpose of this script is to design the longitudinal control system
% for the SkywalkerX8 plant. 

sys = 'SkywalkerX8_Longitudinal_Control';
SkywalkerX8.Control.Longitudinal.AlgebraicDesign.ReducedOrderModel.Controller.ThetaCSelector = 0;

LinOpt = linearizeOptions('SampleTime',0,'RateConversionMethod','tustin');  % seek continuous-time model
sysTuneOpts = systuneOptions('MaxIter', 500, 'RandomStart', 5);

%% System Setup %%

% We know we have a gain scheduled controller as a function of Va and
% alpha. As such we create our tuning grids and parameterized gain surfaces
% as a function of the Va and alpha arrays that were used in the
% linearization process.

[Va, alpha] = ndgrid(SkywalkerX8.Control.Longitudinal.SchedulingVariables.VaArray,... 
    SkywalkerX8.Control.Longitudinal.SchedulingVariables.alphaArray);

TuningGrid = struct('Va', Va, 'alpha', alpha);
ShapeFcn = @(Va, alpha)[Va, alpha, Va*alpha];

nVa = length(SkywalkerX8.Control.Longitudinal.SchedulingVariables.VaArray);
nalpha = length(SkywalkerX8.Control.Longitudinal.SchedulingVariables.alphaArray);

% We will also need to block substitute our plant model to our linearized
% version to do controller tuning. This will be true for all controller
% designs so is defined once in the beginning. 

% It should be noted that the outputs need to be padded on output 4 (which
% is alpha in the model) because otherwise our linearized model wouldn't
% have the correct IO dimensions. 

plantSubValue = minreal([SkywalkerX8.Control.Longitudinal.LinearizedPlantModels.LinearizedPlantBlockSub(1:3, :, :, :); 0, 0; SkywalkerX8.Control.Longitudinal.LinearizedPlantModels.LinearizedPlantBlockSub(end, :, :, :)]);
plantSubName = [sys '/SkywalkerX8 Aircraft + Aerodynamics Longitudinal'];

plantSub = struct('Name', plantSubName, 'Value', plantSubValue);

% Reset the variables into which our gains will be written

SkywalkerX8.Control.Longitudinal.ThetaController.KpTheta = zeros(nVa, nalpha);
SkywalkerX8.Control.Longitudinal.ThetaController.KdTheta = zeros(nVa, nalpha);

SkywalkerX8.Control.Longitudinal.altController.KpAlt = zeros(nVa, nalpha);
SkywalkerX8.Control.Longitudinal.altController.KiAlt = zeros(nVa, nalpha);
SkywalkerX8.Control.Longitudinal.altController.KdAlt = zeros(nVa, nalpha);
SkywalkerX8.Control.Longitudinal.altController.NAlt  = zeros(nVa, nalpha);

SkywalkerX8.Control.Longitudinal.altController.aAlt = zeros(nVa, nalpha);
SkywalkerX8.Control.Longitudinal.altController.bAlt  = ones(nVa, nalpha); %Note that we have to do this to avoid division by 0

%% Theta Controller %%

% The first controller we'd like to tune will be the combination of the rate 
% feedback loop and proportional pitch controller. Thus we have 2 gains 
% (ie. theta Controller Kd_theta 2D Lookup Table and PID Controller theta
% Kp 2D Lookup Table in the model). As such, we create a 2D tunable surface 
% and initialise the values based on our algebraic design (which is only a 
% function of Va). 

disp('Theta Control Loop Design Started')

KpInit = SkywalkerX8.Control.Longitudinal.AlgebraicDesign.KpTheta(5);
KdInit = SkywalkerX8.Control.Longitudinal.AlgebraicDesign.KdTheta(5);

Kp = tunableSurface('Kp', KpInit, TuningGrid, ShapeFcn);
Kd = tunableSurface('Kd', KdInit, TuningGrid, ShapeFcn);

tunedBlocks = {'PID Controller theta Kp 2D Lookup Table', 'theta Controller Kd_theta 2D Lookup Table'};

% Remove all other blocks not relevant to this calculation 

thetaPlantSub = plantSub;

controllerSub = [tf(0) tf(0) tf(0)];
switchSub = [tf(0) tf(0) tf(0)];
algBreakSub = tf(1);

controllerVaDtName = [sys '/Gain Scheduled PI Controller Va_dt'];
controllerVaDtValue = controllerSub;

controllerVaDtSub = struct('Name', controllerVaDtName, 'Value', controllerVaDtValue);

controllerVaThetaName = [sys '/Gain Scheduled PIDF Controller Va_theta'];
controllerVaThetaValue = controllerSub;

controllerVaThetaSub = struct('Name', controllerVaThetaName, 'Value', controllerVaThetaValue);

controllerHThetaName = [sys '/Gain Scheduled Controller h_theta'];
controllerHThetaValue = controllerSub;

controllerHThetaSub = struct('Name', controllerHThetaName, 'Value', controllerHThetaValue);

controllerSwitchName = [sys '/Switch'];
controllerSwitchValue = switchSub;

controllerSwitchSub = struct('Name', controllerSwitchName, 'Value', controllerSwitchValue);

algebraicLoopBreakValue = algBreakSub;

algebraicLoopBreak1Name = [sys '/Alg Break 1'];
algebraicLoopBreak2Name = [sys '/Alg Break 2'];
algebraicLoopBreak3Name = [sys '/Alg Break 3'];
algebraicLoopBreak4Name = [sys '/Alg Break 4'];
algebraicLoopBreak5Name = [sys '/Alg Break 5'];

algebraicLoopBreak1Sub = struct('Name', algebraicLoopBreak1Name, 'Value', algebraicLoopBreakValue);
algebraicLoopBreak2Sub = struct('Name', algebraicLoopBreak2Name, 'Value', algebraicLoopBreakValue);
algebraicLoopBreak3Sub = struct('Name', algebraicLoopBreak3Name, 'Value', algebraicLoopBreakValue);
algebraicLoopBreak4Sub = struct('Name', algebraicLoopBreak4Name, 'Value', algebraicLoopBreakValue);
algebraicLoopBreak5Sub = struct('Name', algebraicLoopBreak5Name, 'Value', algebraicLoopBreakValue);
    
BlockSubs = [thetaPlantSub;...
    controllerVaDtSub;...
    controllerVaThetaSub;...
    controllerHThetaSub;...
    controllerSwitchSub;...
    algebraicLoopBreak1Sub;...
    algebraicLoopBreak2Sub;...
    algebraicLoopBreak3Sub;...
    algebraicLoopBreak4Sub;...
    algebraicLoopBreak5Sub];

% Create slTuner interface for tuning of tunedBlocks within the context of
% sys, after substituting out the blocks defined in BlockSubs, with the
% options given in LinOpt.

ST0 = slTuner(sys, tunedBlocks, BlockSubs, LinOpt);

ST0.Ts = 0; % We want continuous-time linearizations 

% Add all relevant points of interest (POI) that we will examine in the
% model.

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
ST0.addPoint(['SkywalkerX8_Longitudinal_Control/2DOF Controller Theta + Rate Damping/'...
'Gain Scheduled P Controller Theta/theta_e/1']);
ST0.addPoint(['SkywalkerX8_Longitudinal_Control/2DOF Controller Theta + Rate Damping/'...
'Gain Scheduled P Controller Theta/PID Controller theta/1']);

ST0.addPoint('theta_c');

ST0.addOpening('theta_c')

% We know we need to constrain what the maximum value can be for Kp due to
% actuator saturation. We'll pull this from the algebraic model gains as
% this is how they were calculated - but add these points here which define
% across where the gain is measured.

thetaPGainLimitInput = ['SkywalkerX8_Longitudinal_Control/2DOF Controller Theta + Rate Damping/'...
'Gain Scheduled P Controller Theta/theta_e/1'];
thetaPGainLimitOutput = ['SkywalkerX8_Longitudinal_Control/2DOF Controller Theta + Rate Damping/'...
'Gain Scheduled P Controller Theta/PID Controller theta/1'];

% Our tuning goals are variable across the linearization points. This is
% handled with varying goals that take in an array of conditions. We
% generate the array of conditions of the same size as the plant
% linearization and assign values from our algebraic calculation.

minDecayArray = zeros(nVa, nalpha);
minDampingArray = zeros(nVa, nalpha);
maxFreqArray = zeros(nVa, nalpha);

gainArray = zeros(nVa, nalpha);

for i = 1:nVa
    minDecayArray(i, :) = SkywalkerX8.Control.Longitudinal.AlgebraicDesign.NatFreqTheta(i);
    minDampingArray(i, :) = 1/sqrt(2);
    maxFreqArray(i, :) = inf;
    
    gainArray(i, :) = abs(SkywalkerX8.Control.Longitudinal.AlgebraicDesign.KpTheta(i));
end

% Create varying tuning goal templates @(param1, param2) param1*param2 will
% get evaluated for each operating condition.

R1Template = @(minDecay, minDamping, maxFreq) TuningGoal.Poles(minDecay, minDamping, maxFreq);
R2Template = @(gain) TuningGoal.Gain(thetaPGainLimitInput, thetaPGainLimitOutput, gain);

R1 = varyingGoal(R1Template, minDecayArray, minDampingArray, maxFreqArray);
R2 = varyingGoal(R2Template, gainArray);

gainMargin = 6; % 6 dB gain margin ideally
phaseMargin = 70; % 70 deg phase margin would provide adequate damping 1/sqrt(2) <= zeta < 1
R3 = TuningGoal.Margins('SkywalkerX8_Longitudinal_Control/SkywalkerX8 Aircraft + Aerodynamics Longitudinal/theta', gainMargin, phaseMargin);
R3.Openings = 'SkywalkerX8_Longitudinal_Control/SkywalkerX8 Aircraft + Aerodynamics Longitudinal/theta';

% Set block params to our tunable surfaces and tune with gain being our
% hard goal (because we need to force this or else we'll get actuator
% saturation) and transient performance being soft (this is just a nice to
% have, but isn't critical to operation).

ST0.setBlockParam('PID Controller theta Kp 2D Lookup Table', Kp,...
    'theta Controller Kd_theta 2D Lookup Table', Kd);
STTheta = systune(ST0, [R1 R3], R2, sysTuneOpts);

% Get values from ST and write them to our desired variables
% Note that TF here stands for transfer function and simply captures the
% values with the correct structure so that later they can be used for
% block subs.

tableValues = getBlockValue(STTheta);
SkywalkerX8.Control.Longitudinal.ThetaController.KpThetaTF = tableValues.PID_Controller_theta_Kp_2D_Lookup_Table;
SkywalkerX8.Control.Longitudinal.ThetaController.KdThetaTF = tableValues.theta_Controller_Kd_theta_2D_Lookup_Table;
SkywalkerX8.Control.Longitudinal.ThetaController.KpTheta = squeeze(tableValues.PID_Controller_theta_Kp_2D_Lookup_Table);
SkywalkerX8.Control.Longitudinal.ThetaController.KdTheta = squeeze(tableValues.theta_Controller_Kd_theta_2D_Lookup_Table);

% Get scheduling parameters and write them to our desired variables
% Note thase these are based on our basis function.

TGS = getBlockParam(STTheta);
SkywalkerX8.Control.Longitudinal.ThetaController.BasisFunction = TGS.PID_Controller_theta_Kp_2D_Lookup_Table.BasisFunctions;
SkywalkerX8.Control.Longitudinal.ThetaController.KpThetaParameterizedGains = getData(TGS.PID_Controller_theta_Kp_2D_Lookup_Table);
SkywalkerX8.Control.Longitudinal.ThetaController.KdThetaParameterizedGains = getData(TGS.theta_Controller_Kd_theta_2D_Lookup_Table);

%% Alt Control Outer Loop %%

% Unfortunately our system from theta_c to h (the new plant, essentially)
% is non-minimum phase. As such, one needs to move beyond a simple PIDF
% controller and allow for greater flexibility in tuning. From a simple 3rd
% order LQG controller tuned in siso tool, it seems that adding a single
% pole should do the trick (or a lead lag with 0 lead); so as such we add a
% gain-scheduled lead-lag pre-compensator to our PIDF controller.

disp('Alt Control Loop Design Started')

aInit = 0.1;
bInit = 0.1;

KpInit = SkywalkerX8.Control.Longitudinal.AlgebraicDesign.KpAlt(5);
KiInit = SkywalkerX8.Control.Longitudinal.AlgebraicDesign.KiAlt(5);
KdInit = 0.1*KpInit;
NInit = 1/(5*SkywalkerX8.Control.Longitudinal.AlgebraicDesign.NatFreqAlt(5)); %Make the derivative filter 5x faster than the system dynamics (to filer noise but not impact performance)

a = tunableSurface('a', aInit, TuningGrid, ShapeFcn);
b = tunableSurface('b', bInit, TuningGrid, ShapeFcn);

Kp = tunableSurface('Kp', KpInit, TuningGrid, ShapeFcn);
Ki = tunableSurface('Ki', KiInit, TuningGrid, ShapeFcn);
Kd = tunableSurface('Kd', KdInit, TuningGrid, ShapeFcn);
N  = tunableSurface('N' , NInit , TuningGrid, ShapeFcn);

tunedBlocks = {'Lead Lag Compensator h_theta a 2D Lookup Table',...
    'Lead Lag Compensator h_theta b 2D Lookup Table',...
    'PID Controller h_theta Kp 2D Lookup Table',...
    'PID Controller h_theta Ki 2D Lookup Table',...
    'PID Controller h_theta Kd 2D Lookup Table',...
    'PID Controller h_theta N 2D Lookup Table'};

% We want to substitute out previously tuned gains from their lookup table
% format into a varying gain block in the model. 
% An alternative approach to this is to simply get the transfer function
% from theta_c to alt (h) and then block sub out our inner loop controller
% for unity gain and replace our plant block sub model I/O from de to
% altitude with the theta_c to altitude models. This will allow us to make
% use of the min-real function to reduce the number of states of the
% system and remove any physically unrealistic instabilities. Note that
% because we get rid of the de -> theta model, we don't need to worry about
% breaking the loop.

transFuncsTheta_CtoAlt = ss(getIOTransfer(STTheta, 'theta_c', 'h'));

altPlantSubValue = minreal([tf(0) tf(0); tf(0) transFuncsTheta_CtoAlt; tf(0) tf(0);  tf(0) tf(0); tf(0) tf(0)]);
altPlantSubName = plantSubName;

altPlantSub = struct('Name', altPlantSubName, 'Value', altPlantSubValue);

thetaControllerBlockSubName = 'SkywalkerX8_Longitudinal_Control/2DOF Controller Theta + Rate Damping';
thetaControllerBlockSubValue = [tf(1) tf(0) tf(0) tf(0)];

thetaControllerBlockSub = struct('Name', thetaControllerBlockSubName,... 
    'Value', thetaControllerBlockSubValue);

% Remove all other blocks not relevant to this calculation 

controllerSub = [tf(0) tf(0) tf(0)];
switchSub = [tf(0) tf(0) tf(1)]; %The switch is subbed out to be unity gain from input 3 to output 1
algBreakSub = tf(1);

controllerVaDtName = [sys '/Gain Scheduled PI Controller Va_dt'];
controllerVaDtValue = controllerSub;

controllerVaDtSub = struct('Name', controllerVaDtName, 'Value', controllerVaDtValue);

controllerVaThetaName = [sys '/Gain Scheduled PIDF Controller Va_theta'];
controllerVaThetaValue = controllerSub;

controllerVaThetaSub = struct('Name', controllerVaThetaName, 'Value', controllerVaThetaValue);

controllerSwitchName = [sys '/Switch'];
controllerSwitchValue = switchSub;

controllerSwitchSub = struct('Name', controllerSwitchName, 'Value', controllerSwitchValue);

algebraicLoopBreakValue = algBreakSub;

algebraicLoopBreak1Name = [sys '/Alg Break 1'];
algebraicLoopBreak2Name = [sys '/Alg Break 2'];
algebraicLoopBreak3Name = [sys '/Alg Break 3'];
algebraicLoopBreak4Name = [sys '/Alg Break 4'];
algebraicLoopBreak5Name = [sys '/Alg Break 5'];

algebraicLoopBreak1Sub = struct('Name', algebraicLoopBreak1Name, 'Value', algebraicLoopBreakValue);
algebraicLoopBreak2Sub = struct('Name', algebraicLoopBreak2Name, 'Value', algebraicLoopBreakValue);
algebraicLoopBreak3Sub = struct('Name', algebraicLoopBreak3Name, 'Value', algebraicLoopBreakValue);
algebraicLoopBreak4Sub = struct('Name', algebraicLoopBreak4Name, 'Value', algebraicLoopBreakValue);
algebraicLoopBreak5Sub = struct('Name', algebraicLoopBreak5Name, 'Value', algebraicLoopBreakValue);

BlockSubs = [altPlantSub;...
    controllerVaDtSub;...
    controllerVaThetaSub;...
    controllerSwitchSub;...
    algebraicLoopBreak1Sub;...
    algebraicLoopBreak2Sub;...
    algebraicLoopBreak3Sub;...
    algebraicLoopBreak4Sub;...
    algebraicLoopBreak5Sub;...
    thetaControllerBlockSub];

% Create slTuner interface for tuning of tunedBlocks within the context of
% sys, after substituting out the blocks defined in BlockSubs, with the
% options given in LinOpt.

ST1 = slTuner(sys, tunedBlocks, BlockSubs, LinOpt);

ST1.Ts = 0; % We want continuous-time linearizations 

% Add all relevant points of interest (POI) that we will examine in the
% model.

altControllerName = [sys '/Gain Scheduled Controller h_theta'];

% We know we need to constrain what the maximum value can be for Kp due to
% actuator saturation. We'll pull this from the algebraic model gains as
% this is how they were calculated - but add these points here which define
% across where the gain is measured.

altPGainLimitInput = 'h_e';
altPGainLimitOutput = [altControllerName '/PIDF Controller h_theta/POut'];

% General plant IO

POI = {'SkywalkerX8_Longitudinal_Control/dt'
       'SkywalkerX8_Longitudinal_Control/de' 
       'SkywalkerX8_Longitudinal_Control/SkywalkerX8 Aircraft + Aerodynamics Longitudinal/Va' 
       'SkywalkerX8_Longitudinal_Control/SkywalkerX8 Aircraft + Aerodynamics Longitudinal/h' 
       'SkywalkerX8_Longitudinal_Control/SkywalkerX8 Aircraft + Aerodynamics Longitudinal/theta'
       'SkywalkerX8_Longitudinal_Control/SkywalkerX8 Aircraft + Aerodynamics Longitudinal/alpha'
       'SkywalkerX8_Longitudinal_Control/SkywalkerX8 Aircraft + Aerodynamics Longitudinal/q'};

ST1.addPoint(POI);
ST1.addPoint(altPGainLimitInput);
ST1.addPoint(altPGainLimitOutput);

ST1.addPoint('h_c');

% Our tuning goals are variable across the linearization points. This is
% handled with varying goals that take in an array of conditions. We
% generate the array of conditions of the same size as the plant
% linearization and assign values from our algebraic calculation.

minDecayArray = zeros(nVa, nalpha);
minDampingArray = zeros(nVa, nalpha);
maxFreqArray = zeros(nVa, nalpha);

gainArray = zeros(nVa, nalpha);

maximumExpectedAltitude = 50; % This is 1/10 of the absolute max altitude expected

for i = 1:nVa
    
    minDecayArray(i, :) = SkywalkerX8.Control.Longitudinal.AlgebraicDesign.NatFreqAlt(i)*1/2; %We allow for slower dynamics in non-linear to relax tuning constraints.
    minDampingArray(i, :) = 1/sqrt(2);
    maxFreqArray(i, :) = inf;
    
    Va = SkywalkerX8.Control.Longitudinal.SchedulingVariables.VaArray(i);
    
    maximumAllowedTheta = interp1([SkywalkerX8.Performance.Va(1)... 
        SkywalkerX8.Performance.Va(end-1)], [SkywalkerX8.Performance.maxPitchAngle(1)... 
        SkywalkerX8.Performance.maxPitchAngle(end-1)], Va);

    gainArray(i, :) = abs(maximumAllowedTheta/maximumExpectedAltitude);
    
end

% Create varying tuning goal templates @(param1, param2) param1*param2 will
% get evaluated for each operating condition.

R1Template = @(minDecay, minDamping, maxFreq) TuningGoal.Poles(minDecay, minDamping, maxFreq);
R2Template = @(gain) TuningGoal.Gain(altPGainLimitInput, altPGainLimitOutput, gain);

R1 = varyingGoal(R1Template, minDecayArray, minDampingArray, maxFreqArray);
R2 = varyingGoal(R2Template, gainArray);

gainMargin = 6; % 6 dB gain margin ideally
phaseMargin = 70; % 70 deg phase margin would provide adequate damping 1/sqrt(2) <= zeta < 1
R3 = TuningGoal.Margins('SkywalkerX8_Longitudinal_Control/SkywalkerX8 Aircraft + Aerodynamics Longitudinal/h', gainMargin, phaseMargin);
R3.Openings = 'SkywalkerX8_Longitudinal_Control/SkywalkerX8 Aircraft + Aerodynamics Longitudinal/h';

% Set block params to our tunable surfaces and tune with gain being our
% hard goal (because we need to force this or else we'll get actuator
% saturation) and transient performance being soft (this is just a nice to
% have, but isn't critical to operation).

ST1.setBlockParam('Lead Lag Compensator h_theta a 2D Lookup Table', a,...
    'Lead Lag Compensator h_theta b 2D Lookup Table', b,...
    'PID Controller h_theta Kp 2D Lookup Table', Kp,...
    'PID Controller h_theta Ki 2D Lookup Table', Ki,...
    'PID Controller h_theta Kd 2D Lookup Table', Kd,...
    'PID Controller h_theta N 2D Lookup Table', N);

STAlt = systune(ST1, R3, R1, sysTuneOpts);

% Get values from ST and write them to our desired variables

% tableValues = getBlockValue(ST);
% SkywalkerX8.Control.Longitudinal.ThetaController.KpTheta = squeeze(tableValues.PID_Controller_theta_Kp_2D_Lookup_Table);
% SkywalkerX8.Control.Longitudinal.ThetaController.KdTheta = squeeze(tableValues.theta_Controller_Kd_theta_2D_Lookup_Table);
% 
% % Get scheduling parameters and write them to our desired variables
% % Note thase these are based on our basis function.
% 
% TGS = getBlockParam(ST);
% SkywalkerX8.Control.Longitudinal.ThetaController.BasisFunction = TGS.PID_Controller_theta_Kp_2D_Lookup_Table.BasisFunctions;
% SkywalkerX8.Control.Longitudinal.ThetaController.KpThetaParameterizedGains = getData(TGS.PID_Controller_theta_Kp_2D_Lookup_Table);
% SkywalkerX8.Control.Longitudinal.ThetaController.KdThetaParameterizedGains = getData(TGS.tableValues.theta_Controller_Kd_theta_2D_Lookup_Table);
% 
% ST0.removeOpening('theta_c');