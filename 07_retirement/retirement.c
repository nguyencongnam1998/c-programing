#include <stdlib.h>
#include <stdio.h>

struct _retire_infor
{
  int months;
  double contribution;
  double rate_of_return;
};
typedef struct _retire_infor retire_infor;

void retirement(int startAge, double initial, retire_infor working, retire_infor retired){
  double balance = initial;
  int Age = startAge/12;
  int month = startAge%12;
  printf("Age %3d month %2d you have $%.2lf\n",Age,month,balance);
  for (int i=0; i < working.months;i++){
    balance = balance + working.contribution + balance*(working.rate_of_return/12);
    month++;
    if (month==12){
      Age++;
      month=0;
    }
    printf("Age %3d month %2d you have $%.2lf\n",Age,month,balance);
  }
  for (int i=1; i < retired.months;i++){
    balance = balance + retired.contribution + balance*(retired.rate_of_return/12);
    month++;
    if (month==12){
      Age++;
      month=0;
    }
    printf("Age %3d month %2d you have $%.2lf\n",Age,month,balance);
  }
}

int main(void){
  retire_infor Working;
  retire_infor Retired;
  
  Working.months = 489;
  Working.contribution = 1000;
  Working.rate_of_return = 0.045;

  Retired.months = 384;
  Retired.contribution = -4000;
  Retired.rate_of_return = 0.01;

  int initial_ = 21345;
  int months_ = 327;

  retirement(months_, initial_, Working, Retired);

  return 0;
}
