clc 
clear all
pkg load statistics

Data=[7  7  4  5  9  9 
      4 12  8  1  8  7
      3 13  2  1 17  7
     12  5  6  2  1 13
     14 10  2  4  9 11
      3  5 12  6  10 7];
      
alpha = 0.01;
m_0 = 5.5; 

% H0: mean = 5.5  
% H1: mean > 5.5  

[H, PVAL, CI, STATS] = ttest(Data(:), m_0, 'alpha', alpha,'tail', 'right');

n = length(Data(:));   % or n - 1 = STATS.df
t = tinv(1-alpha,n-1); % cuantile of order 1-alpha for T(n-1)
RR = [t, inf];      % rejection region
fprintf('H is %1d\n',H)    
fprintf('TS_0 is %6.4f\n',STATS.tstat) %observed value of the test statistic T 
fprintf('RR=[%4.2f,inf]\n',t) 
fprintf('P-value is %6.4f\n',PVAL)

if H == 0
  disp('We accept H0 (1st method, using RR)')
  disp('The average number of files does not exceed 5.5')
else
  disp('We reject H0 (1st method, using RR)')
  disp('The average number of files exceeds 5.5')
end

if alpha < PVAL
  disp('We accept H0 (2nd method, using P)')
  disp('The average number of files does not exceed 5.5')
else
  disp('We reject H0 (2nd method, using P)')
  disp('The average number of files exceeds 5.5')
end