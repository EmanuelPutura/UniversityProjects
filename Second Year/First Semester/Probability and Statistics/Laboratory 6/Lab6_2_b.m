clc
clear all
pkg load statistics

Premium = [22.4 24.5 21.6 22.4 24.8 21.7 23.4 23.3 21.6 20.0];
Regular = [17.7 19.6 12.1 15.4 14.0 14.8 19.6 14.8 12.6 12.2];
  
alpha = 0.05;  

% H0:  D (the difference) =  0
% H0:  D (the difference) >  0  (right-tailed test)

[H, PVAL, CI, STATS] = ttest2(Premium, Regular, 'alpha', alpha, 'tail', 'both', 'vartype', 'equal');

n1 = length(Premium); 
n2 = length(Regular);
t = tinv(1 - alpha, n1 + n2 - 2); % cuantile of order 1-alpha for T(n1+n2-2)
RR = [t, inf];                    % rejecting region
fprintf('H is %1d\n', H)  
fprintf('TS_0 is %6.4f\n', STATS.tstat)
fprintf('RR is (%6.4f,%6.4f)\n', RR)
fprintf('P-value is %12.11f\n', PVAL)

if H==0
  disp('We accept H0 (1st method, using RR)')
  disp('The means are equal')
else
  disp('We reject H0 (1st method, using RR)')
  disp('The first mean is greater than the second one')
end

if alpha < PVAL
  disp('We accept H0 (2nd method, using P)')
else
  disp('We reject H0 (2nd method, using P)')
end