#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

#define MAX_CONFIG_SIZE 128
#define CONFIG_MEMSIZE 128

int mode_event;

int MPOWER_ENABLED;
int NO_OF_THREADS;
int INTEL_PSTATE;

char CPU_EPP_BATT[MAX_CONFIG_SIZE];
char CPU_EPP_AC[MAX_CONFIG_SIZE];

char CPU_SCALING_GOVERNOR_BATT[MAX_CONFIG_SIZE];
char CPU_SCALING_GOVERNOR_AC[MAX_CONFIG_SIZE];

char CPU_TURBO_BOOST_BATT[MAX_CONFIG_SIZE];
char CPU_TURBO_BOOST_AC[MAX_CONFIG_SIZE];

char CPU_MAX_BATT[MAX_CONFIG_SIZE];
char CPU_MIN_BATT[MAX_CONFIG_SIZE];

char CPU_MAX_AC[MAX_CONFIG_SIZE];
char CPU_MIN_AC[MAX_CONFIG_SIZE];

char CPU_MAX_PERF_BATT[MAX_CONFIG_SIZE];
char CPU_MIN_PERF_BATT[MAX_CONFIG_SIZE];

char CPU_MAX_PERF_AC[MAX_CONFIG_SIZE];
char CPU_MIN_PERF_AC[MAX_CONFIG_SIZE];

char GPU_MAX_BATT[MAX_CONFIG_SIZE];
char GPU_MIN_BATT[MAX_CONFIG_SIZE];
char GPU_BOOST_BATT[MAX_CONFIG_SIZE];

char GPU_MAX_AC[MAX_CONFIG_SIZE];
char GPU_MIN_AC[MAX_CONFIG_SIZE];
char GPU_BOOST_AC[MAX_CONFIG_SIZE];

