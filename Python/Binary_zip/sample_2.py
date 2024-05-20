str_bin = f'{0x2E90:0>16b}'
print(str_bin)


hex_1  = int("0xA883",16)
str_bin = format(hex_1, '0>16b')
print(str_bin)

hour = int(str_bin[0:5],2)
minute = int(str_bin[5:11],2)
second = int(str_bin[11:16],2) * 2

print("%(num1)02d:%(num2)02d.%(num3)02d" % {"num1":hour,"num2" : minute,"num3":second})
