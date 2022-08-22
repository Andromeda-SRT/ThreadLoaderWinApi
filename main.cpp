#include "defines.cpp"
#include <windows.h>
#include <ctime>
#include <stdio.h> //For snprintf()
#include <math.h> //For math functions and atof()

DWORD WINAPI MyThread(LPVOID params);
double f(double x, double q, double p);
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);

struct DataForThread
{
    double a_i;   
    double b_i;    
    double p;    
    double q;
	double n_i; 
	double k;   
    double ss_i; 
};


bool fArray = false; //Flag for show arrays status

HWND hLable1, hLable2, hLable3, hLable4, hLable5, hLable6, hLablef, hLablei,
	 hwnd,
	 hPanel, 
	 hButton1, hButton2, hButton3, hButtonS,
	 hEdit1, hEdit2, hEdit3, hEdit4, hEdit5, hEdit6,
	 hListBox;

int index = 0;
static int  baseX = 20,
			standartHeight = 20;
					

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize		 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);
	
	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszClassName = "WindowClass";
	wc.hIcon		 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm		 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","Thread Loader",WS_VISIBLE | WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		333, /* width */
		baseX * 25, /* height */
		NULL,NULL,hInstance,NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	/*
		This is the heart of our program where all input is processed and 
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/
	
	//SETTINGS PART =====================================================
	//PANEL1
	DWORD dwExStyle = NULL; //WS_EX_CLIENTEDGE|WS_EX_DLGMODALFRAME
	DWORD dwStyle = WS_CHILD|WS_VISIBLE;
	hPanel = CreateWindowEx(dwExStyle, "STATIC", "", dwStyle, 
		0, 0, /* x , y */
		323, baseX * 6.5, /* width , height */
		hwnd, (HMENU)NULL, hInstance, (LPVOID)NULL);
	//a
	hLable1 = CreateWindow("STATIC",
    		"a = ",WS_CHILD | WS_VISIBLE | SS_CENTER,
    		5, baseX * 1, /* x , y */
			50, standartHeight,  /* width , height */
			hwnd,(HMENU)ID_STATIC_A,NULL,NULL);
	hEdit1 = CreateWindow("Edit","0.1",WS_VISIBLE | WS_CHILD | WS_BORDER,
	        44, baseX * 1,
	        50, standartHeight, 
	        hwnd,(HMENU)EDIT_A,NULL,NULL);
	//b		
	hLable2 = CreateWindow("STATIC",
    		"b = ",WS_CHILD | WS_VISIBLE | SS_CENTER,
    		5, baseX * 2,
			50, standartHeight, 
			hwnd,(HMENU)ID_STATIC_B,NULL,NULL);
	hEdit2 = CreateWindow("Edit","1.8",WS_VISIBLE | WS_CHILD | WS_BORDER,
	        44, baseX * 2,
	        50, standartHeight,
	        hwnd,(HMENU)EDIT_B,NULL,NULL);
	//p
	hLable3 = CreateWindow("STATIC",
    		"p = ",WS_CHILD | WS_VISIBLE | SS_CENTER,
    		94, baseX * 1, 
			50, standartHeight, 
			hwnd,(HMENU)ID_STATIC_P,NULL,NULL);
	hEdit3 = CreateWindow("Edit","0.4",WS_VISIBLE | WS_CHILD | WS_BORDER,
	        134, baseX * 1,
	        50, standartHeight, 
	        hwnd,(HMENU)EDIT_P,NULL,NULL);
	//q		
	hLable4 = CreateWindow("STATIC",
    		"q = ",WS_CHILD | WS_VISIBLE | SS_CENTER,
    		94, baseX * 2,
			50, standartHeight, 
			hwnd,(HMENU)ID_STATIC_Q,NULL,NULL);		
	hEdit4 = CreateWindow("Edit","0.3",WS_VISIBLE | WS_CHILD | WS_BORDER,
	        134, baseX * 2,
	        50, standartHeight,
	        hwnd,(HMENU)EDIT_Q,NULL,NULL);
	//n		
	hLable5 = CreateWindow("STATIC",
    		"n = ",WS_CHILD | WS_VISIBLE | SS_CENTER,
    		5, baseX * 3.5,
			50, standartHeight,  
			hwnd,(HMENU)ID_STATIC_N,NULL,NULL);
	hEdit5 = CreateWindow("Edit","100000000",WS_VISIBLE | WS_CHILD | WS_BORDER,
	        44, baseX * 3.5,
	        50*2.1, standartHeight,
	        hwnd,(HMENU)EDIT_N,NULL,NULL);
	//k		
	hLable6 = CreateWindow("STATIC",
    		"K = ",WS_CHILD | WS_VISIBLE | SS_CENTER,
    		5, baseX * 4.5, 
			50, standartHeight, 
			hwnd,(HMENU)ID_STATIC_K,NULL,NULL);
	hEdit6 = CreateWindow("Edit","4",WS_VISIBLE | WS_CHILD | WS_BORDER,
	        44, baseX * 4.5, 
	        50*2.1, standartHeight,
	        hwnd,(HMENU)EDIT_K,NULL,NULL);
	//Information
	hLablei = CreateWindow("STATIC",
    		"",WS_CHILD | SS_LEFT | WS_BORDER | WS_VSCROLL, //| WS_VISIBLE
    		133, baseX * 1, 
			177, baseX * 6, 
			hwnd,(HMENU)ID_STATIC_INFO,NULL,NULL);
	//BUTTONS		
	hButton1 = CreateWindow("BUTTON",
			"Clear n K",WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON,
			222, baseX * 1, 
			77, standartHeight + 10,
			hwnd,(HMENU)BUTTON_1,NULL,NULL);
	hButton2 = CreateWindow("BUTTON",
			"START",WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON,
			222, baseX * 2 + 10, 
			77, standartHeight + 10,
			hwnd,(HMENU)BUTTON_2,NULL,NULL);
	hButton3 = CreateWindow("BUTTON",
			"CLEAR",WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON,
			222, baseX * 4,
			77, standartHeight + 10, 
			hwnd,(HMENU)BUTTON_3,NULL,NULL);
	hButtonS = CreateWindow("BUTTON",
			"SAVE AS",WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON,
			222, baseX * 5 + 10,
			77, standartHeight / 1.2, 
			hwnd,(HMENU)BUTTON_4,NULL,NULL);
			
	//WORKING AREA ======================================================						
	hListBox = CreateWindow("LISTBOX",
			NULL, WS_VISIBLE|WS_CHILD|LBS_STANDARD|WS_VSCROLL|WS_HSCROLL,
			6, baseX * 7, /* x , y */
			311, baseX * 15 + 10, /*width , height */
			hwnd,(HMENU)LISTBOX,NULL,NULL);
			
			SendMessage(hListBox, LB_SETHORIZONTALEXTENT, 500, 0);
	
	//FOOTER PART =======================================================
	//LABLE "About program"
	hLablef = CreateWindow("STATIC",
    		"Work with threads v0.1",WS_CHILD | WS_VISIBLE | SS_CENTER,
    		0, baseX * 22+10, /* x , y */
			323, 20,  /* width , height */
			hwnd,(HMENU)ID_STATICF,NULL,NULL);
	
	
	
	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}
	return msg.wParam;
}

