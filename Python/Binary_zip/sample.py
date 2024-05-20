# get decimal encoding
encode_of_A = ord('A')
print(encode_of_A)

# convert decimal to hex
hex_encode_of_A = hex(encode_of_A)
print(hex_encode_of_A)
if(hex_encode_of_A == '0x41'):
    print("ok")

# convert hex to char
char_1 = chr(0x46)
print(char_1)

byte_array_1 = bytearray("abcdあ","utf_8")
print(byte_array_1)
print(byte_array_1.decode())

byte_array_1 = bytearray("abcdあ","shift_jis")
print(byte_array_1)
print(byte_array_1.decode("shift_jis"))

byte_1 = b'Vbox\x83\x81\x83\x82.txt'
str = byte_1.decode("shift_jis")
print(str)
# convert string to hex encoding
# hex_str = "abc".encode("hex")

