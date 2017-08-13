#include<stdio.h>
#include<stdlib.h>
#include<sys/ioctl.h>
#include<unistd.h>
#include<linux/nvme_ioctl.h>
#include<fcntl.h>
#include<linux/types.h>
#define SMART_LEN 512

int main(int argc, char* argv[]){
	if(argc < 2){
		printf("kindly give the device file name\n");
		return 1;
		
	}	
	int fd;
	fd = open(argv[1],O_RDWR);
	if(fd == 0){
		printf("could not open device file\n");
		return 1;
	}else printf("device file opened successfully %d\n",fd);

	char data[SMART_LEN];
	for(register int i=0; i<SMART_LEN;data[i++]=0);
	struct nvme_admin_cmd cmd = {
		.opcode = 0x02,
		.nsid = 0xffffffff,
		.addr = data,
		.data_len = SMART_LEN,
		.cdw10 = 0x007F0002,//bit 31:28 reserved = 0h
				    // bit 27:16 NUMBER OF DWORDS = 07Fh(512B)
					//bit 15:08 RESERVED = 00h
				//bit 7:0 LOG PAGE IDENTIFIER = 02h

	};
	

	int ret;

	ret= ioctl(fd,NVME_IOCTL_ADMIN_CMD,&cmd);

	if(ret==0) printf("successful \n");
	else printf("failed %d\n",ret);
	
//	for(register int i=0;i<SMART_LEN;printf("%c",data[i++]));
	printf("SMART LOG DETAILS\n\n");
	if(data[0]&0x1)
		printf("--Available Spare Space has fallen below the threshold\n");
	if(data[0]&0x2)
		printf("--Temperature has exceed a critical threshold\n");
	if(data[0]&0x4)
		printf("--Device Reliability has been degraded\n");
	if(data[0]&0x8)
		printf("--Volatile memory backup device has failed\n");
	if(*((__u16*)(data+1)))
		printf("--Temperature: %d\n", *((__u16*)(data+1)));
	printf("--Available spare space: %d %\n",(int)data[3]);
	printf("--Available spare threshold: %d %\n",(int)data[4]);
	printf("--Percentage used(goes upto 255): %d %\n",(int)data[5]);
	printf("--Data Units Read(1000 units of 512B): %lld \n",*((__u64*)(data+32)) );
	printf("--Data Units Written(1000 units of 512B): %lld \n",*((__u64*)(data+48)));
	printf("--Host Read Commands: %lld \n", *((__u64*)(data+64)));
	printf("--Host Writes Commands: %lld \n", *((__u64*)(data+80)));
	printf("--Controller Busy Time: %lld \n",  *((__u64*)(data+96)));
	printf("--Power Cycles: %lld \n",  *((__u64*)(data+112)));
	printf("--Power On Hours: %lld \n", *((__u64*)(data+128)));
	printf("--Unsafe Shutdowns: %lld \n", *((__u64*)(data+144)));
	printf("--Media Errors: %lld \n", *((__u64*)(data+160)));
	printf("--Number of Error Information Log Entries: %lld \n", *((__u64*)(data+176)));

			

return 0;
}
