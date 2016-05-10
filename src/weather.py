from __future__ import print_function
import json
import serial
import time
import urllib2

#know which URL to look at
u = "http://api.wunderground.com/api/244c59b05b80bc66/hourly/q/TX/Austin.json"
f = urllib2.urlopen(u)

#get/parse the JSON
json_string = f.read()
f.close()
parsed_json = json.loads(json_string)

#store temperatures in dictionary
temp_dict = {}
for h in range(0,12):
    try:
        temp_dict[h] = parsed_json["hourly_forecast"][h]["temp"]["english"]
        #debugging purposes
        #print(temp_dict[h])
    except IndexError:
        #store unlikely temp in case of errors
        temp_dict[h] = -99

#send temperatures to arduino
port = "/dev/ttyUSB1"
ard = serial.Serial(port, 115200)

for i in range(0, 12):
    ard.write(temp_dict[i] + ' ')
    time.sleep(1)
