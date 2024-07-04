#include <stdio.h>
#include <time.h>

int count =0;
void move(int n,char start,char end,char sub){
  count ++;
}
void hanoi(int n,char start,char end,char sub){
  if (n==1){
    move(n, start,end,sub);
    return;
  }
  else{
  hanoi(n-1,start,sub,end);
  move(n, start,end,sub);
  hanoi(n-1,sub,end,start);
  }

}
int main(){
  clock_t start_time = clock();
  hanoi(20,'a','b','c'); 
  printf("총 움직인 횟수는: %d\n", count);
  clock_t finish_time = clock();
  printf("실행시간: %f",(double)(finish_time - start_time)/(CLOCKS_PER_SEC/10000));
}
