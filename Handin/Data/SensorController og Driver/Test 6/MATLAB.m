close all; clc; clear all; 

%% Load data
run = 0; value = 0; T = 0; Data = [0 0 0 0 0];
expectedValue = 0; correctRead = 0; 

for channel = 0:3
fid = fopen(['Test6Ch' num2str(channel)],'r');
tline = fgetl(fid);

    while ischar(tline)
        databyline = regexp(tline,'\d*','Match');
        if (size(databyline) > 0)
            run = str2num(databyline{1,1});
            value = str2num(databyline{1,2});
            T = str2num(databyline{1,5});
            if (mod(run,4) == channel)
                expectedValue = 4095;
            else 
                expectedValue = 0; 
            end
            correctRead = (expectedValue == value);
            Data = [Data; [channel run value T correctRead]];
        end
        tline = fgetl(fid);
    end
 fclose(fid);
  
 Data(1,:) = [];
end
 %% Plot data
 
histogram(Data(:,4))
xlabel("Time [µs]")
ylabel("Frequency")
xlim([10000 10700])
title("Read time")