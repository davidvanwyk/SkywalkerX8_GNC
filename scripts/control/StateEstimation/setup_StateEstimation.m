%% State Estimation Setup %%

% This script sets up our state estimator. This has several low pass
% filters, some sensor inversions and 2 EKFs.

%% Angular Rates %%

% Our angular rates are measured directly - as such we can simply low pass
% filter these. We know that we filter p and q down to 13 rad/s in the
% control loop. We also know that we sample at 100 Hz (approx 628 rad/s).
% As such, we filter these at 20 Hz (127 rad/s) so as to not interfere with
% the dynamics we are trying to control, but also to remove as much noise
% as possible.

% We make use of a second order filter.

SkywalkerX8.Sensors.Filters.AngularRates.Roll.FilterBandwidthHz = 100;
SkywalkerX8.Sensors.Filters.AngularRates.Roll.FilterTF = tf(SkywalkerX8.Sensors.Filters.AngularRates.Roll.FilterBandwidthHz*2*pi,...
                                                            [1 SkywalkerX8.Sensors.Filters.AngularRates.Roll.FilterBandwidthHz*2*pi]);
SkywalkerX8.Sensors.Filters.AngularRates.Roll.FilterSampleTime = 1/100;
SkywalkerX8.Sensors.Filters.AngularRates.Roll.FilterTFDigital = c2d(SkywalkerX8.Sensors.Filters.AngularRates.Roll.FilterTF, SkywalkerX8.Sensors.Filters.AngularRates.Roll.FilterSampleTime);
SkywalkerX8.Sensors.Filters.AngularRates.Roll.InitialCondition = 0;

SkywalkerX8.Sensors.Filters.AngularRates.Pitch.FilterBandwidthHz = 100;
SkywalkerX8.Sensors.Filters.AngularRates.Pitch.FilterTF = tf(SkywalkerX8.Sensors.Filters.AngularRates.Pitch.FilterBandwidthHz*2*pi,...
                                                            [1 SkywalkerX8.Sensors.Filters.AngularRates.Pitch.FilterBandwidthHz*2*pi]);
SkywalkerX8.Sensors.Filters.AngularRates.Pitch.FilterSampleTime = 1/100;
SkywalkerX8.Sensors.Filters.AngularRates.Pitch.FilterTFDigital = c2d(SkywalkerX8.Sensors.Filters.AngularRates.Pitch.FilterTF, SkywalkerX8.Sensors.Filters.AngularRates.Pitch.FilterSampleTime);
SkywalkerX8.Sensors.Filters.AngularRates.Pitch.InitialCondition = 0;

SkywalkerX8.Sensors.Filters.AngularRates.Yaw.FilterBandwidthHz = 100;
SkywalkerX8.Sensors.Filters.AngularRates.Yaw.FilterTF = tf(SkywalkerX8.Sensors.Filters.AngularRates.Yaw.FilterBandwidthHz*2*pi,...
                                                           [1 SkywalkerX8.Sensors.Filters.AngularRates.Yaw.FilterBandwidthHz*2*pi]);
SkywalkerX8.Sensors.Filters.AngularRates.Yaw.FilterSampleTime = 1/100;
SkywalkerX8.Sensors.Filters.AngularRates.Yaw.FilterTFDigital = c2d(SkywalkerX8.Sensors.Filters.AngularRates.Yaw.FilterTF, SkywalkerX8.Sensors.Filters.AngularRates.Yaw.FilterSampleTime);
SkywalkerX8.Sensors.Filters.AngularRates.Yaw.InitialCondition = 0;

%% Altitude %%

% Our barometer measures altitude making use of an absolute pressure
% measurement and an inverted sensor model. As such, we just low pass
% filter our pressure sensor to get rid of as much noise as possible. The
% bandwidth of our altitude loop is approximately 1 rad/s, with a 6.5 rad/s
% (approx 1 Hz) filter on the derivative. As such, we attempt to filter
% down without affecting the dynamics so 5 Hz.

% We make use of a second order filter.

SkywalkerX8.Sensors.Filters.AltitudePressure.FilterBandwidthHz = 5;
SkywalkerX8.Sensors.Filters.AltitudePressure.FilterTF = tf(SkywalkerX8.Sensors.Filters.AltitudePressure.FilterBandwidthHz*2*pi,...
                                                   [1 SkywalkerX8.Sensors.Filters.AltitudePressure.FilterBandwidthHz*2*pi]);
