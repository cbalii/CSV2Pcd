/*****
日期：	2018-07-08
编写：	alii
功能：	将veloview输出的csv文件转换为pcd文件, 使用批处理方式，将文件夹 data_csv 中的csv文件转为 data_pcd 中的pcd文件
注意：	输入的csv文件需要放置到文件夹data_csv下，并建立文件夹 data_pcd
		报错提示使用危险函数，在预处理器定义中加入 _SCL_SECURE_NO_WARNINGS;_CRT_SECURE_NO_WARNINGS 
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
	//str.find_first_not_of(" \t\r\n"),在字符串str中从索引0开始，返回首次不匹配"\t\r\n"的位置
	str.erase(0, str.find_first_not_of(" \t\r\n"));
	str.erase(str.find_last_not_of(" \t\r\n") + 1);
	return str;
}
//模板函数：将string类型变量转换为常用的数值类型（此方法具有普遍适用性）
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

	ifstream fin0("file_list.txt"); //打开文件流操作
	string line0;
	while (getline(fin0, line0))
	{
		string inputdata =  "data_csv/" + line0;
		cout << line0 ;
		line0 = line0.substr(0, line0.length() - 3);
		string outputdata = "data_pcd/" + line0  + "pcd";

		int j = 0;
		ifstream fin1(inputdata); //打开文件流操作
		string line1;
		while (getline(fin1, line1))   //整行读取，换行符“\n”区分，遇到文件尾标志eof终止读取
		{
			j++;
		}

		pcl::PointCloud<pcl::PointXYZ> cloud;

		cloud.width = j - 1;//first mission  NumOfData8910
		cloud.height = 1;
		cloud.is_dense = false;
		cloud.points.resize(cloud.width*cloud.height);

		ifstream fin(inputdata); //打开文件流操作
		string line;
		int i = 0;
		getline(fin, line);
		while (getline(fin, line))   //整行读取，换行符“\n”区分，遇到文件尾标志eof终止读取
		{
			istringstream sin(line); //将整行字符串line读入到字符串流istringstream中
			vector<string> fields; //声明一个字符串向量
			string field;
			while (getline(sin, field, ',')) //将字符串流sin中的字符读入到field字符串中，以逗号为分隔符
			{
				fields.push_back(field); //将刚刚读取的字符串添加到向量fields中
			}
			string X = Trim(fields[0]); //清除掉向量fields中第一个元素的无效字符，并赋值给变量x
			string Y = Trim(fields[1]); //清除掉向量fields中第二个元素的无效字符，并赋值给变量y
			string Z = Trim(fields[2]); //清除掉向量fields中第三个元素的无效字符，并赋值给变量z
			//cout <<i<<":"<< "：" << X << "\t" << Y << "\t" << Z << endl;
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