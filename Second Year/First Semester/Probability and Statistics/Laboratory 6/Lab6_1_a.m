clc
clear all
pkg load statistics

Data=[7  7  4  5  9  9 
      4 12  8  1  8  7
      3 13  2  1 17  7
     12  5  6  2  1 13
     14 10  2  4  9 11
      3  5 12  6  10 7];
      
alpha = 0.05; 
sigma = 5;   
m_0 = 9;      

% H0: mean = 9                   
% H1: mean < 9  

[H, PVAL, CI, Z, ZCRIT] = ztest(Data(:), m_0, sigma, 'alpha', alpha, 'tail', 'left');

t = norminv(alpha, 0, 1); % cuantile of order alpha for N(0,1)
RR = [-inf , t];          % rejection region
fprintf('H is %1d\n', H)  % if H=0 we accept H0; if H=1 we reject H0
fprintf('TS_0 is %6.4f\n', Z) % observed value of the test statistic  Z 
fprintf('RR= (%6.4f,%6.4f)\n', RR)
fprintf('P-value is %6.4f\n',PVAL) % P-value

if H == 0
  disp('We accept H0, i.e. the mean is at least 9')
else
  disp('We reject H0, i.e. the mean is less than 9')
end

if alpha < PVAL
  disp('We accept H0')
else
  disp('We reject H0')
end