SkywalkerX8.Sensors.Filters.AltitudePressure.FilterTF = SkywalkerX8.Sensors.Filters.AltitudePressure.FilterTF^2;
SkywalkerX8.Sensors.Filters.AltitudePressure.FilterSampleTime = 1/100;
SkywalkerX8.Sensors.Filters.AltitudePressure.FilterTFDigital = c2d(SkywalkerX8.Sensors.Filters.AltitudePressure.FilterTF, SkywalkerX8.Sensors.Filters.AltitudePressure.FilterSampleTime);

SkywalkerX8.Sensors.StateEstimate.SensorInversion.AltitudePressure.Gravity = SkywalkerX8.System.Gravity;
SkywalkerX8.Sensors.StateEstimate.SensorInversion.AltitudePressure.Density = 1.225;
SkywalkerX8.Sensors.Filters.AltitudePressure.InitialCondition = 0;

%% Airspeed %%

% Our airspeed is measured using a differential pressure sensor, followed
% by an inverted sensor model. As such we filter our pressure measurement
% as much as we can without removing the dynamics we need. The Va loop has
% a crossover frequency of 15 rad/s (approx 2.4 Hz), so we filter at >3x
% above this, 10 Hz.

% We make use of a second order filter.

SkywalkerX8.Sensors.Filters.AirspeedPressure.FilterBandwidthHz = 5;
SkywalkerX8.Sensors.Filters.AirspeedPressure.FilterTF = tf(SkywalkerX8.Sensors.Filters.AirspeedPressure.FilterBandwidthHz*2*pi,...
                                                   [1 SkywalkerX8.Sensors.Filters.AirspeedPressure.FilterBandwidthHz*2*pi]);
SkywalkerX8.Sensors.Filters.AirspeedPressure.FilterTF = SkywalkerX8.Sensors.Filters.AirspeedPressure.FilterTF^2;
SkywalkerX8.Sensors.Filters.AirspeedPressure.FilterSampleTime = 1/100;
SkywalkerX8.Sensors.Filters.AirspeedPressure.FilterTFDigital = c2d(SkywalkerX8.Sensors.Filters.AirspeedPressure.FilterTF, SkywalkerX8.Sensors.Filters.AirspeedPressure.FilterSampleTime);

SkywalkerX8.Sensors.Filters.AirspeedPressure.InitialCondition = 0;

%% Angle of Attack %%

% Our angle of attack is measured by an angle of attack sensor - so a
% direct measurement. We make use of our theta bandwidth as alpha should
% vary approximately at the same rate as theta.

SkywalkerX8.Sensors.Filters.AoA.FilterBandwidthHz = SkywalkerX8.Sensors.Filters.AngularRates.Pitch.FilterBandwidthHz;

SkywalkerX8.Sensors.Filters.AoA.FilterTF = tf(SkywalkerX8.Sensors.Filters.AoA.FilterBandwidthHz*2*pi,...
                                              [1 SkywalkerX8.Sensors.Filters.AoA.FilterBandwidthHz*2*pi]);
SkywalkerX8.Sensors.Filters.AoA.FilterTF = SkywalkerX8.Sensors.Filters.AoA.FilterTF^2;
SkywalkerX8.Sensors.Filters.AoA.FilterSampleTime = 1/100;
SkywalkerX8.Sensors.Filters.AoA.FilterTFDigital = c2d(SkywalkerX8.Sensors.Filters.AoA.FilterTF, SkywalkerX8.Sensors.Filters.AoA.FilterSampleTime);


SkywalkerX8.Sensors.Filters.AoA.InitialCondition = 0;

%% Attitude Estimation EKF %%

% This section sets up our attitude estimation. This is primarily to do
% with setting up our state and measurement covariance matrices, as well as
% our sample times. Initial conditions will be set up in the initial
% conditions script, but are initialized here.

SkywalkerX8.Sensors.EKF.Attitude.NumStates  = 2; %Phi, Theta
SkywalkerX8.Sensors.EKF.Attitude.NumInputs  = 4; %p, q, r, Va
SkywalkerX8.Sensors.EKF.Attitude.NumMeasurements = 3; %ax, ay, az

