#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct temp{
    char name[20];
    int age;
    double weight;
    double height;
    struct temp *next;
    struct temp *previous;
} person;

person* delete(person* h,char *s){
    for (person *offset=h ;offset!= NULL; offset = offset->next){
        if ( strcmp(offset->name,s) == 0 ){
            if (offset == h){
                offset->next->previous = NULL;
                h=offset->next;
                return h;
            }else{
                offset->previous->next = offset->next;
                offset->next = offset->previous;
                return h;
            }
        }
    }
    return h;
}

int main(int argc, char *argv[]){

    FILE *fp;
    int line=0;
    int c;
    char s[100];
           
    if (argc != 2) {
        printf("コマンドのあとに一つファイルを指定してください\n");
    }

    if ( ( fp=fopen(argv[1],"r") ) == NULL){
        printf("ファイルの読み込みに失敗しました。\n");
        return 1;
    }

    while((c = getc(fp)) != EOF) {
        if(c == '\n') {
            line++;
        }
    }
    fseek(fp,0,SEEK_SET);

    //格納
    person *list;
    list = (person*)malloc(sizeof(person));

    fscanf(fp,"%[^,],%d,%lf,%lf\n",list->name,&(list->age),&(list->weight),&(list->height));
    list->previous = NULL;
    person *head = list;
    for (int i=1; i<line; i++) {
        list->next = (person*)malloc(sizeof(person));
        fscanf(fp,"%[^,],%d,%lf,%lf\n",list->next->name,&(list->next->age),&(list->next->weight),&(list->next->height));
        list->next->previous = list;
        if (i<line-1){
            list = list->next;
        }else{
            list->next->next = NULL;
        }

    }

    //削除
    printf("削除を開始します。\n削除を終了するには\"finish\"と入力してください。\n");
    while (1){
        scanf("%[^\n]%*c",s);
        if (strcmp(s,"finish") == 0){
            break;
        }else{
            head=delete(head,s);
        }
    }

    //表示
    for (person *offset=head; offset!=NULL; offset = offset->next){
        printf("(name,age,weight,height) = (%s,%d,%f,%f)\n",offset->name,offset->age,offset->weight,offset->height);
    }

    
    return 0;
}
