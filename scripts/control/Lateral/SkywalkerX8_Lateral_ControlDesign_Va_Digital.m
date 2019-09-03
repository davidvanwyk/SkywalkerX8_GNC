%% p, Phi and Chi Control Design (da)%%

% p, Phi and Chi are controlled by actuating the ailerons. Given that these
% do not depend on alpha and we assume a small beta (we have no control
% over beta for this airframe) so the main impact on the dynamics are
% assumed to be based on Va.

%% System Setup %%

sys = 'SkywalkerX8_Lateral_Control_Digital';

LinOpt = linearizeOptions('SampleTime', 0, 'RateConversionMethod', 'tustin');  % seek continuous-time model
sysTuneOpts = systuneOptions('MaxIter', 500, 'RandomStart', 5);

%% System Setup %%

% We know we have a gain scheduled controller as a function of Va. As such 
% we create our tuning grids and parameterized gain surfaces
% as a function of the Va array that were used in the
% linearization process.

Va = SkywalkerX8.Control.Lateral.SchedulingVariables.VaArray';

VaTuningGrid = struct('Va', Va);
VaShapeFcn = @(Va)[Va, Va^2, Va^3];

nVa = length(SkywalkerX8.Control.Lateral.SchedulingVariables.VaArray);

% We will also need to block substitute our plant model to our linearized
% version to do controller tuning. This will be true for all controller
% designs so is defined once in the beginning. 

SkywalkerX8.Control.Lateral.LinearizedPlantModels.LinearizedPlantBlockSub =...
    [tf(0) tf(0) tf(0);...
    tf(0) tf(0) SkywalkerX8.Control.Lateral.LinearizedPlantModels.Da2ChiReducedModels;...
    tf(0) tf(0) SkywalkerX8.Control.Lateral.LinearizedPlantModels.Da2PhiReducedModels;...
    tf(0) tf(0) SkywalkerX8.Control.Lateral.LinearizedPlantModels.Da2pReducedModels];
                                                                             

plantSubValue = SkywalkerX8.Control.Lateral.LinearizedPlantModels.LinearizedPlantBlockSub;
plantSubName = [sys '/SkywalkerX8 Aircraft + Aerodynamics Lateral'];

plantSub = struct('Name', plantSubName, 'Value', plantSubValue);

%% Reset the variables into which our gains will be written

SkywalkerX8.Control.Lateral.PhiController.Digital.SampleTime = 1/100;
SkywalkerX8.Control.Lateral.ChiController.Digital.SampleTime = 1/100;

SkywalkerX8.Control.Lateral.PhiController.Digital.KpPhi = zeros(nVa, 1);
SkywalkerX8.Control.Lateral.PhiController.Digital.KiPhi = zeros(nVa, 1);
SkywalkerX8.Control.Lateral.PhiController.Digital.KdPhi = zeros(nVa, 1);
SkywalkerX8.Control.Lateral.PhiController.Digital.NPhi = zeros(nVa, 1);

SkywalkerX8.Control.Lateral.PhiController.Digital.KpPhi2DOF = zeros(nVa, 1);
SkywalkerX8.Control.Lateral.PhiController.Digital.KdPhi2DOF = zeros(nVa, 1);
SkywalkerX8.Control.Lateral.PhiController.Digital.NPhi2DOF = zeros(nVa, 1);

SkywalkerX8.Control.Lateral.ChiController.Digital.KpChi = zeros(nVa, 1);
SkywalkerX8.Control.Lateral.ChiController.Digital.KiChi = zeros(nVa, 1);
SkywalkerX8.Control.Lateral.ChiController.Digital.KdChi = zeros(nVa, 1);
SkywalkerX8.Control.Lateral.ChiController.Digital.NChi = zeros(nVa, 1);

SkywalkerX8.Control.Lateral.ChiController.Digital.KpChi2DOF = zeros(nVa, 1);
SkywalkerX8.Control.Lateral.ChiController.Digital.KdChi2DOF = zeros(nVa, 1);
SkywalkerX8.Control.Lateral.ChiController.Digital.NChi2DOF = zeros(nVa, 1);

