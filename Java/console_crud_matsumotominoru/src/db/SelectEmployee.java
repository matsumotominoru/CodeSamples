package jp.co.sss.crud.db;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.text.SimpleDateFormat;

import jp.co.sss.crud.input.Input;

public class SelectEmployee {
	/**
	 * 入力した文字列を社員名に含む社員情報を全て表示する。
	 * 社員IDは昇順で表示。
	 */
	public static void selectEmployee(){
		Connection conn = null;
		PreparedStatement ps = null;
		ResultSet rs = null;

		try{
			conn = DBManager.getConnection();

			//社員名を入力する
			String emp_Name_sub;
			int name_Length;
			System.out.print("社員名を入力してください:");
			do{
				emp_Name_sub = Input.input();
				name_Length = emp_Name_sub.length();
				if(name_Length >= 31 || name_Length == 0){
					System.out.print("1文字以上30文字以下の文字列を入力してください:");
				}
			}while(name_Length >= 31 || name_Length == 0);//入力値が31文字以上または0文字のとき入力をやり直す。

			emp_Name_sub = "%" + emp_Name_sub + "%";

			//内部結合で表示する。部署IDで貼り合わせる。
			String sql = "select e.emp_id , e.emp_name , e.gender , e.birthday , d.dept_name from employee e inner join department d on e.DEPT_ID = d.DEPT_ID where e.emp_name like ? order by e.emp_id";

			ps = conn.prepareStatement(sql);
			ps.setString(1, emp_Name_sub);

			rs = ps.executeQuery();

			int emp_Id ;
			String emp_Name ;
			int emp_Gender_Num ;
			String emp_Gender = null ;
			String emp_Birthday ;
			String dept_Name ;

			//日付の出力形式を変えるためにこのクラスのメソッドformatを後で用いる。
			SimpleDateFormat simple = new SimpleDateFormat("yyyy/MM/dd");

			if(rs.next()){
				System.out.println("社員ID\t社員名\t性別\t生年月日\t部署名");
				//引数の番号は列を左から数えた番号。その列にあるデータを取って左辺の変数に入れる。
				emp_Id = rs.getInt(1);
				emp_Name = rs.getString(2);
				emp_Gender_Num = rs.getInt(3);
				//1のとき男性、2のとき女性とする。
				if(emp_Gender_Num == 1){
					emp_Gender = "男性";
				}
				else if(emp_Gender_Num == 2){
					emp_Gender = "女性";
				}
				//DBから日付をDate形式でとった後、-を/に変えるため、formatメソッドを用いる
				emp_Birthday = simple.format(rs.getDate(4));
				dept_Name = rs.getString(5);

				System.out.println(emp_Id + "\t" + emp_Name + "\t" + emp_Gender + "\t" + emp_Birthday + "\t" + dept_Name);
			}
			else {
				System.out.println("該当する社員は存在しません");
			}

			while(rs.next()){
				//引数の番号は列を左から数えた番号。その列にあるデータを取って左辺の変数に入れる。
				emp_Id = rs.getInt(1);
				emp_Name = rs.getString(2);
				emp_Gender_Num = rs.getInt(3);
				//1のとき男性、2のとき女性とする。
				if(emp_Gender_Num == 1){
					emp_Gender = "男性";
				}
				else if(emp_Gender_Num == 2){
					emp_Gender = "女性";
				}
				//DBから日付をDate形式でとった後、-を/に変えるため、formatメソッドを用いる
				emp_Birthday = simple.format(rs.getDate(4));
				dept_Name = rs.getString(5);

				System.out.println(emp_Id + "\t" + emp_Name + "\t" + emp_Gender + "\t" + emp_Birthday + "\t" + dept_Name);
			}
		}
		catch(Exception e){
			e.printStackTrace();
		}
		finally{
			DBManager.close(conn);
			DBManager.close(ps);
			DBManager.close(rs);
		}
	}

}
