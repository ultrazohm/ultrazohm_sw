function modes = compute_modes(x,u,t)

  tmp1 = (x(1) + ((-1.0) .* u(1)));
  tmp2 = (((-1.0) .* x(2)) + ((-1.0) .* u(1)));
  tmp3 = (((-1.0) .* x(3)) + ((-1.0) .* u(1)));
  tmp4 = (x(2) + ((-1.0) .* u(1)));
  tmp5 = (((-1.0) .* x(1)) + ((-1.0) .* u(1)));
  tmp6 = (x(3) + ((-1.0) .* u(1)));

  mode1 = (tmp1 > ((0.8) .* (1.0)));
  mode2 = (u(2) > (0.5));
  mode3 = (tmp2 > ((0.8) .* (1.0)));
  mode4 = (u(3) > (0.5));
  mode5 = (tmp3 > ((0.8) .* (1.0)));
  mode6 = (u(4) > (0.5));
  mode7 = (tmp4 > ((0.8) .* (1.0)));
  mode8 = (u(5) > (0.05));
  mode9 = (tmp5 > ((0.8) .* (1.0)));
  mode10 = (u(6) > (0.5));
  mode11 = (tmp6 > ((0.8) .* (1.0)));
  mode12 = (u(7) > (0.05));

  modes = [mode1 mode2 mode3 mode4 mode5 mode6 mode7 mode8 mode9 mode10 mode11 mode12];

end