SkywalkerX8.Control.Lateral.PhiController.Digital.upperSaturationDa = Inf;
SkywalkerX8.Control.Lateral.PhiController.Digital.lowerSaturationDa = -Inf;

SkywalkerX8.Control.Lateral.ChiController.Digital.upperSaturationPhiC = Inf;
SkywalkerX8.Control.Lateral.ChiController.Digital.lowerSaturationPhiC = -Inf;

%% Phi Da Control Design %%

disp('Starting Phi Control Loop Design...')

KpInit = 0.2861;
KiInit = 3.5357;
KdInit = -0.6717;
NInit = 2.822;

Kp2DOFInit = -1.0545;
Kd2DOFInit = 1.4099;
N2DOFInit = 0.9608;

Kp = tunableSurface('Kp', KpInit, VaTuningGrid, VaShapeFcn);
Ki = tunableSurface('Ki', KiInit, VaTuningGrid, VaShapeFcn);
Kd = tunableSurface('Kd', KdInit, VaTuningGrid, VaShapeFcn);
N = tunableSurface('N', NInit, VaTuningGrid, VaShapeFcn);

Kp2DOF = tunableSurface('Kp2DOF', Kp2DOFInit, VaTuningGrid, VaShapeFcn);
Kd2DOF = tunableSurface('Kd2DOF', Kd2DOFInit, VaTuningGrid, VaShapeFcn);
N2DOF = tunableSurface('N2DOF', N2DOFInit, VaTuningGrid, VaShapeFcn);

tunedBlocks = {'PIDF Controller Phi Kp 2D Lookup Table',...
               'PIDF Controller Phi Ki 2D Lookup Table',...
               'PIDF Controller Phi Kd 2D Lookup Table',...
               'PIDF Controller Phi N 2D Lookup Table',...
               'PDF Controller Phi 2DOF Kp 2D Lookup Table',...
               'PDF Controller Phi 2DOF Kd 2D Lookup Table',...
               'PDF Controller Phi 2DOF N 2D Lookup Table'};

minRealTolerance = 1E-05;

controllerChiPhiSubValue = [tf(0),...
                           tf(0)];
                       
controllerChiPhiSubName = [sys '/Gain Scheduled Controller Chi'];

controllerChiPhiSub = struct('Name', controllerChiPhiSubName, 'Value', controllerChiPhiSubValue);
    
BlockSubs = [plantSub;...
             controllerChiPhiSub];

% Create slTuner interface for tuning of tunedBlocks within the context of
% sys, after substituting out the blocks defined in BlockSubs, with the
% options given in LinOpt.

ST0 = slTuner(sys, tunedBlocks, BlockSubs, LinOpt);

ST0.Ts = 0; % We want continuous-time linearizations 

% Add all relevant points of interest (POI) that we will examine in the
% model.

POI = {'SkywalkerX8_Lateral_Control_Digital/Phi_c'
       'SkywalkerX8_Lateral_Control_Digital/Phi_e' 
       'SkywalkerX8_Lateral_Control_Digital/da'
       'SkywalkerX8_Lateral_Control_Digital/Gain Scheduled Controller Phi/DF Controller Phi/Sum/da*_e'
       'SkywalkerX8_Lateral_Control_Digital/Gain Scheduled Controller Phi/DF Controller Phi/Product1/Nda*_e'
       'SkywalkerX8_Lateral_Control_Digital/Gain Scheduled Controller Phi/DF Controller Phi/Integrator/da*'
       'SkywalkerX8_Lateral_Control_Digital/SkywalkerX8 Aircraft + Aerodynamics Lateral/Va' 
       'SkywalkerX8_Lateral_Control_Digital/SkywalkerX8 Aircraft + Aerodynamics Lateral/p' 
       'SkywalkerX8_Lateral_Control_Digital/SkywalkerX8 Aircraft + Aerodynamics Lateral/Phi'
       'SkywalkerX8_Lateral_Control_Digital/SkywalkerX8 Aircraft + Aerodynamics Lateral/Chi'};

ST0.addPoint(POI);

