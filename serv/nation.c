
/*********************************
* ���� �̸� : nation.c
* ��� : nation ����
* last modified : 2019/02/22
* ������ : �۽�ȣ
**********************************/
#include "nation.h"
#include "building.h"
#include "player.h"

/*
* �Լ� �̸� : getNationName
* return : char* nation->name
* ���� : nation nation
* ��� : nation�� �̸��� �����´�.
* last modified : 2019/02/21
* ������ : �۽�ȣ
*/
char* getNationName(Nation* nation)
{
	return nation->name;

}

/*
* �Լ� �̸� : setNationName
* return : void
* ���� : nation nation ,char* name
* ��� : nation�� �̸��� �ִ´�.
* last modified : 2019/02/21
* ������ : �۽�ȣ
*/
void setNationName(Nation* nation, char* name) {
	strcpy(nation->name, name);

}
/*
* �Լ� �̸� : getNationPrice
* return : int nation->price
* ���� : void
* ��� : nation�� price�� �����´�.
* last modified : 2019/02/21
* ������ : �۽�ȣ
*/
int getNationPrice(Nation* nation) {
	return nation->price;

}

/*
* �Լ� �̸� : setNationPrice
* return :void
* ���� : nation* nation, int price
* ��� : nation�� price��  ���ο� �������� �ٲ۴�.
* last modified : 2019/02/21
* ������ : �۽�ȣ
*/
void setNationPrice(Nation* nation, int price) {
	nation->price = price;

}

/*
* �Լ� �̸� : setNationFine
* return :void
* ���� : Nation* nation, int stack
* ��� : �ǹ����� ���̵��� �Ѵ�.
* last modified : 2019/02/22
* ������ : �۽�ȣ
*/
void stackNationPrice(Nation* nation, int s_price) {

	setNationPrice(nation, getNationPrice(nation) + s_price);
}


/*
* �Լ� �̸� : getNationLocationNum
* return :int
* ���� : Nation* nation
* ��� : location num�� return
* last modified : 2019/02/22
* ������ : �����
*/
int getNationLocationNum(Nation* nation) {
	return nation->location_num;
}

/*
* �Լ� �̸� : getNationLocationNum
* return :void
* ���� : Nation* nation, int location_num
* ��� : location num�� set
* last modified : 2019/02/22
* ������ : �����
*/
void setNationLocationNum(Nation* nation, int location_num) {
	nation->location_num = location_num;
}

/*
* �Լ� �̸� : getNationStatus
* return : int nation->action;
* ���� : nation* nation
* ��� : ������ ����� �����´�.
* last modified : 2019/02/21
* ������ : �۽�ȣ
*/
int getNationStatus(Nation* nation) {
	return nation->status;

}

/*
* �Լ� �̸� : setNationStatus
* return : void
* ���� : nation* nation, Nation_Staus status
* ��� : ������ ����� �����Ѵ�.
* last modified : 2019/02/21
* ������ : �۽�ȣ
*/
void setNationStatus(Nation* nation, Nation_Staus status) {

	nation->status = status;

}
/*
* �Լ� �̸� : getNationOwner
* return : Player*
* ���� : Nation* nation
* ��� : ������ ������ �����Ѵ�.
* last modified : 2019/02/21
* ������ : �۽�ȣ
*/
struct _player* getNationOwner(Nation* nation) {
	return nation->owner;
}
/*
* �Լ� �̸� : setNationOwner
* return :	void
* ���� : Nation* nation, Player* player
* ��� : ������ ������ �����Ѵ�
* last modified : 2019/02/21
* ������ : �۽�ȣ
*/
void setNationOwner(Nation* nation, struct _player* player) {
	nation->owner = player;
}


/*
* �Լ� �̸� : makeNation
* return : Nation *
* ���� : Nation* nation,char* name, int price, Nation_Staus status
* ��� : ���ø� ���� �� �ش� ���ø� return�Ѵ�
* last modified : 2019/02/22
* ������ : �����
*/

Nation * makeNation(char* name, int price, Nation_Staus status, int location_num) {
	Nation * nation = (Nation *)malloc(sizeof(Nation));
	nationInit(nation, name, price, status, location_num);
	return nation;
}

/*
* �Լ� �̸� : nationsInit
* return : void
* ���� : Nation * nation, char* name, int price, Nation_Staus status
* ��� : nation init
* last modified : 2019/02/22
* ������ : �����
*/

void nationInit(Nation * nation, char* name, int price, Nation_Staus status, int location_num) {
	setNationName(nation, name);
	setNationPrice(nation, price);
	setNationStatus(nation, status);
	setNationOwner(nation, NULL);           // �ʱ� ������ �����Ƿ� NULL �� �ʱ�ȭ �߽��ϴ�.
	setNationLocationNum(nation, location_num);
	nation->numOfBuilding = 0;
}

