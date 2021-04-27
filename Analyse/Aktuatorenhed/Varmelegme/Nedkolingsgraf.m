%Nedkolingsgraf
clear all;
%%
% nedkpoong af glas
K = 0.045;
A = 5.274;
L = 0.394;
BTUcon = 3.412;
Res = zeros(20,1);
n = zeros(25,1);

% fordampning
Kon = 14.48;
for t = 1:25

    DT = t*(9/5)+32;
    QBTU = (K*A*DT*1.1)/L;
    Wattloss = QBTU/BTUcon;
    Res(t) = Wattloss+Kon;
end

plot(Res(1:length(Res)));


%% Plot
%%plot(Input(1191:length(Input)));
title('Nedkølingsgraf af 25L vand med 35 PSU')
xlabel('5 sekunder interval');
ylabel('Grader');
hold on
grid on
plot(Plast_25L(381:length(Plast_25L)));
hold off
