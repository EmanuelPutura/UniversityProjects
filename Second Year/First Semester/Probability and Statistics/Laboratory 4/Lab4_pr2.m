clear ALL
pkg load statistics

p=0.3
u=rand

X=(u < p)
n=5

%  Verify 
N=100
for j=1:N
for i=1:n
  U=rand;
  Bino(i)=(U < p); % generate a sample of N values
end
S(j)=sum(Bino)
end
 
disp("S: ")
disp(S)

Frq_a=hist(S,0:n)
Frq_r = Frq_a / N   % compute the relative frequency
disp('Estimated Binomial distribution')
disp([0:n; Frq_r])
disp('Theoretical Binomial distribution')
disp([0:n; binopdf(0:n,n,p)])

bar(0:n , Frq_r, 'b')
hold on
bar(0:n , binopdf(0:n, n, p), 'y')
legend('Estimated', 'Theoretical')
set(findobj('type', 'patch'), 'facealpha', 0.7)
