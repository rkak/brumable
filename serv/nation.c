
/*********************************
* 파일 이름 : nation.c
* 기능 : nation 선언
* last modified : 2019/02/22
* 수정자 : 송승호
**********************************/
#include "nation.h"
#include "building.h"
#include "player.h"

/*
* 함수 이름 : getNationName
* return : char* nation->name
* 인자 : nation nation
* 기능 : nation의 이름을 가져온다.
* last modified : 2019/02/21
* 수정자 : 송승호
*/
char* getNationName(Nation* nation)
{
	return nation->name;

}

/*
* 함수 이름 : setNationName
* return : void
* 인자 : nation nation ,char* name
* 기능 : nation에 이름을 넣는다.
* last modified : 2019/02/21
* 수정자 : 송승호
*/
void setNationName(Nation* nation, char* name) {
	strcpy(nation->name, name);

}
/*
* 함수 이름 : getNationPrice
* return : int nation->price
* 인자 : void
* 기능 : nation의 price를 가져온다.
* last modified : 2019/02/21
* 수정자 : 송승호
*/
int getNationPrice(Nation* nation) {
	return nation->price;

}

/*
* 함수 이름 : setNationPrice
* return :void
* 인자 : nation* nation, int price
* 기능 : nation의 price를  새로운 가격으로 바꾼다.
* last modified : 2019/02/21
* 수정자 : 송승호
*/
void setNationPrice(Nation* nation, int price) {
	nation->price = price;

}

/*
* 함수 이름 : setNationFine
* return :void
* 인자 : Nation* nation, int stack
* 기능 : 건물값이 쌓이도록 한다.
* last modified : 2019/02/22
* 수정자 : 송승호
*/
void stackNationPrice(Nation* nation, int s_price) {

	setNationPrice(nation, getNationPrice(nation) + s_price);
}


/*
* 함수 이름 : getNationLocationNum
* return :int
* 인자 : Nation* nation
* 기능 : location num을 return
* last modified : 2019/02/22
* 수정자 : 박희완
*/
int getNationLocationNum(Nation* nation) {
	return nation->location_num;
}

/*
* 함수 이름 : getNationLocationNum
* return :void
* 인자 : Nation* nation, int location_num
* 기능 : location num을 set
* last modified : 2019/02/22
* 수정자 : 박희완
*/
void setNationLocationNum(Nation* nation, int location_num) {
	nation->location_num = location_num;
}

/*
* 함수 이름 : getNationStatus
* return : int nation->action;
* 인자 : nation* nation
* 기능 : 도시의 기능을 가져온다.
* last modified : 2019/02/21
* 수정자 : 송승호
*/
int getNationStatus(Nation* nation) {
	return nation->status;

}

/*
* 함수 이름 : setNationStatus
* return : void
* 인자 : nation* nation, Nation_Staus status
* 기능 : 도시의 기능을 설정한다.
* last modified : 2019/02/21
* 수정자 : 송승호
*/
void setNationStatus(Nation* nation, Nation_Staus status) {

	nation->status = status;

}
/*
* 함수 이름 : getNationOwner
* return : Player*
* 인자 : Nation* nation
* 기능 : 도시의 주인을 리턴한다.
* last modified : 2019/02/21
* 수정자 : 송승호
*/
struct _player* getNationOwner(Nation* nation) {
	return nation->owner;
}
/*
* 함수 이름 : setNationOwner
* return :	void
* 인자 : Nation* nation, Player* player
* 기능 : 도시의 주인을 저장한다
* last modified : 2019/02/21
* 수정자 : 송승호
*/
void setNationOwner(Nation* nation, struct _player* player) {
	nation->owner = player;
}


/*
* 함수 이름 : makeNation
* return : Nation *
* 인자 : Nation* nation,char* name, int price, Nation_Staus status
* 기능 : 도시를 설정 후 해당 도시를 return한다
* last modified : 2019/02/22
* 수정자 : 박희완
*/

Nation * makeNation(char* name, int price, Nation_Staus status, int location_num) {
	Nation * nation = (Nation *)malloc(sizeof(Nation));
	nationInit(nation, name, price, status, location_num);
	return nation;
}

/*
* 함수 이름 : nationsInit
* return : void
* 인자 : Nation * nation, char* name, int price, Nation_Staus status
* 기능 : nation init
* last modified : 2019/02/22
* 수정자 : 박희완
*/

void nationInit(Nation * nation, char* name, int price, Nation_Staus status, int location_num) {
	setNationName(nation, name);
	setNationPrice(nation, price);
	setNationStatus(nation, status);
	setNationOwner(nation, NULL);           // 초기 주인은 없으므로 NULL 로 초기화 했습니다.
	setNationLocationNum(nation, location_num);
	nation->numOfBuilding = 0;
}

