#include <iostream>
#include <thread>
#include <stdlib.h>

#include "hivedoublebuffer.h"

HiveDoubleBuffer<char*> buffer;
int counter = 0;


using namespace std;

void inbound()
{
  while(1)
    {
      while(1)
        {
          int length = 32;
          static char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.-#'?!";
          char *randomString = NULL;

          if (length)
            {
              randomString = (char*)malloc(sizeof(char) * (length +1));

              if (randomString)
                {
                  for (int n = 0;n < length;n++)
                    {
                      int key = rand() % (int)(sizeof(charset) -1);
                      randomString[n] = charset[key];
                    }

                  randomString[length] = '\0';
                }
            }
          counter ++;
          printf("%d push: %s\n", counter, "randomString");
          buffer.push("randomString");
          if((rand() % 30) < 1)
            {
              break;
            }
        }
      this_thread::sleep_for(std::chrono::milliseconds(rand() % 300));
    }
}

int main()
{
  std::thread childThread(inbound);     // spawn new thread that calls foo()
//  childThread.detach();

  while(1)
    {
      while (1)
        {
          char* string;
          if(!buffer.take(string))
            {
              break;
            }
          counter ++;
          printf("%d take: %s\n", counter, string);
        }
      this_thread::sleep_for(std::chrono::milliseconds(500));
    }


  return 0;
}
