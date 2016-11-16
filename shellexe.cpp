#include <stdio.h>
#include <stdlib.h>



int main(int argc, char* argv[]){

  int ret1;
  int ret2;

  int state;



  //コマンドの実行

  ret1 = system("ping -c 192.168.1.1");
  ret2 = system("ls -lh");



  //子プロセスが正常に終了している場合のみステータスを取得

  if(WIFEXITED(ret1)){

    state = WEXITSTATUS(ret1);

  }else{

    state = -1;

  }



  printf("STATUS=%d\n", state);



  return ret1;

}
