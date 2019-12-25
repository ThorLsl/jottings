#include "CCreateSalaryTools.h"


int main()
{
	auto pSolution = CCreateSalaryTools();

	pSolution.readInformation();
	pSolution.CalculateSalary();
	pSolution.autoAdjust();
	pSolution.writeSalarySheet();

	system("pause");

	return 0;
}