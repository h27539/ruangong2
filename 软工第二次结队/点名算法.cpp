#include <iostream>
#include <istream>
#include <streambuf>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;
struct student{
    string id;
    string name;
    string grade;//绩点
    string a[20];//20次出勤记录
    int mark;//出勤分数
    double result;
}stu[90],item;
int main() {
    string course,path;
    cout<<"输入五门课程到勤信息所在文件夹目录（eg.user/tables）："<<endl;
    cin>>path;
    int i=0;
//    cout<<"课程序号（1/2/3/4/5）：";
//    cin>>course;
    double sum=0;
    for (int iii=1; iii<=5; iii++) {
        string csv_path;
        
        csv_path=path+"/course"+to_string(iii)+".csv";
//        cout<<path<<endl;
        ifstream csv_data(csv_path, ios::in);
    //    infile.open(str.c_str(), ios::in);
        string line;
        if (!csv_data.is_open())
        {
            cout << "Error: opening file fail" << endl;
            exit(1);
        }
        istringstream sin;         //将整行字符串line读入到字符串istringstream中
        vector<std::string> words; //声明一个字符串向量
        string word;
        // 读取标题行
        getline(csv_data, line);
        // 读取数据
        i=0;
        while (getline(csv_data, line))
        {
            sin.clear();
            sin.str(line);
            words.clear();
            int j=0,k=0;
            while (getline(sin, word, ',')) //将字符串流sin中的字符读到field字符串中，以逗号为分隔符
             {
                words.push_back(word); //将每一格中的数据逐个push
                 switch (j++) {
                     case 0: stu[i].id=word;break;
                     case 1: stu[i].name=word;break;
                     case 2: stu[i].grade=word;break;
                     default: stu[i].a[k++]=word;
                 }
    //            cout << word<<" ";
            }
    //        cout << endl;
            i++;
            // do something
        }
        //此时已经得到每个学生具体的数据，并按顺序存储在结构体对应的位置里面。
        int ii=20;
        double E_sum=0;
        while (ii--) {
//            cout<<"第"<<20-ii<<"次点名：";
            int N=20-ii;//第N次抽点
    //        scanf("%d",&N);
            for(i=0;i<90;i++){
                stu[i].mark=100; //初始换出勤分数每人为100分，如果缺勤一次扣5分。
            }
            int j=0;
            for(i=0;i<90;i++){
                for(j=0;j<N-1;j++){
                    if(stu[i].a[j]=="0"){
                        stu[i].mark-=5;
                    }
                }
            }
            //得到每个人的出勤总分数
            //开始计算每个人的最终得分result=rate1*grade(绩点）+rate2*mark(出勤分数）；
            double rate1=0.1,rate2=0.9;
            for(i=0;i<90;i++){
                stu[i].result=rate1*atoi(stu[i].grade.c_str())+rate2*stu[i].mark;
            }
            //进行排序，按从小到大排序进行排序
            for(i=0;i<89;i++){
                for(j=0;j<89;j++){
                    if(stu[j].result>stu[j+1].result){
                        item=stu[j];
                        stu[j]=stu[j+1];
                        stu[j+1]=item;
                    }
                }
            }
            //完成排序，抽人可以按顺序用学号进行抽点。
            int n=4;//抽点的人数，也可以为90；
            double n1=0;
            for(i=0;i<n;i++){
//                cout<<stu[i].id<<" ";
                if (stu[i].a[N-1]=="0") n1++;
            }
//            cout<<endl<<"第"<<N<<"次E = "<<n1/n<<endl;
            E_sum+=n1/n;
        }
//        cout<<"E = "<<E_sum/20<<endl;
        sum+=E_sum/20;
        csv_data.close();
    }
    cout<<"E = "<<sum/5<<endl;
    return 0;
}
