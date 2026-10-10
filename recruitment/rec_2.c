#include <stdio.h>
#include <string.h>

//数字转换函数
void shiftf(char str1[], char str2[], int arr1[], int arr2[]) { //将一对给定的字符串转化为数组
    for (int i = 0; i < strlen(str1); i++) {
        arr1[i] = str1[i] - '0';
    }
    for (int i = 0; i < strlen(str2); i++) {
        arr2[i] = str2[i] - '0';
    }
}

//合并函数
void combine(int len1, int len2, int arr1[], int arr2[], int arr[]) { //将两个已知长度的数组合并
    int lens = len1 + len2;

    for (int i = 0; i < len1; i++) {
        arr[i] = arr1[i];
    }
    for (int i = len1; i < lens; i++) {
        arr[i] = arr2[i - len1];
    }
}

//求和-比大小函数
int sum_comp(int lens, int arr[lens]){ //对一个偶数个元素的数组前后半求和并比大小
    int sum1 = 0, sum2 = 0;
    for (int i = 0; i < lens / 2; i++){
        sum1 += arr[i];
    }
    for (int i = lens / 2; i < lens; i++){
        sum2 += arr[i];
    }
    if (sum1 == sum2){
        return 1; //符合条件的标志
    }
    return 0;
}


int main(void){
    long num = 0; //“答案可能较大，在 C 语言中应使用足够大的整数类型保存。“

    
    //接收输入
    int n; scanf("%d", &n);
    char str[n][5]; //二维数组，包含n个一维数组（n行），每个一维数组内不超过5个元素
    int len[n]; //寄存每个字符串的长度

    for (int i = 0; i < n; i++){
        scanf("%s", str[i]);
        len[i] = strlen(str[i]);
    } //同时完成两个数组的输入
    

    //正式工作
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){ //双层循环遍历挑选两个数组（可能相同）进行测试
            if((len[i] + len[j]) % 2 == 0){ //第一关：偶数判定
                //预备好函数操作的对象
                int arr[10], arr1[5], arr2[5];
                //调用数字转换函数
                shiftf(str[i], str[j], arr1, arr2); //arr1、arr2的内容被改变了
                //调用合并函数
                combine(len[i], len[j], arr1, arr2, arr);
                //调用求和-比大小函数
                if (sum_comp(len[i] + len[j], arr)){
                    num++;
                }
            }
        }
    } //就是有点暴力：时间复杂度来到O(n^2)。只能祈祷实际输入别太大

    printf("%ld\n", num);

    return 0;
}