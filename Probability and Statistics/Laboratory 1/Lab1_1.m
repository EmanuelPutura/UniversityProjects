%{
  matrix . operations (applied to each element)
  input()
  eye(3)
  ones(3)
  zeros(3)
  printf(), format(), disp()
  graphics in Octave, plot, subplot, title, legend, colors, linewidth, linestyle
%}

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%% Exercise 1 %%%%%%%%%%%%%%%%%%%%%%%%% 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

A = [1, 0, -2;
     2, 1,  3;
     0, 1,  0];
B = [2, 1,  1;
     1, 0, -1;
     1, 1,  0];

C = A -  B
D = A *  B
E = A .* B

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%% Exercise 2 %%%%%%%%%%%%%%%%%%%%%%%%% 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

x = 0:0.01:3;
figure();
plot(x, x .^ 5 / 10, "-r", x, x .* sin(x), "--b", x, cos(x), ":g", "linewidth", 3);
title("Lab 1 Graph 1");
legend("x^5 / 10", "x * sin (x)", "cos (x)");

figure();
subplot(3, 1, 1);
plot(x, x .^ 5 / 10, "-r");
title("Lab 1 Graph F1");
legend("x^5 / 10");

subplot(3, 1, 2);
plot(x, x .* sin(x));
title("Lab 1 Graph F2");
legend("x * sin (x)");

subplot(3, 1, 3);
plot(x, cos(x), ":g", "linewidth", 3);
title("Lab 1 Graph F3");
legend("cos (x)");
