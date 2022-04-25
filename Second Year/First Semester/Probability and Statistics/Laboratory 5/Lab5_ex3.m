clc
clear all
pkg load statistics

Premium=[22.4 24.5 21.6 22.4 24.8 21.7 23.4 23.3 21.6 20.0];
Regular=[17.7 19.6 12.1 15.4 14.0 14.8 19.6 14.8 12.6 12.2];

conf_level = 0.98;     
alpha = 1 - conf_level   

% a) 

m_1 = mean(Premium); 
m_2 = mean(Regular);
v_1 = var(Premium); 
v_2 = var(Regular); 
n_1 = length(Premium); 
n_2 = length(Regular); 
t = tinv(1 - alpha / 2, n_1 + n_2 - 2); 
s_p = ((n_1 - 1) * v_1 + (n_2 - 1) * v_2) / (n_1 + n_2 - 2);
d_L = m_1 - m_2 - t * sqrt(s_p) * sqrt(1 / n_1 + 1 / n_2);    
d_R = m_1 - m_2 + t * sqrt(s_p) * sqrt(1 / n_1 + 1 / n_2);   
fprintf('a) CI for difference of means is (%4.2f,%4.2f)\n', d_L, d_R)

% b)

c = (v_1 / n_1) / (v_1 / n_1 + v_2 / n_2);
n = 1 / (c ^ 2 / (n_1 - 1) + (1 - c) ^ 2 / (n_2 - 1));
t = tinv(1 - alpha / 2, n); 
s_p = ((n_1 - 1) * v_1 + (n_2 - 1) * v_2) / (n_1 + n_2 - 2);
D_L = m_1 - m_2 - t * sqrt(v_1 / n_1 + v_2 / n_2); 
D_R = m_1 - m_2 + t * sqrt(v_1 / n_1 + v_2 / n_2); 
fprintf('b) CI for difference of means is (%4.2f,%4.2f)\n', D_L, D_R)


% c) 

f_L = finv(1 - alpha / 2, n_1 - 1, n_2 - 1);
f_R = finv(alpha / 2, n_1 - 1, n_2 - 1);
V_L = (1 / f_L) * (v_1 / v_2); 
V_R = (1 / f_R) * (v_1 / v_2);
fprintf('c) CI for ratio of variances (%4.2f,%4.2f)\n', V_L, V_R)
