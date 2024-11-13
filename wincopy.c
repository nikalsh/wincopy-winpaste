#include <stdio.h>
#include <stdbool.h>
#include <locale.h>
#include <Windows.h>
#include <WinUser.h>

#define println(format, ...) printf("%s::%d::%s: "format"\n", __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)

int main(int argc, char** argv)
{
  SetConsoleCP(CP_UTF8);
  SetConsoleOutputCP(CP_UTF8);
  
  char* old_locale;
  char* saved_locale;
  old_locale = setlocale(LC_ALL, NULL);
  saved_locale = _strdup(old_locale);
  setlocale(LC_ALL, "");
  
  int ret = 0;
  HGLOBAL hMem = NULL;
  
  char line[256];
  char lines[2048];
  int len = 0;
    
  while (fgets (line, sizeof(line), stdin)) {
    memcpy(&lines[len], line, sizeof(line));
    len = len + strlen(line);
  }

  bool opened = OpenClipboard(NULL);
  if (!opened) {
    println("Could not open clipboard."); 
    ret = 1;
    goto exit;
  }
  
  len = len + 1;
  hMem = GlobalAlloc(GMEM_MOVEABLE, len);
  memcpy(GlobalLock(hMem), lines, len);
  GlobalUnlock(hMem);

  bool emptied = EmptyClipboard();
  if (!emptied) {
    println("Could not empty clipboard.");
    ret = 1;
    goto exit;
  }

  bool set = SetClipboardData(CF_TEXT, hMem);
  bool closed = CloseClipboard();
  if (!set) {
    println("Could not set clipboard.");
    ret = 1;
    goto exit;
  }

  if (!closed) {
    println("Could not close clipboard.");
    ret = 1;
    goto exit;
  }
  
 exit:
  GlobalFree(hMem);
  setlocale(LC_ALL, saved_locale);
  return ret;
} 
