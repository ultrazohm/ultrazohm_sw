# This script opens the .xdc constraint files and extract the relevant information from them
# like package pin, pulldown, iostandard
# Afterwards, it loads information extracted from Trenz pinout excel sheet to generate new files.
#  

import csv
from os import listdir, getcwd
from os.path import isfile, join

class XdcInfo:
    def __init__(self, port):
        self.package_pin = []
        self.pulldown = []
        self.iostandard = []
        self.diff_term = []
        self.diff_term_adv = []
        self.port = port
    
    def write(self):
        output = []
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

        
# extract port info, removing last ] and all {}
def extract_port(sp):
    port = sp[:-1].replace('{','')
    return port.replace('}','')

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
                port = extract_port(sl[4])
                if sl[1] == "PACKAGE_PIN":            
                    xdc_dict[port] = XdcInfo(port)
                    xdc_dict[port].package_pin = sl[2]
                elif sl[1] == "PULLDOWN":
                    xdc_dict[port].pulldown = sl[2]  
                elif sl[1] == "DIFF_TERM":
                    xdc_dict[port].diff__term = sl[2]
                elif sl[1] == "DIFF_TERM_ADV":
                    xdc_dict[port].diff_term_adv = sl[2]
                elif sl[1] == "IOSTANDARD":
                    xdc_dict[port].iostandard = sl[2]
    return xdc_dict
                


# get all xdc files in folder
xdc_files = [f for f in listdir(getcwd()) if isfile(join(getcwd(), f)) and f.endswith((".xdc",".XDC"))]

# process one xdc at a time, extracting the relevant info and re-writing to a new .xdc
for xdc_input in xdc_files:
    f = open("new/"+xdc_input,'w')

    print(xdc_input)
    xdc_dict = extract_info_from_xdc(xdc_input)

    for port in xdc_dict.items():
        f.writelines(port[1].write())
        f.write("\n")

    f.close()

    
           
