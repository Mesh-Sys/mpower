#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_CONFIG_VALUE_SIZE 8
#define MAX_CONFIG_LINE_SIZE 24

int mode;

char CPU_TURBO_BOOST_BATT[MAX_CONFIG_VALUE_SIZE];
char CPU_MAX_BATT[MAX_CONFIG_VALUE_SIZE];
char CPU_MIN_BATT[MAX_CONFIG_VALUE_SIZE];
char CPU_MAX_AC[MAX_CONFIG_VALUE_SIZE];
char CPU_MIN_AC[MAX_CONFIG_VALUE_SIZE];
char CPU_MAX_PERF_BATT[MAX_CONFIG_VALUE_SIZE];
char CPU_MIN_PERF_BATT[MAX_CONFIG_VALUE_SIZE];
char CPU_MAX_PERF_AC[MAX_CONFIG_VALUE_SIZE];
char CPU_MIN_PERF_AC[MAX_CONFIG_VALUE_SIZE];
char GPU_MAX_BATT[MAX_CONFIG_VALUE_SIZE];
char GPU_MIN_BATT[MAX_CONFIG_VALUE_SIZE];
char GPU_BOOST_BATT[MAX_CONFIG_VALUE_SIZE];
 
void find_str(char const *str, char const *substr,int *index)
{
    char *pos = strstr(str, substr);
    int loc = pos - str;
    
    char *val = calloc(MAX_CONFIG_VALUE_SIZE, sizeof(char));
    char *sname = calloc(MAX_CONFIG_LINE_SIZE, sizeof(char));

    if(pos){
        for(int j = 0;j < MAX_CONFIG_LINE_SIZE;j++){
            if(j >= loc){
                if(str[j] == '\0'){
                    break;
                }else if(j > loc){
                    strncat(val,&str[j],1);
                }
            }else{
                strncat(sname,&str[j],1);
            }
        }

        if(strcmp(sname, "CPU_TURBO_BOOST_BATT") == 0){
            strcpy(CPU_TURBO_BOOST_BATT, val);
       }else if(strcmp(sname, "CPU_MAX_BATT") == 0){
            strcpy(CPU_MAX_BATT, val);
       }else if(strcmp(sname, "CPU_MIN_BATT") == 0){
            strcpy(CPU_MIN_BATT, val);
       }else if(strcmp(sname, "CPU_MAX_AC") == 0){
            strcpy(CPU_MAX_AC, val);
       }else if(strcmp(sname, "CPU_MIN_AC") == 0){
            strcpy(CPU_MIN_AC, val);
       }else if(strcmp(sname, "CPU_MAX_PERF_BATT") == 0){
            strcpy(CPU_MAX_PERF_BATT, val);
       }else if(strcmp(sname, "CPU_MIN_PERF_BATT") == 0){
            strcpy(CPU_MIN_PERF_BATT, val);
       }else if(strcmp(sname, "CPU_MAX_PERF_AC") == 0){
            strcpy(CPU_MAX_PERF_AC, val);
       }else if(strcmp(sname, "CPU_MIN_PERF_AC") == 0){
            strcpy(CPU_MIN_PERF_AC, val);
       }else if(strcmp(sname, "GPU_MAX_BATT") == 0){
            strcpy(GPU_MAX_BATT, val);
       }else if(strcmp(sname, "GPU_MIN_BATT") == 0){
            strcpy(GPU_MIN_BATT, val);
       }else if(strcmp(sname, "GPU_BOOST_BATT") == 0){
            strcpy(GPU_BOOST_BATT, val);
       }else{
            printf("Error occured while macthing config...\n");
       }
    }else{
        printf("Error \"=\" not matched\n");
    }

    free(val);
    val = NULL;
    
    free(sname);
    sname = NULL;

}
void OnACstatusChanged(int status){
    if(status == 1){
        fprintf(stderr,"[%d] ACTIVATED IN AC\n",status);
    }else{

        fprintf(stderr,"[%d] ACTIVATED IN BATT\n",status);
    }
    mode = 0;
}
int main(void)
{

    char str[12][24] = {"CPU_TURBO_BOOST_BATT=0",
                        "CPU_MAX_BATT=2000000",
                        "CPU_MIN_BATT=800000",
                        "CPU_MAX_AC=3900000",
                        "CPU_MIN_AC=800000",
                        "CPU_MAX_PERF_BATT=50",
                        "CPU_MIN_PERF_BATT=20",
                        "CPU_MAX_PERF_AC=100",
                        "CPU_MIN_PERF_AC=20",
                        "GPU_MAX_BATT=800",
                        "GPU_MIN_BATT=350",
                        "GPU_BOOST_BATT=800"};
    
    int len = sizeof(str)/sizeof(str[0]);
    for(int i = 0;i < len;i++){
        find_str(str[i],"=",&i);
    }
    
    printf("CPU_TURBO_BOOST_BATT = value: [%s]\n",CPU_TURBO_BOOST_BATT);
    printf("CPU_MAX_BATT = value: [%s]\n",CPU_MAX_BATT);
    printf("CPU_MIN_BATT = value: [%s]\n",CPU_MIN_BATT);
    printf("CPU_MAX_AC = value: [%s]\n",CPU_MAX_AC);
    printf("CPU_MIN_AC = value: [%s]\n",CPU_MIN_AC);
    printf("CPU_MAX_PERF_BATT = value: [%s]\n",CPU_MAX_PERF_BATT);
    printf("CPU_MIN_PERF_BATT = value: [%s]\n",CPU_MIN_PERF_BATT);
    printf("CPU_MAX_PERF_AC = value: [%s]\n",CPU_MAX_PERF_AC);
    printf("CPU_MIN_PERF_AC = value: [%s]\n",CPU_MIN_PERF_AC);
    printf("GPU_MAX_BATT = value: [%s]\n",GPU_MAX_BATT);
    printf("GPU_MIN_BATT = value: [%s]\n",GPU_MIN_BATT);
    printf("GPU_BOOST_BATT = value: [%s]\n",GPU_BOOST_BATT);

    int NO_OF_THREADS = 8;
    for(int i = 0; i < NO_OF_THREADS; i++){


        char cbdir[64] = "/sys/devices/system/cpu/";
        char tcn[8] = "cpu";
        char gdir[32] = "/cpufreq/";
        char ec[64] = "ls ";

        char cval[4];
        sprintf(cval,"%d",i);

        printf("{%s}:%d\n", cval,i);

        strcat(tcn,cval);
        strcat(cbdir,tcn);
        strcat(cbdir,gdir);

        strcat(ec,cbdir);
        printf("[%s]\n", ec);
        system(ec);
    }

    //popen
    #include <stdio.h>

    printf("\n\n\n\n\n");

    FILE *fp;
    char path[4];

    
    int status;
    
    while(1){
    
        fp = popen("cat /sys/class/power_supply/AC/online", "r");
        if (fp == NULL){
            /* Handle error */;
        }
        
        
        while (fgets(path, 4, fp) != NULL){
            //fprintf(stderr,"[%s]", path);
            if(strcmp(path,"1\n") == 0){
                if (status == 0){
                    mode = 1;
                }
                fprintf(stderr,"Charging\n");
                status = 1;

            }else if(strcmp(path,"0\n") == 0){
                if(status == 1){
                    mode = 1;
                }
                fprintf(stderr,"Discharging\n");
                status = 0;
            }
        }

        if(mode == 1){
            OnACstatusChanged(status);
        }

        sleep(3);
    }
    
    fprintf(stderr, "finished with cntrl + c\n");
    pclose(fp);
    return 0;
}