function plant = setup_Aerodynamics(plant)

%% Aerodynamic Coeffecient Arrays %%

plant.Aerodynamics.CD = [0.0197, 0.0791, 1.06, 0, 0.148, -0.00584, 0.0633]; %Drag coefficient array
plant.Aerodynamics.CY = [0, -0.224, -0.1172, 0.0959, 0.0433]; %Sideforce coefficient array
plant.Aerodynamics.CL = [0.0867, 4.02, 3.8954, 0.278]; %Lift coefficient array
plant.Aerodynamics.Cl = [0, -0.0849, -0.4018, 0.025, 0.12]; %Roll coefficient array
plant.Aerodynamics.Cm = [0.0302, -0.126, -1.3047, -0.206]; %Pitch coefficient array
plant.Aerodynamics.Cn = [0, 0.0283, -0.0247, -0.1252, -0.00339]; %Yaw coefficient array

%% Aerodynamic Stall Modelling %%

plant.Aerodynamics.alpha_0 = 0.267;
plant.Aerodynamics.M = 50;
plant.Aerodynamics.Cmfp = -0.2168;

end