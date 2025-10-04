#pragma once
#pragma once
#include<graphics.h>
#include<easyx.h>
#include<windows.h>
#include<iostream>
#include<conio.h>
#include<Mmsystem.h>
#include<vector>
#include<time.h>
#include<fstream>
#include<random>
#include<thread>
using namespace std;
#pragma comment(lib,"winmm.lib")
enum GameStaus {
	See,
	Cam,
	Flash,
	Mask
};
int RE_RANDOM(int a) {
	std::random_device rd;  // 真随机数生成器
	std::mt19937 gen(rd()); // Mersenne Twister 引擎
	std::uniform_int_distribution<> dis(0, a);  // 生成 0 到 99 之间的整数
	int random_number = dis(gen);
	return random_number;
}
struct Vector2 {
	int x;
	int y;
};
void putpicture(int dstx, int dsty, IMAGE* img, COLORREF color, int alpha) {//0~255 255表示不透明
	DWORD* imgp = GetImageBuffer(img);
	DWORD* bgimgp = GetImageBuffer();
	int w, bw, h, i, j;
	w = img->getwidth();
	bw = getwidth();
	h = img->getheight();
	color += 0xff000000;
	if (alpha < 0)alpha = 0;
	else if (alpha > 255)alpha = 255;
	for (i = 0; i < h; ++i)
		for (j = 0; j < w; ++j)
			if (imgp[i * w + j] != color)
				bgimgp[(i + dsty) * bw + j + dstx] = RGB(
					((int)(alpha / 255.0 * GetRValue(imgp[i * w + j]) + (1 - alpha / 255.0) * GetRValue(bgimgp[(i + dsty) * bw + j + dstx]))),
					((int)(alpha / 255.0 * GetGValue(imgp[i * w + j]) + (1 - alpha / 255.0) * GetGValue(bgimgp[(i + dsty) * bw + j + dstx]))),
					((int)(alpha / 255.0 * GetBValue(imgp[i * w + j]) + (1 - alpha / 255.0) * GetBValue(bgimgp[(i + dsty) * bw + j + dstx])))
				);
}
class room {
public:
	bool IsOntheRoom;
	std::vector<IMAGE> monster;
	IMAGE free[2];
};
class Athor {
private:
	int list_i;
	bool JumpScary;
	bool IsJump;
public:
	vector<int> listroom;
	int JumpScary_time;
	int mtime;
	int Jump_time_now;
	void Charge_Isjump(bool a) {
		IsJump = a;
	}
	bool ReJump() {
		return IsJump;
	}
	bool Jump() {
		return JumpScary;
	}
	Athor() {
		Jump_time_now = -1;
		IsJump = false;
	}
	void move(bool a) {
		if (list_i + 1 == listroom.size() && !JumpScary && a) {
			JumpScary = true;
			Jump_time_now = time(NULL);
		}
		if (!JumpScary) {
			list_i++;
			if (list_i > listroom.size() - 1) {
				list_i = 0;
			}
		}
	}
	void jump_kill(GameStaus pb, int a, room* Ch) {
		if (pb == a && JumpScary) {
			//cout << "OK ";
			// cout << JumpScary;
			Jump_time_now = -1;
			JumpScary = false;
			Ch->IsOntheRoom = false;
			list_i = 0;
		}
		else if (Jump_time_now != -1 && JumpScary) {
			if (time(NULL) - JumpScary_time >= Jump_time_now) {
				IsJump = true;
			}
		}
	}
	void jump_kill(bool d, room* Ch) {
		if (d && JumpScary) {
			Jump_time_now = -1;
			JumpScary = false;
			Ch->IsOntheRoom = false;
			list_i = 0;
		}
		else if (Jump_time_now != -1 && JumpScary) {
			if (time(NULL) - JumpScary_time >= Jump_time_now) {
				IsJump = true;
			}
		}
	}
	bool timming(int a) {
		if (time(NULL) - a >= mtime) {
			return true;
		}
		return false;
	}
	int Re_i() {
		return list_i;
	}
};
class Xue {
public:
	int x, y;
	void print() {
		putpixel(x, y, RGB(255, 255, 255));
	}
};
class UI {
private:
	int startx, starty, width, height;
	Vector2 end;
public:
	UI(int x, int y, int wi, int hei) {
		startx = x; starty = y; width = wi; height = hei;
		end.x = startx + wi;
		end.y = starty + height;
	}
	UI() {
		startx = 0; starty = 0; width = 0; height = 0;
		end.x = 0; end.y = 0;
	}
	bool Down(MOUSEMSG* pb) {
		if (pb->x > startx && pb->x<end.x && pb->y>starty && pb->y < end.y && pb->mkLButton) {
			return true;
		}
		return false;
	}
};