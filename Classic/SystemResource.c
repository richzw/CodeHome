//http://stackoverflow.com/questions/63166/how-to-determine-cpu-and-memory-consumption-from-inside-a-process?rq=1
// CPU usage by current process
  #include "windows.h"
    static ULARGE_INTEGER lastCPU, lastSysCPU, lastUserCPU;
    static int numProcessors;
    static HANDLE self;
    
    void init(){
        SYSTEM_INFO sysInfo;
        FILETIME ftime, fsys, fuser;
    
        GetSystemInfo(&sysInfo);
        numProcessors = sysInfo.dwNumberOfProcessors;
    
        GetSystemTimeAsFileTime(&ftime);
        memcpy(&lastCPU, &ftime, sizeof(FILETIME));
    
        self = GetCurrentProcess();
        GetProcessTimes(self, &ftime, &ftime, &fsys, &fuser);
        memcpy(&lastSysCPU, &fsys, sizeof(FILETIME));
        memcpy(&lastUserCPU, &fuser, sizeof(FILETIME));
    }
    
    double getCurrentValue(){
        FILETIME ftime, fsys, fuser;
        ULARGE_INTEGER now, sys, user;
        double percent;
    
        GetSystemTimeAsFileTime(&ftime);
        memcpy(&now, &ftime, sizeof(FILETIME));
    
        GetProcessTimes(self, &ftime, &ftime, &fsys, &fuser);
        memcpy(&sys, &fsys, sizeof(FILETIME));
        memcpy(&user, &fuser, sizeof(FILETIME));
        percent = (sys.QuadPart - lastSysCPU.QuadPart) +
            (user.QuadPart - lastUserCPU.QuadPart);
        percent /= (now.QuadPart - lastCPU.QuadPart);
        percent /= numProcessors;
        lastCPU = now;
        lastUserCPU = user;
        lastSysCPU = sys;
    
        return percent * 100;
    }
	
//Total Virtual Memory:
    #include "windows.h"
    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&memInfo);
    DWORDLONG totalVirtualMem = memInfo.ullTotalPageFile;
	
//Virtual Memory currently used by current process:
    #include "windows.h"
    #include "psapi.h"
    PROCESS_MEMORY_COUNTERS_EX pmc;
    GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
    SIZE_T virtualMemUsedByMe = pmc.PrivateUsage;\
	
//Physical Memory currently used by current process:
    SIZE_T physMemUsedByMe = pmc.WorkingSetSize;
	
//Linux
//Virtual Memory currently used by current process:
    #include "stdlib.h"
    #include "stdio.h"
    #include "string.h"
   
    int parseLine(char* line){
        int i = strlen(line);
        while (*line < '0' || *line > '9') line++;
        line[i-3] = '\0';
        i = atoi(line);
        return i;
    }  

    int getValue(){ //Note: this value is in KB!
        FILE* file = fopen("/proc/self/status", "r");
        int result = -1;
        char line[128];
    
        while (fgets(line, 128, file) != NULL){
            if (strncmp(line, "VmSize:", 7) == 0){
                result = parseLine(line);
                break;
            }
        }
        fclose(file);
        return result;
    }

//Physical Memory currently used by current process:
    int getValue(){ //Note: this value is in KB!
        FILE* file = fopen("/proc/self/status", "r");
        int result = -1;
        char line[128];
    
        while (fgets(line, 128, file) != NULL){
            if (strncmp(line, "VmRSS:", 6) == 0){
                result = parseLine(line);
                break;
            }
        }
        fclose(file);
        return result;
    }	
	
//CPU currently used by current process:
    #include "stdlib.h"
    #include "stdio.h"
    #include "string.h"
    #include "sys/times.h"
    #include "sys/vtimes.h"
    
    static clock_t lastCPU, lastSysCPU, lastUserCPU;
    static int numProcessors;
    
    void init(){
        FILE* file;
        struct tms timeSample;
        char line[128];
    
        lastCPU = times(&timeSample);
        lastSysCPU = timeSample.tms_stime;
        lastUserCPU = timeSample.tms_utime;
    
        file = fopen("/proc/cpuinfo", "r");
        numProcessors = 0;
        while(fgets(line, 128, file) != NULL){
            if (strncmp(line, "processor", 9) == 0) numProcessors++;
        }
        fclose(file);
    }
    
    double getCurrentValue(){
        struct tms timeSample;
        clock_t now;
        double percent;
    
        now = times(&timeSample);
        if (now <= lastCPU || timeSample.tms_stime < lastSysCPU ||
            timeSample.tms_utime < lastUserCPU){
            //Overflow detection. Just skip this value.
            percent = -1.0;
        }
        else{
            percent = (timeSample.tms_stime - lastSysCPU) +
                (timeSample.tms_utime - lastUserCPU);
            percent /= (now - lastCPU);
            percent /= numProcessors;
            percent *= 100;
        }
        lastCPU = now;
        lastSysCPU = timeSample.tms_stime;
        lastUserCPU = timeSample.tms_utime;
    
        return percent;
    }	
