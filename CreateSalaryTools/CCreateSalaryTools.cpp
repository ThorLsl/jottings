#include<fstream>
#include <sstream>
#include <time.h>
#include "Pub_function.h"

#include "CCreateSalaryTools.h"

CCreateSalaryTools::CCreateSalaryTools()
{
	m_CurSalaryTotal = 0.0f;
	m_dAverageMonthWage = 0.0f;
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

	sscanf(vec_pData.back().c_str(), "%lf,%d,%lf,%lf,%d,%d",&m_dSalaryTotal,&m_iWorkerTotal,&m_dMinDailySalary,&m_dMaxDailySalary,&m_iMinWorkingDays,&m_iMaxWorkingDays);
	std::cout << "工资总数：" << m_dSalaryTotal << endl
		<< "工人总数：" << m_iWorkerTotal << endl
		<< "最低日工资：" << m_dMinDailySalary << endl
		<< "最高日工资：" << m_dMaxDailySalary << endl
		<< "最小月工作天数" << m_iMinWorkingDays << endl
		<< "最大月工作天数" << m_iMaxWorkingDays << endl;

	m_dAverageMonthWage = m_dSalaryTotal / m_iWorkerTotal;
}

void CCreateSalaryTools::writeSalarySheet()
{
	std::string pdata = "";
	for (size_t i = 0; i < m_vecSalarySheet.size(); i++)
	{
		char str[200];
		sprintf(str, "%f    %d    %f\n", m_vecSalarySheet.at(i).s_fDailyWage, m_vecSalarySheet.at(i).s_iWokeingDays, m_vecSalarySheet.at(i).s_dMonthWage);
		pdata += str;
	}

	char str[200];
	sprintf(str, "目标总额：%f\n生成总额：%f\n差值：%f", m_dSalaryTotal, m_CurSalaryTotal, m_dSalaryTotal - m_CurSalaryTotal);
	pdata += str;

	ofstream out("out.txt");
	if (out.is_open())
	{
		out << pdata;
		out.close();
	}
}

void CCreateSalaryTools::CalculateSalary()
{
	for (size_t i = 0; i < m_iWorkerTotal;)
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

			m_CurSalaryTotal += salary;
			
			i++;
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
	if (0.0f < fSalary&&fSalary <= 5000.0f)
	{
		return true;
	}

	return false;
}

void CCreateSalaryTools::autoAdjust()
{
	if (m_vecSalarySheet.empty()) return;

	while (true)
	{
		if (abs(m_CurSalaryTotal - m_dSalaryTotal) <= 1000) break;

		int index = rand() % m_vecSalarySheet.size();

		if (m_CurSalaryTotal > m_dSalaryTotal)
		{
			if (m_vecSalarySheet.at(index).s_dMonthWage > m_dAverageMonthWage)
			{
				float wage = m_vecSalarySheet.at(index).s_fDailyWage;
				float newWage = m_vecSalarySheet.at(index).s_dMonthWage - wage;
				if (isSalaryMatch(newWage))
				{
					m_vecSalarySheet.at(index).s_iWokeingDays -= 1;
					m_vecSalarySheet.at(index).s_dMonthWage = newWage;

					m_CurSalaryTotal -= wage;
				}
			}
		}
		else
		{
			if (m_vecSalarySheet.at(index).s_dMonthWage <= m_dAverageMonthWage)
			{
				float wage = m_vecSalarySheet.at(index).s_fDailyWage;
				float newWage = m_vecSalarySheet.at(index).s_dMonthWage + wage;
				if (isSalaryMatch(newWage))
				{
					m_vecSalarySheet.at(index).s_iWokeingDays += 1;
					m_vecSalarySheet.at(index).s_dMonthWage = newWage;

					m_CurSalaryTotal += wage;
				}
			}

		}
	}
}
