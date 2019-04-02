% Longitudinal Linearised Model Analysis %

% The purpose of this script is to perform some analysis on the reduced
% order algebraic model of the longitudinal dynamics of the SkywalkerX8
% system. This will be done by making use of the Simulink model
% SkywalkerX8_Longitudinal_Algebraic_Control.slx.

% We will pull the algebraically designed controller data
% (SkywalkerX8_Longitudinal_LinearModelPrediction.m) in and analyse the
% system from the perspective of disturbance rejection and the impact of
% measurement noise. This will primarily be a frequency domain exercise
% with heavy use of the bode plot.

bodeFreqRange = {1E-02,1E02};

figure(1)
ax11 = subplot(3, 1, 1);
hold(ax11, 'on');
ax12 = subplot(3, 1, 2);
hold(ax12, 'on');
ax13 = subplot(3, 1, 3);
hold(ax13, 'on');

figure(2)
ax21 = subplot(2, 1, 1);
hold on;
ax22 = subplot(2, 1, 2);
hold on;

figure(3)
ax31 = gca();
hold on;

figure(4)
ax41 = subplot(3, 1, 1);
hold(ax41, 'on');
ax42 = subplot(3, 1, 2);
hold(ax42, 'on');
ax43 = subplot(3, 1, 3);
hold(ax43, 'on');

figure(5)
ax51 = subplot(3, 1, 1);
hold(ax51, 'on');
ax52 = subplot(3, 1, 2);
hold(ax52, 'on');
ax53 = subplot(3, 1, 3);
hold(ax53, 'on');

for i = 1:length(SkywalkerX8.Control.Longitudinal.SchedulingVariables.VaArray)

    % Select the theta controller to be the altitude loop to start with

    SkywalkerX8.Control.Longitudinal.AlgebraicDesign.ReducedOrderModel.Controller.ThetaCSelector = 0;

    SkywalkerX8.Control.Longitudinal.AlgebraicDesign.ReducedOrderModel.QDE_Numerator ...
        = cell2mat(SkywalkerX8.Control.Longitudinal.AlgebraicDesign.De2qLinearizedModels(i).Numerator);
    SkywalkerX8.Control.Longitudinal.AlgebraicDesign.ReducedOrderModel.QDE_Denominator ...
        = cell2mat(SkywalkerX8.Control.Longitudinal.AlgebraicDesign.De2qLinearizedModels(i).Denominator);

    SkywalkerX8.Control.Longitudinal.AlgebraicDesign.ReducedOrderModel.Va_trim ...
        =  SkywalkerX8.Control.Longitudinal.SchedulingVariables.VaArray(i);

    SkywalkerX8.Control.Longitudinal.AlgebraicDesign.ReducedOrderModel.dt_trim ...
        = SkywalkerX8.Control.Longitudinal.OpAirframe(i).Inputs(1).u;

    SkywalkerX8.Control.Longitudinal.AlgebraicDesign.ReducedOrderModel.Vadt_Numerator ...
        = cell2mat(SkywalkerX8.Control.Longitudinal.AlgebraicDesign.Dt2VaLinearizedModels(i).Numerator);
    SkywalkerX8.Control.Longitudinal.AlgebraicDesign.ReducedOrderModel.Vadt_Numerator ...
        = SkywalkerX8.Control.Longitudinal.AlgebraicDesign.ReducedOrderModel.Vadt_Numerator(2);
    SkywalkerX8.Control.Longitudinal.AlgebraicDesign.ReducedOrderModel.Vadt_Denominator ...
        = cell2mat(SkywalkerX8.Control.Longitudinal.AlgebraicDesign.Dt2VaLinearizedModels(i).Denominator);

    SkywalkerX8.Control.Longitudinal.AlgebraicDesign.ReducedOrderModel.Controller.KdTheta ...
        = SkywalkerX8.Control.Longitudinal.AlgebraicDesign.KdTheta(i);
    SkywalkerX8.Control.Longitudinal.AlgebraicDesign.ReducedOrderModel.Controller.KpTheta ...
        = SkywalkerX8.Control.Longitudinal.AlgebraicDesign.KpTheta(i);

    SkywalkerX8.Control.Longitudinal.AlgebraicDesign.ReducedOrderModel.Controller.KpAlt ...
        = SkywalkerX8.Control.Longitudinal.AlgebraicDesign.KpAlt(i);
    SkywalkerX8.Control.Longitudinal.AlgebraicDesign.ReducedOrderModel.Controller.KiAlt ...
        = SkywalkerX8.Control.Longitudinal.AlgebraicDesign.KiAlt(i);

    SkywalkerX8.Control.Longitudinal.AlgebraicDesign.ReducedOrderModel.Controller.KpV2 ...
        = SkywalkerX8.Control.Longitudinal.AlgebraicDesign.KpV2(i);

    SkywalkerX8.Control.Longitudinal.AlgebraicDesign.ReducedOrderModel.Controller.KiV2 ...
        = SkywalkerX8.Control.Longitudinal.AlgebraicDesign.KiV2(i);

    SkywalkerX8.Control.Longitudinal.AlgebraicDesign.ReducedOrderModel.Controller.KpV ...
        = SkywalkerX8.Control.Longitudinal.AlgebraicDesign.KpV(i);

    SkywalkerX8.Control.Longitudinal.AlgebraicDesign.ReducedOrderModel.Controller.KiV ...
        = SkywalkerX8.Control.Longitudinal.AlgebraicDesign.KiV(i);

    %% TF Check %%

    mdl = 'SkywalkerX8_Longitudinal_Algebraic_Control';
    POI = {'Va_c' 'h_c' '\theta_c' 'Va' 'q' '\theta' 'h' 'D_{dt}' 'D_{de}' 'D_V' 'D_q'...,
        'D_\theta' 'M_{V_a}' 'M_q' 'M_\theta' 'M_h'};
    sllin = slLinearizer(mdl, POI);
    
    VA_VAc = getIOTransfer(sllin, 'Va_c', 'Va');
    H_HC = getIOTransfer(sllin, 'h_c', 'h');
    THETA_THETAc = getIOTransfer(sllin, '\theta_c', '\theta');
    
    VA_Ddt = getIOTransfer(sllin, 'D_{dt}', 'Va');
    VA_DV = getIOTransfer(sllin, 'D_V', 'Va');
    
    VA_Mv = getIOTransfer(sllin, 'M_{V_a}', 'Va');
    
    H_Dde = getIOTransfer(sllin, 'D_{de}', 'h');
    H_Dq = getIOTransfer(sllin, 'D_q', 'h');
    H_Dtheta = getIOTransfer(sllin, 'D_\theta', 'h');
    
    H_Mq = getIOTransfer(sllin, 'M_q', 'h');
    H_Mtheta = getIOTransfer(sllin, 'M_\theta', 'h');
    H_Mh = getIOTransfer(sllin, 'M_h', 'h');
    
    bode(ax11, VA_VAc, bodeFreqRange, 'b');
    bode(ax12, H_HC, bodeFreqRange, 'b');
    bode(ax13, THETA_THETAc, bodeFreqRange, 'b');

    bode(ax21, VA_Ddt, bodeFreqRange, 'b');
    bode(ax22, VA_DV, bodeFreqRange, 'b');

    bode(ax31, VA_Mv, bodeFreqRange, 'b');

    bode(ax41, H_Dde, bodeFreqRange, 'b');
    bode(ax42, H_Dq, bodeFreqRange, 'b');
    bode(ax43, H_Dtheta, bodeFreqRange, 'b');

    bode(ax51, H_Mq, bodeFreqRange, 'b');
    bode(ax52, H_Mtheta, bodeFreqRange, 'b');
    bode(ax53, H_Mh, bodeFreqRange, 'b');
    
