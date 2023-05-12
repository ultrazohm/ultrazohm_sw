function [] = write_matrix2file(variable, head, fid, isdouble)

%check if variable array or matrix
is_array  = (1==size(variable,1))|| (1==size(variable,2));
num_rows  = size(variable,1);
str_cell  = cell(1, num_rows);

if(exist('isdouble', 'var'))
    precision = 15;
else
    precision = 8;
end 

for ii=1:num_rows
    str          = num2str(variable(ii,:),precision);
    str_cell{ii} = str;
end
str_cell_comma = regexprep(str_cell,'\s+',',\t');
fprintf(fid,['\t',head]);
for ii=1:num_rows
    if (is_array)
        fprintf(fid,['\n\t\t',str_cell_comma{ii}]);
    else % if variable is a matrix
        fprintf(fid,['\n\t\t{',str_cell_comma{ii},'}']);
    end
    if ii<num_rows
        fprintf(fid,[',']);
    end
end
fprintf(fid,'\n\t};\n\n');

end

