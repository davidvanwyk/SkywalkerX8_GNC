function [r, qOut, c, rho, lambda, flag, i] = pathManager_followWaypointsFillet(W, WChangeCheck, p, R, prev_state, prev_i)

%% Setup

% Inputs are all in inertial co-ordinates

% Variables

% W = Waypoint path (array of Waypoints arrays) [W1, W2, W3... WN] (Note 1
% indexed)
% Where:
% WN = [WNn, WNe, WNd] (m)
% Wprev = Previous Waypoint path (to check if the Waypoint path has been
% changed sinced the last iteration)
% p = current aircraft location [pn, pe, pd] (m)
% R = radius of the orbit we want to follow (m)

% Outputs

% flag = straight line or orbit folloWing (1 = straight line, 2 = orbit
% folloWing)
% r = origin of the path [rn, re, rd] (m)
% q = desired course path (unit vector) [qn, qe, qd] (m)
% c = center of the orbit We Want to folloW [cn, ce, cd] (m)
% rho = radius of the orbit We Want to folloW (m)
% lambda = direction of the orbin We Want to folloW (+1 clockWise, -1 counter-clockWise)

state = prev_state;
i = prev_i;

r = zeros(3, 1);
qOut = zeros(3, 1);
c = zeros(3, 1);
travPlaneNormal = zeros(3, 1);
travPlanePoint = zeros(3, 1);
x = 0;
y = 0;
h_c = 0;
rho = 0;
lambda = 0;
flag = 0;

q = zeros(3, 1, size(W, 3));
lengths = zeros(size(W, 3), 1);
N = size(W, 3);

if (i + 1) > N
   iPlusOne = (i + 1) - N + 1; 
else 
   iPlusOne = i + 1;
end

if not(WChangeCheck)
   for k = 1:length(size(W, 3))
    lengths(k) = norm(W(:, :, k) - p);
   end
   [~, ibuff] = min(lengths); 
   i = min(ibuff) - 1;
   state = 1;
else

if norm( W(:, :, i) - W(:, :, i - 1) ) >= 1E-06
    q(:, :, i - 1) = ( W(:, :, i) - W(:, :, i - 1) )/norm( W(:, :, i) - W(:, :, i - 1) );
else
    q(:, :, i - 1) = zeros(3, 1);
end

if norm( W(:, :, iPlusOne) - W(:, :, i) ) >= 1E-06
    q(:, :, i) = ( W(:, :, iPlusOne) - W(:, :, i) )/norm( W(:, :, iPlusOne) - W(:, :, i) );
else
    q(:, :, i) = zeros(3, 1);
end

fillAngle = acos(-q(:, :, i - 1)'*q(:, :, i));

if state == 1
   
    flag = 1;
    r = W(:, :, i - 1);
    qOut = q(:, :, i - 1);
    z = W(:, :, i) - (R/tan(fillAngle/2))*q(:, :, i - 1);
    
    if halfPlaneCheck(p, z, q(:, :, i - 1))
       
        flag = 2;
        
    end
    
else %if state == 2
   
    flag = 2;
    
    if norm( q(:, :, i - 1) - q(:, :, i) ) >= 1E-06
        c = W(:, :, i) - (R/sin(fillAngle/2))*( q(:, :, i - 1) - q(:, :, i) )/norm( q(:, :, i - 1) - q(:, :, i) );
    else
        c = W(:, :, i);
    end
    
    % In order to make our transition between line segments more graceful,
    % we generate a plane between line segments and use our current
    % position to determine what our ideal position should be to remain on
    % this plane. We do this by making use of the standard equation:
    
    % m(x - x0) + n(y - y0) + o(z - z0) = 0
    
    % Where a, b and c make up our normal vector and x0, y0 and z0 makes up
    % a point on the plane (which we know is c.
    
    travPlaneNormal = cross(q(:, :, i), q(:, :, i - 1));
    travPlanePoint = W(:, :, i);
    
    m = travPlaneNormal(1);
    n = travPlaneNormal(2);
    o = travPlaneNormal(3);
    
    x0 = travPlanePoint(1);
    y0 = travPlanePoint(2);
    z0 = travPlanePoint(3);
    
    x = p(1);
    y = p(2);
    
    Neg_h_c = ((m*(x0 - x) + n*(y0 - y))/o + z0); %negative because conversion to alt takes place in orbit block
    
    c(3, 1) = Neg_h_c; 
    
    if q(3, :, i - 1) > 0 %We're ascending
        
        if ( c(3,1) >= W(3, :, i) ) && ( q(3, :, i) == 0 ) %If we're above the next required altitude and the next line segment is an altitude hold segment
           
            c(3, 1) = W(3, :, i);
            
        end
        
    end
    
    if q(3, :, i - 1) < 0 %We're descending

        if ( c(3,1) <= W(3, :, i) ) && ( q(3, :, i) == 0 ) %If we're below the next required altitude and the next line segment is an altitude hold segment

            c(3, 1) = W(3, :, i);

        end
        
    end
    
    rho = R;
    lambda = sign(q(1, 1, i - 1)*q(2, 1, i) - q(2, 1, i - 1)*q(1, 1, i));
    z = W(:, :, i) + R/tan(fillAngle/2)*q(:, :, i);
    
    if halfPlaneCheck(p, z, q(:, :, i))
        
        i = i + 1;
        
        if i > N
           i = 2;
        end
        
        state = 1;
        flag = 1;
        
    end
    
end

end