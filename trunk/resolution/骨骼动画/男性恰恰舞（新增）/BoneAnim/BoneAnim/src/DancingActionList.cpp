#include "DancingActionList.h"

DancingActionList::DancingActionList(void)
	{
		
		actNum=6;//��ʼ��������Ϊ6��
		actionnames=new Ogre::String[actNum];//��̬����ռ�
		
// 		actionnames[0]="zuojiaodengdi";//��ŵŵ�
// 		actionnames[1]="ceshen";//����
// 		actionnames[2]="zuojiaoqiluo";//�������
// 		actionnames[3]= "huizuoshou";//������
// 		actionnames[4]="xiadun";//�¶�
// 		actionnames[5]="youtuihoushen";//���Ⱥ���
// 		actionnames[6]="qitiaoluodi";//�������
// 		actionnames[7]="qianhoubu";//ǰ��i
// 		actionnames[8]="mabuyaobai";//��ҡ��
// 		actionnames[9]="youjiaoqiluo";//�ҽ�����

		actionnames[0]="niupiguyaobai";//Ťƨ��ҡ��
		actionnames[1]="zhuanquan";//תȦ
		actionnames[2]="wanyao";//����
		actionnames[3]= "qishen";//����
		actionnames[4]="shangxiafanshou";//���·���
		actionnames[5]="shoufangxia";//�ַ���


		presentActNum = 0;//��ʼ����ǰ����Ϊ��һ��
	}

DancingActionList::~DancingActionList(void)
{
	if (actionnames)
		delete[] actionnames;
}

void DancingActionList::jumpToNextAct()
{
	++presentActNum;//������һ������
	if(presentActNum == actNum)//����ǰ����Խ��,��������һ������
	{
		presentActNum = 0;
	}
}