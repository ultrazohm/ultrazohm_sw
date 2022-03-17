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
        self.diff_inverted = False
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
        if self.diff_inverted: 
            output.append("# WARNING: Differential signals are inverted in respect to TE0808 9EG device. \n") 
            output.append("# Take care to invert the signal inside the PL! \n") 
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

def print_header(origin, target):
    output = ["# This file was auto-generated using the python script process_xdc.py\n"]
    output.append("# The script has as input the original constraints. Pinout info is extracted from\n")
    output.append("# Trenz pinout sheet (obtained from https://shop.trenz-electronic.de/Download/?path=Trenz_Electronic/Pinout) \n")
    output.append("# into csv files with the C-PIN, C-NAME, FPGA Pin Name, and Module Net Name columns.\n")
    output.append("# Obs.: Column order is not important, but names need to be strictly followed.\n#\n")
    output.append("# Constraints ported from {} to {}.\n".format(origin, target))
    output.append("#\n")
    output.append("# Script author: Tomas P. Correa\n")
    output.append("# Date: check GIT repo\n\n\n")
    return output


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
target_filename = "TE0803_REV01.csv"

dict_origin = read_pinout(origin_filename)
dict_target = read_pinout(target_filename)

# process one xdc at a time, extracting the relevant info and re-writing to a new .xdc
for xdc_input in xdc_files:
    with open("new/"+xdc_input,'w') as f: 
  
        print(xdc_input)
        xdc_dict = extract_info_from_xdc(xdc_input)

        f.writelines(print_header(origin_filename, target_filename))

        for port in xdc_dict.items():
            p = port[1]
            # find dict on the origin list that has the same package pin
            origin_info = [item for item in dict_origin if item["FPGA Pin Name"] == p.package_pin][0]
            p.connector_name = origin_info["C-Name"]
            p.connector_number = origin_info["C-Pin"]       
            # find dict on the target list that is connected to the same B2B connector pin
            target_info = [item for item in dict_target if item["C-Name"] == origin_info["C-Name"] and item["C-Pin"] == origin_info["C-Pin"]][0]
            # replace package_pin with the information of the target board
            p.package_pin = target_info["FPGA Pin Name"]
            p.module_net_name = target_info["Module Net Name"]
            # invert _P and _N pins if there is a mismatch (even = _P and odd = _N)
            if p.iostandard == "LVDS":
                if "[" in p.port and "]" in p.port:    
                    number = int(p.port[p.port.find("[")+1:p.port.find("]")])
                    if number % 2 == 0 and p.module_net_name.endswith("_N"):
                        # number is even, but ends with _N 
                        # uses aux, because only number within [] must be changed
                        aux = p.port.split("[")
                        aux[1] = aux[1].replace(str(number),str(number+1))
                        p.port = "[".join(aux)
                        p.diff_inverted = True
                    if number % 2 != 0 and p.module_net_name.endswith("_P"):
                        # number is odd, but ends with _P -> switch 
                        # uses aux, because only number within [] must be changed
                        aux = p.port.split("[")
                        aux[1] = aux[1].replace(str(number),str(number-1))
                        p.port = "[".join(aux)
                        p.diff_inverted = True
            f.writelines(p.write())
            f.write("\n")


    
           
