#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<numeric>
#include<Windows.h>
#include<iomanip>

using namespace std;
//string UTF8ToGB(const char* str) //����ת��utf-8 --> gbk,������벻�����ֵ������������⡣
//{
//	string result;
//	WCHAR* strSrc;
//	LPSTR szRes;
//
//	//�����ʱ�����Ĵ�С
//	int i = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
//	strSrc = new WCHAR[i + 1];
//	MultiByteToWideChar(CP_UTF8, 0, str, -1, strSrc, i);
//
//	//�����ʱ�����Ĵ�С
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
	cout << "���������е��ļ�·����" << endl;
	
	string fileName[3]; //���ļ�·��;
	for (int i = 0; i < 3; i++) {
		cin >> fileName[i];
	}

	//�����ļ�����
	fstream oriFile;
	fstream copFile;
	fstream ansFile;
	//�����ļ�����������
	string str1;
	string str2;
	//��¼ÿһ������ƶ�
	float ans;
	//��¼�ı����о������ƶ�
	vector<float> ansArray;
	//
	int len1;
	int len2;
	float sum=0;
	int count = 0;
	//��С�༭����
	float ed;

	float getEd(string str1, string str2, int len1, int len2);


	//���ļ�
	oriFile.open(fileName[0], ios::in);
	copFile.open(fileName[1],ios::in);
	ansFile.open(fileName[2], ios::out);


	//����ԭʼ�ļ��ͳ�Ϯ�ļ�
	if (oriFile.is_open() && copFile.is_open()) {
		while (!oriFile.eof()||!copFile.eof()) {
			getline(oriFile, str1);
			getline(copFile, str2);
			if (!str1.empty() || !str2.empty())
				count++;
			if (str1.empty() && str2.empty()) continue;  //  ����Ϊ���У���������

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

	sum /= count; //������

	//
	cout << sum << endl;
	
	
	//д�ļ�
	if (ansFile.is_open()) {
		ansFile <<setprecision(4)<< sum*100<<"%";
		cout << "����ɹ���" << endl;
	}

	oriFile.close();
	copFile.close();
	ansFile.close();

	system("pause");
	return 0;
}

float getEd(string str1, string str2,int len1,int len2) {  //������С�༭����
	//
	int temp;

	vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1));//len1��len2�еĶ�ά���飬��¼״ֵ̬��

	//��ʼ��
	for (int i = 1; i <= len1; i++) {  //��dp[2][0]��ʾһ������Ϊ2���ַ���str1��һ�����ַ���str2����С�༭����Ϊ2��
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