void set_cpu_freq(char const *CPU_MAX, char const *CPU_MIN){
	for(int i = 0; i < NO_OF_THREADS; i++){
		char PREFIX_CPU_DIR_MAX[72] = " > /sys/devices/system/cpu/";
		char PREFIX_CPU_DIR_MIN[72] = " > /sys/devices/system/cpu/";
		char SUFIX_CPU_DIR_MAX[32] = "/cpufreq/scaling_max_freq";
		char SUFIX_CPU_DIR_MIN[32] = "/cpufreq/scaling_min_freq";

		char CMD_MAX[256] = "echo ";
		char CMD_MIN[128] = " && echo ";


		char TCPU[32] = "cpu";
		char TMP_CPU_NUM[12];

		sprintf(TMP_CPU_NUM,"%d",i);

		strcat(TCPU,TMP_CPU_NUM);

		strcat(PREFIX_CPU_DIR_MAX,TCPU);
		strcat(PREFIX_CPU_DIR_MIN,TCPU);

		strcat(PREFIX_CPU_DIR_MAX,SUFIX_CPU_DIR_MAX);
		strcat(PREFIX_CPU_DIR_MIN,SUFIX_CPU_DIR_MIN);

		strcat(CMD_MAX,CPU_MAX);
		strcat(CMD_MIN,CPU_MIN);

		strcat(CMD_MAX,PREFIX_CPU_DIR_MAX);
		strcat(CMD_MIN,PREFIX_CPU_DIR_MIN);

		strcat(CMD_MAX,CMD_MIN);

		system(CMD_MAX);
	}
}
void set_cpu_pstate_perf(char const *CPU_PMAX, char const *CPU_PMIN){
	char CPU_DIR_MAX[72] = " > /sys/devices/system/cpu/intel_pstate/max_perf_pct";
	char CPU_DIR_MIN[72] = " > /sys/devices/system/cpu/intel_pstate/min_perf_pct";

	char CMD_MAX[256] = "echo ";
	char CMD_MIN[128] = " && echo ";

	strcat(CMD_MAX,CPU_PMAX);
	strcat(CMD_MIN,CPU_PMIN);

	strcat(CMD_MAX,CPU_DIR_MAX);
	strcat(CMD_MIN,CPU_DIR_MIN);

	strcat(CMD_MAX,CMD_MIN);

	system(CMD_MAX);
}
void set_cpu_scaling_governor(char const *SCALING_GOVERNOR){
	for(int i = 0; i < NO_OF_THREADS; i++){
		char PREFIX_CPU_DIR[128] = " > /sys/devices/system/cpu/";
		char SUFIX_CPU_DIR[32] = "/cpufreq/scaling_governor";

		char CMD[128] = "echo ";

		char TCPU[32] = "cpu";
		char TMP_CPU_NUM[12];

		sprintf(TMP_CPU_NUM,"%d",i);

		strcat(TCPU,TMP_CPU_NUM);

		strcat(PREFIX_CPU_DIR,TCPU);

		strcat(PREFIX_CPU_DIR,SUFIX_CPU_DIR);

		strcat(CMD,SCALING_GOVERNOR);

		strcat(CMD,PREFIX_CPU_DIR);

		system(CMD);
	}
}
void set_cpu_epp(char const *EPP_PREF){
	for(int i = 0; i < NO_OF_THREADS; i++){
		char PREFIX_CPU_DIR[128] = " > /sys/devices/system/cpu/";
		char SUFIX_CPU_DIR[42] = "/cpufreq/energy_performance_preference";

		char CMD[128] = "echo ";

		char TCPU[32] = "cpu";
		char TMP_CPU_NUM[12];

		sprintf(TMP_CPU_NUM,"%d",i);

		strcat(TCPU,TMP_CPU_NUM);

		strcat(PREFIX_CPU_DIR,TCPU);

		strcat(PREFIX_CPU_DIR,SUFIX_CPU_DIR);

		strcat(CMD,EPP_PREF);

		strcat(CMD,PREFIX_CPU_DIR);

		system(CMD);
	}
}
void set_cpu_turbo_boost_state(char const *TURBO_STATE){
		char TURBO_DIR[64] = " > /sys/devices/system/cpu/intel_pstate/no_turbo";

		char CMD[128] = "echo ";

		strcat(CMD,TURBO_STATE);

		strcat(CMD,TURBO_DIR);

		system(CMD);
}
void set_gpu_freq(char const *GPU_MAX, char const *GPU_MIN, char const *GPU_BOOST){
	char GPU_DIR_MAX[72] = " > /sys/class/drm/card1/gt_max_freq_mhz";
	char GPU_DIR_MIN[72] = " > /sys/class/drm/card1/gt_min_freq_mhz";
	char GPU_DIR_BOOST[72] = " > /sys/class/drm/card1/gt_boost_freq_mhz";

	char CMD_MAX[512] = "echo ";
	char CMD_MIN[256] = " && echo ";
	char CMD_BOOST[128] = " && echo ";


	strcat(CMD_MAX,GPU_MAX);
	strcat(CMD_MIN,GPU_MIN);
	strcat(CMD_BOOST,GPU_BOOST);

	strcat(CMD_MAX,GPU_DIR_MAX);
	strcat(CMD_MIN,GPU_DIR_MIN);
	strcat(CMD_BOOST,GPU_DIR_BOOST);

	strcat(CMD_MIN,CMD_BOOST);
	strcat(CMD_MAX,CMD_MIN);

	system(CMD_MAX);
}
void get_config(char const *str, char const *substr){

	char *pos = strstr(str,substr);
	int loc = pos - str;

	char *val = calloc(MAX_CONFIG_SIZE,sizeof(char));
	char *sname = calloc(MAX_CONFIG_SIZE,sizeof(char));

	if(pos){
		for(int i = 0;i < MAX_CONFIG_SIZE;i++){
			if(i >= loc){
				if((str[i] == '\0') || (str[i] == '\n')){
					break;
				}else if(i > loc){
					strncat(val,&str[i],1);
				}
			}else{
				strncat(sname,&str[i],1);
			}
		}

		if(strcmp(sname, "NO_OF_THREADS") == 0){
			NO_OF_THREADS = atoi(val);
		}else if(strcmp(sname, "INTEL_PSTATE") == 0){
			INTEL_PSTATE = atoi(val);
		}else if(strcmp(sname, "MPOWER_ENABLED") == 0){
			MPOWER_ENABLED = atoi(val);
		}else if(strcmp(sname, "CPU_EPP_BATT") == 0){
			strcpy(CPU_EPP_BATT,val);
		}else if(strcmp(sname, "CPU_EPP_AC") == 0){
			strcpy(CPU_EPP_AC,val);
		}else if(strcmp(sname, "CPU_SCALING_GOVERNOR_BATT") == 0){
			strcpy(CPU_SCALING_GOVERNOR_BATT,val);
		}else if(strcmp(sname, "CPU_SCALING_GOVERNOR_AC") == 0){
			strcpy(CPU_SCALING_GOVERNOR_AC,val);
		}else if(strcmp(sname, "CPU_TURBO_BOOST_BATT") == 0){
			strcpy(CPU_TURBO_BOOST_BATT,val);
		}else if(strcmp(sname, "CPU_TURBO_BOOST_AC") == 0){
			strcpy(CPU_TURBO_BOOST_AC,val);
		}else if(strcmp(sname, "CPU_MAX_BATT") == 0){
			strcpy(CPU_MAX_BATT,val);
		}else if(strcmp(sname, "CPU_MIN_BATT") == 0){
			strcpy(CPU_MIN_BATT,val);
		}else if(strcmp(sname, "CPU_MAX_AC") == 0){
			strcpy(CPU_MAX_AC,val);
		}else if(strcmp(sname, "CPU_MIN_AC") == 0){
			strcpy(CPU_MIN_AC,val);
		}else if(strcmp(sname, "CPU_MAX_PERF_BATT") == 0){
			strcpy(CPU_MAX_PERF_BATT,val);
		}else if(strcmp(sname, "CPU_MIN_PERF_BATT") == 0){
			strcpy(CPU_MIN_PERF_BATT,val);
		}else if(strcmp(sname, "CPU_MAX_PERF_AC") == 0){
			strcpy(CPU_MAX_PERF_AC,val);
		}else if(strcmp(sname, "CPU_MIN_PERF_AC") == 0){
			strcpy(CPU_MIN_PERF_AC,val);
		}else if(strcmp(sname, "GPU_MAX_BATT") == 0){
			strcpy(GPU_MAX_BATT,val);
		}else if(strcmp(sname, "GPU_MIN_BATT") == 0){
			strcpy(GPU_MIN_BATT,val);
		}else if(strcmp(sname, "GPU_BOOST_BATT") == 0){
			strcpy(GPU_BOOST_BATT,val);
		}else if(strcmp(sname, "GPU_MAX_AC") == 0){
			strcpy(GPU_MAX_AC,val);
		}else if(strcmp(sname, "GPU_MIN_AC") == 0){
			strcpy(GPU_MIN_AC,val);
		}else if(strcmp(sname, "GPU_BOOST_AC") == 0){
			strcpy(GPU_BOOST_AC,val);
		}else{
			fprintf(stderr, "Error occured when reading config values");
		}
	}

	free(val);
	free(sname);
	val = NULL;
	sname = NULL;
}
int get_charge_status(){
	FILE *fp;
    char path[4];
    int chstatus = 0;
    
    fp = popen("cat /sys/class/power_supply/AC/online", "r");        
     while (fgets(path, 4, fp) != NULL){
         if(strcmp(path,"1\n") == 0){
            chstatus = 1;
         }else if(strcmp(path,"0\n") == 0){
            chstatus = 0;
         }
     }
    pclose(fp);
    return chstatus;
}
void apply_config(int *status){

	if(*status == 1){	//AC CONFIG
		//fprintf(stderr,"APPLY AC CONFIG\n\n");

		//check for intel pstate and set cpu based on that
		if(INTEL_PSTATE == 1){
			set_cpu_pstate_perf(CPU_MAX_PERF_AC,CPU_MIN_PERF_AC);
		}else{
			set_cpu_freq(CPU_MAX_AC,CPU_MIN_AC);
		}
		set_cpu_epp(CPU_EPP_AC);
		set_cpu_scaling_governor(CPU_SCALING_GOVERNOR_AC);
		set_cpu_turbo_boost_state(CPU_TURBO_BOOST_AC);
		set_gpu_freq(GPU_MAX_AC,GPU_MIN_AC,GPU_BOOST_AC);
	}else if(*status == 0){		//BATTERY CONFIG
		//fprintf(stderr,"APPLY BATTERY CONFIG\n\n");
		
		//check for intel pstate and set cpu based on that
		if(INTEL_PSTATE == 1){
			set_cpu_pstate_perf(CPU_MAX_PERF_BATT,CPU_MIN_PERF_BATT);
		}else{
			set_cpu_freq(CPU_MAX_BATT,CPU_MIN_BATT);
		}
		set_cpu_epp(CPU_EPP_BATT);
		set_cpu_scaling_governor(CPU_SCALING_GOVERNOR_BATT);
		set_cpu_turbo_boost_state(CPU_TURBO_BOOST_BATT);
		set_gpu_freq(GPU_MAX_BATT,GPU_MIN_BATT,GPU_BOOST_BATT);
	}

	mode_event = 0;
}
int main(){
	
	//read config file
	FILE *CONFIG_FILE;
	CONFIG_FILE = fopen("/etc/mpower.conf","r");

	char *readc = calloc(CONFIG_MEMSIZE * CONFIG_MEMSIZE, sizeof(char));

	if(CONFIG_FILE != NULL){
		int inc = 0;
		while(fgets(&readc[inc],CONFIG_MEMSIZE,CONFIG_FILE)){
			get_config(&readc[inc],"=");
			inc++;
		}
	}else{
		fprintf(stderr, "Error occured when reading the config file");
	}

	free(readc);
	readc = NULL;
	fclose(CONFIG_FILE);

	if(MPOWER_ENABLED == 1){
		bool mpswitch = true;

		//initialize
		int init_config = get_charge_status();
		apply_config(&init_config);

		//charge status
		int status = 2;
		int pstatus = 2;

		//execute
		while(mpswitch){
			//fprintf(stderr,"active\n");
			status = get_charge_status();

			if((pstatus == 1) && (status == 0)){
				mode_event = 1;
			}else if((pstatus == 0) && (status == 1)){
				mode_event = 1;
			}

			if(mode_event == 1){
				apply_config(&status);
			}

			sleep(5);
			pstatus = status;
		}
	}

	return 0;
}