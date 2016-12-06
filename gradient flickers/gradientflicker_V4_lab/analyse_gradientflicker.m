clear
clc
close all

addpath(genpath('C:\Users\s4262470\Documents\angela_renton_local\fNIRS\bvaio1.57\'));

%% settings

fs = 2000;
load chanlocs;

chan2use = [22 23 24 25 26 27 28 29 47 48 49 50 51 52 53 54 59 60 61];

[EEG, ~] = pop_loadbv( [ cd '/data/'] , 'test_s03_2016-03-21_14-25-16.vhdr');% file.eeg.left{session});

%% get rid of mastoids and EOG
n.channels = 64;
BEST = ~ismember( 1:n.channels, [13 19 32] );
n.channels = sum(BEST);

EEG.data = EEG.data(BEST,:);

%% get events

figure;
latency = [EEG.event.latency]';

type = NaN( length( EEG.event ), 1);

for EE = 1:length( EEG.event )
    tmp = EEG.event(EE).type;
    tmp( tmp == 's' ) = [];
    
    if strcmp( tmp, 'Impedance' )
        type(EE,1) = NaN;
    else
        type(EE,1) = str2num(tmp);
    end
    
end

type(end-5:end) = [];
latency(end-5:end) = [];

stem(latency, type); hold on;

%% check data

h=figure;
plot(EEG.data')
saveas(h, [ cd '/results/datacheck.png']);


%% frequency settings

% std::vector<int> x = { 29, 7, 11, 13, 15 }; // {4.97, 20.57, 13.09, 11.08}
% std::vector<int> y = { 17, 19, 23, 5, 31 }; // {8.47, 7.58, 6.27, 28.8};

Hz = [4.97 20.57 13.09 8.47 7.58 6.29];
n.Hz = length(Hz);

lim.s = [0 5]; % epoch limits (seconds) relative to trigger

lim.x = ceil(lim.s*fs) + 1;
lim.x(2) = lim.x(2)  - 1;

n.s = lim.s(2)-lim.s(1);
n.x = lim.x(2)-lim.x(1)+1;

t = (0:n.x-1)/fs;

f = 0 : 1/n.s : fs - 1/n.s; % f = 0 : 1/n.s : fs;

for H = 1:length(Hz)
    [~, IDX_Hz(H)] = min( abs( f - Hz(H) ) );
    real_Hz(H) = f(IDX_Hz(H));
end

%% cond

COND = [ 1 2 3 4 5 6 7 8 9];

%% Make ERP

ERP = nan(n.x, n.channels, length(COND));
AMP = nan(n.x, n.channels, length(COND)+1);

for CC = 1:length(COND)
    
    offset = latency(ismember( type, COND(CC)  )); % find cue trigger
    
    start = round( offset + lim.x(1) );
    stop = round( offset + lim.x(2) );
    
    trial = NaN( n.x, n.channels, length(latency) );
    
    for E =1:length(offset)
        disp([CC E]);
        data2use = EEG.data(:, start(E):stop(E) )';
        
        data2use = detrend(data2use,'linear');
        data2use = detrend(data2use,'constant');
        data2use = data2use - repmat( data2use(1,:), size(data2use,1), 1);
        
        trial(:,:,E) = data2use;
        %         plot(data2use)
    end
    
    %% gather epochs, make ERP
    
    erp = nanmean(trial,3);
    
    ERP(:,:,CC) = erp;
    
    amp = abs( fft( erp ) )/n.x;
    amp(2:end-1,:) = amp(2:end-1,:)*2; % double amplitudes
    
    AMP(:,:,CC) = amp;
    
    
end

%% Big AMP

erp = nanmean(ERP,3);

amp = abs( fft( erp ) )/n.x;
amp(2:end-1,:) = amp(2:end-1,:)*2; % double amplitudes

AMP(:,:,10) = amp;

%%
Hz = [4.97 20.57 13.09 8.47 7.58 6.29];

h = figure;
plot(f, AMP(:,chan2use,10) )
title(['overall frequency spectrum' ]);
xlabel('freq (Hz)');
ylabel('SSVEP amp (µV)');
xlim([2 25]);

for H = 1:length(Hz)
    line([Hz(H) Hz(H)], get(gca, 'ylim'), 'color', 'k')
end

saveas(h, [ cd '/results/overallspectrum.png']);

%% individual spectrums
clear IM;
% Hzx = [4.97 20.57 13.09 4.97 20.57 13.09 4.97 20.57 13.09];
% Hzy = [8.47 8.47 8.47 7.58 7.58 7.58 6.29 6.29 6.29];

str.tile = {'1' '4' '7' '2' '5' '8' '3' '6' '9'};

Hzx = [4.97 20.57 13.09 ];
Hzy = [8.47 7.58 6.29 ];

tile = 1;
for tilex = 1:3
    for tiley = 1:3
        
        h = figure;
        plot(f, AMP(:,chan2use,tile) )
        title(['tile ' str.tile(tile) ' frequency spectrum' ]);
        xlabel('freq (Hz)');
        ylabel('SSVEP amp (µV)');
        xlim([2 25]);
        
        line([Hzx(tilex) Hzx(tilex)], get(gca, 'ylim'), 'color', 'k')
        line([Hzy(tiley) Hzy(tiley)], get(gca, 'ylim'), 'color', 'k')
        
        saveas(h, [ cd '/results/tile' num2str(tile) 'spectrum.png']);
        IM{tilex, tiley} = imread( [ cd '/results/tile' num2str(tile) 'spectrum.png'] );
        tile = tile+1;
    end
end

imwrite( cell2mat(IM), [ cd '/results/spectrums.png'] )

%% seperate into stripes
clear AMPstripes erpstripes

erpstripes(:,:,1) = mean(ERP(:,:,[1 4 7]), 3);
erpstripes(:,:,2) = mean(ERP(:,:,[2 5 8]), 3);
erpstripes(:,:,3) = mean(ERP(:,:,[3 6 9]), 3);
erpstripes(:,:,4) = mean(ERP(:,:,1:3), 3);
erpstripes(:,:,5) = mean(ERP(:,:,4:6), 3);
erpstripes(:,:,6) = mean(ERP(:,:,7:9), 3);

for CC = 1:6
    amp = abs( fft( erpstripes(:,:,CC) ) )/n.x;
    amp(2:end-1,:) = amp(2:end-1,:)*2; % double amplitudes
    
    AMPstripes(:,:,CC) = amp;
end

%% Get Best in stripes
clear best response

for CC = 1:6
    %     [~, idx] = max(squeeze(max(AMPstripes(IDX_Hz(CC)-2:IDX_Hz(CC)+2, chan2use,CC))));
    [~, idx] = max(squeeze(AMPstripes(IDX_Hz(CC), chan2use,CC)));
    best(CC, 1) = chan2use(idx);
    
    %     response(CC, 1) = max(AMPstripes(IDX_Hz(CC)-2:IDX_Hz(CC)+2, best(CC, 1),CC));
    response(CC, 1) = AMPstripes(IDX_Hz(CC), best(CC, 1),CC);
    
    count = 2;
    for HH = 1:6
        if CC~=HH
            
            %             [~, idx] = max(squeeze(max(AMPstripes(IDX_Hz(HH)-2:IDX_Hz(HH)+2, chan2use,CC))));
            [~, idx] = max(squeeze(AMPstripes(IDX_Hz(HH), chan2use,CC)));
            best(CC, count) = chan2use(idx);
            
            %             response(CC, count) = max(AMPstripes(IDX_Hz(CC)-2:IDX_Hz(CC)+2, best(CC, count),CC));
            response(CC, count) = AMPstripes(IDX_Hz(CC), best(CC, count),CC);
            
            count = count+1;
        end
    end
end

RESPONSE = [response(1:6, 1), mean(response(1:6, 2:6)')'];

%% plot by  frequency
close all

h=figure;
label = { '4.9700'   '20.5700'   '13.0900'    '8.4700'    '7.5800'    '6.2900' };

errorbar_groups(RESPONSE', zeros(6,2)', 'bar_colors', [0.3 0.3 1; 1 0.3 0.3  ], 'bar_names', label, 'FigID', h);
set(gca, 'TickDir', 'out', 'box','off', 'FontSize', 14, 'FontName', 'Arial')

legend({'Attended' 'Unattended'});
title(  'SSVEP amp by stripe'  )
ylabel('SSVEP Amp (µV)')
xlabel('Frequency')
ylim([0 0.042])

saveas(h, [ cd '/results/Ampbystripe.png']);


%% %% Get Best in tile
clear best response idx Zattend Zunattend

for CC = 1:9
    for HH = 1:6
        
%         [~, idx] = max(squeeze(max(AMP(IDX_Hz(HH)-2:IDX_Hz(HH)+2, chan2use,CC))));
[~, idx] = max(squeeze(max(AMP(IDX_Hz(HH)-2:IDX_Hz(HH)+2, chan2use,CC))));
        best(CC, HH) = chan2use(idx);
        
        response(CC, HH) = max(AMP(IDX_Hz(HH)-2:IDX_Hz(HH)+2, best(CC, HH),CC));
        
    end
end

Z = zscore(response);

count = 1;
for j=1:3
    for i = 1:3
        idxHz(count, :) = [find(Hz==Hzx(i)) find(Hz==Hzy(j))];
        count = count+1;
    end
end

for C = 1:9
     Zattend(C,:) = Z(C,idxHz(C,:));
end

for C = 1:9
    for H = 1:2
        U = ~ismember(1:9, C);
        Zunattend(C,H) = mean(Z(U,idxHz(C,H)));
    end
end

reorder = [1 4 7 2 5 8 3 6 9];
Zattend = Zattend(reorder,:);
Zunattend = Zunattend(reorder,:);


%% plot Z score by frequency
close all

tile = 1;
str.tile = {'1' '4' '7' '2' '5' '8' '3' '6' '9'};
for tilex = 1:3
    for tiley = 1:3
        
        h=figure;
        label = { num2str(Hzx(tilex))   num2str(Hzy(tiley))  };
        
        data2plot = [Zattend(tile, :); Zunattend(tile, :)];
        errorbar_groups(data2plot, zeros(2,2)', 'bar_colors', [0.3 0.3 1; 1 0.3 0.3  ], 'bar_names', label, 'FigID', h);
        set(gca, 'TickDir', 'out', 'box','off', 'FontSize', 14, 'FontName', 'Arial')
        
        legend({'Attended' 'Unattended'});
        title(  ['SSVEP Z scores Tile ' str.tile{tile}]  )
        ylabel('Zscore')
        xlabel('Frequency')
        ylim([-1.5 2.5]);
        
        saveas(h, [ cd '/results/tile' str.tile{tile} 'SSVEPs.png']);
        IM{tilex, tiley} = imread( [ cd '/results/tile' str.tile{tile} 'SSVEPs.png'] );
        tile = tile+1;
    end
end

imwrite( cell2mat(IM), [ cd '/results/SSVEPsbytile.png'] )



%% Distribution of SSVEPs

x = [-3:.1:3];
norm = normpdf(x,0,1);

h = figure;

for HH = 1:6
    subplot(2,3,HH)
    plot(x,norm)
    
    for T = 1:9
        line([Z(T,HH) Z(T,HH)], get(gca, 'ylim'), 'color', 'k')
        
        xlin = find(idxHz(:,1)==HH);
        ylin = find(idxHz(:,2)==HH);
        
        if ismember(T,xlin) || ismember(T,ylin)
            line([Z(T,HH) Z(T,HH)], get(gca, 'ylim'), 'color', 'r')
        end
    end
    
    title([num2str(Hz(HH)) 'Hz'])
    xlabel('Z scores')
    set(gca, 'TickDir', 'out', 'box','off')
end

suptitle('SSVEP Z scores - red indicates attention to tagged tile')
saveas(h, [ cd '/results/pdist_by_freq.png']);

%% Distribution of SSVEPs - better figure
close all
clear IM
x = [-3:.1:3];
norm = normpdf(x,0,1);

xcount = 1;
ycount = 1;
for HH = 1:6
    h = figure;
    plot(x,norm)
    
    for T = 1:9
        line([Z(T,HH) Z(T,HH)], get(gca, 'ylim'), 'color', 'k')
        
        xlin = find(idxHz(:,1)==HH);
        ylin = find(idxHz(:,2)==HH);
        
        if ismember(T,xlin) || ismember(T,ylin)
            line([Z(T,HH) Z(T,HH)], get(gca, 'ylim'), 'color', 'r')
        end
    end
    
    title([num2str(Hz(HH)) 'Hz'])
    xlabel('Z scores')
    set(gca, 'TickDir', 'out', 'box','off')
    
    saveas(h, [ cd '/results/pdist' num2str(HH) '.png']);
    
   
    IM{xcount, ycount} = imread( [ cd '/results/pdist' num2str(HH) '.png'] );
    xcount = xcount+1;
    if HH==3;  xcount = 1; ycount = 2;     end
end

imwrite( cell2mat(IM), [ cd '/results/pdist_by_freq_BIG.png'] )

suptitle('SSVEP Z scores - red indicates attention to tagged tile')

%% raw SSVEP response by tile attended or unattended

count = 1;
for j=1:3
    for i = 1:3
        idxHz(count, :) = [find(Hz==Hzx(i)) find(Hz==Hzy(j))];
        count = count+1;
    end
end

for C = 1:9
     Rattend(C,:) = response(C,idxHz(C,:));
end

for C = 1:9
    for H = 1:2
        U = ~ismember(1:9, C);
        Runattend(C,H) = mean(response(U,idxHz(C,H)));
    end
end

reorder = [1 4 7 2 5 8 3 6 9];
Rattend = Rattend(reorder,:);
Runattend = Runattend(reorder,:);

%% plot SSVEP amp by frequency
close all

tile = 1;
str.tile = {'1' '4' '7' '2' '5' '8' '3' '6' '9'};
for tilex = 1:3
    for tiley = 1:3
        
        h=figure;
        label = { num2str(Hzx(tilex))   num2str(Hzy(tiley))  };
        
        data2plot = [Rattend(tile, :);Runattend(tile, :)];
        errorbar_groups(data2plot, zeros(2,2)', 'bar_colors', [0.3 0.3 1; 1 0.3 0.3  ], 'bar_names', label, 'FigID', h);
        set(gca, 'TickDir', 'out', 'box','off', 'FontSize', 14, 'FontName', 'Arial')
        
        legend({'Attended' 'Unattended'});
        title(  ['SSVEP amplitude Tile ' str.tile{tile}]  )
        ylabel('SSVEP amp µV')
        xlabel('Frequency')
        ylim([0 6]);
        
        saveas(h, [ cd '/results/tile' str.tile{tile} 'SSVEPs(raw).png']);
        IM{tilex, tiley} = imread( [ cd '/results/tile' str.tile{tile} 'SSVEPs(raw).png'] );
        tile = tile+1;
    end
end

imwrite( cell2mat(IM), [ cd '/results/RawSSVEPsbytile.png'] )

%% Disinclude other tiles with that frequency

for C = 1:9
    for H = 1:2
        U = ~ismember(1:9, find(idxHz(:,H)==idxHz(C,H)));
        Zunattend2(C,H) = mean(Z(U,idxHz(C,H)));
        Runattend2(C,H) = mean(response(U,idxHz(C,H)));
    end
end

reorder = [1 4 7 2 5 8 3 6 9];
Runattend2 = Runattend2(reorder,:);
Zunattend2 = Zunattend2(reorder,:);

%% plot new Z score by frequency
close all
clear IM1 IM2

tile = 1;
str.tile = {'1' '4' '7' '2' '5' '8' '3' '6' '9'};
for tilex = 1:3
    for tiley = 1:3
        
       
        label = { num2str(Hzx(tilex))   num2str(Hzy(tiley))  };
        
        data2plotZ = [Zattend(tile, :); Zunattend2(tile, :)];
        data2plotR = [Rattend(tile, :); Runattend2(tile, :)];
        
        h1=figure(1);
        errorbar_groups(data2plotZ, zeros(2,2)', 'bar_colors', [0.3 0.3 1; 1 0.3 0.3  ], 'bar_names', label, 'FigID', h1);
        set(gca, 'TickDir', 'out', 'box','off', 'FontSize', 14, 'FontName', 'Arial')
        
        legend({'Attended' 'Unattended-out of stripe'});
        title(  ['SSVEP Z scores Tile ' str.tile{tile}]  )
        ylabel('Zscore')
        xlabel('Frequency')
        ylim([-1.5 2.5]);
        
        h2=figure(2);
        errorbar_groups(data2plotR, zeros(2,2)', 'bar_colors', [0.3 0.3 1; 1 0.3 0.3  ], 'bar_names', label, 'FigID', h2);
        set(gca, 'TickDir', 'out', 'box','off', 'FontSize', 14, 'FontName', 'Arial')
        
        legend({'Attended' 'Unattended-out of stripe'});
        title(  ['SSVEP amplitude Tile ' str.tile{tile}]  )
        ylabel('SSVEP amp (µV)')
        xlabel('Frequency')
        ylim([0 6]);
        
        
        saveas(h1, [ cd '/results/tile' str.tile{tile} 'Z_SSVEPs_truly unattended.png']);
        IM1{tilex, tiley} = imread( [ cd '/results/tile' str.tile{tile} 'Z_SSVEPs_truly unattended.png'] );
        
        saveas(h2, [ cd '/results/tile' str.tile{tile} 'SSVEPs_truly unattended.png']);
        IM2{tilex, tiley} = imread( [ cd '/results/tile' str.tile{tile} 'SSVEPs_truly unattended.png'] );
        
        tile = tile+1;
    end
end

imwrite( cell2mat(IM1), [ cd '/results/Z_SSVEPsbytile_truly unattended.png'] )
imwrite( cell2mat(IM2), [ cd '/results/SSVEPsbytile_truly unattended.png'] )

%% Intermod
close all

str.Hz = {'f1' 'f2' 'f3' 'f4' 'f5' 'f6'};
str.Hzdoub = {'2*f1' '2*f2' '2*f3' '2*f4' '2*f5' '2*f6'};
str.Hz2 = {'f1+f4' 'f2+f4' 'f3+f4' 'f1+f5' 'f2+f5' 'f3+f5' 'f1+f6' 'f2+f6' 'f3+f6'};
str.Hz3 = {'f1-f4' 'f2-f4' 'f3-f4' 'f1-f5' 'f2-f5' 'f3-f5' 'f1-f6' 'f2-f6' 'f3-f6'};

Hz = [4.97 20.57 13.09 8.47 7.58 6.29];
Hz2 = [13.4400   29.0400   21.5600   12.5500   28.1500   20.6700   11.2600   26.8600   19.3800]; %Hzx+Hzy
Hz3 = [ 3.5000   12.1000    4.6200    2.6100   12.9900    5.5100    1.3200   14.2800    6.8000];
  
% Hz3 = [];
% for j = 1:3
%     for i = 1:3
%         Hz3 = [ Hz3, abs(Hzx(i)-Hzy(j))];
%     end
% end

h = figure; hold on;

stem(Hz, ones(length(Hz),1)*2, 'r')
stem(Hz*2, ones(length(Hz),1)*1.5, 'g')
stem(Hz2, ones(length(Hz2),1)*1, 'b')
stem(Hz3, ones(length(Hz3),1)*0.5, 'k')


for H = 1:length(Hz)
    text(Hz(H), 2.05, str.Hz{H})
    text(Hz(H)*2, 1.55, str.Hzdoub{H})
end

for H = 1:length(Hz2)
    text(Hz2(H), 1.05, str.Hz2{H})
    text(Hz3(H), 0.55, str.Hz3{H})
end

legend({'fund' '2*fund' 'a+b' 'a-b'})
xlim([0 45])
ylim([0 3])
xlabel('Frequency (Hz)')

saveas(h, [ cd '/results/FREQUENCIES.png']);
saveas(h, [ cd '/results/FREQUENCIES']);