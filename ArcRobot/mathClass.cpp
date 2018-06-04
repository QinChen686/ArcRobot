#include "stdafx.h"
#include "mathClass.h"

vector<double> mathfun::str2vec(char *pos)
{
	vector<double> res(7, 0);
	char* posChar;
	posChar = pos+1;
	sscanf_s(pos, "[%lf,%lf,%lf][%lf,%lf,%lf,%lf]", &res[0], &res[1], &res[2], &res[3], &res[4], &res[5], &res[6]);
	return res;
}