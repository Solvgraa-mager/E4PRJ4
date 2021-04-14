%Nedkolingsgraf
%load('Input_26_25');
%load('Input5LGlas');
load('Input_5_glas');
load('Plast_25L');


%% Plot
%%plot(Input(1191:length(Input)));
title('Nedkølingsgraf af 25L vand med 35 PSU')
xlabel('5 sekunder interval');
ylabel('Grader');
hold on
grid on
plot(Plast_25L(381:length(Plast_25L)));
hold off

%% Plot fuld
%%plot(Input);
xlabel('5 sekunder interval');
ylabel('Grader');
yline(36);
yline(35);
yline(34);
yline(33);
yline(32);
yline(31);
yline(30);
yline(29);
yline(28);
yline(27);
yline(26);
yline(25);
hold on
plot(Plast_25L);
