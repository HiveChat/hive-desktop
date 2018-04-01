#include <iostream>
#include <thread>
#include <stdlib.h>


#include "hivedoublebuffer.h"

HiveDoubleBuffer<char*> buffer;
int counter = 0;

using namespace std;

/*!
 * \brief randomString returns a char* string if random characters in length len
 * \param len length of the random string
 * \return returns a char* string if random characters in length len
 */
char* randomString(const int &len = 32)
{
  const static char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.-#'?!";
  char *randomString = NULL;

  if (len)
    {
      randomString = (char*)malloc(sizeof(char) * (len +1));

      if (randomString)
        {
          for (int n = 0; n < len; n ++)
            {
              int key = rand() % (int)(sizeof(charset) -1);
              randomString[n] = charset[key];
            }
          randomString[len] = '\0';
        }
    }

  return randomString;
}

/*!
 * \brief inbound Pushes random strings into double buffer.
 * It also simulates streams of data in difference length pushing into the buffer with radom time interval.
 */
void inbound()
{
  while(1)
    {
      while(1)
        {
          counter ++;
          char *str = randomString();
          printf("%d push: %s\n", counter, str);
          buffer.push_front(str);

          //! Simulate the time gap between each received packet.
          this_thread::sleep_for(std::chrono::milliseconds(5));
          //! Simulate the length of a connection by having a 1/30 chance of quitting this loop and rest for a while.
          if((rand() % 30) < 1)
            {
              break;
            }
        }

      //! Simulate the time gap between each connection.
      this_thread::sleep_for(std::chrono::milliseconds(rand() % 300));
    }
}

int main()
{
  //! New a child thread to run the function inbound to simulate net I/O pushing data into the buffer.
  std::thread childThread(inbound);

  while(1)
    {
      while (1)
        {
          char* string = buffer.front();
          if(!string)
            {
              break;
            }
          counter --;
          printf("%d take: %s\n", counter, string);
          buffer.pop_front();

          //! Simulate processing time for each packet
          this_thread::sleep_for(std::chrono::milliseconds(rand() % 6));
        }

      //! Check if both buffers are still empty very 100ms
      this_thread::sleep_for(std::chrono::milliseconds(100));
    }


  return 0;
}
