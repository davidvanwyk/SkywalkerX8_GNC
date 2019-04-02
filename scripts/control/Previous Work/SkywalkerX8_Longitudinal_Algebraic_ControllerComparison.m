%% Linear Model Controller Comparison %%

% The purpose of this script is to review the effect of the algebraically
% designed controllers and if it warrants using a gain scheduled controller
% scheme or if a single mid-point controller responds adequately across the
% flight envelope 

pitchRateDamperMidPoint = SkywalkerX8.Control.Longitudinal.AlgebraicDesign.KdTheta(7);
thetaControllerMidPoint = SkywalkerX8.Control.Longitudinal.AlgebraicDesign.KpTheta(7);
hControllerMidPoint = pid(SkywalkerX8.Control.Longitudinal.AlgebraicDesign.KpAlt(7), SkywalkerX8.Control.Longitudinal.AlgebraicDesign.KiAlt(7));
VaControllerThetaMidPoint = pid(SkywalkerX8.Control.Longitudinal.AlgebraicDesign.KpV2(7), SkywalkerX8.Control.Longitudinal.AlgebraicDesign.KiV2(7));
VaControllerdtMidPoint = pid(SkywalkerX8.Control.Longitudinal.AlgebraicDesign.KpV(7), SkywalkerX8.Control.Longitudinal.AlgebraicDesign.KiV(7));

q2theta = tf(1, [1 0]);

figure(1)
ax11 = subplot(1, 2, 1);
hold(ax11, 'on');
ax12 = subplot(1, 2, 2);
hold(ax12, 'on');

figure(2)
ax21 = subplot(1, 2, 1);
hold on;
ax22 = subplot(1, 2, 2);
hold on;

figure(3)
ax31 = subplot(1, 2, 1);
hold on;
ax32 = subplot(1, 2, 2);
hold on;

figure(4)
ax41 = subplot(1, 2, 1);
hold on;
ax42 = subplot(1, 2, 2);
hold on;

figure(5)
ax51 = subplot(1, 2, 1);
hold on;
ax52 = subplot(1, 2, 2);
hold on;

for i = 1:length(SkywalkerX8.Performance.altitude)
   
    theta2alt = tf(SkywalkerX8.Performance.Va(i), [1 0]);
    theta2Va = SkywalkerX8.Control.Longitudinal.AlgebraicDesign.Theta2VaLinearizedModels(i);
    dt2Va = SkywalkerX8.Control.Longitudinal.AlgebraicDesign.Dt2VaLinearizedModels(i);
    
    pitchRateLoopMidPoint(i) = feedback(SkywalkerX8.Control.Longitudinal.AlgebraicDesign.De2qLinearizedModels(i), pitchRateDamperMidPoint);
    thetaControlLoopMidPoint(i) = feedback(thetaControllerMidPoint*pitchRateLoopMidPoint(i)*q2theta, 1);
    hControlLoopMidPoint(i) = feedback(hControllerMidPoint*thetaControlLoopMidPoint(i)*theta2alt, 1);
    VaThetaControlLoopMidPoint(i) = feedback(VaControllerThetaMidPoint*thetaControlLoopMidPoint(i)*theta2Va, 1);
    
    VaDtControlLoopMidPoint(i) = feedback(VaControllerdtMidPoint*dt2Va, 1);
    
    pitchRateDamper = SkywalkerX8.Control.Longitudinal.AlgebraicDesign.KdTheta(i);
    thetaController = SkywalkerX8.Control.Longitudinal.AlgebraicDesign.KpTheta(i);
    hController = pid(SkywalkerX8.Control.Longitudinal.AlgebraicDesign.KpAlt(i), SkywalkerX8.Control.Longitudinal.AlgebraicDesign.KiAlt(i));
    VaControllerTheta = pid(SkywalkerX8.Control.Longitudinal.AlgebraicDesign.KpV2(i), SkywalkerX8.Control.Longitudinal.AlgebraicDesign.KiV2(i));
    VaControllerdt = pid(SkywalkerX8.Control.Longitudinal.AlgebraicDesign.KpV(i), SkywalkerX8.Control.Longitudinal.AlgebraicDesign.KiV(i));

    pitchRateLoop(i) = feedback(SkywalkerX8.Control.Longitudinal.AlgebraicDesign.De2qLinearizedModels(i), pitchRateDamper);
    thetaControlLoop(i) = feedback(thetaController*pitchRateLoop(i)*q2theta, 1);
    hControlLoop(i) = feedback(hController*thetaControlLoop(i)*theta2alt, 1);
    VaThetaControlLoop(i) = feedback(VaControllerTheta*thetaControlLoop(i)*theta2Va, 1);
    
    VaDtControlLoop(i) = feedback(VaControllerdt*dt2Va, 1);
    
    bode(ax11, pitchRateLoop(i), 'b', pitchRateLoopMidPoint(i), 'r--');
    step(ax12, pitchRateLoop(i), 'b', pitchRateLoopMidPoint(i), 'r--');

    bode(ax21, thetaControlLoop(i), 'b', thetaControlLoopMidPoint(i), 'r--');
    step(ax22, thetaControlLoop(i), 'b', thetaControlLoopMidPoint(i), 'r--');

    bode(ax31, hControlLoop(i), 'b', hControlLoopMidPoint(i), 'r--');
    step(ax32, hControlLoop(i), 'b', hControlLoopMidPoint(i), 'r--');

    bode(ax41, VaThetaControlLoop(i), 'b', VaThetaControlLoopMidPoint(i), 'r--');
    step(ax42, VaThetaControlLoop(i), 'b', VaThetaControlLoopMidPoint(i), 'r--');

    bode(ax51, VaDtControlLoop(i), 'b', VaDtControlLoopMidPoint(i), 'r--');
    step(ax52, VaDtControlLoop(i), 'b', VaDtControlLoopMidPoint(i), 'r--');
end