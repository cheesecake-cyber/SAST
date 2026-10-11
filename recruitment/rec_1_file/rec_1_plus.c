//GPT做法

#include <stdio.h>

int main(void) {
    int n, x, y;
    scanf("%d", &n);

    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    scanf("%d %d", &x, &y);

    int face = 0;       // 0北，1东，2南，3西
    int num = 0;        // 朝南次数
    int last = -1;      // 上一条正常转向
    int cc = 0;         // 连续同向转弯次数
    int dizzy = 0;      // 剩余眩晕命令数

    for (int i = 0; i < n; i++) {
        int op = arr[i]; //op代表本次应该怎样转

        if (dizzy > 0) { //还在眩晕
            op = 2;
            dizzy--;
            last = -1;
            cc = 0;
        } else if (op == 0 || op == 1) { //不晕，并且是左右转（可能导致晕）
            if (op == last) {
                cc++;
            } else { //第一次循环一定走到这里
                last = op;
                cc = 1;
            }

            if (cc == x) { //导致晕眩
                dizzy = y;
                last = -1;
                cc = 0;
            }
        } else { //向后转打断晕眩累积
            last = -1;
            cc = 0;
        }

        face = (face + (op == 0 ? 3 : op)) % 4; //朝向重置

        if (face == 2) {
            num++;
        }
    }

    printf("%d\n", num);
    return 0;
}

/*程序思路：
相比第一版增加了last-op的动态变化，dizzy的固定预处理特性也变成了动态的晕眩倒计时
原版的switch被替换成一个条件运算符，简洁清晰
程序大为精简

关键思想：
动态调整（通过last和op的比对，而不是单纯从数组里抽元素）

两版代码共通点：重视代码安全，防止溢出

通过两版程序我学到了什么：
多变量接替赋值以做到状态更新；条件运算符；代码安全检查；其他语法细节
*/