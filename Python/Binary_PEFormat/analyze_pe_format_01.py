import struct
import sys

if __name__ == '__main__':
    if len(sys.argv) < 2:
        print("CLI args required.")
        quit()
    pe_file_name = sys.argv[1]
    with open(pe_file_name, 'rb') as pe_file:
        #_IMAGE_DOS_HEADER
        data = pe_file.read(2)
        fields = struct.unpack('<H', data[0:2])
        header_signature, = fields
        if(hex(header_signature) != "0x5a4d"):
            print("This file is not a PE file.")
            print(f'header_signature is {hex(header_signature)}')
            quit()

        data = pe_file.read(58)

        #Pointer to NT_HEADER
        data = pe_file.read(4)
        fields = struct.unpack('<I', data[0:4])
        pointer_to_nt_header, = fields
        print(hex(pointer_to_nt_header))

        #Skip MS-DOS REAL-MODE STUB PROGRUM
        buffer_size = pointer_to_nt_header - int("0x40",16)
        data = pe_file.read(buffer_size)

        data = pe_file.read(4)
        fields = struct.unpack('<I', data[0:4])
        nt_header_signature, = fields
        if(hex(nt_header_signature) != "0x4550"):
            print("This file is not a PE file.")
            print(f'nt_header_signature is {hex(nt_header_signature)}')
            quit()

        #IMAGE_FILE_HEADER(COFF HEADER)
        data = pe_file.read(20)
        fields = struct.unpack('<HHIIIHH', data[0:20])
        # TODO:time_date_stamp
        # TODO:Characteristics
        machine,number_of_sections,time_date_stamp,not_used,not_used2,size_of_optional_header,Characteristics = fields
        print(f'machine:{hex(machine)}, number_of_sections:{number_of_sections}, time_date_stamp:{hex(time_date_stamp)}, size_of_optional_header:{size_of_optional_header}, Characteristics:{hex(Characteristics)}')

        #IMAGE_OPTIONAL_HEADER standard(Standard COFF Fields)
        data = pe_file.read(28)
        fields = struct.unpack('<HBBIIIIII', data[0:28])
        magic,major_linker_ver,minor_linker_ver,size_of_code,size_of_initialized_data,size_of_uninitialized_data,address_of_entry_point,base_of_code,base_of_data = fields
        print("")
        #IMAGE_OPTIONAL_HEADER additional(Windows Specific Fields)
        # if size_of_optional_header == 224 

        #IMAGE_DATA_DIRECTORY(Data Directories) 16 arrays

        # end if size_of_optional_header
        #Section Table
        # loop number_of_sections


