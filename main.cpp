
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <windows.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;


void PressKey(char c)
{
    INPUT ip;
    ip.type = INPUT_KEYBOARD;
    ip.ki.wScan = 0;
    ip.ki.time = 0;
    ip.ki.dwExtraInfo = 0;
    ip.ki.wVk = c;
    ip.ki.dwFlags = 0; // 0 for key press
    SendInput(1, &ip, sizeof(INPUT));
}

void ReleaseKey(char c)
{
    INPUT ip;
    ip.type = INPUT_KEYBOARD;
    ip.ki.wScan = 0;
    ip.ki.time = 0;
    ip.ki.dwExtraInfo = 0;
    ip.ki.wVk = c;
    ip.ki.dwFlags = KEYEVENTF_KEYUP; // for key release
    SendInput(1, &ip, sizeof(INPUT));
}

void TapKey(char c)
{
    INPUT ip={0};
    ip.type = INPUT_KEYBOARD;
    ip.ki.wScan = 0;
    ip.ki.time = 0;
    ip.ki.dwExtraInfo = 0;
    ip.ki.wVk = c;
    ip.ki.dwFlags = 0; // 0 for key press
    SendInput(1, &ip, sizeof(INPUT));
    ip.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &ip, sizeof(INPUT));
}

void WriteChar(char c) 
{
	
	SHORT vk = VkKeyScanEx(c, GetKeyboardLayout(0) );
	char keycode = vk & 0xff;
	
	if (keycode == -1) return;
	
	if (vk & 0x100) // check upper byte for shift flag
	{
		PressKey(VK_SHIFT);	
		TapKey(keycode);
		ReleaseKey(VK_SHIFT);
	   // send a shift key down
	}
	else if (vk & 0x200) // check for ctrl flag
	{
		PressKey(VK_CONTROL);
		TapKey(keycode);
		ReleaseKey(VK_CONTROL);
	   // send a ctrl key down
	}	
	else TapKey(keycode);
	
}


void SendText(string text)
{
    INPUT ip = {0};
    ip.type = INPUT_KEYBOARD;
    ip.ki.wVk = VK_LSHIFT;
    for(int i=0;i<text.size();i++)
    	WriteChar(text[i]);
}

void SendInt(char number)
{
    char buff[32];
    memset(buff,0,32);
    itoa(number,buff,10);
    string str(buff);
    SendText(str);
}

int main()
{
	unsigned int nlist[] = {
    65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90,
    VK_SPACE, VK_RETURN, VK_TAB, VK_BACK, VK_CAPITAL,
    VK_NUMPAD0, VK_NUMPAD1, VK_NUMPAD2, VK_NUMPAD3, VK_NUMPAD4, VK_NUMPAD5, VK_NUMPAD6, VK_NUMPAD7, VK_NUMPAD8, VK_NUMPAD9,
    VK_MULTIPLY, VK_ADD, VK_SEPARATOR, VK_SUBTRACT, VK_DECIMAL, VK_DIVIDE,
    0
	};
	
	fstream fin("test.cpp",ios::in);
	
	string ch;
	//TODO: ToAscii &&  VkKeyScanEx 
	
	stringstream stream("FUCK you *+-/ %& !( ) { } [ ]( ) { } [ ]: ; _ << >> ? $%^");
	//unsigned int *i = nlist;
	
	bool flag = true;
	while(flag)
	{
		for(int key = 1;key<255;++key)
		{
        	if (GetAsyncKeyState(key) == -32767)  
        	{
            	flag = false;
				break;
			}
		}
         
    } 

	while( getline(fin,ch) ) 
	{
		
		cout<<ch<<endl;
		for(int i = 0;i<ch.size();++i )
		{
			WriteChar(ch[i]);
			Sleep(5);		
		}
		TapKey(VK_RETURN);
	}
		
	cout<<endl<<"done";
	return 0;
}