SkywalkerX8.Sensors.EKF.Attitude.InitialState = zeros(SkywalkerX8.Sensors.EKF.Attitude.NumStates, 1);

% Our state standard deviations are estimated to be 5% of our maximum value
% to start with. This is a tunable parameter, however, and will be noted
% here if adjusted.

attitudePhiAngleStdDev = 0.001;
attitudeThetaAngleStdDev = 0.001;
attitudePhiThetaSqrtCovariance = 0;

SkywalkerX8.Sensors.EKF.Attitude.ProcessCovarianceMatrix = 1E-04.*[attitudePhiAngleStdDev        , attitudePhiThetaSqrtCovariance;...
                                                                   attitudePhiThetaSqrtCovariance, attitudeThetaAngleStdDev      ].^2;

% Our measurement covariance matrix is known from our sensor setup. We
% assume no covariance between measurements, and make use of variance =
% std_dev^2 to determine the diagonal elements. The kalman filter simulink
% block allows for just specifying the variance for each measurement.

SkywalkerX8.Sensors.EKF.Attitude.MeasurementCovarianceMatrix = [SkywalkerX8.Sensors.IMU.Accelerometer.X.NoiseDensity*(1/sqrt(SkywalkerX8.Sensors.IMU.Accelerometer.SampleTime)),...
                                                                SkywalkerX8.Sensors.IMU.Accelerometer.Y.NoiseDensity*(1/sqrt(SkywalkerX8.Sensors.IMU.Accelerometer.SampleTime)) ,...
                                                                SkywalkerX8.Sensors.IMU.Accelerometer.Z.NoiseDensity*(1/sqrt(SkywalkerX8.Sensors.IMU.Accelerometer.SampleTime)) ].^2;
                                                            
% The initial state covariance is in order to state our confidence on our
% initial state. Given this project - we know our initial state exactly, so
% this will just be set to 0.

SkywalkerX8.Sensors.EKF.Attitude.InitialStateCovarianceMatrix = 1E-06;

% Our sample times determine how the kalman filter operates in terms of
% state propagation period (state transition sample time) and measurement
% updates (measurement sample time). This can be done on a
% measurement-by-measurement basis if required but in this case our
% measurements all occur at the same rate as they come from a single IMU
% sampled at one rate. We assume that our state transition will be done at
% the rate of the fastest input sample rate.

SkywalkerX8.Sensors.EKF.Attitude.StateTransitionSampleTime = SkywalkerX8.Sensors.IMU.Gyroscope.SampleTime;
SkywalkerX8.Sensors.EKF.Attitude.MeasurementSampleTime = SkywalkerX8.Sensors.IMU.Accelerometer.SampleTime;

% State Estimation Output Filters 
% We setup our EKF attitude output filters.

SkywalkerX8.Sensors.EKF.Attitude.Filters.aFilterBandwidthHz = 50;
SkywalkerX8.Sensors.EKF.Attitude.Filters.aFilterSampleTime = 1/100;

SkywalkerX8.Sensors.EKF.Attitude.Filters.axFilterTF = tf((SkywalkerX8.Sensors.EKF.Attitude.Filters.aFilterBandwidthHz*2*pi)^2, [1 2*SkywalkerX8.Sensors.EKF.Attitude.Filters.aFilterBandwidthHz*2*pi (SkywalkerX8.Sensors.EKF.Attitude.Filters.aFilterBandwidthHz*2*pi)^2]);
SkywalkerX8.Sensors.EKF.Attitude.Filters.ayFilterTF = tf((SkywalkerX8.Sensors.EKF.Attitude.Filters.aFilterBandwidthHz*2*pi)^2, [1 2*SkywalkerX8.Sensors.EKF.Attitude.Filters.aFilterBandwidthHz*2*pi (SkywalkerX8.Sensors.EKF.Attitude.Filters.aFilterBandwidthHz*2*pi)^2]);
SkywalkerX8.Sensors.EKF.Attitude.Filters.azFilterTF = tf((SkywalkerX8.Sensors.EKF.Attitude.Filters.aFilterBandwidthHz*2*pi)^2, [1 2*SkywalkerX8.Sensors.EKF.Attitude.Filters.aFilterBandwidthHz*2*pi (SkywalkerX8.Sensors.EKF.Attitude.Filters.aFilterBandwidthHz*2*pi)^2]);

