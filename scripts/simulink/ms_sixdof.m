function ms_sixdof(block)
%MSFUNTMPL A Template for a MATLAB S-Function
%   The MATLAB S-function is written as a MATLAB function with the
%   same name as the S-function. Replace 'msfuntmpl' with the name
%   of your S-function.  
%
%   It should be noted that the MATLAB S-function is very similar
%   to Level-2 C-Mex S-functions. You should be able to get more 
%   information for each of the block methods by referring to the
%   documentation for C-Mex S-functions.
%  
%   Copyright 2003-2010 The MathWorks, Inc.
  
%
% The setup method is used to setup the basic attributes of the
% S-function such as ports, parameters, etc. Do not add any other
% calls to the main body of the function.  
%   
setup(block);
  
%endfunction

% Function: setup ===================================================
% Abstract:
%   Set up the S-function block's basic characteristics such as:
%   - Input ports
%   - Output ports
%   - Dialog parameters
%   - Options
% 
%   Required         : Yes
%   C-Mex counterpart: mdlInitializeSizes
%
function setup(block)

  % Register the number of ports.
  
  % Inputs: 
  
  % Fxyz (3x1)
  % Mlmn (3x1)
  
  % Outputs:
  
  % V_inertial (3x1)
  % X_inertial (3x1)
  % Phi, Theta, Psi (Roll, pitch, yaw) (3x1)
  % Rotation matrix from inertial to body (3x3)
  % V_body (3x1)
  % Omega_body (3x1)
  % Alpha_body (3x1)
  % Acceleration_body (3x1)
  % Rotation body to intertial * Acceleration_body (3x1)
  
  % States:
  
  % p_n : Inertial north position of the system
  % p_e : Inertial east position of the system
  % p_d : Inertial down position (negative of altitude)
  % u : Body frame velocity along i^b 
  % v : Body frame velocity along j^b 
  % w : Body frame velocity along k^b
  % Phi: Roll angle in F^v2
  % Theta: Pitch angle in F^v1
  % Psi: Yaw angle in F^v
  % p : Roll rate along i^b in body frame
  % q : Pitch rate along j^b in body frame
  % r : Yaw rate along k^b in body frame
  
  block.NumInputPorts  = 2;
  block.NumOutputPorts = 9;
  
  % Set up the continuous states.
  block.NumContStates = 14;
  
  % Set up the port properties to be inherited or dynamic.
  % block.SetPreCompInpPortInfoToInherited;
  % block.SetPreCompOutPortInfoToInherited;

  % Override the input port properties.
  block.InputPort(1).DatatypeID         = 0;  % double
  block.InputPort(1).Complexity         = 'Real';
  block.InputPort(1).Dimensions         = [1, 3];
  block.InputPort(1).DirectFeedthrough  = false;
  
  block.InputPort(2).DatatypeID         = 0;  % double
  block.InputPort(2).Complexity         = 'Real';
  block.InputPort(2).Dimensions         = [1, 3];
  block.InputPort(2).DirectFeedthrough  = false;
  
  % Override the output port properties.
  block.OutputPort(1).DatatypeID        = 0; % double
  block.OutputPort(1).Complexity        = 'Real';
  block.OutputPort(1).Dimensions        = [1, 3];
  
  block.OutputPort(2).DatatypeID        = 0; % double
  block.OutputPort(2).Complexity        = 'Real';
  block.OutputPort(2).Dimensions        = [1, 3];
  
  block.OutputPort(3).DatatypeID        = 0; % double
  block.OutputPort(3).Complexity        = 'Real';
  block.OutputPort(3).Dimensions        = [1, 3];
  
  block.OutputPort(4).DatatypeID        = 0; % double
  block.OutputPort(4).Complexity        = 'Real';
  block.OutputPort(4).Dimensions        = [3, 3];
  
  block.OutputPort(5).DatatypeID        = 0; % double
  block.OutputPort(5).Complexity        = 'Real';
  block.OutputPort(5).Dimensions        = [1, 3];
  
  block.OutputPort(6).DatatypeID        = 0; % double
  block.OutputPort(6).Complexity        = 'Real';
  block.OutputPort(6).Dimensions        = [1, 3];
  
  block.OutputPort(7).DatatypeID        = 0; % double
  block.OutputPort(7).Complexity        = 'Real';
  block.OutputPort(7).Dimensions        = [1, 3];
  
  block.OutputPort(8).DatatypeID        = 0; % double
  block.OutputPort(8).Complexity        = 'Real';
  block.OutputPort(8).Dimensions        = [1, 3];
  
  block.OutputPort(9).DatatypeID        = 0; % double
  block.OutputPort(9).Complexity        = 'Real';
  block.OutputPort(9).Dimensions        = [1, 3];

  % Register the parameters.
  block.NumDialogPrms     = 6;
  
  % Dialog parameters
  % 1. Inertial initial position, [Xe Ye Ze] (3x1)
  % 2. Body frame initial velocity [u v w] (3x1)
  % 3. Initial Roll, Pitch and Yaw [phi theta psi] (3x1)
  % 4. Initial Roll rate, Pitch Rate and Yaw Rate [p q r] (3x1)
  % 5. Mass [m] (1x1)
  % 6. Inertia Matrix [Jxx Jxy Jxz; Jyx Jyy Jyz; Jzx Jzy Jzz](3x3) 
  
  block.DialogPrm(1).DatatypeID         = 0;
  block.DialogPrm(1).Complexity         = 'Real';
  block.DialogPrm(1).Dimensions         = [1, 3];
  
  block.DialogPrm(2).DatatypeID         = 0;
  block.DialogPrm(2).Complexity         = 'Real';
  block.DialogPrm(2).Dimensions         = [1, 3];
  
  block.DialogPrm(3).DatatypeID         = 0;
  block.DialogPrm(3).Complexity         = 'Real';
  block.DialogPrm(3).Dimensions         = [1, 3];
  
  block.DialogPrm(4).DatatypeID         = 0;
  block.DialogPrm(4).Complexity         = 'Real';
  block.DialogPrm(4).Dimensions         = [1, 3];
  
  block.DialogPrm(5).DatatypeID         = 0;
  block.DialogPrm(5).Complexity         = 'Real';
  block.DialogPrm(5).Dimensions         = [1, 1];
  
  block.DialogPrm(6).DatatypeID         = 0;
  block.DialogPrm(6).Complexity         = 'Real';
  block.DialogPrm(6).Dimensions         = [3, 3];
  
  % Register the sample times.
  %  [0 offset]            : Continuous sample time
  %  [positive_num offset] : Discrete sample time
  %
  %  [-1, 0]               : Inherited sample time
  %  [-2, 0]               : Variable sample time
  block.SampleTimes = [0 0];
  
  % -----------------------------------------------------------------
  % Options
  % -----------------------------------------------------------------
  % Specify if Accelerator should use TLC or call back to the 
  % MATLAB file
  block.SetAccelRunOnTLC(false);
  
  % Specify the block simStateCompliance. The allowed values are:
  %    'UnknownSimState', < The default setting; warn and assume DefaultSimState
  %    'DefaultSimState', < Same SimState as a built-in block
  %    'HasNoSimState',   < No SimState
  %    'CustomSimState',  < Has GetSimState and SetSimState methods
  %    'DisallowSimState' < Errors out when saving or restoring the SimState
  block.SimStateCompliance = 'DefaultSimState';
  
  % -----------------------------------------------------------------
  % The MATLAB S-function uses an internal registry for all
  % block methods. You should register all relevant methods
  % (optional and required) as illustrated below. You may choose
  % any suitable name for the methods and implement these methods
  % as local functions within the same file.
  % -----------------------------------------------------------------

  % -----------------------------------------------------------------
  % Register methods called at run-time
  % -----------------------------------------------------------------

    %
  % SetInputPortSamplingMode:
  %   Functionality    : Check and set input and output port 
  %                      attributes and specify whether the port is operating 
  %                      in sample-based or frame-based mode
  %   C-Mex counterpart: mdlSetInputPortFrameData.
  %   (The DSP System Toolbox is required to set a port as frame-based)
  %
  block.RegBlockMethod('SetInputPortSamplingMode', @SetInpPortFrameData);
  
  block.RegBlockMethod('Outputs', @Outputs);

  % 
  % Derivatives:
  %   Functionality    : Call to update the derivatives of the
  %                      continuous states during a simulation step.
  %   C-Mex counterpart: mdlDerivatives
  %
  block.RegBlockMethod('Derivatives', @Derivatives);
  
  % 
  % InitializeConditions:
  %   Functionality    : Call to initialize the state and the work
  %                      area values.
  %   C-Mex counterpart: mdlInitializeConditions
  % 
  block.RegBlockMethod('InitializeConditions',    @InitConditions);  
  
  %
  % PostPropagationSetup:
  %   Functionality    : Set up the work areas and the state variables. You can
  %                      also register run-time methods here.
  %   C-Mex counterpart: mdlSetWorkWidths
  %
  block.RegBlockMethod('PostPropagationSetup', @DoPostPropSetup);
  
