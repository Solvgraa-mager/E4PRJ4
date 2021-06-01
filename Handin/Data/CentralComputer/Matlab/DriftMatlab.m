clc;
clear all;

%% Test af sleep() før autostart på den embeddede 

y = [407,410,410,397,402,406,407];
%y_gns = ((y(1)+y(2)+y(3)+y(4)+y(5)+y(6)+y(7)) / 7;
figure(1);clf;
plot(y,'x','MarkerSize',10);
hold on;
grid on;
title('Drift before compensation - Without boot')
xlabel('Drift nr.');
ylabel('1 / Drift = punkter pr. drift');
ylim([390 420]);
hold off;


%% Før auto med kompensering
%Tjooooo, kun et halvt punkt - så det konkluderes i stedet på drift.


%% Test af sleep() med autostart

y = [157,156,155,156,155,157,157,156,155,152,156];
%y_gns = ((y(1)+y(2)+y(3)+y(4)+y(5)+y(6)+y(7)) / 11;
figure(2);clf;
plot(y,'x','MarkerSize',10);
hold on;
grid on;
title('Drift before compensation - With boot')
xlabel('Drift nr.');
ylabel('1 / Drift = punkter pr. drift');
ylim([150 160]);
hold off;


%% Efter auto med kompensering