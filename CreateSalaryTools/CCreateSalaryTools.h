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
	bool isWorkingDaysMatch(int days);
	void autoAdjust();
private:
	int m_iWorkerTotal;		//��������
	double m_dSalaryTotal;	//��������
	vector<double> m_dailyWageVec;	//�չ���

	int m_iMaxWorkingDays;		//����¹�������
	int m_iMinWorkingDays;		//��С�¹�������

	vector<SSalaryStruct> m_vecSalarySheet;

	double m_dAverageMonthWage;
	float m_CurSalaryTotal;
};
