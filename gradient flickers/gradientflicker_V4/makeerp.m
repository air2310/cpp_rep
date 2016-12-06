function [ERP, AMP] = makeerp(data, Lim, COND, TYPE, LATENCY, fs, n, S)

lim.x = ceil(Lim*fs);
lim.x(2) = lim.x(2) - 1;


for C =1:n.cond
    
    idx = ismember( TYPE, COND{C}  ); % find cue trigger
    
    latency = LATENCY(idx);
    
    start = round( latency + lim.x(1) );
    stop = round( latency + lim.x(2) );
    
    trial = NaN( n.x, n.channels, length(latency) );
    
    for E =1:length(latency)
        disp([S C E length(latency)]);
        
        
        data2use = data(:, start(E):stop(E) )';
        
        
        data2use = detrend(data2use,'linear');
        data2use = detrend(data2use,'constant');
        data2use = data2use - repmat( data2use(1,:), size(data2use,1), 1);
        
        trial(:,:,E) = data2use;
%         plot(data2use)
    end
    
    %% gather epochs, make ERP
    
    erp = nanmean(trial,3);
    
    ERP(:,:,C) = erp;
    
    amp = abs( fft( erp ) )/n.x;
    amp(2:end-1,:) = amp(2:end-1,:)*2; % double amplitudes
    
    AMP(:,:,C) = amp;
    
end
