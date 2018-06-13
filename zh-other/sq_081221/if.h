#ifndef TEMPLATE_IF__H
#define TEMPLATE_IF__H

template <bool cond, class Then, class Else>
struct If
{
  typedef Then Ret;
};

template <class Then, class Else>
struct If<false, Then, Else>
{
  typedef Else Ret;
};

#endif
