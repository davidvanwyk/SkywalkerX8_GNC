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

% This generates an initial block-sub for the SkywalkerX8_SkywalkerX8.Control.Longitudinal
% model. 

SkywalkerX8.Control.Longitudinal.LinearizedPlantModels.LinearizedPlantBlockSub = append(SkywalkerX8.Control.Longitudinal.LinearizedPlantModels.Dt2VaReducedModels,... 
                                                                                        [SkywalkerX8.Control.Longitudinal.LinearizedPlantModels.De2AltReducedModels,...
                                                                                        SkywalkerX8.Control.Longitudinal.LinearizedPlantModels.De2ThetaReducedModels,...
                                                                                        SkywalkerX8.Control.Longitudinal.LinearizedPlantModels.De2qReducedModels]');

plantSubValue = [SkywalkerX8.Control.Longitudinal.LinearizedPlantModels.LinearizedPlantBlockSub(1:3, :, :, :); 0, 0; SkywalkerX8.Control.Longitudinal.LinearizedPlantModels.LinearizedPlantBlockSub(end, :, :, :)];
plantSubName = [sys '/SkywalkerX8 Aircraft + Aerodynamics Longitudinal'];

plantSub = struct('Name', plantSubName, 'Value', plantSubValue);

% Reset the variables into which our gains will be written

SkywalkerX8.Control.Longitudinal.thetaController.KpTheta = zeros(nVa, nalpha);
SkywalkerX8.Control.Longitudinal.thetaController.KiTheta = zeros(nVa, nalpha);
SkywalkerX8.Control.Longitudinal.thetaController.KdTheta = zeros(nVa, nalpha);
SkywalkerX8.Control.Longitudinal.thetaController.NTheta = zeros(nVa, nalpha);

SkywalkerX8.Control.Longitudinal.thetaController.KpTheta2DOF = zeros(nVa, nalpha);
SkywalkerX8.Control.Longitudinal.thetaController.KdTheta2DOF = zeros(nVa, nalpha);
SkywalkerX8.Control.Longitudinal.thetaController.NTheta2DOF = zeros(nVa, nalpha);

SkywalkerX8.Control.Longitudinal.altController.KpAlt = zeros(nVa, nalpha);
SkywalkerX8.Control.Longitudinal.altController.KiAlt = zeros(nVa, nalpha);
SkywalkerX8.Control.Longitudinal.altController.KdAlt = zeros(nVa, nalpha);
SkywalkerX8.Control.Longitudinal.altController.NAlt = zeros(nVa, nalpha);

SkywalkerX8.Control.Longitudinal.altController.KpAlt2DOF = zeros(nVa, nalpha);
SkywalkerX8.Control.Longitudinal.altController.KdAlt2DOF = zeros(nVa, nalpha);
SkywalkerX8.Control.Longitudinal.altController.NAlt2DOF = zeros(nVa, nalpha);

SkywalkerX8.Control.Longitudinal.VaThetaController.KpVaTheta = zeros(nVa, nalpha);
SkywalkerX8.Control.Longitudinal.VaThetaController.KiVaTheta = zeros(nVa, nalpha);
SkywalkerX8.Control.Longitudinal.VaThetaController.KdVaTheta = zeros(nVa, nalpha);
SkywalkerX8.Control.Longitudinal.VaThetaController.NVaTheta = zeros(nVa, nalpha);

SkywalkerX8.Control.Longitudinal.VaThetaController.KpVaTheta2DOF = zeros(nVa, nalpha);
SkywalkerX8.Control.Longitudinal.VaThetaController.KdVaTheta2DOF = zeros(nVa, nalpha);
SkywalkerX8.Control.Longitudinal.VaThetaController.NVaTheta2DOF = zeros(nVa, nalpha);

% Reset Saturation Limits %

SkywalkerX8.Control.Longitudinal.thetaController.upperSaturationNegativeDe = Inf;
SkywalkerX8.Control.Longitudinal.thetaController.lowerSaturationNegativeDe = -Inf;

SkywalkerX8.Control.Longitudinal.altController.upperSaturationThetaC = Inf;
SkywalkerX8.Control.Longitudinal.altController.lowerSaturationThetaC = -Inf;

SkywalkerX8.Control.Longitudinal.VaThetaController.upperSaturationThetaC = Inf;
SkywalkerX8.Control.Longitudinal.VaThetaController.lowerSaturationThetaC = -Inf;

%% q Controller %%

% The first controller to tune is the q controller. This is essentially a
% rearranged version of the rate-damping controller, and is equivalent to
% taking the normal rate damping term and putting it in as a P controller
% while adding 1/K before the summing junction. This just is easier to
% analyze. 

% Note: An even simpler methodology is to use q as the "DF" term in the
% theta PIDF controller. This removes the complexity of needing another
% tuning step and allows goals to be defined in a much more logical way
% (ie. providing tuning goals for a P q controller is rather difficult and
% not really physically meaningful without taking the theta controller into
% consideration either way).

%% Theta Controller %%

% The next controller we'd like to tune will be the pitch controller.  
% Thus, we create a 2D tunable surface and initialise the values based on 
% sisotool at midpoint Va and alpha - keeping our gain limit in mind (which
% will be calculated later on).

disp('Theta Control Loop Design Started')
    
% We can see from sisotool that having a PIDF controller is more beneficial 
% than the normal PI controller. We get the following gains from sisotool 
% with a midpoint controller (Va, alpha) = (Va(5), alpha(3)). We then do
% our tuning and update this with the tuned midpoint controller from that
% (can be repeated as many times as the user would like) from time to time.

KpInit = 0.1096;
KiInit = 0.3107;
KdInit = -0.3911;
NInit = 0.3323;

Kp2DOFInit = -1.0415;
Kd2DOFInit = 0.8578;
N2DOFInit = 0.9124;

Kp = tunableSurface('Kp', KpInit, TuningGrid, ShapeFcn);
Ki = tunableSurface('Ki', KiInit, TuningGrid, ShapeFcn);
Kd = tunableSurface('Kd', KdInit, TuningGrid, ShapeFcn);
N = tunableSurface('N', NInit, TuningGrid, ShapeFcn);

Kp2DOF = tunableSurface('Kp2DOF', Kp2DOFInit, TuningGrid, ShapeFcn);
Kd2DOF = tunableSurface('Kd2DOF', Kd2DOFInit, TuningGrid, ShapeFcn);
N2DOF = tunableSurface('N2DOF', N2DOFInit, TuningGrid, ShapeFcn);

tunedBlocks = {'PIDF Controller theta Kp 2D Lookup Table',... 
               'PIDF Controller theta Ki 2D Lookup Table',...
               'PIDF Controller theta Kd 2D Lookup Table',...
               'PIDF Controller theta N 2D Lookup Table',...
               'PDF Controller theta 2DOF Kp 2D Lookup Table',...
               'PDF Controller theta 2DOF Kd 2D Lookup Table',...
               'PDF Controller theta 2DOF N 2D Lookup Table'};

thetaPlantSubValue = [tf(0) SkywalkerX8.Control.Longitudinal...
                      .LinearizedPlantModels.De2VaReducedModels;...
                      tf(0) SkywalkerX8.Control.Longitudinal...
                      .LinearizedPlantModels.De2AltReducedModels;...
                      tf(0) SkywalkerX8.Control.Longitudinal...
                      .LinearizedPlantModels.De2ThetaReducedModels;...
                      tf(0) tf(0);...
                      tf(0) SkywalkerX8.Control.Longitudinal...
                      .LinearizedPlantModels.De2qReducedModels];
                          
thetaPlantSubName = plantSubName;

thetaPlantSub = struct('Name', thetaPlantSubName, 'Value', thetaPlantSubValue);

switchSub = [tf(0) tf(0) tf(0)];
algBreakSub = tf(1);

controllerVaDtName = [sys '/Gain Scheduled Controller Va_dt'];
controllerVaDtValue = [tf(0) tf(0)];

controllerVaDtSub = struct('Name', controllerVaDtName, 'Value', controllerVaDtValue);

controllerVaThetaName = [sys '/Gain Scheduled Controller Va_theta'];
controllerVaThetaValue = [tf(0) tf(0) tf(0)];

controllerVaThetaSub = struct('Name', controllerVaThetaName, 'Value', controllerVaThetaValue);

controllerHThetaName = [sys '/Gain Scheduled Controller h_theta'];
controllerHThetaValue = [tf(0) tf(0) tf(0)];

controllerHThetaSub = struct('Name', controllerHThetaName, 'Value', controllerHThetaValue);

controllerSwitchName = [sys '/Switch'];
controllerSwitchValue = switchSub;

controllerSwitchSub = struct('Name', controllerSwitchName, 'Value', controllerSwitchValue);

thetaClampSwitchName = [sys '/Gain Scheduled Controller Theta/PI Controller Theta/Clamp Switch'];
thetaClampSwitchValue = [tf(0) tf(0) tf(1)];

thetaClampSwitchSub = struct('Name', thetaClampSwitchName, 'Value', thetaClampSwitchValue);

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
            thetaClampSwitchSub;...
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

POI = {'SkywalkerX8_Longitudinal_Control/theta_c'
       'SkywalkerX8_Longitudinal_Control/theta_e' 
       'SkywalkerX8_Longitudinal_Control/de'
       'SkywalkerX8_Longitudinal_Control/Gain Scheduled Controller Theta/DF Controller Theta/Sum/de*_e'
       'SkywalkerX8_Longitudinal_Control/Gain Scheduled Controller Theta/DF Controller Theta/Product1/Nde*_e'
       'SkywalkerX8_Longitudinal_Control/Gain Scheduled Controller Theta/DF Controller Theta/Integrator/de*'
       'SkywalkerX8_Longitudinal_Control/Switch/theta_c'
       'SkywalkerX8_Longitudinal_Control/Gain Scheduled Controller Theta/de'
       'SkywalkerX8_Longitudinal_Control/Gain Scheduled Controller Theta/PI Controller Theta/POut'
       'SkywalkerX8_Longitudinal_Control/SkywalkerX8 Aircraft + Aerodynamics Longitudinal/Va' 
       'SkywalkerX8_Longitudinal_Control/SkywalkerX8 Aircraft + Aerodynamics Longitudinal/h' 
       'SkywalkerX8_Longitudinal_Control/SkywalkerX8 Aircraft + Aerodynamics Longitudinal/theta'
       'SkywalkerX8_Longitudinal_Control/SkywalkerX8 Aircraft + Aerodynamics Longitudinal/alpha'
       'SkywalkerX8_Longitudinal_Control/SkywalkerX8 Aircraft + Aerodynamics Longitudinal/q'};

ST0.addPoint(POI);

ST0.addOpening('theta_c');
ST0.addOpening('SkywalkerX8_Longitudinal_Control/SkywalkerX8 Aircraft + Aerodynamics Longitudinal/Va');
ST0.addOpening('SkywalkerX8_Longitudinal_Control/SkywalkerX8 Aircraft + Aerodynamics Longitudinal/h');
ST0.addOpening('SkywalkerX8_Longitudinal_Control/SkywalkerX8 Aircraft + Aerodynamics Longitudinal/alpha');

% We know we need to constrain what the maximum value can be for Kp due to
% actuator saturation.

% We'll make the assumption that theta will not exceed 60 degrees, and we
% know our maximum elevator deflection. We will assume our maximum
% generated command from the outer loop will not be an instant swing - so
% we assume 50% of the expected maximum theta. We also take this
% opportunity to set our saturation limits.

thetaMax = 60*pi/180*0.5;
deMax = 2*15*pi/180; %x2 because our mixing matrix essentially halves this across 2 actuators

SkywalkerX8.Control.Longitudinal.thetaController...
    .upperSaturationNegativeDe = deMax;
SkywalkerX8.Control.Longitudinal.thetaController...
    .lowerSaturationNegativeDe = -deMax;

% so we can generate a
% limit on gain from these 2 values:

thetaGainLimit = deMax/thetaMax;

% and we assume this will only really be commanded if we are in trim (ie.
% we don't need to double it because of going from - max to + max)

thetaPGainLimitInput = 'SkywalkerX8_Longitudinal_Control/Sum/theta_e';
thetaPGainLimitOutput = 'SkywalkerX8_Longitudinal_Control/Gain Scheduled Controller Theta/de';

R1 = TuningGoal.Gain(thetaPGainLimitInput, thetaPGainLimitOutput, thetaGainLimit);
R1.Focus = [1E-02 1E02]; %Only focus on this frequency band

% Next we know that we need to limit our derivative in terms of bandwidth.
% We do this with the associated filter (ie. we constrain the gain of "N",
% the F in the PIDF controller). This needs to be limited to <13 rad/s, as
% this is the rate limit of the actuator. 

NGainLimit = 13;

NGainLimitInput = 'SkywalkerX8_Longitudinal_Control/Gain Scheduled Controller Theta/DF Controller Theta/Sum/de*_e';
NGainLimitOutput = 'SkywalkerX8_Longitudinal_Control/Gain Scheduled Controller Theta/DF Controller Theta/Product1/Nde*_e';

NGainLimitLoopOpening = {'SkywalkerX8_Longitudinal_Control/Gain Scheduled Controller Theta/DF Controller Theta/Sum/de*_e',...
                         'SkywalkerX8_Longitudinal_Control/Gain Scheduled Controller Theta/DF Controller Theta/Product1/Nde*_e'};

R2 = TuningGoal.Gain(NGainLimitInput, NGainLimitOutput, NGainLimit);
R2.Openings = NGainLimitLoopOpening;
R2.Focus = [1E-02 1E02]; %Only focus on this frequency band

% Next we know that our general response should have the standard gain
% margin of 6 dB, and a 40 deg phase margin should provide adequate damping, 
% while still ensuring as rapid a response as possible (and around a 10% OS 
% for a 2nd order system). So we assume this

gainMargin = 6; % >6 dB gain margin ideally
phaseMargin = 40; % 70 deg phase margin would provide adequate damping 1/sqrt(2) <= zeta < 1 - but we are fine with this being a bit lower in the interests of getting better response if possible
R3 = TuningGoal.Margins('SkywalkerX8_Longitudinal_Control/SkywalkerX8 Aircraft + Aerodynamics Longitudinal/theta', gainMargin, phaseMargin);
R3.Focus = [1E-02 1E02]; %Only focus on this frequency band

% Next we know that we want our crossover frequency to be at <= 3 rad/s, as
% per our linearization where we identified that our reduced order models
% are only accurate up until approximately 3 rad/s, so we try and cut off
% the plant prior to this so that our reduced order models are accurate and
% the inaccuracies are minimized by the rolloff. We also try and aim for a
% 40 dB/decade rolloff after the crossover frequency and allow a tolerance
% of half a decade (ie. 2.5 -> 3.5 rad/s crossover) at the crossover.

LS = frd([100 1 0.0001],[0.03 3.0 300]);  
R4 = TuningGoal.LoopShape('theta', LS, 0.5);

% Next we know that we want our altitude loop to be a simple first order
% lag. We also know that the desirable response time is what it would take
% for the system flying at its current airspeed (Va) at the maximum
% expected theta (assumed 60 degrees). As such, we want a variable tuning
% goal as a function of Va. We will slow this down by 5% in order to
% account for the need to first establish the desired theta (ie. Va at
% theta = 60 degrees would be our optimal solution assuming theta = 60
% could be achieved instantly). We will make this specification for rise
% time, which is approximately 2.2*tau (or tau = trise/2.2)

% We also know the theta loop needs to be adequately far enough away in
% bandwidth so that it has minimal impact on the altitude loop. As such, we
% specify a bandwidth separation in terms of a faster rise time. We also
% allow 5% overshoot because this is an internal loop so overshoot is not
% much of an issue for us.

altMax = 122*0.1; %Small signal design goal
tauScalar = 1.05;
riseTimeToTau = 1/2.2;
bandwidthSeparation = 20; %Small signal design goal
tauValues = zeros(nVa, nalpha); 
OSValues = zeros(nVa, nalpha);

for i = 1:nVa
    
    optimalTimeToAltitude = altMax/(SkywalkerX8.Control.Longitudinal.SchedulingVariables.VaArray(i)*sin(thetaMax));
    tauValues(i, :) = optimalTimeToAltitude*tauScalar*riseTimeToTau/bandwidthSeparation;
    OSValues(i, :) = 5;
    
end

FH = @(tau, OS) TuningGoal.StepTracking('theta_c', 'theta', tau, OS);

R5 = varyingGoal(FH, tauValues, OSValues);

thetac2DeGainLimit = deMax/thetaMax;

thetac2DeGainLimitInput = 'SkywalkerX8_Longitudinal_Control/Sum/theta_e';
thetac2DeGainLimitOutput = 'SkywalkerX8_Longitudinal_Control/Gain Scheduled Controller Theta/PI Controller Theta/POut';

thetac2DeGainLimitLoopOpening = {thetac2DeGainLimitInput,...
                                 thetac2DeGainLimitOutput};

R6 = TuningGoal.Gain(thetac2DeGainLimitInput, thetac2DeGainLimitOutput, thetac2DeGainLimit);
R6.Openings = thetac2DeGainLimitLoopOpening;
R6.Focus = [1E-02 1E02]; %Only focus on this frequency band

ST0.setBlockParam('PIDF Controller theta Kp 2D Lookup Table', Kp);
ST0.setBlockParam('PIDF Controller theta Ki 2D Lookup Table', Ki);
ST0.setBlockParam('PIDF Controller theta Kd 2D Lookup Table', Kd);
ST0.setBlockParam('PIDF Controller theta N 2D Lookup Table', N);

ST0.setBlockParam('PDF Controller theta 2DOF Kp 2D Lookup Table', Kp2DOF);
ST0.setBlockParam('PDF Controller theta 2DOF Kd 2D Lookup Table', Kd2DOF);
ST0.setBlockParam('PDF Controller theta 2DOF N 2D Lookup Table', N2DOF);

STTheta = systune(ST0, [R1, R3, R6], [R2, R4, R5], sysTuneOpts);

% Get values from ST and write them to our desired variables
% Note that TF here stands for transfer function and simply captures the
% values with the correct structure so that later they can be used for
% block subs.

tableValues = getBlockValue(STTheta);
SkywalkerX8.Control.Longitudinal.thetaController.KpThetaTF = tableValues.PIDF_Controller_theta_Kp_2D_Lookup_Table;
SkywalkerX8.Control.Longitudinal.thetaController.KiThetaTF = tableValues.PIDF_Controller_theta_Ki_2D_Lookup_Table;
SkywalkerX8.Control.Longitudinal.thetaController.KdThetaTF = tableValues.PIDF_Controller_theta_Kd_2D_Lookup_Table;
SkywalkerX8.Control.Longitudinal.thetaController.NThetaTF = tableValues.PIDF_Controller_theta_N_2D_Lookup_Table;

SkywalkerX8.Control.Longitudinal.thetaController.KpTheta2DOFTF = tableValues.PDF_Controller_theta_2DOF_Kp_2D_Lookup_Table;
SkywalkerX8.Control.Longitudinal.thetaController.KdTheta2DOFTF = tableValues.PDF_Controller_theta_2DOF_Kd_2D_Lookup_Table;
SkywalkerX8.Control.Longitudinal.thetaController.NTheta2DOFTF = tableValues.PDF_Controller_theta_2DOF_N_2D_Lookup_Table;

SkywalkerX8.Control.Longitudinal.thetaController.KpTheta = squeeze(tableValues.PIDF_Controller_theta_Kp_2D_Lookup_Table);
SkywalkerX8.Control.Longitudinal.thetaController.KiTheta = squeeze(tableValues.PIDF_Controller_theta_Ki_2D_Lookup_Table);
SkywalkerX8.Control.Longitudinal.thetaController.KdTheta = squeeze(tableValues.PIDF_Controller_theta_Kd_2D_Lookup_Table);
SkywalkerX8.Control.Longitudinal.thetaController.NTheta = squeeze(tableValues.PIDF_Controller_theta_N_2D_Lookup_Table);

SkywalkerX8.Control.Longitudinal.thetaController.KpTheta2DOF = squeeze(tableValues.PDF_Controller_theta_2DOF_Kp_2D_Lookup_Table);
SkywalkerX8.Control.Longitudinal.thetaController.KdTheta2DOF = squeeze(tableValues.PDF_Controller_theta_2DOF_Kd_2D_Lookup_Table);
SkywalkerX8.Control.Longitudinal.thetaController.NTheta2DOF = squeeze(tableValues.PDF_Controller_theta_2DOF_N_2D_Lookup_Table);

% Get scheduling parameters and write them to our desired variables
% Note thase these are based on our basis function.

TGS = getBlockParam(STTheta);
SkywalkerX8.Control.Longitudinal.thetaController.BasisFunction = TGS.PIDF_Controller_theta_Kp_2D_Lookup_Table.BasisFunctions;
SkywalkerX8.Control.Longitudinal.thetaController...
    .KpThetaParameterizedGains = getData(TGS.PIDF_Controller_theta_Kp_2D_Lookup_Table);
SkywalkerX8.Control.Longitudinal.thetaController...
    .KiThetaParameterizedGains = getData(TGS.PIDF_Controller_theta_Ki_2D_Lookup_Table);
SkywalkerX8.Control.Longitudinal.thetaController...
    .KdThetaParameterizedGains = getData(TGS.PIDF_Controller_theta_Kd_2D_Lookup_Table);
SkywalkerX8.Control.Longitudinal.thetaController...
    .NThetaParameterizedGains = getData(TGS.PIDF_Controller_theta_N_2D_Lookup_Table);

SkywalkerX8.Control.Longitudinal.thetaController...
    .KpTheta2DOFParameterizedGains = getData(TGS.PDF_Controller_theta_2DOF_Kp_2D_Lookup_Table);
SkywalkerX8.Control.Longitudinal.thetaController...
    .KdTheta2DOFParameterizedGains = getData(TGS.PDF_Controller_theta_2DOF_Kd_2D_Lookup_Table);
SkywalkerX8.Control.Longitudinal.thetaController...
    .NTheta2DOFParameterizedGains = getData(TGS.PDF_Controller_theta_2DOF_N_2D_Lookup_Table);

disp('Theta Control Loop Design Complete')
        
%% Alt Control Outer Loop %%

disp('Alt Control Loop Design Started')
    
%We get our initial values from siso tool with a midpoint controller (Va,
%alpha) = (Va(5), alpha(3)). We also know that our reduced model is
%essentially a scaled integration based on Va and our current theta. As
%such, we can simplify this controller drastically to a simple P controller
%and then constrain our gain to limit actuator saturation.

KpInit = 0.0168;
KiInit = 0.005;
KdInit = -0.0263;
NInit = 0.1880;

Kp = tunableSurface('Kp', KpInit, TuningGrid, ShapeFcn);
Ki = tunableSurface('Ki', KiInit, TuningGrid, ShapeFcn);
Kd = tunableSurface('Kd', KdInit, TuningGrid, ShapeFcn);
N = tunableSurface('N', NInit, TuningGrid, ShapeFcn);

tunedBlocks = {'PIDF Controller h_theta Kp 2D Lookup Table',...
               'PIDF Controller h_theta Ki 2D Lookup Table',...
               'PIDF Controller h_theta Kd 2D Lookup Table',...
               'PIDF Controller h_theta N 2D Lookup Table'};

% By ensuring that we keep our bandwidth lower than 2-3 x that of the theta
% controller we can trivialise our plant to De2Alt/De2Theta (ie. Theta to
% Alt) because we can assume theta_c to theta is unity gain. 

% We can get theta_c to alt as the sub model and then we can simply replace
% the theta controller with feedthrough an open up q and theta. This is
% better.

minRealTolerance = 1E-05;

%While getting the transfer function from theta_c to alt is certainly
%possible, it contains higher order dynamics we don't really care about. As
%such, we use the simplified linear model of Va/s when looking at theta to
%altitude and use this as the plant sub. The intention here is to make
%tuning easier. 

thetaCToAlt = minreal(tf(getIOTransfer(STTheta, 'theta_c', 'h')), minRealTolerance, false);

thetaCToAltEstimate = idss(zeros(1, 1, nVa, nalpha));

for i = 1:nVa
    
    thetaCToAltEstimate(:, :, i, :) =  tf(SkywalkerX8.Control.Longitudinal.SchedulingVariables.VaArray(i), [1 0]);
    
end

altPlantSubValue = [tf(0) tf(0);...
                    tf(0) thetaCToAltEstimate;...
                    tf(0) tf(0);...
                    tf(0) tf(0);...
                    tf(0) tf(0)];
                          
altPlantSubName = plantSubName;

altPlantSub = struct('Name', altPlantSubName, 'Value', altPlantSubValue);

controllerThetaSubValue = [tf(0),...
                           tf(1),...
                           tf(0),...
                           tf(0),...
                           tf(0)];
                       
controllerThetaSubName = [sys '/Gain Scheduled Controller Theta'];

controllerThetaSub = struct('Name', controllerThetaSubName, 'Value', controllerThetaSubValue);

switchSub = [tf(0) tf(0) tf(1)]; %This changes from previous because we now want our theta_alt controller to go through
algBreakSub = tf(1);

controllerVaDtName = [sys '/Gain Scheduled Controller Va_dt'];
controllerVaDtValue = [tf(0) tf(0)];

controllerVaDtSub = struct('Name', controllerVaDtName, 'Value', controllerVaDtValue);

controllerVaThetaName = [sys '/Gain Scheduled Controller Va_theta'];
controllerVaThetaValue = [tf(0) tf(0) tf(0)];

controllerVaThetaSub = struct('Name', controllerVaThetaName, 'Value', controllerVaThetaValue);

controllerSwitchName = [sys '/Switch'];
controllerSwitchValue = switchSub;

controllerSwitchSub = struct('Name', controllerSwitchName, 'Value', controllerSwitchValue);

altClampSwitchName = [sys '/Gain Scheduled Controller h_theta/PIDF Controller h_theta/Clamp Switch'];
altClampSwitchValue = [tf(0) tf(0) tf(1)];

altClampSwitchSub = struct('Name', altClampSwitchName, 'Value', altClampSwitchValue);

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
            controllerThetaSub;...
            controllerVaDtSub;...
            controllerVaThetaSub;...
            controllerSwitchSub;...
            altClampSwitchSub;...
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

POI = {'SkywalkerX8_Longitudinal_Control/h_c'
       'SkywalkerX8_Longitudinal_Control/h_e' 
       'SkywalkerX8_Longitudinal_Control/theta_c_h'
       'SkywalkerX8_Longitudinal_Control/de'
       'SkywalkerX8_Longitudinal_Control/Gain Scheduled Controller h_theta/PIDF Controller h_theta/Sum/theta_c*_e'
       'SkywalkerX8_Longitudinal_Control/Gain Scheduled Controller h_theta/PIDF Controller h_theta/Product1/theta_c*'
       'SkywalkerX8_Longitudinal_Control/Gain Scheduled Controller h_theta/PIDF Controller h_theta/POut'
       'SkywalkerX8_Longitudinal_Control/Gain Scheduled Controller h_theta/PIDF Controller h_theta/IOut/1'
       'SkywalkerX8_Longitudinal_Control/SkywalkerX8 Aircraft + Aerodynamics Longitudinal/Va' 
       'SkywalkerX8_Longitudinal_Control/SkywalkerX8 Aircraft + Aerodynamics Longitudinal/h' 
       'SkywalkerX8_Longitudinal_Control/SkywalkerX8 Aircraft + Aerodynamics Longitudinal/theta'
       'SkywalkerX8_Longitudinal_Control/SkywalkerX8 Aircraft + Aerodynamics Longitudinal/alpha'
       'SkywalkerX8_Longitudinal_Control/SkywalkerX8 Aircraft + Aerodynamics Longitudinal/q'};

ST0.addPoint(POI);

ST0.addOpening('SkywalkerX8_Longitudinal_Control/SkywalkerX8 Aircraft + Aerodynamics Longitudinal/Va');
ST0.addOpening('SkywalkerX8_Longitudinal_Control/SkywalkerX8 Aircraft + Aerodynamics Longitudinal/theta');
ST0.addOpening('SkywalkerX8_Longitudinal_Control/SkywalkerX8 Aircraft + Aerodynamics Longitudinal/alpha');
ST0.addOpening('SkywalkerX8_Longitudinal_Control/SkywalkerX8 Aircraft + Aerodynamics Longitudinal/q');

% We know we need to constrain what the maximum value can be for Kp due to
% actuator saturation.

% We'll make the assumption that theta will not exceed 60 degrees, and we
% know our maximum altitude is 122 m by law - so let's assume 10% of that
% will be the largest seen error signal (small signal). We also take this 
% opportunity to set our saturation limits.

thetaMax = 60*pi/180;
altMax = 122*0.1;

SkywalkerX8.Control.Longitudinal.altController.upperSaturationThetaC = thetaMax;
SkywalkerX8.Control.Longitudinal.altController.lowerSaturationThetaC = -thetaMax;

% so we can generate a
% limit on gain from these 2 values:

altGainLimit = thetaMax/altMax;

% and we assume this will only really be commanded if we are in trim

altPGainLimitInput = 'SkywalkerX8_Longitudinal_Control/Sum2/h_e';
altPGainLimitOutput = 'SkywalkerX8_Longitudinal_Control/Gain Scheduled Controller h_theta/PIDF Controller h_theta/POut';

R1 = TuningGoal.Gain(altPGainLimitInput, altPGainLimitOutput, altGainLimit);
R1.Openings = {altPGainLimitInput,...
               altPGainLimitOutput};
R1.Focus = [1E-02 1E02];

% Next we know that our general response should have the standard gain
% margin of 6 dB, and a 60 deg phase margin forces a response that does not
% have a resonance peak, but we accept slightly lower in the interest of 
% better performance,
% while still ensuring as rapid a response as possible (and around a 5% OS 
% for a 2nd order system). So we assume this

gainMargin = 6; % >6 dB gain margin ideally
phaseMargin = 45; % 45 deg phase margin would provide adequate damping
R2 = TuningGoal.Margins('SkywalkerX8_Longitudinal_Control/SkywalkerX8 Aircraft + Aerodynamics Longitudinal/h', gainMargin, phaseMargin);
R2.Focus = [1E-02 1E02];

% Next we know that we want our crossover frequency to be at 1.0 rad/s, as
% from our previous design we know our cutoff frequency was at
% approximately 10 rad/s, so we can reduce the inner-loop to a unity gain if
% we band limit this outer loop to 1/10th the cutoff frequency of the inner
% loop.

LS = frd([1000000 1 0.0001],[0.01 1.0 100]);  
R3 = TuningGoal.LoopShape('h', LS, 0.5);

% Next we know that we want our altitude loop to be a simple first order
% lag. We also know that the desirable response time is what it would take
% for the system flying at its current airspeed (Va) at the maximum
% expected theta (assumed 60 degrees). As such, we want a variable tuning
% goal as a function of Va. We will slow this down by 5% in order to
% account for the need to first establish the desired theta (ie. Va at
% theta = 60 degrees would be our optimal solution assuming theta = 60
% could be achieved instantly). We will make this specification for rise
% time, which is approximately 2.2*tau (or tau = trise/2.2)

tauScalar = 1.05;
riseTimeToTau = 1/2.2;
bandwidthSeparation = 2;
tauValues = zeros(nVa, nalpha); 
OSValues = zeros(nVa, nalpha);

for i = 1:nVa
    
    optimalTimeToAltitude = altMax/(SkywalkerX8.Control.Longitudinal.SchedulingVariables.VaArray(i)*sin(thetaMax));
    tauValues(i, :) = optimalTimeToAltitude*tauScalar*riseTimeToTau/bandwidthSeparation;
    OSValues(i, :) = 0; %0% overshoot is ideal if possible
    
end

FH = @(tau, OS) TuningGoal.StepTracking('h_c', 'h', tau, OS);

R4 = varyingGoal(FH, tauValues, OSValues);

altFFControllerPGainLimitInput = 'SkywalkerX8_Longitudinal_Control/h_c';
altFFControllerPGainLimitOutput = 'SkywalkerX8_Longitudinal_Control/Gain Scheduled Controller h_theta/theta_c_h';

R5 = TuningGoal.Gain(altFFControllerPGainLimitInput, altFFControllerPGainLimitOutput, altGainLimit);
R5.Openings = 'SkywalkerX8_Longitudinal_Control/SkywalkerX8 Aircraft + Aerodynamics Longitudinal/h';
R5.Focus = [1E-02 1E02];

% Next we know that we need to limit our derivative in terms of bandwidth.
% We do this with the associated filter (ie. we constrain the gain of "N",
% the F in the PIDF controller). This needs to be limited to approximately
% 6.5 rad/s (half of the theta control loop filter) to not cause issues with the inner loop.

NGainLimit = 6.5;

NGainLimitInput = 'SkywalkerX8_Longitudinal_Control/Gain Scheduled Controller h_theta/PIDF Controller h_theta/Sum/theta_c*_e';
NGainLimitOutput = 'SkywalkerX8_Longitudinal_Control/Gain Scheduled Controller h_theta/PIDF Controller h_theta/Product1/theta_c*';

NGainLimitLoopOpening = {'SkywalkerX8_Longitudinal_Control/Gain Scheduled Controller h_theta/PIDF Controller h_theta/Sum/theta_c*_e',...
                         'SkywalkerX8_Longitudinal_Control/Gain Scheduled Controller h_theta/PIDF Controller h_theta/Product1/theta_c*'};

R6 = TuningGoal.Gain(NGainLimitInput, NGainLimitOutput, NGainLimit);
R6.Openings = NGainLimitLoopOpening;
R6.Focus = [1E-02 1E02]; %Only focus on this frequency band

ST0.setBlockParam('PIDF Controller h_theta Kp 2D Lookup Table', Kp);
ST0.setBlockParam('PIDF Controller h_theta Ki 2D Lookup Table', Ki);
ST0.setBlockParam('PIDF Controller h_theta Kd 2D Lookup Table', Kd);
ST0.setBlockParam('PIDF Controller h_theta N 2D Lookup Table', N);

STAlt = systune(ST0, [R1, R2, R5], [R3, R4, R6], sysTuneOpts);

% Get values from ST and write them to our desired variables
% Note that TF here stands for transfer function and simply captures the
% values with the correct structure so that later they can be used for
% block subs.

tableValues = getBlockValue(STAlt);

SkywalkerX8.Control.Longitudinal.altController.KpAltTF = tableValues.PIDF_Controller_h_theta_Kp_2D_Lookup_Table;
SkywalkerX8.Control.Longitudinal.altController.KiAltTF = tableValues.PIDF_Controller_h_theta_Ki_2D_Lookup_Table;
SkywalkerX8.Control.Longitudinal.altController.KdAltTF = tableValues.PIDF_Controller_h_theta_Kd_2D_Lookup_Table;
SkywalkerX8.Control.Longitudinal.altController.NAltTF = tableValues.PIDF_Controller_h_theta_N_2D_Lookup_Table;

SkywalkerX8.Control.Longitudinal.altController.KpAlt = squeeze(tableValues.PIDF_Controller_h_theta_Kp_2D_Lookup_Table);
SkywalkerX8.Control.Longitudinal.altController.KiAlt = squeeze(tableValues.PIDF_Controller_h_theta_Ki_2D_Lookup_Table);
SkywalkerX8.Control.Longitudinal.altController.KdAlt = squeeze(tableValues.PIDF_Controller_h_theta_Kd_2D_Lookup_Table);
SkywalkerX8.Control.Longitudinal.altController.NAlt = squeeze(tableValues.PIDF_Controller_h_theta_N_2D_Lookup_Table);

% Get scheduling parameters and write them to our desired variables
% Note thase these are based on our basis function.

TGS = getBlockParam(STAlt);
SkywalkerX8.Control.Longitudinal.altController.BasisFunction = TGS.PIDF_Controller_h_theta_Kp_2D_Lookup_Table.BasisFunctions;
SkywalkerX8.Control.Longitudinal.altController.KpAltParameterizedGains = getData(TGS.PIDF_Controller_h_theta_Kp_2D_Lookup_Table);
SkywalkerX8.Control.Longitudinal.altController.KiAltParameterizedGains = getData(TGS.PIDF_Controller_h_theta_Ki_2D_Lookup_Table);
SkywalkerX8.Control.Longitudinal.altController.KdAltParameterizedGains = getData(TGS.PIDF_Controller_h_theta_Kd_2D_Lookup_Table);
SkywalkerX8.Control.Longitudinal.altController.NAltParameterizedGains = getData(TGS.PIDF_Controller_h_theta_N_2D_Lookup_Table);

% Next we define our tracking constant (not used for controller design, but
% provided by the designer to assist with bumpless transfer in
% implementation). 

% This Is defined relative to our Ki gain via a scalar. As such, it should
% be x times faster than this integrator loop. 10 seems like a reasonable
% value.

SkywalkerX8.Control.Longitudinal.altController.KtScalar = 10;

disp('Alt Control Loop Design Complete')

%% Va Control Design %%

% Va is controlled either by using propeller speed (dt) or theta. This
% script deals with the latter case, because the scheduling variable is
% the same as the theta/altitude controller (both Va and alpha). This is
% because if the system has a strong dependency on theta, it will also
% depend on angle of attack and as such we will need to incorporate these
% effects into the gain scheduling. This is clear from the bode plots of
% the system and how the dynamics vary substantially with varying alpha.

% Va Theta Control Design %

disp('Va Theta Control Loop Design Started')
    
%We get our initial values from siso tool with a midpoint controller (Va,
%alpha) = (Va(5), alpha(3)). 

KpInit = 0.0106;
KiInit = 0.0247;
KdInit = 0.0031;
NInit = 1.5205;

Kp = tunableSurface('Kp', KpInit, TuningGrid, ShapeFcn);
Ki = tunableSurface('Ki', KiInit, TuningGrid, ShapeFcn);
Kd = tunableSurface('Kd', KdInit, TuningGrid, ShapeFcn);
N = tunableSurface('N', NInit, TuningGrid, ShapeFcn);

tunedBlocks = {'PIDF Controller Va_theta Kp 2D Lookup Table',...
               'PIDF Controller Va_theta Ki 2D Lookup Table',...
               'PIDF Controller Va_theta Kd 2D Lookup Table',...
               'PIDF Controller Va_theta N 2D Lookup Table'};

% We can get theta_c to Va as the sub model and then we can simply replace
% the theta controller with feedthrough and open up q and theta. 

minRealTolerance = 1E-05;

thetaCToVa = minreal(tf(getIOTransfer(STTheta, 'theta_c', 'Va')), minRealTolerance, false);

VaThetaPlantSubValue = [tf(0) thetaCToVa;...
                        tf(0) tf(0);...
                        tf(0) tf(0);...
                        tf(0) tf(0);...
                        tf(0) tf(0)];
                          
VaThetaPlantSubName = plantSubName;

VaThetaPlantSub = struct('Name', VaThetaPlantSubName, 'Value', VaThetaPlantSubValue);

controllerThetaSubValue = [tf(1),...
                           tf(0),...
                           tf(0),...
                           tf(0),...
                           tf(0)];
                       
controllerThetaSubName = [sys '/Gain Scheduled Controller Theta'];

controllerThetaSub = struct('Name', controllerThetaSubName, 'Value', controllerThetaSubValue);

switchSub = [tf(1) tf(0) tf(0)]; %This changes from previous because we now want our Va_theta controller to go through
algBreakSub = tf(1);

controllerVaDtName = [sys '/Gain Scheduled Controller Va_dt'];
controllerVaDtValue = [tf(0) tf(0)];

controllerVaDtSub = struct('Name', controllerVaDtName, 'Value', controllerVaDtValue);

controllerAltName = [sys '/Gain Scheduled Controller h_theta'];
controllerAltValue = [tf(0) tf(0) tf(0)];

controllerAltSub = struct('Name', controllerAltName, 'Value', controllerAltValue);

controllerSwitchName = [sys '/Switch'];
controllerSwitchValue = switchSub;

controllerSwitchSub = struct('Name', controllerSwitchName, 'Value', controllerSwitchValue);

VaThetaClampSwitchName = [sys '/Gain Scheduled Controller Va_theta/PIDF Controller Va_theta/Clamp Switch'];
VaThetaClampSwitchValue = [tf(0) tf(0) tf(1)];

VaThetaClampSwitchSub = struct('Name', VaThetaClampSwitchName, 'Value', VaThetaClampSwitchValue);

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
    
BlockSubs = [VaThetaPlantSub;...
            controllerThetaSub;...
            controllerVaDtSub;...
            controllerAltSub;...
            controllerSwitchSub;...
            VaThetaClampSwitchSub;...
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
       'SkywalkerX8_Longitudinal_Control/theta_c_Va'
       'SkywalkerX8_Longitudinal_Control/de'
       'SkywalkerX8_Longitudinal_Control/SkywalkerX8 Aircraft + Aerodynamics Longitudinal/Va' 
       'SkywalkerX8_Longitudinal_Control/SkywalkerX8 Aircraft + Aerodynamics Longitudinal/h' 
       'SkywalkerX8_Longitudinal_Control/SkywalkerX8 Aircraft + Aerodynamics Longitudinal/theta'
       'SkywalkerX8_Longitudinal_Control/SkywalkerX8 Aircraft + Aerodynamics Longitudinal/alpha'
       'SkywalkerX8_Longitudinal_Control/SkywalkerX8 Aircraft + Aerodynamics Longitudinal/q'};

ST0.addPoint(POI);

ST0.addOpening('SkywalkerX8_Longitudinal_Control/SkywalkerX8 Aircraft + Aerodynamics Longitudinal/h');
ST0.addOpening('SkywalkerX8_Longitudinal_Control/SkywalkerX8 Aircraft + Aerodynamics Longitudinal/theta');
ST0.addOpening('SkywalkerX8_Longitudinal_Control/SkywalkerX8 Aircraft + Aerodynamics Longitudinal/alpha');
ST0.addOpening('SkywalkerX8_Longitudinal_Control/SkywalkerX8 Aircraft + Aerodynamics Longitudinal/q');

% We know we need to constrain what the maximum value can be for Kp due to
% actuator saturation.

% We'll make the assumption that theta will not exceed 60 degrees, and we
% know our maximum velocity change - so let's assume 1/2 of that
% will be the largest seen error signal. We also take this opportunity to
% set our saturation limits.

thetaMax = 60*pi/180;
VaChangeMax = (SkywalkerX8.Control.Longitudinal...
               .SchedulingVariables.VaArray(end)...
              - SkywalkerX8.Control.Longitudinal...
                .SchedulingVariables.VaArray(1))*2/3;

SkywalkerX8.Control.Longitudinal...
    .VaThetaController.upperSaturationThetaC = thetaMax;
SkywalkerX8.Control.Longitudinal...
    .VaThetaController.lowerSaturationThetaC = -thetaMax;

% so we can generate a
% limit on gain from these 2 values:

VaThetaGainLimit = thetaMax/VaChangeMax;

% and we assume this will only really be commanded if we are in trim

VaThetaPGainLimitInput = 'SkywalkerX8_Longitudinal_Control/Sum3/Va_e';
VaThetaPGainLimitOutput = 'SkywalkerX8_Longitudinal_Control/Gain Scheduled Controller Va_theta/theta_c_Va';

R1 = TuningGoal.Gain(VaThetaPGainLimitInput, VaThetaPGainLimitOutput, VaThetaGainLimit);
R1.Focus = [1E-02 1E02];

% Next we know that our general response should have the standard gain
% margin of 6 dB, and a 70 deg phase margin forces a response that does not
% have a resonance peak, while still ensuring as rapid a response as
% possible (and around a 5% OS for a 2nd order system). So we assume this

gainMargin = 6; % >6 dB gain margin ideally
phaseMargin = 40; % 40 degree phase margin is fine for this controller given that it's only going to be conditionally active
R2 = TuningGoal.Margins('SkywalkerX8_Longitudinal_Control/SkywalkerX8 Aircraft + Aerodynamics Longitudinal/Va', gainMargin, phaseMargin);
R2.Focus = [1E-02 1E02];

% Next we know that we want our crossover frequency to be at approximately 0.75 rad/s, as
% we know our second order approximations are only true up until around 3
% rad/s and there is a large resonance peak at approximately 1 rad/s, So we 
% try and band limit this so that our models are correct and we avoid the
% resonance peak.

LS = frd([100 1 0.0001],[0.005 0.5 50]);  
R3 = TuningGoal.LoopShape('Va', LS, 0.2);

% Next we know that we want our Va loop to have a rise time that
% corresponds to the crossover frequency above, but also that overshoot
% is allowable. As such, we specify this as a requirement.

tau = 4/2.2; 
OS = 4;

R4 = TuningGoal.StepTracking('Va_c', 'Va', tau, OS);

ST0.setBlockParam('PIDF Controller Va_theta Kp 2D Lookup Table', Kp);
ST0.setBlockParam('PIDF Controller Va_theta Ki 2D Lookup Table', Ki);
ST0.setBlockParam('PIDF Controller Va_theta Kd 2D Lookup Table', Kd);
ST0.setBlockParam('PIDF Controller Va_theta N 2D Lookup Table', N);

STVaTheta = systune(ST0, [R1, R2], [R3, R4], sysTuneOpts);

% Get values from ST and write them to our desired variables
% Note that TF here stands for transfer function and simply captures the
% values with the correct structure so that later they can be used for
% block subs.

tableValues = getBlockValue(STVaTheta);

SkywalkerX8.Control.Longitudinal.VaThetaController.KpVaThetaTF = tableValues.PIDF_Controller_Va_theta_Kp_2D_Lookup_Table;
SkywalkerX8.Control.Longitudinal.VaThetaController.KiVaThetaTF = tableValues.PIDF_Controller_Va_theta_Ki_2D_Lookup_Table;
SkywalkerX8.Control.Longitudinal.VaThetaController.KdVaThetaTF = tableValues.PIDF_Controller_Va_theta_Kd_2D_Lookup_Table;
SkywalkerX8.Control.Longitudinal.VaThetaController.NVaThetaTF = tableValues.PIDF_Controller_Va_theta_N_2D_Lookup_Table;

SkywalkerX8.Control.Longitudinal.VaThetaController.KpVaTheta = squeeze(tableValues.PIDF_Controller_Va_theta_Kp_2D_Lookup_Table);
SkywalkerX8.Control.Longitudinal.VaThetaController.KiVaTheta = squeeze(tableValues.PIDF_Controller_Va_theta_Ki_2D_Lookup_Table);
SkywalkerX8.Control.Longitudinal.VaThetaController.KdVaTheta = squeeze(tableValues.PIDF_Controller_Va_theta_Kd_2D_Lookup_Table);
SkywalkerX8.Control.Longitudinal.VaThetaController.NVaTheta = squeeze(tableValues.PIDF_Controller_Va_theta_N_2D_Lookup_Table);

% Get scheduling parameters and write them to our desired variables
% Note thase these are based on our basis function.

TGS = getBlockParam(STVaTheta);
SkywalkerX8.Control.Longitudinal...
    .VaThetaController.BasisFunction = TGS.PIDF_Controller_Va_theta_Kp_2D_Lookup_Table.BasisFunctions;
SkywalkerX8.Control.Longitudinal...
    .VaThetaController.KpVaThetaParameterizedGains = getData(TGS.PIDF_Controller_Va_theta_Kp_2D_Lookup_Table);
SkywalkerX8.Control.Longitudinal...
    .VaThetaController.KiVaThetaParameterizedGains = getData(TGS.PIDF_Controller_Va_theta_Ki_2D_Lookup_Table);
SkywalkerX8.Control.Longitudinal...
    .VaThetaController.KdVaThetaParameterizedGains = getData(TGS.PIDF_Controller_Va_theta_Kd_2D_Lookup_Table);
SkywalkerX8.Control.Longitudinal...
    .VaThetaController.NVaThetaParameterizedGains = getData(TGS.PIDF_Controller_Va_theta_N_2D_Lookup_Table);

% Next we define our tracking constant (not used for controller design, but
% provided by the designer to assist with bumpless transfer in
% implementation). 

% This Is defined relative to our Ki gain via a scalar. As such, it should
% be x times faster than this integrator loop. 10 seems like a reasonable
% value.

SkywalkerX8.Control.Longitudinal.VaThetaController.KtScalar = 10;

disp('Va Theta Control Loop Design Complete')