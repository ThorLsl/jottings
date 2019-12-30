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

	std::vector<string> vec_pData;
	Pub_Split(pData.c_str(), "\r\n", vec_pData);

	if (vec_pData.size() == 4)
	{
		std::cout << "Read informotion success" << endl;

		sscanf(vec_pData.at(2).c_str(), "%lf,%d,%d,%d", &m_dSalaryTotal, &m_iWorkerTotal, &m_iMinWorkingDays, &m_iMaxWorkingDays);

		std::vector<string> vec_pData1;
		Pub_Split(vec_pData.back().c_str(), "#", vec_pData1);
		m_dailyWageVec.clear();
		for (size_t i = 0; i < vec_pData1.size(); i++)
		{
			double wage = 0.0f;
			sscanf(vec_pData1.at(i).c_str(), "%lf", &wage);
			m_dailyWageVec.push_back(wage);
		}

		m_dAverageMonthWage = m_dSalaryTotal / m_iWorkerTotal;

		std::cout << "工资总数：" << m_dSalaryTotal << endl
			<< "工人总数：" << m_iWorkerTotal << endl
			<< "最小月工作天数" << m_iMinWorkingDays << endl
			<< "最大月工作天数" << m_iMaxWorkingDays << endl;
		std::cout << "日工资：";
		for (auto temp : m_dailyWageVec)
		{
			std::cout << temp<<"\t";
		}
		std::cout << endl;
	}
	else
	{
		std::cout << "Read informotion false" << endl;
	}
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

		std::cout << "Write data to out.txt" << endl;
	}
}

void CCreateSalaryTools::CalculateSalary()
{
	srand(time(NULL));

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

			//std::cout << dailyWage << "\t" << wokingDays << "\t" << salary << endl;
		}
	}
}

float CCreateSalaryTools::RandDailyWage()
{
	int k = rand() % (m_dailyWageVec.size());
	//std::cout << k << endl;
	float fDailyWage = m_dailyWageVec.at(k);
	return fDailyWage;
}

int CCreateSalaryTools::RandWokingDays()
{
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

bool CCreateSalaryTools::isWorkingDaysMatch(int days)
{
	if (m_iMinWorkingDays <= days&& days <= m_iMaxWorkingDays)
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
				if (isSalaryMatch(newWage) && isWorkingDaysMatch(m_vecSalarySheet.at(index).s_iWokeingDays - 1))
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
				if (isSalaryMatch(newWage) && isWorkingDaysMatch(m_vecSalarySheet.at(index).s_iWokeingDays + 1))
				{
					m_vecSalarySheet.at(index).s_iWokeingDays += 1;
					m_vecSalarySheet.at(index).s_dMonthWage = newWage;

					m_CurSalaryTotal += wage;
				}
			}

		}
	}
}
