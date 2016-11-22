/*  main.c  - main */

#include <xinu.h>

process	main(void)
{

	int32	retval;
	pid32	netpid;
	uint32	localip;
	char	buff[200];
	uint32  lent=0;
	uint32	waitfor = 60000;	// milliseconds to wait while receiving UDP packets
	int32 	i;
	int32 	slot=0;
	struct	udpentry *udptr;
	
	
	
	open(ETHER0,NULL, NULL);
	
	resume( (netpid = create(netin, 8192, 50, "netin", 0)) );
	kprintf("\n\r**********************************************************\n\r");
	NetData.ipvalid = FALSE;
	retval = getlocalip();
	if (retval == SYSERR) {
		panic("Error: could not obtain an IP address\n\r");
	} else {
		
		/*	Print IP address in ASCII and Hex	*/
	    kprintf("IP address is %d.%d.%d.%d   %08x\n\r",
		(retval>>24)&0xff, (retval>>16)&0xff, (retval>>8)&0xff,
		 retval&0xff,retval);

		 /*	Print Subnet mask and IP address of router	*/
		 
	    kprintf("Subnet mask is %d.%d.%d.%d and router is %d.%d.%d.%d\n\r",
		(NetData.ipmask>>24)&0xff, (NetData.ipmask>>16)&0xff,
		(NetData.ipmask>> 8)&0xff,  NetData.ipmask&0xff,
		(NetData.iprouter>>24)&0xff, (NetData.iprouter>>16)&0xff,
		(NetData.iprouter>> 8)&0xff, NetData.iprouter&0xff);
	}

	/* Try sending a packet to port 33000 */
	//localip = NetData.ipaddr;
	kprintf("\n\r**********************************************************\n\r");
	kprintf("Trying to send a UDP message to 0xC0A80205 port 33000\n\r");
	retval = udp_register(0, 33000,31000);	// Register slot in udptab
	if (retval == SYSERR) {
		kprintf("cannot register 0, 33000, 31000\n\r");
	}
	
	/*	Keep sending a UDP packet and receiving for 60 seconds after each send	*/
	
	while (TRUE) 					
	{
			/*Reset buff to blank*/
			for(i=0;i<200;i++)
			{
				buff[i]=NULL;
			}
		//for (slot=0; slot<UDP_SLOTS; slot++)
		//{
			udptr = &udptab[slot];
			if(udptr->udstate != UDP_FREE)	// Ensure slot is valid
			{
			//retval = udp_send(IP_BCAST, "Hello there...    \n\n",20);
			retval = udp_sendto(slot,0xC0A80205,33000, "Hello there...    \n\n",20);
			}
			else	// if slot is not valid
			{
				retval = SYSERR;
				kprintf("No valid slot\n\r");
			}

			if (retval == SYSERR) // Slot was invalid, UDP not sent
			{
				kprintf("cannot send UDP\n\r");
			}
			else	// UDP sent
			{
				kprintf("UDP SENT\n\r");
			}
			/*Reset buff to blank*/
			for(i=0;i<200;i++)
			{
				buff[i]=NULL;
			}
		kprintf("Trying to receive a UDP message to port 31000\n\r");
		lent = udp_recv(slot,buff,sizeof(buff),waitfor);
		kprintf("Received value %s\n",buff);
		//}
		kprintf("press enter to send again: ");
		retval = read(CONSOLE, buff, 200);
		if (retval == EOF) {
			break;
		}
	}
	
	/* Run the Xinu shell */

	//recvclr();
	//resume(create(shell, 8192, 50, "shell", 1, CONSOLE));
	
	/* Wait for shell to exit and recreate it */
/*
	while (TRUE) {
		receive();
		sleepms(200);
		kprintf("\n\nMain process recreating shell\n\n");
		resume(create(shell, 4096, 20, "shell", 1, CONSOLE));
	}
*/
	return OK;
    
}