ST0.addOpening('SkywalkerX8_Lateral_Control_Digital/SkywalkerX8 Aircraft + Aerodynamics Lateral/Phi_c');
ST0.addOpening('SkywalkerX8_Lateral_Control_Digital/SkywalkerX8 Aircraft + Aerodynamics Lateral/Va');
ST0.addOpening('SkywalkerX8_Lateral_Control_Digital/SkywalkerX8 Aircraft + Aerodynamics Lateral/Chi');

% We know we need to constrain what the maximum value can be for Kp due to
% actuator saturation.

% We know that da cannot exceed 30 degrees. We also know what our expected maximum
% and minimum phi are, so we use these to define our gain limit as being 
% approximately 1/2 of the absolute max difference in phi. We also take this
% chance to set saturation limits.

daMax = 2*15*pi/180; %x2 because split over 2 elevons
phiMax = 30*pi/180*0.5;
          
SkywalkerX8.Control.Lateral.PhiController.Digital.upperSaturationDa = daMax;
SkywalkerX8.Control.Lateral.PhiController.Digital.lowerSaturationDa = -daMax;

% so we can generate a
% limit on gain from these 2 values:

PhiDaGainLimit = daMax/phiMax;

% and we assume this will only really be commanded if we are in trim

PhiDaPGainLimitInput = 'SkywalkerX8_Lateral_Control_Digital/Sum/Phi_e';
PhiDaPGainLimitOutput = 'SkywalkerX8_Lateral_Control_Digital/Gain Scheduled Controller Phi/da';

R1 = TuningGoal.Gain(PhiDaPGainLimitInput, PhiDaPGainLimitOutput, PhiDaGainLimit);
R1.Focus = [1E-02 1E02];

% Next we know that we need to limit our derivative in terms of bandwidth.
% We do this with the associated filter (ie. we constrain the gain of "N",
% the F in the PIDF controller). This needs to be limited to approximately
% 13 rad/s to not cause issues with the actuator.

NGainLimit = 13;

NGainLimitInput = 'SkywalkerX8_Lateral_Control_Digital/Gain Scheduled Controller Phi/DF Controller Phi/Sum/da*_e';
NGainLimitOutput = 'SkywalkerX8_Lateral_Control_Digital/Gain Scheduled Controller Phi/DF Controller Phi/Product1/Nda*_e';

NGainLimitLoopOpening = {'SkywalkerX8_Lateral_Control_Digital/Gain Scheduled Controller Phi/DF Controller Phi/Sum/da*_e',...
                         'SkywalkerX8_Lateral_Control_Digital/Gain Scheduled Controller Phi/DF Controller Phi/Product1/Nda*_e'};

R2 = TuningGoal.Gain(NGainLimitInput, NGainLimitOutput, NGainLimit);
R2.Openings = NGainLimitLoopOpening;
R2.Focus = [1E-02 1E02]; %Only focus on this frequency band

% Next we know that our general response should have the standard gain
% margin of 6 dB, and a 70 deg phase margin forces a response that does not
% have a resonance peak, while still ensuring as rapid a response as
% possible (and around a 5% OS for a 2nd order system). So we assume this

gainMargin = 6; % >6 dB gain margin ideally
phaseMargin = 30; % 30 deg phase margin should provide adequate damping
R3 = TuningGoal.Margins('SkywalkerX8_Lateral_Control_Digital/SkywalkerX8 Aircraft + Aerodynamics Lateral/Phi', gainMargin, phaseMargin);
R3.Focus = [1E-02 1E02];

% Next we know that our theta controller was capable of having a crossover
% frequency at approximately 2 rad/s. We also know that da -> l
% aerodynamically has about half the gain of de -> m. This, as well as the
% fact that Jyy is only 13.85% of Jxx means we expect our roll to be
% substantially slower than our pitch. We will aim for approximately 25-30%
% the speed but this might need to be adjusted.

LS = frd([1000 1 0.001],[0.08 8 800]);  
R4 = TuningGoal.LoopShape('Phi', LS, 0.5);

