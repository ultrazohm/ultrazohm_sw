function [out] = GenerateDutyCycle(VDC,voltage)
   DutyCycle  = ( (voltage / (VDC/single(2)) + single(1)) /single(2)); 
   if(DutyCycle < 0)
       out = single(0);
   elseif (DutyCycle > 1)
       out = single(1);
   else
       out = DutyCycle;
   end
end