SkywalkerX8.Sensors.EKF.Attitude.Filters.axFilterTFDigital = c2d(SkywalkerX8.Sensors.EKF.Attitude.Filters.axFilterTF, SkywalkerX8.Sensors.EKF.Attitude.Filters.aFilterSampleTime);
SkywalkerX8.Sensors.EKF.Attitude.Filters.ayFilterTFDigital = c2d(SkywalkerX8.Sensors.EKF.Attitude.Filters.ayFilterTF, SkywalkerX8.Sensors.EKF.Attitude.Filters.aFilterSampleTime);
SkywalkerX8.Sensors.EKF.Attitude.Filters.azFilterTFDigital = c2d(SkywalkerX8.Sensors.EKF.Attitude.Filters.azFilterTF, SkywalkerX8.Sensors.EKF.Attitude.Filters.aFilterSampleTime);

% SkywalkerX8.Sensors.EKF.Attitude.Filters.PhiFilterBandwidthHz = 10/(2*pi);
% SkywalkerX8.Sensors.EKF.Attitude.Filters.ThetaFilterBandwidthHz = 10/(2*pi);
% 
% SkywalkerX8.Sensors.EKF.Attitude.Filters.PhiFilterTF = tf((SkywalkerX8.Sensors.EKF.Attitude.Filters.PhiFilterBandwidthHz*2*pi)^2, [1 2*SkywalkerX8.Sensors.EKF.Attitude.Filters.PhiFilterBandwidthHz*2*pi (SkywalkerX8.Sensors.EKF.Attitude.Filters.PhiFilterBandwidthHz*2*pi)^2]);
% SkywalkerX8.Sensors.EKF.Attitude.Filters.ThetaFilterTF = tf((SkywalkerX8.Sensors.EKF.Attitude.Filters.ThetaFilterBandwidthHz*2*pi)^2, [1 2*SkywalkerX8.Sensors.EKF.Attitude.Filters.ThetaFilterBandwidthHz*2*pi (SkywalkerX8.Sensors.EKF.Attitude.Filters.ThetaFilterBandwidthHz*2*pi)^2]);
% 
% SkywalkerX8.Sensors.EKF.Attitude.Filters.PhiFilterSampleTime = 1/100;
% SkywalkerX8.Sensors.EKF.Attitude.Filters.ThetaFilterSampleTime = 1/100;
% 
% SkywalkerX8.Sensors.EKF.Attitude.Filters.PhiFilterTFDigital = c2d(SkywalkerX8.Sensors.EKF.Attitude.Filters.PhiFilterTF, SkywalkerX8.Sensors.EKF.Attitude.Filters.PhiFilterSampleTime);
% SkywalkerX8.Sensors.EKF.Attitude.Filters.ThetaFilterTFDigital = c2d(SkywalkerX8.Sensors.EKF.Attitude.Filters.ThetaFilterTF, SkywalkerX8.Sensors.EKF.Attitude.Filters.ThetaFilterSampleTime);

%% GPS Smoothing EKF %%

% This section sets up our GPS Smoothing EKF. This is primarily to do
% with setting up our state and measurement covariance matrices, as well as
% our sample times. Initial conditions will be set up in the initial
% conditions script, but are initialized here.

SkywalkerX8.Sensors.EKF.GPSSmoothing.NumStates  = 7; %pn, pe, Vg, Chi, wn, we, Psi
SkywalkerX8.Sensors.EKF.GPSSmoothing.NumInputs  = 5; %Va, q, r, Phi, Theta
SkywalkerX8.Sensors.EKF.GPSSmoothing.NumMeasurements = 6; %yGPSn, yGPSe, yGPSVg, yGPSChi, yGPSWindN, yGPSWindE

SkywalkerX8.Sensors.EKF.GPSSmoothing.InitialState = zeros(SkywalkerX8.Sensors.EKF.GPSSmoothing.NumStates, 1);

% Our state standard deviations are estimated to be 1% of our maximum value
% to start with. This is a tunable parameter, however, and will be noted
% here if adjusted.

% We know that our GPS measurements are fairly accurate here so we can set
% our position StdDev to a reasonably large value for process because our
% measurement is going to be good.

positionStdDev = 0.01; %m
velocityStdDev = 0.01; %m/s
angleStdDev = 0.0001; %rad

