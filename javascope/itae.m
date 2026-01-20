function [itae] = itae(set_point,actual_value,time,Ts)
% Calculates ITAE cirteria
%   Takes three vectors with set-point values, actual values, and a vector with time stamps
%   time(1) is treated as t=0.0

% Make sure dimensions match
if(length(set_point) > length(actual_value))
    index=length(actual_value);
elseif(length(set_point) < length(actual_value))
    index=length(set_point);
else
    index=length(set_point); % length is the same
end
%assert(length(set_point) == length(time));

error=set_point(1:index)-actual_value(1:index);
time_with_offset=time-time(1);
time_with_offset=time_with_offset(1:index);
assert(time_with_offset(1) == 0);

itae=trapz(Ts,abs(error) .* time_with_offset ) ;
end