/*
* �Լ� �̸� : getNumofBuilding
* return : void
* ���� : Nation* nation
* ��� : ���ð� �����ϰ� �ִ� �ǹ��� ���� �����´�
* last modified : 2019/02/21
* ������ : �۽�ȣ
*/
int getNumofBuilding(Nation* nation) {
	return nation->numOfBuilding;

}

/*
* �Լ� �̸� : setNumofBuilding
* return : void
* ���� : Nation* nation, int num
* ��� : ���ð� ������ �ִ� �ǹ��� ���� �����Ѵ�.
* last modified : 2019/02/21
* ������ : �۽�ȣ
*/
void setNumofBuilding(Nation* nation, int num) {
	nation->numOfBuilding = num;

}


/*
* �Լ� �̸� : checkNumofBuilding
* return : int
* ���� : Nation* nation
* ��� : �ش� nation ����ü�� NumofBuliding �� ���� 3�� �Ѵ��� �ʳѴ��� üũ
3�� �ѱ��� ������ TRUE ����  3�� �ѱ�� FALSE ����
* last modified : 2019/02/21
* ������ : �۽�ȣ
*/
int checkNumofBuilding(Nation* nation) {
	if (getNumofBuilding(nation) < BUILDINGCOUNT)
	{
		return TRUE;

	}
	else
		return FALSE;


}




/*
* �Լ� �̸� : findLocationByNum
* return : Nation *
* ���� : Nation** city, int cur_location
* ��� : city �迭 ���� city ���� cur_location�� ���� city�� ã���ش�
* last modified : 2019/02/22
* ������ : �����
*/
Nation* findLocationByNum(Nation ** city, int cur_location) {
	// index�� �� location�̹Ƿ�
	return city[cur_location];
}


/*
* �Լ� �̸� : whoPossess
* return : Player*  ���ǿ� ���� NULL �ϰ�� 0 �ƴҰ�� �ش� ������ Player�� �ּҰ� ��ȯ
* ���� : Nation ** city, int cur_location
* ��� : ���� ��ȣ�� ���� ���ÿ� ������ �ִ��� �������� ���� ����
* last modified : 2019/02/22
* ������ : �����
*/
struct _player* whoPossess(Nation ** city, int cur_location) {
	//	if (city[cur_location]->owner == NULL)  //NULL�� ���...? ������ NULL�̸� NULL return.
	//		return 0;
	//	else
	return city[cur_location]->owner;

}
/*
* �Լ� �̸� : findLocation
* return : Nation*
* ���� : Nation ** city, char * name
* ��� : �̸��� �Ѱ� �޾� �̸��� ��ġ�ϴ� ���ð� �ִ��� Ȯ��
* last modified : 2019/02/23
* ������ : �����
*/
Nation* findLocation(Nation ** city, char * name) {
	for (int i = 0; i < CITY_COUNT; i++) {
		if (strcmp(city[i]->name, name) == 0)
			return city[i];
	}
	return NULL;
}


/*
* �Լ� �̸� :delNationOwner
* return : int
* ���� : Nation* nation
* ��� : �Ű� �Ǵ� �Ļ�ÿ� ������ �ǹ������� ����ϰ�  ���� 80%�� ���� �׸��� �ʱ�ȭ
* last modified : 2019/02/22
* ������ : �۽�ȣ
*/
int delNationOwner(Nation* nation) {
	int temp = 0.8*getNationPrice(nation);
	nationBuildingClear(nation);
	setNationOwner(nation, NULL);
	return temp;
}

/*
* �Լ� �̸� :addNationBuilding
* return : int
* ���� : Nation* nation, Building * building
* ��� :  nation ���� ����
* last modified : 2019/02/22
* ������ : �۽�ȣ
*/

int addNationBuilding(Nation * nation, Building building) {
	if (checkNumofBuilding(nation)) {   // �ش� ����ü�� �ǹ��� ���� 3�������� üũ
		nation->buildings[nation->numOfBuilding++] = building;  //�ǹ� ����
		stackNationPrice(nation, building.price); //�ǹ��� ���� nation�� price �� ����
		setNumofBuilding(nation, getNumofBuilding(nation) + 1); // �ǹ��� ���� ����
		return TRUE; // ���������� ���������
	}
	else
		return FALSE; // �ǹ��� ���� 3�̻��̰ų� �������� ��� 
}


/*
* �Լ� �̸� :nationBuildingClear
* return : void
* ���� : Nation* nation,char* name, int price, Nation_Staus status
* ��� : nation ����ü ������ building���� �ʱ�ȭ �Ѵ�.
* last modified : 2019/02/21
* ������ : �۽�ȣ
*/
void nationBuildingClear(Nation* nation) {
	int numOfBuilding = nation->numOfBuilding;
	for (int i = 0; i < numOfBuilding; i++) {
//		buildingClear(&(nation->buildings[i])); // memory allocation�� ���� �ʾ� �ʿ� x.
		numOfBuilding--;
	}
	setNumofBuilding(nation, numOfBuilding);
}