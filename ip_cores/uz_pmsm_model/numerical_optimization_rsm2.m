% Fitting_flux_approximation_lsqnonlin
close all;
clear;
rng(0);

%% Hoerner PMSM
load('kennfeld_klein_Imax.mat')

[Xsoll,Ysoll] = meshgrid(0:5:150);
Psi_d_fine = interp2(i_d_sim,i_q_sim,psi_d_sim,Xsoll,Ysoll,'makima');
Psi_q_fine = interp2(i_d_sim,i_q_sim,psi_q_sim,Xsoll,Ysoll,'makima');
% Currents
id = Xsoll;
iq = Ysoll;
%Psi_d
psi_d = Psi_d_fine;
%Psi_q
psi_q = Psi_q_fine;
figure
surf(id,iq,psi_d)
title('\psi_d original')

figure
surf(id,iq,psi_q)
title('\psi_q original')

%% Prepare interpolation (ground truth flux maps)

id_vec = id(1,:);
iq_vec = iq(:,1);

F_psi_d = griddedInterpolant({id_vec, iq_vec}, psi_d', 'spline', 'nearest');
F_psi_q = griddedInterpolant({id_vec, iq_vec}, psi_q', 'spline', 'nearest');

%% Build grid once (important for speed)

[ID,IQ] = meshgrid(id_vec,iq_vec);

psi_d_true = F_psi_d(ID,IQ);
psi_q_true = F_psi_q(ID,IQ);

%% Build robust initial guess from 1D slices

[p0,lb,ub] = build_initial_guess_and_bounds(id_vec,iq_vec,psi_d_true,psi_q_true);

% Keep dimension-consistent bounds from initializer
lb = lb(:);
ub = ub(:);
%% Optimization options

options = optimoptions('lsqnonlin',...
    'Algorithm','trust-region-reflective',...
    'Display','iter',...
    'MaxIterations',4000,...
    'MaxFunctionEvaluations',80000,...
    'StepTolerance',1e-14,...
    'FunctionTolerance',1e-14,...
    'OptimalityTolerance',1e-14,...
    'FiniteDifferenceType','central',...
    'ScaleProblem','jacobian');

%% Run optimization

res_fun = @(p) flux_residuals(p,ID,IQ,psi_d_true,psi_q_true);

[param_opt,~] = lsqnonlin(res_fun,p0,lb,ub,options);

% Continuation run: restart from previous optimum with tighter tolerances
options_refine = optimoptions(options,...
    'MaxIterations',6000,...
    'MaxFunctionEvaluations',120000,...
    'StepTolerance',1e-16,...
    'FunctionTolerance',1e-16,...
    'OptimalityTolerance',1e-16);

[param_opt,resnorm] = lsqnonlin(res_fun,param_opt,lb,ub,options_refine);

disp('Optimized parameters:')
disp(param_opt)

%% Evaluate fitted model

[psi_d_fit,psi_q_fit] = predict_psi_dq(ID,IQ,param_opt);

figure
surf(ID,IQ,psi_d_fit)
title('Fitted \psi_d')

figure
surf(ID,IQ,psi_q_fit)
title('Fitted \psi_q')

%% Error plots

figure
surf(ID,IQ,psi_d_true - psi_d_fit)
title('Error \psi_d')

figure
surf(ID,IQ,psi_q_true - psi_q_fit)
title('Error \psi_q')


%% Evaluate fitted model
[psi_d_fit,psi_q_fit] = predict_psi_dq(ID,IQ,param_opt);

%% Compute relative errors
rel_err_d = (psi_d_true - psi_d_fit) ./ (abs(psi_d_true) + 1e-8);
rel_err_q = (psi_q_true - psi_q_fit) ./ (abs(psi_q_true) + 1e-8);

%% -------------------------------
%% Combined plotting in one figure
figure('Position',[100 100 1200 800])

% Original vs fitted psi_d
subplot(2,2,1)
surf(ID,IQ,psi_d_true)
title('\psi_d original','Interpreter','latex')
xlabel('i_d [A]')
ylabel('i_q [A]')
zlabel('\psi_d [Wb]')
shading interp
colorbar

subplot(2,2,2)
surf(ID,IQ,psi_d_fit)
title('\psi_d fitted','Interpreter','latex')
xlabel('i_d [A]')
ylabel('i_q [A]')
zlabel('\psi_d [Wb]')
shading interp
colorbar

% Relative error psi_d
subplot(2,2,3)
surf(ID,IQ,rel_err_d)
title('Relative error \psi_d','Interpreter','latex')
xlabel('i_d [A]')
ylabel('i_q [A]')
zlabel('Relative error')
shading interp
colorbar

% Relative error psi_q
subplot(2,2,4)
surf(ID,IQ,rel_err_q)
title('Relative error \psi_q','Interpreter','latex')
xlabel('i_d [A]')
ylabel('i_q [A]')
zlabel('Relative error')
shading interp
colorbar

sgtitle('Flux fitting results and relative errors','Interpreter','latex')

%%
figure
subplot(1,2,1)
surf(ID,IQ,psi_d_true)
hold on
mesh(ID,IQ,psi_d_fit)
xlabel('id [A]')
ylabel('iq [A]')
zlabel('psi d [Wb]')

subplot(1,2,2)
surf(ID,IQ,psi_q_true)
hold on
mesh(ID,IQ,psi_q_fit)
xlabel('id [A]')
ylabel('iq [A]')
zlabel('psi d [Wb]')

%% ----------------------------------------------------
%% Residual function for lsqnonlin
function r = flux_residuals(p,ID,IQ,psi_d_true,psi_q_true)

[psi_d_pred,psi_q_pred] = predict_psi_dq(ID,IQ,p);

% Normalize residual channels so both axes are weighted similarly
scale_d = max(abs(psi_d_true(:))) + eps;
scale_q = max(abs(psi_q_true(:))) + eps;

err_d = (psi_d_pred - psi_d_true) ./ scale_d;
err_q = (psi_q_pred - psi_q_true) ./ scale_q;

r = [err_d(:); err_q(:)];

end

%% ----------------------------------------------------
%% Flux model
function [psi_d_approx, psi_q_approx] = predict_psi_dq(i_d, i_q, p)

ad1 = p(1);
ad2 = p(2);
ad3 = p(3);
ad4 = p(4);
ad5 = p(5);
ad6 = p(6);

aq1 = p(7);
aq2 = p(8);
aq3 = p(9);
aq4 = p(10);
aq5 = p(11);
aq6 = p(12);

k1 = p(13);
k2 = p(14);
k3 = p(15);



% Self flux
psidself = ad1 .* tanh(ad2 .* i_d) + ad3 .* i_d;
psiqself = aq1 .* tanh(aq2 .* i_q) + aq3 .* i_q;

f1=1-exp(-(ad4.*i_d).^2);
f2=1-exp(-(ad5.*i_d).^2);
f3=1-exp(-(ad6.*i_d).^2);

g1=1-exp(-(aq4.*i_q).^2);
g2=1-exp(-(aq5.*i_q).^2);
g3=1-exp(-(aq6.*i_q).^2);

f1_derv=2*ad4.^2 .*i_d .* exp(-(ad4.*i_d).^2);
f2_derv=2*ad5.^2 .*i_d .* exp(-(ad5.*i_d).^2);
f3_derv=2*ad6.^2 .*i_d .* exp(-(ad6.*i_d).^2);

g1_derv=2*aq4.^2 .*i_q .* exp(-(aq4.*i_q).^2);
g2_derv=2*aq5.^2 .*i_q .* exp(-(aq5.*i_q).^2);
g3_derv=2*aq6.^2 .*i_q .* exp(-(aq6.*i_q).^2);

psid_cross=k1 .* f1_derv .*g1 + k2 .*f2_derv .*g2 + k3 .*f3_derv .*g3;
psiq_cross=k1 .* f1 .*g1_derv + k2 .*f2 .* g2_derv + k3 .*f3 .*g3_derv;

psi_d_approx=psidself - psid_cross;
psi_q_approx=psiqself - psiq_cross;

end

%% ----------------------------------------------------
function y = stable_log_cosh(x)
% Numerically stable log(cosh(x))
% y = abs(x) + log1p(exp(-2 .* abs(x))) - log(2);
y=log(cosh(x));
end

%% ----------------------------------------------------
function [p0,lb,ub] = build_initial_guess_and_bounds(id_vec,iq_vec,psi_d_map,psi_q_map)

[~,id_null] = min(abs(id_vec));
[~,iq_null] = min(abs(iq_vec));
[~,id1] = max(abs(id_vec));
[~,iq1] = max(abs(iq_vec));

psi_d_iq_null = psi_d_map(iq_null,:);
psi_q_id_null = psi_q_map(:,id_null);
psi_d_iq1 = psi_d_map(iq1,:);
psi_q_id1 = psi_q_map(:,id1);

id_range = max(id_vec) - min(id_vec);
iq_range = max(iq_vec) - min(iq_vec);

% Deterministic, physics-aware seeds
ad_seed = [max(abs(psi_d_iq_null)); 2/max(id_range,1); id_vec(id_null)];
aq_seed = [max(abs(psi_q_id_null)); 2/max(iq_range,1); 0];
ad_cross_seed = [max(abs(psi_d_iq1)); 2/max(id_range,1); id_vec(id_null)];
aq_cross_seed = [max(abs(psi_q_id1)); 2/max(iq_range,1); 0];

opt1d = optimoptions('lsqnonlin',...
    'Algorithm','trust-region-reflective',...
    'Display','off',...
    'MaxIterations',400,...
    'MaxFunctionEvaluations',3000);

lb_d = [0; 1e-5; min(id_vec)];
ub_d = [2*max(abs(psi_d_map(:))) + eps; 1; max(id_vec)];
lb_q = [0; 1e-5; -5];
ub_q = [2*max(abs(psi_q_map(:))) + eps; 1; 5];

ad_self = lsqnonlin(@(ad) ad(1).*tanh(ad(2).*(id_vec-ad(3))) - psi_d_iq_null, ad_seed, lb_d, ub_d, opt1d);
aq_self = lsqnonlin(@(aq) aq(1).*tanh(aq(2).*iq_vec) + aq(3).*iq_vec - psi_q_id_null, aq_seed, lb_q, ub_q, opt1d);
% Keep cross fits (useful scale hints), but final p0 is remapped to the
% current 15-parameter prototype used in predict_psi_dq.
ad_cross = lsqnonlin(@(ad) ad(1).*tanh(ad(2).*(id_vec-ad(3))) - psi_d_iq1, ad_cross_seed, lb_d, ub_d, opt1d); %#ok<NASGU>
aq_cross = lsqnonlin(@(aq) aq(1).*tanh(aq(2).*iq_vec) + aq(3).*iq_vec - psi_q_id1, aq_cross_seed, lb_q, ub_q, opt1d); %#ok<NASGU>

% Parameter map for current predict_psi_dq:
% p = [ad1..ad6, aq1..aq6, k1..k3]
ad1 = ad_self(1);
ad2 = ad_self(2);
ad3 = ad_self(3);

aq1 = aq_self(1);
aq2 = aq_self(2);
aq3 = aq_self(3);

% Gaussian width seeds (must be > 0)
ad4 = max(2/max(id_range,1), 1e-4);
ad5 = max(4/max(id_range,1), 1e-4);
ad6 = max(6/max(id_range,1), 1e-4);

aq4 = max(2/max(iq_range,1), 1e-4);
aq5 = max(4/max(iq_range,1), 1e-4);
aq6 = max(6/max(iq_range,1), 1e-4);

% Seed k1..k3 from linear least squares on both axes simultaneously
[ID,IQ] = meshgrid(id_vec,iq_vec);

psidself = ad1 .* tanh(ad2 .* ID) + ad3 .* ID;
psiqself = aq1 .* tanh(aq2 .* IQ) + aq3 .* IQ;

rd = psidself - psi_d_map;
rq = psiqself - psi_q_map;

f1 = 1 - exp(-(ad4 .* ID).^2);
f2 = 1 - exp(-(ad5 .* ID).^2);
f3 = 1 - exp(-(ad6 .* ID).^2);

g1 = 1 - exp(-(aq4 .* IQ).^2);
g2 = 1 - exp(-(aq5 .* IQ).^2);
g3 = 1 - exp(-(aq6 .* IQ).^2);

f1_derv = 2 .* (ad4.^2) .* ID .* exp(-(ad4 .* ID).^2);
f2_derv = 2 .* (ad5.^2) .* ID .* exp(-(ad5 .* ID).^2);
f3_derv = 2 .* (ad6.^2) .* ID .* exp(-(ad6 .* ID).^2);

g1_derv = 2 .* (aq4.^2) .* IQ .* exp(-(aq4 .* IQ).^2);
g2_derv = 2 .* (aq5.^2) .* IQ .* exp(-(aq5 .* IQ).^2);
g3_derv = 2 .* (aq6.^2) .* IQ .* exp(-(aq6 .* IQ).^2);

A = [ ...
    [f1_derv(:).*g1(:), f2_derv(:).*g2(:), f3_derv(:).*g3(:)]; ...
    [f1(:).*g1_derv(:), f2(:).*g2_derv(:), f3(:).*g3_derv(:)] ...
    ];
b = [rd(:); rq(:)];

lambda = 1e-8;
k = (A.'*A + lambda*eye(3)) \ (A.'*b);
if any(~isfinite(k))
    k = [0;0;0];
end

p0 = [ad1;ad2;ad3;ad4;ad5;ad6;aq1;aq2;aq3;aq4;aq5;aq6;k(:)];

% Global bounds around physically meaningful ranges
psi_d_max = max(abs(psi_d_map(:))) + eps;
psi_q_max = max(abs(psi_q_map(:))) + eps;

% Bounds for [ad1..ad6, aq1..aq6, k1..k3]
k_lim = 20 * max([psi_d_max, psi_q_max]);

lb = [0, 1e-5, min(id_vec), ...
    1e-5, 1e-5, 1e-5, ...
    0, 1e-5, -5, ...
    1e-5, 1e-5, 1e-5, ...
    -k_lim, -k_lim, -k_lim];

ub = [2*psi_d_max, 1, max(id_vec), ...
    2, 2, 2, ...
    2*psi_q_max, 1, 5, ...
    2, 2, 2, ...
    k_lim, k_lim, k_lim];

lb = lb(:);
ub = ub(:);
end