VREF = 2.5; % Volt
r_sense = 250; % ohm
n = 10;
bitCount = 2^n; % counts

stepSize = VREF / bitCount; % Volt
% volt

voltageArray = zeros(n, 1); % voltage array for ADC steps

    fprintf("ADC bit count &  %d  &\\\\ \n",n);
    fprintf("VREF &           %.1d  & [V]\\\\ \n",VREF);
    fprintf("Stepsize   &     %f& [mV] \\\\ \n",stepSize*1e3);



minStepSize = [3.2e-3,8e-3];

optimalBitCount = VREF./minStepSize ;

ceil(log2(optimalBitCount));




for idx = 1:n
    voltageArray(idx) = [stepSize];
    fprintf("Bit %02d &         %02.2f  &  [mV]\\\\\n", idx - 1, stepSize * 1000);
    stepSize = stepSize * 2;
end
