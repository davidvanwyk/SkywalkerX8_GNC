function plant = setup_SystemCharacteristics(plant)

plant.System.Mass = 3.364; %Mass of the system (kg)
plant.System.InertiaTensor = [1.229 0 0.9343; 0 0.1702 0; 0.9343 0 0.8808]; %Inertia Tensor (kg.m^2)
plant.System.Gravity = 9.81; %Gravitational acceleration (m/s^2)

end