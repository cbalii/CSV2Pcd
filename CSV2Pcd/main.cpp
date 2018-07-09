/*****
���ڣ�	2018-07-08
��д��	alii
���ܣ�	��veloview�����csv�ļ�ת��Ϊpcd�ļ�, ʹ��������ʽ�����ļ��� data_csv �е�csv�ļ�תΪ data_pcd �е�pcd�ļ�
ע�⣺	�����csv�ļ���Ҫ���õ��ļ���data_csv�£��������ļ��� data_pcd
		������ʾʹ��Σ�պ�������Ԥ�����������м��� _SCL_SECURE_NO_WARNINGS;_CRT_SECURE_NO_WARNINGS 
*****/
#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

string Trim(string& str)
{
	//str.find_first_not_of(" \t\r\n"),���ַ���str�д�����0��ʼ�������״β�ƥ��"\t\r\n"��λ��
	str.erase(0, str.find_first_not_of(" \t\r\n"));
	str.erase(str.find_last_not_of(" \t\r\n") + 1);
	return str;
}
//ģ�庯������string���ͱ���ת��Ϊ���õ���ֵ���ͣ��˷��������ձ������ԣ�
template <class Type> Type stringToNum(const string& str)
{
	istringstream iss(str);
	Type num;
	iss >> num;
	return num;
}
int main(int argc, char *argv[])
{
	fstream file_list("file_list.txt", std::ios::out);
	file_list.close();
	system("dir data_csv /a /b >> file_list.txt");

	ifstream fin0("file_list.txt"); //���ļ�������
	string line0;
	while (getline(fin0, line0))
	{
		string inputdata =  "data_csv/" + line0;
		cout << line0 ;
		line0 = line0.substr(0, line0.length() - 3);
		string outputdata = "data_pcd/" + line0  + "pcd";

		int j = 0;
		ifstream fin1(inputdata); //���ļ�������
		string line1;
		while (getline(fin1, line1))   //���ж�ȡ�����з���\n�����֣������ļ�β��־eof��ֹ��ȡ
		{
			j++;
		}

		pcl::PointCloud<pcl::PointXYZ> cloud;

		cloud.width = j - 1;//first mission  NumOfData8910
		cloud.height = 1;
		cloud.is_dense = false;
		cloud.points.resize(cloud.width*cloud.height);

		ifstream fin(inputdata); //���ļ�������
		string line;
		int i = 0;
		getline(fin, line);
		while (getline(fin, line))   //���ж�ȡ�����з���\n�����֣������ļ�β��־eof��ֹ��ȡ
		{
			istringstream sin(line); //�������ַ���line���뵽�ַ�����istringstream��
			vector<string> fields; //����һ���ַ�������
			string field;
			while (getline(sin, field, ',')) //���ַ�����sin�е��ַ����뵽field�ַ����У��Զ���Ϊ�ָ���
			{
				fields.push_back(field); //���ոն�ȡ���ַ�����ӵ�����fields��
			}
			string X = Trim(fields[0]); //���������fields�е�һ��Ԫ�ص���Ч�ַ�������ֵ������x
			string Y = Trim(fields[1]); //���������fields�еڶ���Ԫ�ص���Ч�ַ�������ֵ������y
			string Z = Trim(fields[2]); //���������fields�е�����Ԫ�ص���Ч�ַ�������ֵ������z
			//cout <<i<<":"<< "��" << X << "\t" << Y << "\t" << Z << endl;
			cloud.points[i].x = stringToNum<float>(X);
			cloud.points[i].y = stringToNum<float>(Y);
			cloud.points[i].z = stringToNum<float>(Z);
			i++;
		}
		pcl::io::savePCDFileASCII(outputdata, cloud);
		cout<< ":OK" << endl;
	}
	system("pause");
	return(0);
}