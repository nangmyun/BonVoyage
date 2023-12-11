//���� + ���
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include <stdlib.h> // rand()�Լ� ���� ���̺귯��
#include <time.h> // time()�Լ� ���� ���̺귯��
#include<cmath> //�ݿø� �Լ� round() ��� 
#include<Windows.h>
#include<conio.h>
#include<vector> 
#include <time.h>

// UI ����
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
	//���� �� ��, �̵��ϴµ� ���� ������, ���� �� �ִ� �ڿ�, ����, ����ü ���� ����(���� �� 1, �ƴϸ� 0) 
	int dayUntil, usingEnergy, energy, food, creature;
	string PlanetType, level, cretureType; //�༺ Ÿ��, ���̵�, ����ü ���� 
public:
	Planet(int cp); //�༺ ���� �������� �̾� �ֱ� 
	void showPlanetState(); //�༺ ���� ����
	int ShowIntState(int n) { //1 �Է� �� ���� �� ��, 2 �̵��ϴµ� ���� ������, 3 ���� �� �ִ� �ڿ�, 4 ���� �� �ִ� ����, 5 ����ü ���� ���� �� ��ȯ 
		if (n == 1) return dayUntil;
		else if (n == 2) return usingEnergy;
		else if (n == 3) return energy;
		else if (n == 4) return food;
		else return creature;
	}
	string ShowStringState(int n) { //1 �Է� �� �༺ Ÿ��, 2 ���̵�, 3 ����ü ����  �� ��ȯ 
		if (n == 1) return PlanetType;
		else if (n == 2) return level;
		else return cretureType;
	}
};

Planet::Planet(int cp) {
	int random;
	srand(cp); // �Ź� �ٸ� �õ尪 ����
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

	if (rand() % 2 == 0) PlanetType = "����";
	else PlanetType = "�ϼ�";

	random = rand() % 3;
	if (random == 0) level = "��";
	else if (random == 1) level = "��";
	else level = "��";

	creature = rand() % 2;

	if (rand() % 2 == 0) cretureType = "����";
	else cretureType = "�¼�";

	energy = rand() % 3 + 1;
	food = rand() % 3 + 1;
}

class Room {
protected:
	int lv; // ���׷��̵� ����
	string name;
public:
	Room() { lv = 0; }
	//���׷��̵� ����(�ִ� ������ �� 0, �ڿ� ���� �� 1 ��ȯ), ���� �� ���׷��̵� ��� ��ȯ
	//������ �ϴµ� ���� ���� �ڿ����� 100���Ϸ� ������ ��� �޽��� ���
	int Upgrade(int resource);
	int ShowLv() { return lv; }
	string ShowName() { return name; }
	void lvUp() {
		lv++;
	}
	virtual int function() = 0; //�� �Ǹ��� ��� ���� �Լ� 
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
			cout << ">>���! ������ ���׷��̵� �Ͻðڽ��ϱ�? (�� / �ƴϿ�)\n";
			cout << ">>���׷��̵� �� ���� ������ �ڿ�: " << (resource - UpgradeCost) << "\n�Է�: ";
			string n;
			cin >> n;
			if (n == "��") return UpgradeCost;
			else if (n == "�ƴϿ�") return 1;
			else {
				cout << ">>�߸� �Է��߽��ϴ�. ���׷��̵尡 ��ҵ˴ϴ�.";
				return 1;
			}
		}
		else return UpgradeCost;
	}
}

class ResourceRoom : public Room {
public:
	ResourceRoom() { lv = 1; name = "�ڿ���"; }
	virtual int function() {
		if (lv == 1) return 170;
		else if (lv == 2) return 210;
		else return 240;
	}
};

class ScienceRoom : public Room {
public:
	ScienceRoom() { name = "�����"; }
	virtual int function() {
		if (lv == 0) return 0;
		else if (lv == 1) return 1;
		else if (lv == 2) return 2;
		else return 3;
	}
};

class EngineRoom : public Room {
public:
	EngineRoom() { name = "������"; }
	virtual int function() { //��ȯ�ϴ� �� %������!!!! 
		if (lv == 0) return 0;
		else if (lv == 1) return 10;
		else if (lv == 2) return 20;
		else return 30;
	}
};

class MedicalRoom : public Room {
public:
	MedicalRoom() { name = "�Ƿ��"; }
	virtual int function() {
		if (lv == 0) return 0;
		else if (lv == 1) return 3;
		else if (lv == 2) return 5;
		else return 7;
	}
};

class DefenseRoom : public Room {
public:
	DefenseRoom() { name = "����"; }
	virtual int function() { //��ȯ�ϴ� �� %������!!!! 
		if (lv == 0) return 0;
		else if (lv == 1) return 5;
		else if (lv == 2) return 8;
		else return 12;
	}
};

class Person {
	int MAXhp, MAXfull, MAXmental; //������ �ִ� ���ݰ� 
	int hp, full, mental; //���� ���ݰ�. ü��, ��θ�, ��Ż. ��� �� ���� 0 ���� 
	int talk; //��ȭ�ߴ��� ���ߴ��� �÷��� ��. 
	int ABnDIS, SELnVIO, S_DEAD;
	string job; //���� �̸� 
public:
	//ü�� ����, ���� ����,  
	Person(int h, int f, int m, string j, int t, int A, int S, int D) {
		MAXhp = h; MAXfull = f; MAXmental = m;
		hp = h; full = f + 5; mental = m; job = j;
		talk = t;
		ABnDIS = A; SELnVIO = S; S_DEAD = D;
	}
	//int& operator +=(int n); //Ž��� ���� ���� ���۷����� 
	void HpControl(int h) { hp += h; } //ü�� ��� �Ǵ� �϶� 
	void FullControl(int f) { full += f; } //���� ��� �Ǵ� �϶� 
	void MentalControl(int m) { mental += m; } //��Ż ��� �Ǵ� �϶�
	void SetTalkFlag(int flag) { talk = flag; }
	int ShowMaxState(int n) { //1 �Է� �� MAXhp, 2 �Է� �� MAXfull, 3 �Է� �� MAXmental �� ��ȯ 
		if (n == 1) return MAXhp;
		else if (n == 2) return MAXfull;
		else if (n == 3) return MAXmental;
	}
	int ShowState(int n) { //1 �Է� �� hp, 2 �Է� �� full, 3 �Է� �� mental �� ��ȯ, 4�� talk. 
		if (n == 1) return hp;
		else if (n == 2) return full;
		else if (n == 3) return mental;
		else return talk;
	}
	int EventPercent(int e) { //0==����,�ı� �߻�Ȯ��, 1==����,���� �߻�Ȯ��, 2==�ڻ� �߻�Ȯ�� 
		if (e == 0) return ABnDIS;
		else if (e == 1) return SELnVIO;
		else return S_DEAD;
	}
	string ShowJob() { return job; } //���� �̸� ��ȯ 
};

class SpaceShip {
	int day, energy, food, exploredPlanet, cp[3], alive; //cp�� srand()�� ���� �õ尪�� �����س��� �迭 
	//string state; //����, �̵�, ���� 
	Person* p[4]; //Ž��� ���� ����. ������� ��������, �����Ͼ�, �ǻ�, ���� 
	Room* r[5]; //��ü ���� ����. ������� �ڿ���, �����, ������, �Ƿ��, ���� 
	vector<Planet> planetList; //index 0�� ������ �༺ �� 
	vector<Planet>::iterator it;
public:
	SpaceShip();
	~SpaceShip();
	int alive_person();
	void PrintInformation(); //"���� ����" �Է� �� ��µǴ� ���� 
	void Game(); //���� �����ϴ� �Լ�(while�� ����) 
	int StartDay(); //�ڿ� ���� ���� �˻�, ����� �پ��� ü�� ȸ�� 
	void UpgradeRoom(); //��ü ���� ���׷��̵� 
	void Feed(); //�ķ� �й� 
	int choosePlanet(); //�༺ ���� �� ���� 
	int ExploreMember1, ExploreMember2, ExploreMember3, ExploreMember4;  //�༺ ���� ���� �Լ���
	void DecideToExplore();
	void YesToExplore();
	void NoToExplore();
	void EventProbability();
	void GoodEvent();
	void BadEvent();
	void day_talk(); //�༺ ���� �� ����ϴ� ����~ 
	void scientist_script();
	void engineer_script();
	void doctor_script();
	void army_script();
	void abuse_distroy_panic_event(int i);
	void violence_selfinjury_panic_event(int i);
	void suicide_panic_event(int i);
	void PrintEnding(int e); //1: �ڿ� ���� ����,  2: all ��� ����, 3: �� ���� ���� ���� 
	void StartUI();
	void PlanetUI1();
	void PlanetUI2();
};

