#ifndef __DXINPUT_H__
#define __DXINPUT_H__

#define INPUTEVENT(name, n) (name[n] & 0x80)

#include <dinput.h>
#include <d3dx9.h>

#ifndef D3D9_LIB
#define D3D9_LIB
#pragma comment(lib, "d3d9.lib")
#endif

#include <d3dx9.h>
#ifndef D3DX9_LIB
#define D3DX9_LIB
#pragma comment(lib, "d3dx9.lib")
#endif

#ifndef DXGUID_LIB
#define DXGUID_LIB
#pragma comment(lib, "dxguid.lib")
#endif

#ifndef DINPUT8_LIB
#define DINPUT8_LIB
#pragma comment(lib, "dinput8.lib")
#endif



class DxInput
{
private:
	DxInput(){}
	~DxInput(){}

	DxInput(const DxInput &){}
	DxInput& operator=(const DxInput &){}
public:
	enum MOUSE_STATE
	{
		LBUTTONDOWN = 0,
		RBUTTONDOWN,
		WHEELBUTTONDOWN
	};
public:
	static DxInput* GetInstance();

	HRESULT Create(HWND _hwnd);
	bool Update();
	void Release();
	
	bool Keyboard_Up( const int key );
	bool Keyboard_Down( const int key );
	bool Keyboard_DownState( const int key );
	
	bool Mouse_Up( const MOUSE_STATE n );
	bool Mouse_Down( const MOUSE_STATE n );
	bool Mouse_DownState( const MOUSE_STATE n );
	bool Mouse_DoubleClick( const MOUSE_STATE n , float _timing = 250.0f );

	D3DXVECTOR3 GetMouseMovement();
	D3DXVECTOR2 GetCursorPos();
private:
	static DxInput* m_pDxInput;
	
	HWND m_hWnd;

	LPDIRECTINPUT8			m_pDX8;				
	LPDIRECTINPUTDEVICE8	m_pKeyboard;	
	LPDIRECTINPUTDEVICE8	m_pMouse;	
	DIMOUSESTATE			m_MouseState;

	char m_key_buffer[256];
	bool m_key_down[256];
	bool m_button_down[4];
};

#endif