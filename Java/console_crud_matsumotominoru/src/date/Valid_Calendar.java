package jp.co.sss.crud.date;

public class Valid_Calendar {
	public static final  boolean valid_Calendar(int year , int month , int day){
		if(day <= 0 || day >= 32){
			return false;
		}
		if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12){
			return true;
		}
		if (month == 4 || month == 6 || month == 9 || month == 11){
			if(day == 31){
				return false;
			}
			else {
				return true;
			}

		}
		if (month == 2){
			if(day <= 28){
				return true;
			}
			else if (isLeapYear(year) && day == 29){
				return true;
			}
		}
		return false;
	}

	public static final boolean isLeapYear(int year){
		boolean bl = false;
		if (year%4 == 0){
			bl = true;
			if(year%100 == 0){
				bl = false;
				if(year%400 == 0){
					bl = true;
				}
			}
		}

	return bl;
	}

}
