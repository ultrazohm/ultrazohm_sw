function [rangeX,rangeY,grid] = interpol_flux_scatter_psiq (array,rangeX,rangeY)
% Author Philipp Gebhardt
% Oktober 2019
%
% This function is an inter- and extrapolation of an inregular scattered x y z measuring data, 
% which generates a regular grid of a q-flux map of a permanent magnet synchonous machine.
% These machines usually have an linear flux map but can differ in
% saturation from the linear model. Thats why this function approximates
% the scattered data to a linear surface whichs deviation is assumed with
% inverse distance weihting from the scattered data. 
% 
% Input "array" is from type single(100,3) = irregular scattered x y z data
% Input "rangeX" is from type single(20,1) = range of x-Axes from new grid = Output also
% Input "rangeY" is from type single(20,1) = range of y-Axes from new grid = Output also 
% Output "grid"  is from type single(20,20) = z values of regular grid 

%initialise variables
OA=single(zeros(3,1));
i1=single(0);
i2=single(0);
i3=single(0);
e=single(0);

%Find evaluable range of psi array

%initialise counter
n_curr=single(0);

%check content of array fields
for(k=single(1):single(length(array(1,:))))
   
    if(array(1,k)~=0||array(2,k)~=0||array(3,k)~=0)
             %set counter if content exist 
             n_curr=k;
    end
    
end

%initialise normal vectors
N=single(zeros(3,100));

%Create empty grid
grid=single(zeros(length(rangeX),length(rangeY)));

%Calculate normal vecotr of Triangles between psi array values 
for(k=single(1):single(n_curr))    
    
    %Find nearest neighbours 
    for(t=single(1):single(n_curr))
     
        %Calculate distance
        array(4,t)=( (array(1,t) - array(1,k) )^2  +  ( array(2,t)-array(2,k) )^2    )^0.5;
    
    end
    
    %nearest is point itself
    i1=k;
    
    %prevent self identification
    array(4,i1)=2000;
    
    %initialize error
    e=single(1000);
    
    %Find most appropriate Triangle 
    % -> no small angles in the triangle = Delaunay-Triangulation
    
    %consider all possible triangles between the psi array values
    for(t=single(1):single(n_curr))
    if(abs(array(4,t))<e)
        i2=t;
        e=array(4,t);
    end    
    end
    
    
    %Find most appropriate Triangle 
    % -> no small angles in the triangle = Delaunay-Triangulation
    
    %consider all possible triangles between the psi array values
    for(t=single(1):single(n_curr))
    if(t~=i1 && t~=i2)
        
    % Calculate scalarproduct of every possible triangle and divide throuh
    % norm of vectors to get cos() of angle
    AB=[array(1,i2)-array(1,i1);array(2,i2)-array(2,i1);array(3,i2)-array(3,i1)];
    AC=[array(1,t)-array(1,i1);array(2,t)-array(2,i1);array(3,t)-array(3,i1)];
    
    array(4,t)=abs(dot(AB,AC)/(norm(AB)*norm(AC)));
    else
        array(4,t)=1e20;
    end
    end

    %finde kleinstes Skalarprodukt
    
    
    %find smallest cos() of angle because triangle should be as right-angled as
    %possible and cos(90°)=0
    
    e=single(1e19);
    for(t=single(1):single(n_curr))
    if(abs(array(4,t))<e)
        i3=t;
        e=array(4,t);
    end    
    end
        
    %create triangle vectors
    
    AB=[array(1,i2)-array(1,i1); array(2,i2)-array(2,i1); array(3,i2)-array(3,i1)];
    AC=[array(1,i3)-array(1,i1); array(2,i3)-array(2,i1); array(3,i3)-array(3,i1)];
    
    %calculate the normal vector
    N(:,k)=cross(AB,AC); 
    
    %normalize the normal vector
    abs_N=(N(1,k)*N(1,k)+N(2,k)*N(2,k)+N(3,k)*N(3,k))^0.5;
    N(:,k)=N(:,k)/abs_N;
    
    %Reverse negative normal vectors
    if (N(3,k)<0)
    N(:,k)=N(:,k)*(-1);
    end
   %Prevent unplausible gradientsn
    if (N(2,k)>0)
    N(2,k)=0;
    end
    
