#include "HomeStack_network.h"

HomeStack_network::HomeStack_network(QWidget *parent)
  : ScrollStack(parent)
{
  this->setUpUI(LayoutStyle::Linear);
}