% Next we simply add a goal for our response in the time domain. We'd like
% this to be as fast as possible, given the previous constraints on
% crossover frequency and margins. We know that for a coordinated turn,
% dPsi/dt = g/Va*tan(phi). As such, we can estimate an optimal psi_dot
% assuming a constant bank angle (let's assume half the maximum) and use
% this to determine an expected rise time (making use of the previous
% expected maximum Chi command as the reference command). We slow this
% requirement down slightly to account for having to actually get to the
% bank angle from 0 roll - and assume this to mean we'll be 20% slower than
% optimal.

% We use the above, and take into account needing our inner phi loop to be
% 2-3x faster than the outer loop to reduce the requirement for this inner
% loop.

chiMax = 90*pi/180;

g = 9.81;
tauScalar = 1;
riseTimeToTau = 1/2.2;
bandwidthSeparation = 50;
tauValues = zeros(nVa, 1); 
OSValues = zeros(nVa, 1);

for i = 1:nVa
    
    psiDotMax = (g/SkywalkerX8.Control.Lateral.SchedulingVariables.VaArray(i))*tan(phiMax);
    optimalRiseTime = chiMax/psiDotMax;
    tauValues(i) = optimalRiseTime*tauScalar*riseTimeToTau/bandwidthSeparation;
    OSValues(i) = 5; %5% overshoot is fine given that this is an inner loop
    
end

FH = @(tau, OS) TuningGoal.StepTracking('Phi_c', 'Phi', tau, OS);

R5 = varyingGoal(FH, tauValues, OSValues);

ST0.setBlockParam('PIDF Controller Phi Kp 2D Lookup Table', Kp);
ST0.setBlockParam('PIDF Controller Phi Ki 2D Lookup Table', Ki);
ST0.setBlockParam('PIDF Controller Phi Kd 2D Lookup Table', Kd);
ST0.setBlockParam('PIDF Controller Phi N 2D Lookup Table', N);

ST0.setBlockParam('PDF Controller Phi 2DOF Kp 2D Lookup Table', Kp2DOF);
ST0.setBlockParam('PDF Controller Phi 2DOF Kd 2D Lookup Table', Kd2DOF);
ST0.setBlockParam('PDF Controller Phi 2DOF N 2D Lookup Table', N2DOF);

STPhi = systune(ST0, [R1, R3], [R2, R4, R5], sysTuneOpts);

tableValues = getBlockValue(STPhi);

SkywalkerX8.Control.Lateral.PhiController.Digital.KpPhiTF = tableValues.PIDF_Controller_Phi_Kp_2D_Lookup_Table;
SkywalkerX8.Control.Lateral.PhiController.Digital.KiPhiTF = tableValues.PIDF_Controller_Phi_Ki_2D_Lookup_Table;
SkywalkerX8.Control.Lateral.PhiController.Digital.KdPhiTF = tableValues.PIDF_Controller_Phi_Kd_2D_Lookup_Table;
SkywalkerX8.Control.Lateral.PhiController.Digital.NPhiTF = tableValues.PIDF_Controller_Phi_N_2D_Lookup_Table;

SkywalkerX8.Control.Lateral.PhiController.Digital.KpPhi2DOFTF = tableValues.PDF_Controller_Phi_2DOF_Kp_2D_Lookup_Table;
SkywalkerX8.Control.Lateral.PhiController.Digital.KdPhi2DOFTF = tableValues.PDF_Controller_Phi_2DOF_Kd_2D_Lookup_Table;
SkywalkerX8.Control.Lateral.PhiController.Digital.NPhi2DOFTF = tableValues.PDF_Controller_Phi_2DOF_N_2D_Lookup_Table;

SkywalkerX8.Control.Lateral.PhiController.Digital.KpPhi = squeeze(tableValues.PIDF_Controller_Phi_Kp_2D_Lookup_Table);
SkywalkerX8.Control.Lateral.PhiController.Digital.KiPhi = squeeze(tableValues.PIDF_Controller_Phi_Ki_2D_Lookup_Table);
SkywalkerX8.Control.Lateral.PhiController.Digital.KdPhi = squeeze(tableValues.PIDF_Controller_Phi_Kd_2D_Lookup_Table);
SkywalkerX8.Control.Lateral.PhiController.Digital.NPhi = squeeze(tableValues.PIDF_Controller_Phi_N_2D_Lookup_Table);

SkywalkerX8.Control.Lateral.PhiController.Digital.KpPhi2DOF = squeeze(tableValues.PDF_Controller_Phi_2DOF_Kp_2D_Lookup_Table);
SkywalkerX8.Control.Lateral.PhiController.Digital.KdPhi2DOF = squeeze(tableValues.PDF_Controller_Phi_2DOF_Kd_2D_Lookup_Table);
SkywalkerX8.Control.Lateral.PhiController.Digital.NPhi2DOF = squeeze(tableValues.PDF_Controller_Phi_2DOF_N_2D_Lookup_Table);

% Get scheduling parameters and write them to our desired variables
% Note thase these are based on our basis function.

TGS = getBlockParam(STPhi);
SkywalkerX8.Control.Lateral.PhiController.Digital.BasisFunction = TGS.PIDF_Controller_Phi_Kp_2D_Lookup_Table.BasisFunctions;
SkywalkerX8.Control.Lateral.PhiController.Digital.KpPhiParameterizedGains = getData(TGS.PIDF_Controller_Phi_Kp_2D_Lookup_Table);
SkywalkerX8.Control.Lateral.PhiController.Digital.KiPhiParameterizedGains = getData(TGS.PIDF_Controller_Phi_Ki_2D_Lookup_Table);
SkywalkerX8.Control.Lateral.PhiController.Digital.KdPhiParameterizedGains = getData(TGS.PIDF_Controller_Phi_Kd_2D_Lookup_Table);
SkywalkerX8.Control.Lateral.PhiController.Digital.NPhiParameterizedGains = getData(TGS.PIDF_Controller_Phi_N_2D_Lookup_Table);

SkywalkerX8.Control.Lateral.PhiController.Digital.KpPhi2DOFParameterizedGains = getData(TGS.PDF_Controller_Phi_2DOF_Kp_2D_Lookup_Table);
SkywalkerX8.Control.Lateral.PhiController.Digital.KdPhi2DOFParameterizedGains = getData(TGS.PDF_Controller_Phi_2DOF_Kd_2D_Lookup_Table);
SkywalkerX8.Control.Lateral.PhiController.Digital.NPhi2DOFParameterizedGains = getData(TGS.PDF_Controller_Phi_2DOF_N_2D_Lookup_Table);

disp('Phi Control Loop Design Complete')

%% Chi Control Design %%

disp('Starting Chi Control Loop Design...')

KpInit = 0.1;
KiInit = 1;

Kp = tunableSurface('Kp', KpInit, VaTuningGrid, VaShapeFcn);
Ki = tunableSurface('Ki', KiInit, VaTuningGrid, VaShapeFcn);

tunedBlocks = {'PIDF Controller Chi Kp 2D Lookup Table',...
               'PIDF Controller Chi Ki 2D Lookup Table'};

minRealTolerance = 1E-05;

% We now reduce these models to make the tuning easier. We know our
% bandwidth for this control loop is approximately 0.25 rad/s, as such, we
% can ignore any dynamics higher than around 0.75 rad/s when tuning. As
% such, we can use a reducton for r to a 3rd order model, and a reduction
% for Chi as a first order model. This should drastically simplify our
% tuning efforts.

phiMax = 30*pi/180;

for i = 1:nVa
    
    phiCToChiEstimate(:, :, i) =  tf((g/SkywalkerX8.Control.Lateral.SchedulingVariables.VaArray(i))*tan(phiMax*0.5), [1 0]);
    
end

plantSubValue = [tf(0) tf(0) tf(0);...
                 tf(0) tf(0) phiCToChiEstimate;...
                 tf(0) tf(0) tf(0);...
                 tf(0) tf(0) tf(0)];
             
plantSubName = [sys '/SkywalkerX8 Aircraft + Aerodynamics Lateral'];

plantSub = struct('Name', plantSubName, 'Value', plantSubValue);

controllerPhiSubValue = [tf(1),...
                         tf(0),...
                         tf(0),...
                         tf(0)];
                       
controllerPhiSubName = [sys '/Gain Scheduled Controller Phi'];

controllerPhiSub = struct('Name', controllerPhiSubName, 'Value', controllerPhiSubValue);
    
BlockSubs = [plantSub;...
             controllerPhiSub];

% Create slTuner interface for tuning of tunedBlocks within the context of
% sys, after substituting out the blocks defined in BlockSubs, with the
% options given in LinOpt.

ST0 = slTuner(sys, tunedBlocks, BlockSubs, LinOpt);

ST0.Ts = 0; % We want continuous-time linearizations 

% Add all relevant points of interest (POI) that we will examine in the
% model.

POI = {'SkywalkerX8_Lateral_Control_Digital/Chi_c/1'
       'SkywalkerX8_Lateral_Control_Digital/Chi_e' 
       'SkywalkerX8_Lateral_Control_Digital/Phi_c'
       'SkywalkerX8_Lateral_Control_Digital/Sum2/Chi_e'
       'SkywalkerX8_Lateral_Control_Digital/Gain Scheduled Controller Chi/PIDF Controller Va_theta/POut'
       'SkywalkerX8_Lateral_Control_Digital/SkywalkerX8 Aircraft + Aerodynamics Lateral/Va' 
       'SkywalkerX8_Lateral_Control_Digital/SkywalkerX8 Aircraft + Aerodynamics Lateral/p' 
       'SkywalkerX8_Lateral_Control_Digital/SkywalkerX8 Aircraft + Aerodynamics Lateral/Phi'
       'SkywalkerX8_Lateral_Control_Digital/SkywalkerX8 Aircraft + Aerodynamics Lateral/Chi'};

ST0.addPoint(POI);

ST0.addOpening('SkywalkerX8_Lateral_Control_Digital/SkywalkerX8 Aircraft + Aerodynamics Lateral/Va');
ST0.addOpening('SkywalkerX8_Lateral_Control_Digital/SkywalkerX8 Aircraft + Aerodynamics Lateral/p');
ST0.addOpening('SkywalkerX8_Lateral_Control_Digital/SkywalkerX8 Aircraft + Aerodynamics Lateral/Phi');

% We know we need to constrain what the maximum value can be for Kp due to
% actuator saturation.

% We assume that our maximum expected Chi change wil be 90 degrees. We also know
% that we expect our maximum phi to be 60 degrees. We assume our maximum
% step in Chi will be approximately half the absolute maximum.

chiMax = 90*pi/180;
          
SkywalkerX8.Control.Lateral.ChiController.Digital.upperSaturationPhiC = phiMax;
SkywalkerX8.Control.Lateral.ChiController.Digital.lowerSaturationPhiC = -phiMax;

% so we can generate a
% limit on gain from these 2 values:

ChiPhiGainLimit = 10*phiMax/chiMax;

% and we assume this will only really be commanded if we are in trim

ChiPhiPGainLimitInput = 'SkywalkerX8_Lateral_Control_Digital/Sum2/Chi_e';
ChiPhiPGainLimitOutput = 'SkywalkerX8_Lateral_Control_Digital/Gain Scheduled Controller Chi/Phi_c';

R1 = TuningGoal.Gain(ChiPhiPGainLimitInput, ChiPhiPGainLimitOutput, ChiPhiGainLimit);
R1.Focus = [1E-02 1E02];

% Next we know that our general response should have the standard gain
% margin of 6 dB, and a 70 deg phase margin forces a response that does not
% have a resonance peak, while still ensuring as rapid a response as
% possible (and around a 5% OS for a 2nd order system). So we assume this

gainMargin = 6; % >6 dB gain margin ideally
phaseMargin = 40; % 40 deg phase margin should provide adequate damping
R2 = TuningGoal.Margins('SkywalkerX8_Lateral_Control_Digital/SkywalkerX8 Aircraft + Aerodynamics Lateral/Chi', gainMargin, phaseMargin);
R2.Focus = [1E-02 1E02];

% Next we know that our phi controller has a crossover frequency at
% approximately 0.75 rad/s. In order to have this be uncoupled for the
% inner loop dynamics, we specify a 3x bandwidth seperation.

LS = frd([100000 1 0.001],[0.002 0.2 2]);  
R3 = TuningGoal.LoopShape('Chi', LS, 0.5);

% Next we simply add a goal for our response in the time domain. We'd like
% this to be as fast as possible, given the previous constraints on
% crossover frequency and margins. We know that for a coordinated turn,
% dPsi/dt = g/Va*tan(phi). As such, we can estimate an optimal psi_dot
% assuming a constant bank angle (let's assume half the maximum) and use
% this to determine an expected rise time (making use of the previous
% expected maximum Chi command as the reference command). We slow this
% requirement down slightly to account for having to actually get to the
% bank angle from 0 roll - and assume this to mean we'll be 10% slower than
% optimal

g = 9.81;
tauScalar = 1;
bandwidthSeparation = 1.5;
riseTimeToTau = 1/2.2;
tauValues = zeros(nVa, 1); 
OSValues = zeros(nVa, 1);

for i = 1:nVa
    
    psiDotMax = (g/SkywalkerX8.Control.Lateral.SchedulingVariables.VaArray(i))*tan(phiMax);
    optimalRiseTime = chiMax/psiDotMax;
    tauValues(i) = optimalRiseTime*tauScalar*riseTimeToTau/bandwidthSeparation;
    OSValues(i) = 5; %5% overshoot is acceptable if possible
    
end

FH = @(tau, OS) TuningGoal.StepTracking('Chi_c', 'Chi', tau, OS);

R4 = varyingGoal(FH, tauValues, OSValues);

ChiPhiPGainLimitInput = 'SkywalkerX8_Lateral_Control_Digital/Sum2/Chi_e';
ChiPhiPGainLimitOutput = 'SkywalkerX8_Lateral_Control_Digital/Gain Scheduled Controller Chi/PIDF Controller Va_theta/POut';

R5 = TuningGoal.Gain(ChiPhiPGainLimitInput, ChiPhiPGainLimitOutput, ChiPhiGainLimit);
R5.Focus = [1E-02 1E02];
R5.Openings = {ChiPhiPGainLimitInput, ChiPhiPGainLimitOutput};

ST0.setBlockParam('PIDF Controller Chi Kp 2D Lookup Table', Kp);
ST0.setBlockParam('PIDF Controller Chi Ki 2D Lookup Table', Ki);

STChi = systune(ST0, [R1, R2], [R4, R5], sysTuneOpts);

tableValues = getBlockValue(STChi);

SkywalkerX8.Control.Lateral.ChiController.Digital.KpChiTF = tableValues.PIDF_Controller_Chi_Kp_2D_Lookup_Table;
SkywalkerX8.Control.Lateral.ChiController.Digital.KiChiTF = tableValues.PIDF_Controller_Chi_Ki_2D_Lookup_Table;

SkywalkerX8.Control.Lateral.ChiController.Digital.KpChi = squeeze(tableValues.PIDF_Controller_Chi_Kp_2D_Lookup_Table);
SkywalkerX8.Control.Lateral.ChiController.Digital.KiChi = squeeze(tableValues.PIDF_Controller_Chi_Ki_2D_Lookup_Table);

% Get scheduling parameters and write them to our desired variables
% Note thase these are based on our basis function.

TGS = getBlockParam(STChi);
SkywalkerX8.Control.Lateral.ChiController.Digital.BasisFunction = TGS.PIDF_Controller_Chi_Kp_2D_Lookup_Table.BasisFunctions;
SkywalkerX8.Control.Lateral.ChiController.Digital.KpChiParameterizedGains = getData(TGS.PIDF_Controller_Chi_Kp_2D_Lookup_Table);
SkywalkerX8.Control.Lateral.ChiController.Digital.KiChiParameterizedGains = getData(TGS.PIDF_Controller_Chi_Ki_2D_Lookup_Table);

disp('Chi Control Loop Design Complete')