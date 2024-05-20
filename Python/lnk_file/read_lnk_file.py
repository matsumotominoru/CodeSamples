import struct
import sys

def read_shell_item_format(lnk_file,size_of_link_target_id):
    # ref. https://github.com/libyal/libfwsi/blob/main/documentation/Windows%20Shell%20Item%20format.asciidoc
    data = lnk_file.read(2)
    fields = struct.unpack('<H', data[0:2])
    data_size,= fields
    if(data_size == 0):
        return False
    
    data = lnk_file.read(1)
    fields = struct.unpack('<B', data[0:1])
    class_type_id, = fields
    print(f'class_type_id={hex(class_type_id)},data_size={data_size-3}')
    
    data = lnk_file.read(data_size - 3)
    print(data)
    return True

def read_extra_data_in_lnk(lnk_file):
        data = lnk_file.read(4)
        fields = struct.unpack('<I', data[0:4])
        data_size,= fields
        if(data_size == 0):
            return False
        data = lnk_file.read(4)
        fields = struct.unpack('<I', data[0:4])
        signature,= fields
        print(f'data_saze={data_size},signature={hex(signature)}')
        
        # read data block
        if (hex(signature) == 0xa0000009):
            #Windows Property Store
            read_property_store(lnk_file,data_size - 8)
        else:
            data = lnk_file.read(data_size - 8)
        return True

