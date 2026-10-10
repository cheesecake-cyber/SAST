#include <stdio.h>
int main(void){
    int face = 0;  //小明面朝向的方向
    int num = 0;  //计数小明回答“南”的数量
    
    
    //接收输入
    int n;
    scanf("%d", &n);
    
    int arr[n]; 
    for (int i = 0; i < n; i++){
        scanf("%d", &arr[i]);
    } //遍历数组输入数据。

    int x, y;
    scanf("%d %d", &x, &y);

    
    //预处理！
    //先看看会不会晕、什么时候晕
    int cc = 1; //晕眩计数器：有多少次重复？跟x比较
    int dizzy[n]; //晕眩启动器，确定晕眩位置
    for (int i = 0; i < n; i++){
        dizzy[i] = 0;
    } //dizzy初始化
    
    if ((x == 1) && (arr[0] != 2)){
        dizzy[0] = 1;
    } //补丁，防止x=1的情况第一次命令不晕眩

    for (int i = 1; i < n; i++){ //晕眩前摇累积
        if ((arr[i] == 1) && (arr[i-1] == 1)) { //右转又右转➡️
            cc++;
        }else if ((arr[i] == 0) && (arr[i-1] == 0)){ //左转又左转⬅️
            cc++;
        }else{
            cc = 1;
        }
        if (cc == x){
            cc = 1;
            dizzy[i] = 1; //通过dizzy数组排除只能执行最后一次晕眩的弊端
            i += y + 1; 
            /*模拟晕眩跳过y个数，保证dizzy数组和实际晕眩情况一致。
            这里多+1的意义是避免跳过y条命令后，arr[i-1]仍是眩晕触发前的命令，
            造成眩晕过程中的命令（arr[i-1]）被纳入计数*/
        }
    }
    
    
    //转圈阶段
    for (int i = 0; i < n; i++){
        switch(arr[i]){ //这段只管改变非晕眩的小明的本身状态
            case 0: 
                face += 3; //逆时针90度就是顺时针270度
                break;
            case 1:
                face++;
                break;
            case 2:
                face += 2;
                break;
            default:
                break; //这句没用，以备不时之需
        }
        if (face % 4 == 2){
            num++; //最关键的：喊“南！”
        }
        if (dizzy[i] == 1){ //晕了！
            for (int j = 0; j < y; j++){
                face += 2;
            }
            if (i + y < n){ //保证程序安全，防止i大小超过arr数组限制
                i += y; //覆盖原本动作
            }else{
                break;
            }
        }
        face %= 4; //保证程序安全，保证face不会过大溢出
    }


    //总结
    printf("%d\n", num);

    return 0;
}

/*有个问题：眩晕过程中还会喊“南”吗？眩晕结束时如果面向南，会喊“南”吗？
我默认：过程中不喊；结束也不喊*/
