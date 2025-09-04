#include <stdarg.h>
#include <stdio.h>


void print_addrs(int num, ...) {
  va_list arglist;

  va_start(arglist, num);

  printf("addresses-- >");
  for (int i=0; i < num; i++) {
    printf("(%d)%p, ",i, va_arg(arglist, void*));
  }
  printf(".\n");

  va_end(arglist);
  return;
}

int main(void) {
  int x;
  print_addrs(3, main, NULL, &x);
  print_addrs(0);
  print_addrs(2, &x, &main);
  print_addrs(9, main, NULL);
}
