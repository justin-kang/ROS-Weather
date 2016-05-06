'''
REFERENCES:
https://dwechsler.wordpress.com/2012/03/13/how-to-programmatically-retrieve-
 weather-data/
https://www.wunderground.com/weather/api/d/docs?d=data/hourly&MR=1
http://stackoverflow.com/questions/24074914/python-to-arduino-serial-read-write
'''

from __future__ import print_function
import json
#import rospy
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
for h in range(0,20):
    try:
        temp_dict[h] = parsed_json["hourly_forecast"][h]["temp"]["english"]
        print(temp_dict[h])
    except IndexError:
        temp_dict[h] = -99

'''
#send temperatures to arduino
port = "/dev/ttyACM0"
ard = serial.Serial(port, 9600, timeout = 5)

for i in range(0, 20):
    #ard.flush()
    ard.write(temp_dict[i] + ' ')
    time.sleep(1)
'''
