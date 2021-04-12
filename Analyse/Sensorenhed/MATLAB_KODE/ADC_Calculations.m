clear
format short eng
set(0, ...
    'DefaultLineLineWidth', 1.5, ...
    'DefaultAxesColorOrder', [0 0 0], ...
    'DefaultAxesLineStyleOrder', '-|--|:|-.');

n = [6, 8, 10, 11, 12, 16];

VREF = 2.5;
bitCount = (2.^n)'
VSS = 0;
ADCresolution = (VREF) ./ bitCount;
readValue = [21, 30];
lsv = -5;
hsv = 45;
readDiff = readValue(2) - readValue(1);
% inputVoltage = 0:5
inputReadingMin = fourtwentycalc(min(readValue), lsv, hsv);
inputReadingMax = fourtwentycalc(max(readValue), lsv, hsv);
r_sense = 100;
inputVoltageMin = inputReadingMin * r_sense
inputVoltageMax = inputReadingMax * r_sense

minVoltagePercent = inputVoltageMin / VREF;
maxVoltagePercent = inputVoltageMax / VREF;

figure(8000); clf;
tiledlayout(ceil(length(bitCount) / 2), (ceil(length(bitCount) / 4)))

for idx = 1:length(bitCount)
    nexttile

    voltageVect = [inputVoltageMin:ADCresolution(idx):inputVoltageMax];
    voltageVect = [readVal(1):ADCresolution(idx):inputVoltageMax];

    digitalValue = (voltageVect / VREF) .* (bitCount(idx) - 1);
    readVector = linspace(readValue(1),readValue(2),length((digitalValue)));
    stairs(voltageVect, digitalValue, '-k');
    title({['ADC bitcount: ', num2str(n(idx))], ...
            [' ADC Resolution: ', num2str(ADCresolution(idx) * 1000), 'mV pr. step']})
    xlabel('Spænding [V]')
    ylabel('Digital værdi')
    ax = gca;
    ax.YAxis.Exponent = 0;
    % set(gca, 'YTickLabel', cellstr(num2str(reshape(get(gca, 'YTick'), [], 1), '%02x')))
    xlim([inputVoltageMin inputVoltageMax])
    grid on
    grid minor
    % ylim([readValue(1) readValue(2)])
    % ytickformat(['%g', char(176), 'C'])
end
