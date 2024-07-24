/* Light Fetch 
 *   For Linux, BSD, Macos, Windows, etc.*/
	
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
			printf("CPU: %s", cpu_name);
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
	printf("GPU: %s", gpu_name);

	pclose(fp);


	/*   Finding Informatino about the GPU vendor ( Can be turned on, if you want to :) )

	fp = popen("lshw -C display 2>/dev/null | grep 'vendor:' | sed 's/vendor: //'", "r");
	fgets(gpu_vendor, sizeof(gpu_vendor), fp);
	printf("GPU: %s", gpu_vendor);

	pclose(fp);	*/
}


/* If you see this, I am currently working on this :D

void get_ram_usage() {
	FILE *fp;
	char buffer[256];
	unsigned long total_memory = 0;
	unsigned long free_memory = 0;
	unsigned long available_memory = 0;

	unsigned long buffer = 0;
	unsigned long cached = 0;


}

*/




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

printf("\nOS/Distro: %s  (%s)\n", buffer.nodename,  buffer.sysname);
printf("Kernel: %s\n", buffer.release);
printf("Architecture: %s\n", buffer.machine);
printf("Hostname: %s\n", hostname);
get_cpu_name();
get_gpu_name();

printf("\n");

return 0;
}
