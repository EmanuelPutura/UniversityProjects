clc
clear all
pkg load statistics

Data=[7  7  4  5  9  9 
      4 12  8  1  8  7
      3 13  2  1 17  7
     12  5  6  2  1 13
     14 10  2  4  9 11
      3  5 12  6  10 7];
      
conf_level = 0.99;       
alpha = 1 - conf_level;   

% a)  

sigma = 5; 
m_s = mean(Data(:));  
n = length(Data(:));  
z = norminv(1 - alpha / 2, 0, 1);  
m_L = m_s - sigma / sqrt(n) * z;  
m_R = m_s + sigma / sqrt(n) * z;  
fprintf('The confidence interval for mean is (%4.2f,%4.2f)\n', m_L, m_R)

%b) 

s = std(Data(:)); 
t = tinv(1 - alpha / 2, n - 1);  
M_L = m_s - s / sqrt(n) * t;  
M_R = m_s + s / sqrt(n) * t;
fprintf('The confidence interval for mean in the second case is (%4.2f,%4.2f)\n', M_L, M_R)


%c)  
v = var(Data(:));  
chi_L = chi2inv(1 - alpha / 2,n - 1); 
chi_R = chi2inv(alpha / 2,n - 1);    
V_L = (n - 1) * v / chi_L;
V_R= (n - 1) * v / chi_R;
fprintf('The confidence interval for variance is (%4.2f,%4.2f)\n', chi_L, chi_R)
