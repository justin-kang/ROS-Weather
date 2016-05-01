'''
REFERENCES:
https://dwechsler.wordpress.com/2012/03/13/how-to-programmatically-retrieve-
 weather-data/
https://www.wunderground.com/weather/api/d/docs?d=data/hourly&MR=1
http://stackoverflow.com/questions/24074914/python-to-arduino-serial-read-write
'''

from __future__ import print_function
import json
import rospy
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
for h in range(0,24):
    try:
        temp_dict[h] = parsed_json["hourly_forecast"][h]["temp"]["english"]
    except IndexError:
        temp_dict[h] = -99

port = "dev/ttyACM0"
ard = serial.Serial(port, 9600, timeout = 5)

for i in range(0, 20):
    ard.flush()
    ard.write(temp_dict[i])
    time.sleep(1)

'''
#print temperatures to file "temps.txt"
file = open("temps.txt", 'w')
for i in range(0, 24):
    t = str(temp_dict[i])+'\n'
    file.write(t)

#get current time
current_time = time.localtime()
current_hour = current_time.tm_hour
month = current_time.tm_mon
day = current_time.tm_mday
year = current_time.tm_year

#formatting
counter = 1
am = True
degree = u"\N{DEGREE SIGN}"'F'

#print out temperature at each hour
for i in range(0,24):
    hour = (current_hour + counter) % 12
    if (hour == 0):
        hour = 12
    am = (current_hour + counter) / 12
    if (am % 2 == 0):
        am = True
    else:
        am = False
    if ((hour == 12) & (am == True)):
        day = day + 1
    print("At time", hour, end="")
    if am == True:
        print("am, ", end="")
    else:
        print("pm, ", end="")
    print("{m}/{d}/{y}, ".format(m=month, d=day, y=year), end="")
    t = str(temp_dict[i])+degree
    print("temperature is", t, end='\n')
    counter = counter + 1
'''
