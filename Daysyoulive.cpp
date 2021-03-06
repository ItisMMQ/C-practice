#include "stdafx.h"
#include <stdlib.h>
#include "stdio.h"
#include <iostream>
using namespace std;

typedef struct
{
	int month;
	int day;
	int year;
}Date;

int Days(Date *tod, Date *bir)
{
	//enum Months{Jan=1,Feb,Mar,Apr,May,Jun,Jul,Aus,Sep,Oct,Nov,Dec};
	int m = 0, d = 0, y = (tod->year) - (bir->year) - 1, sum = 0;
	y = y * 365;
	for (int k = bir->year; k < tod->year; k++)//加上由于闰年多出的日子
	{
		if (k % 4 == 0)
		{
			sum += 1;
		}
	}
	if (tod->month > 2 && tod->year % 4 == 0 || tod->month == 2 && tod->day == 29)
	{
		sum += 1;
	}
	for
		(int i = (bir->month + 1); i <= 12; i++)//我出生后一个月到过年那几个月的日子
	{
		switch (i)
		{
		case 1:m = 31; break;//不用算，因为不可能从一月开始
		case 2:m = 28; break;
		case 3:m = 31; break;
		case 4:m = 30; break;
		case 5:m = 31; break;
		case 6:m = 30; break;
		case 7:m = 31; break;
		case 8:m = 31; break;
		case 9:m = 30; break;
		case 10:m = 31; break;
		case 11:m = 30; break;
		case 12:m = 31; break;
		default:break;
		}
		sum += m;
	}
	for (int j = 1; j < tod->month; j++)//今年到现在为止的上个月已过的月份
	{
		switch (j)
		{
		case 1:m = 31; break;
		case 2:m = 28; break;
		case 3:m = 31; break;
		case 4:m = 30; break;
		case 5:m = 31; break;
		case 6:m = 30; break;
		case 7:m = 31; break;
		case 8:m = 31; break;
		case 9:m = 30; break;
		case 10:m = 31; break;
		case 11:m = 30; break;
		case 12:m = 31; break;//不用算，因为不可能把十二月过完
		default:break;
		}
		sum += m;

	}
	//出生的那个月和当前月一共度过了几天
	switch (bir->month)
	{
	case 1:m = 31; break;
	case 2:m = 28; break;
	case 3:m = 31; break;
	case 4:m = 30; break;
	case 5:m = 31; break;
	case 6:m = 30; break;
	case 7:m = 31; break;
	case 8:m = 31; break;
	case 9:m = 30; break;
	case 10:m = 31; break;
	case 11:m = 30; break;
	case 12:m = 31; break;
	default:break;
	}
	d = m - bir->day + tod->day;
	sum = sum + y + d;
	cout << "You have live for " << sum << " days!" << endl;
	return 0;
}


int main()
{
	Date birthday;
	Date today = { 3,16,2018 };  //可以改为读入系统日期
	cout << "Please input your birthday:(month-day-year)" << endl;
	cin >> birthday.month >> birthday.day >> birthday.year;
	int Days(Date *tod, Date *bir);  //将两个日期的结构体指针传入
	Date *tod = &today, *bir = &birthday;
	Days(tod, bir);
	system("pause");
	return 0;
}
