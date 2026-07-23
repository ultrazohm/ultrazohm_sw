wait_on_hw_ila [get_hw_ilas -of_objects [get_hw_devices xczu9_0] -filter {CELL_NAME=~"zusys_i/uz_user/ila_0"}]
display_hw_ila_data [upload_hw_ila_data [get_hw_ilas -of_objects [get_hw_devices xczu9_0] -filter {CELL_NAME=~"zusys_i/uz_user/ila_0"}]]
write_hw_ila_data -csv_file -force {C:\Users\jonat\Documents\iladata.csv} hw_ila_data_5