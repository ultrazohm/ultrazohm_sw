%Plot MMPA

Iq = -I_max:I_max;
CurrentCircle_Id_plus = sqrt(I_max*I_max - Iq.*Iq); 
CurrentCircle_Id_minus = -CurrentCircle_Id_plus;

plot(CurrentCircle_Id_plus, Iq, 'r')
hold on;
plot(CurrentCircle_Id_minus, Iq, 'r')

CenterOfEllipses_Id = -psi_pm/Ld;


Iq = -2*I_max:2*I_max;
%MMPA
MMPA_Id = -psi_pm/(2*(Ld-Lq)) - sqrt(psi_pm*psi_pm/(4*(Ld-Lq)^2)+Iq.*Iq);

%Speed Ellipses
U_FA = U_DC/sqrt(3) - R*I_max;
Id_speed = zeros(9,length(Iq));
for i = 1:10
    w_el = (i*500+2500)*pi*zp/30;
    Id_speed(i,:) = (sqrt((U_FA/w_el)^2 - (Lq*Iq).^2)-psi_pm)/Ld;
    
end

%Torque curves 
Iq_M = 0:2*I_max;
TorqueConstant_Id = zeros(10,length(Iq_M));
for i = 1:10
    M_const = i+0.5; %Nm
    TorqueConstant_Id(i,:) = (2*M_const/(3*zp) - psi_pm.*Iq_M)./((Ld-Lq).*Iq_M);
end


plot(CenterOfEllipses_Id, 0, 'go')
plot(MMPA_Id, Iq, 'b--', 'LineWidth',2.0)
plot(Id_speed,Iq, 'k--')
plot(TorqueConstant_Id,Iq_M,'g')
axis equal
grid on;
xlim([CenterOfEllipses_Id, 200])

%Calculate w_b (Eckdrehzahl)
% 1. Schnittpunkt Stromkreis und MMPA berechnen
Id_Intersection_Wb = -psi_pm/(4*(Ld-Lq)) - sqrt(psi_pm*psi_pm/(16*(Ld-Lq)^2)+(I_max*I_max/2));
Iq_Intersection_Wb = sqrt(I_max^2 - Id_Intersection_Wb^2);
w_b = U_FA/sqrt((Lq*Iq_Intersection_Wb)^2 + (Ld*Id_Intersection_Wb+psi_pm)^2);
n_cut = w_b*30/(pi*zp);


%Calculate maximum speed 
w_c = U_FA/(psi_pm+Ld*(-I_max));
n_max = w_c*30/(pi*zp);

%Calculate list of Intersections between Speed-Ellipses and Current Circle
List_wEl_Intersection_Speed = linspace(n_cut,n_max,15);
List_Iq_Intersection_Speed = zeros(length(List_wEl_Intersection_Speed),1);
List_Id_Intersection_Speed = zeros(length(List_wEl_Intersection_Speed),1);
for i = 1:length(List_wEl_Intersection_Speed)
    w_el = List_wEl_Intersection_Speed(i)*zp*pi/30;
    syms iq positive
    eqn = (sqrt((U_FA/w_el)^2 - (Lq*iq)^2)-psi_pm)/Ld == -sqrt(I_max*I_max - iq*iq);
    S = solve(eqn, iq);
    if isempty(S)
        List_Iq_Intersection_Speed(i) = 0;
        List_Id_Intersection_Speed(i) = 0;
    else
        List_Iq_Intersection_Speed(i) = double(S);
        List_Id_Intersection_Speed(i) = -sqrt(I_max*I_max - List_Iq_Intersection_Speed(i)^2);
    end
       
end

plot(List_Id_Intersection_Speed,List_Iq_Intersection_Speed, 'rx')

