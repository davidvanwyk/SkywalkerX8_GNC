Guidance, Navigation & Control of a Small, Unmanned Blended Wing Body Aircraft
==============================================================================

This repository contains all of the MATLAB/Simulink scripts and models used in the development of a full GNC suite for a Skywalker X8 aircraft. This was performed as part of the research for an MSc. at UCT (Univeristy of Cape Town) in South Africa named Guidance, Navigation and Control of a Small, Unmanned Blended Wing Body Aircraft - the dissertation of which can be found here: https://open.uct.ac.za/handle/11427/32426. 

Instructions
------------

Using this work should be fairly trivial. Should one wish to start from a working point, simply load the SkywalkerX8.mat file. This will also be done automatically if the Masters.prj file is loaded within MATLAB to open the Simulink project, which should also handle all required project pathing.

System setup
############

If not using the .mat file, run from scripts/setup:

1. setup_Skywalker.m
2. setup_Actuators.m
3. setup_Sensors.m
4. SkywalkerX8_Longitudinal_AltitudeStateMachine_Setup.m
5. SkywalkerX8_InitialConditions.m (this can be adjusted at the user's discretion)


Performance Calculation
#######################

This allows one to characterise the performance of the airframe and can be used by running the following in the corresponding order:

In scripts/performance

1. SkywalkerX8_FlightEnvelope.m
2. SkywalkerX8_FlightEnvelopePerformanceModes.m

This should output a flight envelope with the corner points used to show some performance characteristics

Autopilot Design
################

The autopilot is designed in 2 steps.

1. Longitudinal Autopilot Design
2. Lateral Autopilot Design

Note that this applies to both the continuous and digital autopilots so simply append "_Digital" to the file names mentioned should you wish to tune the digital controllers.

For the longitudinal autopilot simply run:

In scripts/control/Longitudinal

1. SkywalkerX8_Longitudinal_Linearization_VaAlpha.m (either for continuous or digital - no change)
2. SkywalkerX8_Longitudinal_Linearization_Va.m (either for continuous or digital - no change)
3. SkywalkerX8_Longitudinal_ControlDesign_VaAlpha.m
4. SkywalkerX8_Longitudinal_ControlDesign_Va.m

For the lateral autopilot simply run:

In scripts/control/Lateral

1. SkywalkerX8_Lateral_Linearization_Va.m
2. SkywalkerX8_Lateral_ControlDesign_Va.m

State Estimation
################

In scripts/control/StateEstimation

1. setup_StateEstimation.m

Guidance and Navigation
#######################

In scripts/guidance

1. setup_GuidanceAndNavigation.m

NOTE: Please review the models folder should you wish to perform verification runs (models denoted with _Verification are used for this purpose). Also feel free to play around with controller tuning goals depending on your application.

The figures provided are the performance given by the GNC system as implemented in the .mat file provided (albeit with adjusted initial conditions).