function InitConditions(block)

    %% Initialize States

    %% Inertial Position
    block.ContStates.Data(1) = block.DialogPrm(1).Data(1);
    block.ContStates.Data(2) = block.DialogPrm(1).Data(2);
    block.ContStates.Data(3) = block.DialogPrm(1).Data(3);

    %% Body Frame Velocity
    block.ContStates.Data(4) = block.DialogPrm(2).Data(1);
    block.ContStates.Data(5) = block.DialogPrm(2).Data(2);
    block.ContStates.Data(6) = block.DialogPrm(2).Data(3);

    %% Roll, Pitch, Yaw Angle
    block.ContStates.Data(7) = block.DialogPrm(3).Data(1);
    block.ContStates.Data(8) = block.DialogPrm(3).Data(2);
    block.ContStates.Data(9) = block.DialogPrm(3).Data(3);

    %% Roll, Pitch, Yaw Velocity
    block.ContStates.Data(10) = block.DialogPrm(4).Data(1);
    block.ContStates.Data(11) = block.DialogPrm(4).Data(2);
    block.ContStates.Data(12) = block.DialogPrm(4).Data(3);
    
    %% 0-Wind Alpha Beta %%
    block.ContStates.Data(13) = atan2(block.DialogPrm(2).Data(3), block.DialogPrm(2).Data(1));
    
    if (sqrt(block.DialogPrm(2).Data(1)^2 + block.DialogPrm(2).Data(2)^2 + block.DialogPrm(2).Data(3)^2) <= 0.01)
        
        block.ContStates.Data(14) = 0;
        
    else
        
        block.ContStates.Data(14) = asin(block.DialogPrm(2).Data(2)/sqrt(block.DialogPrm(2).Data(1)^2 + block.DialogPrm(2).Data(2)^2 + block.DialogPrm(2).Data(3)^2));
        
    end
    
    %% Initialise DWork
    Jxx = block.DialogPrm(6).Data(1, 1);
    Jxy = block.DialogPrm(6).Data(1, 2);
    Jxz = block.DialogPrm(6).Data(1, 3);

    Jyx = block.DialogPrm(6).Data(2, 1);
    Jyy = block.DialogPrm(6).Data(2, 2);
    Jyz = block.DialogPrm(6).Data(2, 3);

    Jzx = block.DialogPrm(6).Data(3, 1);
    Jzy = block.DialogPrm(6).Data(3, 2);
    Jzz = block.DialogPrm(6).Data(3, 3);

    gamma =  Jxx*Jzz - Jxz^2;

    block.Dwork(1).Data(1) = Jxz*(Jxx - Jyy + Jzz)/gamma;
    block.Dwork(1).Data(2) = (Jzz*(Jzz - Jyy) + Jxz^2)/gamma;
    block.Dwork(1).Data(3) = Jzz/gamma;
    block.Dwork(1).Data(4) = Jxz/gamma;
    block.Dwork(1).Data(5) = (Jzz - Jxx)/Jyy;
    block.Dwork(1).Data(6) = Jxz/Jyy;
    block.Dwork(1).Data(7) = ((Jxx - Jyy)*Jxx + Jxz^2)/gamma;
    block.Dwork(1).Data(8) = Jxx/gamma;

    gamma_1 = block.Dwork(1).Data(1);
    gamma_2 = block.Dwork(1).Data(2);
    gamma_3 = block.Dwork(1).Data(3);
    gamma_4 = block.Dwork(1).Data(4);
    gamma_5 = block.Dwork(1).Data(5);
    gamma_6 = block.Dwork(1).Data(6);
    gamma_7 = block.Dwork(1).Data(7);
    gamma_8 = block.Dwork(1).Data(8);
    
    phi = block.DialogPrm(3).Data(1);
    theta = block.DialogPrm(3).Data(2);
    psi = block.DialogPrm(3).Data(3);

    rotationMatrix_BodyToInertial = [cos(theta)*cos(psi), sin(phi)*sin(theta)*cos(psi) - cos(phi)*sin(psi), cos(phi)*sin(theta)*cos(psi) + sin(phi)*sin(psi);
                      cos(theta)*sin(psi), sin(phi)*sin(theta)*sin(psi) + cos(phi)*cos(psi), cos(phi)*sin(theta)*sin(psi) - sin(phi)*cos(psi);
                      -sin(theta), sin(phi)*cos(theta), cos(phi)*cos(theta)];

    rotationMatrix_RollPitchYawToBody = [1, sin(phi)*tan(theta), cos(phi)*tan(theta);
                                         0, cos(phi), -sin(phi);
                                         0, sin(phi)/cos(theta), cos(phi)/cos(theta)];
    
    mass = block.DialogPrm(5).Data;
    
    fx = block.InputPort(1).Data(1);
    fy = block.InputPort(1).Data(2);
    fz = block.InputPort(1).Data(3);
    
    l  = block.InputPort(2).Data(1);
    m  = block.InputPort(2).Data(2);
    n  = block.InputPort(2).Data(3);
                                     
    u = block.DialogPrm(2).Data(1);
    v = block.DialogPrm(2).Data(2);
    w = block.DialogPrm(2).Data(3);

    p = block.DialogPrm(4).Data(1);
    q = block.DialogPrm(4).Data(2);
    r = block.DialogPrm(4).Data(3);
    
    block.Dwork(2).Data(1:3) = rotationMatrix_BodyToInertial*[u; v; w];
    block.Dwork(2).Data(4:6) = [r*v - q*w; p*w - r*u; q*u - p*v] + (1/mass)*[fx; fy; fz];
    block.Dwork(2).Data(7:9) = rotationMatrix_RollPitchYawToBody*[p; q; r];
    block.Dwork(2).Data(10:12) = [gamma_1*p*q - gamma_2*q*r; gamma_5*p*r - gamma_6*(p^2 - r^2); gamma_7*p*q - gamma_1*q*r] + [gamma_3*l + gamma_4*n; m/Jyy; gamma_4*l + gamma_8*n];
    
