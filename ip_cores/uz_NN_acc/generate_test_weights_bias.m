rng(0);
export=false;
%% Network dimensions
in_size = 32;
hidden_size = 64;
num_hidden = 10;
out_size = 16;

%% Helper: He initialization
he_init = @(fan_in, fan_out) sqrt(2/fan_in) * randn(fan_in, fan_out);

%% Allocate weights & biases
B = cell(1, num_hidden);
Bias = cell(1, num_hidden);

% Input → first hidden
B{1} = he_init(in_size, hidden_size);
Bias{1} = zeros(1, hidden_size);

% Hidden → hidden
for i = 2:num_hidden
    B{i} = he_init(hidden_size, hidden_size);
    Bias{i} = zeros(1, hidden_size);
end

% Output layer
B_out = he_init(hidden_size, out_size);
Bias_out = zeros(1, out_size);

%% Forward pass function
forward_nn = @(x) nn_forward(x, B, Bias, B_out, Bias_out);

%% Example input (32 values in [0,1])
x = repmat(0.5,1,32);%rand(1, in_size);

%% Run network
y = forward_nn(x);

disp("Output:")
disp(y)

%% ===== EXPORT WEIGHTS =====
if(export)
    num_hidden = length(B);

    for i = 1:num_hidden
        filename = sprintf('Weights_Layer_%d.csv', i);
        write_matrix_with_f(filename, B{i});
    end

    % Output layer weights
    write_matrix_with_f('Weights_Layer_out.csv', B_out);

%% ===== EXPORT BIASES =====
    for i = 1:num_hidden
        filename = sprintf('Bias_Layer_%d.csv', i);
        write_matrix_with_f(filename, Bias{i});
    end

    % Output layer bias
    write_matrix_with_f('Bias_Layer_out.csv', Bias_out);
end

function y = nn_forward(x, B, Bias, B_out, Bias_out)

    % Hidden layers (ReLU)
    for i = 1:length(B)
        x = max(0, x * B{i} + Bias{i});
    end

    % Output layer (tanh)
    y = tanh(x * B_out + Bias_out);

    % Scale from [-1,1] → [0,100]
    %y = (y + 1) * 50;

end
function write_matrix_with_f(filename, M)

    fid = fopen(filename, 'w');

    % Flatten row-wise (matches HLS typical layout)
    M_flat = M';
    M_flat = M_flat(:);

    for i = 1:length(M_flat)
        val = M_flat(i);

        % Format number
        str = sprintf('%.7g', val);

        % Ensure decimal point exists (for C float compatibility)
        if ~contains(str, '.') && ~contains(str, 'e')
            str = [str, '.0'];
        end

        % Write with 'f'
        fprintf(fid, '%sf', str);

        if i ~= length(M_flat)
            fprintf(fid, ',');
        end
    end

    fclose(fid);
end