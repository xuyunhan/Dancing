#include "DancingActionList.h"

DancingActionList::DancingActionList(void)
	{
		
		actNum=10;//��ʼ��������Ϊ10��
		actionnames=new Ogre::String[actNum];//��̬����ռ�
		
		actionnames[0]="zuojiaodengdi";//��ŵŵ�
		actionnames[1]="ceshen";//����
		actionnames[2]="zuojiaoqiluo";//�������
		actionnames[3]= "huizuoshou";//������
		actionnames[4]="xiadun";//�¶�
		actionnames[5]="youtuihoushen";//���Ⱥ���
		actionnames[6]="qitiaoluodi";//�������
		actionnames[7]="qianhoubu";//ǰ��i
		actionnames[8]="mabuyaobai";//��ҡ��
		actionnames[9]="youjiaoqiluo";//�ҽ�����

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