// Attackers.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <math.h>
#include <iostream>

using namespace std;

int main()
{
	double AttackerSuccessProbability(double q, int z);
	double q =0;
	cout << "Enter success probability:  q= ";
	cin >> q;cout << endl;
	for (int z = 0; z <= 10; ++z)//可适当修改步长，例z+5
		cout << "z=" << z << " P=" << AttackerSuccessProbability(q, z) <<endl;//需修改输出格式

	system("pause");
    return 0;
}

double AttackerSuccessProbability(double q, int z)//q是成功率，z是个数
{
	double p = 1.0 - q;//失败率
	double lambda = z * (q / p);
	double sum = 1.0;//最后几率
	int i, k;
	for (k = 0; k <= z; ++k)
	{
		double poisson = exp(-lambda);
		for (i = 1; i <= k; i++)
			poisson *= lambda / i;
		sum -= poisson * (1 - pow(q / p, z - k));
	}
	return sum;
}