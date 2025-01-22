function [y1,y2]=regressionline(Array,rejectOutliers)
%Evaluation of a linear regression line

%--------initializing---------------------------------------
gerade=zeros(2,1);
zaehler=single(0);
measSum=single(0);
iestSum=single(0);
Xy=single(0);
Xx=single(0);
meanMeas=single(0);
meanIest=single(0);
SS_xy=single(0);
SS_xx=single(0);

%--------summing up----------------------------------
for k=single(2):single(length(Array)-1)
    
    %----------reject outliers---------------------------
    if (k >5 && Array(k)>0)         
        if(( Array(k)<1.3*Array(k+1) || Array(k)<1.3*Array(k-1) ||rejectOutliers==0 ) && ( Array(k)>Array(k+1)*0.7  || Array(k)>Array(k-1)*0.7) ||rejectOutliers==0 )  
        zaehler=zaehler+1;
        measSum=measSum+k;
        iestSum=iestSum+Array(k);        
        Xy=k*Array(k)+Xy;
        Xx=k*k+Xx;
    end
    end   
end

%-------calculate mean-------------------------------
meanMeas=measSum/zaehler;
meanIest=iestSum/zaehler;

%----------calculate varianz--------------------------
    SS_xy = Xy-zaehler*meanMeas*meanIest; 
    SS_xx = Xx- zaehler*meanMeas*meanMeas; 

%-------viscous friction-------------------------------    
gerade(1)=single(SS_xy/SS_xx);

%-------Coulomb friction-----------------------------
gerade(2)=single(meanIest-(SS_xy/SS_xx)*meanMeas);

y1=single(gerade(1));
y2=single(gerade(2));

