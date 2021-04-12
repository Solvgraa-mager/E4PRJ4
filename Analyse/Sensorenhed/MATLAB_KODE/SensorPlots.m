clear
format short eng
set(0, ...
    'DefaultLineLineWidth', 1.5, ...
    'DefaultAxesColorOrder', [0 0 0], ...
    'DefaultAxesLineStyleOrder', '-|--|:|-.');

current = linspace(4, 20, 100);
current = current .* 1e-3;





saltrange = linspace(0, 50, 100);

pHrange = linspace(0, 14, 100);
temprange = linspace(-30, 80, 100);
% temp2range = linspace(-50, 400, 100);
temp3range = linspace(-5, 45, 100);

t = tiledlayout(2, 2, 'padding', 'compact');
nexttile
plot(saltrange, current * 1000, 'DisplayName', 'OxyGuard - Salinity Probe')
rectangle('Position', [30 4 10 16])
legend('location', 'northwest')
axis tight
title('Salinitet')
% ylabel('Outputstrøm')
xlabel('Salinitet [PSU]')
grid on
grid minor

nexttile
plot(pHrange, current * 1000, 'DisplayName', 'PHTM-014')
hold on
plot(pH2range, current * 1000, 'DisplayName', 'PHTM-212')
hold off
legend('location', 'northwest')
% ylabel('Outputstrøm')
xlabel('pH-koncentration')
title('pH')
rectangle('Position', [6 4 2 16])
axis tight
grid on
grid minor

nexttile([1 2])
plot(temprange, current * 1000, 'DisplayName', 'Comet System - P0120')
hold on
% plot(temp2range, current * 1000, 'DisplayName', 'PR electronics - 7400 : Pt100')
plot(temp3range, current * 1000, 'DisplayName', 'OxyGuard - Temperature Probe')
hold off
title('Temperatur')
rectangle('Position', [21 4 9 16])
% ylabel('Outputstrøm')
legend('location', 'northwest')
axis tight
xlabel(['Temperatur [', char(176), 'C]'])
grid on
grid minor

ylabel(t, 'Outputstrøm')