/*
* 함수 이름 : getNumofBuilding
* return : void
* 인자 : Nation* nation
* 기능 : 도시가 보유하고 있는 건물의 수를 가져온다
* last modified : 2019/02/21
* 수정자 : 송승호
*/
int getNumofBuilding(Nation* nation) {
	return nation->numOfBuilding;

}

/*
* 함수 이름 : setNumofBuilding
* return : void
* 인자 : Nation* nation, int num
* 기능 : 도시가 가지고 있는 건물의 수를 저장한다.
* last modified : 2019/02/21
* 수정자 : 송승호
*/
void setNumofBuilding(Nation* nation, int num) {
	nation->numOfBuilding = num;

}


/*
* 함수 이름 : checkNumofBuilding
* return : int
* 인자 : Nation* nation
* 기능 : 해당 nation 구조체에 NumofBuliding 의 수가 3을 넘는지 않넘는지 체크
3을 넘기지 않으면 TRUE 리턴  3을 넘기면 FALSE 리턴
* last modified : 2019/02/21
* 수정자 : 송승호
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
* 함수 이름 : findLocationByNum
* return : Nation *
* 인자 : Nation** city, int cur_location
* 기능 : city 배열 내의 city 내의 cur_location과 같은 city를 찾아준다
* last modified : 2019/02/22
* 수정자 : 박희완
*/
Nation* findLocationByNum(Nation ** city, int cur_location) {
	// index가 곧 location이므로
	return city[cur_location];
}


/*
* 함수 이름 : whoPossess
* return : Player*  조건에 따라 NULL 일경우 0 아닐경우 해당 도시의 Player의 주소값 반환
* 인자 : Nation ** city, int cur_location
* 기능 : 받은 번호에 대한 도시에 주인이 있는지 없는지에 대한 여부
* last modified : 2019/02/22
* 수정자 : 박희완
*/
struct _player* whoPossess(Nation ** city, int cur_location) {
	//	if (city[cur_location]->owner == NULL)  //NULL인 경우...? 어차피 NULL이면 NULL return.
	//		return 0;
	//	else
	return city[cur_location]->owner;

}
/*
* 함수 이름 : findLocation
* return : Nation*
* 인자 : Nation ** city, char * name
* 기능 : 이름을 넘겨 받아 이름과 일치하는 도시가 있는지 확인
* last modified : 2019/02/23
* 수정자 : 박희완
*/
Nation* findLocation(Nation ** city, char * name) {
	for (int i = 0; i < CITY_COUNT; i++) {
		if (strcmp(city[i]->name, name) == 0)
			return city[i];
	}
	return NULL;
}


/*
* 함수 이름 :delNationOwner
* return : int
* 인자 : Nation* nation
* 기능 : 매각 또는 파산시에 땅값과 건물가격을 계산하고  그중 80%만 리턴 그리고 초기화
* last modified : 2019/02/22
* 수정자 : 송승호
*/
int delNationOwner(Nation* nation) {
	int temp = 0.8*getNationPrice(nation);
	nationBuildingClear(nation);
	setNationOwner(nation, NULL);
	return temp;
}

/*
* 함수 이름 :addNationBuilding
* return : int
* 인자 : Nation* nation, Building * building
* 기능 :  nation 빌딩 생성
* last modified : 2019/02/22
* 수정자 : 송승호
*/

int addNationBuilding(Nation * nation, Building building) {
	if (checkNumofBuilding(nation)) {   // 해당 구조체의 건물의 수가 3이하인지 체크
		nation->buildings[nation->numOfBuilding++] = building;  //건물 생성
		stackNationPrice(nation, building.price); //건물의 가격 nation의 price 에 더함
		setNumofBuilding(nation, getNumofBuilding(nation) + 1); // 건물의 갯수 증가
		return TRUE; // 성공적으로 마쳤을경우
	}
	else
		return FALSE; // 건물의 수가 3이상이거나 실패했을 경우 
}


/*
* 함수 이름 :nationBuildingClear
* return : void
* 인자 : Nation* nation,char* name, int price, Nation_Staus status
* 기능 : nation 구조체 내부의 building들을 초기화 한다.
* last modified : 2019/02/21
* 수정자 : 송승호
*/
void nationBuildingClear(Nation* nation) {
	int numOfBuilding = nation->numOfBuilding;
	for (int i = 0; i < numOfBuilding; i++) {
//		buildingClear(&(nation->buildings[i])); // memory allocation을 하지 않아 필요 x.
		numOfBuilding--;
	}
	setNumofBuilding(nation, numOfBuilding);
}