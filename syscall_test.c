#include <stdio.h>
#include <unistd.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <string.h>
#include <stdlib.h>

#define ADD 442
#define SUB 443
#define MUL 444
#define REM 445

int add(int x, int y){

	int result = 0;
        if(x<0 && y<0){// x가 음수, y가 음수일 때

                x = -x; // x를 양수로(절대값)수
                y = -y; // y를 양수로(절대값)
                result = syscall(ADD,x,y); // 구한 절대값들 더해줌
                printf("result = %d\n", -result); // 절대값들 합의 음수

        }else if(x<0 && y>0){ // x가 음수, y가 양수일 때

		x = -x;// x를 양수로(절대값)
		if(y>x){ // y의 값이 x의 절대값보다 클 때 서로 바꿔줌
			int temp = y;
			y = x;
			x = temp;
		
			result = syscall(SUB, x,y);// 원래 y의 값이 더 컸으므로
			printf("result = %d\n", result); // 값은 양수로 나옴
		}else{
			result = syscall(SUB,x,y);// x의 절대값이 더 컸으므로
			printf("result = %d\n", -result);// 값은 음수로 나옴
		}
	}
	else if(x>0 && y<0){ // x가 양수, y가 음수일 때
		
		y = -y;// y를 양수로(절대값)
		if(y>x){// y의 절대값이 x의 값보다 클 때 서로 바꿔줌
                        int temp = y;
                        y = x;
                        x = temp;
              
			result = syscall(SUB, x, y);//원래 y의 절대값이 더 컸으므로 
			printf("result = %d\n", -result);//값은 음수로 나옴
		}else{
			result = syscall(SUB,x,y);// x의 값이 더 컸으므로
			printf("result = %d\n", result);//값은 양수로 나옴
		}
	}
	else{// x가 0이상, y가 0이상 일때

                result = syscall(ADD,x,y);
                printf("result = %d\n", result);
        }
	return 0;
}
int sub(int x,int y){

	int result=0;
	
	if(x<0 && y>0){//x가 음수, y가 양수일때

		x = -x;//x를 양수로(절대값)
		result = syscall(ADD,x,y);//절대값과 양수를 더해줌
		printf("result = %d\n", -result);// 합들의 음수

	}else if(x>0 && y<0){ // x가 양수, y가 음수일 때

		y = -y;//y를 양수로(절대값)
		result = syscall(ADD, x,y);//절대값과 양수를 더해줌
		printf("result = %d\n", result);//마이너스 2개가 +와 같으므로 절대값의 합과 같음

	}else if(x<0 && y<0){//x가 음수, y가 음수 일 때

		x = -x;//x를 양수로(절대값)
		y = -y;//y를 양수로(절대값)
		if(y > x){//y의 절대값이 x의 절대값보다 클 때 서로 바꿔줌
			int temp = y;
			y = x;
			x = temp;
			result = syscall(SUB,x,y);//절대값들의 차
			printf("result = %d\n", result);//원래 y의 절대값이 더 컸으므로 양수
		}else{
			result = syscall(SUB,x,y);//절대값들의 차
			printf("result = %d\n", -result);//x의 절대값이 더 크므로 음수
		}
	}
	else{//x가 0이상, y가 0이상 일 때
		if(y>x){//y의 값이 x보다 클 때 서로 바꿔줌
                        int temp = y;
                        y = x;
                        x = temp;

			result = syscall(SUB,x,y);
			printf("result = %d\n", -result);//원래 y의 값이 더 컸으므로 음수
		}else{
			result = syscall(SUB,x,y);
			printf("result = %d\n", result);//x의 값이 더 컸으므로 양수
		}
	}

	return 0;
}

int mul(int x, int y){

	int result=0;
	if(x>0 && y<0){//x가 양수, y가 음수일 때

		y = -y;//y를 양수로(절대값)
		result = syscall(MUL,x,y);
		printf("result = %d\n", -result);//음수가 하나였으므로 결과도 음수

	}else if(x<0 && y>0){//x가 음수, y가 양수일 때

		x = -x;//x를 양수로(절대값)
		result = syscall(MUL,x,y);
		printf("result = %d\n", -result);//음수가 하나였으므로 결과도 음수

	}else if(x<0 && y<0){//x가 음수, y가 음수일 때

		x = -x;//x를 양수로(절대값)
		y = -y;//y를 양수로(절대값)
		result = syscall(MUL,x,y);
		printf("result = %d\n", result);//음수가 2개였으므로 결과는 양수
	}else{//x가 0이상, y가 0이상일 떄

		result = syscall(MUL,x,y);
		printf("result = %d\n", result);// 0이상의 값들 이므로 결과는 양수
	}
	return 0;
}
int rem(int x, int y){

	int result=0;

	if(y==0){//나누는 값이 0일 때

		printf("0으로 나눌 수 없습니다.\n");
		exit(1);
	}

	if(x<0 && y>0){//x가 음수, y가 양수일 때

		x = -x;//x를 양수로(절대값)
		result = syscall(REM,x,y);
		printf("result = %d\n", -result);//음수가 1개이므로 결과도 음수

	}else if(x>0 && y<0){//x가 양수, y가 음수일 때

		y = -y;//y를 양수로(절대값)
		result = syscall(REM,x,y);
		printf("result = %d\n", -result);//음수가 1개이므로 결과도 음수

	}else if(x<0 && y<0){//x가 음수, y가 음수일 때

		x = -x;//x를 양수로(절대값)
		y = -y;//y를 양수로(절대값)
		result = syscall(REM,x,y);
		printf("result = %d\n", result);//음수가 2개이므로 결과는 양수
	}else{//x가 0이상, y가 0초과일 때

		result = syscall(REM,x,y);
		printf("result = %d\n", result);//음수가 하나도 없으므로 결과는 양수
	}

	return 0;
}

int main(){


	int x,y;
	char op;


	printf(">> ");
	scanf("%d%c%d", &x,&op,&y);
	
	if(op == '+'){
		add(x,y);
	}else if(op == '-'){
		sub(x,y);
	}else if(op == '*'){
		mul(x,y);
	}else if(op == '%'){
		rem(x,y);
	}
	return 0;
}

