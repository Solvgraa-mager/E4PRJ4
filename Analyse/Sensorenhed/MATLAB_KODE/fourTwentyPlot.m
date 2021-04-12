function fourTwentyPlot(sensortype, minSensorVal, maxSensorVal, minSensorRange, maxSensorRange, accuracy, resolution, r_sense)
    minCurrent = fourtwentycalc(minSensorVal, minSensorRange, maxSensorRange);
    maxCurrent = fourtwentycalc(maxSensorVal, minSensorRange, maxSensorRange) %mA;
    minVoltage = minCurrent * r_sense;
    maxVoltage = maxCurrent * r_sense;
    ADCbits = 16;
    minVoltagePercent = minVoltage / 5;
    maxVoltagePercent = maxVoltage / 5;
    sensorRange = minSensorRange:resolution:maxSensorRange;

    ADCMIN = 2^ADCbits * minVoltagePercent;
    ADCMAX = 2^ADCbits * maxVoltagePercent;

    ADCreso = (maxVoltage - minVoltage) / (ADCMAX - ADCMIN);

    tempLength = length(sensorRange);
    currentTemp = linspace(4e-3, 20e-3, tempLength);

    fprintf("Sensorrange:            %2.4f : %2.4f [Unit]\n", minSensorRange, maxSensorRange);
    fprintf("Area of int.:           %2.4f : %2.4f [Unit]\n", minSensorVal, maxSensorVal);
    fprintf("Input current:          %2.4f : %2.4f [mA]\n", minCurrent * 1000, maxCurrent * 1000);
    fprintf("Measured voltage:       %2.4f : %2.4f [V]\n", minVoltage, maxVoltage);
    fprintf("Sensing resistor:       %d [ohm]\n", r_sense);
    fprintf("Voltage usage:          %2.2f : %2.2f [%%]\n", minVoltagePercent * 100, maxVoltagePercent * 100);
    fprintf("ADC bits:               %d \n", ADCbits);
    fprintf("ADC range:              %d : %d [count]\n", ADCMIN, ADCMAX);
    fprintf("Voltage pr. ADC count:  %f [µV] \n", ADCreso * 1e6);

    if sensortype == "Temperatur"
        sensortick = ['%g', char(176), 'C'];
        figureNum = 100;
    elseif sensortype == "pH"
        sensortick = ['%g'];
        figureNum = 200;
    elseif sensortype == "Salinitet"
        sensortick = ['%gPSU'];
        figureNum = 300;
    end

    figure(figureNum); clf;
    t = tiledlayout(2, 2, 'padding', 'compact');
    nexttile
    plot(sensorRange, currentTemp * 1000, '.')
    title(['Strøm som en funktion af: ', sensortype])
    % ylabel('Outputstrøm [mA]')
    rectangle('Position', [minSensorVal, 4, maxSensorVal - minSensorVal, 16])
    axis tight
    grid on
    grid minor
    xlim([minSensorRange, maxSensorRange])
    ylim([4, 20])
    ytickformat('%gmA')
    xtickformat(sensortick)

    nexttile
    plot(sensorRange, currentTemp * 1000, '.')
    title(['Afgrænset område for typen: ', sensortype])
    axis tight
    grid on
    grid minor
    xlim([minSensorVal, maxSensorVal])
    ylim([minCurrent * 1000, maxCurrent * 1000])
    ytickformat('%gmA')
    xtickformat(sensortick)
    nexttile([1 2])

    title(['Spændingsoutput som funktion af: ', sensortype])
    plot(sensorRange, currentTemp * r_sense, 'DisplayName', ['R_{sense} = ', num2str(r_sense), '\Omega']);
    ylabel('Spænding [V]')
    xlim([minSensorVal, maxSensorVal])
    legend('location', 'northwest')
    ytickformat('%gV')
    xtickformat(sensortick)
    grid on
    grid minor
    xlabel(t, sensortype);
end
