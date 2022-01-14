clc
clear all
pkg load statistics

Premium = [22.4 24.5 21.6 22.4 24.8 21.7 23.4 23.3 21.6 20.0];
Regular = [17.7 19.6 12.1 15.4 14.0 14.8 19.6 14.8 12.6 12.2];

alpha = 0.05;   

% H0:  R (the ratio) = 1
% H0:  r (the ratio) =/= 1  (two-tailed test)

[H, PVAL, CI, STATS] = vartest2(Premium, Regular, 'alpha', alpha, 'tail', 'both');

n1 = length(Premium);     
n2 = length(Regular);     
t_1 = finv(alpha / 2, n1 - 1, n2 - 1);   %cuantile of order alpha/2 for F(n1-1,n2-1)
t_2 = finv(1 - alpha / 2, n1 - 1, n2 - 1); %cuantile of order 1-alpha/2 for F(n1-1,n2-1)
RR = [-inf, t_1, t_2, inf];         % rejection region
fprintf('H is %1d\n', H) ;      % if H=0 we accept H0 but if H=1 we reject H0
fprintf('TS_0 is %6.4f\n', STATS.fstat); % observed value of the test statistic F 
fprintf('RR is (%6.4f,%6.4f)U(%6.4f,%6.4f)\n', RR);
fprintf('P-value is %6.4f\n', PVAL);

if H==0
  disp('We accept H0 (1st method, using RR)')
  disp('The variances are equal')
else
  disp('We reject H0 (1st method, using RR)')
  disp('The variances are different')
end

if alpha < PVAL
  disp('We accept H0 (2nd method, using P)')
else
  disp('We reject H0 (2nd method, using P)')
end