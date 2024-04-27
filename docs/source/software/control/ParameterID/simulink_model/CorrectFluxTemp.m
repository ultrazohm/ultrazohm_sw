function CorrectFluxTemp(psi_array,psi_temp_const,Wtemp_out)
%Author Philipp Gebhardt
%Oktober 2019
%
%This function corrects the temperature specific d-flux offset in psi_array,
%which is a result of pm-flux decreasment at higher temperatures

for k=single(1):single(100)
   
    psi_array(5,k)=psi_array(5,k)+(psi_array(4,k)-Wtemp_out)*psi_temp_const;
    psi_array(4,k)=Wtemp_out;
    
end



end