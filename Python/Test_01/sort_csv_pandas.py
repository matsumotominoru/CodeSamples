import pandas
import csv
# sort a cp932 csv file that has no header
# load all csv data to memory, so a huge csv file may not be sorted.
if __name__ == "__main__":
    _oracle_csv_file_name = "DCTCSTK01_Oracle_export_no_header.csv"
    #add arg header=None
    df_oracle = pandas.read_csv(_oracle_csv_file_name,encoding = "cp932", dtype='object', header=None)
    #specify column index instead of column name
    df_sort_oracle = df_oracle.sort_values([0,1])
    #add arg header=None
    df_sort_oracle.to_csv(_oracle_csv_file_name, index = False , quoting=csv.QUOTE_ALL, encoding = "cp932", header=None)
