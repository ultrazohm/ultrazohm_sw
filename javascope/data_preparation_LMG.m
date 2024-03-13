[l w] = size(measurement.Transient_3_0_173160_);
i_ph = zeros(3,l,w);
%%
for i=1:w
i_ph(1,1:l,i) = measurement.Transient_3_0_173160_(:,i);
i_ph(2,1:l,i) = measurement.Transient_4_0_173160_(:,i);
i_ph(3,1:l,i) = measurement.Transient_5_0_173160_(:,i);
end