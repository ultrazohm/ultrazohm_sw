# This script opens the .xdc constraint files and extract the relevant information from them
# like package pin, pulldown, iostandard
# Afterwards, it loads information extracted from Trenz pinout excel sheet to generate new files.
# 
# Author: Tomas P. Correa
# Date: check in git ;-)

import csv
from os import listdir, getcwd
from os.path import isfile, join

class XdcInfo:
    def __init__(self, port):
        self.package_pin = ""
        self.pulldown = ""
        self.iostandard = ""
        self.diff_term = ""
        self.diff_term_adv = ""
        self.module_net_name = ""
        self.connector_name = ""
        self.connector_number = ""
        self.port = port
    
    def write(self):
        output = ["# Port {} = {} ({}:{})\n".format(self.port, self.module_net_name, self.connector_name, self.connector_number)]
         #print("PORT", self.port, "pulldown ", self.pulldown, "iostandard", self.iostandard, "package_pin ", self.package_pin)
        if self.package_pin: 
            output.append("set_property PACKAGE_PIN " + self.package_pin + " [get_ports " + self.port + "]\n" ) 
        if self.pulldown: 
            output.append("set_property PULLDOWN " + self.pulldown + " [get_ports " + self.port + "]\n") 
        if self.diff_term: 
            output.append("set_property DIFF_TERM " + self.diff_term + " [get_ports " + self.port + "]\n") 
        if self.diff_term_adv: 
            output.append("set_property DIFF_TERM_ADV " + self.diff_term_adv + " [get_ports " + self.port + "]\n") 
        if self.iostandard: 
            output.append("set_property IOSTANDARD " + self.iostandard + " [get_ports " + self.port + "]\n") 
        return output

        
# it extracts the port info, removing last ] and all {} and finding all the existing ports that 
# match the string if it contains star (*) 
def extract_port(sp, dict):
    port = sp[:-1].replace('{','')
    port =  port.replace('}','')
    # if the port definition use star (*), find all ports that match
    if "*" in port:
        search_string = port.replace('*','')
        port = [item for item in dict.keys() if search_string in item]
        print(port)   
    else: # otherwise, make port a list, so we can iterate in anycase
        port = [port]
    return port

# it extracts port, package pin, pulldown, diff term, dif term adv properties from the xdc file and 
# returns a dictionary with the port as key and an XdcInfo object for every key
def extract_info_from_xdc(filename):
    xdc_input = open(filename)
    xdc_dict = {}

    for line in xdc_input:
        if line.startswith("#"):
            pass
        elif "set_property" in line:
            # check what is the property and assign to dict
            sl = line.split()
            if len(sl) > 4:
                port = extract_port(sl[4], xdc_dict)
                for p in port: # port must be a list, otherwise we will iterate the string characters 
                    if sl[1] == "PACKAGE_PIN":            
                        xdc_dict[p] = XdcInfo(p)
                        xdc_dict[p].package_pin = sl[2]
                    elif sl[1] == "PULLDOWN":
                        xdc_dict[p].pulldown = sl[2]  
                    elif sl[1] == "DIFF_TERM":
                        xdc_dict[p].diff__term = sl[2]
                    elif sl[1] == "DIFF_TERM_ADV":
                        xdc_dict[p].diff_term_adv = sl[2]
                    elif sl[1] == "IOSTANDARD":
                        xdc_dict[p].iostandard = sl[2]
    return xdc_dict

# it reads the pinout from the csv file extracted from Trenz pinout sheet                
def read_pinout(filename):
    with open(filename) as f:
        obj = csv.DictReader(f, delimiter=";")
        output = []
        for item in obj:         
            if item["FPGA Pin Name"] != "---" and item["FPGA Pin Name"] != "--" :
                output.append(item)
    return output
    
## ------------------- script begins here -------------------
# get all xdc files in folder
xdc_files = [f for f in listdir(getcwd()) if isfile(join(getcwd(), f)) and f.endswith((".xdc",".XDC"))]

# Package pins and B2B connector matching extracted from Trenz pinout sheet
# https://shop.trenz-electronic.de/Download/?path=Trenz_Electronic/Pinout
# if you want just to reprocess the existing xdc files to the same board, 
# just make target_filename = origin_filename
origin_filename = "TE0808_REV02.csv"
target_filename = "TE0803_REV02.csv"

dict_origin = read_pinout(origin_filename)
dict_target = read_pinout(target_filename)

# process one xdc at a time, extracting the relevant info and re-writing to a new .xdc
for xdc_input in xdc_files:
    f = open("new/"+xdc_input,'w')
    
    print(xdc_input)
    xdc_dict = extract_info_from_xdc(xdc_input)

    for port in xdc_dict.items():

        # find dict on the origin list that has the same package pin
        origin_info = [item for item in dict_origin if item["FPGA Pin Name"] == port[1].package_pin][0]
        port[1].connector_name = origin_info["C-Name"]
        port[1].connector_number = origin_info["C-Pin"]       
        # find dict on the target list that is connected to the same B2B connector pin
        target_info = [item for item in dict_target if item["C-Name"] == origin_info["C-Name"] and item["C-Pin"] == origin_info["C-Pin"]][0]
        # replace package_pin with the information of the target board
        port[1].package_pin = target_info["FPGA Pin Name"]
        port[1].module_net_name = target_info["Module Net Name"]

      
        f.writelines(port[1].write())
        f.write("\n")

    f.close()

    
           
