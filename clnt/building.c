
/*********************************
* 파일 이름 : building.c
* 기능 : building 관련 함수 선언
* last modified : 2019/02/21
* 수정자 : 송승호
**********************************/
#include "building.h"
/*
* 함수 이름 : get_name
* return : char* b->name
* 인자 : nation nation
* 기능 : building의 이름을 가져온다.
* last modified : 2019/02/21
* 수정자 : 송승호
*/
char* getBuildingName(Building* b) {
	return b->name;
}
/*
* 함수 이름 : set_name
* return : void
* 인자 : building* b ,char* name
* 기능 : building에 이름을 넣는다.
* last modified : 2019/02/21
* 수정자 : 송승호
*/
void setBuildingName(Building* b) {
	strcpy(b->name, "빌딩");
}
/*
* 함수 이름 : get_price
* return : int b->price
* 인자 : building* b
* 기능 : nation의 price를 가져온다.
* last modified : 2019/02/21
* 수정자 : 송승호
*/
int getBuildingPrice(Building* b) {
	return b->price;
}
/*
* 함수 이름 : set_price
* return :void
* 인자 : building* b, int price ;
* 기능 : nation의 price를  새로운 가격으로 바꾼다.
* last modified : 2019/02/21
* 수정자 : 송승호
*/
void setBuildingPrice(Building* b, int price) {
	b->price = price;
}

/*
* 함수 이름 : makeBuilding
* return : Building* b
* 인자 : Building *b, char* name, int price
* 기능 : building을 구성하고 building을 리턴한다.
* last modified : 2019/02/21
* 수정자 : 송승호
*/
void makeBuilding(Building *b, int price) {
//	Building * b = (Building  *)malloc(sizeof(Building));
	buildingInit(b, price);
	return b;
}

/*
* 함수 이름 : buildingInit
* return :
* 인자 :void
* 기능 : building을 초기화 한다.
* last modified : 2019/02/21
* 수정자 : 송승호
*/
void buildingInit(Building* b, int price) {
	setBuildingName(b);
	setBuildingPrice(b, price);
}