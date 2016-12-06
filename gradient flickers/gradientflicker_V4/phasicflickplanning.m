Hzs = [11 13 17 19];
for H = 1:length(Hzs)
clear sig
Hz = Hzs(H);
fs = 144;
frames = fs/Hz;

% frameactual = 14;
% t = 0:0.0069:frames/144;
% t = 0:frames;

t = 0:1/fs:1/Hz;

trial = 0:1/fs:5-1/fs;

for x = 1:length(trial)
    sig(x) = sin(2*pi/frames*x);
end

h = figure; hold on
plot(trial, sig);
plot(trial, sig, 'rx')
title([num2str(Hz) 'Hz'])

% saveas(h, [ cd '/' num2str(Hz) '.png'])
end
return
%% How I'll do it in C++
triallength = 5;
f.trial = fs*triallength;

fs = 144;
Hz = 11;
frames = fs/Hz;


for x = 1:f.trial
    sig(x) = sin(2*pi/frames*x);
end


%% TEST SIGNAL
fs = 144;
lim.s = [0 5]; % epoch limits (seconds) relative to trigger

lim.x = ceil(lim.s*fs) + 1;
lim.x(2) = lim.x(2)  - 1;

n.s = lim.s(2)-lim.s(1);
n.x = lim.x(2)-lim.x(1)+1;

t = (0:n.x-1)/fs;

f = 0 : 1/n.s : fs - 1/n.s; % f = 0 : 1/n.s : fs;


amp = abs( fft( sig ) )/n.x;
amp(2:end-1,:) = amp(2:end-1,:)*2; % double amplitudes
    
h = figure;
plot(f,amp )

%% TEST SIGNAL - 60Hz
fs = 60;
lim.s = [0 5]; % epoch limits (seconds) relative to trigger

lim.x = ceil(lim.s*fs) + 1;
lim.x(2) = lim.x(2)  - 1;

n.s = lim.s(2)-lim.s(1);
n.x = lim.x(2)-lim.x(1)+1;

t = (0:n.x-1)/fs;

f = 0 : 1/n.s : fs - 1/n.s; % f = 0 : 1/n.s : fs;


amp = abs( fft( sig ) )/n.x;
amp(2:end-1,:) = amp(2:end-1,:)*2; % double amplitudes
    
h = figure;
plot(f,amp )

    
    