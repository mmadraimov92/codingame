import sys
import math

def distance(lon1,lat1,lon2,lat2):
    x = (math.radians(lon2)-math.radians(lon1)) * math.cos((math.radians(lat1)+math.radians(lat2))/2)
    y = math.radians(lat2)-math.radians(lat1)
    return math.sqrt(x**2+y**2)*6371
    
lon = float(input().replace(',','.'))
lat = float(input().replace(',','.'))
n = int(input())
d = sys.maxsize
for i in range(n):
    ID, name, address,tel_num,lon_deg,lat_deg = input().split(';')
    lon_deg = float(lon_deg.replace(',','.'))
    lat_deg = float(lat_deg.replace(',','.'))
    if d > distance(lon,lat,lon_deg,lat_deg):
        closest = name
        d = distance(lon,lat,lon_deg,lat_deg)

print(closest)

