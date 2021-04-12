
current = linspace(4,20,100);

figure(9000);clf
plot( current)
hold on
plot( current,'o', 'MarkerIndices',[1,25,50,75,100])
hold off
xtickformat('percentage')
ytickformat('%gmA')

% xlabel('Værdi [%]')
% ylabel('Strøm [mA]')
grid on
grid minor
axis([0 100 4 20]);

yyaxis right
plot(current*0.250)
ytickformat('%gV')


title('4-20mA med 250\Omega målemodstand')