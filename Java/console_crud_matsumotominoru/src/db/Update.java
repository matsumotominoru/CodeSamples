package jp.co.sss.crud.db;

import java.sql.Connection;
import java.sql.PreparedStatement;

import jp.co.sss.crud.input.Input;

public class Update {
	/**
	 * 入力した社員IDを持つ社員データを更新する。
	 */
	public static void update(){
		Connection conn = null;
		PreparedStatement ps = null;

		try{
			conn = DBManager.getConnection();

			String sql = "update employee set emp_name = ? , gender = ? , birthday = ? , dept_id = ? where emp_id = ?";

			ps = conn.prepareStatement(sql);

			System.out.print("更新する社員の社員IDを入力してください:");
			int emp_Id = Integer.parseInt(Input.input());
			System.out.print("社員名:");
			String emp_Name = Input.input();
			System.out.print("性別(1: 男性,2: 女性):");
			int gender_Num = Integer.parseInt(Input.input());
			System.out.print("生年月日(西暦年/月/日):");
			String birthday = Input.input();

			int dept_Id ;
			do{
				System.out.print("部署ID(1: 営業部、2:経理部、3:総務部):");
				dept_Id = Integer.parseInt(Input.input());
				if(dept_Id <= 0 || dept_Id >= 4){
					System.out.print("1以上3以下の整数を入力してください:");
				}
			} while(dept_Id <= 0 || dept_Id >= 4);//部署IDが0以下または4以上のとき入力し直す。

			ps.setString(1, emp_Name);
			ps.setInt(2, gender_Num);
			ps.setString(3 , birthday);
			ps.setInt(4, dept_Id);
			ps.setInt(5, emp_Id);

			int cnt = ps.executeUpdate();
			//1件以上実行されたとき削除完了メッセージを出力、実行されなかったらなしと出力
			if(cnt >= 1){
				System.out.println("社員情報を更新しました。");
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

	/**
	 * 入力した社員IDを持つ社員データを更新する。値が入力された列のみ更新する。
	 * 未入力の列は更新されない。
	 *
	 */
	public static void update1(){
		Connection conn = null;
		PreparedStatement ps = null;

		try{
			conn = DBManager.getConnection();

			System.out.print("更新する社員の社員IDを入力してください:");
			String emp_Id = Input.input();
			System.out.print("社員名:");
			String emp_Name = Input.input();
			System.out.print("性別(1: 男性,2: 女性):");
			String gender_Num = Input.input();
			System.out.print("生年月日(西暦年/月/日):");
			String birthday = Input.input();
			System.out.print("部署ID(1: 営業部、2:経理部、3:総務部):");
			String dept_Id = Input.input();

			if(emp_Name.equals("")){

			}
			else {
				String sql1 = "update employee set emp_name = ? where emp_id = ?";
				ps = conn.prepareStatement(sql1);
				ps.setString(1, emp_Name);
				ps.setString(2, emp_Id);
				ps.executeUpdate();
//				DBManager.close(ps);
			}
			if(gender_Num.equals("")){

			}
			else {
				String sql2 = "update employee set gender = ? where emp_id = ?";
				ps = conn.prepareStatement(sql2);
				ps.setString(1, gender_Num);
				ps.setString(2, emp_Id);
				ps.executeUpdate();
			}

			if(birthday.equals("")){

			}
			else {
				String sql3 = "update employee set birthday = ? where emp_id = ?";
				ps = conn.prepareStatement(sql3);
				ps.setString(1, birthday);
				ps.setString(2, emp_Id);
				ps.executeUpdate();
			}

			if(dept_Id.equals("")){

			}
			else {
				String sql4 = "update employee set dept_id = ? where emp_id = ?";
				ps = conn.prepareStatement(sql4);
				ps.setString(1, dept_Id);
				ps.setString(2, emp_Id);
				ps.executeUpdate();
			}

				System.out.println("社員情報を更新しました。");

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