end

% Mid Point Controller Check %

    SkywalkerX8.Control.Longitudinal.AlgebraicDesign.ReducedOrderModel.Controller.KdTheta ...
        = SkywalkerX8.Control.Longitudinal.AlgebraicDesign.KdTheta(7);
    SkywalkerX8.Control.Longitudinal.AlgebraicDesign.ReducedOrderModel.Controller.KpTheta ...
        = SkywalkerX8.Control.Longitudinal.AlgebraicDesign.KpTheta(7);

    SkywalkerX8.Control.Longitudinal.AlgebraicDesign.ReducedOrderModel.Controller.KpAlt ...
        = SkywalkerX8.Control.Longitudinal.AlgebraicDesign.KpAlt(7);
    SkywalkerX8.Control.Longitudinal.AlgebraicDesign.ReducedOrderModel.Controller.KiAlt ...
        = SkywalkerX8.Control.Longitudinal.AlgebraicDesign.KiAlt(7);

    SkywalkerX8.Control.Longitudinal.AlgebraicDesign.ReducedOrderModel.Controller.KpV2 ...
        = SkywalkerX8.Control.Longitudinal.AlgebraicDesign.KpV2(7);

    SkywalkerX8.Control.Longitudinal.AlgebraicDesign.ReducedOrderModel.Controller.KiV2 ...
        = SkywalkerX8.Control.Longitudinal.AlgebraicDesign.KiV2(7);

    SkywalkerX8.Control.Longitudinal.AlgebraicDesign.ReducedOrderModel.Controller.KpV ...
        = SkywalkerX8.Control.Longitudinal.AlgebraicDesign.KpV(7);

    SkywalkerX8.Control.Longitudinal.AlgebraicDesign.ReducedOrderModel.Controller.KiV ...
        = SkywalkerX8.Control.Longitudinal.AlgebraicDesign.KiV(7);

