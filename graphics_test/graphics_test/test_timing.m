clear
clc
close all

%%

load('Latency_normal.mat')

latency_norm = latency;
figure;
plot(diff(latency_norm));

title('normal priority')
ylim([0 0.08])
%%

load('Latency_background.mat')

latency_back = latency;
figure;
plot(diff(latency_back));

title('background priority')
ylim([0 0.08])
%%

load('Latency_TC.mat')

latency_tc = latency;
figure;
plot(diff(latency_tc));

title('time critical priority')
ylim([0.01 0.02])

%%
load('Latency_TC3.mat')

latency_tc = latency;
figure;
plot(round(diff(latency_tc)*1000)/1000);

title('time critical priority')
ylim([0.01 0.02])
