#include <cstdio>
#include <windows.h>
#include <vfw.h>


// ========== DECLARATION =================

char video_extension;

int movi_Offset;
int movi_Size;
fileHandle_t  idxF;
int num_indices;
int frame_rate;
int frame_period;
int video_width; 
int video_height;
int video_num_video_frames;
int video_max_record_size;

int       video_frameRate;
int       video_framePeriod;
int       video_numVideoFrames;
int       video_maxRecordSize;
qboolean  video_motionJpeg;

// =========== DEFINITION =================


// Play an AVI using the MSvfw32.lib 
// in the case of Dev-C++ link with libmsvfw32.a via
// Project>>Project Options>>Parameters>>Add Lib>>libmsvfw32.a
// created via BCX generated C code then modified for Dev-C++
// (actually-Dev C++ is the IDE for the GNU GCC/G++ compiler)
// a Dev-C++ tested Windows Application by  vegaseat  21nov2004 

#define ID_MCIFrame 0
#define ID_MENU1 9001
#define ID_MENU2 9002
#define ID_MENU3 9003
static HINSTANCE BCX_hInstance;
static int     BCX_ScaleX;
static int     BCX_ScaleY;
static char    BCX_ClassName[2048];
static HANDLE  ghInst;
static HWND    Form1;
static HWND    MCIFrame;
static HMENU   MainMenu;
static HMENU   FileMenu;
static OPENFILENAME OpenFileName;
static char    szFile[2048];
static char    szFileTitle[2048];
#define Show(Window)  RedrawWindow(Window,0,0,0);ShowWindow(Window,SW_SHOW);
HWND    BCX_Form(char*,int=0,int=0,int=250,int=150,int=0,int=0);
void    BCX_Set_Form_Color (HWND,COLORREF);
void    Center (HWND,HWND=0,HWND=0);
char*   BCX_TmpStr(size_t);
char*   str (double);
char*   curdir (void);
void    FormLoad (void);
LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM);
int     InitOpenFileName (void);
int     PopFileOpenDlg (HWND, char *, char *);
BOOL    AddMenu (HWND);

