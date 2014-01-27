#include "DxInput.h"

DxInput* DxInput::m_pDxInput = nullptr;

DxInput* DxInput::GetInstance()
{
	if ( m_pDxInput == nullptr )
		m_pDxInput = new DxInput();

	return m_pDxInput;
}


// 매개 변수에 SetCooperativeLevel 를 설정할수 있게금 한다.
HRESULT DxInput::Create(HWND _hwnd)
{
	m_hWnd = _hwnd;

	HRESULT hr_Keyboard;
	HRESULT hr_Mouse;

	ZeroMemory(m_key_buffer,256);
	ZeroMemory(m_MouseState.rgbButtons,4);


	//Keyboard Setting
	if(DirectInput8Create( GetModuleHandle(NULL),DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&m_pDX8, NULL) == -1)
		return FALSE;

	if(m_pDX8->CreateDevice(GUID_SysKeyboard, &m_pKeyboard, NULL) == -1)
		return FALSE;

	if( m_pKeyboard->SetDataFormat( &c_dfDIKeyboard ) == -1) 
		return FALSE;

	hr_Keyboard = m_pKeyboard->SetCooperativeLevel( _hwnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE );
	if( hr_Keyboard == DIERR_UNSUPPORTED) 
		return FALSE;

	m_pKeyboard->Acquire();

	//Mouse Setting
	if( m_pDX8->CreateDevice( GUID_SysMouse, &m_pMouse, NULL ) == -1 )
		return FALSE;

	if( m_pMouse->SetDataFormat( &c_dfDIMouse ) == -1 )
		return FALSE;

	hr_Mouse = m_pMouse->SetCooperativeLevel( _hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE );
	if( hr_Mouse == DIERR_UNSUPPORTED )
		return FALSE;

	m_pMouse->Acquire();

	return S_OK;
}


//release 의 종류를 2개로 나눈다 . 마우스 . 키보드
void DxInput::Release()
{
	m_pKeyboard->Release();
	m_pMouse->Release();
	m_pDX8->Release();

	m_pKeyboard = nullptr;
	m_pDX8 = nullptr;
	m_pMouse = nullptr;

	delete m_pDxInput;
	m_pDxInput = nullptr;
}

bool DxInput::Keyboard_Up( const int key )
{
	if(!INPUTEVENT(m_key_buffer,key) && m_key_down[key])
		return true;
	return false;
}

bool DxInput::Keyboard_Down( const int key )
{
	if(INPUTEVENT(m_key_buffer,key) && !m_key_down[key])
		return true;
	return false;
}

bool DxInput::Keyboard_DownState( const int key )
{
	if(INPUTEVENT(m_key_buffer,key))
		return true;
	return false;
}


bool DxInput::Mouse_Up( const MOUSE_STATE n )
{
	if(!INPUTEVENT(m_MouseState.rgbButtons,n) && m_button_down[n])
		return true;
	return false;
}

bool DxInput::Mouse_Down( const MOUSE_STATE n )
{
	if(INPUTEVENT(m_MouseState.rgbButtons,n) && !m_button_down[n])
		return true;
	return false;
}

bool DxInput::Mouse_DownState( const MOUSE_STATE n )
{
	if(INPUTEVENT(m_MouseState.rgbButtons,n))
		return true;
	return false;
}

bool DxInput::Update() 
{
	for(int i=0;i<256;i++)
	{
		if(INPUTEVENT(m_key_buffer,i))
		{
			m_key_down[i]=true;
		}
		else
		{
			m_key_down[i]=false;
		}
	}

	if ( FAILED(m_pKeyboard->GetDeviceState(sizeof(m_key_buffer),(LPVOID) &m_key_buffer)) ) 
	{
		if( FAILED(m_pKeyboard->Acquire()) ) 
		{
			return false;
		}
		if( FAILED(m_pKeyboard->GetDeviceState(sizeof(m_key_buffer),(LPVOID) &m_key_buffer)) )
		{
			return false;
		}
	}

	for(int i=0;i<4;i++)
	{
		if(INPUTEVENT(m_MouseState.rgbButtons, i))
		{
			m_button_down[i]=true;
		}
		else
		{
			m_button_down[i]=false;
		}
	}


	if ( FAILED(m_pMouse->GetDeviceState(sizeof(DIMOUSESTATE),&m_MouseState)) )
	{
		if( FAILED(m_pMouse->Acquire()) )
		{
			return false;
		}
		if( FAILED(m_pMouse->GetDeviceState(sizeof(DIMOUSESTATE),&m_MouseState)) ) 
		{
			return false;
		}
	}
	return true;
}

D3DXVECTOR3 DxInput::GetMouseMovement()
{
	return D3DXVECTOR3 ((float)m_MouseState.lX,(float)m_MouseState.lY, (float)m_MouseState.lZ);
}

D3DXVECTOR2 DxInput::GetCursorPos()
{
	POINT pt;

	::GetCursorPos(&pt);
	ScreenToClient(m_hWnd, &pt);

	return D3DXVECTOR2((float)pt.x, (float)pt.y);
}
bool DxInput::Mouse_DoubleClick( const MOUSE_STATE n , float _timing )
{
	static int _clickCount = 0;
	static DWORD _time = 0; 

	if ( GetTickCount() - _time >= _timing )
		_clickCount = 0;

	if ( _clickCount == 0 )
		_time = GetTickCount();

	if ( Mouse_Down(n) )
		_clickCount += 1;

	if ( _clickCount < 2 )
		return false;

	_clickCount = 0;
	_time = 0;

	return true;
}



