#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H

template <typename Handler_T>
class Event;
template <class Event_T>
class Channel;
class Publisher;
class Subscriber;

template <typename Handler_T>
class Event
{
public:
  Event();
};

template <class Event_T>
class Channel
{
public:
  Channel();
};

class Publisher
{
public:
  Publisher();
};

class Subscriber
{
public:
  Subscriber();
};

#endif // SUBSCRIBER_H
