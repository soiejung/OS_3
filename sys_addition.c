#include <linux/kernel.h>
#include <linux/linkage.h>
#include <linux/syscalls.h>

asmlinkage int sys_addition(int x, int y){

	printk("x : %d",x);
	printk("y : %d", y);
	return x+y;
}

SYSCALL_DEFINE2(addition, int, x, int, y){
	
	return sys_addition(x,y);
}
