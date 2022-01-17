/*
Example:
2 ABBAJJKZKZ
3 GACCBDDBAGEE
3 GACCBGDDBAEE
1 ABCBCA
0

Result:
All customers tanned successfully.
1 customer(s) walked away.
All customers tanned successfully.
2 customer(s) walked away.
*/

#include <cstdio>
#include <cstdlib>
#include <cstring>

char array[50];
int words[50];
int N;

int main(void){
    int i, j;
    int len, leftnum;
    int fullnum;
    while (scanf("%d", &N) , N != 0){
        scanf(" %s", array);
        memset(words, 0, sizeof(words));
        len = strlen(array);
        leftnum = fullnum = 0;
        for (i = 0; i < len; i ++){
            if (words[array[i] - '0'] == 0){
                if (fullnum < N){
                    words[array[i] - '0'] = 1;
                    fullnum++;
                }
                else{
                    words[array[i] - '0'] = 2;
                    leftnum++;
                }
            }
            else if (words[array[i] - '0'] == 1){
                fullnum --;
                words[array[i] - '0'] = 0;
            }
            else if(words[array[i] - '0'] == 2){
                    words[array[i] - '0'] = 0;
            }
        }
        if (leftnum == 0){
            printf("All customers tanned successfully.\n");
        }
        else{
            printf("%d customer(s) walked away.\n", leftnum);
        }
    }
    return 0;
}
