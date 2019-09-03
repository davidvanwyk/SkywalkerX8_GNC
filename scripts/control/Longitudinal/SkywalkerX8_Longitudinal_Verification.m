%% Skywalker X8 Longitudinal Controller Verification %%

% The purpose of this script is to review the longitudinal controllers
% designed in SkywalkerX8_Longitudinal_ControlDesign.m. The reason for this
% is that the controllers are designed assuming a reduced order linearized
% model - this is good design practice to remove complexities and as long
% as model divergence from the higher order models is kept in mind (ie.
% design the controllers to cut off the higher frequency dynamics) it
% shouldn't pose a problem. 

% This script will review the design by putting in the higher order
% linearized models - the user is then encouraged to review the design
% further by applying various test profiles to the system at different
% conditions in order to verify that everything works as expect when the
% non-linear model is employed. 

sys = 'SkywalkerX8_Longitudinal_Control';
SkywalkerX8.Control.Longitudinal.AlgebraicDesign.ReducedOrderModel.Controller.ThetaCSelector = 0;

LinOpt = linearizeOptions('SampleTime',0,'RateConversionMethod','tustin');  % seek continuous-time model

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

%% Altitude Loop Verification %%

% We will need to block substitute our plant model to our linearized
% version to do controller tuning. This will be true for all controller
% designs so is defined once in the beginning. 

% It should be noted that the outputs need to be padded on output 4 (which
% is alpha in the model) because otherwise our linearized model wouldn't
% have the correct IO dimensions. 

% This generates an initial block-sub for the SkywalkerX8_SkywalkerX8.Control.Longitudinal
% model. 

plantSubValue = [tf(0), tf(0);...
                 tf(0), SkywalkerX8.Control.Longitudinal.LinearizedPlantModels.De2AltLinearizedModels;...
                 tf(0), SkywalkerX8.Control.Longitudinal.LinearizedPlantModels.De2ThetaLinearizedModels;...
                 tf(0), tf(0);...
                 tf(0), SkywalkerX8.Control.Longitudinal.LinearizedPlantModels.De2qLinearizedModels];
plantSubName = [sys '/SkywalkerX8 Aircraft + Aerodynamics Longitudinal'];

plantSub = struct('Name', plantSubName, 'Value', plantSubValue);

q2de = tf(getIOTransfer(STTheta, 'q', 'de', {'theta', 'q'}));
theta_e2de = tf(getIOTransfer(STTheta, 'theta_e', 'de', {'theta', 'q'}));

controllerThetaSubValue = [theta_e2de,...
                           tf(0),...
                           tf(0),...
                           q2de];                       
controllerThetaSubName = [sys '/Gain Scheduled Controller Theta'];

controllerThetaSub = struct('Name', controllerThetaSubName, 'Value', controllerThetaSubValue);

h_e2theta_c_h = tf(getIOTransfer(STAlt, 'h_e', 'theta_c_h', {'h'}));

controllerHThetaName = [sys '/Gain Scheduled Controller h_theta'];
controllerHThetaValue = [h_e2theta_c_h,...
                         tf(0),...
                         tf(0)];

controllerHThetaSub = struct('Name', controllerHThetaName, 'Value', controllerHThetaValue);

controllerSub = [tf(0) tf(0) tf(0)];
switchSub = [tf(0) tf(0) tf(1)]; %This changes from previous because we now want our theta_alt controller to go through
algBreakSub = tf(1);

controllerVaDtName = [sys '/Gain Scheduled Controller Va_dt'];
controllerVaDtValue = controllerSub;

controllerVaDtSub = struct('Name', controllerVaDtName, 'Value', controllerVaDtValue);

controllerVaThetaName = [sys '/Gain Scheduled Controller Va_theta'];
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
    
BlockSubs = [plantSub;...
            controllerThetaSub;...
            controllerHThetaSub;...
            controllerVaDtSub;...
            controllerVaThetaSub;...
            controllerSwitchSub;...
            algebraicLoopBreak1Sub;...
            algebraicLoopBreak2Sub;...
            algebraicLoopBreak3Sub;...
            algebraicLoopBreak4Sub;...
            algebraicLoopBreak5Sub];

% Create slLinearizer interface for linearizing our model given all of our
% blocksubs and linearization options.

SLAlt = slLinearizer(sys, BlockSubs, LinOpt);

% Add all relevant points of interest (POI) that we will examine in the
% model.

POI = {'SkywalkerX8_Longitudinal_Control/h_c'
       'SkywalkerX8_Longitudinal_Control/h_e' 
       'SkywalkerX8_Longitudinal_Control/theta_c_h'
       'SkywalkerX8_Longitudinal_Control/theta_c'
       'SkywalkerX8_Longitudinal_Control/theta_e'
       'SkywalkerX8_Longitudinal_Control/de'
       'SkywalkerX8_Longitudinal_Control/SkywalkerX8 Aircraft + Aerodynamics Longitudinal/Va' 
       'SkywalkerX8_Longitudinal_Control/SkywalkerX8 Aircraft + Aerodynamics Longitudinal/h' 
       'SkywalkerX8_Longitudinal_Control/SkywalkerX8 Aircraft + Aerodynamics Longitudinal/theta'
       'SkywalkerX8_Longitudinal_Control/SkywalkerX8 Aircraft + Aerodynamics Longitudinal/alpha'
       'SkywalkerX8_Longitudinal_Control/SkywalkerX8 Aircraft + Aerodynamics Longitudinal/q'};

SLAlt.addPoint(POI);

SLAlt.addOpening('SkywalkerX8_Longitudinal_Control/SkywalkerX8 Aircraft + Aerodynamics Longitudinal/Va');
SLAlt.addOpening('SkywalkerX8_Longitudinal_Control/SkywalkerX8 Aircraft + Aerodynamics Longitudinal/alpha');