// standard Windows Graphical User Interface main
int WINAPI WinMain(HINSTANCE hInst,HINSTANCE hPrev,LPSTR CmdLine,int CmdShow)
{
 WNDCLASS Wc;
 MSG      Msg;
 // *****************************
 strcpy(BCX_ClassName,"MCI_demo1");
 // ************************************
 // Scale Dialog Units To Screen Units
 // ************************************
 RECT rc          =  {0,0,4,8};
 MapDialogRect       (NULL,&rc);
 BCX_ScaleX       =  rc.right/2;
 BCX_ScaleY       =  rc.bottom/4;
 BCX_hInstance    =  hInst;
 // ******************************************************
 Wc.style         =  CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
 Wc.lpfnWndProc   =  WndProc;
 Wc.cbClsExtra    =  0;
 Wc.cbWndExtra    =  0;
 Wc.hInstance     =  hInst;
 Wc.hIcon         =  LoadIcon(NULL,IDI_WINLOGO);
 Wc.hCursor       =  LoadCursor(NULL,IDC_ARROW);
 Wc.hbrBackground =  (HBRUSH)(COLOR_BTNFACE+1);
 Wc.lpszMenuName  =  NULL;
 Wc.lpszClassName =  BCX_ClassName;
 RegisterClass(&Wc);
 FormLoad();
 
 // event message loop 
 while(GetMessage(&Msg,NULL,0,0))
 {
    HWND hActiveWindow = GetActiveWindow();
    if (!IsWindow(hActiveWindow) || !IsDialogMessage(hActiveWindow,&Msg))
      {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
      }
 }
 return Msg.wParam;
}
// circular storage, hold the memory leaks to a minimum
char *BCX_TmpStr (size_t Bites)
{
  static int   StrCnt;
  static char *StrFunc[2048];
  StrCnt=(StrCnt + 1) & 2047;
  if(StrFunc[StrCnt]) free (StrFunc[StrCnt]);
  return StrFunc[StrCnt]=(char*)calloc(Bites+128,sizeof(char));
}
char *str (double d)
{
  register char *strtmp = BCX_TmpStr(16);
  sprintf(strtmp,"% .15G",d);
  return strtmp;
}
char *curdir (void)
{
  register char *strtmp = BCX_TmpStr(2048);
  GetCurrentDirectory (1024,strtmp);
  return strtmp;
}
// center the window form on the screen, optional, for looks
void Center (HWND hwnd, HWND Xhwnd, HWND Yhwnd)
{
  RECT rect, rectP;
  int  x, y, width, height;
  int  screenwidth, screenheight;
  if(Xhwnd==0)
    {
      RECT  DesktopArea;
      RECT  rc;
      SystemParametersInfo(SPI_GETWORKAREA,0,&DesktopArea,0);
      GetWindowRect(hwnd,&rc);
      SetWindowPos(hwnd,HWND_TOP,
        ((DesktopArea.right-DesktopArea.left)-(rc.right-rc.left))/2+
          DesktopArea.left,((DesktopArea.bottom-DesktopArea.top)-
         (rc.bottom-rc.top))/2 + DesktopArea.top,0,0,SWP_NOSIZE);
      return;
    }
  GetWindowRect (hwnd,&rect);
  GetWindowRect (Xhwnd,&rectP);
  width = rect.right-rect.left;
  x = ((rectP.right-rectP.left)-width)/2 + rectP.left;
  if (Yhwnd==NULL)
  {
      height = rect.bottom-rect.top;
      y = ((rectP.bottom-rectP.top)-height)/2 + rectP.top;
  }
  else
  {
      GetWindowRect(Yhwnd,&rectP);
      height = rect.bottom-rect.top;
      y = ((rectP.bottom-rectP.top)-height)/2+rectP.top;
  }
  screenwidth = GetSystemMetrics(SM_CXSCREEN);
  screenheight = GetSystemMetrics(SM_CYSCREEN);
  if ((x<0)) 
    x=0;
  if ((y<0)) 
    y=0;
  if ((x+width>screenwidth))   
    x = screenwidth-width;
  if ((y+height>screenheight)) 
    y = screenheight-height;
  MoveWindow (hwnd, x, y, width, height, FALSE);
}
// create the windows form
HWND BCX_Form(char *Caption, int X, int Y, int W, int H, int Style, int Exstyle)
{
   HWND  A;
   // assigne default style if none given
   if (!Style)
   {
        Style= WS_MINIMIZEBOX  |
        WS_SIZEBOX      |
        WS_CAPTION      |
        WS_MAXIMIZEBOX  |
        WS_POPUP        |
        WS_SYSMENU;
   }
   A = CreateWindowEx(Exstyle,BCX_ClassName,Caption,
   Style,
   X*BCX_ScaleX,
   Y*BCX_ScaleY,
   (4+W)*BCX_ScaleX,
   (12+H)*BCX_ScaleY,
   NULL,(HMENU)NULL,BCX_hInstance,NULL);
   SendMessage(A,(UINT)WM_SETFONT,(WPARAM)GetStockObject(DEFAULT_GUI_FONT),
     (LPARAM)MAKELPARAM(FALSE,0));
   return A;
}
// color, why not
void BCX_Set_Form_Color (HWND hWnd, COLORREF Kolor)
{
  HBRUSH hbr=CreateSolidBrush(Kolor);
  DeleteObject((HBRUSH)SetClassLong(hWnd,GCL_HBRBACKGROUND,(DWORD)hbr));
  InvalidateRect (hWnd,NULL,TRUE);
}
// the details - corner coordinates,width,height,title
void FormLoad (void)
{
    Form1=BCX_Form("MCI Demo",0,0,197,170);
    SetClassLong(Form1,GCL_STYLE,GetClassLong(Form1,GCL_STYLE)|CS_DBLCLKS);
    BCX_Set_Form_Color(Form1,RGB(0,0,0));
    //  Now create the MCIWnd 
    MCIFrame=MCIWndCreate(Form1,(HINSTANCE)ghInst,WS_CHILD|WS_VISIBLE|MCIWNDF_NOOPEN|MCIWNDF_NOTIFYALL,"");
    AddMenu(Form1);
    Center(Form1);
    Show(Form1);
}
// event message handler
LRESULT CALLBACK WndProc (HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  static char s[2048];
  memset(&s,0,sizeof(s));
  static char mstr[2048];
  memset(&mstr,0,sizeof(mstr));
  static char mstr1[2048];
  memset(&mstr1,0,sizeof(mstr1));
  while(1)
  {
    if (Msg==WM_CREATE)
    {
      return 0;
      break;
    }
    if (Msg==WM_COMMAND)
    {
      if (LOWORD(wParam)==ID_MENU2)
      {
          MCIWndClose(MCIFrame);
          InitOpenFileName();
          PopFileOpenDlg(Form1,szFile,szFileTitle);
          if(strlen(szFile)>0)
          {
              MCIWndOpen(MCIFrame,szFile,0);
          }
          return 0;
      }
      if(LOWORD(wParam)==ID_MENU3)
      {
          MCIWndClose(MCIFrame);
          ExitProcess(0);
      }
      break;
    }
    if (Msg==MCIWNDM_NOTIFYMODE)
    {
      while(1)
      {
        if ((long)lParam==MCI_MODE_NOT_READY)
        {
          SetWindowText(Form1,"Not Ready");
          break;
        }
        if ((long)lParam==MCI_MODE_PAUSE)
        {
          SetWindowText(Form1,"Paused");
          break;
        }
        if ((long)lParam==MCI_MODE_PLAY)
        {
          SetWindowText(Form1,"Playing");
          break;
        }
        if ((long)lParam==MCI_MODE_STOP)
        {
          SetWindowText(Form1,"Stopped");
          break;
        }
        if ((long)lParam==MCI_MODE_OPEN)
        {
          SetWindowText(Form1,"Opening");
          break;
        }
        if ((long)lParam==MCI_MODE_RECORD)
        {
          SetWindowText(Form1,"Recording");
          break;
        }
        if ((long)lParam==MCI_MODE_SEEK)
        {
          SetWindowText(Form1,"Seeking");
        }
        break;
      }
      break;
    }
    if (Msg==MCIWNDM_NOTIFYMEDIA)
    {
      SetWindowText(Form1,(LPSTR)lParam);
      break;
    }
    if (Msg==MCIWNDM_NOTIFYPOS)
    {
      SetWindowText(Form1,str(MCIWndGetPosition(MCIFrame)));
      break;
    }
    if (Msg==MCIWNDM_NOTIFYERROR)
    {
      SetWindowText(Form1,"MCI ERROR");
      break;
    }
    if (Msg==WM_PAINT)
    {
      //  The VideoWindow is restricted to a ratio of 4:3 here 
      break;
    }
    if (Msg==WM_SIZE)
    {
      static  WORD  Basedsp;
      memset(&Basedsp,0,sizeof(Basedsp));
      static  WORD  Cntr;
      memset(&Cntr,0,sizeof(Cntr));
      Basedsp=(HIWORD(lParam)-20)/3;
      Cntr=(LOWORD(lParam)-(Basedsp*4))/2;
      MoveWindow(MCIFrame,Cntr,0,(Basedsp*4),HIWORD(lParam),TRUE);
      //  Don't forget to close opened Files 
      break;
    }
    if (Msg==WM_CLOSE)
    {
      MCIWndClose(MCIFrame);
      DestroyWindow(Form1);
      return 0;
      break;
    }
    if (Msg==WM_DESTROY)
    {
      MCIWndClose(MCIFrame);
      PostQuitMessage(0);
      return 0;
    }
    break;
  }
  // tidy up and exit program
  if (Msg==WM_DESTROY)
  {
       UnregisterClass(BCX_ClassName,BCX_hInstance);
       PostQuitMessage(0);
  }
  return DefWindowProc(hWnd,Msg,wParam,lParam);
}
// tons of options for the neat file dialog box
int InitOpenFileName (void)
{
  *szFile=0;
  *szFileTitle=0;
  OpenFileName.lStructSize=sizeof(OPENFILENAME);
  OpenFileName.hwndOwner=MCIFrame;
  OpenFileName.hInstance=(HINSTANCE)ghInst;
  OpenFileName.lpstrFilter =
    "Avi Files (*.AVI)\0*.avi\0All Files(*.*)\0*.*\0\0";
  OpenFileName.lpstrCustomFilter=NULL;
  OpenFileName.nMaxCustFilter=0;
  OpenFileName.nFilterIndex=0;
  OpenFileName.lpstrFile=szFile;
  OpenFileName.nMaxFile=MAX_PATH;
  OpenFileName.lpstrFileTitle=szFileTitle;
  OpenFileName.nMaxFileTitle=MAX_PATH;
  OpenFileName.lpstrInitialDir=curdir();
  OpenFileName.lpstrTitle=NULL;
  OpenFileName.nFileOffset=0;
  OpenFileName.nFileExtension=0;
  OpenFileName.lpstrDefExt="*.avi";
  OpenFileName.lCustData=0L;
  OpenFileName.Flags=OFN_SHOWHELP|OFN_PATHMUSTEXIST|OFN_FILEMUSTEXIST|OFN_HIDEREADONLY;
  OpenFileName.lpfnHook=NULL;
  OpenFileName.lpTemplateName=NULL;
  return 0;
}
int PopFileOpenDlg (HWND Form1, char *szFile, char *szFileTitle)
{
  OpenFileName.lpstrTitle="Open File";
  OpenFileName.hwndOwner=MCIFrame;
  OpenFileName.lpstrFile=szFile;
  OpenFileName.lpstrFileTitle=szFileTitle;
  OpenFileName.Flags=OFN_EXPLORER|OFN_CREATEPROMPT;
  return GetOpenFileNamePreview(&OpenFileName);
}
BOOL AddMenu (HWND hwndOwner)
{
  MainMenu=CreateMenu();
  FileMenu=CreateMenu();
  InsertMenu(MainMenu,0,MF_POPUP,(UINT)FileMenu,"&File");
  AppendMenu(FileMenu,MF_STRING,ID_MENU2,"&Open");
  AppendMenu(FileMenu,MF_STRING,ID_MENU3,"&Exit");
  // activate the menu 
  if (!SetMenu(hwndOwner,MainMenu))
  {
      return FALSE;
  }
  return TRUE;
}
// ************* credit to a true genius Kevin *****************
//   Created with BCX -- The BASIC To C Translator (ver 5.02)
//  BCX (c) 1999, 2000, 2001, 2002, 2003, 2004 by Kevin Diggins
// **********************