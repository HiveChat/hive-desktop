#ifndef HIVEDOUBLEBUFFER_H
#define HIVEDOUBLEBUFFER_H

#include "../libs/libParsley/include/PUdpSocket.h"
#include "../libs/libParsley/include/PFunction.h"

#include <QDebug>

#include <list>
#include <iostream>

template <typename T>
class DoubleBuffer final
{
public:
  DoubleBuffer();
  ~DoubleBuffer();

  Parsley::Callback<void, DoubleBuffer <T>*> onPushed;

  T front();
  void push_front(T item);
  bool pop_front();

private:
  using Container = std::list<T>;

  Container buffer1;
  Container buffer2;
  bool reading = false;
  bool writing = false;
  bool isFliping = false;

  Container *inbound_buffer = &buffer1;
  Container *outbound_buffer = &buffer2;


  void flip();
};

template<typename T>
DoubleBuffer<T>::DoubleBuffer()
{
}

template<typename T>
DoubleBuffer<T>::~DoubleBuffer()
{
  printf("Destroying HiveDoubleBuffer<T>...\n");

}

template<typename T>
void DoubleBuffer<T>::push_front(T item)
{
  while(1)
    {
      if(isFliping)
        {
          //do something is better
          continue;
        }

      writing = true;
      inbound_buffer->push_front(item);
      writing = false;
      break;
    }
  onPushed.call(this);
}

template<typename T>
T DoubleBuffer<T>::front()
{
  while(1)
    {
      if(isFliping)
        {
          //do something is better
          continue;
        }
      if(outbound_buffer->empty())
        {
          flip();
          if(outbound_buffer->empty())
            {
              return nullptr;
            }
        }
      reading = true;
      T item = outbound_buffer->front();
      reading = false;
      return item;
    }
}

template<typename T>
bool DoubleBuffer<T>::pop_front()
{
  while(1)
    {
      if(isFliping)
        {
          //do something is better
          continue;
        }
      if(outbound_buffer->empty())
        {
          flip();
          if(outbound_buffer->empty())
            {
              return false;
            }
        }
      reading = true;
      printf("pop: %s\n", outbound_buffer->front());
      outbound_buffer->pop_front();
      reading = false;
      break;
    }
  return true;
}

template<typename T>
void DoubleBuffer<T>::flip()
{
  isFliping = true;
  while(1)
    {
      if(writing || reading)
        {
          //do something is better
          continue;
        }
      Container *temp = inbound_buffer;
      inbound_buffer = outbound_buffer;
      outbound_buffer = temp;
      break;
    }
  isFliping = false;
}










#endif // HIVEDOUBLEBUFFER_H
