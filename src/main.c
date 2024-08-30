/* Light Fetch 
 *   For UNIX-LIKE OSes. For Example: Linux, BSD, Macos, etc.*/
	
        /* Made by Valentin */



/* Getting Libraries */

#include <stdio.h>
#include <sys/utsname.h>
#include <unistd.h>         // library for gethostname
#include <limits.h>         // library needed for HOST_NAME_MAX
#include <string.h>
#include <stdlib.h>
#include <sys/statvfs.h>

/* GLOBAL Variables */

int show_cpu_name = 0;
int show_gpu_name = 0;
int show_gpu_vendor = 0;
int memory_show_style = 2;
int show_uptime_seconds = 0;
int show_uptime = 0;
int show_ram_usage = 0;


/* Functions */



/* Getting Values from 'lightfetch.conf' File */

void get_config_parameters() {
        FILE *fp;
        char buffer[256];

        fp = fopen("lightfetch.conf", "r");

        while(fgets(buffer, sizeof(buffer), fp))
        {
                if(sscanf(buffer, "GPU-Vendor: %d", &show_gpu_vendor) == 1)
                {
                        continue;
                }
                if(sscanf(buffer, "Memory-Show-Style: %d", &memory_show_style) == 1)
                {
                        continue;
                }
                if(sscanf(buffer, "Show-Uptime-Seconds: %d", &show_uptime_seconds) == 1)
                {
                        continue;
                }
                if(sscanf(buffer, "Show-Uptime: %d", &show_uptime) == 1)
                {
                        continue;
                }
                if(sscanf(buffer, "Show-Ram-Usage: %d", &show_ram_usage) == 1)
                {
                        continue;
                }
                if(sscanf(buffer, "Show-CPU-Name: %d", &show_cpu_name) == 1)
                {
                        continue;
                }
                if(sscanf(buffer, "Show-GPU-Name: %d", &show_gpu_name) == 1)
                {
                        continue;
                }
        }
	    fclose(fp);
}   


void get_cpu_name() {
        if (show_cpu_name == 1) {
                FILE *fp;
	            char buffer[1024];
	            char *match = "model name";

	            fp = fopen("/proc/cpuinfo", "r");

	            while (fgets(buffer,sizeof(buffer), fp)) {
		                if (strncmp(buffer, match, strlen(match)) == 0) {
			                    char *cpu_name = strchr(buffer, ':') + 2;	// Finding the ':' and printing the value after it
			                    printf("\033[1mCPU\033[0m: %s", cpu_name);
			                    break;
		                }
	            }
	            fclose(fp);
        }
}

void get_gpu_name() {
        if (show_gpu_name == 1) {
                FILE *fp;
	            char gpu_name[256];

	            fp = popen("lshw -C display 2>/dev/null | grep 'product:' | sed 's/product: //'", "r");
	            fgets(gpu_name, sizeof(gpu_name), fp);
	            printf("\033[1mGPU\033[0m: %s", gpu_name);

	            pclose(fp);
        }

	    /*   Finding Informatino about the GPU vendor ( Can be turned on, if you want to :) )   */
    
        if(show_gpu_vendor == 1) {
                FILE *fp;
                char gpu_vendor[256] = "Unknown";
	    
                fp = popen("lshw -C display 2>/dev/null | grep 'vendor:' | sed 's/vendor: //'", "r");
	            fgets(gpu_vendor, sizeof(gpu_vendor), fp);
	            printf("\033[1mGPU\033[0m: %s", gpu_vendor);

	            pclose(fp);
        
        }
}



