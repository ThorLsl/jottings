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
	int m_iWorkerTotal;		//��������
	double m_dSalaryTotal;	//��������
	double m_dMaxDailySalary;	//����չ���
	double m_dMinDailySalary;	//����չ���

	int m_iMaxWorkingDays;		//����¹�������
	int m_iMinWorkingDays;		//��С�¹�������

	vector<pair<int, double>> m_vecSalarySheet;
};
