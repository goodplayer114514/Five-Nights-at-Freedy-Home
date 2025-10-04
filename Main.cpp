#include"Game.h"
using namespace std;
#define Cam_width 1600
#define Cam_height 900
#define Mrjay_room room_num[Mrjay.listroom[Mrjay.Re_i()]]
#define MrLam_room room_num[MrLam.listroom[MrLam.Re_i()]]
#define Cheems_room room_num[Cheems.listroom[Cheems.Re_i()]]
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)
#define NUM_FLASH 100
int Flash_num=0;
UI newga(0, 300, 300, 70);
UI con(0, 450, 300, 70);
UI exiti(0, 640, 100, 70);
IMAGE MIAN, Continue, newgame, exitt;
room room_num[6];
IMAGE night[5];
IMAGE you[8];
IMAGE way, nosing;
bool startmian = true;
ExMessage keyborad;
MOUSEMSG mouse;
UI A1(1309, 511, 47, 30);
UI A2(1446, 509, 43, 20);
UI A3(1376, 548, 38, 30);
UI A4(1316, 636, 36, 30);
UI A5(1374, 635, 36, 30);
UI A6(1447, 637, 36, 30);
UI button(800, 820, 800, 80);
UI button1(0, 820, 800, 80);
Athor Mrjay;
Athor MrLam;
Athor Cheems;
bool live = true, LockDoor = false;
string word = " ";
int day = 0;
UI Room_A[6];
vector<Xue> listXue;
IMAGE Kill[5];
int hour;
int time_hour;
IMAGE mMask;
IMAGE buttonMask[2];
//thread GetKey;
IMAGE cheems_cat;
IMAGE Soc[5];
int Soc_i;
int cheems[5] = {
	120,
	60,
	30,
	25,
	10
};
int Jay[5] = {
	180,
	120,
	40,
	25,
	20
};
int Lam[5] = {
	120,
	80,
	50,
	40,
	30
};

