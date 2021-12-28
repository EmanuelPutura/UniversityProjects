pkg load statistics;

#{
  Normal Distribution N(mu, sigma):
  - normpdf, normcdf
  - norminv(x, mu, sigma) (the inverse of CDF, i.e., the quantile at x) 
 
  Student Distribution T(n):
  - tpdf, tcdf
  - tinv(x, n)
 
  Chi Square Distribution CS(n):
  - chi2pdf, chi2cdf
  - chi2inv(x, n)  

  Fischer Distribution F(m, n):
  - fpdf, fcdf
  - finv(x, m, n)
#}

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%% Exercise 1 %%%%%%%%%%%%%%%%%%%%%%%%% 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%% Normal Distribution N(mu, sigma) %%%%%%%%%%%%%%
disp("Normal Distribution N(mu, sigma):");
mu = input("mu = ");
sigma = input("sigma = ");

% a)
printf("P(X <= 0) = %d\n", normcdf(0, mu, sigma));
printf("P(X >= 0) = %d\n", 1 - normcdf(0, mu, sigma));

% b)
printf("P(-1 <= X <= 1) = %d\n", normcdf(1, mu, sigma) - normcdf(-1, mu, sigma));
printf("P(X <= -1 OR X >= 1) = %d\n", 1 - normcdf(1, mu, sigma) + normcdf(-1, mu, sigma));

% c)
alpha = input("alpha = ");
printf("P(X < x_alpha) = alpha, x_alpha = %d\n", norminv(alpha, mu, sigma));

% d)
beta = input("beta = ");
printf("P(X > x_beta) = beta, x_beta = %d\n", norminv(1 - beta, mu, sigma)); 

%%%%%%%%%%%%%%%%% Student Distribution T(n) %%%%%%%%%%%%%%%%%%
disp("Student Distribution T(n):");
n = input("n = ");

% a)
printf("P(X <= 0) = %d\n", tcdf(0, n));
printf("P(X >= 0) = %d\n", 1 - tcdf(0, n));

% b)
printf("P(-1 <= X <= 1) = %d\n", tcdf(1, n) - tcdf(-1, n));
printf("P(X <= -1 OR X >= 1) = %d\n", 1 - tcdf(1, n) + tcdf(-1, n));

% c)
alpha = input("alpha = ");
printf("P(X < x_alpha) = alpha, x_alpha = %d\n", tinv(alpha, n));

% d)
beta = input("beta = ");
printf("P(X > x_beta) = beta, x_beta = %d\n", tinv(1-beta, n));

%%%%%%%%%%%%%%%% Chi Square Distribution CS(n) %%%%%%%%%%%%%%%%
disp("Chi Square Distribution CS(n):");
n = input("n = ");
printf("P(X <= 0) = %d\n", chi2cdf(0, n));
printf("P(X >= 0) = %d\n", 1 - chi2cdf(0, n));
printf("P(-1 <= X <= 1) = %d\n", chi2cdf(1, n) - chi2cdf(-1, n));
printf("P(X <= -1 OR X >= 1) = %d\n", 1 - chi2cdf(1, n) + chi2cdf(-1, n));
alpha = input("alpha = ");
printf("P(X < x_alpha) = alpha, x_alpha = %d\n", chi2inv(alpha, n));
beta = input("beta = ");
printf("P(X > x_beta) = beta, x_beta = %d\n", chi2inv(1-beta, n)); 

%%%%%%%%%%%%%%%% Fischer Distribution F(m, n) %%%%%%%%%%%%%%%%%
disp("Fischer Distribution F(m, n):");
m = input("m = ");
n = input("n = ");
printf("P(X <= 0) = %d\n", fcdf(0, m, n));
printf("P(X >= 0) = %d\n", 1 - fcdf(0, m, n));
printf("P(-1 <= X <= 1) = %d\n", fcdf(1, m, n) - fcdf(-1, m, n));
printf("P(X <=-1 OR X >= 1) = %d\n", 1 - fcdf(1, m, n) + fcdf(-1, m, n));
alpha = input("alpha = ");
printf("P(X < x_alpha) = alpha, x_alpha = %d\n", finv(alpha, m, n));
beta = input("beta = ");
printf("P(X > x_beta) = beta, x_beta = %d\n", finv(1-beta, m, n)); 
