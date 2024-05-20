def compare_csv_data(_oracle_csv_file_name,_postgre_csv_file_name,_number_of_rows_oracle):
    oracle_csv_counter = 0
    has_diff_global = False
    number_of_unmatched_rows = 0
    with open(_oracle_csv_file_name, newline='', encoding="cp932") as oracle_csv_file:
        oracle_csv_reader = csv.reader(oracle_csv_file, delimiter=',', quotechar='"')
        with open(_postgre_csv_file_name, newline='', encoding="utf-8") as postgre_csv_file:
            postgre_csv_reader = csv.reader(postgre_csv_file, delimiter=',', quotechar='"')
            # 一行目はヘッダー行のため比較を行わずスキップする。
            next(oracle_csv_reader)
            next(postgre_csv_reader)
            
            for oracle_row in oracle_csv_reader:
                index_of_postgre_column = 0
                has_diff_in_corrent_row = False
                postgre_row = next(postgre_csv_reader)
                for oracle_value in oracle_row:
                    # 項目が一致するか確認し、不一致ならデータ差分がある旨出力する。
                    if(not AreItemsEqualEachOther(oracle_value,postgre_row[index_of_postgre_column])):
                        print(f'データ差分：{oracle_csv_counter + 1}レコード{index_of_postgre_column+1}列に差分があります。現行DBデータの値:「{oracle_value}」、リニューアルDBデータの値:「{postgre_row[index_of_postgre_column]}」')
                        has_diff_global = True
                        has_diff_in_corrent_row = True
                    
                    index_of_postgre_column += 1
                oracle_csv_counter += 1
                if has_diff_in_corrent_row:
                    number_of_unmatched_rows += 1
                # 1万件単位で進捗度を表示する。
                if oracle_csv_counter % 10000 == 0:
                    print(f'{oracle_csv_counter}件 / {_number_of_rows_oracle}件 完了。')
            if oracle_csv_counter % 10000 != 0:
                print(f'{oracle_csv_counter}件 / {_number_of_rows_oracle}件 完了。')
