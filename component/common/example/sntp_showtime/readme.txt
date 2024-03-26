LWIP SNTP SHOWTIME EXAMPLE

Description:
Show system time maintained by time from NTP server and system tick.

Configuration:
Can Modify SNTP_SERVER_ADDRESS and SNTP_UPDATE_DELAY in sntp.c for NTP time update
For SNTP_UPDATE_DELAY to work, SNTP_STARTUP_DELAY should be defined

[platform_opts.h]
	#define CONFIG_EXAMPLE_SNTP_SHOWTIME    1

Execution:
Can make automatical Wi-Fi connection when booting by using wlan fast connect example.
A lwip ntp showtime example thread will be started automatically when booting.

Expected result:
When "#define TIME_MODE 0" it should show UTC time in microseconds:
Example:
	Tue Jan  2 09:02:03 2024
	 + 169829 usec

When "#define TIME_MODE 1" it should show current timezone with seconds:
Example: 2024-1-8 10:51:13 UTC+8

[Supported List]
	Supported :
	    Ameba-1, Ameba-z, Ameba-pro, Ameba-z2, Ameba-D