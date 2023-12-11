//결정 + 상담
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include <stdlib.h> // rand()함수 포함 라이브러리
#include <time.h> // time()함수 포함 라이브러리
#include<cmath> //반올림 함수 round() 사용 
#include<Windows.h>
#include<conio.h>
#include<vector> 
#include <time.h>

// UI 색상
#define COLOR_NONE		"\033[0m"
#define COLOR_BLACK		"\033[0;30m"
#define COLOR_GRAY		"\033[0;37m"
#define COLOR_BBLACK	"\033[0;90m"
#define COLOR_RED		"\033[0;31m"
#define COLOR_GREEN		"\033[0;32m"
#define COLOR_YELLOW	"\033[0;93m"
#define COLOR_BLUE		"\033[0;34m"
#define COLOR_BBLUE		"\033[0;94m"
#define COLOR_PURPLE	"\033[0;35m"
#define COLOR_CYAN		"\033[0;36m"
#define COLOR_BCYAN     "\033[0;96m"
#define log(x, str) printf(x str COLOR_NONE"\n"); 


int explore;
using namespace std;


void gotoxy(int x, int y) {
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

class Planet {
	//남은 일 수, 이동하는데 쓰는 에너지, 얻을 수 있는 자원, 음식, 생명체 존재 유무(존재 시 1, 아니면 0) 
	int dayUntil, usingEnergy, energy, food, creature;
	string PlanetType, level, cretureType; //행성 타입, 난이도, 생명체 성향 
public:
	Planet(int cp); //행성 정보 랜덤으로 뽑아 넣기 
	void showPlanetState(); //행성 정보 띄우기
	int ShowIntState(int n) { //1 입력 시 남은 일 수, 2 이동하는데 쓰는 에너지, 3 얻을 수 있는 자원, 4 얻을 수 있는 음식, 5 생명체 존재 유무 값 반환 
		if (n == 1) return dayUntil;
		else if (n == 2) return usingEnergy;
		else if (n == 3) return energy;
		else if (n == 4) return food;
		else return creature;
	}
	string ShowStringState(int n) { //1 입력 시 행성 타입, 2 난이도, 3 생명체 성향  값 반환 
		if (n == 1) return PlanetType;
		else if (n == 2) return level;
		else return cretureType;
	}
};

Planet::Planet(int cp) {
	int random;
	srand(cp); // 매번 다른 시드값 생성
	dayUntil = rand() % 8 + 3; // 3~10

	switch (dayUntil) {
	case 3:
		usingEnergy = 310;
		break;
	case 4:
		usingEnergy = 424;
		break;
	case 5:
		usingEnergy = 538;
		break;
	case 6:
		usingEnergy = 653;
		break;
	case 7:
		usingEnergy = 767;
		break;
	case 8:
		usingEnergy = 881;
		break;
	case 9:
		usingEnergy = 996;
		break;
	default:
		usingEnergy = 1110;
	}

	if (rand() % 2 == 0) PlanetType = "가스";
	else PlanetType = "암석";

	random = rand() % 3;
	if (random == 0) level = "상";
	else if (random == 1) level = "중";
	else level = "하";

	creature = rand() % 2;

	if (rand() % 2 == 0) cretureType = "공격";
	else cretureType = "온순";

	energy = rand() % 3 + 1;
	food = rand() % 3 + 1;
}

class Room {
protected:
	int lv; // 업그레이드 레벨
	string name;
public:
	Room() { lv = 0; }
	//업그레이드 실패(최대 레벨일 시 0, 자원 부족 시 1 반환), 성공 시 업그레이드 비용 반환
	//성공은 하는데 업글 이후 자원값이 100이하로 남으면 경고 메시지 출력
	int Upgrade(int resource);
	int ShowLv() { return lv; }
	string ShowName() { return name; }
	void lvUp() {
		lv++;
	}
	virtual int function() = 0; //각 실마다 기능 실행 함수 
};

int Room::Upgrade(int resource) {
	if (lv == 3) return 0;
	int UpgradeCost;

	if (lv == 0) UpgradeCost = 700;
	if (lv == 1) UpgradeCost = 900;
	else UpgradeCost = 1200;

	if (resource < UpgradeCost) return 1;
	else {
		if (resource - UpgradeCost <= 100) {
			cout << ">>경고! 정말로 업그레이드 하시겠습니까? (예 / 아니오)\n";
			cout << ">>업그레이드 시 남은 에너지 자원: " << (resource - UpgradeCost) << "\n입력: ";
			string n;
			cin >> n;
			if (n == "예") return UpgradeCost;
			else if (n == "아니오") return 1;
			else {
				cout << ">>잘못 입력했습니다. 업그레이드가 취소됩니다.";
				return 1;
			}
		}
		else return UpgradeCost;
	}
}

class ResourceRoom : public Room {
public:
	ResourceRoom() { lv = 1; name = "자원실"; }
	virtual int function() {
		if (lv == 1) return 170;
		else if (lv == 2) return 210;
		else return 240;
	}
};

class ScienceRoom : public Room {
public:
	ScienceRoom() { name = "실험실"; }
	virtual int function() {
		if (lv == 0) return 0;
		else if (lv == 1) return 1;
		else if (lv == 2) return 2;
		else return 3;
	}
};

class EngineRoom : public Room {
public:
	EngineRoom() { name = "엔진실"; }
	virtual int function() { //반환하는 값 %단위임!!!! 
		if (lv == 0) return 0;
		else if (lv == 1) return 10;
		else if (lv == 2) return 20;
		else return 30;
	}
};

class MedicalRoom : public Room {
public:
	MedicalRoom() { name = "의료실"; }
	virtual int function() {
		if (lv == 0) return 0;
		else if (lv == 1) return 3;
		else if (lv == 2) return 5;
		else return 7;
	}
};

class DefenseRoom : public Room {
public:
	DefenseRoom() { name = "장비실"; }
	virtual int function() { //반환하는 값 %단위임!!!! 
		if (lv == 0) return 0;
		else if (lv == 1) return 5;
		else if (lv == 2) return 8;
		else return 12;
	}
};

class Person {
	int MAXhp, MAXfull, MAXmental; //각자의 최대 스텟값 
	int hp, full, mental; //현재 스텟값. 체력, 배부름, 멘탈. 사망 시 전부 0 저장 
	int talk; //대화했는지 안했는지 플래그 용. 
	int ABnDIS, SELnVIO, S_DEAD;
	string job; //직업 이름 
public:
	//체력 조절, 공복 조절,  
	Person(int h, int f, int m, string j, int t, int A, int S, int D) {
		MAXhp = h; MAXfull = f; MAXmental = m;
		hp = h; full = f + 5; mental = m; job = j;
		talk = t;
		ABnDIS = A; SELnVIO = S; S_DEAD = D;
	}
	//int& operator +=(int n); //탐사원 스탯 조절 오퍼레이터 
	void HpControl(int h) { hp += h; } //체력 상승 또는 하락 
	void FullControl(int f) { full += f; } //공복 상승 또는 하락 
	void MentalControl(int m) { mental += m; } //멘탈 상승 또는 하락
	void SetTalkFlag(int flag) { talk = flag; }
	int ShowMaxState(int n) { //1 입력 시 MAXhp, 2 입력 시 MAXfull, 3 입력 시 MAXmental 값 반환 
		if (n == 1) return MAXhp;
		else if (n == 2) return MAXfull;
		else if (n == 3) return MAXmental;
	}
	int ShowState(int n) { //1 입력 시 hp, 2 입력 시 full, 3 입력 시 mental 값 반환, 4면 talk. 
		if (n == 1) return hp;
		else if (n == 2) return full;
		else if (n == 3) return mental;
		else return talk;
	}
	int EventPercent(int e) { //0==폭언,파괴 발생확률, 1==자해,폭력 발생확률, 2==자살 발생확률 
		if (e == 0) return ABnDIS;
		else if (e == 1) return SELnVIO;
		else return S_DEAD;
	}
	string ShowJob() { return job; } //직업 이름 반환 
};

class SpaceShip {
	int day, energy, food, exploredPlanet, cp[3], alive; //cp는 srand()를 위한 시드값을 저장해놓는 배열 
	//string state; //결정, 이동, 도착 
	Person* p[4]; //탐사원 정보 저장. 순서대로 생태학자, 엔지니어, 의사, 군인 
	Room* r[5]; //기체 구역 저장. 순서대로 자원실, 실험실, 엔진실, 의료실, 장비실 
	vector<Planet> planetList; //index 0에 선택한 행성 들어감 
	vector<Planet>::iterator it;
public:
	SpaceShip();
	~SpaceShip();
	int alive_person();
	void PrintInformation(); //"현재 정보" 입력 시 출력되는 정보 
	void Game(); //게임 진행하는 함수(while문 돌림) 
	int StartDay(); //자원 부족 엔딩 검사, 배고픔 줄어들고 체력 회복 
	void UpgradeRoom(); //기체 구역 업그레이드 
	void Feed(); //식량 분배 
	int choosePlanet(); //행성 생성 및 결정 
	int ExploreMember1, ExploreMember2, ExploreMember3, ExploreMember4;  //행성 도착 후의 함수들
	void DecideToExplore();
	void YesToExplore();
	void NoToExplore();
	void EventProbability();
	void GoodEvent();
	void BadEvent();
	void day_talk(); //행성 선택 후 상담하는 날들~ 
	void scientist_script();
	void engineer_script();
	void doctor_script();
	void army_script();
	void abuse_distroy_panic_event(int i);
	void violence_selfinjury_panic_event(int i);
	void suicide_panic_event(int i);
	void PrintEnding(int e); //1: 자원 부족 엔딩,  2: all 사망 엔딩, 3: 신 지구 도착 엔딩 
	void StartUI();
	void PlanetUI1();
	void PlanetUI2();
};

SpaceShip::SpaceShip() {
	p[0] = new Person(80, 100, 80, "생태학자", 0, 15, 40, 50);
	p[1] = new Person(90, 90, 80, "엔지니어", 0, 18, 60, 40);
	p[2] = new Person(80, 80, 100, "의사", 0, 15, 30, 30);
	p[3] = new Person(100, 60, 100, "군인", 0, 13, 70, 40);
	r[0] = new ResourceRoom();
	r[1] = new ScienceRoom();
	r[2] = new EngineRoom();
	r[3] = new MedicalRoom();
	r[4] = new DefenseRoom();
	day = 1;
	energy = 3000;
	food = 300;
	exploredPlanet = 0;
	ExploreMember1 = 0;
	ExploreMember2 = 0;
	ExploreMember3 = 0;
	ExploreMember4 = 0;
}

int SpaceShip::alive_person() {
	int alive_count=0;
	for (int i = 0; i < 4; i++) {
		if (p[i]->ShowState(1) > 0) {
			alive_count++;
		}
	}
	return alive_count;
}

SpaceShip :: ~SpaceShip() {
	delete p[0];
	delete p[1];
	delete p[2];
	delete p[3];
	delete r[0];
	delete r[1];
	delete r[2];
	delete r[3];
	delete r[4];
}

int SpaceShip::StartDay() {
	if (day != 1) energy += r[0]->function();
	if (energy <= 0) return  1; //자원 부족 엔딩 

	for (int i = 0; i < 4; i++) { //배부름 감소, hp 회복 
		if (p[i]->ShowState(2) == 0) continue;

		p[i]->FullControl(-5);
		if (p[i]->ShowState(2) <= 0) { //배고픔 0 이하 아사 
		   //정금주 | 아사 이벤트 출력 
			cout << ">>" << p[i]->ShowJob() << "은(는) 아사했습니다. 더욱 각별한 주의가 필요합니다." << endl;
			for (int j = 0; j < 4; j++) {
				p[j]->MentalControl(-10);
			}
			p[i]->HpControl(-p[i]->ShowState(1));//사망 처리 
			p[i]->FullControl(-p[i]->ShowState(2));
			p[i]->MentalControl(-p[i]->ShowState(3));
			continue;
		}
		p[i]->HpControl(r[3]->function());
		if (p[i]->ShowState(1) > p[i]->ShowMaxState(1)) p[i]->HpControl(-(p[i]->ShowState(1) - p[i]->ShowMaxState(1)));
	}
	//남아있는 사람이 모두 아사했을 경우 
	if (p[0]->ShowState(2) == 0 && p[1]->ShowState(2) == 0 && p[2]->ShowState(2) == 0 && p[3]->ShowState(2) == 0) return 2; //all 사망 엔딩 
	return 0;
}

void SpaceShip::UpgradeRoom() {
	string n;
	int rnum, result, ug;
	while (1) {
		system("cls");
		//UI 출력 
		cout << ">>각 기체 구역 현재 레벨\n";
		for (int i = 0; i < 5; i++) cout << "  " << r[i]->ShowName() << ": " << r[i]->ShowLv() << "Lv\n";
		cout << ">>현재 보유 에너지 자원: " << energy << "\n\n";
		cout << ">>업그레이드를 원하는 기체 구역 이름을 입력해주세요.\n";
		cout << ">>업그레이드를 끝내려면 '끝'을 입력해주세요.\n>>";
		cin >> n;

		if (n == "끝") break;
		else if (n == "자원실") rnum = 0;
		else if (n == "실험실") rnum = 1;
		else if (n == "엔진실") rnum = 2;
		else if (n == "의료실") rnum = 3;
		else if (n == "장비실") rnum = 4;
		else {
			cout << "\n>>다시 입력해 주세요.";
			_getch();
			continue;
		}

		if (r[rnum]->ShowLv() == 0) ug = 700;
		else if (r[rnum]->ShowLv() == 1) ug = 900;
		else ug = 1200;

		cout << "\n>>" << r[rnum]->ShowName() << "이 맞습니까? (예 / 아니오)\n";
		cout << ">>업그레이드에 필요한 에너지 자원: " << ug << "\n";
		cout << ">>현재 보유 에너지 자원: " << energy << "\n>>";
		cin >> n;

		if (n == "예") {
			result = r[rnum]->Upgrade(energy);

			if (result == 0) {
				cout << "\n>>해당 기체 구역은 이미 최대 레벨입니다.";
			}
			else if (result == 1) {
				cout << "\n>>에너지가 부족해 업그레이드에 실패했습니다.\n";
				cout << ">>업그레이드에 필요한 에너지 자원: " << ug << endl;
				cout << ">>현재 보유 에너지 자원: " << energy;
			}
			else {
				energy -= result;
				cout << "\n>>" << r[rnum]->ShowName() << " 업그레이드가 완료 되었습니다.\n";
				cout << ">>남은 에너지 자원: " << energy;
				r[rnum]->lvUp();
			}
			_getch();
		}
		else if (n == "아니오");
		else {
			cout << ">>잘못 입력했습니다. 업그레이드가 취소됩니다.";
			_getch();
		}
	}
}

void SpaceShip::Feed() {
	string name;
	int person, amount;
	while (1) {
		system("cls");
		//UI 출력 
		cout << ">>각 탐사원 현재 배부름 수치\n";
		for (int i = 0; i < 4; i++) {
			if (p[i]->ShowState(1) == 0) cout << "  " << p[i]->ShowJob() << " | 현재 사망\n";
			else cout << "  " << p[i]->ShowJob() << " | 배부름 수치: " << p[i]->ShowState(2) << "/" << p[i]->ShowMaxState(2) << "\n";
		}
		cout << ">>현재 보유 음식량: " << food << "\n\n";
		cout << ">>음식을 배급할 탐사원 이름을 입력해주세요.\n";
		cout << ">>음식 배급을 끝내려면 '끝'을 입력해주세요.\n>>";
		cin >> name;

		if (name == "끝") break;
		else if (name == "생태학자") person = 0;
		else if (name == "엔지니어") person = 1;
		else if (name == "의사") person = 2;
		else if (name == "군인") person = 3;
		else {
			cout << "\n>>다시 입력해 주세요.";
			_getch();
			continue;
		}

		cout << ">>음식을 얼마나 배급할까요?\n입력: ";
		cin >> amount;

		if (amount > food) {
			cout << ">>현재 보유하고 있는 음식량을 넘어섰습니다. 다시 입력해주세요.";
			_getch();
			continue;
		}
		else if (p[person]->ShowState(2) + amount > p[person]->ShowMaxState(2)) {
			cout << "\n>>해당 탐사자의 최대 배부름 수치를 넘는 양을 배급했기에 남는 음식을 반환했습니다.\n";
			amount = p[person]->ShowMaxState(2) - p[person]->ShowState(2);
		}
		cout << ">>음식을 " << amount << " 만큼 배급했습니다.";
		food -= amount;
		p[person]->FullControl(amount);
		_getch();
	}
}

int SpaceShip::choosePlanet() {
	if (day != 1) it = planetList.erase(it);
	Planet p1(cp[0]), p2(cp[1]), p3(cp[2]);
	planetList.push_back(p1);
	planetList.push_back(p2);
	planetList.push_back(p3);

	int sLv;
	string n;
	sLv = r[1]->function();

	while (1) {
		system("cls");
		it = planetList.begin();

		for (int i = 0; i < 3; i++) {
			gotoxy(1 + i * 45, 0);
			if (i == 0) cout << "행성 A";
			else if (i == 1) cout << "행성 B";
			else  cout << "행성 C";
			gotoxy(1 + i * 45, 1);
			cout << "해당 행성까지 이동하는데 걸리는 일 수: " << it->ShowIntState(1);
			gotoxy(1 + i * 45, 2);
			cout << "행성 타입: " << it->ShowStringState(1) << " 행성";
			gotoxy(1 + i * 45, 3);
			cout << "탐사 난이도: " << it->ShowStringState(2);
			gotoxy(1 + i * 45, 4);
			if (sLv >= 1) {
				cout << "생명체 유무: ";
				if (it->ShowIntState(5) == 1) cout << "O";
				else  cout << "X";
			}
			else cout << "해당 정보 열람 조건: 실험실 레벨 1";
			gotoxy(1 + i * 45, 5);
			if (sLv >= 2) cout << "생명체 성향: " << it->ShowStringState(3);
			else cout << "해당 정보 열람 조건: 실험실 레벨 2";
			gotoxy(1 + i * 45, 6);
			if (sLv >= 3) cout << "획득 가능 자원량 | 에너지: " << it->ShowStringState(3) << " 음식: " << it->ShowStringState(4);
			else cout << "해당 정보 열람 조건: 실험실 레벨 3";
			gotoxy(1 + i * 45, 8);
			cout << "이동하는 데 소모되는 에너지: " << it->ShowIntState(2);
			it++;
		}
		gotoxy(1, 11);
		cout << ">>현재 보유 자원 | 에너지: " << energy << " 음식: " << food << endl;
		cout << ">>탐사하고자 하는 행성 이름을 입력해주세요.\n";
		cout << ">>탐사하고 싶은 행성이 없다면 'N'를 입력해주세요. 내일로 넘어갑니다.\n>>";
		cin >> n;
		if (!(n == "A" || n == "B" || n == "C" || n == "N")) {
			cout << ">>다시 입력해 주세요.";
			_getch();
			continue;
		}
		else if (n == "N") {
			cout << ">>탐사할 행성을 고르지 않았습니다. 내일로 넘어갑니다.";
			it = planetList.begin();
			it = planetList.erase(it);
			it = planetList.erase(it);
			_getch();
			return 0; //탐사 안 하는 경우 
		}
		else {
			if ((n == "A" && planetList[0].ShowStringState(1) == "가스") || (n == "B" && planetList[1].ShowStringState(1) == "가스") || (n == "C" && planetList[2].ShowStringState(1) == "가스")) {
				cout << ">>해당 행성은 탐사가 불가능한 가스 행성입니다. 다시 선택해주세요.\n";
				_getch();
				continue;
			}
			cout << ">>행성 " << n << "를 목적지로 이동합니다.\n";
			//벡터에 선택한 행성만 남기고 다른 행성들 다 지움
			//planetList[0]에 선택한 행성 존재 
			//이터레이터 it도 planetList[0]을 가리키게 해놨으니까 탐사할 행성 변수에 접근할 때 planetList[0], it 둘 중 하나로 접근해도 무방 
			if (n == "A") {
				it = planetList.begin();
				it++;
				it = planetList.erase(it);
				it = planetList.erase(it);
				it = planetList.begin();
			}
			else if (n == "B") {
				it = planetList.begin();
				it = planetList.erase(it);
				it++;
				it = planetList.erase(it);
				it = planetList.begin();
			}
			else {
				it = planetList.begin();
				it = planetList.erase(it);
				it = planetList.erase(it);
			}
			cout << ">>이동을 위해 에너지 자원 " << it->ShowIntState(2) << " 만큼 소모했습니다.\n";
			energy -= it->ShowIntState(2);
			cout << ">>현재 보유 에너지: " << energy;
			_getch();
			return 1; //탐사 하는 경우   
		}
	}
}

//추가
void SpaceShip::DecideToExplore() {//행성 도착 후 탐사 할지 말지 정하기
	system("cls");
	int DecideToExplore;
	string WantToStop;
	srand(time(NULL));
	if (rand() % 2 == 0) PlanetUI1();
	else PlanetUI2(); 
	cout << ">>행성에 도착했습니다. 이 행성을 탐사하시겠습니까?\n";
	cout << "  1. YES       2. NO\n>>";
	while (1) {
		cin >> DecideToExplore;
		if (DecideToExplore == 1) {
			YesToExplore();
			_getch();
			for (int k = 0; k < 3; k++) {
				if (k == 2) {
					EventProbability(); //탐사 중 랜덤이벤트 발생
					_getch();
					system("cls");
					cout << ">>이제 이 행성에 대한 정보는 어느정도 알게 된 것 같습니다.\n>>이젠 다른 행성으로 떠나야 할 시간입니다.\n>>탐사선으로 복귀합니다.\n ";
					explore = 0;
					_getch();
				}
				else {
					EventProbability(); //탐사 중 랜덤이벤트 발생
					_getch();
					system("cls");
					cout << ">>현재 행성 탐사를 멈추고 이륙하시겠습니까?(예/아니오)\n>>";
					cin >> WantToStop;
					if (WantToStop == "예")
					{
						cout << ">>탐사를 멈추고 탐사선으로 복귀합니다.\n";
						explore = 0;
						_getch();
						break;
					}
					else if (!((WantToStop == "예") || (WantToStop == "아니오"))) {
						cout << ">>다시 입력해 주세요.\n>>";
						_getch();
						continue;
					}
				}

			}
			break;
		}
		else if (DecideToExplore == 2) {
			NoToExplore();
			_getch();
			break;
		}
		else {
			cout << ">>다시 입력해주세요\n>>";
			_getch();
			continue;
		}
	}
}
void SpaceShip::YesToExplore() {     //탐사 보낼 대원 선택하기
	system("cls");
	int n;
	cout << ">>탐사를 보낼 대원을 선택하세요.\n";
	while (1) {
		if (p[0]->ShowState(1) > 0) {
			cout << ">>생태학자를 탐사에 보내시겠습니까?\n";
			cout << "  1. 예    2. 아니오\n>>";
			cin >> n;
			if (n == 1) {
				cout << "\n생태학자를 선택하셨습니다.\n";
				ExploreMember1 = 1;
				_getch();
				break;
			}
			else if (n == 2) {
				cout << "\n생태학자를 보내지 않습니다.\n";
				ExploreMember1 = 0;
				_getch();
				break;
			}
			else {
				cout << ">>다시 입력해주세요\n>>";
				_getch();
				continue;
			}
		}
		else {
			cout << ">>생태학자 사망";
			_getch();
			break;
		}
	}
	system("cls");
	cout << ">>탐사를 보낼 대원을 선택하세요.\n";
	while (1) {
		if (p[1]->ShowState(1) > 0) {
			cout << ">>엔지니어를 탐사에 보내시겠습니까?\n";
			cout << "  1. 예    2. 아니오\n>>";
			cin >> n;
			if (n == 1) {
				cout << "\n엔지니어를 선택하셨습니다.\n";
				ExploreMember2 = 1;
				_getch();
				break;
			}
			else if (n == 2) {
				cout << "\n엔지니어를 보내지 않습니다.\n";
				ExploreMember2 = 0;
				_getch();
				break;
			}
			else {
				cout << ">>다시 입력해주세요\n>>";
				_getch();
				continue;
			}
		}
		else {
			cout << ">>엔지니어 사망";
			_getch();
			break;
		}
	}
	system("cls");
	cout << ">>탐사를 보낼 대원을 선택하세요.\n";
	while (1) {
		if (p[2]->ShowState(1) > 0) {
			cout << ">>의사를 탐사에 보내시겠습니까?\n";
			cout << "  1. 예    2. 아니오\n>>";
			cin >> n;
			if (n == 1) {
				cout << "\n의사를 선택하셨습니다.\n";
				ExploreMember3 = 1;
				_getch();
				break;
			}
			else if (n == 2) {
				cout << "\n의사를 보내지 않습니다.\n";
				ExploreMember3 = 0;
				_getch();
				break;
			}
			else {
				cout << ">>다시 입력해주세요\n>>";
				_getch();
				continue;
			}
		}
		else {
			cout << ">>의사 사망";
			_getch();
			break;
		}
	}
	system("cls");
	cout << ">>탐사를 보낼 대원을 선택하세요.\n";
	while (1) {
		if (p[3]->ShowState(1) > 0) {
			cout << ">>군인을 탐사에 보내시겠습니까?\n";
			cout << "1. 예    2. 아니오\n>>";
			cin >> n;
			if (n == 1) {
				cout << "군인을 선택하셨습니다.\n";
				ExploreMember4 = 1;
				_getch();
				break;
			}
			else if (n == 2) {
				cout << "\n군인을 보내지 않습니다.\n";
				ExploreMember4 = 0;
				_getch();
				break;
			}
			else {
				cout << ">>다시 입력해주세요\n>>";
				_getch();
				continue;
			}
		}
		else {
			cout << ">>군인 사망";
			_getch();
			break;
		}
	}
	system("cls");
	cout << "행성으로 탐사를 보낼 구성원 : ";
	if (ExploreMember1 == 1) cout << "생태학자 ";
	if (ExploreMember2 == 1) cout << "엔지니어 ";
	if (ExploreMember3 == 1) cout << "의사 ";
	if (ExploreMember4 == 1) cout << "군인 ";
}
void SpaceShip::NoToExplore() {
	system("cls");
	cout << ">>행성 탐사를 멈추고 이륙하겠습니다...\n";
}
void SpaceShip::EventProbability() {   // 1/2 확률로 good 또는bad 이벤트 발생
	system("cls");
	srand((unsigned int)time(NULL));
	if (rand() % 2 == 0) {
		GoodEvent();
	}
	else {
		BadEvent();
	}
}
void SpaceShip::GoodEvent() {
	cout << ">>...왠지 좋은 일이 생길 것만 같다!\n";
	srand(time(NULL));
	if (rand() % 2 == 0) {
		srand(time(NULL));
		int plus_hp, plus_mental;
		plus_hp = rand() % 10;
		plus_mental = rand() % 10;
		cout << ">>테라피 이벤트 발생!!\n";
		cout << ">>탐사원 모두 체력 " << plus_hp << ", 정신력 " << plus_mental << "을(를) 얻었습니다.\n";
		if (ExploreMember1 == 1) {
			p[0]->HpControl(+plus_hp);  //체력
			if (p[0]->ShowState(1) > p[0]->ShowMaxState(1))
			{
				p[0]->HpControl(-(p[0]->ShowState(1) - p[0]->ShowMaxState(1)));
			}
			p[0]->MentalControl(+plus_mental);  //멘탈
			if (p[0]->ShowState(3) > p[0]->ShowMaxState(3))
			{
				p[0]->MentalControl(-(p[0]->ShowState(3) - p[0]->ShowMaxState(3)));
			}
		}
		if (ExploreMember2 == 1) {
			p[1]->HpControl(+plus_hp);  //체력
			if (p[1]->ShowState(1) > p[1]->ShowMaxState(1))
			{
				p[1]->HpControl(-(p[1]->ShowState(1) - p[1]->ShowMaxState(1)));
			}
			p[1]->MentalControl(+plus_mental);  //멘탈
			if (p[1]->ShowState(3) > p[1]->ShowMaxState(3))
			{
				p[1]->MentalControl(-(p[1]->ShowState(3) - p[1]->ShowMaxState(3)));
			}
		}
		if (ExploreMember3 == 1) {
			p[2]->HpControl(+plus_hp);  //체력
			if (p[2]->ShowState(1) > p[2]->ShowMaxState(1))
			{
				p[2]->HpControl(-(p[2]->ShowState(1) - p[2]->ShowMaxState(1)));
			}
			p[2]->MentalControl(+plus_mental);  //멘탈
			if (p[2]->ShowState(3) > p[2]->ShowMaxState(3))
			{
				p[2]->MentalControl(-(p[2]->ShowState(3) - p[2]->ShowMaxState(3)));
			}
		}
		if (ExploreMember4 == 1) {
			p[3]->HpControl(+plus_hp);  //체력
			if (p[3]->ShowState(1) > p[3]->ShowMaxState(1))
			{
				p[3]->HpControl(-(p[3]->ShowState(1) - p[3]->ShowMaxState(1)));
			}
			p[3]->MentalControl(+plus_mental);  //멘탈
			if (p[3]->ShowState(3) > p[3]->ShowMaxState(3))
			{
				p[3]->MentalControl(-(p[3]->ShowState(3) - p[3]->ShowMaxState(3)));
			}
		}
		_getch();
	}
	else {
		srand(time(NULL));
		int plus_food, plus_energy;
		plus_food = rand() % 10;
		plus_energy = rand() % 100;
		food += plus_food;
		energy += plus_energy;
		cout << ">>자원 풍족\n";
		cout << ">>음식 " << plus_food << ", 에너지" << plus_energy << "을(를) 얻었습니다.\n";
		_getch();
	}
}
void SpaceShip::BadEvent() {
	cout << ">>...왠지 불길하다... 금방이라도 무슨 일이 벌어질 것만 같다...\n";
	int minus_hp, minus_full, minus_mental;
	srand(time(NULL));
	if (rand() % 3 == 0) {
		srand(time(NULL));
		minus_hp = rand() % 10;
		minus_full = rand() % 10;
		minus_mental = rand() % 10;
		cout << ">>중독 이벤트 발생!!\n";
		cout << ">>탐사원 모두 체력 " << minus_hp << ", 배부름 " << minus_full << ", 정신력 " << minus_mental << "을(를) 잃었습니다.\n";
		if (ExploreMember1 == 1) {
			p[0]->HpControl(-minus_hp);      //체력
			p[0]->FullControl(-minus_full);    //공복
			p[0]->MentalControl(-minus_mental);  //멘탈
		}
		if (ExploreMember2 == 1) {
			p[1]->HpControl(-minus_hp);      //체력
			p[1]->FullControl(-minus_full);    //공복
			p[1]->MentalControl(-minus_mental);  //멘탈
		}
		if (ExploreMember3 == 1) {
			p[2]->HpControl(-minus_hp);      //체력
			p[2]->FullControl(-minus_full);    //공복
			p[2]->MentalControl(-minus_mental);  //멘탈
		}
		if (ExploreMember4 == 1) {
			p[3]->HpControl(-minus_hp);      //체력
			p[3]->FullControl(-minus_full);    //공복
			p[3]->MentalControl(-minus_mental);  //멘탈
		}
		_getch();
	}
	else if (rand() % 3 == 1) {
		srand(time(NULL));
		minus_hp = rand() % 10;
		minus_mental = rand() % 10;
		cout << ">>공격 이벤트 발생!!\n";
		cout << ">>탐사원 모두 체력 " << minus_hp << ", 정신력 " << minus_mental << "을(를) 잃었습니다.\n";
		if (ExploreMember1 == 1) {
			p[0]->HpControl(-minus_hp);      //체력
			p[0]->MentalControl(-minus_mental);  //멘탈
		}
		if (ExploreMember2 == 1) {
			p[1]->HpControl(-minus_hp);      //체력
			p[1]->MentalControl(-minus_mental);  //멘탈
		}
		if (ExploreMember3 == 1) {
			p[2]->HpControl(-minus_hp);      //체력
			p[2]->MentalControl(-minus_mental);  //멘탈
		}
		if (ExploreMember4 == 1) {
			p[3]->HpControl(-minus_hp);      //체력
			p[3]->MentalControl(-minus_mental);  //멘탈
		}
		_getch();
	}
	else {
		srand(time(NULL));
		minus_hp = rand() % 10 + 5;
		minus_full = rand() % 10;
		minus_mental = rand() % 10 + 2;
		cout << ">>재해 이벤트 발생!!\n";
		cout << ">>탐사원 모두 체력 " << minus_hp << ", 배부름 " << minus_full << ", 정신력 " << minus_mental << "을(를) 잃었습니다.\n";
		if (ExploreMember1 == 1) {
			p[0]->HpControl(-minus_hp);      //체력
			p[0]->FullControl(-minus_full);    //공복
			p[0]->MentalControl(-minus_mental);  //멘탈
		}
		if (ExploreMember2 == 1) {
			p[1]->HpControl(-minus_hp);      //체력
			p[1]->FullControl(-minus_full);    //공복
			p[1]->MentalControl(-minus_mental);  //멘탈
		}
		if (ExploreMember3 == 1) {
			p[2]->HpControl(-minus_hp);      //체력
			p[2]->FullControl(-minus_full);    //공복
			p[2]->MentalControl(-minus_mental);  //멘탈
		}
		if (ExploreMember4 == 1) {
			p[3]->HpControl(-minus_hp);      //체력
			p[3]->FullControl(-minus_full);    //공복
			p[3]->MentalControl(-minus_mental);  //멘탈
		}
		_getch();
	}
}
//추가완


void abuse_distroy_script() {
	system("cls");
	printf("  자원이 한정된 이상, 모두가 공평하긴 어려워요.\n");
	printf("  이러한 사실을 알고 있고, 이해하지만, 받아들이기는 힘드네요.\n");
	printf("  계획이 있기에 당신은 그런 선택을 한거겠죠?\n");
	_getch();
}

void violence_selfinjury_script() {
	//자해는 스크립트 없읍니다~.
	//hp만 깍임. 
}

void suicide_script() {
	system("cls");
	printf("  최근들어 잠에 들기 힘들어요.\n");
	printf("  냉동수면의 여파일지도 모르죠.\n");
	printf("  너무 오래 잠들어있어서 그런걸까요? \n");
	printf("  …\n");
	printf("  잠은 죽음의 예행연습이라는 말도 있죠.\n\n\n");
	printf("  쪽지가 끝나있다.\n");
	printf("  방에는 잠든 탐사원이 누워있다.\n");
	_getch();
}

void scientist_script1() {//대사1 
	system("cls");
	printf(">>캡틴, 이 어두운 우주 공간에서 빛이 거의 없는 것 같아요.\n  매일매일 우리는 희망을 찾기 위해 헤메고 있지만, 끝이 어디인지 알 수 없는 이 무한한 우주는 정말로 우울하기만 해요.\n");
	printf("  우리는 자원 수급 장치를 잃었고, 어떻게든 살아남기 위해 투쟁하고 있지만, 이것이 얼마나 더 이어질지 모르잖아요.\n  불확실성과 두려움에 휩싸인 채, 삶의 의미를 찾기가 참으로 어렵네요.\n");
	printf("  우리 각자가 선택하는 길마다 어떤 상실과 희생이 따라오고, 그래도 우리는 앞으로 나아가야만 해요.\n  이 어두운 우주에서 혼자가 아닌 것은 위로가 되지만, 동시에 우리의 무력함과 취약함을 더욱 통감하게 만들어요.\n");
	printf("  이 모든 고통과 상실 속에서, 우리는 어떻게 강하게 남을 수 있을까요?\n  이것이 끝이라면, 우리는 최후의 순간까지 서로를 위로하고 지지할 수 있을까요?\n  이 어두운 여정에서 우리가 무엇을 얻을 수 있을지 모르겠지만, 최소한 서로에게 힘이 되어 줄 수 있을까요?\n\n");
	Sleep(2000);
	printf("1. 의지를 가져야 해. 여기서 더 이상 우울해하지 말고, 우리가 겪고 있는 어려움에 더 강해져야 해.\n   모두가 힘들어하지만, 우리는 함께 버티고 있어.\n   내일이 더 나아질지는 모르겠지만, 우리가 힘을 합치면 어떤 상황에서도 이겨낼 수 있어.\n");
	printf("2. 어둠과 어려움이 우리를 향해 닥치고 있지만, 우리는 함께 이 어두운 우주에서 빛을 찾아 나갈 거야.\n   모두가 고통을 겪고 있지만, 그 속에서 뭔가를 얻을 수 있을 거야.\n   우리는 희망을 가져야 해. 함께라면 우리는 무엇이든 이겨낼 수 있어.\n");
}

void scientist_script2() {//대사2 
	system("cls");
	printf(">>캡틴, 말씀드리기 전에 먼저 말하고 싶은 게 있습니다. 이건 참고만 하세요. 혹시나 모르니까요.\n");
	printf("  캡틴, 이 여정은 정말로 절망적이죠. 자원 수급 장치를 잃고, 우리는 불균형과 불확실성의 속에서 살아가고 있습니다.\n  각자가 어디에 에너지를 투입할지, 어떤 선택을 할지 모르는 상태에서 살아가는 건 참으로 힘들어요.\n");
	printf("  우리는 이미 많은 것을 잃었고, 앞으로 얼마나 버틸 수 있을지도 불투명합니다.\n  자원이 부족하고 상황은 악화되고 있어, 이 모든 것이 우리에게 무리한 부담을 주고 있습니다.\n");
	printf("  더구나, 이런 암울한 환경에서는 상처와 스트레스가 더 높아집니다.\n  중노동과 자원의 불균형은 우리의 정신적, 심리적 건강을 악화시킬 수 있어요.\n  캡틴, 우리는 이미 한계에 다다랐고, 이 상황이 더 이상 지속되기 힘들어질 것 같습니다.\n");
	printf("  혹시 이런 상황에서 어떻게 진행될지, 어떻게 버틸지에 대한 계획이 있나요?\n  혹시나 우리의 생존 가능성에 대한 비관적인 전망을 어떻게 다룰지 생각해보셨다면, 제게 말씀해 주세요.\n\n");
	Sleep(2000);
	printf("1. 좋은 질문이야. 현재 상황은 힘들긴 하지만, 우리는 언제나 새로운 가능성을 찾아 나가는 것이 중요해.\n   우리가 이런 어려운 상황에서도 함께 협력하고 지지해주면서 서로에게 힘이 되어줄 수 있다면, 어떤 어려움도 극복할 수 있을 거야.\n   더 나아가, 우리가 이런 상황에서 얻을 수 있는 것들도 생각해보면 좋을 것 같아.\n   지금은 힘들겠지만, 우리가 이 어둠 속에서 빛을 찾아낼 수 있을 거라 믿어.\n");
	printf("2. 맞아. 현실은 어려운 선택과 희생이 따르고 있어.\n   하지만 우리는 아직 여러 가능성을 가지고 있고, 절망에 빠지지 않고 단결하여 어떤 일이든 해낼 수 있을 거야.\n   모두가 어두운 상황에서 빛을 찾는 데에 기여하면서 서로를 지지해주면, 예상치 못한 변화와 희망도 찾을 수 있을 거야.\n   우리가 함께 있다면, 이 어둠 속에서도 서로에게 희망의 불씨를 계속 전해갈 수 있을 거야.\n");
}

void engineer1_script1() {//대사1 
	system("cls");
	printf(">>캡틴, 이 여정은 정말로 절망적이에요. 자원 수급 장치를 잃었어요.\n  그리고 우리는 불균형과 불확실성 속에서 살아가고 있어요.\n");
	printf("  매일 더 많은 에너지가 필요하고, 그 에너지를 효율적으로 사용하는 방법은 찾기 어려워요.\n");
	printf("  우리는 이미 피곤하고, 지친 상태입니다. 이런 고통 속에서 빠져나가기가 어렵다는 걸 느껴요.\n");
	printf("  자원을 나누는 게 항상 공정하지 않게 느껴져서 희망조차 찾기 힘듭니다.\n");
	printf("  우리는 더 이상 언제까지 이런 상황에서 버틸 수 있을까요? 모든 게 너무 힘듭니다.\n");
	printf("  정말 어두운 우주 속에서 헤매고 있는 느낌이에요...\n\n");
	Sleep(2000);
	printf("1. 우주의 어두운 면을 느끼고 있구나. 이 여정은 힘들지만, 우리는 이미 많은 어려움을 극복해왔어.\n   모든 것이 어려울 때에야 우리의 진정한 강함이 드러나는 법이지. 함께 버티면 더 강해질 수 있어.\n");
	printf("2. 네 말이 맞아. 이 여정은 정말 어둡고 힘들어. 하지만 우리는 이미 여러 도전을 이겨냈고,\n   우리의 인내와 협력으로 어떤 어려움이라도 극복할 수 있을 거야. 함께 힘을 모으면 더 나아질 수 있어.\n");
}

void engineer1_script2() {//대사2 
	system("cls");
	printf(">>캡틴, 이게 다 내 잘못이에요. 자원 수급 장치를 잃었을 때 더 신중해져야 했어요.\n");
	printf("  이제서야 후회되지만, 그때 어떻게 했어야 했는지 생각하면 정말 후련하지 않아요.\n\n");
	Sleep(2000); 
	printf("1. 우리는 이미 어려운 상황에 처해있어. 네 잘못이 아닌 우리 모두의 문제야.\n   자책하지 말고 함께 해결책을 찾아보자.\n");
	printf("2. 너무 자책하지 마. 이 여정은 모두가 예측할 수 없는 것이었어.\n   이제서야 뒤돌아보는 것보다 앞으로 어떻게 진행될지 생각해보자.\n");
}

void doctor_script1() {//대사1 
	system("cls");
	printf(">>캡틴, 이 여정은 정말로 절망적이에요. 자원 수급 장치를 잃었어요.\n  그리고 우리는 불균형과 불확실성 속에서 살아가고 있어요.\n");
	printf("  매일 더 많은 에너지가 필요하고, 그 에너지를 효율적으로 사용하는 방법은 찾기 어려워요.\n");
	printf("  우리는 이미 피곤하고, 지친 상태입니다. 이런 고통 속에서 빠져나가기가 어렵다는 걸 느껴요.\n");
	printf("  자원을 나누는 게 항상 공정하지 않게 느껴져서 희망조차 찾기 힘듭니다.\n");
	printf("  우리는 더 이상 언제까지 이런 상황에서 버틸 수 있을까요? 모든 게 너무 힘듭니다.\n");
	printf("  정말 어두운 우주 속에서 헤매고 있는 느낌이에요...\n\n");
	Sleep(2000);
	printf("1. 우주의 어두운 면을 느끼고 있구나. 이 여정은 힘들지만, 우리는 이미 많은 어려움을 극복해왔어.\n   모든 것이 어려울 때에야 우리의 진정한 강함이 드러나는 법이지. 함께 버티면 더 강해질 수 있어.\n");
	printf("2. 네 말이 맞아. 이 여정은 정말 어둡고 힘들어. 하지만 우리는 이미 여러 도전을 이겨냈고,\n   우리의 인내와 협력으로 어떤 어려움이라도 극복할 수 있을 거야. 함께 힘을 모으면 더 나아질 수 있어.\n");
}

void doctor_script2() {//대사2
	system("cls");
	printf(">>캡틴, 이 어두운 우주 공간에서 빛이 거의 없는 것 같아요.\n  매일매일 우리는 희망을 찾기 위해 헤메고 있지만, 끝이 어디인지 알 수 없는 이 무한한 우주는 정말로 우울하기만 해요.\n");
	printf("  우리는 자원 수급 장치를 잃었고, 어떻게든 살아남기 위해 투쟁하고 있지만, 이것이 얼마나 더 이어질지 모르잖아요.\n  불확실성과 두려움에 휩싸인 채, 삶의 의미를 찾기가 참으로 어렵네요.\n");
	printf("  우리 각자가 선택하는 길마다 어떤 상실과 희생이 따라오고, 그래도 우리는 앞으로 나아가야만 해요.\n  이 어두운 우주에서 혼자가 아닌 것은 위로가 되지만, 동시에 우리의 무력함과 취약함을 더욱 통감하게 만들어요.\n");
	printf("  이 모든 고통과 상실 속에서, 우리는 어떻게 강하게 남을 수 있을까요?\n  이것이 끝이라면, 우리는 최후의 순간까지 서로를 위로하고 지지할 수 있을까요?\n  이 어두운 여정에서 우리가 무엇을 얻을 수 있을지 모르겠지만, 최소한 서로에게 힘이 되어 줄 수 있을까요?\n\n");
	Sleep(2000);
	printf("1. 의지를 가져야 해. 여기서 더 이상 우울해하지 말고, 우리가 겪고 있는 어려움에 더 강해져야 해.\n   모두가 힘들어하지만, 우리는 함께 버티고 있어.\n   내일이 더 나아질지는 모르겠지만, 우리가 힘을 합치면 어떤 상황에서도 이겨낼 수 있어.\n");
	printf("2. 어둠과 어려움이 우리를 향해 닥치고 있지만, 우리는 함께 이 어두운 우주에서 빛을 찾아 나갈 거야.\n   모두가 고통을 겪고 있지만, 그 속에서 뭔가를 얻을 수 있을 거야.\n   우리는 희망을 가져야 해. 함께라면 우리는 무엇이든 이겨낼 수 있어.\n");
}

void army_script1() {//대사1 
	system("cls");
	printf(">>캡틴, 말씀드리기 전에 먼저 말하고 싶은 게 있습니다. 이건 참고만 하세요. 혹시나 모르니까요.\n");
	printf("  캡틴, 이 여정은 정말로 절망적이죠. 자원 수급 장치를 잃고, 우리는 불균형과 불확실성의 속에서 살아가고 있습니다.\n  각자가 어디에 에너지를 투입할지, 어떤 선택을 할지 모르는 상태에서 살아가는 건 참으로 힘들어요.\n");
	printf("  우리는 이미 많은 것을 잃었고, 앞으로 얼마나 버틸 수 있을지도 불투명합니다.\n  자원이 부족하고 상황은 악화되고 있어, 이 모든 것이 우리에게 무리한 부담을 주고 있습니다.\n");
	printf("  더구나, 이런 암울한 환경에서는 상처와 스트레스가 더 높아집니다.\n  중노동과 자원의 불균형은 우리의 정신적, 심리적 건강을 악화시킬 수 있어요.\n  캡틴, 우리는 이미 한계에 다다랐고, 이 상황이 더 이상 지속되기 힘들어질 것 같습니다.\n");
	printf("  혹시 이런 상황에서 어떻게 진행될지, 어떻게 버틸지에 대한 계획이 있나요?\n  혹시나 우리의 생존 가능성에 대한 비관적인 전망을 어떻게 다룰지 생각해보셨다면, 제게 말씀해 주세요.\n\n");
	Sleep(2000);
	printf("1. 좋은 질문이야. 현재 상황은 힘들긴 하지만, 우리는 언제나 새로운 가능성을 찾아 나가는 것이 중요해.\n   우리가 이런 어려운 상황에서도 함께 협력하고 지지해주면서 서로에게 힘이 되어줄 수 있다면, 어떤 어려움도 극복할 수 있을 거야.\n   더 나아가, 우리가 이런 상황에서 얻을 수 있는 것들도 생각해보면 좋을 것 같아.\n   지금은 힘들겠지만, 우리가 이 어둠 속에서 빛을 찾아낼 수 있을 거라 믿어.\n");
	printf("2. 맞아. 현실은 어려운 선택과 희생이 따르고 있어.\n   하지만 우리는 아직 여러 가능성을 가지고 있고, 절망에 빠지지 않고 단결하여 어떤 일이든 해낼 수 있을 거야.\n   모두가 어두운 상황에서 빛을 찾는 데에 기여하면서 서로를 지지해주면, 예상치 못한 변화와 희망도 찾을 수 있을 거야.\n   우리가 함께 있다면, 이 어둠 속에서도 서로에게 희망의 불씨를 계속 전해갈 수 있을 거야.\n");
}

void army_script2() {//대사2 
	system("cls");
	printf(">>캡틴, 이게 다 내 잘못이에요. 자원 수급 장치를 잃었을 때 더 신중해져야 했어요.\n");
	printf("  이제서야 후회되지만, 그때 어떻게 했어야 했는지 생각하면 정말 후련하지 않아요.\n\n");
	Sleep(2000);
	printf("1. 우리는 이미 어려운 상황에 처해있어. 네 잘못이 아닌 우리 모두의 문제야.\n   자책하지 말고 함께 해결책을 찾아보자.\n");
	printf("2. 너무 자책하지 마. 이 여정은 모두가 예측할 수 없는 것이었어.\n   이제서야 뒤돌아보는 것보다 앞으로 어떻게 진행될지 생각해보자.\n");
}

void SpaceShip::abuse_distroy_panic_event(int i) {//폭언 파괴 이벤트 스크립트 함 수 
	int random;
	srand(time(NULL));
	random = rand() % 100;

	if (p[i]->ShowState(3) < 40) {//멘탈이 40이하면 
		if (random >= 0 && random < p[i]->EventPercent(0)) {
			abuse_distroy_script();//?%로 해당 이벤트 발생. 
			p[i]->HpControl(-3);
		}

	}
}

void SpaceShip::violence_selfinjury_panic_event(int i) {//자해, 폭력 이벤트 스크립트 함수 
	int random;
	srand(time(NULL));
	random = rand() % 100;

	if (p[i]->ShowState(3) < 20) {//멘탈이 20이하면  
		if (random >= 0 && random < p[i]->EventPercent(0)) {
			violence_selfinjury_script();//?%로 해당 이벤트 발생. 
			p[i]->HpControl(-10);
		}
	}
}

void SpaceShip::suicide_panic_event(int i) {//자살 이벤트 스크립트 함수 
	int random;
	srand(time(NULL));
	random = rand() % 100;

	if (p[i]->ShowState(3) < 10) {//멘탈이 10이하면 
		if (random >= 0 && random < p[i]->EventPercent(0)) {
			suicide_script();//?%로 해당 이벤트 발생. 
			p[i]->HpControl(-100);
		}
	}
}

void SpaceShip::scientist_script() {
	//대충 실험실 내부 프린팅 
	int random;
	srand(time(NULL));
	random = rand() % 2;


	int choose;
	int i = 0;
	violence_selfinjury_panic_event(i);
	suicide_panic_event(i);

	if (random == 1) {
		scientist_script1();

		while (1) {
			printf(">>");
			int result = scanf("%d", &choose);

			if (result == 1) { // 성공적으로 정수를 입력받은 경우
				if (choose == 1) {
					printf(">>1 선택");
					p[i]->MentalControl(5);
					break;
				}
				else if (choose == 2) {
					printf(">>2 선택");
					p[i]->MentalControl(-5);
					abuse_distroy_panic_event(i);
					break;
				}
				else {
					printf(">>잘못된 입력입니다.\n");
				}
			}
			else {
				printf(">>숫자가 아닌 입력입니다. 다시 시도하세요.\n");
				// 입력 버퍼를 비우기
				while (getchar() != '\n');
			}
		}

		return;
	}
	else {
		scientist_script2();

		while (1) {
			printf(">>");
			int result = scanf("%d", &choose);

			if (result == 1) { // 성공적으로 정수를 입력받은 경우
				if (choose == 1) {
					printf(">>1 선택");
					p[i]->MentalControl(5);
					break;
				}
				else if (choose == 2) {
					printf(">>2 선택");
					p[i]->MentalControl(-5);
					abuse_distroy_panic_event(i);
					break;
				}
				else {
					printf(">>잘못된 입력입니다.\n");
				}
			}
			else {
				printf(">>숫자가 아닌 입력입니다. 다시 시도하세요.\n");
				// 입력 버퍼를 비우기
				while (getchar() != '\n');
			}
		}
		return;
	}
	_getch();
}

void SpaceShip::engineer_script() {
	int random;
	srand(time(NULL));
	random = rand() % 2;


	int choose;
	int i = 1;
	violence_selfinjury_panic_event(i);
	suicide_panic_event(i);

	if (random == 1) {
		engineer1_script1();

		while (1) {
			printf(">>");
			int result = scanf("%d", &choose);

			if (result == 1) { // 성공적으로 정수를 입력받은 경우
				if (choose == 1) {
					printf(">>1 선택");
					p[i]->MentalControl(-5);
					abuse_distroy_panic_event(i);
					break;
				}
				else if (choose == 2) {
					printf(">>2 선택");
					p[i]->MentalControl(5);
					break;
				}
				else {
					printf(">>잘못된 입력입니다.\n");
				}
			}
			else {
				printf(">>숫자가 아닌 입력입니다. 다시 시도하세요.\n");
				// 입력 버퍼를 비우기
				while (getchar() != '\n');
			}
		}

		return;
	}
	else {
		engineer1_script2();
		while (1) {
			printf(">>");
			int result = scanf("%d", &choose);

			if (result == 1) { // 성공적으로 정수를 입력받은 경우
				if (choose == 1) {
					printf(">>1 선택");
					p[i]->MentalControl(5);
					break;
				}
				else if (choose == 2) {
					printf(">>2 선택");
					p[i]->MentalControl(-5);
					abuse_distroy_panic_event(i);
					break;
				}
				else {
					printf(">>잘못된 입력입니다.\n");
				}
			}
			else {
				printf(">>숫자가 아닌 입력입니다. 다시 시도하세요.\n");
				// 입력 버퍼를 비우기
				while (getchar() != '\n');
			}
		}
		return;
	}
	_getch();
}

void SpaceShip::doctor_script() {
	//대충 수술실 내부 프린팅 
	int random;
	srand(time(NULL));
	random = rand() % 2;


	int choose;
	int i = 2;
	violence_selfinjury_panic_event(i);
	suicide_panic_event(i);

	if (random == 1) {
		doctor_script1();

		while (1) {
			printf(">>");
			int result = scanf("%d", &choose);

			if (result == 1) { // 성공적으로 정수를 입력받은 경우
				if (choose == 1) {
					printf(">>1 선택");
					p[i]->MentalControl(-5);
					abuse_distroy_panic_event(i);
					break;
				}
				else if (choose == 2) {
					printf(">>2 선택");
					p[i]->MentalControl(5);
					break;
				}
				else {
					printf(">>잘못된 입력입니다.\n");
				}
			}
			else {
				printf(">>숫자가 아닌 입력입니다. 다시 시도하세요.\n");
				// 입력 버퍼를 비우기
				while (getchar() != '\n');
			}
		}

		return;
	}
	else {
		doctor_script2();

		while (1) {
			printf(">>");
			int result = scanf("%d", &choose);

			if (result == 1) { // 성공적으로 정수를 입력받은 경우
				if (choose == 1) {
					printf(">>1 선택");
					p[i]->MentalControl(5);
					break;
				}
				else if (choose == 2) {
					printf(">>2 선택");
					p[i]->MentalControl(-5);
					abuse_distroy_panic_event(i);
					break;
				}
				else {
					printf(">>잘못된 입력입니다.\n");
				}
			}
			else {
				printf(">>숫자가 아닌 입력입니다. 다시 시도하세요.\n");
				// 입력 버퍼를 비우기
				while (getchar() != '\n');
			}
		}
		return;
	}
	_getch();
}

void SpaceShip::army_script() {
	//대충 장비실 내부 프린팅
	int random;
	srand(time(NULL));
	random = rand() % 2;


	int choose;
	int i = 2;
	violence_selfinjury_panic_event(i);
	suicide_panic_event(i);

	if (random == 1) {
		army_script1();

		while (1) {
			printf(">>");
			int result = scanf("%d", &choose);

			if (result == 1) { // 성공적으로 정수를 입력받은 경우
				if (choose == 1) {
					printf(">>1 선택");
					p[i]->MentalControl(5);
					break;
				}
				else if (choose == 2) {
					printf(">>2 선택");
					p[i]->MentalControl(-5);
					abuse_distroy_panic_event(i);
					break;
				}
				else {
					printf(">>잘못된 입력입니다.\n");
				}
			}
			else {
				printf(">>숫자가 아닌 입력입니다. 다시 시도하세요.\n");
				// 입력 버퍼를 비우기
				while (getchar() != '\n');
			}
		}

		return;
	}
	else {
		army_script2();

		while (1) {
			printf(">>");
			int result = scanf("%d", &choose);

			if (result == 1) { // 성공적으로 정수를 입력받은 경우
				if (choose == 1) {
					printf(">>1 선택");
					p[i]->MentalControl(-5);
					abuse_distroy_panic_event(i);
					break;
				}
				else if (choose == 2) {
					printf(">>2 선택");
					p[i]->MentalControl(5);
					break;
				}
				else {
					printf(">>잘못된 입력입니다.\n");
				}
			}
			else {
				printf(">>숫자가 아닌 입력입니다. 다시 시도하세요.\n");
				// 입력 버퍼를 비우기
				while (getchar() != '\n');
			}
		}
		return;
	}
	_getch();
}

void SpaceShip::day_talk() {

	int ib;
	int flag = 0;

	int random;
	srand(time(NULL));
	random = rand() % 5;
	violence_selfinjury_panic_event(random);

	for (int i = 0; i < alive_person(); i++) {
		system("cls");
		//조종실 내부 프린팅
		printf(">>어느 탐사원과 대화시간을 가질까?\n");
		if (p[0]->ShowState(1) > 0 && p[0]->ShowState(flag) == 0) { //살아있는 애들만 선택지에 뜨게 
			printf("1. 생태학자\n");
		}
		else {
			printf("?. □▦▤▦\n");
		}
		if (p[1]->ShowState(1) > 0 && p[1]->ShowState(flag) == 0) {
			printf("2. 엔지니어\n");
		}
		else {
			printf("?. ▦□▤▦\n");
		}
		if (p[2]->ShowState(1) > 0 && p[2]->ShowState(flag) == 0) {
			printf("3. 의사\n");
		}
		else {
			printf("?. □▤\n");
		}
		if (p[3]->ShowState(1) > 0 && p[3]->ShowState(flag) == 0) {
			printf("4. 군인\n");
		}
		else {
			printf("?. ▤▦\n");
		}
		printf(">>");
		scanf("%d", &ib);

		switch (ib) {
		case 1:
			if (p[0]->ShowState(flag) == 1) {
				system("cls");
				cout << "  [생태학자의 오늘치 대화는 완료되었습니다.]\n\n";
				i--;
				_getch();
				break;
			}
			scientist_script();//스크립트 출력 
			p[0]->SetTalkFlag(1);//하루 한번 대화했음 내일 전까지 다시 못함. 
			break;
		case 2:
			if (p[1]->ShowState(flag) == 1) {
				system("cls");
				cout << "  [엔지니어의 오늘치 대화는 완료되었습니다.]\n\n";
				i--;
				_getch();
				break;
			}
			engineer_script();
			p[1]->SetTalkFlag(1);
			break;
		case 3:
			if (p[2]->ShowState(flag) == 1) {
				system("cls");
				cout << "  [의사의 오늘치 대화는 완료되었습니다.]\n\n";
				i--;
				_getch();
				break;
			}
			doctor_script();
			p[2]->SetTalkFlag(1);
			break;
		case 4:
			if (p[3]->ShowState(flag) == 1) {
				system("cls");
				cout << "  [군인의 오늘치 대화는 완료되었습니다.]\n\n";
				i--;
				_getch();
				break;
			}
			army_script();
			p[3]->SetTalkFlag(1);
			break;
		default:
			printf(">>입력이 잘못되었습니다. ex: 1");
			while (getchar() != '\n');
			i--;
			_getch();
		}

	}
	flag = 0;
	for (int j = 0; j < 4; j++) {
		p[j]->SetTalkFlag(0);//하루 끝나고 다시 플래그 0으로 돌림. 
	}
	violence_selfinjury_panic_event(random);
	cout << ">>탐사원 모두 상담을 완료했습니다.\n";
}

void SpaceShip::Game() {
	int e = 0;
	int tDay = 0;
	StartUI(); 
	while (1) {
		e = StartDay();
		if (e != 0) { //자원 부족, 아사 엔딩 
			break;
		}
		PrintInformation();
		cp[0] = time(NULL);
		UpgradeRoom();
		cp[1] = time(NULL);
		Feed();
		cp[2] = time(NULL);
		if (explore != 1) {
			explore = choosePlanet();
			tDay = planetList[0].ShowIntState(1);
		}
		if (explore == 1) { //행성 탐사를 하는 경우 
		   //for(int i = 0; i < planetList[0].ShowIntState(1); i++){
		   //   일수에 따라 상담 ㄱ
		   //   다음 날로 넘어감(if 팀원이 죽거나 정신력 부족으로 미치는 등 뭔가 이벤트가 있다면 이벤트 화면도 띄움)
		   //}
		   //도착하면 탐사 인원 선택
		   //행성 정보 보여주고 탐사할 건지? 선택
		   //탐사 결과 보여줌
		   //다음 날로 넘어감(if 팀원이 죽거나 정신력 부족으로 미치는 등 뭔가 이벤트가 있다면 이벤트 화면도 띄움)
			
			if (tDay > 0) {
				day_talk();
			}
			if (tDay = 0) {
				DecideToExplore();
			}
			
		}
		else energy -= 100;
		tDay--;
		day++;
	}
	PrintEnding(e);
}

void SpaceShip::PrintInformation() { //"현재 정보" 입력 시 출력되는 정보 
   //일 수, 참험 행성 수, 탐사선 정보, 기체 구역 lv, 참사원 체력, 배부름 출력 
	system("cls");
	cout << ">>깨어난 지 " << day << "일 경과\n";
	cout << ">>남은 자원 | 에너지: " << energy << " 음식: " << food << "\n";
	cout << ">>탐험한 행성 수: " << exploredPlanet << "개\n";
	cout << ">>각 기체 구역 현재 레벨\n";
	for (int i = 0; i < 5; i++) cout << "  " << r[i]->ShowName() << ": " << r[i]->ShowLv() << "Lv\n";
	cout << ">>각 탐사원 정보\n";
	for (int i = 0; i < 4; i++) cout << "  " << p[i]->ShowJob() << " | 체력: " << p[i]->ShowState(1) << "/" << p[i]->ShowMaxState(1) << " 배부름 수치: " << p[i]->ShowState(2) << "/" << p[i]->ShowMaxState(2) << " 정신력: " << p[i]->ShowState(3) << "/" << p[i]->ShowMaxState(3) << "\n";
	_getch();
}

void SpaceShip::PrintEnding(int e) {
	if (e == 1) { //우주 미아 엔딩 출력 
		system("cls");
		cout << "  >>모든 에너지가 소비되었습니다." << endl;
		Sleep(1000);
		cout << "  >>탐사원의 생존이 더이상 불가능하다고 판단." << endl;
		Sleep(1000);
		cout << "  >>모든 현재 생존 탐사원들에게 안락사 용 약물. 넴뷰탈을 제공합니다." << endl << endl;
		Sleep(1000);
		cout << "  >>탐사원의 시스템 제어 권한 박탈." << endl << endl;
		Sleep(2500);
		cout << "  …" << endl;
		Sleep(2500);
		cout << "  …" << endl;
		Sleep(2500);
		cout << "  …" << endl << endl;
		Sleep(2500);
		cout << "   >>현시간부로 모든 탐사원이 사망했습니다. 이에따라 유서 영상 수집을 시작하겠습니다." << endl << endl;
		Sleep(1000);
		cout << "   >>탐사선에 저장된 현재까지의 영상기록 재생…" << endl;
		Sleep(1000);
		cout << "   >>탐사원들의 대화 수집…" << endl;
		Sleep(1000);
		cout << "   >>중요기억장치에 저장 중…" << endl << endl;
		Sleep(2500);
		cout << "   >>저장이 완료되었습니다." << endl << endl;
		Sleep(1000);
		cout << "   [모든 탐사원이 사망함에 따라 보이저 호 시스템 관리 AI를 절전모드로 전환합니다…]" << endl << endl;
		Sleep(1000);
		cout << "   [전환중…]" << endl << endl;
		Sleep(2500);
		cout << "   [자동 탐사모드를 시작합니다…]" << endl;
		Sleep(1000);
		cout << "   [기존 설정에 의하여 새로운 지구 발견까지 무기한 예상 탐사가 진행되며, 발견 후 보이저 호 시스템 관리 AI의 절전모드가 해제됩니다…]" << endl << endl;
		Sleep(1000);
		cout << "         Ending..." << endl;
		_getch();

	}
	else if (e == 2) { //모두 죽은 엔딩 출력 
		system("cls");
		cout << "   >>현시간부로 모든 탐사원이 사망했습니다. 이에따라 마지막 탐사일지를 작성하겠습니다." << endl << endl;
		Sleep(1000);
		cout << "   >>탐사선에 저장된 현재까지의 영상기록 재생…" << endl;
		Sleep(1000);
		cout << "   >>탐사원들의 대화 수집…" << endl;
		Sleep(1000);
		cout << "   >>중요기억장치에 저장 중…" << endl << endl;
		Sleep(2500);
		cout << "   >>저장이 완료되었습니다." << endl << endl;
		Sleep(1000);
		cout << "   [모든 탐사원이 사망함에 따라 보이저 호 시스템 관리 AI를 절전모드로 전환합니다…]" << endl << endl;
		Sleep(1000);
		cout << "   [전환중…]" << endl << endl;
		Sleep(2500);
		cout << "   [자동 탐사모드를 시작합니다…]" << endl;
		Sleep(1000);
		cout << "   [기존 설정에 의하여 새로운 지구 발견까지 무기한 예상 탐사가 진행되며, 발견 후 보이저 호 시스템 관리 AI의 절전모드가 해제됩니다…]" << endl << endl;
		Sleep(1000);
		cout << "         Ending..." << endl;
		_getch();
	}
	else { //신 지구를 찾은 엔딩 출력 
		system("cls");
		cout << "  보이저 호의 여정은 어려움과 맞닥뜨렸지만, " << endl;
		Sleep(1000);
		cout << "  새로운 지구를 찾아내는 순간이 다가왔습니다." << endl << endl;
		Sleep(1000);
		cout << "  탐사원들은 오랜 여정 동안 많은 어려움에 부딪혔지만," << endl;
		Sleep(1000);
		cout << "  그들의 힘과 희생으로 보이저 호는 마침내 목표를 달성했습니다." << endl << endl;
		Sleep(1000);
		cout << "  탐사원은 각자의 분야에서 새로운 지구를 개척하는, 새로운 여정을 시작했습니다." << endl << endl;
		Sleep(2500);
		cout << "  ." << endl;
		Sleep(2500);
		cout << "  ." << endl;
		Sleep(2500);
		cout << "  ." << endl << endl;
		Sleep(2500);
		cout << "   [메모리얼 기념관]" << endl << endl;
		Sleep(1000);
		cout << "   신지구 발견 당시의 영상물을 불러옵니다." << endl << endl;
		Sleep(1000);
		cout << "   로딩중…" << endl << endl;
		Sleep(2500);
		cout << "   영상을 재생합니다." << endl << endl;
		Sleep(1000);
		cout << "   ”이제 인류는 새로운 지구에서 다시 시작할 기회를 얻었습니다.”" << endl;
		Sleep(2000);
		cout << "   ”모두가 기여한 노력과 희생에 감사드립니다.”" << endl;
		Sleep(2000);
		cout << "   ”이제 우리는 함께 이 곳을 개척하고 새로운 삶을 살아갈 것입니다.”" << endl << endl;
		Sleep(2000);
		cout << "   ”새로운 지구에 오신 것을 환영합니다!”" << endl << endl;
		Sleep(1000);
		cout << "         Ending..." << endl;
		_getch();
	}

}

void SpaceShip::StartUI() {
	log(COLOR_YELLOW, "                                               @@@@@@@@@@@@@@@                     ");
	log(COLOR_YELLOW, "                                            @@@@@@@@@@@@@@@@@@@@@                   ");
	log(COLOR_YELLOW, "                                         ,@@@@@@@@@@@@@@@@@@@@@@@@@@,                ");
	log(COLOR_YELLOW, "                                        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                ");
	log(COLOR_YELLOW, "                                     #@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#               ");
	log(COLOR_YELLOW, "                                    @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@              ");
	log(COLOR_YELLOW, "                                   @@@@@@@@@@@@@@@@@@@  @@@@@@@@@@@@@@@@@@@             ");
	log(COLOR_YELLOW, "                                  @@@@@@@@@@@@@@@@@@@@  @@@@@@@@@@@@@@@@@@@@            ");
	log(COLOR_YELLOW, "                                 ,@@@@@@@@@@@@@@@@@@@    @@@@@@@@@@@@@@@@@@@@,           ");
	log(COLOR_YELLOW, "                                ,$@@@@@@@@@@@@@@@@@@,    ,@@@@@@@@@@@@@@@@@@@@,           ");
	log(COLOR_YELLOW, "                                ,@@@@@@@@@@@@@@@@@@@  @@  @@@@@@@@@@@@@@@@@@@@@,          ");
	log(COLOR_YELLOW, "                               ,@@@@@@@@@@@@@@@@@@@@  @@  @@@@@@@@@@@@@@@@@@@@@,          ");
	log(COLOR_YELLOW, "                               ,@@@@@@@@@@@@@@@@@@@@      @@@@@@@@@@@@@@@@@@@@@,          ");
	log(COLOR_YELLOW, "                               ,@@@@@@@@@@@@@@@@@@@@      @@@@@@@@@@@@@@@@@@@@@,          ");
	log(COLOR_YELLOW, "                               ,@@@@@@@@@@@@@@@@@@@@      @@@@@@@@@@@@@@@@@@@@@,          ");
	log(COLOR_YELLOW, "                                ,@@@@@@@@@@@@@@@@@@@      @@@@@@@@@@@@@@@@@@@@,          ");
	log(COLOR_YELLOW, "                                 ,@@@@@@@@@@@@@@@@@        @@@@@@@@@@@@@@@@@@,          ");
	log(COLOR_YELLOW, "                                   @@@@@@@@@@@@@@            @@@@@@@@@@@@@@@,           ");
	log(COLOR_YELLOW, "                                     @@@@@@@@@@@              @@@@@@@@@@@@,           ");
	log(COLOR_YELLOW, "                                      @@@@@@@@@$$$$$      $$$$$@@@@@@@@@@,            ");
	log(COLOR_YELLOW, "                                        :@@@@@@@@@@@@!  !@@@@@@@@@@@@@@            ");
	log(COLOR_YELLOW, "                                          ,@@@@@@@@@@@  @@@@@@@@@@@@,             ");
	log(COLOR_YELLOW, "                                            @@@@@@@@@@  @@@@@@@@@@@               ");
	log(COLOR_YELLOW, "                                              @@@@@@@    @@@@@@@@              ");
	log(COLOR_YELLOW, "                                                ::@~       :@::.             ");
	log(COLOR_YELLOW, "                                                                                 ");
	log(COLOR_GRAY, "                                                @@@@@@@@@@@@@@          @@@@@@@@, ");
	log(COLOR_GRAY, "                              @@@$             @@@@@@@@@@@@@@@         @@@@@@@@@@@@@ ");
	log(COLOR_GRAY, "                 @@@@@@  $$$$$@@@@$            @@@@@@@@@@@@@@@@@   $$  *@@@@@@@@@@@@@@ ");
	log(COLOR_GRAY, "               @@@@@@@@@@  @@@@@@@@@@@@!!!;      .!@@@@@@@@@@@@@@!!!@@!  !#@@@@@@@@@@@ @@@@@ ");
	log(COLOR_BBLACK, "              @@@@@@@@@  @@@@@@@@@@@@@!@#:     ;@@@@@@@@@@!  !@@@@@@@@@@@@@@@@@@@@@       @@@@, ");
	log(COLOR_BBLACK, "            @@@@@@   @@@    @@@@@@@@       @@@@@@@@@@@@   @@@@@@    @,     $@   !@@@@@@@@  @@@@ ");
	log(COLOR_BBLACK, "         @@@@@@@@  @@     @@,,,;@!!!!!    ,#!@@@$  :    @@@@@@@!!!!   ! ;#@!!!!@@@@@@@@@@@ @@@@@ ");
	log(COLOR_BBLACK, "        @@@@@@@@@@@@@@@@@@@@@@@@@@@@@.!!@@@@::;@@@@!#:    : :@@@@@@@@@@@:  :@:#@@!!!!!@@@@@@@@@@@@, ");

	cout << "\n";

	log(COLOR_BCYAN, ":::::::::   ::::::::  ::::    :::       :::     :::  ::::::::  :::   :::     :::      ::::::::  :::::::::: ");
	log(COLOR_BCYAN, ":+:    :+: :+:    :+: :+:+:   :+:       :+:     :+: :+:    :+: :+:   :+:   :+: :+:   :+:    :+: :+:        ");
	log(COLOR_BCYAN, "+:+    +:+ +:+    +:+ :+:+:+  +:+       +:+     +:+ +:+    +:+  +:+ +:+   +:+   +:+  +:+        +:+        ");
	log(COLOR_BCYAN, "+#++:++#+  +#+    +:+ +#+ +:+ +#+       +#+     +:+ +#+    +:+   +#++:   +#++:++#++: :#:        +#++:++#   ");
	log(COLOR_BCYAN, "+#+    +#+ +#+    +#+ +#+  +#+#+#        +#+   +#+  +#+    +#+    +#+    +#+     +#+ +#+   +#+# +#+        ");
	log(COLOR_BCYAN, "#+#    #+# #+#    #+# #+#   #+#+#         #+#+#+#   #+#    #+#    #+#    #+#     #+# #+#    #+# #+#        ");
	log(COLOR_BCYAN, "#########   ########  ###    ####           ###      ########     ###    ###     ###  ########  ########## ");

	_getch();

}

void SpaceShip::PlanetUI1() {
	log(COLOR_GRAY, "                     ~@@@@@@@@@~                   ");
	log(COLOR_GRAY, "        @          @@@@@@@@@@@@@@@                 ");
	log(COLOR_GRAY, "                 @@@@@@@@@@@@@@@@@@@               ");
	log(COLOR_GRAY, "               ;@@@@@@@@@@@@@@@@@@@@@@             ");
	log(COLOR_GRAY, "             $@@@@@@@@@@@@@@@@@@@@@@@@@,    @      ");
	log(COLOR_GRAY, "            .@@@@@@@@@@@@@@@@@@@@@@@@@@@*          ");
	log(COLOR_GRAY, "            ,@@@@@@@@@@@@@@@@@@@@@@@@@@@@          ");
	log(COLOR_GRAY, "           :@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#         ");
	log(COLOR_GRAY, "           :@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@         ");
	log(COLOR_GRAY, "           @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@        ");
	log(COLOR_GRAY, "           ;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#         ");
	log(COLOR_GRAY, "           :@@@@@@@@@@@@@@@@@@@@@@@@@@@@@~         ");
	log(COLOR_GRAY, "           -=@@@@@@@@@@@@@@@@@@@@@@@@@@@=          ");
	log(COLOR_BBLACK, "             ,$@@@@@@@@@@@@@@@@@@@@@@@@,    @      ");
	log(COLOR_BBLACK, "       @        @@@@@@@@@@@@@@@@@@@@@;     @@@     ");
	log(COLOR_BBLACK, "                  @@@@@@@@@@@@@@@@@@        @      ");
	log(COLOR_BBLACK, "           @       ~@@@@@@@@@@@@@@                 ");
	log(COLOR_BBLACK, "                     ~@@@@@@@@@~       @           ");
	cout << "\n";
}

void SpaceShip::PlanetUI2() {
	log(COLOR_GRAY, "     @@              ~@@@@@@@@@~                       ");
	log(COLOR_GRAY, "   @@@@@@          @@@@@@@@@@@@@@@         @           ");
	log(COLOR_GRAY, "     @@          @@@@@@@@@@@@@@@@@@@                   ");
	log(COLOR_GRAY, "               ;@@@@@@@@@@@@@@@@@@@@@@                 ");
	log(COLOR_GRAY, "             $@@@@@@@@@@@@@@@@@@@@@@@@@,      @        ");
	log(COLOR_GRAY, "       @    .@@@@@@@@@@@@@@@@@@@@@@@@@@@*    @@@       ");
	log(COLOR_GRAY, "            ,@@@@@@@@@@@@@@@@@@@@@@@@@@@@     @        ");
	log(COLOR_GRAY, "           :@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#             ");
	log(COLOR_BCYAN, "  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  ");
	log(COLOR_CYAN, "  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  ");
	log(COLOR_GRAY, "           ;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#             ");
	log(COLOR_GRAY, "           :@@@@@@@@@@@@@@@@@@@@@@@@@@@@@~             ");
	log(COLOR_GRAY, "           -=@@@@@@@@@@@@@@@@@@@@@@@@@@@=              ");
	log(COLOR_GRAY, "             ,$@@@@@@@@@@@@@@@@@@@@@@@@,               ");
	log(COLOR_GRAY, "                @@@@@@@@@@@@@@@@@@@@@;           @     ");
	log(COLOR_BBLACK, "      @           @@@@@@@@@@@@@@@@@@                   ");
	log(COLOR_BBLACK, "                   ~@@@@@@@@@@@@@@    @                ");
	log(COLOR_BBLACK, "                     ~@@@@@@@@@~                       ");
	cout << "\n";
}

int main() {
	SpaceShip s;
	s.Game();
}
