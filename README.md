# NVMe-SMART-LOG
This Code sends read SMART Log command and interpret the data thus returned.


STEPS to send the read SMART Log command in NVMe in LINUX: (it’s easy! we just have to send an admin command – Get Log Page)
1. Open the device file in O_RDWR mode.

2. Get 512 bytes allocated to receive and store the SMART data.

3. Prepare the “nvme_admin_cmd” structure.  This structure is defined in nvme drivers libraries.

4. Call the IOCTL function to send and register the admin command.

5. Interpret the returned raw data.


The code is self explanatory

Link to my BLOG for more details:
https://wisesciencewise.wordpress.com/2017/05/22/c-program-to-read-and-interpret-smart-log-of-an-nvme-drive/
