alpha = 0.3;

%% random test signal
testsignal =-2 + (2+2)*rand(20,1);
testsignal=single(testsignal);
[expectedsignal] = exponentialsmoothing(alpha,testsignal);
plot(testsignal,'-o','Color','r','DisplayName','testsignal'); hold on;
%% matlab smooth method
plot(expectedsignal,'Color','g','DisplayName','filtersignal');
legend
%% export to array for vscode

for i=1:numel(expectedsignal)
    expectedsignalstr{:,i}= append(num2str(expectedsignal(i)),'f');
end
for i=1:numel(testsignal)
    testsignalstr{:,i} = append(num2str(testsignal(i)),'f');
end
writecell(expectedsignalstr,'expectedsignal.csv','Delimiter','comma');
writecell(testsignalstr,'testsignal.csv','Delimiter','comma');

function [filty] = exponentialsmoothing(alpha,testsignal)
    filty= zeros(length(testsignal),1);
    filty(1)=testsignal(1);
    for n = 2:length(testsignal)
            % apply the exponential smoother [1]
            filty(n) = alpha*testsignal(n) + (1-alpha)*testsignal(n-1);
    end
end
