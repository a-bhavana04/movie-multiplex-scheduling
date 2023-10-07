//consolidation of modules for version 1
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <string.h>
#define ROWS 5
#define COLS 5
int total_screen,total_capacity;
//function  to check if current date from system is equal to release date
int release_date(int date,int month,int year)
{
    SYSTEMTIME stime;
    GetSystemTime(&stime);
    if (stime.wDay==date && stime.wMonth==month && stime.wYear==year)
        return 1;
}
//function to check if date entered is of valid format
int valid_date(int day, int mon, int year)
{
    int is_valid = 1, is_leap = 0;

    if (year >= 2022 && year <= 9999)
    {

        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
        {
            is_leap = 1;
        }
        if(mon >= 1 && mon <= 12)
        {
            if (mon == 2)
            {
                if (is_leap && day == 29)
                {
                    is_valid = 1;
                }
                else if(day > 28)
                {
                    is_valid = 0;
                }
            }
            else if (mon == 4 || mon == 6 || mon == 9 || mon == 11)
            {
                if (day > 30)
                {
                    is_valid = 0;
                }
            }

            else if(day > 31)
            {
                is_valid = 0;
            }
        }

        else
        {
            is_valid = 0;
        }

    }
    else
    {
        is_valid = 0;
    }

    return is_valid;

}
//to calculate the difference between two dates to check if the diff%7!=0 then demand_score is calculated
//otherwise if diff%7==0 then it is the next week so initial_demand is considered
int date_diff(int day1,int mon1,int year1,int day2,int mon2,int year2)
{

    int day_diff, mon_diff, year_diff;

    if(!valid_date(day1, mon1, year1))
    {
        printf("Date is invalid.\n");
        exit(0);
    }

    if(!valid_date(day2, mon2, year2))
    {
        printf("Date is invalid.\n");
        exit(0);
    }

    if(day2 < day1)
    {
        if (mon2 == 3)
        {
            if ((year2 % 4 == 0 && year2 % 100 != 0) || (year2 % 400 == 0))
            {
                day2 += 29;
            }

            else
            {
                day2 += 28;
            }
        }
        else if (mon2 == 5 || mon2 == 7 || mon2 == 10 || mon2 == 12)
        {
           day2 += 30;
        }

        else
        {
           day2 += 31;
        }

        mon2 = mon2 - 1;
    }

    if (mon2 < mon1)
    {
        mon2 += 12;
        year2 -= 1;
    }

    day_diff = day2 - day1;
    mon_diff = mon2 - mon1;
    year_diff = year2 - year1;
    return day_diff;
}
//to calculate the average of deman_arr
int avg_calc(int date,int month,int year,int arr[50],int length)
{
    int sum=0,k;
    SYSTEMTIME stime;
    GetSystemTime(&stime);
    if (date_diff(date,month,year,stime.wDay,stime.wMonth,stime.wYear)%7!=0 || date_diff(date,month,year,stime.wDay,stime.wMonth,stime.wYear)!=0)
    {
        for(k=0;k<length;k++)
            sum=sum+arr[k];
        return (sum/length);
    }
}
//to find the number of screens based on demand
int screen_calc(int dem)
{
    int screen_run;
    if (dem<=100 && dem>80)
        screen_run=0.7*total_screen;
    else if (dem<=80 && dem>60)
        screen_run=0.5*total_screen;
    else if(dem<=60 && dem>33)
        screen_run=0.2*total_screen;
    else
        screen_run=0;
    //total_screen-=screen_run;
    return screen_run;
}
//to calculate the initial_demand and demand_score
int demand_calc(int d,int m,int y,int screen_showed)
{
    int initial_demand,tickets_booked,demand_arr[50],i=0;
    SYSTEMTIME stime;
    GetSystemTime(&stime);
    if (release_date(d,m,y)==1)
    {
        initial_demand=100;
        i=0;
    }
    else
    {
        if (i==0)
        {
            int sample_arr[7]={70,70,70,70,70,70,70};
            initial_demand=avg_calc(d,m,y,sample_arr,7);
            i++;
        }
    }
    return initial_demand;
}
int screen_show(int initial_demand)
{
    int d,m,y,i=0,screen_showed,tickets_booked,demand_arr[50];
    if (release_date(d,m,y)==1)
    {
        screen_showed=screen_calc(initial_demand);
        i=0;
    }
    else
    {
        if (i==0)
        {
            int sample_arr[7]={70,70,70,70,70,70,70};
            screen_showed=screen_calc(initial_demand);
            i++;
        }
    }
    if (screen_showed==0)
        printf("Movie is removed from screening in the multiplex");
    else
    {
        printf("\n Enter number of tickets booked today : ");
        scanf("%d",&tickets_booked);
        demand_arr[i]=((tickets_booked/(screen_showed*total_capacity))*100);
        return screen_showed;
    }
}
int popularity(){
 int pop_score,pop_lang=0,mov_rate;
 int lang;
 printf("Enter the movie rating based on reliable source: ");
 scanf("%d",&mov_rate);


printf("\n Enter the language[1-Tamil;2-English;3-Other regional languages:]");
scanf("%d",&lang);
 if(lang==1){
  pop_lang=10;
}
 else if(lang==2){
  pop_lang=7;
}
 else{
  pop_lang=5;
}
pop_score=pop_lang + mov_rate;
return pop_score;
}
void slot_generation(int dow,float slot_arr[5][3])
{
    int i=1,j=0;
    if (dow==0 || dow==5 || dow==6)
    {
         for(i=1;i<total_screen+1;i++)
         {
             //printf("\n SLOTS FOR SCREEN %d",i);
             float arr[5][3]={{(9+(i-1)*0.05),(12+(i-1)*0.05),5},
                    {(12+(i-1)*0.05),(3+(i-1)*0.05),4},
                    {(3+(i-1)*0.5),(6+(i-1)*0.05),1},
                    {(6+(i-1)*0.05),(9+(i-1)*0.05),2},
                    {(9+(i-1)*0.05),(12+(i-1)*0.05),3}};
            for (j=0;j<5;j++)
            {
                slot_arr[j][0]=arr[j][0];
                slot_arr[j][1]=arr[j][1];
                slot_arr[j][2]=arr[j][2];
                //printf("\n %0.2f - %0.2f    \t\t   %0.0f ",arr[j][0],arr[j][1],arr[j][2]);
            }
         }
    }
    else if(dow<=4 && dow>=1)
    {
        for(i=1;i<total_screen+1;i++)
         {
            //printf("\n SLOTS FOR SCREEN %d",i);
            float  arr[5][3]={{(9+((i-1)*0.05)),(12+((i-1)*0.05)),5},
                {(12+(i-1)*0.05),(3+(i-1)*0.05),3},
                {(3+(i-1)*0.05),(6+(i-1)*0.05),2},
                {(6+(i-1)*0.05),(9+(i-1)*0.05),1},
                {(9+(i-1)*0.05),(12+(i-1)*0.05),4}};
            for (j=0;j<5;j++)
            {
                slot_arr[j][0]=arr[j][0];
                slot_arr[j][1]=arr[j][1];
                slot_arr[j][2]=arr[j][2];
                //printf("\n %0.2f - %0.2f    \t\t   %0.0f ",arr[j][0],arr[j][1],arr[j][2]);
            }
         }
    }
}
int runtime(int comb_score[50],int run_time[],int movie_no,int dow)
{
    int dayscore,final_score;
    if (dow==0 || dow==5 || dow==6)
        dayscore=100;
    else if(dow<=4 && dow>=1)
        dayscore=10;
    for(int i=0;i<movie_no;i++)
    {
        final_score=(comb_score[i]+dayscore)*0.5;
        if ((final_score>90) && (final_score<=100))
                run_time[i]=5;
        else if ((final_score>70) && (final_score<=90))
                run_time[i]=4;
        else if((final_score>50) && (final_score<=70))
                run_time[i]=3;
        else if ((final_score>30) && (final_score<=50))
                run_time[i]=2;
        else
                run_time[i]=1;
    }
}
void list2rank(int arr[50],int n,int newarr[50])
{
   for (int i = 0; i < n; i++)
    {
        int curRank = 0;

        for (int j = 0; j < i; j++)
        {
            if (arr[i] < arr[j])
            {
                curRank++;
            }
            else
            {
                newarr[j]++;
            }
        }

        newarr[i] = curRank;
    }
}
void bin_scheduler(int aggval[50][50],int binarr[50][50],int mapint[50],int comb_score[50],int movie_no,int dow)
{
    int temp[50],output[50],ind,val,run_time[50];
    for(int i=0;i<total_screen;i++)
    {
        ind=mapint[i];
        runtime(comb_score,run_time,movie_no,dow);
        val=run_time[ind];
        //printf("val %d",val);
        for(int j=0;j<ROWS;j++)
        {
            temp[j]=aggval[i][j];
        }
        /*printf("\n");
        for(int j=0;j<ROWS;j++)
        {
            printf("t %d",temp[j]);
        }*/
        list2rank(temp,5,output);
        printf("\n");
        /*for(int j=0;j<ROWS;j++)
        {
            printf("o %d",output[j]);
        }*/
        for (int j=0;j<5;j++)
        {
            binarr[i][j]=0;
        }
        for (int j=0;j<val;j++)
        {
            int indc=output[j];
            binarr[i][indc]=1;
        }
    }
    printf("\n");
    for (int i=0;i<total_screen;i++)
    {
        for(int j=0;j<5;j++)
        {
            printf("\t%d",binarr[i][j]);
        }
        printf("\n");
    }
}
void display(int binarr[50][50],float slot[5][3],int mapint[50], char name_arr[50][50])
{
    int temp;
    printf("\n");
    for(int i=0;i<total_screen;i++)
    {
        printf("\n SCREEN %d",i+1);
        temp=mapint[i];
        printf("\t%s",name_arr[temp]);
        printf("\n");
        float  arr[5][3]={{(9+((i)*0.05)),(12+((i)*0.05)),5},
                {(12+(i)*0.05),(3+(i)*0.05),3},
                {(3+(i)*0.05),(6+(i)*0.05),2},
                {(6+(i)*0.05),(9+(i)*0.05),1},
                {(9+(i)*0.05),(12+(i)*0.05),4}};
        for(int j=0;j<COLS;j++)
        {

            if (binarr[i][j]==1)
            {
                printf("\t %0.2f - %0.2f ",arr[j][0],arr[j][1]);
                printf("\n");
            }
            else
            {
                printf("\t - \t");
                printf("\n");
            }

        }
    }
}
void occupancy_calc(int combscore[50],float slot[5][3],int aggval[50][5],int mapint[50])
{
    int dow;
    SYSTEMTIME stime;
    GetSystemTime(&stime);
    dow=stime.wDayOfWeek;
    int moviefactor,j,slot_scores;
    //printf("%d",total_screen);
    for(int i=0;i<total_screen;i++)
    {
        j=mapint[i];
        //printf("\n %d",i);
        moviefactor=combscore[j];
        //printf("\n \t j%d",j);
        //printf("\n mf %d",moviefactor);
        for(int k=0;k<5;k++)
        {
            //printf("\n hi %d\n",k);
            slot_scores=(6-((slot[k][3])))*10;
            if (1<=dow<=4)
                slot_scores+=1;
            else if(dow==5 || dow==6 || dow==0)
                slot_scores+=10;
            aggval[i][k]=(moviefactor+slot_scores)*0.625;
            //printf("c2 %d",i);
            //printf("\t o%d",aggval[i][k]);
        }
    }
    printf("\n");
    for(int i=0;i<total_screen;i++)
    {
        for(int j=0;j<5;j++)
        {
            printf("\t%d",aggval[i][j]);
        }
        printf("\n");
    }
}
void mapping(int total_screen,int movienum,char movie_lst[50][50],int movie_screen[50],int mapint[50])
{
    int i=0,j=0,k;
    int count=movie_screen[j];
    while(j<movienum)
    {
        //for(i=0;i<movie_screen[j];i++)
        while(i<count)
        {
            //strcpy(maparr[i],movie_lst[j]);
            //printf("\n%d",j);
            mapint[i]=j;
            i++;
            //printf("\t m%d",mapint[i]);
        }
        j++;
        count=count+movie_screen[j];
    }

    /*for(k=0;k<total_screen;k++)
        printf("m%d",mapint[k]);*/
}
void main()
{
    int date_rel,month_rel,year_rel,demand,map_int[50],aggval[50][5],dow,schedule_arr[50][50];
    char movie_arr[50][50],map_arr[50][50];
    int i,j,movie_to_screen[50],movie_no,screens,comb_arr[50];
    printf("Enter number of screens in the multiplex : ");
    scanf("%d",&total_screen);
    printf("\n Enter capacity of each screen : ");
    scanf("%d",&total_capacity);
    printf("\n Enter number of movies : ");
    scanf("%d",&movie_no);
    for(i=0;i<movie_no;i++)
    {
            printf("\n Enter movie name : ");
            scanf("%s",movie_arr[i]);
            printf("Enter release date (dd/mm/yy): ");
            scanf("%d/%d/%d", &date_rel,&month_rel,&year_rel);
            int popularity_score;
            popularity_score=popularity();
            printf("\n The popularity score calculated based on movie rating and other constrains is:%d",popularity_score);
            demand=demand_calc(date_rel,month_rel,year_rel,screens);
            movie_to_screen[i]=screen_show(demand);
            //printf("\n%d  %d",demand,popularity_score);
            comb_arr[i]=(demand+popularity_score)*0.83;

    }
    for(int i=0;i<movie_no;i++)
    {
        printf("combined scores %d",comb_arr[i]);
    }

    for (j=0;j<movie_no;j++)
    {
        printf("\n name of movie : %s   number of screens allotted : %d",movie_arr[j],movie_to_screen[j]);
    }
    mapping(total_screen,movie_no,movie_arr,movie_to_screen,map_int);
    float slot_timing[5][3];
    //SYSTEMTIME stime;
    //GetSystemTime(&stime);
    //dow=stime.wDayOfWeek;
    for(int dow=0;dow<7;dow++)
    {
        slot_generation(dow,slot_timing);
        occupancy_calc(comb_arr,slot_timing,aggval,map_int);
        bin_scheduler(aggval,schedule_arr,map_int,comb_arr,movie_no,dow);
        display(schedule_arr,slot_timing,map_int,movie_arr);
    }
}
