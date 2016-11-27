function plotFig = cdfCauchyPlot(cauchy_gamma, cauchy_x0, max_time, plotName)
        linspace_size = 100;
        cauchy_x = linspace(0, max_time, linspace_size);
        cauchy_y = (1/pi)*atan((cauchy_x - cauchy_x0)/cauchy_gamma) + 0.5; %ok
        hold on;
        figure;
        %set(gca, 'LineWidth', 4);
        %set(gca, 'fontsize', 16);
        plotFig = plot(cauchy_x, cauchy_y, '-b');
        ylabel('F(t)');
        xlabel('t');
        title(plotName);
        hold off;
end