void win() {
	PlaySound(NULL, NULL, NULL);
	IMAGE win;
	loadimage(&win, L"res//win1.jpg", 1600, 900);
	PlaySound(L"music\\clock.wav", NULL, SND_ASYNC | SND_FILENAME);
	putimage(0, 0, &win);
	Sleep(1000);
	loadimage(&win, L"res//win2.jpg", 1600, 900);
	PlaySound(L"music\\clock.wav", NULL, SND_ASYNC | SND_FILENAME);
	putimage(0, 0, &win);
	Sleep(1000);
	loadimage(&win, L"res//win3.jpg", 1600, 900);
	PlaySound(L"music\\clock.wav", NULL, SND_ASYNC | SND_FILENAME);
	putimage(0, 0, &win);
	Sleep(1000);
	loadimage(&win, L"res//win4.jpg", 1600, 900);
	PlaySound(L"music\\clock.wav", NULL, SND_ASYNC | SND_FILENAME);
	putimage(0, 0, &win);
	Sleep(1000);
	loadimage(&win, L"res//win5.jpg", 1600, 900);
	PlaySound(L"music\\clock.wav", NULL, SND_ASYNC | SND_FILENAME);
	putimage(0, 0, &win);
	Sleep(1000);
	PlaySound(NULL, NULL, NULL);
}
void deadorlive() {
	if (Mrjay.ReJump()) {
		clearcliprgn();
		PlaySound(L"music\\Jay跳杀.wav", NULL, SND_ASYNC | SND_FILENAME);
		putimage(0, 0, &Kill[0]);
		Sleep(1000);
		putimage(0, 0, &Kill[1]);
		Sleep(1000);
		putimage(0, 0, &Kill[2]);
		Sleep(100);
		clearcliprgn();
		live = false;
	}
	else if (MrLam.ReJump()) {
		clearcliprgn();
		PlaySound(L"music\\Lam跳杀.wav", NULL, SND_ASYNC | SND_FILENAME);
		putimage(0, 0, &Kill[3]);
		Sleep(1000);
		clearcliprgn();
		live = false;
	}
	else if (Cheems.ReJump()) {
		clearcliprgn();
		PlaySound(L"music\\cheems.wav", NULL, SND_ASYNC | SND_FILENAME);
		putimage(0, 0, &Kill[4]);
		Sleep(6000);
		clearcliprgn();
		live = false;
	}
}
void initXue() {
	Xue xue;
	listXue.clear();
	for (int i = 0; i < 900; i++) {
		xue.x = RE_RANDOM(1600);
		xue.y = RE_RANDOM(900);
		listXue.push_back(xue);
	}
}
void PRINT() {
	for (int i = 0; i < listXue.size(); i++) {
		listXue[i].print();
	}
}
void initroom() {
	Room_A[0] = A1;
	Room_A[1] = A2;
	Room_A[2] = A3;
	Room_A[3] = A4;
	Room_A[4] = A5;
	Room_A[5] = A6;
}
void Re_list() {
	for (int i = 0; i < 6; i++) {
		room_num[i].IsOntheRoom = false;
	}
	Mrjay_room.IsOntheRoom = true;
	MrLam_room.IsOntheRoom = true;
	Cheems_room.IsOntheRoom = true;
}
void JayAI(int a) {
	if (Mrjay.timming(a)) {
		//room_num[Mrjay.listroom[Mrjay.Re_i()]].IsOntheRoom = false;
		Mrjay.move(true);
		Mrjay.mtime = time(NULL);
		//room_num[Mrjay.listroom[Mrjay.Re_i()]].IsOntheRoom = true;
		PlaySound(L"music//脚步声.wav", NULL, SND_ASYNC | SND_FILENAME);
	}
}
void LamAI(int a) {
	if (MrLam.timming(a)) {
		//room_num[MrLam.listroom[MrLam.Re_i()]].IsOntheRoom = false;
		MrLam.move(true);
		MrLam.mtime = time(NULL);
		//room_num[MrLam.listroom[MrLam.Re_i()]].IsOntheRoom = true;
		PlaySound(L"music//脚步声.wav", NULL, SND_ASYNC | SND_FILENAME);
	}
}
void CheemsAI(int a) {
	if (Cheems.timming(a)) {
		//room_num[Cheems.listroom[Cheems.Re_i()]].IsOntheRoom = false;
		Cheems.move(true);
		Cheems.mtime = time(NULL);
		//room_num[Cheems.listroom[Cheems.Re_i()]].IsOntheRoom = true;
		PlaySound(L"music//脚步声.wav", NULL, SND_ASYNC | SND_FILENAME);
	}
}
void init() {
	Mrjay.listroom.push_back(0); Mrjay.listroom.push_back(2); Mrjay.listroom.push_back(3);
	MrLam.listroom.push_back(1); MrLam.listroom.push_back(2); MrLam.listroom.push_back(5);
	Cheems.listroom.push_back(2); Cheems.listroom.push_back(4);
	loadimage(&MIAN, L"res\\Main.jpg", 1600, 900);
	loadimage(&Continue, L"res\\continue.png", 1000, 400);
	loadimage(&newgame, L"res\\newgame.png", 1000, 400);
	loadimage(&exitt, L"res\\exit.png", 1000, 400);
	loadimage(&night[0], L"res\\night1.jpg", 1600, 900);
	loadimage(&night[1], L"res\\night2.jpg", 1600, 900);
	loadimage(&night[2], L"res\\night3.jpg", 1600, 900);
	loadimage(&night[3], L"res\\night4.jpg", 1600, 900);
	loadimage(&night[4], L"res\\night5.jpg", 1600, 900);
	loadimage(&you[0], L"res\\yourroom_1.jpg", 1600, 900);
	loadimage(&you[1], L"res\\yourroom_2.jpg", 1600, 900);
	loadimage(&way, L"res\\way.png", 200, 200);
	loadimage(&(room_num[0].free[0]), L"res\\livingroom1.jpg", 1600, 900);
	loadimage(&(room_num[0].free[1]), L"res\\livingroom2.jpg", 1600, 900);
	loadimage(&(room_num[1].free[0]), L"res\\kithen1.jpg", 1600, 900);
	loadimage(&(room_num[1].free[1]), L"res\\kithen2.jpg", 1600, 900);
	loadimage(&(room_num[2].free[0]), L"res\\dinnerroom1.jpg", 1600, 900);
	loadimage(&(room_num[2].free[1]), L"res\\dinnerroom2.jpg", 1600, 900);
	loadimage(&(room_num[3].free[0]), L"res\\bedroom1_1.jpg", 1600, 900);
	loadimage(&(room_num[3].free[1]), L"res\\bedroom1_2.jpg", 1600, 900);
	loadimage(&(room_num[4].free[0]), L"res\\toliet1.jpg", 1600, 900);
	loadimage(&(room_num[4].free[1]), L"res\\toliet2.jpg", 1600, 900);
	loadimage(&(room_num[5].free[0]), L"res\\bedroom2_1.jpg", 1600, 900);
	loadimage(&(room_num[5].free[1]), L"res\\bedroom2_2.jpg", 1600, 900);
	loadimage(&nosing, L"res\\nosing.jpg", 1600, 900);
	IMAGE mos, mop;
	loadimage(&mos, L"res\\jay_1a1.jpg", 1600, 900);
	loadimage(&mop, L"res\\jay_1a2.jpg", 1600, 900);
	room_num[0].monster.push_back(mos);
	room_num[0].monster.push_back(mop);
	loadimage(&mos, L"res\\jay_3a1.jpg", 1600, 900);
	loadimage(&mop, L"res\\jay_3a2.jpg", 1600, 900);
	room_num[2].monster.push_back(mos);
	room_num[2].monster.push_back(mop);
	loadimage(&mos, L"res\\jay4a_1.jpg", 1600, 900);
	loadimage(&mop, L"res\\jay4a_2.jpg", 1600, 900);
	room_num[3].monster.push_back(mos);
	room_num[3].monster.push_back(mop);
	loadimage(&mos, L"res\\lam2a_1.jpg", 1600, 900);
	loadimage(&mop, L"res\\lam_2a2.jpg", 1600, 900);
	room_num[1].monster.push_back(mos);
	room_num[1].monster.push_back(mop);
	loadimage(&mos, L"res\\lam3a_1.jpg", 1600, 900);
	loadimage(&mop, L"res\\lam3a_2.jpg", 1600, 900);
	room_num[2].monster.push_back(mos);
	room_num[2].monster.push_back(mop);
	loadimage(&mos, L"res\\lam6a_1.jpg", 1600, 900);
	loadimage(&mop, L"res\\lam6a_2.jpg", 1600, 900);
	room_num[5].monster.push_back(mos);
	room_num[5].monster.push_back(mop);
	loadimage(&mos, L"res\\cheems3a_1.jpg", 1600, 900);
	loadimage(&mop, L"res\\cheems3a_2.jpg", 1600, 900);
	room_num[2].monster.push_back(mos);
	room_num[2].monster.push_back(mop);
	loadimage(&mos, L"res\\cheems5a_1.jpg", 1600, 900);
	loadimage(&mop, L"res\\cheems5a_2.jpg", 1600, 900);
	room_num[4].monster.push_back(mos);
	room_num[4].monster.push_back(mop);
	loadimage(&mos, L"res\\jay_lam_3a_1.jpg", 1600, 900);
	loadimage(&mop, L"res\\jay_lam_3a_2.jpg", 1600, 900);
	room_num[2].monster.push_back(mos);
	room_num[2].monster.push_back(mop);
	loadimage(&mos, L"res\\cheems_lam3a_1.jpg", 1600, 900);
	loadimage(&mop, L"res\\cheems_lam3a_2.jpg", 1600, 900);
	room_num[2].monster.push_back(mos);
	room_num[2].monster.push_back(mop);
	loadimage(&mos, L"res\\jay_cheems_3a_1.jpg", 1600, 900);
	loadimage(&mop, L"res\\jay_cheems_3a_2.jpg", 1600, 900);
	room_num[2].monster.push_back(mos);
	room_num[2].monster.push_back(mop);
	loadimage(&mos, L"res\\togther1.jpg", 1600, 900);
	loadimage(&mop, L"res\\togther2.jpg", 1600, 900);
	room_num[2].monster.push_back(mos);
	room_num[2].monster.push_back(mop);
	//jay 0,1 Lam 2,3 Cheems 4,5
	//Jay && Lam 6,7 Lam && cheems 8,9 Jay && cheems 10,11
	//3body 12,13
	loadimage(&Kill[0], L"res\\jaykill1.jpg", 1600, 900);
	loadimage(&Kill[1], L"res\\jaykill2.jpg", 1600, 900);
	loadimage(&Kill[2], L"res\\jaykill3.jpg", 1600, 900);
	loadimage(&Kill[3], L"res\\Lamkill.jpg", 1600, 900);
	loadimage(&Kill[4], L"res\\cheemskill.jpg", 1600, 900);
	loadimage(&mMask, L"res\\Mask.jpg", 1600, 900);
	/*loadimage(&time_GUI[0], L"am0.jpg", 200,200);
	loadimage(&time_GUI[1], L"am1.jpg", 200, 200);
	loadimage(&time_GUI[2], L"am2.jpg", 200,200);
	loadimage(&time_GUI[3], L"am3.jpg", 200, 200);
	loadimage(&time_GUI[4], L"am4.jpg", 200, 200);
	loadimage(&time_GUI[5], L"am5.jpg", 200, 200);*/
	loadimage(&buttonMask[0], L"res\\MaskButton.bmp", 800, 80);
	loadimage(&buttonMask[1], L"res\\MaskButton.bmp", 800, 80);
	loadimage(&cheems_cat, L"res\\cheems.jpg", 400, 400);
	loadimage(&Soc[0], L"res\\Soc1.jpg", 200, 200);
	loadimage(&Soc[1], L"res\\Soc2.jpg", 200, 200);
	loadimage(&Soc[2], L"res\\Soc3.jpg", 200, 200);
	loadimage(&Soc[3], L"res\\Soc4.jpg", 200, 200);
	loadimage(&Soc[4], L"res\\Soc5.jpg", 200, 200);
}
void write(int a) {
	fstream file("days.txt");
	file << (char)(a + '0');
	day = a;
	file.clear();
	file.close();
}
void START_MAIN() {
	//GetMouse = thread(GetMouseAndEX);
	live = true;
	startmian = true;
	PlaySound(L"music//主菜单音乐_1.wav", NULL, SND_ASYNC | SND_FILENAME);
	while (startmian) {
		//cout << mouse.x<<" " << mouse.y;
		initXue();
		mouse = GetMouseMsg();
		BeginBatchDraw();
		clearcliprgn();
		putimage(0, 0, &MIAN);
		putpicture(0, 200, &newgame, RGB(0, 0, 0), 255);
		putpicture(0, 300, &Continue, RGB(0, 0, 0), 255);
		putpicture(0, 400, &exitt, RGB(0, 0, 0), 255);
		if (newga.Down(&mouse)) {
			startmian = false;
			write(0);
		}
		if (con.Down(&mouse)) {
			startmian = false;
		}
		if (exiti.Down(&mouse)) {
			exit(0);
		}
		PRINT();
		EndBatchDraw();
	}
	PlaySound(NULL, NULL, NULL);
	live = true;
	clearcliprgn();
}
void Cam_hi(GameStaus pb) {
	if (pb == Cam) {
		initXue();
		clearcliprgn();
		putimage(0, 0, &nosing);
		if (A1.Down(&mouse)) {
			if (!room_num[0].IsOntheRoom) {
				bool a = true;
				putimage(0, 0, &(room_num[0].free[0])); a = false;
				putimage(0, 0, &(room_num[0].free[1])); a = true;
			}
			else {
				putimage(0, 0, &room_num[0].monster[0]);
			}

		}if (A2.Down(&mouse)) {
			//cout << "hi";
			if (!room_num[1].IsOntheRoom) {
				bool a = true;
				putimage(0, 0, &(room_num[1].free[0])); a = false;
				putimage(0, 0, &(room_num[1].free[1])); a = true;
			}
			else {
				putimage(0, 0, &room_num[1].monster[0]);
			}
		}if (A3.Down(&mouse)) {
			//cout << "hi";
			if (room_num[2].IsOntheRoom) {
				//cout << "ok ";
				if (Cheems.listroom[Cheems.Re_i()] == 2 && MrLam.listroom[MrLam.Re_i()] == 2 && Mrjay.listroom[Mrjay.Re_i()] == 2)
					putimage(0, 0, &room_num[2].monster[12]);
				else if (Cheems.listroom[Cheems.Re_i()] == 2 && Mrjay.listroom[Mrjay.Re_i()] == 2)
					putimage(0, 0, &room_num[2].monster[10]);
				else if (Cheems.listroom[Cheems.Re_i()] == 2 && MrLam.listroom[MrLam.Re_i()] == 2)
					putimage(0, 0, &room_num[2].monster[8]);
				else if (Mrjay.listroom[Mrjay.Re_i()] == 2 && MrLam.listroom[MrLam.Re_i()] == 2)//Lam&&jay
					putimage(0, 0, &room_num[2].monster[6]);
				else if (Mrjay.listroom[Mrjay.Re_i()] == 2)//jay
					putimage(0, 0, &room_num[2].monster[0]);
				else if (MrLam.listroom[MrLam.Re_i()] == 2)//Lam
					putimage(0, 0, &room_num[2].monster[2]);
				else if (Cheems.listroom[Cheems.Re_i()] == 2)//Cheems
					putimage(0, 0, &room_num[2].monster[4]);
			}
			else {
				//cout << "no good";
				bool a = true;
				putimage(0, 0, &(room_num[2].free[0])); a = false;
				putimage(0, 0, &(room_num[2].free[1])); a = true;
			}
		}if (A4.Down(&mouse)) {
			//cout << "hi";
			if (!room_num[3].IsOntheRoom) {
				bool a = true;
				putimage(0, 0, &(room_num[3].free[0])); a = false;
				putimage(0, 0, &(room_num[3].free[1])); a = true;
			}
			else {
				putimage(0, 0, &room_num[3].monster[0]);
			}
		}if (A5.Down(&mouse)) {
			//cout << "hi";
			if (!room_num[4].IsOntheRoom) {
				bool a = true;
				putimage(0, 0, &(room_num[4].free[0])); a = false;
				putimage(0, 0, &(room_num[4].free[1])); a = true;
			}
			else {
				putimage(0, 0, &room_num[4].monster[0]);
			}
		}if (A6.Down(&mouse)) {
			//cout << "hi";
			if (!room_num[5].IsOntheRoom) {
				bool a = true;
				putimage(0, 0, &(room_num[5].free[0])); a = false;
				putimage(0, 0, &(room_num[5].free[1])); a = true;
			}
			else {
				putimage(0, 0, &room_num[5].monster[0]);
			}
		}
		putpicture(1300, 500, &way, RGB(0, 0, 0), 255);
		PRINT();
	}
}
void test() {
	putimage(0, 0, &night[day]);
	Flash_num = 0;
	GameStaus player = See;
	Sleep(1000);
	clearcliprgn();
	Mrjay.mtime = time(NULL);
	MrLam.mtime = time(NULL);
	Cheems.mtime = time(NULL);
	time_hour = time(NULL);
	hour = 0;
	live = true;
	PlaySound(L"music\\BGM.wav", NULL, SND_ASYNC | SND_FILENAME| SND_LOOP);
	while (hour != 5 && live) {
		cout << mouse.x << " " << mouse.y << endl;
		//Cheems.Charge_Isjump(true);
		//cout << player;
		if (time(NULL) - 60 == time_hour) {
			hour++;
			time_hour = time(NULL);
		}
		Re_list();
		deadorlive();
		CheemsAI(cheems[day]);
		JayAI(Jay[day]);
		LamAI(Lam[day]);
		Cheems.jump_kill(player, 2, &(room_num[Cheems.listroom[Cheems.Re_i()]]));
		Mrjay.jump_kill(LockDoor, &(room_num[Mrjay.listroom[Mrjay.Re_i()]]));
		MrLam.jump_kill(player, 2, &(room_num[MrLam.listroom[MrLam.Re_i()]]));
		BeginBatchDraw();
		//deadorlive();
		getmessage(&keyborad);
		mouse = GetMouseMsg();
		/*if (keyborad.message = WM_KEYDOWN&&player!=Mask) {
			switch (keyborad.vkcode) {
			case VK_UP:
				player = Mask;
				//cout << "YES" << endl;
				break;
			}
		}
		else if (keyborad.message = WM_KEYDOWN&&player==Mask) {
			switch (keyborad.vkcode) {
			case VK_UP:
				player = See;
				break;
			}
		}*/
		if (button1.Down(&mouse) && !LockDoor) {
			LockDoor = true;
		}
		else if (button1.Down(&mouse) && LockDoor) {
			LockDoor = false;
		}
		if (button.Down(&mouse) && player != Mask) {
			player = Mask;
		}
		else if (button.Down(&mouse) && player == Mask) {
			player = See;
		}
		else if (player == Mask) {
			putimage(0, 0, &mMask);
		}
		else if (mouse.mkLButton && player != Cam&&Flash_num< NUM_FLASH*4) {
			player = Flash;
			Flash_num++;
		}
		else if (player == Flash && !mouse.mkLButton) {
			player = See;
		}
		else if (mouse.mkRButton && player != Cam) {
			player = Cam;
		}
		else if (player == Cam && mouse.mkRButton) {
			player = See;
		}
		clearcliprgn();
		if (player == See)
			putimage(0, 0, &you[0]);
		else if (player == Flash)
			putimage(0, 0, &you[1]);
		if (Cheems.Re_i() == 1 && player == Flash)
			putpicture(645, 109, &cheems_cat, RGB(0, 0, 0), 255);

		//---------------------------------------------------------//

		//cout << mouse.x << " " << mouse.y << endl;
		Cam_hi(player);
		putpicture(800, 820, &buttonMask[0], RGB(255, 255, 255), 255);
		putpicture(0, 820, &buttonMask[1], RGB(255, 255, 255), 255);
		cout << Flash_num<<endl;
		if (Flash_num % NUM_FLASH == 0) {
			Soc_i = Flash_num / NUM_FLASH;
		}
		putpicture(0, 0, &Soc[Soc_i], RGB(0, 0, 0), 255);
		if (LockDoor)
			setfillcolor(RGB(0, 255, 0));
		else
			setfillcolor(RGB(255, 0, 0));
		fillrectangle(100, 400,140, 440);
		outtextxy(100, 450, L"Door");
		Sleep(1000 / 60);
		EndBatchDraw();
	}
	PlaySound(NULL, NULL, NULL);
	if (live) {
		//cout << "yes";
		if (day != 4) {
			clearcliprgn();
			win();
			//outtextxy(0, 0, L"Yes,You Live!");
			Sleep(2000);
			clearcliprgn();
			write(day + 1);
			test();
		}
		else {
			write(day + 1);
			outtextxy(Cam_width / 2, Cam_height / 2, L"The End(Now Get Out)");
			Sleep(2000);
			exit(0);
		}
	}
	else {
		START_MAIN();
	}
	//GetMouse.join();
	hour = 0;
}
void read() {
	fstream file("days.txt");
	file >> word;
	day = word[0] - '0';
	//cout << a;
	file.clear();
	file.close();
}
int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow){
	initroom();
	init();
	read();
	initgraph(Cam_width, Cam_height);
	//putimage(0, 0, &(Kill[4]));
	//while (1);
	START_MAIN();
	Mrjay.JumpScary_time = 10;
	MrLam.JumpScary_time = 15;
	Cheems.JumpScary_time=20;
	test();
}