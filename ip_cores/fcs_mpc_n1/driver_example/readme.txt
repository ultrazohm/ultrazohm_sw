this will probably not work out of the box.
it is a subset of my test bench implementation 

to dos:
- adjust name of ip core, in my casae the ip core name is "XCtrl_wrapper"
- HLS generates a low-lower driver with the same name that is included in "xctrl_wrapper.h" which is part of the Platform
- replace float->u32 conversion with uz_* functions
- the entries of the "plant" struct (which includes the systems matrices) is exported from matlab and is therefore in double
- to export the matrices from matlab into a header file I used the functions "write2headerfile" and "write_matrix2file" which are also included in this folder. "write2headerfile" will need adjustments
- the header file is then included in "load_testvector.c" which copies the entries into the "plant" struct.
- double-check if row-major or coloumn-major notation is used thoroughly. It works the way it is now, but it could very well be, that I switched it up twice. 

intended call order for initialization 
1. void load_plant_model(&plant_model);
2. pred_ctrl_N1_intialize(&plant_model, lambda_u);