end



%optimize grid data 

%repeat for every grid value
for(m=single(1):single(length(rangeX(1,:))))
    for(n=single(1):single(length(rangeY(1,:))))
    
    %initialize variables     
    dis_gitter=single(0);
    dis_gitter_alt=single(1000);
    N_aver=single(zeros(3,1));
    
        % repeat for every psi_array value
        for(k=single(1):single(n_curr))    
       
    	%Calculate distance to grid data value
            
        dis_gitter=( (array(1,k)-rangeX(m))^2+(array(2,k)-rangeY(n))^2  )^0.5;
        
            if(dis_gitter<dis_gitter_alt)
                dis_gitter_alt=dis_gitter;
                OA=[array(1,k); array(2,k); array(3,k)];
               % N_aver=N(:,k); %Use this N_aver if you do not want to use the distance weighting
            end
     
        end

    %Presumption L ~ const, Averageing the gradient with inverse distance weighting    
    
    %Initialize variables
     
    N_sum=single(zeros(3,1));
    dis_sum=single(0);
 
    %weighting factor p for consistent gradient of the surface
    %the lower p is the more  is the gradient unified 
 
    p=2;    %=square weighting  
  
    %Sum up normal vectors and weight the vectors by distance to the grid
    %point
  
    for(t=single(1):single(n_curr))
    array(4,t)=( (rangeX(m) - array(1,t) )^2  +  ( rangeY(n)-array(2,t) )^2    )^0.5;
    N_sum(:,1)=N_sum(:,1)+N(:,t)*(1/array(4,t))^p; 
    dis_sum=dis_sum+(1/array(4,t))^p;
    end

    %Calculate griddata with averaged normal vector starting at the nearest
    %measuring points 
    
    %Average N_aver
    N_aver(:)=N_sum(:)/(dis_sum);
    %Normalizing the Vectors N_aver
    abs_N=(N_aver(1)*N_aver(1)+N_aver(2)*N_aver(2)+N_aver(3)*N_aver(3))^0.5;
    N_aver(:)=N_aver(:)/abs_N;
    
    grid(n,m)=( dot(N_aver,OA)-N_aver(1)*rangeX(m)-N_aver(2)*rangeY(n))/( N_aver(3) );       
    end
end

grid_old=grid;

%Smooth Surface


for(m=single(1):single(length(rangeX(1,:))))
    for(n=single(1):single(length(rangeY(1,:))))
    grid_sum=single(0);
    grid_count=single(0);

     for(t=single(0):single(2)) 
         
     if(t+n<=length(rangeY(1,:))&&t~=0&&n-t>0)
      grid_sum=grid_sum+grid_old(n+t,m);
       grid_sum=grid_sum+grid_old(n-t,m);
      grid_count=grid_count+2;
     end
     
     if(t+m<=length(rangeX(1,:))&&m-t>0&&t~=0)
     grid_sum=grid_sum+grid_old(n,m+t);
     grid_sum=grid_sum+grid_old(n,m-t);
     grid_count=grid_count+2;
     end
     
     if(t+n<=length(rangeY(1,:))&&t~=0&&n-t>0&&t+m<=length(rangeX(1,:))&&m-t>0&&t~=0)
     grid_sum=grid_sum+grid_old(n+t,m+t);
     grid_sum=grid_sum+grid_old(n+t,m-t);
     grid_sum=grid_sum+grid_old(n-t,m-t);
     grid_sum=grid_sum+grid_old(n-t,m+t);
     grid_count=grid_count+4;
     end
     
     if(t==0)
         grid_sum=grid_sum+grid_old(n,m);
         grid_count=grid_count+1;
     end
     
     end
        grid(n,m)=grid_sum/grid_count;
    end
end

end