# dictの値にlistのlistを入れる。
json_string_4 = '''
{
    "DCZAFAX01":{
        "has_new_column" : true,
        "new_column" : ["TOKUTEI_JOKEN_KBN","JUYD","LINK_STRING","LINK_URL"],
        "column_index" : [5,11,13,14],
        "initial_value" : [" ","0"," "," "],
        "column_name_modified" : true,
        "modified_column" : ["HSNMT_NO","KNM_NO"],
        "modified_column_index" : [2,3]
    }
}
'''
json_dict_4 = json.loads(json_string_4)
if(json_dict_4["DCZAFAX01"]["has_new_column"]):
    number_of_new_column = len(json_dict_4["DCZAFAX01"]["new_column"])
    str = '"'
    for i in range(number_of_new_column):
        str += json_dict_4["DCZAFAX01"]["initial_value"][i] + '","'
        print(json_dict_4["DCZAFAX01"]["column_index"][i]+5)
    print(str[0:-2])

old_column_list_str = "OSRS_NO,HSNMT_NO,KNM_NO,OSRS_KBN,KEIYK_TANI_CD,KSAI_STAT_D,KSAI_STAT_TIME,KSAI_END_D,KSAI_END_TIME,OSRS_HNBN,SNKI_FLG,SKJO_FLG,TORK_D,TORK_TIME,KOSIN_D,KOSIN_TIME,KOSIN_PGM_ID,KOSIN_USER_ID,REC_SAKSE_YMD,REC_KOSIN_YMD,KOSIN_KBN,TIME_STAMP"
old_column_list = old_column_list_str.split(",")

number_of_new_column = len(json_dict_4["DCZAFAX01"]["new_column"])
for i in range(number_of_new_column):
    old_column_list.insert(json_dict_4["DCZAFAX01"]["column_index"][i]-1,json_dict_4["DCZAFAX01"]["new_column"][i])

if(json_dict_4["DCZAFAX01"]["column_name_modified"]):
                    for i in range(len(json_dict_4["DCZAFAX01"]["modified_column"])):
                        old_column_list[json_dict_4["DCZAFAX01"]["modified_column_index"][i]-1] = json_dict_4["DCZAFAX01"]["modified_column"][i]

for i in range(0):
    print("ok")

new_column_str = '"'
for item in old_column_list:
    new_column_str += item + ','
print(new_column_str[0:-1])