%Calculate Intersection of Torque Curves and MMPA
List_M_const = 0:0.5:10;
List_Iq_Torque = zeros(length(List_M_const),1);
List_Id_Torque = zeros(length(List_M_const),1);
for i = 1:length(List_M_const)
    M_val = List_M_const(i);
    syms iq positive
    eqn = (2*M_val/(3*zp) - psi_pm*iq)/((Ld-Lq)*iq) == -psi_pm/(2*(Ld-Lq)) - sqrt(psi_pm*psi_pm/(4*(Ld-Lq)^2)+iq*iq);
    S = solve(eqn, iq);
    if isempty(S)
        List_Iq_Torque(i) = 0;
        List_Id_Torque(i) = 0;        
    else
        List_Iq_Torque(i) = double(S);
        List_Id_Torque(i) = -psi_pm/(2*(Ld-Lq)) - sqrt(psi_pm*psi_pm/(4*(Ld-Lq)^2)+List_Iq_Torque(i)^2);
    end
end
plot(List_Id_Torque, List_Iq_Torque, 'bo');

%Calculate Intersection of Torque Curves and CurrentCircle
List_M_const = 0:0.5:10;
List_Iq_Torque_Imax = zeros(length(List_M_const),1);
List_Id_Torque_Imax = zeros(length(List_M_const),1);
for i = 1:length(List_M_const)
    M_val = List_M_const(i);
    syms iq positive
    eqn = (2*M_val/(3*zp) - psi_pm*iq)/((Ld-Lq)*iq) == -sqrt(I_max^2 - iq^2);
    S_Imax = solve(eqn, iq);
    if isempty(S_Imax)
        %No Intersection
        List_Iq_Torque_Imax(i) = -1;
        List_Id_Torque_Imax(i) = -1;
        if M_val == 0
            List_Iq_Torque_Imax(i) = 0;
            List_Id_Torque_Imax(i) = 0;
        end
    elseif length(S_Imax) == 1
        List_Iq_Torque_Imax(i) = double(S_Imax);
        List_Id_Torque_Imax(i) = -sqrt(I_max^2 - List_Iq_Torque_Imax(i)^2);
    else
        List_Iq_Torque_Imax(i) = double(S_Imax(1));
        List_Id_Torque_Imax(i) = -sqrt(I_max^2 - List_Iq_Torque_Imax(i)^2);
    end
end

List_M_Imax =  List_M_const(List_Iq_Torque_Imax ~= -1);
List_Id_Torque_Imax = List_Id_Torque_Imax(List_Iq_Torque_Imax ~= -1);
List_Iq_Torque_Imax = List_Iq_Torque_Imax(List_Iq_Torque_Imax ~= -1);

List_Id_Torque_Imax(length(List_Id_Torque_Imax)+1) = Id_Intersection_Wb;
List_Iq_Torque_Imax(length(List_Iq_Torque_Imax)+1) = Iq_Intersection_Wb;
List_M_Imax(length(List_M_Imax)+1) = 3*zp/2 * (psi_pm*Iq_Intersection_Wb+(Ld-Lq)*Id_Intersection_Wb*Iq_Intersection_Wb);



plot(List_Id_Torque_Imax, List_Iq_Torque_Imax, 'go');





% iq_table = zeros(length(List_wEl_Intersection_Speed)+1,length(List_M_const));
% %First row for speed = 0
% iq_table(1,:) = real(List_Iq_Torque');
% for k = 1:length(List_Iq_Torque)
%    if iq_table(1,k) > List_Iq_Intersection_Speed(1)
%        iq_table(1,k) = List_Iq_Intersection_Speed(1);
%    end
% end
% %Second row for speed = n_cut --> Same values
% iq_table(2,:) = iq_table(1,:);
% 
% for i = 1:(length(List_wEl_Intersection_Speed)-1)
%     for k = 1:length(List_M_const)
%        if List_Iq_Torque_Imax(k) <= List_Iq_Intersection_Speed(i+1) && List_Iq_Torque_Imax(k) >= 0
%            iq_table(i+2,k) = real(List_Iq_Torque_Imax(k));
%        else
%            iq_table(i+2,k) = real(List_Iq_Intersection_Speed(i+1));
%        end 
%     end
% end

