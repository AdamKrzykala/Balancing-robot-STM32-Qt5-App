clear all; close all;

f1 = figure; hold on; grid on;

sim('sterowanie_model.slx', t);

figure(f1);
plot(t, Theta);

