
@portrecv(ipv4_addr, remote_port, local_port, data[], data_size)
{
	new i;
	
	printf("%d.%d.%d.%d %d->%d\n", ipv4_addr >> 24, (ipv4_addr >> 16) & 0xFF, (ipv4_addr >> 8) & 0xFF, ipv4_addr & 0xFF, remote_port, local_port)
	
	printf("Data Size: %d\r\nData:\r\n", data_size)
    
    for (i = 0; i < data_size; i++)
    {
        printf("%c ", data[i])
    }
    
    printf("\r\n")
	
}

@timer0()
{
	qcm_eth_sendudp(qcm_eth_make_ip_addr(172,29,2,108), 50000, ''hello'')

}

main()
{
	qcm_eth_init(qcm_eth_make_ip_addr(172,29,2,201), qcm_eth_make_ip_addr(172,29,100,1), qcm_eth_make_ip_addr(255, 255, 0, 0))
	
	sleep(500)
	
	qcm_eth_listenport(50000)
	
	qcm_timer_start(TIMER_0,1000,true)
    
}