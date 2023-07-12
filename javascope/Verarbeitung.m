clc
clear
close all

mittelwert_eta = zeros(4,8);
drehzahl = ["0000" "0300" "0700" "1050"];

for m = 1:length(drehzahl)
    fullname = append("C:\Users\Nina Diringer\repos\2022_10_leykam_diringer_schindler_mtpa\Messungen\Messungen LMG\300323_kont_MTPA_",drehzahl(m),"rpm.mat");
    load(fullname)
    P_el = P1_G1_Wide_W + P2_G1_Wide_W + P3_G1_Wide_W;
    eta = double(PSIM_POWER1_W)./double(P_el) .*-1;
    
    A = diff(PSIM_TORQUE1_Nm);
    B = find(abs(A)>0.01);
    B = [B;length(PSIM_TORQUE1_Nm)];
    
    for i = 1:length(B)-1
            mittelwert_eta(m,i) = mean(eta(B(i)+1:B(i+1)));
            mittelwert_torque(m,i) = mean(PSIM_TORQUE1_Nm(B(i)+1:B(i+1)))*-1;
    
    end
    
    plot(mittelwert_torque(m,:), mittelwert_eta(m,:));
    hold on
    grid on

end
%time = Daten(1).Values.Time;