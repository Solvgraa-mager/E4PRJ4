%% Strukturering
clear all;
clc;
close all;

syms x;
%% Salinitet

%SALINITET OVER LITER MÆTTET SALTVAND TILFØRSEL:
figure(101);
y=(1/0.06944)*x+0; %0,069 liter mættet saltvand pr. time
fplot(y, [0 0.1]);
grid on;
title('Salinitets forøgelse i 25 L ifht. tilsætning af x L mættet saltvand');
xlabel('Mættet saltvand tilføjet [Liter]');
ylabel('Salinitets forøgelse i 25 L [PSU]');

%HVOR LANG TID SKAL EN PUMPE VÆRE TÆNDT VED SPEC. FLOW RATE FOR AT TILFØJE
%1 PSU TIL VANDET:
X=([1: 1000]);

x_akse=X.*0.1;

y_ml=69.44./x_akse;

figure(102);
plot(x_akse,y_ml)
xlim([0 20])
ylim([0 200])
title('Tid i ON tilstand ved flow rate for at opnå 1 PSU ændring')
xlabel('Tid i ON tilstand [s]')
ylabel('Flow rate [mL/sek]')

y_liter=(0.0694*3600)./x_akse;

figure(103);
plot(x_akse,y_liter)
xlim([0 20])
ylim([0 200])

title('Tid i ON tilstand ved flow rate for at opnå 1 PSU ændring')
xlabel('Tid i ON tilstand [s]')
ylabel('Flow rate [Liter/time]')

%% Vandstand
y_vandstand=1/10*x;

figure(104);
fplot(y_vandstand, [0 100]);
title('Tømningspumpe: Flow rate ifht. duty cycle');
ylabel('Flow rate [Liter/time]');
xlabel('PWM Duty Cycle [%]');
grid on;

%% Temperatur:

%OPSLAGSGRAF: PWM OVER VARMETILFØRSEL
y_varme1=1/50*x;
figure(105);
fplot(y_varme1, [0 100]);
title('Varmelegeme: Varmeafsættelse ifht. duty cycle');
ylabel('Varmeafsættelse [grader celcius pr. time]');
xlabel('PWM Duty Cycle [%]');

%OPSLAGSGRAF: 

V=25; %volumen i liter
dT=4168; %Vands varmekapacitet: joules pr. liter pr. grad. 
%Hvor mange joule skal der til for at varme 1 kg vand op med 1 grader celcius (indenfor 0-100 grader).

%Der estimeres til en start tab på 15%. Varmeeffektivitet = 85%.
tab=1.15;
figure(106);
y_varme2=1*(((V*1*dT)/x)/60)/60; %x = antal watt
y_varme3=tab*(((V*1*dT)/x)/60)/60;
y_varme4=(tab+0.1)*(((V*1*dT)/x)/60)/60;
y_varme5=(tab+0.2)*(((V*1*dT)/x)/60)/60;
fplot(y_varme2, [25 45]);
hold on;
fplot(y_varme3, [25 45]);
hold on;
fplot(y_varme4, [25 45]);
hold on;
fplot(y_varme5, [25 45]);
title('Tid for 1 grader celcius varmeforøgelse i 25 L vand');
xlabel('Effekt [W]');
ylabel('Tid [timer]');
yline(1);
legend('Tab = 0%','Tab = 15%', 'Tab = 25%', 'Tab = 35%', 'Max tid = 1 time');

grid on;

%DESIGNPARAMETRE
%Step størrelse
A_step=35;

%Reference temp (minimumtemperatur)
A_reference = 21;

%Max stationærfejl:
E_ss = 1/A_step;

%Fra 21 grader til 35 grader må tage 9 timer
T_settle = 32400; %sekunder

%OS og zeta:
OS_max=1.1;
zeta=0.7;