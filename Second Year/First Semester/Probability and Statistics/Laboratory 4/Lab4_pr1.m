%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%% Exercise 1 %%%%%%%%%%%%%%%%%%%%%%%%% 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

p = input("Give p:");
N = input("Give N (number of simulations):");
U = rand(1, N)              % N random numbers between 0 and 1
X = (U < p)                 % basically an indicator random variable
U_X = unique(X)             % take the uniques from the indicator, values will be from {0, 1} only
n_X = hist(X, length(U_X))  % count how many values of zero and how many values of one there are
rel_freq = n_X / N          % computer the relative frequency of zero and one
