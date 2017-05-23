#include "HomeStack_storage.h"

HomeStack_storage::HomeStack_storage(QWidget *parent)
{
  this->setUpUI(LayoutStyle::Linear);
  this->setIcon(":/img/img/storage.png");
  this->setTitle("Home");
  this->setSubTitle("storage");
  this->addTag("Overview");

  this->setParent(parent);
}


