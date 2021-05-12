%Nedkolingsgraf
clear all;
% %%
% % nedkpoong af glas
% K = 0.045;
% A = 5.274;
% L = 0.394;
% BTUcon = 3.412;
% Res = zeros(15,1);
% n = zeros(15,1);
% maxWatt = 60;
% PWM = zeros(15,1);
% % fordampning
% Kon = 14.48;
% for t = 1:15
% 
%     DT = t*(9/5)+32;
%     QBTU = (K*A*DT*1.1)/L;
%     Wattloss = QBTU/BTUcon;
%     Res(t) = Wattloss+Kon
%     PWM(t) = Res(t)/maxWatt*100
% end
% 
% 
% 
% X1 = 1;
% Y1 = Res(1);
% X2 = 10;
% Y2 = Res(10);
% A1 = (Y2-Y1)/(X2-X1);
% B1 = Y1 - M * X1;
% 
% 
% 
% X11 = 1;
% Y11 = PWM(1);
% X22 = 10;
% Y22 = PWM(10);
% A11 = (Y22-Y11)/(X22-X11);
% B11 = Y11 - M * X11;
% 
% plot(Res(1:length(Res)));
% hold on
% grid on
% plot(PWM(1:length(Res)));
% legend('Watt','PWM (%)')
% xlabel('Temperatur forskel i grader c')
% ylabel ('enhed x')
%% Plot
%plot(Plast_25L(725:length(Plast_25L)));
hold on
plot(Plast_25L_21_Tilsat(1:length(Plast_25L_21_Tilsat)));
title('Nedkølingsgraf af 25L vand med 35 PSU')
xlabel('5 sekunder interval');
ylabel('Grader');
grid on
hold off

%%  Real
X = double(blanks(length(Water_Heated)).');
for i = 1:length(Water_Heated)
   X(i) = Water_Heated(i)-2;
end
%plot(Water_Heated(210:length(Water_Heated)));
plot(X(210:length(X)));
title('opvarmning af 25L vand med 35 PSU 40 Watt ( 33.33% PWM)')
xlabel('40 sekunder interval ( 1.1 time pr 100) ');
ylabel('Grader');
hold on
grid on
%%  Fake

Y = double(blanks(length(WaterHeated_Fake)).');
for i = 1:length(WaterHeated_Fake)
   Y(i) = WaterHeated_Fake(i)-1;
end
plot(Y(210:length(Y)));
%plot(WaterHeated_Fake(210:length(WaterHeated_Fake)));
title('opvarmning af 25L vand med 35 PSU 24 Watt ( 20% PWM)')
xlabel('40 sekunder interval ( 1.1 time pr 100) ');
ylabel('Grader');
grid on
hold on


%% FUCKED

% Z = double(blanks(length(Fucked)).');
% for i = 1:736
%    Z(i) = Fucked(i)-0;
% end
% 
% for i = 1400:length(Z)
%    Z(i-737) = Fucked(i)-0;
% end
% 

% plot(Z(1:length(Z)-(1400-736)));
hold on
plot(Fucked(1:length(Fucked)));
title('opvarmning af 25L vand med 35 PSU 24 Watt ( 20% PWM)')
xlabel('40 sekunder interval ( 1.1 time pr 100) ');
ylabel('Grader');
grid on