function plant = setup_Aerodynamics(plant)

%% Aerodynamic Coeffecient Arrays %%

plant.Aerodynamics.CD = [0.0197, 0.0791, 1.06, 0, 0.148, -0.00584, 0.0633]; %Drag coefficient array. CD0, CDalpha, CDalpha^2, CDde, CDq, CDbeta^2, CDbeta
plant.Aerodynamics.CY = [0, -0.224, -0.1172, 0.0959, 0.0433]; %Sideforce coefficient array. CY0, CYbeta, CYp, CYr, CYda
plant.Aerodynamics.CL = [0.0867, 4.02, 3.8954, 0.278]; %Lift coefficient array. CL0, CLalpha, CLq, CLde
plant.Aerodynamics.Cl = [0, -0.0849, -0.4018, 0.025, 0.12]; %Roll coefficient array. Cl0, Clbeta, Clp, Clr, Clda
plant.Aerodynamics.Cm = [0.0302, -0.126, -1.3047, -0.206]; %Pitch coefficient array. Cm0, Cmalpha, Cmq, Cmde
plant.Aerodynamics.Cn = [0, 0.0283, -0.0247, -0.1252, -0.00339]; %Yaw coefficient array. Cn0, Cnbeta, Cnp, Cnr, Cnda

%% Aerodynamic Stall Modelling %%

plant.Aerodynamics.alpha_0 = 0.267;
plant.Aerodynamics.M = 50;
plant.Aerodynamics.Cmfp = -0.2168;

end