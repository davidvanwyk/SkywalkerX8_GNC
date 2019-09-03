%% Sensor Setup %%

% This script is developed to set up each of the sensors used in the model.

%% GPS Setup %%

% We use the setup parameters from R. W. Beard, T. W. McLain, Small
% Unmanned Aircraft: Theory and Practice to get our GPS model. This makes
% use of a Gauss Markhov process, as per J. Rankin, "GPS and differential
% GPS: An error model for sensor simulation".

SkywalkerX8.Sensors.GPS.SampleTime = 1/5; %Expect GPS sample time of 5 Hz, as per VN-200 as an example
SkywalkerX8.Sensors.GPS.pnInit = 0;
SkywalkerX8.Sensors.GPS.peInit = 0; 
SkywalkerX8.Sensors.GPS.pdInit = -50; 

SkywalkerX8.Sensors.GPS.North.StdDev = 0.21; % m
SkywalkerX8.Sensors.GPS.North.TimeConstant = 1100; % s

SkywalkerX8.Sensors.GPS.East.StdDev = 0.21; % m
SkywalkerX8.Sensors.GPS.East.TimeConstant = 1100; % s

SkywalkerX8.Sensors.GPS.Alt.StdDev = 0.4; % m
SkywalkerX8.Sensors.GPS.Alt.TimeConstant = 1100; % s

SkywalkerX8.Sensors.GPS.Velocity.StdDev = 0.05/4; %m/s (VN-200 gives a velocity error band of +- 0.05m/s, we tread this as 4-sigma).

%% IMU Setup %%

% We use setup parameters from an Invensense MPU6000, as is used by the
% Pixhawk, for the accelerometers and gyros.

%% Accelerometer %%

% We will assume a sample time of 100 Hz - this should provide a reasonable
% separation between GPS sample time and IMU sample time. 

SkywalkerX8.Sensors.IMU.Accelerometer.SampleTime = 1/100;

SkywalkerX8.Sensors.IMU.Accelerometer.X.NoiseDensity = 400*1E-06*9.81; % Datasheet gives spec in ug, so we scale to m/s^2.
SkywalkerX8.Sensors.IMU.Accelerometer.Y.NoiseDensity = 400*1E-06*9.81; % Datasheet gives spec in ug, so we scale to m/s^2.
SkywalkerX8.Sensors.IMU.Accelerometer.Z.NoiseDensity = 400*1E-06*9.81; % Datasheet gives spec in ug, so we scale to m/s^2.

% Bandwidth is programmable to < 260 Hz. We specify this as 200 Hz given
% that our sample time is 100 Hz, so we want to be well above the nyquist
% frequency with our sampling rate so we filter this down to 20 Hz, meaning
% our sample frequency is 5x the bandwidth. We also know that we filter our
% measurments down to 2 Hz in order to avoid actuator issues in the
% controller, so this should be sufficiently far enough away from that to
% introduce issues.

SkywalkerX8.Sensors.IMU.Accelerometer.X.BandwidthHz = 20;
SkywalkerX8.Sensors.IMU.Accelerometer.Y.BandwidthHz = 20;
SkywalkerX8.Sensors.IMU.Accelerometer.Z.BandwidthHz = 20;

% Initial conditions of the sensor (these will be set up in the initial
% conditions script)

SkywalkerX8.Sensors.IMU.Accelerometer.X.InitialCondition = 0;
SkywalkerX8.Sensors.IMU.Accelerometer.Y.InitialCondition = 0;
SkywalkerX8.Sensors.IMU.Accelerometer.Z.InitialCondition = 0;

% Saturation Limits (assume maximum saturation limits of the MPU6000)

SkywalkerX8.Sensors.IMU.Accelerometer.X.UpperSat = 16*9.81;
SkywalkerX8.Sensors.IMU.Accelerometer.X.LowerSat = -16*9.81;

SkywalkerX8.Sensors.IMU.Accelerometer.Y.UpperSat = 16*9.81;
SkywalkerX8.Sensors.IMU.Accelerometer.Y.LowerSat = -16*9.81;

SkywalkerX8.Sensors.IMU.Accelerometer.Z.UpperSat = 16*9.81;
SkywalkerX8.Sensors.IMU.Accelerometer.Z.LowerSat = -16*9.81;

