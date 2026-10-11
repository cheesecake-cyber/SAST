//GPT展示实力

#include <stdio.h>
#include <string.h>

int main(void) {
    int n;
    scanf("%d", &n);

    char s[n][6];
    int len[n];
    int pre[n][6]; // 前缀和
    int freq[6][46] = {0}; // 按长度和数字总和统计票数；46源于5*9+1


    //预处理：初始化、统计前缀和、重新归类为freq
    for (int i = 0; i < n; i++) {
        scanf("%s", s[i]);
        len[i] = strlen(s[i]);

        pre[i][0] = 0;
        for (int k = 0; k < len[i]; k++) {
            pre[i][k + 1] = pre[i][k] + s[i][k] - '0';
        }

        //对于第i个字符串：
        //freq[长度][数字总和]++;
        freq[len[i]][pre[i][len[i]]]++;
        //freq将所有字符串重新统计归类，得到了最有用的信息
        //后面freq与key的配合，将时间复杂度大幅降低
    }

    long long num = 0;

    for (int a = 1; a <= 5; a++) {     //这里的a和b直接就是长度。这是freq的功劳
        for (int b = 1; b <= 5; b++) { //很关键！由于freq事先对每个字符串重新统计了
            if ((a + b) % 2 != 0) {    //所以这里避免了遍历两遍到n，使得时间复杂度骤降⬇️
                continue;
            }

            int half = (a + b) / 2;

            if (a >= b) {
                // 前半部分的分界线在第一张票内
                for (int i = 0; i < n; i++) { //这里就是最复杂的地方，O(25n)
                    if (len[i] != a) {
                        continue;
                    }

                    int key = 2 * pre[i][half] - pre[i][a];
                    // = pre[i][half] - （pre[i][a] - pre[i][half]）
                    if (key >= 0 && key <= 45) { //最多5个9连加
                        num += freq[b][key];
                        //精妙之处：这里求出的key就是想要的后半部分和。
                        //因此直接从freq里调出后半部分（长度为b）符合这个条件（数字总和为key）的字符串数量即可
                    }
                }
            } else {
                // 前半部分的分界线在第二张票内
                int k = half - a;

                for (int j = 0; j < n; j++) { //与if语句下的同理
                    if (len[j] != b) {
                        continue;
                    }

                    int key = pre[j][b] - 2 * pre[j][k];
                    //依然求出第一张票应有的数字和key
                    if (key >= 0 && key <= 45) {
                        num += freq[a][key];
                    }
                }
            }
        }
    }

    printf("%lld\n", num);
    return 0;
}

/*程序思路：
使用前缀和简化计算，freq频率统计降低时间复杂度。
相比前两代程序，创新在于用freq配合key的搭配，逆向从数字和的角度确定符合要求的字符串数量，
从而避免了正向讨论O(n^2)的困境。
freq数组作为关键的中间产物截断了任务，将之变为简单的两部分：
求出freq，O(n)；用freq判断字符串是否符合要求，O(25n)。
这就不会导致复杂任务叠加造成计算量指数上涨。

关键思想：
复杂任务的拆解；信息的再整合（不同表达形式）


三版程序的共通点：都将代码分成了输入、预处理、主体程序、输出几部分，保证程序可读性
有的还设计了函数。

通过三版程序我学到了什么：
函数语法；字符转化为数字（-'0'）；多个关键字如scanf、strlen（以及<string.h>库）;前缀和算法；
使用continue减少嵌套；freq-key频率统计技巧；代码debug；应用ai工具学习编程和写代码；其他语法细节
*/