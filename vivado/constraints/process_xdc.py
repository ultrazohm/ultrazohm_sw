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
                
def read_pinout(filename):
    with open(filename) as f:
        obj = csv.DictReader(f, delimiter=";")
        output = []
        for item in obj:         
            if item["FPGA Pin Name"] != "---" and item["FPGA Pin Name"] != "--" :
                output.append(item)
    return output
    

# get all xdc files in folder
xdc_files = [f for f in listdir(getcwd()) if isfile(join(getcwd(), f)) and f.endswith((".xdc",".XDC"))]

# Package pins and B2B connector matching extracted from Trenz pinout sheet
# https://shop.trenz-electronic.de/Download/?path=Trenz_Electronic/Pinout
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
        # find dict on the target list that is connected to the same B2B connector pin
        target_info = [item for item in dict_target if item["C-Name"] == origin_info["C-Name"] and item["C-Pin"] == origin_info["C-Pin"]][0]
        # replace package_pin with the information of the target board
        port[1].package_pin = target_info["FPGA Pin Name"]
      
        f.writelines(port[1].write())
        f.write("\n")

    f.close()

    
           
