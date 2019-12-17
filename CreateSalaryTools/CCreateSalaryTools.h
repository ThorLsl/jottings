#pragma once
#include <iostream>
#include <vector>

using namespace std;

class CCreateSalaryTools
{
public:
	CCreateSalaryTools();
	~CCreateSalaryTools();

	void readInfomation();
	void writeSalarySheet();

	double CalculateSalary();
private:
	int m_iWorkerTotal;		//工人总数
	double m_dSalaryTotal;	//工资总数
	double m_dMaxDailySalary;	//最高日工资
	double m_dMinDailySalary;	//最低日工资

	int m_iMaxWorkingDays;		//最大月工作天数
	int m_iMinWorkingDays;		//最小月工作天数

	vector<pair<int, double>> m_vecSalarySheet;
};