for i = 1:length(SkywalkerX8.Control.Longitudinal.SchedulingVariables.VaArray)

    % Select the theta controller to be the altitude loop to start with

    SkywalkerX8.Control.Longitudinal.AlgebraicDesign.ReducedOrderModel.Controller.ThetaCSelector = 0;

    SkywalkerX8.Control.Longitudinal.AlgebraicDesign.ReducedOrderModel.QDE_Numerator ...
        = cell2mat(SkywalkerX8.Control.Longitudinal.AlgebraicDesign.De2qLinearizedModels(i).Numerator);
    SkywalkerX8.Control.Longitudinal.AlgebraicDesign.ReducedOrderModel.QDE_Denominator ...
        = cell2mat(SkywalkerX8.Control.Longitudinal.AlgebraicDesign.De2qLinearizedModels(i).Denominator);

    SkywalkerX8.Control.Longitudinal.AlgebraicDesign.ReducedOrderModel.Va_trim ...
        =  SkywalkerX8.Control.Longitudinal.SchedulingVariables.VaArray(i);

    SkywalkerX8.Control.Longitudinal.AlgebraicDesign.ReducedOrderModel.dt_trim ...
        = SkywalkerX8.Control.Longitudinal.OpAirframe(i).Inputs(1).u;

    SkywalkerX8.Control.Longitudinal.AlgebraicDesign.ReducedOrderModel.Vadt_Numerator ...
        = cell2mat(SkywalkerX8.Control.Longitudinal.AlgebraicDesign.Dt2VaLinearizedModels(i).Numerator);
    SkywalkerX8.Control.Longitudinal.AlgebraicDesign.ReducedOrderModel.Vadt_Numerator ...
        = SkywalkerX8.Control.Longitudinal.AlgebraicDesign.ReducedOrderModel.Vadt_Numerator(2);
    SkywalkerX8.Control.Longitudinal.AlgebraicDesign.ReducedOrderModel.Vadt_Denominator ...
        = cell2mat(SkywalkerX8.Control.Longitudinal.AlgebraicDesign.Dt2VaLinearizedModels(i).Denominator);

    %% TF Check %%

    mdl = 'SkywalkerX8_Longitudinal_Algebraic_Control';
    POI = {'Va_c' 'h_c' '\theta_c' 'Va' 'q' '\theta' 'h' 'D_{dt}' 'D_{de}' 'D_V' 'D_q'...,
        'D_\theta' 'M_{V_a}' 'M_q' 'M_\theta' 'M_h'};
    sllin = slLinearizer(mdl, POI);
    
    VA_VAc = getIOTransfer(sllin, 'Va_c', 'Va');
    H_HC = getIOTransfer(sllin, 'h_c', 'h');
    THETA_THETAc = getIOTransfer(sllin, '\theta_c', '\theta');
    
    VA_Ddt = getIOTransfer(sllin, 'D_{dt}', 'Va');
    VA_DV = getIOTransfer(sllin, 'D_V', 'Va');
    
    VA_Mv = getIOTransfer(sllin, 'M_{V_a}', 'Va');
    
    H_Dde = getIOTransfer(sllin, 'D_{de}', 'h');
    H_Dq = getIOTransfer(sllin, 'D_q', 'h');
    H_Dtheta = getIOTransfer(sllin, 'D_\theta', 'h');
    
    H_Mq = getIOTransfer(sllin, 'M_q', 'h');
    H_Mtheta = getIOTransfer(sllin, 'M_\theta', 'h');
    H_Mh = getIOTransfer(sllin, 'M_h', 'h');
    
    bode(ax11, VA_VAc, bodeFreqRange, 'r--');
    bode(ax12, H_HC, bodeFreqRange, 'r--');
    bode(ax13, THETA_THETAc, bodeFreqRange, 'r--');

    bode(ax21, VA_Ddt, bodeFreqRange, 'r--');
    bode(ax22, VA_DV, bodeFreqRange, 'r--');

    bode(ax31, VA_Mv, bodeFreqRange, 'r--');

    bode(ax41, H_Dde, bodeFreqRange, 'r--');
    bode(ax42, H_Dq, bodeFreqRange, 'r--');
    bode(ax43, H_Dtheta, bodeFreqRange, 'r--');

    bode(ax51, H_Mq, bodeFreqRange, 'r--');
    bode(ax52, H_Mtheta, bodeFreqRange, 'r--');
    bode(ax53, H_Mh, bodeFreqRange, 'r--');
    
end