%endfunction

function DoPostPropSetup(block)

  %% Setup Dwork
  block.NumDworks                = 2;
  
  block.Dwork(1).Name            = 'Gamma'; 
  block.Dwork(1).Dimensions      = 8;
  block.Dwork(1).DatatypeID      = 0;
  block.Dwork(1).Complexity      = 'Real';
  block.Dwork(1).UsedAsDiscState = false;
  
  block.Dwork(2).Name            = 'Derivatives'; 
  block.Dwork(2).Dimensions      = 12;
  block.Dwork(2).DatatypeID      = 0;
  block.Dwork(2).Complexity      = 'Real';
  block.Dwork(2).UsedAsDiscState = false;
  
%endfunction


function Outputs(block)

    mass = block.DialogPrm(5).Data;
    
    gamma_1 = block.Dwork(1).Data(1);
    gamma_2 = block.Dwork(1).Data(2);
    gamma_3 = block.Dwork(1).Data(3);
    gamma_4 = block.Dwork(1).Data(4);
    gamma_5 = block.Dwork(1).Data(5);
    gamma_6 = block.Dwork(1).Data(6);
    gamma_7 = block.Dwork(1).Data(7);
    gamma_8 = block.Dwork(1).Data(8);
    
    Jyy = block.DialogPrm(6).Data(2, 2);
    
    fx = block.InputPort(1).Data(1);
    fy = block.InputPort(1).Data(2);
    fz = block.InputPort(1).Data(3);
    
    l  = block.InputPort(2).Data(1);
    m  = block.InputPort(2).Data(2);
    n  = block.InputPort(2).Data(3);
    
    u = block.ContStates.Data(4);
    v = block.ContStates.Data(5);
    w = block.ContStates.Data(6);
    
    phi = block.ContStates.Data(7);
    theta = block.ContStates.Data(8);
    psi = block.ContStates.Data(9);
    
    p = block.ContStates.Data(10);
    q = block.ContStates.Data(11);
    r = block.ContStates.Data(12);
    
    phi = wrapToPi(phi);
    theta = wrapToPi(theta);
    psi = wrapToPi(psi);
    
    alpha_lon = atan2(w, u);
    
    if (sqrt(u^2 + v^2 + w^2) >= 0.01)
       
        beta_lat = asin(v/sqrt(u^2 + v^2 + w^2));
    
    else
        
        beta_lat = 0;
        
    end
    
    
    block.ContStates.Data(7) = phi;
    block.ContStates.Data(8) = theta;
    block.ContStates.Data(9) = psi;
    
    block.ContStates.Data(13) = alpha_lon;
    block.ContStates.Data(14) = beta_lat;
    
    rotationMatrix_BodyToInertial = [cos(theta)*cos(psi), sin(phi)*sin(theta)*cos(psi) - cos(phi)*sin(psi), cos(phi)*sin(theta)*cos(psi) + sin(phi)*sin(psi);
                      cos(theta)*sin(psi), sin(phi)*sin(theta)*sin(psi) + cos(phi)*cos(psi), cos(phi)*sin(theta)*sin(psi) - sin(phi)*cos(psi);
                      -sin(theta), sin(phi)*cos(theta), cos(phi)*cos(theta)];
    
    block.OutputPort(1).Data = block.Dwork(2).Data(1:3)';
    block.OutputPort(2).Data = block.ContStates.Data(1:3)';
    block.OutputPort(3).Data = block.ContStates.Data(7:9)';
    block.OutputPort(4).Data = rotationMatrix_BodyToInertial';
    block.OutputPort(5).Data = block.ContStates.Data(4:6)';
    block.OutputPort(6).Data = block.ContStates.Data(10:12)';
    block.OutputPort(7).Data = [gamma_1*p*q - gamma_2*q*r; gamma_5*p*r - gamma_6*(p^2 - r^2); gamma_7*p*q - gamma_1*q*r]'...
                                    + [gamma_3*l + gamma_4*n; m/Jyy; gamma_4*l + gamma_8*n]';
    block.OutputPort(8).Data = [r*v - q*w; p*w - r*u; q*u - p*v]' + (1/mass)*[fx; fy; fz]';
    block.OutputPort(9).Data = (1/mass)*[fx; fy; fz]';
  
