#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <string.h> 
#include "main.h" 


void saveData(Person **s, int count,int selectnumber){
    FILE *fp;
    if(selectnumber == 1) fp = fopen("poengbong.txt", "wt");
    else fp = fopen("hidink.txt","rt");
    for(int i=0; i<count; i++){
        if(s[i]->age==-1) continue;
    fprintf(fp, "%s %d %0.1f %0.1f %s \n",s[i]->name,s[i]->age,s[i]->length,s[i]->weight,s[i]->detail);
    }
    fclose(fp);
    printf("=> 저장됨! ");
}

int loadData(Person **s, int selectnumber){
    int count =0;
    FILE *fp;
    if(selectnumber == 1) fp=fopen("poengbong.txt", "rt");
    else fp = fopen("hidink.txt","rt");
    if(fp==NULL){
        printf("=> 파일 없음");
    }
    else{
        while(!feof(fp)){
        s[count]=(Person *)malloc(sizeof(Person));
        fscanf(fp, "%s", s[count]->name);
        if(feof(fp)) break;
        fscanf(fp, "%d", &s[count]->age);
        fscanf(fp, "%lf", &s[count]->length);
        fscanf(fp, "%lf", &s[count]->weight);
        fscanf(fp, "%[^\n]s", s[count]->detail);
        count++;
    }
    fclose(fp);
    printf("=> 로딩성공!\n");
    }
    
    return count;
}
int reserveTime(Team *t[]){ //이것은 적절한 시간으로 빌렸는지 확인하는 함수입니다.
    int startTime;
    int endTime;
    int count=0;
    while(1){
        printf("빌리고 싶은 시작 시간를 입력하세요(오후 5시는 17시로 입력!) : ");
        scanf("%d",&startTime);
        printf("\n끝나는 시간을 입력하세요(오후 6시는 18시로 입력!) : ");
        scanf("%d",&endTime);

        if(t[startTime]->starttime = startTime) printf("\n그 시간엔 이미 사용자가 있습니다.\n");
        else if(endTime - startTime  == 1) {
            t[startTime]->starttime = startTime;//t[start]에 넣은 것은 예약한 사람을 확인하는데 시간별로 확인하기 위해서 이렇게 사용했습니다.
            break;
        }
        else printf("\n빌리는 시간이 적절하지 않습니다. 다시 입력해주세요! : ");
    }
    return startTime;    
}

void reserveteamName(Team *t[],int time){ //team의 이름과 리더를 찾는 함수이다.
    char teamName[100];
    char teamLeader[100];

    printf("\n빌리는 팀 이름을 입력해주세요! : ");
    scanf("%[^\n]s",teamName);
    printf("\n대표자의 이름을 입력해주세요! : ");
    getchar();
    scanf("%[^\n]s",teamLeader);

    for(int i=0; i<24; i++){
        if(!strcmp(teamName,t[i]->teamname)) {
            printf("\n이미 빌린 팀입니다.\n");
            t[time]->starttime = 0;
            t[time]->endtime = 0;
            printf("자동적으로 예약시스템이 취소 후 종료됩니다.\n");
            return;
        }
        if(!strcmp(teamLeader,t[i]->name)) {
            printf("\n이미 빌린 사람입니다.\n");
            t[time]->starttime = 0;
            t[time]->endtime = 0;
            printf("자동적으로 예약시스템이 취소 후 종료됩니다.\n");
            return;
        }

    }
    strcpy(t[time]->teamname,teamName);
    strcpy(t[time]->name,teamLeader);    
}

void reserveSystem(Team **t){//위에 두 함수를 호출해서 사람을 받는다.
    int number = reserveTime(t);
    reserveteamName(t,number);
}

void teamfillmethod(Team **t){ //team의 사이즈를 먼저 늘리기 이유 : 예약을 조회할 때 nullptr이라면 그 시간은 비어있다고 생각
    for(int i=0; i<24; i++){
        t[i] = (Team*)malloc(sizeof(Team));
    }
}

int createProduct(Person *s){
    printf("이름은 ? ");
    scanf("%s",s->name);
    printf("현재 나이 ? ");
    scanf("%d",&s->age);
    printf("현재 신장은 ? ");
    scanf("%lf",&s->length);
    printf("몸무게는 ? ");
    scanf("%lf",&s->weight);
    printf("특이사항은 ? ");
    getchar();
    scanf("%[^\n]s", s->detail);
    printf("=> 추가됨! \n");
    return 0;
};

void readProduct(Person *s){
    printf("  이름: %4s\n  나이: %d\n  신장: %0.1f\n  몸무게: %0.1f\n  특이사항: %s \n",s->name,s->age,s->length,s->weight,s->detail);
};

void listproduct(Person *s[], int count){
    printf("^o^ 두근두근 당신의 이상형을 찾아보세요 ^o^ \n");
    printf("===========================\n");
    for(int i=0; i<count; i++){
        if(s[i]->age ==-1) continue;
        printf("%2d번 이상형^o^\n",i+1);
        readProduct(s[i]);
    }
    printf("\n");
};

int updateProduct(Person *s){
    printf("이름은 ? ");
    scanf("%s",s->name);
    printf("현재 나이 ? ");
    scanf("%d",&s->age);
    printf("현재 신장은 ? ");
    scanf("%lf",&s->length);
    printf("몸무게는 ? ");
    scanf("%lf",&s->weight);
    printf("특이사항은? ");
    getchar();
    scanf("%[^\n]s", s->detail);
    printf("=> 수정되었습니다.! \n");
    return 0;
};

int selectdatano (Person *s[], int count){
    int no;
    listproduct(s, count);
    printf("번호는? (취소 :0)?");
    scanf("%d", &no);
    return no;
}

int deleteproduct(Person *s){
    s->age=-1;
    printf("=> 삭제됨! \n");
    return 0;
};

void searchName(Person **s, int count){
    int scnt =0;
    char search[20];
    printf("검색할 이름은? ");
    scanf("%s", search);
    printf("^o^ 두근두근 당신의 이상형을 찾아보세요 ^o^ \n");
    printf("================================\n");
    for(int i=0;i<count;i++){
        if(s[i]->age==-1) continue;
        if(strstr(s[i]->name,search)){
            printf("%2d ", i+1);
            readProduct(s[i]);
            scnt++;
        }
    }
    if(scnt == 0) printf("=> 검색된데이터없음!");
    printf("\n");
};
int idcheck(){
    int input;

    while(1){
        printf("\n당신의 학번을 입력해주세요: ");
        scanf("%d",&input);
        if(input >= 11111111 && input <= 24000000){
            break;
        }
        else{
            printf("학번이 맞지 않습니다. 다시 입력하시길 바랍니다.\n ");
    }
}
    return input;
}


int selectMenu(){
    int menu;
    printf("\n*** FOOTBALL CHECK SYSTEM ***\n");
    printf("1. 경기장 조회\n");
    printf("2. 경기장 예약\n");
    printf("3. 예약 수정\n");
    printf("4. 예약 삭제\n");
    printf("5. 파일저장\n");
    printf("6. 이름검색\n");
    printf("7. 현재 경기장 예약 현황 조회");
    printf("0. 종료\n\n");
    printf("=> 원하는 메뉴는? ");
    scanf("%d", &menu);
    return menu;
};
