%% Va Dt Control Design %%

% Va is controlled either by using propeller speed (dt) or theta. This
% script deals with the former case, because the scheduling variable is
% simplified to be in terms of Va as this will dominate the dynamics of the
% system from the perspective of the dt->Va transfer function. 

% This linearized model from dt to Va was linearized assuming a constant theta,
% this is because if this isn't the case a small change in dt causes our
% system to shift out of trim and start to firstly gain altitude and then
% immediately lose because theta is not being controlled. Thus we force
% theta constant and trim that way. This is fine because we do not expect
% Va to be extremely dependent on alpha, so making it scheduled purely on
% Va is reasonable. 

% These will also be evaluated to determine if gain scheduling is even 
% needed for this controller.

%% System Setup %%

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

% This generates an initial block-sub for the SkywalkerX8_SkywalkerX8.Control.Longitudinal
% model. 

SkywalkerX8.Control.Longitudinal.LinearizedPlantModels.LinearizedPlantBlockSub = append(SkywalkerX8.Control.Longitudinal.LinearizedPlantModels.Dt2VaReducedModels,... 
                                                                                        [SkywalkerX8.Control.Longitudinal.LinearizedPlantModels.De2AltReducedModels,...
                                                                                        SkywalkerX8.Control.Longitudinal.LinearizedPlantModels.De2ThetaReducedModels,...
                                                                                        SkywalkerX8.Control.Longitudinal.LinearizedPlantModels.De2qReducedModels]');

plantSubValue = [SkywalkerX8.Control.Longitudinal.LinearizedPlantModels.LinearizedPlantBlockSub(1:3, :, :, :); 0, 0; SkywalkerX8.Control.Longitudinal.LinearizedPlantModels.LinearizedPlantBlockSub(end, :, :, :)];
plantSubName = [sys '/SkywalkerX8 Aircraft + Aerodynamics Longitudinal'];

plantSub = struct('Name', plantSubName, 'Value', plantSubValue);

%% Reset the variables into which our gains will be written

SkywalkerX8.Control.Longitudinal.VaDtController.KpVaDt = zeros(nVa, 1);
SkywalkerX8.Control.Longitudinal.VaDtController.KiVaDt = zeros(nVa, 1);
SkywalkerX8.Control.Longitudinal.VaDtController.KdVaDt = zeros(nVa, 1);
SkywalkerX8.Control.Longitudinal.VaDtController.NVaDt = zeros(nVa, 1);

SkywalkerX8.Control.Longitudinal.VaDtController.upperSaturationDt = Inf;
SkywalkerX8.Control.Longitudinal.VaDtController.lowerSaturationDt = -Inf;

%% Va Dt Control Design %%

Va = SkywalkerX8.Control.Longitudinal.SchedulingVariables.VaArray';

VaTuningGrid = struct('Va', Va);
VaShapeFcn = @(Va)[Va, Va^2];

disp('Starting Va_dt Control Loop Design...')

KpInit = 0.1818;
KiInit = 0.0921;
KdInit = -0.0313;
NInit = 4.6266;

Kp = tunableSurface('Kp', KpInit, VaTuningGrid, VaShapeFcn);
Ki = tunableSurface('Ki', KiInit, VaTuningGrid, VaShapeFcn);
Kd = tunableSurface('Kd', KdInit, VaTuningGrid, VaShapeFcn);
N = tunableSurface('N', NInit, VaTuningGrid, VaShapeFcn);

tunedBlocks = {'PIDF Controller Va_dt Kp Lookup Table',...
               'PIDF Controller Va_dt Ki Lookup Table',...
               'PIDF Controller Va_dt Kd Lookup Table',...
               'PIDF Controller Va_dt N Lookup Table'};

minRealTolerance = 1E-05;

VaDtPlantSubValue = [SkywalkerX8.Control.Longitudinal...
                    .LinearizedPlantModels.Dt2VaLinearizedModels tf(0);...
                    tf(0) tf(0);...
                    tf(0) tf(0);...
                    tf(0) tf(0);...
                    tf(0) tf(0)];
                          
VaDtPlantSubName = plantSubName;

VaDtPlantSub = struct('Name', VaDtPlantSubName, 'Value', VaDtPlantSubValue);

controllerThetaSubValue = [tf(0),...
                           tf(0),...
                           tf(0),...
                           tf(0),...
                           tf(0)];
                       
controllerThetaSubName = [sys '/Gain Scheduled Controller Theta'];

controllerThetaSub = struct('Name', controllerThetaSubName, 'Value', controllerThetaSubValue);

controllerSub = [tf(0) tf(0) tf(0)];
switchSub = [tf(0) tf(0) tf(0)]; %This changes from previous because we now want our theta_alt controller to go through
algBreakSub = tf(1);

controllerVaThetaName = [sys '/Gain Scheduled Controller Va_theta'];
controllerVaThetaValue = controllerSub;

controllerVaThetaSub = struct('Name', controllerVaThetaName, 'Value', controllerVaThetaValue);

controllerSwitchName = [sys '/Switch'];
controllerSwitchValue = switchSub;

controllerSwitchSub = struct('Name', controllerSwitchName, 'Value', controllerSwitchValue);

VaDtClampSwitchName = [sys '/Gain Scheduled Controller Va_dt/PIDF Controller Va_dt/Clamp Switch'];
VaDtClampSwitchValue = [tf(0) tf(0) tf(1)];

VaDtClampSwitchSub = struct('Name', VaDtClampSwitchName, 'Value', VaDtClampSwitchValue);

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
    
BlockSubs = [VaDtPlantSub;...
            controllerThetaSub;...
            controllerVaThetaSub;...
            controllerSwitchSub;...
            VaDtClampSwitchSub;...
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

POI = {'SkywalkerX8_Longitudinal_Control/Va_c'
       'SkywalkerX8_Longitudinal_Control/Va_e' 
       'SkywalkerX8_Longitudinal_Control/dt'
       'SkywalkerX8_Longitudinal_Control/SkywalkerX8 Aircraft + Aerodynamics Longitudinal/Va' 
       'SkywalkerX8_Longitudinal_Control/SkywalkerX8 Aircraft + Aerodynamics Longitudinal/h' 
       'SkywalkerX8_Longitudinal_Control/SkywalkerX8 Aircraft + Aerodynamics Longitudinal/theta'
       'SkywalkerX8_Longitudinal_Control/SkywalkerX8 Aircraft + Aerodynamics Longitudinal/alpha'
       'SkywalkerX8_Longitudinal_Control/SkywalkerX8 Aircraft + Aerodynamics Longitudinal/q'
       'SkywalkerX8_Longitudinal_Control/Gain Scheduled Controller Va_dt/PIDF Controller Va_dt/Sum/De'
       'SkywalkerX8_Longitudinal_Control/Gain Scheduled Controller Va_dt/PIDF Controller Va_dt/Product1/NDe'};

ST0.addPoint(POI);

ST0.addOpening('SkywalkerX8_Longitudinal_Control/SkywalkerX8 Aircraft + Aerodynamics Longitudinal/h');
ST0.addOpening('SkywalkerX8_Longitudinal_Control/SkywalkerX8 Aircraft + Aerodynamics Longitudinal/theta');
ST0.addOpening('SkywalkerX8_Longitudinal_Control/SkywalkerX8 Aircraft + Aerodynamics Longitudinal/alpha');
ST0.addOpening('SkywalkerX8_Longitudinal_Control/SkywalkerX8 Aircraft + Aerodynamics Longitudinal/q');

% We know we need to constrain what the maximum value can be for Kp due to
% actuator saturation.

% We know that dt cannot exceed 1. We also know what our expected maximum
% and minimum airspeeds are, so we use these to define our gain limit as being 
% approximately 50% (small signal) of the absolute max difference in Va. 
% We also take this chance to set saturation limits.

dtMax = 1;
VaChangeMax = (SkywalkerX8.Control.Longitudinal...
               .SchedulingVariables.VaArray(end)...
              - SkywalkerX8.Control.Longitudinal...
                .SchedulingVariables.VaArray(1))*1/2;
          
SkywalkerX8.Control.Longitudinal.VaDtController.upperSaturationDt = dtMax;
SkywalkerX8.Control.Longitudinal.VaDtController.lowerSaturationDt = 0;

% so we can generate a
% limit on gain from these 2 values:

VaDtGainLimit = dtMax/VaChangeMax;

% and we assume this will only really be commanded if we are in trim

VaDtPGainLimitInput = 'SkywalkerX8_Longitudinal_Control/Sum3/Va_e';
VaDtPGainLimitOutput = 'SkywalkerX8_Longitudinal_Control/Gain Scheduled Controller Va_dt/dt';

R1 = TuningGoal.Gain(VaDtPGainLimitInput, VaDtPGainLimitOutput, VaDtGainLimit);
R1.Focus = [1E-02 1E02];

% Next we know that our general response should have the standard gain
% margin of 6 dB, and a 60 deg phase margin forces a response that does not
% have a resonance peak, while still ensuring as rapid a response as
% possible (and around a 5% OS for a 2nd order system). So we assume this

gainMargin = 6; % >6 dB gain margin ideally
phaseMargin = 60; % 60 deg phase margin should provide adequate damping
R2 = TuningGoal.Margins('SkywalkerX8_Longitudinal_Control/SkywalkerX8 Aircraft + Aerodynamics Longitudinal/Va', gainMargin, phaseMargin);
R2.Focus = [1E-02 1E02];

% Next we know that we want our crossover frequency to be at approximately
% 3 rad/s so that it's much faster than the theta loop. We try and bump this
% up slightly so that it's as fast as it can be.

LS = frd([100 1 0.0001],[0.03 3 300]);  
R3 = TuningGoal.LoopShape('Va', LS, 0.5);

% Next we simply add a goal for our response in the time domain. We'd like
% this to be as fast as possible, given the previous constraints on
% crossover frequency and margins. 

wn = 0.1/2.2; %We want a rise time of approximately 0.1 s so we divide by 2.2 to get 
               %wn.
OS = 4; %4% overshoot is fine on Va and corresponds to the 70 degree phase
        %we specified previously

R4 = TuningGoal.StepTracking('Va_c', 'Va', wn, OS);

% Filter Frequency is kept low because the actuator can only respond in 0.2
% s, so our lag is 5 rad/s - meaning we limit this to half that.

NGainLimit = 2.5;

NGainLimitInput = 'SkywalkerX8_Longitudinal_Control/Gain Scheduled Controller Va_dt/PIDF Controller Va_dt/Sum/De';
NGainLimitOutput = 'SkywalkerX8_Longitudinal_Control/Gain Scheduled Controller Va_dt/PIDF Controller Va_dt/Product1/NDe';

NGainLimitLoopOpening = {NGainLimitInput,...
                         NGainLimitOutput};

R5 = TuningGoal.Gain(NGainLimitInput, NGainLimitOutput, NGainLimit);
R5.Openings = NGainLimitLoopOpening;
R5.Focus = [1E-02 1E02]; %Only focus on this frequency band

ST0.setBlockParam('PIDF Controller Va_dt Kp Lookup Table', Kp);
ST0.setBlockParam('PIDF Controller Va_dt Ki Lookup Table', Ki);
ST0.setBlockParam('PIDF Controller Va_dt Kd Lookup Table', Kd);
ST0.setBlockParam('PIDF Controller Va_dt N Lookup Table', N);

STVaDt = systune(ST0, [R1, R2], [R3, R4, R5], sysTuneOpts);

tableValues = getBlockValue(STVaDt);

SkywalkerX8.Control.Longitudinal.VaDtController.KpVaDtTF = tableValues.PIDF_Controller_Va_dt_Kp_Lookup_Table;
SkywalkerX8.Control.Longitudinal.VaDtController.KiVaDtTF = tableValues.PIDF_Controller_Va_dt_Ki_Lookup_Table;
SkywalkerX8.Control.Longitudinal.VaDtController.KdVaDtTF = tableValues.PIDF_Controller_Va_dt_Kd_Lookup_Table;
SkywalkerX8.Control.Longitudinal.VaDtController.NVaDtTF = tableValues.PIDF_Controller_Va_dt_N_Lookup_Table;

SkywalkerX8.Control.Longitudinal.VaDtController.KpVaDt = squeeze(tableValues.PIDF_Controller_Va_dt_Kp_Lookup_Table);
SkywalkerX8.Control.Longitudinal.VaDtController.KiVaDt = squeeze(tableValues.PIDF_Controller_Va_dt_Ki_Lookup_Table);
SkywalkerX8.Control.Longitudinal.VaDtController.KdVaDt = squeeze(tableValues.PIDF_Controller_Va_dt_Kd_Lookup_Table);
SkywalkerX8.Control.Longitudinal.VaDtController.NVaDt = squeeze(tableValues.PIDF_Controller_Va_dt_N_Lookup_Table);

% Get scheduling parameters and write them to our desired variables
% Note thase these are based on our basis function.

TGS = getBlockParam(STVaDt);
SkywalkerX8.Control.Longitudinal...
    .VaDtController.BasisFunction = TGS.PIDF_Controller_Va_dt_Kp_Lookup_Table.BasisFunctions;
SkywalkerX8.Control.Longitudinal...
    .VaDtController.KpVaDtParameterizedGains = getData(TGS.PIDF_Controller_Va_dt_Kp_Lookup_Table);
SkywalkerX8.Control.Longitudinal...
    .VaDtController.KiVaDtParameterizedGains = getData(TGS.PIDF_Controller_Va_dt_Ki_Lookup_Table);
SkywalkerX8.Control.Longitudinal...
    .VaDtController.KdVaDtParameterizedGains = getData(TGS.PIDF_Controller_Va_dt_Kd_Lookup_Table);
SkywalkerX8.Control.Longitudinal...
    .VaDtController.NVaDtParameterizedGains = getData(TGS.PIDF_Controller_Va_dt_N_Lookup_Table);

% Next we define our tracking constant (not used for controller design, but
% provided by the designer to assist with bumpless transfer in
% implementation). 

% This Is defined relative to our Ki gain via a scalar. As such, it should
% be x times faster than this integrator loop. 10 seems like a reasonable
% value.

SkywalkerX8.Control.Longitudinal.VaDtController.KtScalar = 10;

disp('Va_dt Control Loop Design Complete')