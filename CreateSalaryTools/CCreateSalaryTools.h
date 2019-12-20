#pragma once
#include <iostream>
#include <vector>

using namespace std;

struct SSalaryStruct
{
	int s_iWokeingDays;
	float s_fDailyWage;
	double s_dMonthWage;

	SSalaryStruct():s_iWokeingDays(0),s_fDailyWage(0.0),s_dMonthWage(0.0) {}
};

class CCreateSalaryTools
{
public:
	CCreateSalaryTools();
	~CCreateSalaryTools();

	void readInformation();
	void writeSalarySheet();

	void CalculateSalary();

	float RandDailyWage();
	int RandWokingDays();
	
	bool isSalaryMatch(float fSalary);
private:
	int m_iWorkerTotal;		//工人总数
	double m_dSalaryTotal;	//工资总数
	double m_dMaxDailySalary;	//最高日工资
	double m_dMinDailySalary;	//最低日工资

	int m_iMaxWorkingDays;		//最大月工作天数
	int m_iMinWorkingDays;		//最小月工作天数

	vector<SSalaryStruct> m_vecSalarySheet;
};
