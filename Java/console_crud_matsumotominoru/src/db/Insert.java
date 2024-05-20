package jp.co.sss.crud.db;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import jp.co.sss.crud.date.Valid_Calendar;
import jp.co.sss.crud.input.Input;
public class Insert {
	/**
	 * 入力した社員情報をデータベース上に作成する。ただし社員IDは自動採番とする。
	 */
	public static void insert(){
		Connection conn = null;
		PreparedStatement ps = null;

		try{
			conn = DBManager.getConnection();

			String sql = "insert into employee values (seq_emp.NEXTVAL , ? , ? , ? , ?)";

			ps = conn.prepareStatement(sql);
			//社員名の登録
			int name_Length;
			String emp_Name;
			System.out.print("社員名:");
			do{
				emp_Name = Input.input();
				name_Length = emp_Name.length();
				if(name_Length >= 31 || name_Length == 0){
					System.out.print("1文字以上30文字以下の文字列を入力してください:");
				}
			}while(name_Length >= 31 || name_Length == 0);//入力値が31文字以上または0文字のとき入力をやり直す。

			//性別の登録
			int gender_Num;
			System.out.print("性別(1: 男性,2: 女性):");
			do{
				try{
				gender_Num = Integer.parseInt(Input.input());
				}
				//整数以外の入力はすべて0にする。
				catch (NumberFormatException e){
					gender_Num = 0;
				}
				if(gender_Num <= 0 || gender_Num >= 3){
					System.out.print("1以上2以下の整数を入力してください:");
				}
			}while(gender_Num <= 0 || gender_Num >= 3);//入力値が1,2以外のときは入力をやり直す。

			//生年月日の入力
			int year;
			int month;
			int day;
			boolean pattern_Match = false;
			boolean is_Date = false;
			String birthday;
			Pattern pattern = Pattern.compile("[1-2][0-9][0-9][0-9]/[0-1]?[0-9]/[0-3]?[0-9]");
			Matcher matcher;

			System.out.print("生年月日(西暦年/月/日):");
			do{
				birthday = Input.input();
				matcher = pattern.matcher(birthday);
				pattern_Match = matcher.matches();
				if(pattern_Match){
					System.out.println("正しい正規表現");
					String[] calendars = birthday.split("/", 3);
					year = Integer.parseInt(calendars[0]);
					month = Integer.parseInt(calendars[1]);
					day = Integer.parseInt(calendars[2]);

						System.out.println(year +":"+ month +":"+ day);

						is_Date = Valid_Calendar.valid_Calendar(year, month, day);
				}
				else {
					System.out.println("異なる正規表現");
				}

				if(!is_Date){
					System.out.print("正しい形式(西暦年/月/日)で日付を入力してください:");
				}
			}while(!is_Date);

			//部署IDの入力
			int dept_Id ;
			System.out.print("部署ID(1:営業部、2:経理部、3:総務部):");
			do{
				try{
					dept_Id = Integer.parseInt(Input.input());
				}
				//整数以外の入力はすべて0にする。
				catch (NumberFormatException e){
					dept_Id = 0;
				}
				if(dept_Id <= 0 || dept_Id >= 4){
					System.out.print("1以上3以下の整数を入力してください:");
				}
			} while(dept_Id <= 0 || dept_Id >= 4);//部署IDが0以下または4以上のとき入力し直す。

			ps.setString(1, emp_Name);
			ps.setInt(2 , gender_Num);
			ps.setString(3, birthday);
			ps.setInt(4, dept_Id);

			int cnt = ps.executeUpdate();
			//1件以上実行されたとき削除完了メッセージを出力、実行されなかったらなしと出力
			if(cnt >= 1){
				System.out.println("社員情報を登録しました。");
			}
			else{
				System.out.println("なし");
			}
		}
		catch (Exception e){
			e.printStackTrace();
		}
		finally{
			DBManager.close(conn);
			DBManager.close(ps);
		}
	}

}
