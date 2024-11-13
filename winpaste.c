#include <stdbool.h>
#include <stdio.h>
#include <locale.h>
#include <Windows.h>
#include <WinUser.h>

#define println(format, ...) printf("%s::%d::%s: "format"\n", __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)

int main(int argc, char** argv)
{
  SetConsoleOutputCP(CP_UTF8);
  SetConsoleCP(CP_UTF8);
  
  char* old_locale;
  char* saved_locale;
  old_locale = setlocale(LC_ALL, NULL);
  saved_locale = _strdup(old_locale);
  setlocale(LC_ALL, "");
  
  int ret = 0;
  
  bool opened = OpenClipboard(NULL);
  if (!opened) {
    println("Could not open clipboard.");
    ret = 1;
    goto exit;
  }

  HANDLE handle = GetClipboardData(CF_TEXT);
  if (handle == NULL) {
    println("Could not get clipboard data.");
    ret = 1;
    goto exit;
  }

  bool closed = CloseClipboard();
  if (!closed) {
    println("Could not close clipboard.");
    ret = 1;
    goto exit;
  }
  
  printf("%s", (char*) handle);
  
 exit:
  setlocale(LC_ALL, saved_locale);
  return ret;
}
