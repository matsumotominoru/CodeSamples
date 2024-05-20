package jp.co.sss.crud.db;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.text.SimpleDateFormat;

import jp.co.sss.crud.input.Input;

public class SelectDepartment {
	/**
	 * 入力した部署IDに該当する社員情報を表示する
	 * 社員IDは昇順で表示する。
	 */
	public static void selectDepartment(){
		Connection conn = null;
		PreparedStatement ps = null;
		ResultSet rs = null;

		try{
			conn = DBManager.getConnection();

			//部署IDを入力する
			int dept_Id ;
			System.out.print("部署ID(1:営業部、2:経理部、3:総務部)を入力してください:");
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

			//内部結合で表示する。部署IDで貼り合わせる。
			String sql = "select e.emp_id , e.emp_name , e.gender , e.birthday , d.dept_name from employee e inner join department d on e.DEPT_ID = d.DEPT_ID where e.dept_id = ? order by e.emp_id";

			ps = conn.prepareStatement(sql);
			ps.setInt(1, dept_Id);

			rs = ps.executeQuery();

			int emp_Id ;
			String emp_Name ;
			int emp_Gender_Num ;
			String emp_Gender = null ;
			String emp_Birthday ;
			String dept_Name ;

			//日付の出力形式を変えるためにこのクラスのメソッドformatを後で用いる。
			SimpleDateFormat simple = new SimpleDateFormat("yyyy/MM/dd");

			System.out.println("社員ID\t社員名\t性別\t生年月日\t部署名");
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
