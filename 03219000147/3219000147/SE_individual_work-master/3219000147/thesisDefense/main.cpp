#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<numeric>
#include<Windows.h>
#include<iomanip>

using namespace std;
//string UTF8ToGB(const char* str) //编码转换utf-8 --> gbk,解决编码不符出现的中文乱码问题。
//{
//	string result;
//	WCHAR* strSrc;
//	LPSTR szRes;
//
//	//获得临时变量的大小
//	int i = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
//	strSrc = new WCHAR[i + 1];
//	MultiByteToWideChar(CP_UTF8, 0, str, -1, strSrc, i);
//
//	//获得临时变量的大小
//	i = WideCharToMultiByte(CP_ACP, 0, strSrc, -1, NULL, 0, NULL, NULL);
//	szRes = new CHAR[i + 1];
//	WideCharToMultiByte(CP_ACP, 0, strSrc, -1, szRes, i, NULL, NULL);
//
//	result = szRes;
//	delete[]strSrc;
//	delete[]szRes;
//
//	return result;
//}

int main() {
	cout << "请输入所有的文件路径：" << endl;
	
	string fileName[3]; //存文件路径;
	for (int i = 0; i < 3; i++) {
		cin >> fileName[i];
	}

	//创建文件对象
	fstream oriFile;
	fstream copFile;
	fstream ansFile;
	//创建文件输入流对象
	string str1;
	string str2;
	//记录每一句的相似度
	float ans;
	//记录文本所有句子相似度
	vector<float> ansArray;
	//
	int len1;
	int len2;
	float sum=0;
	int count = 0;
	//最小编辑距离
	float ed;

	float getEd(string str1, string str2, int len1, int len2);


	//打开文件
	oriFile.open(fileName[0], ios::in);
	copFile.open(fileName[1],ios::in);
	ansFile.open(fileName[2], ios::out);


	//遍历原始文件和抄袭文件
	if (oriFile.is_open() && copFile.is_open()) {
		while (!oriFile.eof()||!copFile.eof()) {
			getline(oriFile, str1);
			getline(copFile, str2);
			if (!str1.empty() || !str2.empty())
				count++;
			if (str1.empty() && str2.empty()) continue;  //  若都为空行，则跳过。

			len1 = str1.size();
			len2 = str2.size();
			ed = getEd(str1, str2, len1, len2);
			//
			cout << ed << endl;

			ans = 1.0 - 1.0 * ed / max(len1, len2);
			//
			cout << ans << endl;

			ansArray.push_back(ans);

			//
			cout << endl;
		}
	}
	//
	cout << endl;
	//
	cout << count << endl;

	vector<float>::iterator iter;
	for (iter = ansArray.begin(); iter != ansArray.end(); iter++) {
		sum += *iter;
	}
	//
	cout << sum << endl;

	sum /= count; //查重率

	//
	cout << sum << endl;
	
	
	//写文件
	if (ansFile.is_open()) {
		ansFile <<setprecision(4)<< sum*100<<"%";
		cout << "输出成功！" << endl;
	}

	oriFile.close();
	copFile.close();
	ansFile.close();

	system("pause");
	return 0;
}

float getEd(string str1, string str2,int len1,int len2) {  //计算最小编辑距离
	//
	int temp;

	vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1));//len1行len2列的二维数组，记录状态值。

	//初始化
	for (int i = 1; i <= len1; i++) {  //例dp[2][0]表示一个长度为2的字符串str1与一个空字符串str2的最小编辑距离为2。
		dp[i][0] = i;
	}
	for (int j = 1; j <= len2; j++) {
		dp[0][j] = j;
	}
	dp[0][0] = 0;

	for (int i = 1; i <= len1; i++) {
		for (int j = 1; j <= len2; j++) {
			if (str2[j - 1] == str1[i - 1])
				dp[i][j] = dp[i - 1][j - 1];
			else {
				temp = min(dp[i][j - 1], dp[i - 1][j]);
				dp[i][j] = min(temp, dp[i - 1][j - 1]) + 1;
			}
		}
	}

	return dp[len1][len2];

}