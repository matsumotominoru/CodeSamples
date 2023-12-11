import struct
import sys

#int_ms_dos_date is 2-Byte or lower integer
def get_date_from_ms_dos_date(int_ms_dos_date):
    #Convert to 16 bit fixed length binary string
    str_bin_ms_dos_date = format(int_ms_dos_date, '0>16b')
    year = int(str_bin_ms_dos_date[0:7],2) + 1980
    month = int(str_bin_ms_dos_date[7:11],2)
    day = int(str_bin_ms_dos_date[11:16],2)
    return(f"{year}/{month}/{day}")

#int_ms_dos_time is 2-Byte or lower integer
def get_time_from_ms_dos_time(int_ms_dos_time):
    #Convert to 16 bit fixed length binary string
    str_bin_ms_dos_time = format(int_ms_dos_time, '0>16b')
    hour = int(str_bin_ms_dos_time[0:5],2)
    minute = int(str_bin_ms_dos_time[5:11],2)
    second = int(str_bin_ms_dos_time[11:16],2) * 2
    return("%(num1)02d:%(num2)02d.%(num3)02d" % {"num1":hour,"num2" : minute,"num3":second})

# read zip header and zipped data
def read_zip_header_and_data(file_stream):
    print("ZIP_HEADER")
    data = file_stream.read(10)
    fields = struct.unpack('<HHHHH', data[0:10])
    version,bit_flag,compression_method,int_last_modification_time,int_last_modification_date = fields

    last_modification_date = get_date_from_ms_dos_date(int_last_modification_date)
    last_modification_time = get_time_from_ms_dos_time(int_last_modification_time)

    compression_method_str = "unknown"
    if(compression_method == 0x08):
        compression_method_str = "deflate"

    print(f'version = {version}, bit flag = {bit_flag}, compression method is {compression_method_str}, last modification date-time is {last_modification_date} {last_modification_time}')

    data = file_stream.read(16)
    fields = struct.unpack('<IIIHH', data[0:16])
    crc32, comp_size, uncomp_size, filenamesize, extra_size = fields
    data = file_stream.read(filenamesize)
    filename = data[0:filenamesize]
    data = file_stream.read(extra_size)

    str_filename = ""
    if(bit_flag == 0):
        str_filename = filename.decode("cp932")
    elif(bit_flag == 2048):
        str_filename = filename.decode("utf_8")

    print(f'filename={str_filename},crc32={hex(crc32)},comp_size={comp_size}, uncomp_size={uncomp_size}, filenamesize={filenamesize}, extra_size={extra_size}\n')

    # skip to the next header
    data = file_stream.read(comp_size)

def read_central_directory(file_stream):
    print("CENTRAL_DIRECTORY")
    data = file_stream.read(12)
    fields = struct.unpack('<HHHHHH', data[0:12])
    version1,version2,bit_flag,compression_method,int_last_modification_time,int_last_modification_date = fields

    last_modification_date = get_date_from_ms_dos_date(int_last_modification_date)
    last_modification_time = get_time_from_ms_dos_time(int_last_modification_time)

    compression_method_str = "unknown"
    if(compression_method == 0x08):
        compression_method_str = "deflate"

    print(f'version1 = {version1},version2 = {version2}, bit flag = {bit_flag}, compression method is {compression_method_str}, last modification date-time is {last_modification_date} {last_modification_time}')

    data = file_stream.read(30)
    fields = struct.unpack('<IIIHHHHHII', data[0:30])
    crc32, comp_size, uncomp_size, filenamesize, extra_size,comment_length,start_position,internal_attri,external_attri,relative_position = fields

    data = file_stream.read(filenamesize)
    filename = data[0:filenamesize]

    data = file_stream.read(extra_size)

    data = file_stream.read(comment_length)
    comment = data[0:comment_length]

    str_filename = ""
    if(bit_flag == 0):
        str_filename = filename.decode("cp932")
        str_comment = comment.decode("cp932")
    elif(bit_flag == 2048):
        str_filename = filename.decode("utf_8")
        str_comment = comment.decode("utf_8")

    print(f'filename={str_filename},crc32={hex(crc32)},comp_size={comp_size}, uncomp_size={uncomp_size}, filenamesize={filenamesize}, extra_size={extra_size},comment={str_comment},{start_position},{internal_attri},{external_attri},{relative_position}\n')

def read_central_directory_record(file_stream):
    print("CENTRAL_DIRECTORY_RECORD")
    data = file_stream.read(18)
    fields = struct.unpack('<HHHHIIH', data[0:18])
    num_of_disk1,num_of_disk2,sum_of_entries,total_num_of_entries,size,offset,comment_length = fields
    print(f'num_of_disk1={num_of_disk1},num_of_disk2={num_of_disk2},sum_of_entries={sum_of_entries},total_num_of_entries={total_num_of_entries},size={size},offset={offset}')

    data = file_stream.read(comment_length)
    comment = data[0:comment_length]
    str_comment = comment.decode("cp932")
    print(f'comment:{str_comment}')

if __name__ == '__main__':
    if len(sys.argv) < 2:
        print("CLI args required.")
        quit()
    zip_file_name = sys.argv[1]
    with open(zip_file_name, 'rb') as zip_file:
        # read data fields repeatedly until EOF.
        while(True):
            # read magic number
            data = zip_file.read(4)
            fields = struct.unpack('<I', data[0:4])
            header_signature, = fields

            if(hex(header_signature) == "0x4034b50"):
                read_zip_header_and_data(zip_file)
            elif(hex(header_signature) == "0x8074b50"):
                print("extended header")
            elif(hex(header_signature) == "0x2014b50"):
                read_central_directory(zip_file)
            elif(hex(header_signature) == "0x6054b50"):
                read_central_directory_record(zip_file)
                quit()
            else:
                print(f'header_signature is {hex(header_signature)}')
                quit()