if __name__ == '__main__':
    if len(sys.argv) < 2:
        print("CLI args required.")
        quit()
    lnk_file_name = sys.argv[1]
    with open(lnk_file_name, 'rb') as lnk_file:
        # ref. https://github.com/libyal/liblnk/blob/main/documentation/Windows%20Shortcut%20File%20(LNK)%20format.asciidoc
        # read 2.File header
        # read magic number
        data = lnk_file.read(4)
        fields = struct.unpack('<I', data[0:4])
        header_signature, = fields
        if(hex(header_signature) != "0x4c"):
            print("not a lnk file")
            quit()
        
        #read  LNK class identifier
        data = lnk_file.read(16)
        fields = struct.unpack('<IIII', data[0:16])
        header_signature1, header_signature2,header_signature3,header_signature4  = fields
        if(hex(header_signature1) != "0x21401"):
            print("not a lnk file")
            quit()
        if(hex(header_signature2) != "0x0"):
            print("not a lnk file")
            quit()
        if(hex(header_signature3) != "0xc0"):
            print("not a lnk file")
            quit()
        if(hex(header_signature4) != "0x46000000"):
            print("not a lnk file")
            quit()
        
        #read two flags(Data and File attribute)
        data = lnk_file.read(8)
        fields = struct.unpack('<II', data[0:8])
        data_flag,file_attri_flag = fields
        data_flag_dict ={1:"HasTargetIDList",
2:"HasLinkInfo",
4:"HasName",
8:"HasRelativePath",
16:"HasWorkingDir",
32:"HasArguments",
64:"HasIconLocation",
128:"IsUnicode",
256:"ForceNoLinkInfo",
512:"HasExpString",
1024:"RunInSeparateProcess",
2048:"Unkown1",
4096:"HasDarwinID",
8192:"RunAsUser",
16384:"HasExpIcon",
32768:"NoPidlAlias",
65536:"Unkown2",
131072:"RunWithShimLayer",
262144:"ForceNoLinkTrack",
524288:"EnableTargetMetadata",
1048576:"DisableLinkPathTracking",
2097152:"DisableKnownFolderTracking",
4194304:"DisableKnownFolderAlias",
8388608:"AllowLinkToLink",
16777216:"UnaliasOnSave",
33554432:"PreferEnvironmentPath",
67108864:"KeepLocalIDListForUNCTarget"}
        mask_value = 0x01
        data_flag_list = []
        for i in range(len(data_flag_dict)):
            #bit operation
            bool_value =  (data_flag & mask_value == mask_value)
            if(bool_value):
                data_flag_list.append(data_flag_dict[mask_value])
            #left shift
            mask_value = mask_value << 1
        print(f'data_flag={hex(data_flag)}:{data_flag_list}')
        
        file_attri_dict = {1:"READONLY",
2:"HIDDEN",
4:"SYSTEM",
8:"Unknown1",
16:"DIRECTORY",
32:"ARCHIVE",
64:"DEVICE",
128:"NORMAL",
256:"TEMPORARY",
512:"SPARSEFILE",
1024:"REPARSEPOINT",
2048:"COMPRESSED",
4096:"OFFLINE",
8192:"NOTCONTENTINDEXED",
16384:"ENCRYPTED",
32768:"Unknown2",
65536:"VIRTUAL"}
        mask_value = 0x01
        file_attri_list = []
        for i in range(len(file_attri_dict)):
            #bit operation
            bool_value =  (file_attri_flag & mask_value == mask_value)
            if(bool_value):
                file_attri_list.append(file_attri_dict[mask_value])
            #left shift
            mask_value = mask_value << 1
        print(f'file_attri_flag={hex(file_attri_flag)}:{file_attri_list}')

        # get date time(FILETIME)
        data = lnk_file.read(8)
        fields = struct.unpack('<II', data[0:8])
        creation_date,creation_time = fields
        
        data = lnk_file.read(8)
        fields = struct.unpack('<II', data[0:8])
        last_access_date,last_access_time = fields
        
        data = lnk_file.read(8)
        fields = struct.unpack('<II', data[0:8])
        last_modification_date,last_modification_time = fields

        data = lnk_file.read(24)
        fields = struct.unpack('<IIIHHII', data[0:24])
        file_size,icon_value,show_window_value,hot_key,unknown1,unknown2,unknown3 = fields
        print(f'file_size={file_size},icon_value={icon_value},show_window_value={show_window_value},hot_key={hot_key},unknown1={unknown1},unknown2={unknown2},unknown3={unknown3}')
        
        # 3.Link target identifier
        if("HasTargetIDList" in data_flag_list):
            data = lnk_file.read(2)
            fields = struct.unpack('<H', data[0:2])
            size_of_link_target_id, = fields
            has_shell_item = True
            while(has_shell_item):
                has_shell_item = read_shell_item_format(lnk_file,size_of_link_target_id)
        
        # 4.Location information
        if("HasLinkInfo" in data_flag_list):
            data = lnk_file.read(28)
            fields = struct.unpack('<IIIIIII', data[0:28])
            size_of_location_info,location_info_header_size,location_flag,offset_to_volume_info, offset_to_local_path,offset_to_network_share_info,offset_to_common_path = fields
            print(f'size_of_location_info={size_of_location_info},location_info_header_size={location_info_header_size},location_flag={location_flag}\noffset_to_volume_info={offset_to_volume_info},offset_to_local_path={offset_to_local_path},offset_to_network_share_info={offset_to_network_share_info},offset_to_common_path={offset_to_common_path}')
            if(location_info_header_size > 28):
                print('if(location_info_header_size > 28)')
                quit()
            #volume info
            data = lnk_file.read(16)
            fields = struct.unpack('<IIII', data[0:16])
            volume_info_size,drive_type,drive_number,offset_to_the_volume_label = fields
            print(f'volume_info_size={volume_info_size},drive_type={drive_type},drive_number={drive_number},offset_to_the_volume_label={offset_to_the_volume_label}')
            if(offset_to_the_volume_label > 16):
                print(' if(offset_to_the_volume_label > 16)')
                quit()
            data = lnk_file.read(volume_info_size - 16)
            print(f'volume label={data}')
            
            if (offset_to_network_share_info > 0):
                print("offset_to_network_share_info > 0,local path string offset is wrong.")
                quit()
            #  local path string
            data = lnk_file.read(offset_to_common_path - offset_to_local_path)
            print(f'local path string={data}')
            
            # common_path
            data = lnk_file.read(size_of_location_info - offset_to_common_path)
            print(f'common_path={data}')
            
            # 5.Data strings
            # 5.1.description data string
        if("HasName" in data_flag_list):
            data = lnk_file.read(2)
            fields = struct.unpack('<H', data[0:2])
            data_length, = fields
            if("IsUnicode" in data_flag_list):
                data = lnk_file.read(2*data_length)
                print(f'description data string={data.decode("utf_16")}')
            else:
                data = lnk_file.read(data_length)
                print(f'description data string={data}')
            
            # 5.2.relative path data string
        if("HasRelativePath" in data_flag_list):
            data = lnk_file.read(2)
            fields = struct.unpack('<H', data[0:2])
            data_length, = fields
            if("IsUnicode" in data_flag_list):
                data = lnk_file.read(2*data_length)
                print(f'relative path string={data.decode("utf_16")}')
            else:
                data = lnk_file.read(data_length)
                print(f'relative path string={data}')
            
            # 5.3.working directory data string
        if("HasWorkingDir" in data_flag_list):
            data = lnk_file.read(2)
            fields = struct.unpack('<H', data[0:2])
            data_length, = fields
            if("IsUnicode" in data_flag_list):
                data = lnk_file.read(2*data_length)
                print(f'working directory string={data.decode("utf_16")}')
            else:
                data = lnk_file.read(data_length)
                print(f'working directory string={data}')
            
            # 5.4.command line arguments
        if("HasArguments" in data_flag_list):
            data = lnk_file.read(2)
            fields = struct.unpack('<H', data[0:2])
            data_length, = fields
            if("IsUnicode" in data_flag_list):
                data = lnk_file.read(2*data_length)
                print(f'command line arguments={data.decode("utf_16")}')
            else:
                data = lnk_file.read(data_length)
                print(f'command line arguments={data}')
            
            # 5.5.icon location
        if("HasIconLocation" in data_flag_list):
            data = lnk_file.read(2)
            fields = struct.unpack('<H', data[0:2])
            data_length, = fields
            if("IsUnicode" in data_flag_list):
                data = lnk_file.read(2*data_length)
                print(f'icon location={data.decode("utf_16")}')
            else:
                data = lnk_file.read(data_length)
                print(f'icon location={data}')
        #6.Extra data
        has_extra_data = True
        while(has_extra_data):
            has_extra_data = read_extra_data_in_lnk(lnk_file)
        
        data = lnk_file.read(2)
        if(len(data) == 0):
            print('reached EOF')
        else:
            print('has remained data')