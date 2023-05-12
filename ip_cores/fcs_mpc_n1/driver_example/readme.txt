this will probably not work out of the box.
it is a subset of my test bench implementation 

to dos:
- adjust name of ip core, in my casae the ip core name is "XCtrl_wrapper"
- HLS generates a low-lower driver with the same name that is included in "xctrl_wrapper.h" which is part of the Platform
- replace float->u32 conversion with uz_* functions
- the entries of the "plant" struct (which includes the systems matrices) is exported from matlab and is therefore in double
- to export the matrices from matlab into a header file I used the functions "write2headerfile" and "write_matrix2file" which are also included in this folder. "write2headerfile" will need adjustments