% Resolution (specified in LSB/g, so invert and multiply by g (assumed
% 9.81)

SkywalkerX8.Sensors.IMU.Accelerometer.X.Resolution = 9.81/2048;
SkywalkerX8.Sensors.IMU.Accelerometer.Y.Resolution = 9.81/2048;
SkywalkerX8.Sensors.IMU.Accelerometer.Z.Resolution = 9.81/2048;

%% Gyroscope %%

% We will assume a sample time of 100 Hz - this should provide a reasonable
% separation between GPS sample time and IMU sample time. 

SkywalkerX8.Sensors.IMU.Gyroscope.SampleTime = 1/100;

SkywalkerX8.Sensors.IMU.Gyroscope.X.NoiseDensity = deg2rad(0.005); % Datasheet gives spec in deg/s, so we scale to rad/s.
SkywalkerX8.Sensors.IMU.Gyroscope.Y.NoiseDensity = deg2rad(0.005); % Datasheet gives spec in deg/s, so we scale to rad/s.
SkywalkerX8.Sensors.IMU.Gyroscope.Z.NoiseDensity = deg2rad(0.005); % Datasheet gives spec in deg/s, so we scale to rad/s.

% Bandwidth is programmable to < 260 Hz. We specify this as 200 Hz given
% that our sample time is 100 Hz, so we want to be well above the nyquist
% frequency with our sampling rate so we filter this down to 20 Hz, meaning
% our sample frequency is 5x the bandwidth. We also know that we filter our
% measurments down to 2 Hz in order to avoid actuator issues in the
% controller, so this should be sufficiently far enough away from that to
% introduce issues.

SkywalkerX8.Sensors.IMU.Gyroscope.X.BandwidthHz = 20;
SkywalkerX8.Sensors.IMU.Gyroscope.Y.BandwidthHz = 20;
SkywalkerX8.Sensors.IMU.Gyroscope.Z.BandwidthHz = 20;

% Initial conditions of the sensor (these will be set up in the initial
% conditions script)

SkywalkerX8.Sensors.IMU.Gyroscope.X.InitialCondition = 0;
SkywalkerX8.Sensors.IMU.Gyroscope.Y.InitialCondition = 0;
SkywalkerX8.Sensors.IMU.Gyroscope.Z.InitialCondition = 0;

% Saturation Limits (assume maximum saturation limits of the MPU6000)

SkywalkerX8.Sensors.IMU.Gyroscope.X.UpperSat = deg2rad(2000);
SkywalkerX8.Sensors.IMU.Gyroscope.X.LowerSat = deg2rad(-2000);

SkywalkerX8.Sensors.IMU.Gyroscope.Y.UpperSat = deg2rad(2000);
SkywalkerX8.Sensors.IMU.Gyroscope.Y.LowerSat = deg2rad(-2000);

SkywalkerX8.Sensors.IMU.Gyroscope.Z.UpperSat = deg2rad(2000);
SkywalkerX8.Sensors.IMU.Gyroscope.Z.LowerSat = deg2rad(-2000);

% Resolution (specified in LSB/g, so invert and multiply by g (assumed
% 9.81)

SkywalkerX8.Sensors.IMU.Gyroscope.X.Resolution = deg2rad(1/16.4);
SkywalkerX8.Sensors.IMU.Gyroscope.Y.Resolution = deg2rad(1/16.4);
SkywalkerX8.Sensors.IMU.Gyroscope.Z.Resolution = deg2rad(1/16.4);

%% Magnetometer/Compass %%

% We use the VectorNav VN-200 to get an idea of accuracy for an available
% COTS compass. This provides error as RMS, we assume this is a 1 sigma
% measurement at the rate available from the IMU (800 Hz).

SkywalkerX8.Sensors.IMU.Compass.SampleTime = 1/100;

SkywalkerX8.Sensors.IMU.Compass.NoiseDensity = deg2rad(2)/sqrt(800);

SkywalkerX8.Sensors.IMU.Compass.BandwidthHz = 20;
SkywalkerX8.Sensors.IMU.Compass.InitialCondition = 0;

SkywalkerX8.Sensors.IMU.Compass.UpperSat = deg2rad(180);
SkywalkerX8.Sensors.IMU.Compass.LowerSat = deg2rad(-180);

SkywalkerX8.Sensors.IMU.Compass.Resolution = deg2rad(0.05); 

%% Airspeed Pressure Sensor %%

% Airspeed differential pressure sensor (pitot tube). The differential
% pressure sensor is the TE MS4525DO, which is used on the Pixhawk airspeed
% sensor interface. This can be seen here: 

% http://store.jdrones.com/digital_airspeed_sensor_p/senair02kit.htm

% Given that this sensor has a range of 1 psi, we use Bernouli as the 
% following:

% dP = 0.5*rho*Va^2 

% 6894.76 = 0.5*rho*Va^2

% Assuming rho is constant; rho = 1.225 kg/m^3

% Va = 106.1 m/s

SkywalkerX8.Sensors.AirspeedPressure.SampleTime = 1/100;

% From the sensor datasheet we know that the error is +- 1% span. With 1% of
% our range (6894.76 Pa), 0.01 psi (68.9476 Pa), we generate the following. 
% We assume 1% of this error band for the noise. 

SkywalkerX8.Sensors.AirspeedPressure.StdDev = (1/4)*6894.76*0.01*0.01;

% Sensor dynamics are assumed to be 0.5 x the maximum update rate of the
% sensor, and then handled internally depending on how fast one samples
% (ie. as long as we sample slower than the maximum sample rate, we can
% assume an equivalent dynamic of the nyquist frequency)

SkywalkerX8.Sensors.AirspeedPressure.BandwidthHz = 50;

% Initial condition will be assumed 0, unless otherwise defined in initial
% conditions

SkywalkerX8.Sensors.AirspeedPressure.InitialCondition = 0;

% Limits, as per sensor spec:

SkywalkerX8.Sensors.AirspeedPressure.UpperSat = 6894.76; %Pa
SkywalkerX8.Sensors.AirspeedPressure.LowerSat = 0; %Pa

% IC has an output pressure resolution of 14 bits

SkywalkerX8.Sensors.AirspeedPressure.Resolution = SkywalkerX8.Sensors.AirspeedPressure.UpperSat/(2^14 - 1);

%% Barometric Altitude Pressure Sensor %%

% Barometer sensor setup is as per BMP280 barometric pressure sensor,
% commonly used by the Pixhawk. 

SkywalkerX8.Sensors.AltitudePressure.SampleTime = 1/100;

% Std Dev is calculated as treating total error band at 4 sigma. We assume
% our noise is 1% of this.

SkywalkerX8.Sensors.AltitudePressure.StdDev = 1.3;

% Bandwidth is assumed to be handled correctly internal to the device, as
% such, we just put this at the Nyquist Frequency of our sample time.

SkywalkerX8.Sensors.AltitudePressure.BandwidthHz = 50;

% Initial condition assumed 0, but adjusted in initial conditions

SkywalkerX8.Sensors.AltitudePressure.InitialCondition = 0;

% Upper and lower saturation limits for the absolute pressure sensor

SkywalkerX8.Sensors.AltitudePressure.UpperSat = 1200*100; %Scaled from mBar
SkywalkerX8.Sensors.AltitudePressure.LowerSat = 0;

% Resolution is given by the datasheet and is dependent on OSR.

SkywalkerX8.Sensors.AltitudePressure.Resolution = 0.16;

%% Angle of Attack %%

% Angle of attack sensor setup is as per http://www.swiss-airdata.com/products/smv1.

% Maximum sample time is 100 Hz

SkywalkerX8.Sensors.AoA.SampleTime = 1/100;

% We assume that our 3 LSBs are noisy. As such, 7x our resolution:

SkywalkerX8.Sensors.AoA.StdDev = deg2rad(7*0.025);

% Bandwidth is assumed to be handled correctly internal to the device, as
% such, we just put this at the Nyquist Frequency of our sample time.

SkywalkerX8.Sensors.AoA.BandwidthHz = 50;

% Initial condition assumed 0, but adjusted in initial conditions

SkywalkerX8.Sensors.AoA.InitialCondition = 0;

% AoA sensor can be between -180 -> 180 degrees.

SkywalkerX8.Sensors.AoA.UpperSat = deg2rad(180); 
SkywalkerX8.Sensors.AoA.LowerSat = deg2rad(-180);

% As per the sensor datasheet

SkywalkerX8.Sensors.AoA.Resolution = deg2rad(0.025);