/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		
		case WM_CREATE: {
			
    		
			break;
		}
		
		case WM_COMMAND: {
			if ( LOWORD(wParam) == BUTTON_1) {
				SetWindowText(hEdit5,"");
				SetWindowText(hEdit6,"");
			}
			
			if ( LOWORD(wParam) == BUTTON_2) {
				
				char chA[256], chB[256], chP[256], chQ[256], chN[256], chK[256];
				GetWindowText(hEdit1, chA, 256);
				GetWindowText(hEdit2, chB, 256);
				GetWindowText(hEdit3, chP, 256);
				GetWindowText(hEdit4, chQ, 256);
				GetWindowText(hEdit5, chN, 256);
				GetWindowText(hEdit6, chK, 256);
				
				//Cheking to fully Edits
				if ( !chA[0] || !chB[0] || !chP[0] || !chQ[0] || !chN[0] || !chK[0]) {
					MessageBox(0, TEXT("Необходимо заполнить все поля"), TEXT("Внимание"), MB_OK);
				}
				else 
				{
					
					double a,b,p,q,n,k;
					
				 	a = atof(chA); b = atof(chB);
				 	p = atof(chP); q = atof(chQ);
				 	n = atof(chN); k = atof(chK);
				 	
				 	if (k > 64) {
				 		MessageBox(0, TEXT("Системное ограничение для К = 64"), TEXT("Внимание"), MB_OK|MB_ICONINFORMATION);
					 }
					else {
						
					
					 	double h = (b - a) / n;
					 	double step = (b - a) / k;
					 	
					 	DWORD CtThread = k;
					 	
					    DataForThread* params = new DataForThread[CtThread+1] ();
						//params[0] = { params->a_i = 0.0, params->b_i = 0.0, params->p = 0.0, params->q = 0.0, params->n_i = 0.0, params->k = 0.0, params->ss_i = 0.0 };
					
					    bool first_f = false;
					    for (int i = 1; i <= CtThread; i++) {
					        double b1 = a + step;
					        params[i] = { params->a_i = first_f ? a + h : a, params->b_i = b1, params->p = p, params->q = q, params->n_i = n/k, params->k = k, params->ss_i = 0.0 };
					        first_f = true;
					        a += step;
					    }
					
					    
					    HANDLE hArrForMyThread[CtThread];
						
						//------>>> BUG ---------- <<< 
					    for (int i = 1; i <= CtThread; i++) { // if u called (explicitly) from i = 0 then the thread with index [1] will be not created
					        hArrForMyThread[i-1] = CreateThread(NULL, CtThread, MyThread, (LPVOID)&params[i], 0, 0);
					    }
					
					    unsigned int start_time = clock();
		
					    WaitForMultipleObjects(CtThread, hArrForMyThread, TRUE, INFINITE);
					   
					    double ss = 0.0;  
					    
					    for (int i = 1; i <= CtThread; i++) {
					        ss += params[i].ss_i;
					    }
					    delete[] params;
					
					    unsigned int end_time = clock(); 
					
					    unsigned int search_time = end_time - start_time; 
					    double ss_res = 0.00;
						ss_res = ss;  
		
					    double time = (double)search_time / 1000;
					
					
					    for (DWORD i = 0; i < CtThread; ++i) {
					        CloseHandle(hArrForMyThread[i]);
					    }
					    
					    char str[512];
						str[0] = '\0';
					    
					    strcat(str,"n = ");
						strcat(str,chN);
				
						strcat(str," k = ");
						strcat(str,chK);
						
						strcat(str," ss = ");
						char chRes[256]; //Convert double to char
						snprintf(chRes, sizeof chRes, "%g", ss_res);
						strcat(str,chRes);
						
						strcat(str," t = ");
						char chTime[256];
						snprintf(chTime, sizeof chTime, "%g", time);
						strcat(str,chTime);
				
						//SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)(LPSTR)str);
						SendMessage(hListBox, LB_INSERTSTRING, (WPARAM)index, (LPARAM)(int FAR *)str);
					    index++;
					}
					
				}
			}
			
			if ( LOWORD(wParam) == BUTTON_3) {
				SendMessage(hListBox, LB_RESETCONTENT, NULL, NULL);
				index = 0;
				SetWindowText(hEdit1,"");
				SetWindowText(hEdit2,"");
				SetWindowText(hEdit3,"");
				SetWindowText(hEdit4,"");
				SetWindowText(hEdit5,"");
				SetWindowText(hEdit6,"");
			}
    		
    		if ( LOWORD(wParam) == BUTTON_4) {
    			
    			FILE* fp_out;
			
				if ((fp_out = fopen("../test1.txt", "w+")) == NULL) { //w+ - если файл не существует - создать, если файл ранее существовал содержимое удалить
					MessageBox(0, TEXT("Невозможно открыть файл"), TEXT("Ошибка"), MB_OK|MB_ICONERROR);
				}
				else {
					int str_count = SendMessage(hListBox, LB_GETCOUNT, 0, 0L); //Получаем кол-во строк в ListBox-е
					
					for (int str_number = 0; str_number < str_count; str_number++) {
						char * buf = new char[512];
						buf[0] = '\0';
						SendMessage(hListBox, LB_GETTEXT, (WPARAM)str_number, (LPARAM)buf);
						int _size = strlen(buf); //Узнаём длину получаемой строки
						char* data = new char[_size + 1]; //Выделяем память для приходящей строки
						snprintf(data, _size + 1, buf); //Передаём значения в новую С строку с которой будем работатьы
						strcat(data, "\n");
						fwrite(data,_size + 1, 1, fp_out); //Записываем в файл
					}
					
					
					if ((fclose(fp_out) == NULL)) { //Закрываем поток с проверками
						MessageBox(0, TEXT("Файл успешно сохранён!"), TEXT("Информация"), MB_OK|MB_ICONINFORMATION); //Файл был закрыт
					}
					else {
						MessageBox(0, TEXT("Ошибка закрытия файла"), TEXT("Ошибка"), MB_OK|MB_ICONERROR);
					}
					

				}
				
			}
    		
    		
			break;
		}
		
		/* Upon destruction, tell the main thread to stop */
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		
		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}


DWORD WINAPI MyThread(LPVOID params)
{
    DataForThread* ab;
    ab = (DataForThread*)params;
 
    
    double s=(f(ab->a_i, ab->q, ab->p)+f(ab->b_i, ab->q, ab->p))/2;
	double h=(ab->b_i - ab->a_i)/ab->n_i;
	double n = ab->n_i;
	
	for (int i=1; i <= n-1; i++)
	{ 
		double x = ab->a_i+i*h;
		s+=f(x, ab->q, ab->p);
	}
	ab->ss_i = s*h;
    
    ExitThread(0);
}


double f(double x, double q, double p)
{
 	double up = (0.5 * -1) * p * x - M_PI;

    double p1 = exp(up) * sin(q * x - (M_PI / 6));
    double p2 = (M_PI / 8) + p * pow(x, 2);
    double r = p1 / p2;
    return r;
}
