%% House keeping
close all; clear all; clc; 
%% Uden sleep
T_us = readtable('UdenSleep.csv');
Time_us = T_us.Time_s_+10;
Current_us = (T_us.Channel1_V_/0.5)*1000;
MA_us = movmean(Current_us,10000);
plot(Time_us,MA_us)
hold on
plot(Time_us,Current_us,'Color',[1, 0, 0, 0.02])
hold off
xlabel("Time [s]");
ylabel("Current [mA]");
title("Current for µC without sleep function");
legend("Current (MA)", "Current"); 

%% MedPowerDown
T_pd = readtable('MedPowerDown.csv');
Time_pd = T_pd.Time_s_+10;
Current_pd = (T_pd.Channel1_V_/0.5)*1000;
MA_pd = movmean(Current_pd,10000);
plot(Time_pd,MA_pd)
hold on
plot(Time_pd,Current_pd,'Color',[1, 0, 0, 0.02])
hold off
xlabel("Time [s]");
ylabel("Current [mA]");
title("Current for µC with Power Down");
legend("Current (MA)", "Current");

%% Sammenligning

plot(Time_us,MA_us)
hold on;
plot(Time_pd,MA_pd)
hold off
xlabel("Time [s]");
ylabel("Current [mA]");
title("Comparisson on sleep function");
legend("Current (MA)", "Current");
legend("Without sleep (MA)", "With Power Down (MA)", 'Location','east');