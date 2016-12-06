clear
clc
close all

%% ################### 60Hz
FileID = fopen('timing60.txt');

C = textscan(FileID, '%d %f' , 'Headerlines', 1)

fclose(FileID);
%% framerate 

framerate = C{1,2};


d2 = round(diff(framerate)*10000)/10000;
h=figure;

point = 1/60;
line([0 600], [point point], 'color', 'r')

plot(d2(1200:1799))


ylim([point-.01 point+.01])

ylabel('refresh (s)')
xlabel('frames')

title('C++ refresh on scene flicker at 60Hz')

saveas(h, 'scene refresh 60.png')
return
%% ################### 85Hz
FileID = fopen('timing85.txt');

C = textscan(FileID, '%d %f' , 'Headerlines', 1)

fclose(FileID);
%% framerate 

framerate = C{1,2};


d2 = round(diff(framerate)*10000)/10000;
h=figure; hold on;

point = 1/85;
line([0 600], [point point], 'color', 'r')
plot(d2(1200:1799))

ylim([point-.01 point+.01])

ylabel('refresh (s)')
xlabel('frames')

title('C++ refresh on scene flicker at 85Hz')

saveas(h, 'scene refresh 85.png')

%% ################### 100Hz
FileID = fopen('timing100.txt');

C = textscan(FileID, '%d %f' , 'Headerlines', 1)

fclose(FileID);
%% framerate 

framerate = C{1,2};

d2 = round(diff(framerate)*10000)/10000;
h=figure; hold on;

point = 1/100;
line([0 600], [point point], 'color', 'r')
plot(d2(1200:1799))

ylim([point-.01 point+.01])

ylabel('refresh (s)')
xlabel('frames')

title('C++ refresh on scene flicker at 100Hz')

saveas(h, 'scene refresh 100.png')

%% ################### 120Hz
FileID = fopen('timing120.txt');

C = textscan(FileID, '%d %f' , 'Headerlines', 1)

fclose(FileID);
%% framerate 

framerate = C{1,2};

d2 = round(diff(framerate)*10000)/10000;
h=figure; hold on;

point = 1/120;
line([0 600], [point point], 'color', 'r')
plot(d2(1200:1799))

ylim([point-.01 point+.01])

ylabel('refresh (s)')
xlabel('frames')

title('C++ refresh on scene flicker at 120Hz')

saveas(h, 'scene refresh 120.png')

%% ################### 144Hz
FileID = fopen('timing144.txt');

C = textscan(FileID, '%d %f' , 'Headerlines', 1)

fclose(FileID);
%% framerate 

framerate = C{1,2};

d2 = round(diff(framerate)*10000)/10000;
h=figure; hold on;

point = 1/144;
line([0 600], [point point], 'color', 'r')
plot(d2(1200:1799))

ylim([point-.01 point+.01])

ylabel('refresh (s)')
xlabel('frames')

title('C++ refresh on scene flicker at 144Hz')

saveas(h, 'scene refresh 144.png')
%% ################### 144Hz - 100 blocks
FileID = fopen('timing144_100.txt');

C = textscan(FileID, '%d %f' , 'Headerlines', 1)

fclose(FileID);
%% framerate 

framerate = C{1,2};

d2 = round(diff(framerate)*10000)/10000;
h=figure; hold on;

point = 1/144;
line([0 600], [point point], 'color', 'r')
plot(d2(1200:1799))

ylim([point-.01 point+.01])

ylabel('refresh (s)')
xlabel('frames')

title('C++ refresh on scene flicker at 144Hz 100s')

saveas(h, 'scene refresh 144 100s.png')