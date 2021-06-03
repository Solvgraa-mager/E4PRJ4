%% House keeping
close all; clear all; clc;
%% Load data
T = readtable('Overforselstid.csv');
TZoom = readtable('OverforselstidZoom.csv');

Time = (T.Time_s_+0.051189643652561)*1000;
TimeZoom = (TZoom.Time_s_+0.005118992207245)*1000;

%% Plot
figure(1)
plot(Time,T.Channel1_V_);
xlabel("Time [mS]");
ylabel("Voltage [V]");
title("Request Execution Time")
xlim([0 102])

figure(2)
plot(TimeZoom, TZoom.Channel1_V_);
xlabel("Time [mS]");
ylabel("Voltage [V]");
title("Request execution time (Single)")
xlim([0 10])