SpaceShip::SpaceShip() {
	p[0] = new Person(80, 100, 80, "��������", 0, 15, 40, 50);
	p[1] = new Person(90, 90, 80, "�����Ͼ�", 0, 18, 60, 40);
	p[2] = new Person(80, 80, 100, "�ǻ�", 0, 15, 30, 30);
	p[3] = new Person(100, 60, 100, "����", 0, 13, 70, 40);
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
	if (energy <= 0) return  1; //�ڿ� ���� ���� 

	for (int i = 0; i < 4; i++) { //��θ� ����, hp ȸ�� 
		if (p[i]->ShowState(2) == 0) continue;

		p[i]->FullControl(-5);
		if (p[i]->ShowState(2) <= 0) { //����� 0 ���� �ƻ� 
		   //������ | �ƻ� �̺�Ʈ ��� 
			cout << ">>" << p[i]->ShowJob() << "��(��) �ƻ��߽��ϴ�. ���� ������ ���ǰ� �ʿ��մϴ�." << endl;
			for (int j = 0; j < 4; j++) {
				p[j]->MentalControl(-10);
			}
			p[i]->HpControl(-p[i]->ShowState(1));//��� ó�� 
			p[i]->FullControl(-p[i]->ShowState(2));
			p[i]->MentalControl(-p[i]->ShowState(3));
			continue;
		}
		p[i]->HpControl(r[3]->function());
		if (p[i]->ShowState(1) > p[i]->ShowMaxState(1)) p[i]->HpControl(-(p[i]->ShowState(1) - p[i]->ShowMaxState(1)));
	}
	//�����ִ� ����� ��� �ƻ����� ��� 
	if (p[0]->ShowState(2) == 0 && p[1]->ShowState(2) == 0 && p[2]->ShowState(2) == 0 && p[3]->ShowState(2) == 0) return 2; //all ��� ���� 
	return 0;
}

void SpaceShip::UpgradeRoom() {
	string n;
	int rnum, result, ug;
	while (1) {
		system("cls");
		//UI ��� 
		cout << ">>�� ��ü ���� ���� ����\n";
		for (int i = 0; i < 5; i++) cout << "  " << r[i]->ShowName() << ": " << r[i]->ShowLv() << "Lv\n";
		cout << ">>���� ���� ������ �ڿ�: " << energy << "\n\n";
		cout << ">>���׷��̵带 ���ϴ� ��ü ���� �̸��� �Է����ּ���.\n";
		cout << ">>���׷��̵带 �������� '��'�� �Է����ּ���.\n>>";
		cin >> n;

		if (n == "��") break;
		else if (n == "�ڿ���") rnum = 0;
		else if (n == "�����") rnum = 1;
		else if (n == "������") rnum = 2;
		else if (n == "�Ƿ��") rnum = 3;
		else if (n == "����") rnum = 4;
		else {
			cout << "\n>>�ٽ� �Է��� �ּ���.";
			_getch();
			continue;
		}

		if (r[rnum]->ShowLv() == 0) ug = 700;
		else if (r[rnum]->ShowLv() == 1) ug = 900;
		else ug = 1200;

		cout << "\n>>" << r[rnum]->ShowName() << "�� �½��ϱ�? (�� / �ƴϿ�)\n";
		cout << ">>���׷��̵忡 �ʿ��� ������ �ڿ�: " << ug << "\n";
		cout << ">>���� ���� ������ �ڿ�: " << energy << "\n>>";
		cin >> n;

		if (n == "��") {
			result = r[rnum]->Upgrade(energy);

			if (result == 0) {
				cout << "\n>>�ش� ��ü ������ �̹� �ִ� �����Դϴ�.";
			}
			else if (result == 1) {
				cout << "\n>>�������� ������ ���׷��̵忡 �����߽��ϴ�.\n";
				cout << ">>���׷��̵忡 �ʿ��� ������ �ڿ�: " << ug << endl;
				cout << ">>���� ���� ������ �ڿ�: " << energy;
			}
			else {
				energy -= result;
				cout << "\n>>" << r[rnum]->ShowName() << " ���׷��̵尡 �Ϸ� �Ǿ����ϴ�.\n";
				cout << ">>���� ������ �ڿ�: " << energy;
				r[rnum]->lvUp();
			}
			_getch();
		}
		else if (n == "�ƴϿ�");
		else {
			cout << ">>�߸� �Է��߽��ϴ�. ���׷��̵尡 ��ҵ˴ϴ�.";
			_getch();
		}
	}
}

void SpaceShip::Feed() {
	string name;
	int person, amount;
	while (1) {
		system("cls");
		//UI ��� 
		cout << ">>�� Ž��� ���� ��θ� ��ġ\n";
		for (int i = 0; i < 4; i++) {
			if (p[i]->ShowState(1) == 0) cout << "  " << p[i]->ShowJob() << " | ���� ���\n";
			else cout << "  " << p[i]->ShowJob() << " | ��θ� ��ġ: " << p[i]->ShowState(2) << "/" << p[i]->ShowMaxState(2) << "\n";
		}
		cout << ">>���� ���� ���ķ�: " << food << "\n\n";
		cout << ">>������ ����� Ž��� �̸��� �Է����ּ���.\n";
		cout << ">>���� ����� �������� '��'�� �Է����ּ���.\n>>";
		cin >> name;

		if (name == "��") break;
		else if (name == "��������") person = 0;
		else if (name == "�����Ͼ�") person = 1;
		else if (name == "�ǻ�") person = 2;
		else if (name == "����") person = 3;
		else {
			cout << "\n>>�ٽ� �Է��� �ּ���.";
			_getch();
			continue;
		}

		cout << ">>������ �󸶳� ����ұ��?\n�Է�: ";
		cin >> amount;

		if (amount > food) {
			cout << ">>���� �����ϰ� �ִ� ���ķ��� �Ѿ���ϴ�. �ٽ� �Է����ּ���.";
			_getch();
			continue;
		}
		else if (p[person]->ShowState(2) + amount > p[person]->ShowMaxState(2)) {
			cout << "\n>>�ش� Ž������ �ִ� ��θ� ��ġ�� �Ѵ� ���� ����߱⿡ ���� ������ ��ȯ�߽��ϴ�.\n";
			amount = p[person]->ShowMaxState(2) - p[person]->ShowState(2);
		}
		cout << ">>������ " << amount << " ��ŭ ����߽��ϴ�.";
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
			if (i == 0) cout << "�༺ A";
			else if (i == 1) cout << "�༺ B";
			else  cout << "�༺ C";
			gotoxy(1 + i * 45, 1);
			cout << "�ش� �༺���� �̵��ϴµ� �ɸ��� �� ��: " << it->ShowIntState(1);
			gotoxy(1 + i * 45, 2);
			cout << "�༺ Ÿ��: " << it->ShowStringState(1) << " �༺";
			gotoxy(1 + i * 45, 3);
			cout << "Ž�� ���̵�: " << it->ShowStringState(2);
			gotoxy(1 + i * 45, 4);
			if (sLv >= 1) {
				cout << "����ü ����: ";
				if (it->ShowIntState(5) == 1) cout << "O";
				else  cout << "X";
			}
			else cout << "�ش� ���� ���� ����: ����� ���� 1";
			gotoxy(1 + i * 45, 5);
			if (sLv >= 2) cout << "����ü ����: " << it->ShowStringState(3);
			else cout << "�ش� ���� ���� ����: ����� ���� 2";
			gotoxy(1 + i * 45, 6);
			if (sLv >= 3) cout << "ȹ�� ���� �ڿ��� | ������: " << it->ShowStringState(3) << " ����: " << it->ShowStringState(4);
			else cout << "�ش� ���� ���� ����: ����� ���� 3";
			gotoxy(1 + i * 45, 8);
			cout << "�̵��ϴ� �� �Ҹ�Ǵ� ������: " << it->ShowIntState(2);
			it++;
		}
		gotoxy(1, 11);
		cout << ">>���� ���� �ڿ� | ������: " << energy << " ����: " << food << endl;
		cout << ">>Ž���ϰ��� �ϴ� �༺ �̸��� �Է����ּ���.\n";
		cout << ">>Ž���ϰ� ���� �༺�� ���ٸ� 'N'�� �Է����ּ���. ���Ϸ� �Ѿ�ϴ�.\n>>";
		cin >> n;
		if (!(n == "A" || n == "B" || n == "C" || n == "N")) {
			cout << ">>�ٽ� �Է��� �ּ���.";
			_getch();
			continue;
		}
		else if (n == "N") {
			cout << ">>Ž���� �༺�� ���� �ʾҽ��ϴ�. ���Ϸ� �Ѿ�ϴ�.";
			it = planetList.begin();
			it = planetList.erase(it);
			it = planetList.erase(it);
			_getch();
			return 0; //Ž�� �� �ϴ� ��� 
		}
		else {
			if ((n == "A" && planetList[0].ShowStringState(1) == "����") || (n == "B" && planetList[1].ShowStringState(1) == "����") || (n == "C" && planetList[2].ShowStringState(1) == "����")) {
				cout << ">>�ش� �༺�� Ž�簡 �Ұ����� ���� �༺�Դϴ�. �ٽ� �������ּ���.\n";
				_getch();
				continue;
			}
			cout << ">>�༺ " << n << "�� �������� �̵��մϴ�.\n";
			//���Ϳ� ������ �༺�� ����� �ٸ� �༺�� �� ����
			//planetList[0]�� ������ �༺ ���� 
			//���ͷ����� it�� planetList[0]�� ����Ű�� �س����ϱ� Ž���� �༺ ������ ������ �� planetList[0], it �� �� �ϳ��� �����ص� ���� 
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
			cout << ">>�̵��� ���� ������ �ڿ� " << it->ShowIntState(2) << " ��ŭ �Ҹ��߽��ϴ�.\n";
			energy -= it->ShowIntState(2);
			cout << ">>���� ���� ������: " << energy;
			_getch();
			return 1; //Ž�� �ϴ� ���   
		}
	}
}

