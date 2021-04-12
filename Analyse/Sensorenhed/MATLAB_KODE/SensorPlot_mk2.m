clear
format short eng
set(0, ...
    'DefaultLineLineWidth', 1.5, ...
    'DefaultAxesColorOrder', [0, 0, 0], ...
    'DefaultAxesLineStyleOrder', '-|--|:');
% sensortype = 'Temperatur';
sensortype = 'pH';
% sensortype = 'Salinitet';
resolution = 0.1; % Sensor resolution
accuracy = 0.4; % Accuracy of given sensor

minSensorVal = 6; % Minimum required measurement
maxSensorVal = 8; % Maximum required measurement
minSensorRange = 0; % Defined min range of given sensor
maxSensorRange = 14; % Defined max range of given sensor

r_sense = [250]; % Measurement resistor for voltage output
fourTwentyPlot(sensortype, ...
    minSensorVal, maxSensorVal, ...
    minSensorRange, maxSensorRange, ...
    accuracy, resolution, ...
    r_sense)


