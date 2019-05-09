
/*********************************
* ���� �̸� : building.c
* ��� : building ���� �Լ� ����
* last modified : 2019/02/21
* ������ : �۽�ȣ
**********************************/
#include "building.h"
/*
* �Լ� �̸� : get_name
* return : char* b->name
* ���� : nation nation
* ��� : building�� �̸��� �����´�.
* last modified : 2019/02/21
* ������ : �۽�ȣ
*/
char* getBuildingName(Building* b) {
	return b->name;
}
/*
* �Լ� �̸� : set_name
* return : void
* ���� : building* b ,char* name
* ��� : building�� �̸��� �ִ´�.
* last modified : 2019/02/21
* ������ : �۽�ȣ
*/
void setBuildingName(Building* b) {
	strcpy(b->name, "����");
}
/*
* �Լ� �̸� : get_price
* return : int b->price
* ���� : building* b
* ��� : nation�� price�� �����´�.
* last modified : 2019/02/21
* ������ : �۽�ȣ
*/
int getBuildingPrice(Building* b) {
	return b->price;
}
/*
* �Լ� �̸� : set_price
* return :void
* ���� : building* b, int price ;
* ��� : nation�� price��  ���ο� �������� �ٲ۴�.
* last modified : 2019/02/21
* ������ : �۽�ȣ
*/
void setBuildingPrice(Building* b, int price) {
	b->price = price;
}

/*
* �Լ� �̸� : makeBuilding
* return : Building* b
* ���� : Building *b, char* name, int price
* ��� : building�� �����ϰ� building�� �����Ѵ�.
* last modified : 2019/02/21
* ������ : �۽�ȣ
*/
void makeBuilding(Building *b, int price) {
//	Building * b = (Building  *)malloc(sizeof(Building));
	buildingInit(b, price);
	return b;
}

/*
* �Լ� �̸� : buildingInit
* return :
* ���� :void
* ��� : building�� �ʱ�ȭ �Ѵ�.
* last modified : 2019/02/21
* ������ : �۽�ȣ
*/
void buildingInit(Building* b, int price) {
	setBuildingName(b);
	setBuildingPrice(b, price);
}