#ifndef HIVEDOUBLEBUFFER_H
#define HIVEDOUBLEBUFFER_H

#include <QDebug>

#include <forward_list>

template <typename T>
class HiveDoubleBuffer final
{
public:
  HiveDoubleBuffer();

  void push(T *item);
  bool take(T *item);

private:
  using Container = std::forward_list<T*>;
  Container buffer1;
  Container buffer2;
  bool reading = false;
  bool writing = false;
  bool isFliping = false;

  std::forward_list<T*> *inbound_buffer = &buffer1;
  std::forward_list<T*> *outbound_buffer = &buffer2;

  void flip();
};

template<typename T>
void HiveDoubleBuffer<T>::push(T *item)
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
}

template<typename T>
bool HiveDoubleBuffer<T>::take(T *item)
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
      item = outbound_buffer->front();
      outbound_buffer->pop_front();
      reading = false;
      break;
    }
  return true;
}

template<typename T>
void HiveDoubleBuffer<T>::flip()
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