void get_ram_usage() {
	
        if(show_ram_usage == 1) {
                FILE *fp;
	            char buffer[256];
	            unsigned long total_memory = 0;
	            unsigned long free_memory = 0;
	            unsigned long available_memory = 0;

	            unsigned long buffers = 0;
	            unsigned long cached = 0;

	            fp = fopen("/proc/meminfo", "r");
    
	            while(fgets(buffer, sizeof(buffer), fp))
	            {
	                    if(sscanf(buffer, "MemTotal: %lu kB )", &total_memory) == 1)    
                        {
                                continue;
	                    }

                        if(sscanf(buffer, "MemFree: %lu kB", &free_memory) == 1)
                        {
	    	                    continue;
                        }

     	                if(sscanf(buffer, "MemAvailable: %lu kB", &available_memory) == 1)
	                    {
	 	                        continue;
	                    }

	                    if(sscanf(buffer, "Buffers: %lu kB", &buffers) == 1)
	                    {
		                        continue;
	                    }

	                    if(sscanf(buffer, "Cached: %lu kB", &cached) == 1)
	                    {
		                        continue;
	                    }
	            }
    
                fclose(fp);
    
    
	            /* Calculations */

	            //unsigned long used_memory = total_memory - free_memory - cached + buffers;     // Gives Numbers more like in htop
	            unsigned long used_memory = total_memory - available_memory;			 // More accurate (as in command: 'free -h')
    
    
	            /* Converting kB to MiB (comment everything out, if you don't want to convert kB to MiB) */
    
	            double total_memory_mib = total_memory / 1024.0;
	            double free_memory_mib = free_memory / 1024.0;
	            double used_memory_mib = used_memory / 1024.0;
                double available_memory_mib = available_memory / 1024.0;
    
	            double buffers_mib = buffers / 1024.0;
	            double cached_mib = cached / 1024.0;

    
	            /* (1.) ALL-IN-ONE-STYLE (RAM) */
    

    
	            /* Printing the values (for memory in MiB) */

    
                switch(memory_show_style) {
                        case 1:
                                /* (1.) ALL-IN-ONE-STYLE (RAM) */
                                printf("\033[1mTotal Memory\033[0m: %.1lf MiB\n", total_memory_mib);
	                            printf("\033[1mFree Memory\033[0m: %.1lf MiB\n", free_memory_mib);			// Amount of memory that is completely unallocated. (Raw amount of unused RAM)
                                printf("\033[1mAvailable Memory\033[0m: %.1lf MiB\n", available_memory_mib);          // Amount of memory that can be used for other processes (More accurate amount of unused RAM)
                                printf("\033[1mUsed Memory\033[0m: %.1lf MiB\n", used_memory_mib);
      	                        printf("\033[1mBuffers\033[0m: %.1lf MiB\n", buffers_mib);
                                printf("\033[1mCached\033[0m: %.1lf MiB\n", cached_mib);
                                break;

                        case 2:
                                /* (2.) HTOP/FETCH-PROGRAMS-STYLE (RAM) */
                                printf("\033[1mMemory:\033[0m %.1lf MiB/%.1lf MiB\n", used_memory_mib, total_memory_mib);
                                break;
                }   
        
	            /* Printing the values (for memory in kB)
	

	            printf("Total Memory: %lu kB\n", total_memory);
	            printf("Free Memory: %lu kB\n", free_memory);
	            printf("Used Memory: %lu kB\n", used_memory);
	
	            printf("Buffers: %lu kB\n", buffers);
	            printf("Cached: %lu kB\n", cached);
	
	            */
        }    
}

void get_uptime() {

        if(show_uptime == 1) {
                FILE *fp;
    
                double uptime_seconds;
    
                int uptime_minutes;
                int uptime_hours;


                fp = fopen("/proc/uptime", "r");

                if(fscanf(fp, "%lf", &uptime_seconds) == 1){
                }

                fclose(fp);

                /* Calculations */

                uptime_minutes = uptime_seconds / 60;
                uptime_hours = uptime_minutes / 60;

                while(uptime_minutes >= 60) {
                        uptime_minutes -= 60;
                }

                if(show_uptime_seconds == 0) {
                        switch(uptime_hours) {
                                case 0:
                                        printf("\033[1mUptime\033[0m: %d m\n", uptime_minutes);
                                        break;
                                default:
                                        printf("\033[1mUptime\033[0m: %d h, %d m\n", uptime_hours, uptime_minutes);
                        }
                }
                else if(show_uptime_seconds == 1) {
                        printf("\033[1mUptime\033[0m: %.2f seconds\n", uptime_seconds);
                }

        }
}





/* In Testing (I don't think it will be in final program ) */

//void get_disk_usage(const char *path)
//{
//        struct statvfs stat;
//
//        * Getting file system statistics */
//        if(statvfs(path, &stat) != 0) {
//            perror("statvfs");
//            exit(EXIT_FAILURE);
//        }
//
//       /* Declaring Variables / Calculations */
//
 //       unsigned long total_size_bytes = stat.f_blocks * stat.f_frsize;
  //      unsigned long free_size_bytes = stat.f_bfree * stat.f_frsize;
 //       unsigned long used_size_bytes = total_size_bytes - free_size_bytes;




/* Main Loop */

int main()
{

        struct utsname  buffer;

        char hostname[HOST_NAME_MAX + 1]; // +1 for null terminator

        gethostname(hostname, sizeof(hostname));


        if (uname(&buffer) != 0) {
                perror("uname");
	            return 1;
	    }

        /* Getting Path to the file system */
        //const char *path = "/";


        /* Printing LightFetch */

        get_config_parameters();

        printf("\n\033[1mOS/Distro:\033[0m %s  (%s)\n", buffer.nodename,  buffer.sysname);
        printf("\033[1mKernel:\033[0m %s\n", buffer.release);
        printf("\033[1mArchitecture:\033[0m %s\n", buffer.machine);
        printf("\033[1mHostname:\033[0m %s\n", hostname);

        get_uptime();
        get_cpu_name();
        get_gpu_name();
        get_ram_usage();
        //get_disk_usage(path);

        printf("\n");


        return 0;

}