//�߰�
void SpaceShip::DecideToExplore() {//�༺ ���� �� Ž�� ���� ���� ���ϱ�
	system("cls");
	int DecideToExplore;
	string WantToStop;
	srand(time(NULL));
	if (rand() % 2 == 0) PlanetUI1();
	else PlanetUI2(); 
	cout << ">>�༺�� �����߽��ϴ�. �� �༺�� Ž���Ͻðڽ��ϱ�?\n";
	cout << "  1. YES       2. NO\n>>";
	while (1) {
		cin >> DecideToExplore;
		if (DecideToExplore == 1) {
			YesToExplore();
			_getch();
			for (int k = 0; k < 3; k++) {
				if (k == 2) {
					EventProbability(); //Ž�� �� �����̺�Ʈ �߻�
					_getch();
					system("cls");
					cout << ">>���� �� �༺�� ���� ������ ������� �˰� �� �� �����ϴ�.\n>>���� �ٸ� �༺���� ������ �� �ð��Դϴ�.\n>>Ž�缱���� �����մϴ�.\n ";
					explore = 0;
					_getch();
				}
				else {
					EventProbability(); //Ž�� �� �����̺�Ʈ �߻�
					_getch();
					system("cls");
					cout << ">>���� �༺ Ž�縦 ���߰� �̷��Ͻðڽ��ϱ�?(��/�ƴϿ�)\n>>";
					cin >> WantToStop;
					if (WantToStop == "��")
					{
						cout << ">>Ž�縦 ���߰� Ž�缱���� �����մϴ�.\n";
						explore = 0;
						_getch();
						break;
					}
					else if (!((WantToStop == "��") || (WantToStop == "�ƴϿ�"))) {
						cout << ">>�ٽ� �Է��� �ּ���.\n>>";
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
			cout << ">>�ٽ� �Է����ּ���\n>>";
			_getch();
			continue;
		}
	}
}
void SpaceShip::YesToExplore() {     //Ž�� ���� ��� �����ϱ�
	system("cls");
	int n;
	cout << ">>Ž�縦 ���� ����� �����ϼ���.\n";
	while (1) {
		if (p[0]->ShowState(1) > 0) {
			cout << ">>�������ڸ� Ž�翡 �����ðڽ��ϱ�?\n";
			cout << "  1. ��    2. �ƴϿ�\n>>";
			cin >> n;
			if (n == 1) {
				cout << "\n�������ڸ� �����ϼ̽��ϴ�.\n";
				ExploreMember1 = 1;
				_getch();
				break;
			}
			else if (n == 2) {
				cout << "\n�������ڸ� ������ �ʽ��ϴ�.\n";
				ExploreMember1 = 0;
				_getch();
				break;
			}
			else {
				cout << ">>�ٽ� �Է����ּ���\n>>";
				_getch();
				continue;
			}
		}
		else {
			cout << ">>�������� ���";
			_getch();
			break;
		}
	}
	system("cls");
	cout << ">>Ž�縦 ���� ����� �����ϼ���.\n";
	while (1) {
		if (p[1]->ShowState(1) > 0) {
			cout << ">>�����Ͼ Ž�翡 �����ðڽ��ϱ�?\n";
			cout << "  1. ��    2. �ƴϿ�\n>>";
			cin >> n;
			if (n == 1) {
				cout << "\n�����Ͼ �����ϼ̽��ϴ�.\n";
				ExploreMember2 = 1;
				_getch();
				break;
			}
			else if (n == 2) {
				cout << "\n�����Ͼ ������ �ʽ��ϴ�.\n";
				ExploreMember2 = 0;
				_getch();
				break;
			}
			else {
				cout << ">>�ٽ� �Է����ּ���\n>>";
				_getch();
				continue;
			}
		}
		else {
			cout << ">>�����Ͼ� ���";
			_getch();
			break;
		}
	}
	system("cls");
	cout << ">>Ž�縦 ���� ����� �����ϼ���.\n";
	while (1) {
		if (p[2]->ShowState(1) > 0) {
			cout << ">>�ǻ縦 Ž�翡 �����ðڽ��ϱ�?\n";
			cout << "  1. ��    2. �ƴϿ�\n>>";
			cin >> n;
			if (n == 1) {
				cout << "\n�ǻ縦 �����ϼ̽��ϴ�.\n";
				ExploreMember3 = 1;
				_getch();
				break;
			}
			else if (n == 2) {
				cout << "\n�ǻ縦 ������ �ʽ��ϴ�.\n";
				ExploreMember3 = 0;
				_getch();
				break;
			}
			else {
				cout << ">>�ٽ� �Է����ּ���\n>>";
				_getch();
				continue;
			}
		}
		else {
			cout << ">>�ǻ� ���";
			_getch();
			break;
		}
	}
	system("cls");
	cout << ">>Ž�縦 ���� ����� �����ϼ���.\n";
	while (1) {
		if (p[3]->ShowState(1) > 0) {
			cout << ">>������ Ž�翡 �����ðڽ��ϱ�?\n";
			cout << "1. ��    2. �ƴϿ�\n>>";
			cin >> n;
			if (n == 1) {
				cout << "������ �����ϼ̽��ϴ�.\n";
				ExploreMember4 = 1;
				_getch();
				break;
			}
			else if (n == 2) {
				cout << "\n������ ������ �ʽ��ϴ�.\n";
				ExploreMember4 = 0;
				_getch();
				break;
			}
			else {
				cout << ">>�ٽ� �Է����ּ���\n>>";
				_getch();
				continue;
			}
		}
		else {
			cout << ">>���� ���";
			_getch();
			break;
		}
	}
	system("cls");
	cout << "�༺���� Ž�縦 ���� ������ : ";
	if (ExploreMember1 == 1) cout << "�������� ";
	if (ExploreMember2 == 1) cout << "�����Ͼ� ";
	if (ExploreMember3 == 1) cout << "�ǻ� ";
	if (ExploreMember4 == 1) cout << "���� ";
}
void SpaceShip::NoToExplore() {
	system("cls");
	cout << ">>�༺ Ž�縦 ���߰� �̷��ϰڽ��ϴ�...\n";
}
void SpaceShip::EventProbability() {   // 1/2 Ȯ���� good �Ǵ�bad �̺�Ʈ �߻�
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
	cout << ">>...���� ���� ���� ���� �͸� ����!\n";
	srand(time(NULL));
	if (rand() % 2 == 0) {
		srand(time(NULL));
		int plus_hp, plus_mental;
		plus_hp = rand() % 10;
		plus_mental = rand() % 10;
		cout << ">>�׶��� �̺�Ʈ �߻�!!\n";
		cout << ">>Ž��� ��� ü�� " << plus_hp << ", ���ŷ� " << plus_mental << "��(��) ������ϴ�.\n";
		if (ExploreMember1 == 1) {
			p[0]->HpControl(+plus_hp);  //ü��
			if (p[0]->ShowState(1) > p[0]->ShowMaxState(1))
			{
				p[0]->HpControl(-(p[0]->ShowState(1) - p[0]->ShowMaxState(1)));
			}
			p[0]->MentalControl(+plus_mental);  //��Ż
			if (p[0]->ShowState(3) > p[0]->ShowMaxState(3))
			{
				p[0]->MentalControl(-(p[0]->ShowState(3) - p[0]->ShowMaxState(3)));
			}
		}
		if (ExploreMember2 == 1) {
			p[1]->HpControl(+plus_hp);  //ü��
			if (p[1]->ShowState(1) > p[1]->ShowMaxState(1))
			{
				p[1]->HpControl(-(p[1]->ShowState(1) - p[1]->ShowMaxState(1)));
			}
			p[1]->MentalControl(+plus_mental);  //��Ż
			if (p[1]->ShowState(3) > p[1]->ShowMaxState(3))
			{
				p[1]->MentalControl(-(p[1]->ShowState(3) - p[1]->ShowMaxState(3)));
			}
		}
		if (ExploreMember3 == 1) {
			p[2]->HpControl(+plus_hp);  //ü��
			if (p[2]->ShowState(1) > p[2]->ShowMaxState(1))
			{
				p[2]->HpControl(-(p[2]->ShowState(1) - p[2]->ShowMaxState(1)));
			}
			p[2]->MentalControl(+plus_mental);  //��Ż
			if (p[2]->ShowState(3) > p[2]->ShowMaxState(3))
			{
				p[2]->MentalControl(-(p[2]->ShowState(3) - p[2]->ShowMaxState(3)));
			}
		}
		if (ExploreMember4 == 1) {
			p[3]->HpControl(+plus_hp);  //ü��
			if (p[3]->ShowState(1) > p[3]->ShowMaxState(1))
			{
				p[3]->HpControl(-(p[3]->ShowState(1) - p[3]->ShowMaxState(1)));
			}
			p[3]->MentalControl(+plus_mental);  //��Ż
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
		cout << ">>�ڿ� ǳ��\n";
		cout << ">>���� " << plus_food << ", ������" << plus_energy << "��(��) ������ϴ�.\n";
		_getch();
	}
}
void SpaceShip::BadEvent() {
	cout << ">>...���� �ұ��ϴ�... �ݹ��̶� ���� ���� ������ �͸� ����...\n";
	int minus_hp, minus_full, minus_mental;
	srand(time(NULL));
	if (rand() % 3 == 0) {
		srand(time(NULL));
		minus_hp = rand() % 10;
		minus_full = rand() % 10;
		minus_mental = rand() % 10;
		cout << ">>�ߵ� �̺�Ʈ �߻�!!\n";
		cout << ">>Ž��� ��� ü�� " << minus_hp << ", ��θ� " << minus_full << ", ���ŷ� " << minus_mental << "��(��) �Ҿ����ϴ�.\n";
		if (ExploreMember1 == 1) {
			p[0]->HpControl(-minus_hp);      //ü��
			p[0]->FullControl(-minus_full);    //����
			p[0]->MentalControl(-minus_mental);  //��Ż
		}
		if (ExploreMember2 == 1) {
			p[1]->HpControl(-minus_hp);      //ü��
			p[1]->FullControl(-minus_full);    //����
			p[1]->MentalControl(-minus_mental);  //��Ż
		}
		if (ExploreMember3 == 1) {
			p[2]->HpControl(-minus_hp);      //ü��
			p[2]->FullControl(-minus_full);    //����
			p[2]->MentalControl(-minus_mental);  //��Ż
		}
		if (ExploreMember4 == 1) {
			p[3]->HpControl(-minus_hp);      //ü��
			p[3]->FullControl(-minus_full);    //����
			p[3]->MentalControl(-minus_mental);  //��Ż
		}
		_getch();
	}
	else if (rand() % 3 == 1) {
		srand(time(NULL));
		minus_hp = rand() % 10;
		minus_mental = rand() % 10;
		cout << ">>���� �̺�Ʈ �߻�!!\n";
		cout << ">>Ž��� ��� ü�� " << minus_hp << ", ���ŷ� " << minus_mental << "��(��) �Ҿ����ϴ�.\n";
		if (ExploreMember1 == 1) {
			p[0]->HpControl(-minus_hp);      //ü��
			p[0]->MentalControl(-minus_mental);  //��Ż
		}
		if (ExploreMember2 == 1) {
			p[1]->HpControl(-minus_hp);      //ü��
			p[1]->MentalControl(-minus_mental);  //��Ż
		}
		if (ExploreMember3 == 1) {
			p[2]->HpControl(-minus_hp);      //ü��
			p[2]->MentalControl(-minus_mental);  //��Ż
		}
		if (ExploreMember4 == 1) {
			p[3]->HpControl(-minus_hp);      //ü��
			p[3]->MentalControl(-minus_mental);  //��Ż
		}
		_getch();
	}
	else {
		srand(time(NULL));
		minus_hp = rand() % 10 + 5;
		minus_full = rand() % 10;
		minus_mental = rand() % 10 + 2;
		cout << ">>���� �̺�Ʈ �߻�!!\n";
		cout << ">>Ž��� ��� ü�� " << minus_hp << ", ��θ� " << minus_full << ", ���ŷ� " << minus_mental << "��(��) �Ҿ����ϴ�.\n";
		if (ExploreMember1 == 1) {
			p[0]->HpControl(-minus_hp);      //ü��
			p[0]->FullControl(-minus_full);    //����
			p[0]->MentalControl(-minus_mental);  //��Ż
		}
		if (ExploreMember2 == 1) {
			p[1]->HpControl(-minus_hp);      //ü��
			p[1]->FullControl(-minus_full);    //����
			p[1]->MentalControl(-minus_mental);  //��Ż
		}
		if (ExploreMember3 == 1) {
			p[2]->HpControl(-minus_hp);      //ü��
			p[2]->FullControl(-minus_full);    //����
			p[2]->MentalControl(-minus_mental);  //��Ż
		}
		if (ExploreMember4 == 1) {
			p[3]->HpControl(-minus_hp);      //ü��
			p[3]->FullControl(-minus_full);    //����
			p[3]->MentalControl(-minus_mental);  //��Ż
		}
		_getch();
	}
}
//�߰���


void abuse_distroy_script() {
	system("cls");
	printf("  �ڿ��� ������ �̻�, ��ΰ� �����ϱ� �������.\n");
	printf("  �̷��� ����� �˰� �ְ�, ����������, �޾Ƶ��̱�� ����׿�.\n");
	printf("  ��ȹ�� �ֱ⿡ ����� �׷� ������ �ѰŰ���?\n");
	_getch();
}

void violence_selfinjury_script() {
	//���ش� ��ũ��Ʈ �����ϴ�~.
	//hp�� ����. 
}

void suicide_script() {
	system("cls");
	printf("  �ֱٵ�� �ῡ ��� ������.\n");
	printf("  �õ������� ���������� ����.\n");
	printf("  �ʹ� ���� �����־ �׷��ɱ��? \n");
	printf("  ��\n");
	printf("  ���� ������ ���࿬���̶�� ���� ����.\n\n\n");
	printf("  ������ �����ִ�.\n");
	printf("  �濡�� ��� Ž����� �����ִ�.\n");
	_getch();
}

void scientist_script1() {//���1 
	system("cls");
	printf(">>ĸƾ, �� ��ο� ���� �������� ���� ���� ���� �� ���ƿ�.\n  ���ϸ��� �츮�� ����� ã�� ���� ��ް� ������, ���� ������� �� �� ���� �� ������ ���ִ� ������ ����ϱ⸸ �ؿ�.\n");
	printf("  �츮�� �ڿ� ���� ��ġ�� �Ҿ���, ��Ե� ��Ƴ��� ���� �����ϰ� ������, �̰��� �󸶳� �� �̾����� ���ݾƿ�.\n  ��Ȯ�Ǽ��� �η��� �۽��� ä, ���� �ǹ̸� ã�Ⱑ ������ ��Ƴ׿�.\n");
	printf("  �츮 ���ڰ� �����ϴ� �渶�� � ��ǰ� ����� �������, �׷��� �츮�� ������ ���ư��߸� �ؿ�.\n  �� ��ο� ���ֿ��� ȥ�ڰ� �ƴ� ���� ���ΰ� ������, ���ÿ� �츮�� �����԰� ������� ���� �밨�ϰ� ������.\n");
	printf("  �� ��� ����� ��� �ӿ���, �츮�� ��� ���ϰ� ���� �� �������?\n  �̰��� ���̶��, �츮�� ������ �������� ���θ� �����ϰ� ������ �� �������?\n  �� ��ο� �������� �츮�� ������ ���� �� ������ �𸣰�����, �ּ��� ���ο��� ���� �Ǿ� �� �� �������?\n\n");
	Sleep(2000);
	printf("1. ������ ������ ��. ���⼭ �� �̻� ��������� ����, �츮�� �ް� �ִ� ����� �� �������� ��.\n   ��ΰ� �����������, �츮�� �Բ� ��Ƽ�� �־�.\n   ������ �� ���������� �𸣰�����, �츮�� ���� ��ġ�� � ��Ȳ������ �̰ܳ� �� �־�.\n");
	printf("2. ��Ұ� ������� �츮�� ���� ��ġ�� ������, �츮�� �Բ� �� ��ο� ���ֿ��� ���� ã�� ���� �ž�.\n   ��ΰ� ������ �ް� ������, �� �ӿ��� ������ ���� �� ���� �ž�.\n   �츮�� ����� ������ ��. �Բ���� �츮�� �����̵� �̰ܳ� �� �־�.\n");
}

void scientist_script2() {//���2 
	system("cls");
	printf(">>ĸƾ, �����帮�� ���� ���� ���ϰ� ���� �� �ֽ��ϴ�. �̰� ���� �ϼ���. Ȥ�ó� �𸣴ϱ��.\n");
	printf("  ĸƾ, �� ������ ������ ����������. �ڿ� ���� ��ġ�� �Ұ�, �츮�� �ұ����� ��Ȯ�Ǽ��� �ӿ��� ��ư��� �ֽ��ϴ�.\n  ���ڰ� ��� �������� ��������, � ������ ���� �𸣴� ���¿��� ��ư��� �� ������ ������.\n");
	printf("  �츮�� �̹� ���� ���� �Ҿ���, ������ �󸶳� ��ƿ �� �������� �������մϴ�.\n  �ڿ��� �����ϰ� ��Ȳ�� ��ȭ�ǰ� �־�, �� ��� ���� �츮���� ������ �δ��� �ְ� �ֽ��ϴ�.\n");
	printf("  ������, �̷� �Ͽ��� ȯ�濡���� ��ó�� ��Ʈ������ �� �������ϴ�.\n  �߳뵿�� �ڿ��� �ұ����� �츮�� ������, �ɸ��� �ǰ��� ��ȭ��ų �� �־��.\n  ĸƾ, �츮�� �̹� �Ѱ迡 �ٴٶ���, �� ��Ȳ�� �� �̻� ���ӵǱ� ������� �� �����ϴ�.\n");
	printf("  Ȥ�� �̷� ��Ȳ���� ��� �������, ��� ��ƿ���� ���� ��ȹ�� �ֳ���?\n  Ȥ�ó� �츮�� ���� ���ɼ��� ���� ������� ������ ��� �ٷ��� �����غ��̴ٸ�, ���� ������ �ּ���.\n\n");
	Sleep(2000);
	printf("1. ���� �����̾�. ���� ��Ȳ�� ����� ������, �츮�� ������ ���ο� ���ɼ��� ã�� ������ ���� �߿���.\n   �츮�� �̷� ����� ��Ȳ������ �Բ� �����ϰ� �������ָ鼭 ���ο��� ���� �Ǿ��� �� �ִٸ�, � ����� �غ��� �� ���� �ž�.\n   �� ���ư�, �츮�� �̷� ��Ȳ���� ���� �� �ִ� �͵鵵 �����غ��� ���� �� ����.\n   ������ ���������, �츮�� �� ��� �ӿ��� ���� ã�Ƴ� �� ���� �Ŷ� �Ͼ�.\n");
	printf("2. �¾�. ������ ����� ���ð� ����� ������ �־�.\n   ������ �츮�� ���� ���� ���ɼ��� ������ �ְ�, ������ ������ �ʰ� �ܰ��Ͽ� � ���̵� �س� �� ���� �ž�.\n   ��ΰ� ��ο� ��Ȳ���� ���� ã�� ���� �⿩�ϸ鼭 ���θ� �������ָ�, ����ġ ���� ��ȭ�� ����� ã�� �� ���� �ž�.\n   �츮�� �Բ� �ִٸ�, �� ��� �ӿ����� ���ο��� ����� �Ҿ��� ��� ���ذ� �� ���� �ž�.\n");
}

void engineer1_script1() {//���1 
	system("cls");
	printf(">>ĸƾ, �� ������ ������ �������̿���. �ڿ� ���� ��ġ�� �Ҿ����.\n  �׸��� �츮�� �ұ����� ��Ȯ�Ǽ� �ӿ��� ��ư��� �־��.\n");
	printf("  ���� �� ���� �������� �ʿ��ϰ�, �� �������� ȿ�������� ����ϴ� ����� ã�� �������.\n");
	printf("  �츮�� �̹� �ǰ��ϰ�, ��ģ �����Դϴ�. �̷� ���� �ӿ��� ���������Ⱑ ��ƴٴ� �� ������.\n");
	printf("  �ڿ��� ������ �� �׻� �������� �ʰ� �������� ������� ã�� ����ϴ�.\n");
	printf("  �츮�� �� �̻� �������� �̷� ��Ȳ���� ��ƿ �� �������? ��� �� �ʹ� ����ϴ�.\n");
	printf("  ���� ��ο� ���� �ӿ��� ��Ű� �ִ� �����̿���...\n\n");
	Sleep(2000);
	printf("1. ������ ��ο� ���� ������ �ֱ���. �� ������ ��������, �츮�� �̹� ���� ������� �غ��ؿԾ�.\n   ��� ���� ����� ������ �츮�� ������ ������ �巯���� ������. �Բ� ��Ƽ�� �� ������ �� �־�.\n");
	printf("2. �� ���� �¾�. �� ������ ���� ��Ӱ� �����. ������ �츮�� �̹� ���� ������ �̰ܳ°�,\n   �츮�� �γ��� �������� � ������̶� �غ��� �� ���� �ž�. �Բ� ���� ������ �� ������ �� �־�.\n");
}

void engineer1_script2() {//���2 
	system("cls");
	printf(">>ĸƾ, �̰� �� �� �߸��̿���. �ڿ� ���� ��ġ�� �Ҿ��� �� �� ���������� �߾��.\n");
	printf("  �������� ��ȸ������, �׶� ��� �߾�� �ߴ��� �����ϸ� ���� �ķ����� �ʾƿ�.\n\n");
	Sleep(2000); 
	printf("1. �츮�� �̹� ����� ��Ȳ�� ó���־�. �� �߸��� �ƴ� �츮 ����� ������.\n   ��å���� ���� �Բ� �ذ�å�� ã�ƺ���.\n");
	printf("2. �ʹ� ��å���� ��. �� ������ ��ΰ� ������ �� ���� ���̾���.\n   �������� �ڵ��ƺ��� �ͺ��� ������ ��� ������� �����غ���.\n");
}

void doctor_script1() {//���1 
	system("cls");
	printf(">>ĸƾ, �� ������ ������ �������̿���. �ڿ� ���� ��ġ�� �Ҿ����.\n  �׸��� �츮�� �ұ����� ��Ȯ�Ǽ� �ӿ��� ��ư��� �־��.\n");
	printf("  ���� �� ���� �������� �ʿ��ϰ�, �� �������� ȿ�������� ����ϴ� ����� ã�� �������.\n");
	printf("  �츮�� �̹� �ǰ��ϰ�, ��ģ �����Դϴ�. �̷� ���� �ӿ��� ���������Ⱑ ��ƴٴ� �� ������.\n");
	printf("  �ڿ��� ������ �� �׻� �������� �ʰ� �������� ������� ã�� ����ϴ�.\n");
	printf("  �츮�� �� �̻� �������� �̷� ��Ȳ���� ��ƿ �� �������? ��� �� �ʹ� ����ϴ�.\n");
	printf("  ���� ��ο� ���� �ӿ��� ��Ű� �ִ� �����̿���...\n\n");
	Sleep(2000);
	printf("1. ������ ��ο� ���� ������ �ֱ���. �� ������ ��������, �츮�� �̹� ���� ������� �غ��ؿԾ�.\n   ��� ���� ����� ������ �츮�� ������ ������ �巯���� ������. �Բ� ��Ƽ�� �� ������ �� �־�.\n");
	printf("2. �� ���� �¾�. �� ������ ���� ��Ӱ� �����. ������ �츮�� �̹� ���� ������ �̰ܳ°�,\n   �츮�� �γ��� �������� � ������̶� �غ��� �� ���� �ž�. �Բ� ���� ������ �� ������ �� �־�.\n");
}

void doctor_script2() {//���2
	system("cls");
	printf(">>ĸƾ, �� ��ο� ���� �������� ���� ���� ���� �� ���ƿ�.\n  ���ϸ��� �츮�� ����� ã�� ���� ��ް� ������, ���� ������� �� �� ���� �� ������ ���ִ� ������ ����ϱ⸸ �ؿ�.\n");
	printf("  �츮�� �ڿ� ���� ��ġ�� �Ҿ���, ��Ե� ��Ƴ��� ���� �����ϰ� ������, �̰��� �󸶳� �� �̾����� ���ݾƿ�.\n  ��Ȯ�Ǽ��� �η��� �۽��� ä, ���� �ǹ̸� ã�Ⱑ ������ ��Ƴ׿�.\n");
	printf("  �츮 ���ڰ� �����ϴ� �渶�� � ��ǰ� ����� �������, �׷��� �츮�� ������ ���ư��߸� �ؿ�.\n  �� ��ο� ���ֿ��� ȥ�ڰ� �ƴ� ���� ���ΰ� ������, ���ÿ� �츮�� �����԰� ������� ���� �밨�ϰ� ������.\n");
	printf("  �� ��� ����� ��� �ӿ���, �츮�� ��� ���ϰ� ���� �� �������?\n  �̰��� ���̶��, �츮�� ������ �������� ���θ� �����ϰ� ������ �� �������?\n  �� ��ο� �������� �츮�� ������ ���� �� ������ �𸣰�����, �ּ��� ���ο��� ���� �Ǿ� �� �� �������?\n\n");
	Sleep(2000);
	printf("1. ������ ������ ��. ���⼭ �� �̻� ��������� ����, �츮�� �ް� �ִ� ����� �� �������� ��.\n   ��ΰ� �����������, �츮�� �Բ� ��Ƽ�� �־�.\n   ������ �� ���������� �𸣰�����, �츮�� ���� ��ġ�� � ��Ȳ������ �̰ܳ� �� �־�.\n");
	printf("2. ��Ұ� ������� �츮�� ���� ��ġ�� ������, �츮�� �Բ� �� ��ο� ���ֿ��� ���� ã�� ���� �ž�.\n   ��ΰ� ������ �ް� ������, �� �ӿ��� ������ ���� �� ���� �ž�.\n   �츮�� ����� ������ ��. �Բ���� �츮�� �����̵� �̰ܳ� �� �־�.\n");
}

void army_script1() {//���1 
	system("cls");
	printf(">>ĸƾ, �����帮�� ���� ���� ���ϰ� ���� �� �ֽ��ϴ�. �̰� ���� �ϼ���. Ȥ�ó� �𸣴ϱ��.\n");
	printf("  ĸƾ, �� ������ ������ ����������. �ڿ� ���� ��ġ�� �Ұ�, �츮�� �ұ����� ��Ȯ�Ǽ��� �ӿ��� ��ư��� �ֽ��ϴ�.\n  ���ڰ� ��� �������� ��������, � ������ ���� �𸣴� ���¿��� ��ư��� �� ������ ������.\n");
	printf("  �츮�� �̹� ���� ���� �Ҿ���, ������ �󸶳� ��ƿ �� �������� �������մϴ�.\n  �ڿ��� �����ϰ� ��Ȳ�� ��ȭ�ǰ� �־�, �� ��� ���� �츮���� ������ �δ��� �ְ� �ֽ��ϴ�.\n");
	printf("  ������, �̷� �Ͽ��� ȯ�濡���� ��ó�� ��Ʈ������ �� �������ϴ�.\n  �߳뵿�� �ڿ��� �ұ����� �츮�� ������, �ɸ��� �ǰ��� ��ȭ��ų �� �־��.\n  ĸƾ, �츮�� �̹� �Ѱ迡 �ٴٶ���, �� ��Ȳ�� �� �̻� ���ӵǱ� ������� �� �����ϴ�.\n");
	printf("  Ȥ�� �̷� ��Ȳ���� ��� �������, ��� ��ƿ���� ���� ��ȹ�� �ֳ���?\n  Ȥ�ó� �츮�� ���� ���ɼ��� ���� ������� ������ ��� �ٷ��� �����غ��̴ٸ�, ���� ������ �ּ���.\n\n");
	Sleep(2000);
	printf("1. ���� �����̾�. ���� ��Ȳ�� ����� ������, �츮�� ������ ���ο� ���ɼ��� ã�� ������ ���� �߿���.\n   �츮�� �̷� ����� ��Ȳ������ �Բ� �����ϰ� �������ָ鼭 ���ο��� ���� �Ǿ��� �� �ִٸ�, � ����� �غ��� �� ���� �ž�.\n   �� ���ư�, �츮�� �̷� ��Ȳ���� ���� �� �ִ� �͵鵵 �����غ��� ���� �� ����.\n   ������ ���������, �츮�� �� ��� �ӿ��� ���� ã�Ƴ� �� ���� �Ŷ� �Ͼ�.\n");
	printf("2. �¾�. ������ ����� ���ð� ����� ������ �־�.\n   ������ �츮�� ���� ���� ���ɼ��� ������ �ְ�, ������ ������ �ʰ� �ܰ��Ͽ� � ���̵� �س� �� ���� �ž�.\n   ��ΰ� ��ο� ��Ȳ���� ���� ã�� ���� �⿩�ϸ鼭 ���θ� �������ָ�, ����ġ ���� ��ȭ�� ����� ã�� �� ���� �ž�.\n   �츮�� �Բ� �ִٸ�, �� ��� �ӿ����� ���ο��� ����� �Ҿ��� ��� ���ذ� �� ���� �ž�.\n");
}

void army_script2() {//���2 
	system("cls");
	printf(">>ĸƾ, �̰� �� �� �߸��̿���. �ڿ� ���� ��ġ�� �Ҿ��� �� �� ���������� �߾��.\n");
	printf("  �������� ��ȸ������, �׶� ��� �߾�� �ߴ��� �����ϸ� ���� �ķ����� �ʾƿ�.\n\n");
	Sleep(2000);
	printf("1. �츮�� �̹� ����� ��Ȳ�� ó���־�. �� �߸��� �ƴ� �츮 ����� ������.\n   ��å���� ���� �Բ� �ذ�å�� ã�ƺ���.\n");
	printf("2. �ʹ� ��å���� ��. �� ������ ��ΰ� ������ �� ���� ���̾���.\n   �������� �ڵ��ƺ��� �ͺ��� ������ ��� ������� �����غ���.\n");
}

void SpaceShip::abuse_distroy_panic_event(int i) {//���� �ı� �̺�Ʈ ��ũ��Ʈ �� �� 
	int random;
	srand(time(NULL));
	random = rand() % 100;

	if (p[i]->ShowState(3) < 40) {//��Ż�� 40���ϸ� 
		if (random >= 0 && random < p[i]->EventPercent(0)) {
			abuse_distroy_script();//?%�� �ش� �̺�Ʈ �߻�. 
			p[i]->HpControl(-3);
		}

	}
}

void SpaceShip::violence_selfinjury_panic_event(int i) {//����, ���� �̺�Ʈ ��ũ��Ʈ �Լ� 
	int random;
	srand(time(NULL));
	random = rand() % 100;

	if (p[i]->ShowState(3) < 20) {//��Ż�� 20���ϸ�  
		if (random >= 0 && random < p[i]->EventPercent(0)) {
			violence_selfinjury_script();//?%�� �ش� �̺�Ʈ �߻�. 
			p[i]->HpControl(-10);
		}
	}
}

void SpaceShip::suicide_panic_event(int i) {//�ڻ� �̺�Ʈ ��ũ��Ʈ �Լ� 
	int random;
	srand(time(NULL));
	random = rand() % 100;

	if (p[i]->ShowState(3) < 10) {//��Ż�� 10���ϸ� 
		if (random >= 0 && random < p[i]->EventPercent(0)) {
			suicide_script();//?%�� �ش� �̺�Ʈ �߻�. 
			p[i]->HpControl(-100);
		}
	}
}

void SpaceShip::scientist_script() {
	//���� ����� ���� ������ 
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

			if (result == 1) { // ���������� ������ �Է¹��� ���
				if (choose == 1) {
					printf(">>1 ����");
					p[i]->MentalControl(5);
					break;
				}
				else if (choose == 2) {
					printf(">>2 ����");
					p[i]->MentalControl(-5);
					abuse_distroy_panic_event(i);
					break;
				}
				else {
					printf(">>�߸��� �Է��Դϴ�.\n");
				}
			}
			else {
				printf(">>���ڰ� �ƴ� �Է��Դϴ�. �ٽ� �õ��ϼ���.\n");
				// �Է� ���۸� ����
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

			if (result == 1) { // ���������� ������ �Է¹��� ���
				if (choose == 1) {
					printf(">>1 ����");
					p[i]->MentalControl(5);
					break;
				}
				else if (choose == 2) {
					printf(">>2 ����");
					p[i]->MentalControl(-5);
					abuse_distroy_panic_event(i);
					break;
				}
				else {
					printf(">>�߸��� �Է��Դϴ�.\n");
				}
			}
			else {
				printf(">>���ڰ� �ƴ� �Է��Դϴ�. �ٽ� �õ��ϼ���.\n");
				// �Է� ���۸� ����
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

			if (result == 1) { // ���������� ������ �Է¹��� ���
				if (choose == 1) {
					printf(">>1 ����");
					p[i]->MentalControl(-5);
					abuse_distroy_panic_event(i);
					break;
				}
				else if (choose == 2) {
					printf(">>2 ����");
					p[i]->MentalControl(5);
					break;
				}
				else {
					printf(">>�߸��� �Է��Դϴ�.\n");
				}
			}
			else {
				printf(">>���ڰ� �ƴ� �Է��Դϴ�. �ٽ� �õ��ϼ���.\n");
				// �Է� ���۸� ����
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

			if (result == 1) { // ���������� ������ �Է¹��� ���
				if (choose == 1) {
					printf(">>1 ����");
					p[i]->MentalControl(5);
					break;
				}
				else if (choose == 2) {
					printf(">>2 ����");
					p[i]->MentalControl(-5);
					abuse_distroy_panic_event(i);
					break;
				}
				else {
					printf(">>�߸��� �Է��Դϴ�.\n");
				}
			}
			else {
				printf(">>���ڰ� �ƴ� �Է��Դϴ�. �ٽ� �õ��ϼ���.\n");
				// �Է� ���۸� ����
				while (getchar() != '\n');
			}
		}
		return;
	}
	_getch();
}

void SpaceShip::doctor_script() {
	//���� ������ ���� ������ 
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

			if (result == 1) { // ���������� ������ �Է¹��� ���
				if (choose == 1) {
					printf(">>1 ����");
					p[i]->MentalControl(-5);
					abuse_distroy_panic_event(i);
					break;
				}
				else if (choose == 2) {
					printf(">>2 ����");
					p[i]->MentalControl(5);
					break;
				}
				else {
					printf(">>�߸��� �Է��Դϴ�.\n");
				}
			}
			else {
				printf(">>���ڰ� �ƴ� �Է��Դϴ�. �ٽ� �õ��ϼ���.\n");
				// �Է� ���۸� ����
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

			if (result == 1) { // ���������� ������ �Է¹��� ���
				if (choose == 1) {
					printf(">>1 ����");
					p[i]->MentalControl(5);
					break;
				}
				else if (choose == 2) {
					printf(">>2 ����");
					p[i]->MentalControl(-5);
					abuse_distroy_panic_event(i);
					break;
				}
				else {
					printf(">>�߸��� �Է��Դϴ�.\n");
				}
			}
			else {
				printf(">>���ڰ� �ƴ� �Է��Դϴ�. �ٽ� �õ��ϼ���.\n");
				// �Է� ���۸� ����
				while (getchar() != '\n');
			}
		}
		return;
	}
	_getch();
}

void SpaceShip::army_script() {
	//���� ���� ���� ������
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

			if (result == 1) { // ���������� ������ �Է¹��� ���
				if (choose == 1) {
					printf(">>1 ����");
					p[i]->MentalControl(5);
					break;
				}
				else if (choose == 2) {
					printf(">>2 ����");
					p[i]->MentalControl(-5);
					abuse_distroy_panic_event(i);
					break;
				}
				else {
					printf(">>�߸��� �Է��Դϴ�.\n");
				}
			}
			else {
				printf(">>���ڰ� �ƴ� �Է��Դϴ�. �ٽ� �õ��ϼ���.\n");
				// �Է� ���۸� ����
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

			if (result == 1) { // ���������� ������ �Է¹��� ���
				if (choose == 1) {
					printf(">>1 ����");
					p[i]->MentalControl(-5);
					abuse_distroy_panic_event(i);
					break;
				}
				else if (choose == 2) {
					printf(">>2 ����");
					p[i]->MentalControl(5);
					break;
				}
				else {
					printf(">>�߸��� �Է��Դϴ�.\n");
				}
			}
			else {
				printf(">>���ڰ� �ƴ� �Է��Դϴ�. �ٽ� �õ��ϼ���.\n");
				// �Է� ���۸� ����
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
		//������ ���� ������
		printf(">>��� Ž����� ��ȭ�ð��� ������?\n");
		if (p[0]->ShowState(1) > 0 && p[0]->ShowState(flag) == 0) { //����ִ� �ֵ鸸 �������� �߰� 
			printf("1. ��������\n");
		}
		else {
			printf("?. ��ˢǢ�\n");
		}
		if (p[1]->ShowState(1) > 0 && p[1]->ShowState(flag) == 0) {
			printf("2. �����Ͼ�\n");
		}
		else {
			printf("?. �ˡ�Ǣ�\n");
		}
		if (p[2]->ShowState(1) > 0 && p[2]->ShowState(flag) == 0) {
			printf("3. �ǻ�\n");
		}
		else {
			printf("?. ���\n");
		}
		if (p[3]->ShowState(1) > 0 && p[3]->ShowState(flag) == 0) {
			printf("4. ����\n");
		}
		else {
			printf("?. �Ǣ�\n");
		}
		printf(">>");
		scanf("%d", &ib);

		switch (ib) {
		case 1:
			if (p[0]->ShowState(flag) == 1) {
				system("cls");
				cout << "  [���������� ����ġ ��ȭ�� �Ϸ�Ǿ����ϴ�.]\n\n";
				i--;
				_getch();
				break;
			}
			scientist_script();//��ũ��Ʈ ��� 
			p[0]->SetTalkFlag(1);//�Ϸ� �ѹ� ��ȭ���� ���� ������ �ٽ� ����. 
			break;
		case 2:
			if (p[1]->ShowState(flag) == 1) {
				system("cls");
				cout << "  [�����Ͼ��� ����ġ ��ȭ�� �Ϸ�Ǿ����ϴ�.]\n\n";
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
				cout << "  [�ǻ��� ����ġ ��ȭ�� �Ϸ�Ǿ����ϴ�.]\n\n";
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
				cout << "  [������ ����ġ ��ȭ�� �Ϸ�Ǿ����ϴ�.]\n\n";
				i--;
				_getch();
				break;
			}
			army_script();
			p[3]->SetTalkFlag(1);
			break;
		default:
			printf(">>�Է��� �߸��Ǿ����ϴ�. ex: 1");
			while (getchar() != '\n');
			i--;
			_getch();
		}

	}
	flag = 0;
	for (int j = 0; j < 4; j++) {
		p[j]->SetTalkFlag(0);//�Ϸ� ������ �ٽ� �÷��� 0���� ����. 
	}
	violence_selfinjury_panic_event(random);
	cout << ">>Ž��� ��� ����� �Ϸ��߽��ϴ�.\n";
}

void SpaceShip::Game() {
	int e = 0;
	int tDay = 0;
	StartUI(); 
	while (1) {
		e = StartDay();
		if (e != 0) { //�ڿ� ����, �ƻ� ���� 
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
		if (explore == 1) { //�༺ Ž�縦 �ϴ� ��� 
		   //for(int i = 0; i < planetList[0].ShowIntState(1); i++){
		   //   �ϼ��� ���� ��� ��
		   //   ���� ���� �Ѿ(if ������ �װų� ���ŷ� �������� ��ġ�� �� ���� �̺�Ʈ�� �ִٸ� �̺�Ʈ ȭ�鵵 ���)
		   //}
		   //�����ϸ� Ž�� �ο� ����
		   //�༺ ���� �����ְ� Ž���� ����? ����
		   //Ž�� ��� ������
		   //���� ���� �Ѿ(if ������ �װų� ���ŷ� �������� ��ġ�� �� ���� �̺�Ʈ�� �ִٸ� �̺�Ʈ ȭ�鵵 ���)
			
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

void SpaceShip::PrintInformation() { //"���� ����" �Է� �� ��µǴ� ���� 
   //�� ��, ���� �༺ ��, Ž�缱 ����, ��ü ���� lv, ����� ü��, ��θ� ��� 
	system("cls");
	cout << ">>��� �� " << day << "�� ���\n";
	cout << ">>���� �ڿ� | ������: " << energy << " ����: " << food << "\n";
	cout << ">>Ž���� �༺ ��: " << exploredPlanet << "��\n";
	cout << ">>�� ��ü ���� ���� ����\n";
	for (int i = 0; i < 5; i++) cout << "  " << r[i]->ShowName() << ": " << r[i]->ShowLv() << "Lv\n";
	cout << ">>�� Ž��� ����\n";
	for (int i = 0; i < 4; i++) cout << "  " << p[i]->ShowJob() << " | ü��: " << p[i]->ShowState(1) << "/" << p[i]->ShowMaxState(1) << " ��θ� ��ġ: " << p[i]->ShowState(2) << "/" << p[i]->ShowMaxState(2) << " ���ŷ�: " << p[i]->ShowState(3) << "/" << p[i]->ShowMaxState(3) << "\n";
	_getch();
}

void SpaceShip::PrintEnding(int e) {
	if (e == 1) { //���� �̾� ���� ��� 
		system("cls");
		cout << "  >>��� �������� �Һ�Ǿ����ϴ�." << endl;
		Sleep(1000);
		cout << "  >>Ž����� ������ ���̻� �Ұ����ϴٰ� �Ǵ�." << endl;
		Sleep(1000);
		cout << "  >>��� ���� ���� Ž����鿡�� �ȶ��� �� �๰. �ۺ�Ż�� �����մϴ�." << endl << endl;
		Sleep(1000);
		cout << "  >>Ž����� �ý��� ���� ���� ��Ż." << endl << endl;
		Sleep(2500);
		cout << "  ��" << endl;
		Sleep(2500);
		cout << "  ��" << endl;
		Sleep(2500);
		cout << "  ��" << endl << endl;
		Sleep(2500);
		cout << "   >>���ð��η� ��� Ž����� ����߽��ϴ�. �̿����� ���� ���� ������ �����ϰڽ��ϴ�." << endl << endl;
		Sleep(1000);
		cout << "   >>Ž�缱�� ����� ��������� ������ �����" << endl;
		Sleep(1000);
		cout << "   >>Ž������� ��ȭ ������" << endl;
		Sleep(1000);
		cout << "   >>�߿�����ġ�� ���� �ߡ�" << endl << endl;
		Sleep(2500);
		cout << "   >>������ �Ϸ�Ǿ����ϴ�." << endl << endl;
		Sleep(1000);
		cout << "   [��� Ž����� ����Կ� ���� ������ ȣ �ý��� ���� AI�� �������� ��ȯ�մϴ١�]" << endl << endl;
		Sleep(1000);
		cout << "   [��ȯ�ߡ�]" << endl << endl;
		Sleep(2500);
		cout << "   [�ڵ� Ž���带 �����մϴ١�]" << endl;
		Sleep(1000);
		cout << "   [���� ������ ���Ͽ� ���ο� ���� �߰߱��� ������ ���� Ž�簡 ����Ǹ�, �߰� �� ������ ȣ �ý��� ���� AI�� ������尡 �����˴ϴ١�]" << endl << endl;
		Sleep(1000);
		cout << "         Ending..." << endl;
		_getch();

	}
	else if (e == 2) { //��� ���� ���� ��� 
		system("cls");
		cout << "   >>���ð��η� ��� Ž����� ����߽��ϴ�. �̿����� ������ Ž�������� �ۼ��ϰڽ��ϴ�." << endl << endl;
		Sleep(1000);
		cout << "   >>Ž�缱�� ����� ��������� ������ �����" << endl;
		Sleep(1000);
		cout << "   >>Ž������� ��ȭ ������" << endl;
		Sleep(1000);
		cout << "   >>�߿�����ġ�� ���� �ߡ�" << endl << endl;
		Sleep(2500);
		cout << "   >>������ �Ϸ�Ǿ����ϴ�." << endl << endl;
		Sleep(1000);
		cout << "   [��� Ž����� ����Կ� ���� ������ ȣ �ý��� ���� AI�� �������� ��ȯ�մϴ١�]" << endl << endl;
		Sleep(1000);
		cout << "   [��ȯ�ߡ�]" << endl << endl;
		Sleep(2500);
		cout << "   [�ڵ� Ž���带 �����մϴ١�]" << endl;
		Sleep(1000);
		cout << "   [���� ������ ���Ͽ� ���ο� ���� �߰߱��� ������ ���� Ž�簡 ����Ǹ�, �߰� �� ������ ȣ �ý��� ���� AI�� ������尡 �����˴ϴ١�]" << endl << endl;
		Sleep(1000);
		cout << "         Ending..." << endl;
		_getch();
	}
	else { //�� ������ ã�� ���� ��� 
		system("cls");
		cout << "  ������ ȣ�� ������ ������ �´ڶ߷�����, " << endl;
		Sleep(1000);
		cout << "  ���ο� ������ ã�Ƴ��� ������ �ٰ��Խ��ϴ�." << endl << endl;
		Sleep(1000);
		cout << "  Ž������� ���� ���� ���� ���� ����� �ε�������," << endl;
		Sleep(1000);
		cout << "  �׵��� ���� ������� ������ ȣ�� ��ħ�� ��ǥ�� �޼��߽��ϴ�." << endl << endl;
		Sleep(1000);
		cout << "  Ž����� ������ �о߿��� ���ο� ������ ��ô�ϴ�, ���ο� ������ �����߽��ϴ�." << endl << endl;
		Sleep(2500);
		cout << "  ." << endl;
		Sleep(2500);
		cout << "  ." << endl;
		Sleep(2500);
		cout << "  ." << endl << endl;
		Sleep(2500);
		cout << "   [�޸𸮾� ����]" << endl << endl;
		Sleep(1000);
		cout << "   ������ �߰� ����� ������ �ҷ��ɴϴ�." << endl << endl;
		Sleep(1000);
		cout << "   �ε��ߡ�" << endl << endl;
		Sleep(2500);
		cout << "   ������ ����մϴ�." << endl << endl;
		Sleep(1000);
		cout << "   ������ �η��� ���ο� �������� �ٽ� ������ ��ȸ�� ������ϴ�.��" << endl;
		Sleep(2000);
		cout << "   ����ΰ� �⿩�� ��°� ����� ����帳�ϴ�.��" << endl;
		Sleep(2000);
		cout << "   ������ �츮�� �Բ� �� ���� ��ô�ϰ� ���ο� ���� ��ư� ���Դϴ�.��" << endl << endl;
		Sleep(2000);
		cout << "   �����ο� ������ ���� ���� ȯ���մϴ�!��" << endl << endl;
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
