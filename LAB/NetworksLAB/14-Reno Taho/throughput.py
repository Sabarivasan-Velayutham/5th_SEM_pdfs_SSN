#!/usr/bin/python3

f1 = open("out.tr","r")
rl = f1.readlines()

r=0
for val in rl:
	if val[0]=="r":
		# print(val)
		li = list(val.split(" "))
		if li[4]=="tcp":
			r+=int(li[5])
			r-=(int(li[5])%512)
		
f1.close()
t = ((r/10)*(8/1000))/1000
print("Throughput = ",t,"mbps")
