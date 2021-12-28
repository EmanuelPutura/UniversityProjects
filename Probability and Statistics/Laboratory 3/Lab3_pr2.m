pkg load statistics;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%% Exercise 2 %%%%%%%%%%%%%%%%%%%%%%%%% 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Part 1
printf("Normal Approximation of the Binomial Distribution\n");
printf("(0.05 <= p <= 0.95, n -> inf)\n");
p = input("p = ");

figure();
for (n = 1:10:100)
  mu = n * p;
  sigma = sqrt(n * p * (1 - p));
  x = 0:1:n;
  
  y1 = binopdf(x, n, p);
  y2 = normpdf(x, mu, sigma);
  
  subplot(1, 2, 1);
  plot(x, y1, "r");
  title("Binomial Distribution B(n, p)");
  subplot(1, 2, 2);
  plot(x, y2, "b");
  title("Normal Distribution N(n * p, sqrt(n * p * (1 - p)))");
  pause(0.5)
endfor

% Part 2
printf("Poisson Approximation of the Binomial Distribution\n");
printf("(p <= 0.05, n >= 30)\n");

n = input("n = ");
p = input("p = ");

x = 0:1:n;
y1 = binopdf(x, n, p);
y2 = poisspdf(x, n * p);
figure();
plot(x, y1, "-r;Binomial Distribution;", x, y2, "-b;Poisson Distribution;");