SkywalkerX8.Sensors.EKF.GPSSmoothing.ProcessCovarianceMatrix =    1E03*[positionStdDev,...
                                                                  positionStdDev,...
                                                                  velocityStdDev,...
                                                                  angleStdDev   ,...
                                                                  velocityStdDev,...
                                                                  velocityStdDev,...
                                                                  angleStdDev   ].^2;

% Our measurement covariance matrix is known from our sensor setup. We
% assume no covariance between measurements, and make use of variance =
% std_dev^2 to determine the diagonal elements. The kalman filter simulink
% block allows for just specifying the variance for each measurement. It
% should be noted that the variance for Chi will be updated based on the
% estimated Vg at the previous time step. We initialise at a non-zero
% value, however, by assuming a ground speed of 10 m/s.

SkywalkerX8.Sensors.EKF.GPSSmoothing.MeasurementCovarianceMatrix = eye(SkywalkerX8.Sensors.EKF.GPSSmoothing.NumMeasurements).*...
                                                                    [SkywalkerX8.Sensors.GPS.North.StdDev      ;...
                                                                     SkywalkerX8.Sensors.GPS.East.StdDev       ;...
                                                                     SkywalkerX8.Sensors.GPS.Velocity.StdDev   ;...
                                                                     SkywalkerX8.Sensors.GPS.Velocity.StdDev/10;...
                                                                     1E-06                                     ;...
                                                                     1E-06                                     ].^2;

% The initial state covariance is in order to state our confidence on our
% initial state. Given this project - we know our initial state exactly, so
% this will just be set to 0.

SkywalkerX8.Sensors.EKF.GPSSmoothing.InitialStateCovarianceMatrix = 1E-06;

% Our sample times determine how the kalman filter operates in terms of
% state propagation period (state transition sample time) and measurement
% updates (measurement sample time). This can be done on a
% measurement-by-measurement basis if required but in this case our
% measurements all occur at the same rate as they come from a single IMU
% sampled at one rate. We assume that our state transition will be done at
% 5x the rate of the measurement sample rate from the attitude estimate
% EKF.

SkywalkerX8.Sensors.EKF.GPSSmoothing.StateTransitionSampleTime = SkywalkerX8.Sensors.EKF.Attitude.StateTransitionSampleTime;
SkywalkerX8.Sensors.EKF.GPSSmoothing.MeasurementSampleTime = SkywalkerX8.Sensors.GPS.SampleTime;

% We filter some of our output data to ensure we don't measure physically
% impossible dynamics. 

% Chi has a bandwidth of approx 1 Hz. We move the filter to 50 Hz to try to
% not interfere with dynamics but getting rid of as much noise as possible.

SkywalkerX8.Sensors.EKF.GPSSmoothing.Filters.ChiFilter.SampleTime = 1/100;
SkywalkerX8.Sensors.EKF.GPSSmoothing.Filters.ChiFilter.BandwidthHz = 0.5;
SkywalkerX8.Sensors.EKF.GPSSmoothing.Filters.ChiFilter.TF = tf(SkywalkerX8.Sensors.EKF.GPSSmoothing.Filters.ChiFilter.BandwidthHz*2*pi,...
                                                               [1 SkywalkerX8.Sensors.EKF.GPSSmoothing.Filters.ChiFilter.BandwidthHz*2*pi]);
SkywalkerX8.Sensors.EKF.GPSSmoothing.Filters.ChiFilter.TFDigital = c2d(SkywalkerX8.Sensors.EKF.GPSSmoothing.Filters.ChiFilter.TF, SkywalkerX8.Sensors.EKF.GPSSmoothing.Filters.ChiFilter.SampleTime);
SkywalkerX8.Sensors.EKF.GPSSmoothing.Filters.ChiFilter.InitialCondition = 0;

SkywalkerX8.Sensors.EKF.GPSSmoothing.Filters.PsiFilter.BandwidthHz = 0.5;
SkywalkerX8.Sensors.EKF.GPSSmoothing.Filters.PsiFilter.TF = tf(SkywalkerX8.Sensors.EKF.GPSSmoothing.Filters.PsiFilter.BandwidthHz*2*pi,...
                                                               [1 SkywalkerX8.Sensors.EKF.GPSSmoothing.Filters.PsiFilter.BandwidthHz*2*pi]);
SkywalkerX8.Sensors.EKF.GPSSmoothing.Filters.PsiFilter.InitialCondition = 0;