%endfunction

function Derivatives(block)
    
    mass = block.DialogPrm(5).Data;
    
    gamma_1 = block.Dwork(1).Data(1);
    gamma_2 = block.Dwork(1).Data(2);
    gamma_3 = block.Dwork(1).Data(3);
    gamma_4 = block.Dwork(1).Data(4);
    gamma_5 = block.Dwork(1).Data(5);
    gamma_6 = block.Dwork(1).Data(6);
    gamma_7 = block.Dwork(1).Data(7);
    gamma_8 = block.Dwork(1).Data(8);
    
    Jyy = block.DialogPrm(6).Data(2, 2);
    
    fx = block.InputPort(1).Data(1);
    fy = block.InputPort(1).Data(2);
    fz = block.InputPort(1).Data(3);
    
    l  = block.InputPort(2).Data(1);
    m  = block.InputPort(2).Data(2);
    n  = block.InputPort(2).Data(3);
    
    u = block.ContStates.Data(4);
    v = block.ContStates.Data(5);
    w = block.ContStates.Data(6);
    
    phi = block.ContStates.Data(7);
    theta = block.ContStates.Data(8);
    psi = block.ContStates.Data(9);
    
    p = block.ContStates.Data(10);
    q = block.ContStates.Data(11);
    r = block.ContStates.Data(12);
    
    rotationMatrix_BodyToInertial = [cos(theta)*cos(psi), sin(phi)*sin(theta)*cos(psi) - cos(phi)*sin(psi), cos(phi)*sin(theta)*cos(psi) + sin(phi)*sin(psi);
                      cos(theta)*sin(psi), sin(phi)*sin(theta)*sin(psi) + cos(phi)*cos(psi), cos(phi)*sin(theta)*sin(psi) - sin(phi)*cos(psi);
                      -sin(theta), sin(phi)*cos(theta), cos(phi)*cos(theta)];
    
    rotationMatrix_RollPitchYawToBody = [1, sin(phi)*tan(theta), cos(phi)*tan(theta);
                                         0, cos(phi), -sin(phi);
                                         0, sin(phi)/cos(theta), cos(phi)/cos(theta)];
                  
    block.Derivatives.Data(1:3) = rotationMatrix_BodyToInertial*[u; v; w];
    block.Derivatives.Data(4:6) = [r*v - q*w; p*w - r*u; q*u - p*v] + [fx; fy; fz]*(1/mass);
    block.Derivatives.Data(7:9) = rotationMatrix_RollPitchYawToBody*[p; q; r];
    block.Derivatives.Data(10:12) = [gamma_1*p*q - gamma_2*q*r; gamma_5*p*r - gamma_6*(p^2 - r^2); gamma_7*p*q - gamma_1*q*r]...
                                    + [gamma_3*l + gamma_4*n; m/Jyy; gamma_4*l + gamma_8*n];
    block.Derivatives.Data(13:14) = 0;
    block.Dwork(2).Data = block.Derivatives.Data(1:12);
    
%endfunction

function SetInpPortFrameData(block, idx, fd)
  
  block.InputPort(idx).SamplingMode = fd;
  block.OutputPort(1).SamplingMode  = fd;
  block.OutputPort(2).SamplingMode  = fd;
  block.OutputPort(3).SamplingMode  = fd;
  block.OutputPort(4).SamplingMode  = fd;
  block.OutputPort(5).SamplingMode  = fd;
  block.OutputPort(6).SamplingMode  = fd;
  block.OutputPort(7).SamplingMode  = fd;
  block.OutputPort(8).SamplingMode  = fd;
  block.OutputPort(9).SamplingMode  = fd;
  
%endfunction