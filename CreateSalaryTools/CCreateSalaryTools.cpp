#include<fstream>
#include <sstream>
#include <time.h>
#include "Pub_function.h"

#include "CCreateSalaryTools.h"

CCreateSalaryTools::CCreateSalaryTools()
{
}

CCreateSalaryTools::~CCreateSalaryTools()
{
}

void CCreateSalaryTools::readInformation()
{
	std::ifstream in("Information.txt");
	std::ostringstream tmp;
	tmp << in.rdbuf();
	std::string pData = tmp.str();

	std::cout << "Read informotion success" << endl;
	
	std::vector<string> vec_pData;
	Pub_Split(pData.c_str(), "\r\n", vec_pData);

	sscanf(pData.c_str(), "%f,%d,%f,%f,%d,%d",&m_dSalaryTotal,&m_iWorkerTotal,&m_dMinDailySalary,&m_dMinDailySalary,&m_iMinWorkingDays,&m_iMaxWorkingDays);
	std::cout << "工资总数：" << m_dSalaryTotal << endl
		<< "工人总数：" << m_iWorkerTotal << endl
		<< "最低日工资：" << m_dMinDailySalary << endl
		<< "最高日工资：" << m_dMaxDailySalary << endl
		<< "最小月工作天数" << m_iMinWorkingDays << endl
		<< "最大月工作天数" << m_iMaxWorkingDays << endl;
}

void CCreateSalaryTools::writeSalarySheet()
{
	std::string pdata = "";
	for (size_t i = 0; i < m_vecSalarySheet.size(); i++)
	{
		char* str;
		sprintf(str, "%f    %d    %f\r\n", m_vecSalarySheet.at(i).s_fDailyWage, m_vecSalarySheet.at(i).s_iWokeingDays, m_vecSalarySheet.at(i).s_dMonthWage);
		pdata += str;
	}

	ofstream out("out.txt");
	if (out.is_open())
	{
		out << pdata;
		out.close();
	}
}

void CCreateSalaryTools::CalculateSalary()
{
	for (size_t i = 0; i < m_iWorkerTotal; i++)
	{
		float dailyWage = RandDailyWage();
		int wokingDays = RandWokingDays();

		float salary = dailyWage*wokingDays;
		if (isSalaryMatch(salary))
		{
			SSalaryStruct pData;
			pData.s_iWokeingDays = wokingDays;
			pData.s_fDailyWage = dailyWage;
			pData.s_dMonthWage = salary;

			m_vecSalarySheet.push_back(pData);
		}
	}
}

float CCreateSalaryTools::RandDailyWage()
{
	srand(time(NULL));

	int iMin = m_dMinDailySalary / 10;
	int iMax = m_dMaxDailySalary / 10;
	float fDailyWage = (rand() % (iMax - iMin + 1) + iMin)*10.0f;
	return fDailyWage;
}

int CCreateSalaryTools::RandWokingDays()
{
	srand(time(NULL));

	int wokingDays = rand() % (m_iMaxWorkingDays - m_iMinWorkingDays + 1) + m_iMinWorkingDays;

	return wokingDays;
}

bool CCreateSalaryTools::isSalaryMatch(float fSalary)
{
	if (m_iMinWorkingDays <= fSalary&&fSalary <= m_iMaxWorkingDays)
	{
		return true;
	}

	return false;
}
