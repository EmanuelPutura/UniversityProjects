pkg load statistics;

#{
  binopdf, binocdf
  binornd - random sample from the binomial distribution
#}

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%% Exercise 1 %%%%%%%%%%%%%%%%%%%%%%%%% 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

printf("Binomial Distribution B(n, p)\n");
n = input("n = ");
p = input("p = ");

% pdf
x = 0:1:n;
figure();
subplot(3, 1, 1);
plot(x, binopdf(x, n, p), "-r", "linewidth", 1);
title("Ex2: PDF");

% cdf 
x = 0:0.01:n;
subplot(3, 1, 2);
plot(x, binocdf(x, n, p), "-r", "linewidth", 1);
title("Ex2: CDF");

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%% Coin Toss Application %%%%%%%%%%%%%%%%%%%% 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% a)
% Binomial Distribution with n = 3 and p = 1/2
n = 3;
p = 0.5;
x = 0:1:n;
disp(binopdf(x, n, p));
disp("Coin Toss a): B(3, 1/2) - Binomial Distribution PDF");

% b)
x = -2 * n:0.01:2 * n;

subplot(3, 1, 3);
plot(x, binocdf(x, n, p), "-r", "linewidth", 1);
title("Coin Toss b): B(3, 1/2) - Binomial Distribution CDF");

% c)
x = 0:1:n;
pdf = binopdf(x, n, p);
printf("P(X = 0) = %d\n", pdf(1));
printf("P(X != 1) = %d\n", 1 - pdf(2));

% d)
x = 0:1:n;
cdf = binocdf(x, n, p)
printf("P(X <= 2) = %d\n", cdf(3));
printf("P(X <  2) = %d\n", cdf(2));

% e)
printf("P(X >= 1) = %d\n", 1 - cdf(1));
printf("P(X >  1) = %d\n", 1 - cdf(2));

% f)
disp("Simulating 3 coin tosses");
ans = binornd(n, p);
printf("%d coin tosses resulted in heads\n", ans);
