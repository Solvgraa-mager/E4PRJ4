%% Housekeeping
clear all; close all; clc; 
%% Load data
expectedDataPwm = 1:254;
expectedDataValue = expectedDataPwm * (4037/254)
%Plot data
plot(expectedDataPwm,expectedDataValue)
hold on
for channel = 0:3
    fid = fopen(['Test3Ch' num2str(channel)],'r');
    tline = fgetl(fid);
    pwm = 0; value = 0; Data = [0 0];
    while ischar(tline)
        databyline = regexp(tline,'\d*','Match');
        pwm = str2num(databyline{1,1})
        value = str2num(databyline{1,2})
        Data = [Data; [pwm value]]
        tline = fgetl(fid);
    end
    fclose(fid);

    plot(Data(:,1),Data(:,2),'.')
    title('Test 3, Comparison ');
    xlabel("PWM value")
    ylabel("Voltage [V]")
end
hold off
legend("Expected", "Ch0", "Ch1", "Ch2", "Ch3",'Location','northwest')
