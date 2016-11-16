#include <stdio.h>
#include <stdlib.h>
#include <termios.h> //for kbhit
#include <unistd.h> //for kbhit
#include <fcntl.h> //for kbhit

int kbhit(void)/*{{{*/
{
	struct termios oldt, newt;
	int ch;
	int oldf;

	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

	ch = getchar();

	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	fcntl(STDIN_FILENO, F_SETFL, oldf);

	if (ch != EOF) {
		ungetc(ch, stdin);
		return 1;
	}

	return 0;

}/*}}}*/

bool interrupt()/*{{{*/
{
	int key;
	bool rtn = true;
	if (kbhit()) {
		key=getchar();
		if(key=='c'){
			printf("\033[D"); //move cursor to left
			printf("interrupted\n");
			rtn = false;
		}else{
			rtn = true;
		}
	}
	return rtn;
}/*}}}*/

int main(int argc, char* argv[]){
	int ret0;
	int ret1;
	int ret2;

	int state=1;

	while(interrupt()){
		while(state&&interrupt()){
			//コマンドの実行
			// ret0 = system("ping -c 192.168.1.1");
			ret1 = system("mv ./auto_test/bfr/* ./auto_test/aft/ 2> /dev/null");
			// ret2 = system("ls -lh");
			//子プロセスが正常に終了している場合のみステータスを取得
			if(WIFEXITED(ret1)){
				state = WEXITSTATUS(ret1);
			}else{
				state = -1;
			}
			if(!interrupt()){
				return 0;
			}
		}
		// printf("run\n");
		state = -1;
		// printf("STATUS=%d\n", state);
		// system("echo \"bagrun\"");
		system("/home/amsl/MyShellScript/auto_test");
		// system("echo \"graph\"");
	}

	return ret1;
}
