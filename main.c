/* Light Fetch 
 *   For UNIX-LIKE OSes. For Example: Linux, BSD, Macos, etc.*/
	
	/* Made by Valentin */



/* Getting Libraries */

#include <stdio.h>
#include <sys/utsname.h>
#include <unistd.h> // library for gethostname
#include <limits.h> // library needed for HOST_NAME_MAX
#include <string.h>
#include <stdlib.h>



/* Functions */

void get_cpu_name() {
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

void get_gpu_name() {
	FILE *fp;
	char gpu_name[256];
	char gpu_vendor[256] = "Unknown";

	fp = popen("lshw -C display 2>/dev/null | grep 'product:' | sed 's/product: //'", "r");
	fgets(gpu_name, sizeof(gpu_name), fp);
	printf("\033[1mGPU\033[0m: %s", gpu_name);

	pclose(fp);


	/*   Finding Informatino about the GPU vendor ( Can be turned on, if you want to :) )

	fp = popen("lshw -C display 2>/dev/null | grep 'vendor:' | sed 's/vendor: //'", "r");
	fgets(gpu_vendor, sizeof(gpu_vendor), fp);
	printf("GPU: %s", gpu_vendor);

	pclose(fp);	*/
}



void get_ram_usage() {
	FILE *fp;
	char buffer[256];
	unsigned long total_memory = 0;
	unsigned long free_memory = 0;
	unsigned long available_memory = 0;
	unsigned long used_memory = 0;

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
	    if(sscanf(buffer, "Active: %lu kB", &used_memory) == 1)
	    {
		continue;
	    }
	}

	fclose(fp);

	
	/* Calculations */

	//unsigned long used_memory = total_memory - available_memory;


	/* Converting kB to MiB (comment everything out, if you don't want to convert kB to MiB) */

	double total_memory_mib = total_memory / 1024.0;
	double free_memory_mib = free_memory / 1024.0;
	double used_memory_mib = used_memory / 1024.0;
	double available_memory_mib = available_memory / 1024.0;

	double buffers_mib = buffers / 1024.0;
	double cached_mib = cached / 1024.0;


	/* (1.) ALL-IN-ONE-STYLE (RAM) */



	/* Printing the values (for memory in MiB) */

	/*  

	printf("Total Memory: %.1lf MiB\n", total_memory_mib);
	printf("Free Memory: %.1lf MiB\n", free_memory_mib);			// Amount of memory that is completely unallocated. (Raw amount of unused RAM)
	printf("Available Memory: %.1lf MiB\n", available_memory_mib);          // Amount of memory that can be used for other processes (More accurate amount of unused RAM)
	printf("Used Memory: %.1lf MiB\n", used_memory_mib);
	
	printf("Buffers: %.1lf MiB\n", buffers_mib);
	printf("Cached: %.1lf MiB\n", cached_mib);
	
	*/


	/* Printing the values (for memory in kB)

	

	printf("Total Memory: %lu kB\n", total_memory);
	printf("Free Memory: %lu kB\n", free_memory);
	printf("Used Memory: %lu kB\n", used_memory);
	
	printf("Buffers: %lu kB\n", buffers);
	printf("Cached: %lu kB\n", cached);
	
	*/





	/* (2.) HTOP/FETCH-PROGRAMS-STYLE (RAM) */




	/* Printing the values (for memory in MiB) */

	/* FETCH STYLE ( SHOWS CATCHED MEMORY :/ ) */
	printf("\033[1mMemory:\033[0m %.1lf MiB/%.1lf MiB", used_memory_mib, total_memory_mib);

	/* (REAL)USED MEMORY / TOTAL MEMORY  'Version' */
	// printf("\033[1mMemory\033[0m: %.1lf/%.1lf MiB", used_memory_mib, total_memory_mib)
}






/* Main Loop */

int main()
{
struct utsname  buffer;

char hostname[HOST_NAME_MAX + 1]; // +1 for null terminator

/*
if (gethostname(hostname,
sizeof(hostname)) == 0) {
	printf("Host name: %s\n", hostname);
}    else {
	perror("gethostname");
	return 1;
}
*/

if (uname(&buffer) != 0) {
	perror("uname");
	return 1;
	}

gethostname(hostname, sizeof(hostname));




/* Printing LightFetch */

printf("\n\033[1mOS/Distro:\033[0m %s  (%s)\n", buffer.nodename,  buffer.sysname);
printf("\033[1mKernel:\033[0m %s\n", buffer.release);
printf("\033[1mArchitecture:\033[0m %s\n", buffer.machine);
printf("\033[1mHostname:\033[0m %s\n", hostname);
get_cpu_name();
get_gpu_name();
get_ram_usage();

printf("\n");

return 0;
}
