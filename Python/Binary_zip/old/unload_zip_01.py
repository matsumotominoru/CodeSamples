import struct

number_of_files = 20
with open('eLTax_xmlkouzoushiyou.zip', 'rb') as f:
    data = f.read()

start = 0
for i in range(number_of_files):                      
    start += 14
    # Pack codes "H" and "I" represent two and four byte unsigned numbers respectively. 
    # The "<" indicates that they are standard size and in little-endian byte order
    fields = struct.unpack('<IIIHH', data[start:start+16])
    crc32, comp_size, uncomp_size, filenamesize, extra_size = fields

    start += 16
    filename = data[start:start+filenamesize]
    start += filenamesize
    extra = data[start:start+extra_size]
    str_filename = filename.decode("shift_jis")
    print(f'filename={str_filename},crc32={hex(crc32)},comp_size={comp_size}, uncomp_size={uncomp_size}')
    # skip to the next header
    start += extra_size + comp_size