//接下来欣赏GPT的作品
//注释全部为我的批注

#include <stdio.h>
#include <string.h>

int main(void) {
    int n;
    scanf("%d", &n);

    char s[n][6];
    int len[n];
    int sum[n][6];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 6; j++) {
            sum[i][j] = 0; //初始化
        }
    }

    for (int i = 0; i < n; i++) {
        scanf("%s", s[i]);
        len[i] = strlen(s[i]); //沿用我的思路，使用专门数组记录字符串长度

        for (int k = 0; k < len[i]; k++) {
            sum[i][k + 1] = sum[i][k] + s[i][k] - '0'; //前缀和
        }
    }

    long long num = 0; //还是不放心long啊

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) { //但是这里！时间复杂度依然是O(n^2)
            int total = len[i] + len[j];

            if (total % 2 != 0) {
                continue; //好想法，跟我的条件语句反着来，好处是把主体程序放在else（或者说if外面）
                //这样做到了更少的嵌套，更清晰的控制流
            }

            int half = total / 2;
            int left, right;

            if (half <= len[i]) {
                left = sum[i][half]; //用前缀和直接提取
                right = sum[i][len[i]] - sum[i][half]
                      + sum[j][len[j]];
            } else {
                left = sum[i][len[i]]
                     + sum[j][half - len[i]];
                right = sum[j][len[j]]
                      - sum[j][half - len[i]];
            }

            if (left == right) {
                num++;
            } //上面两个if完成了判断两半之和的作用，省去了我的三个函数（前缀和也有功劳）
        }
    }

    printf("%lld\n", num);
    return 0;
}

/*程序思路：
依然暴力遍历，但是用前缀和清晰化简便化了处理字符串的过程：
省去了数字转换（在求出前缀和时就已完成）；
将两半求和变为一组条件语句，用前缀和简洁明了的算出left和right；
而后比大小就可以用最简单的if语句直接完成。
这样移除了三个不必要的函数，提高了可读性和美观程度。

关键思想：
信息整合以简化调取难度（前缀和）
*/
