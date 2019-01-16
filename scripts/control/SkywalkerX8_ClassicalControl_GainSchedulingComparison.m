%% Gain Scheduled Controller Comparison %%

% The purpose of this file is to perform a comparison between a single 
% classical controller and a gain scheduled set of controllers.  

%% User Inputs: Flight Envelope Points to Review %%

% We input which points on the flight envelope we would like to review.
% This will look at the "corner points" of the envelope, as well as a
% central point and is aimed at illustrating the trends in system
% performance as a function of altitude and Va (and the associated trim
% parameters for each altitude/Va combination).

% Note: We scale the Va and Altitude points slightly so that they are 100%
% within the flight envelope and aren't marginal in terms of trim.