SkywalkerX8.Control.Longitudinal.AltStateMachine.PreFlightBypass = true;

SkywalkerX8.InitialConditions.XeYeZe = [0 0 -100];
SkywalkerX8.InitialConditions.uvw = [17.3 0 0.499];
SkywalkerX8.InitialConditions.PhiThetaPsi = [0 0.0288 0];
SkywalkerX8.InitialConditions.pqr = [0 0 0];

SkywalkerX8.InitialConditions.dt = 0.504;
SkywalkerX8.InitialConditions.de = 0.129;
SkywalkerX8.InitialConditions.da = 0;

% Use a "fresh breeze" definition to get magnitude of wind velocity (8 -
% 10.7 m/s)

SkywalkerX8.Ambient.Wind.wnwewd = [6.5, 6.5, 0];

SkywalkerX8.InitialConditions.uvw = SkywalkerX8.InitialConditions.uvw;

Va = sqrt(SkywalkerX8.InitialConditions.uvw*SkywalkerX8.InitialConditions.uvw');

if (Va < SkywalkerX8.Control.Longitudinal.SchedulingVariables.VaArray(1))
   Va =  SkywalkerX8.Control.Longitudinal.SchedulingVariables.VaArray(1);
end
if (Va > SkywalkerX8.Control.Longitudinal.SchedulingVariables.VaArray(end))
   Va = SkywalkerX8.Control.Longitudinal.SchedulingVariables.VaArray(end);
end
alpha = atan2(SkywalkerX8.InitialConditions.uvw(3), SkywalkerX8.InitialConditions.uvw(1));

feedbackControllerThetaOutput = SkywalkerX8.InitialConditions.PhiThetaPsi(2)*...
                                interpn(SkywalkerX8.Control.Longitudinal.SchedulingVariables.VaArray,... 
                                         SkywalkerX8.Control.Longitudinal.SchedulingVariables.alphaArray,... 
                                         SkywalkerX8.Control.Longitudinal.thetaController.KpTheta2DOF,... 
                                         Va, alpha, 'linear');

SkywalkerX8.InitialConditions.ThetaController.Integrator = -SkywalkerX8.InitialConditions.de - feedbackControllerThetaOutput;
SkywalkerX8.InitialConditions.ThetaController.RefController.Derivative = SkywalkerX8.InitialConditions.PhiThetaPsi(2)*...
                                                                         interpn(SkywalkerX8.Control.Longitudinal.SchedulingVariables.VaArray,... 
                                                                                 SkywalkerX8.Control.Longitudinal.SchedulingVariables.alphaArray,... 
                                                                                 SkywalkerX8.Control.Longitudinal.thetaController.KdTheta2DOF,... 
                                                                                 Va, alpha, 'linear');

SkywalkerX8.InitialConditions.altController.Integrator = SkywalkerX8.InitialConditions.PhiThetaPsi(2);
SkywalkerX8.InitialConditions.altController.RefController.Derivative =  -SkywalkerX8.InitialConditions.XeYeZe(3)*...
                                                                         interpn(SkywalkerX8.Control.Longitudinal.SchedulingVariables.VaArray,... 
                                                                                 SkywalkerX8.Control.Longitudinal.SchedulingVariables.alphaArray,... 
                                                                                 SkywalkerX8.Control.Longitudinal.altController.KdAlt2DOF,... 
                                                                                 Va, alpha, 'linear');

SkywalkerX8.InitialConditions.VaThetaController.Integrator = -SkywalkerX8.InitialConditions.PhiThetaPsi(2);

SkywalkerX8.InitialConditions.VaDtController.Integrator = SkywalkerX8.InitialConditions.dt;

%% Sensors %%

g = 9.81;
rho = SkywalkerX8.Sensors.StateEstimate.SensorInversion.AltitudePressure.Density;

SkywalkerX8.Sensors.IMU.Accelerometer.X.InitialCondition = g*sin(SkywalkerX8.InitialConditions.PhiThetaPsi(2));
SkywalkerX8.Sensors.IMU.Accelerometer.Y.InitialCondition = -g*cos(SkywalkerX8.InitialConditions.PhiThetaPsi(2))*sin(SkywalkerX8.InitialConditions.PhiThetaPsi(1));
SkywalkerX8.Sensors.IMU.Accelerometer.Z.InitialCondition = -g*cos(SkywalkerX8.InitialConditions.PhiThetaPsi(2))*cos(SkywalkerX8.InitialConditions.PhiThetaPsi(1));

SkywalkerX8.Sensors.IMU.Gyroscope.X.InitialCondition = SkywalkerX8.InitialConditions.pqr(1);
SkywalkerX8.Sensors.IMU.Gyroscope.Y.InitialCondition = SkywalkerX8.InitialConditions.pqr(2);
SkywalkerX8.Sensors.IMU.Gyroscope.Z.InitialCondition = SkywalkerX8.InitialConditions.pqr(3);

SkywalkerX8.Sensors.IMU.Compass.InitialCondition = SkywalkerX8.InitialConditions.PhiThetaPsi(3);

SkywalkerX8.Sensors.AirspeedPressure.InitialCondition = 0.5*rho*Va^2;
SkywalkerX8.Sensors.AltitudePressure.InitialCondition = -rho*g*SkywalkerX8.InitialConditions.XeYeZe(3);

SkywalkerX8.Sensors.AoA.InitialCondition = atan2(SkywalkerX8.InitialConditions.uvw(3), SkywalkerX8.InitialConditions.uvw(1));

SkywalkerX8.Sensors.GPS.pnInit = SkywalkerX8.InitialConditions.XeYeZe(1);
SkywalkerX8.Sensors.GPS.peInit = SkywalkerX8.InitialConditions.XeYeZe(2);
SkywalkerX8.Sensors.GPS.pdInit = SkywalkerX8.InitialConditions.XeYeZe(3);
SkywalkerX8.Sensors.GPS.VgInit = Va;
SkywalkerX8.Sensors.GPS.ChiInit = SkywalkerX8.InitialConditions.PhiThetaPsi(3);

%% State Estimators %%

%% Filters

SkywalkerX8.Sensors.Filters.AngularRates.Roll.InitialCondition = SkywalkerX8.Sensors.IMU.Gyroscope.X.InitialCondition;
SkywalkerX8.Sensors.Filters.AngularRates.Pitch.InitialCondition = SkywalkerX8.Sensors.IMU.Gyroscope.Y.InitialCondition;
SkywalkerX8.Sensors.Filters.AngularRates.Yaw.InitialCondition = SkywalkerX8.Sensors.IMU.Gyroscope.Z.InitialCondition;


SkywalkerX8.Sensors.Filters.AirspeedPressure.InitialCondition = SkywalkerX8.Sensors.AirspeedPressure.InitialCondition;
SkywalkerX8.Sensors.Filters.AltitudePressure.InitialCondition = SkywalkerX8.Sensors.AltitudePressure.InitialCondition;

SkywalkerX8.Sensors.Filters.AoA.InitialCondition = SkywalkerX8.Sensors.AoA.InitialCondition;

%% Attitude

SkywalkerX8.Sensors.EKF.Attitude.InitialState = SkywalkerX8.InitialConditions.PhiThetaPsi(1:2);

SkywalkerX8.Sensors.EKF.Attitude.InitialInput = [SkywalkerX8.InitialConditions.pqr(1),...
                                                 SkywalkerX8.InitialConditions.pqr(2),...
                                                 SkywalkerX8.InitialConditions.pqr(3),...
                                                 Va,...
                                                 SkywalkerX8.Sensors.AoA.InitialCondition];

SkywalkerX8.Sensors.EKF.Attitude.InitialMeasurement = accelerometerMeasurementEstimate(SkywalkerX8.Sensors.EKF.Attitude.InitialState,...
                                                                                       SkywalkerX8.Sensors.EKF.Attitude.InitialInput);

%% GPS Smoothing

% x = (pn, pe, Vg, Chi, wn, we, psi)
% u = (Va, q, r, Phi, Theta)
% y = (yGPSN, yGPSE, yGPSVg, yGPSChi, 0, 0)

SkywalkerX8.Sensors.EKF.GPSSmoothing.InitialState = [SkywalkerX8.InitialConditions.XeYeZe(1),...
                                                     SkywalkerX8.InitialConditions.XeYeZe(2),...
                                                     Va,...
                                                     SkywalkerX8.InitialConditions.PhiThetaPsi(3),...
                                                     0,...
                                                     0,...
                                                     SkywalkerX8.InitialConditions.PhiThetaPsi(3)];
                                                       
SkywalkerX8.Sensors.EKF.GPSSmoothing.InitialInput = [Va,...
                                                     SkywalkerX8.InitialConditions.pqr(2),...
                                                     SkywalkerX8.InitialConditions.pqr(3),...
                                                     SkywalkerX8.InitialConditions.PhiThetaPsi(1),...
                                                     SkywalkerX8.InitialConditions.PhiThetaPsi(2)];
                                                 
SkywalkerX8.Sensors.EKF.GPSSmoothing.InitialMeasurement = GPSSmoothingMeasurementEstimate(SkywalkerX8.Sensors.EKF.GPSSmoothing.InitialState,...
                                                                                          SkywalkerX8.Sensors.EKF.GPSSmoothing.InitialInput);
                                                                                      
SkywalkerX8.Sensors.EKF.GPSSmoothing.Filters.ChiFilter.InitialCondition = SkywalkerX8.Sensors.EKF.GPSSmoothing.InitialState(4);
SkywalkerX8.Sensors.EKF.GPSSmoothing.Filters.PsiFilter.InitialCondition = SkywalkerX8.Sensors.EKF.GPSSmoothing.InitialState(7);