#ifndef HIVEDOUBLEBUFFER_H
#define HIVEDOUBLEBUFFER_H

#include <QDebug>

#include <list>
#include <iostream>

template <typename T>
class HiveDoubleBuffer final
{
public:
  using PushedCb = std::function<void (HiveDoubleBuffer <T>*)>;

  HiveDoubleBuffer();
  ~HiveDoubleBuffer();

  T front();
  void push_front(T item);
  bool pop_front();

  void bindCb(const PushedCb &value);

private:
  using Container = std::list<T>;

  Container buffer1;
  Container buffer2;
  bool reading = false;
  bool writing = false;
  bool isFliping = false;

  Container *inbound_buffer = &buffer1;
  Container *outbound_buffer = &buffer2;

  PushedCb pushed_cb;

  void flip();
};

template<typename T>
HiveDoubleBuffer<T>::HiveDoubleBuffer()
{
  //! Make sure T is a pointer of a type
  T *t = nullptr;
}

template<typename T>
HiveDoubleBuffer<T>::~HiveDoubleBuffer()
{
  printf("Destroying HiveDoubleBuffer<T>...\n");

}

template<typename T>
void HiveDoubleBuffer<T>::push_front(T item)
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
  if(pushed_cb)
    {
      pushed_cb(this);
    }
}

template<typename T>
T HiveDoubleBuffer<T>::front()
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
bool HiveDoubleBuffer<T>::pop_front()
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
void HiveDoubleBuffer<T>::bindCb(const PushedCb &value)
{
  pushed_cb = value;
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
