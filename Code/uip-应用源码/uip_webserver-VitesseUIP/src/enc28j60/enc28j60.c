/********************************************************************************
 * vim:sw=8:ts=8:si:et
 * To use the above modeline in vim you must have "set modeline" in your .vimrc
 * Author: Guido Socher 
 * Copyright: GPL V2
 * http://www.gnu.org/licenses/gpl.html
 *
 * Based on the enc28j60.c file from the AVRlib library by Pascal Stang.
 * For AVRlib See http://www.procyonengineering.com/
 * Used with explicit permission of Pascal Stang.
 *
 * Title: Microchip ENC28J60 Ethernet Interface Driver
 * Chip type           : ATMEGA88 with ENC28J60
 *******************************************************************************/

#include "enc28j60.h"
#include "spi_enc28j60.h"
#include "delay.h"

#define MIN(a,b) (a) < (b) ? (a) : (b)
static unsigned char Enc28j60Bank;
static unsigned int NextPacketPtr;


unsigned char enc28j60ReadOp(unsigned char op, unsigned char address)
{
    unsigned char dat = 0;
    
    ENC28J60_CSL();
    
    dat = op | (address & ADDR_MASK);
    SPI1_ReadWrite(dat);
    dat = SPI1_ReadWrite(0xFF);
    // do dummy read if needed (for mac and mii, see datasheet page 29)
    if(address & 0x80)
    {
        dat = SPI1_ReadWrite(0xFF);
    }
    // release CS
    ENC28J60_CSH();
    return dat;
}

void enc28j60WriteOp(unsigned char op, unsigned char address, unsigned char data)
{
    unsigned char dat = 0;
    
    ENC28J60_CSL();
    // issue write command
    dat = op | (address & ADDR_MASK);
    SPI1_ReadWrite(dat);
    // write data
    dat = data;
    SPI1_ReadWrite(dat);
    ENC28J60_CSH();
}

void enc28j60ReadBuffer(unsigned int len, unsigned char* data)
{
    ENC28J60_CSL();
    // issue read command
    SPI1_ReadWrite(ENC28J60_READ_BUF_MEM);
    while(len)
    {
        len--;
        // read data
        *data = (unsigned char)SPI1_ReadWrite(0);
        data++;
    }
    *data='\0';
    ENC28J60_CSH();
}

void enc28j60WriteBuffer(unsigned int len, unsigned char* data)
{
    ENC28J60_CSL();
    // issue write command
    SPI1_ReadWrite(ENC28J60_WRITE_BUF_MEM);
    
    while(len)
    {
        len--;
        SPI1_ReadWrite(*data);
        data++;
    }
    ENC28J60_CSH();
}

void enc28j60SetBank(unsigned char address)
{
    // set the bank (if needed)
    if((address & BANK_MASK) != Enc28j60Bank)
    {
        // set the bank
        enc28j60WriteOp(ENC28J60_BIT_FIELD_CLR, ECON1, (ECON1_BSEL1|ECON1_BSEL0));
        enc28j60WriteOp(ENC28J60_BIT_FIELD_SET, ECON1, (address & BANK_MASK)>>5);
        Enc28j60Bank = (address & BANK_MASK);
    }
}

unsigned char enc28j60Read(unsigned char address)
{
    // set the bank
    enc28j60SetBank(address);
    // do the read
    return enc28j60ReadOp(ENC28J60_READ_CTRL_REG, address);
}

void enc28j60Write(unsigned char address, unsigned char data)
{
    // set the bank
    enc28j60SetBank(address);
    // do the write
    enc28j60WriteOp(ENC28J60_WRITE_CTRL_REG, address, data);
//	data = 0;
//	enc28j60WriteOp(ENC28J60_READ_CTRL_REG, address, data);
	
}

void enc28j60PhyWrite(unsigned char address, unsigned int data)
{
    // set the PHY register address
    enc28j60Write(MIREGADR, address);
    // write the PHY data
    enc28j60Write(MIWRL, data);
    enc28j60Write(MIWRH, data>>8);
    // wait until the PHY write completes
    while(enc28j60Read(MISTAT) & MISTAT_BUSY)
    {
        //Del_10us(1);
        //_nop_();
    }
}

void enc28j60clkout(unsigned char clk)
{
    //setup clkout: 2 is 12.5MHz:
    enc28j60Write(ECOCON, clk & 0x7);
}

void enc28j60Init(unsigned char* macaddr)
{   
    //u16 i;
    ENC28J60_CSH();	      

    // perform system reset
    enc28j60WriteOp(ENC28J60_SOFT_RESET, 0, ENC28J60_SOFT_RESET);
   
    // check CLKRDY bit to see if reset is complete
    // The CLKRDY does not work. See Rev. B4 Silicon Errata point. Just wait.
    //while(!(enc28j60Read(ESTAT) & ESTAT_CLKRDY));
    // do bank 0 stuff
    // initialize receive buffer
    // 16-bit transfers, must write low byte first
    // set receive buffer start address	  
	delay_ms(3);	  //gjk errata 2
	 
    NextPacketPtr = RXSTART_INIT;
    // Rx start    
    enc28j60Write(ERXSTL, RXSTART_INIT&0xFF);	 
    enc28j60Write(ERXSTH, RXSTART_INIT>>8);
    // set receive pointer address     
    enc28j60Write(ERXRDPTL, RXSTART_INIT&0xFF);
    enc28j60Write(ERXRDPTH, RXSTART_INIT>>8);
    // RX end
    enc28j60Write(ERXNDL, RXSTOP_INIT&0xFF);
    enc28j60Write(ERXNDH, RXSTOP_INIT>>8);
    // TX start	  1500
    enc28j60Write(ETXSTL, TXSTART_INIT&0xFF);
    enc28j60Write(ETXSTH, TXSTART_INIT>>8);
    // TX end
    enc28j60Write(ETXNDL, TXSTOP_INIT&0xFF);
    enc28j60Write(ETXNDH, TXSTOP_INIT>>8);
    // do bank 1 stuff, packet filter:
    // For broadcast packets we allow only ARP packtets
    // All other packets should be unicast only for our mac (MAADR)
    //
    // The pattern to match on is therefore
    // Type     ETH.DST
    // ARP      BROADCAST
    // 06 08 -- ff ff ff ff ff ff -> ip checksum for theses bytes=f7f9
    // in binary these poitions are:11 0000 0011 1111
    // This is hex 303F->EPMM0=0x3f,EPMM1=0x30
    
   // enc28j60Write(ERXFCON, ERXFCON_UCEN|ERXFCON_CRCEN|ERXFCON_PMEN);
	enc28j60Write(ERXFCON, ERXFCON_UCEN|ERXFCON_CRCEN|ERXFCON_BCEN);  //Ŀ����ʵ��DHCP
    enc28j60Write(EPMM0, 0x3f);
    enc28j60Write(EPMM1, 0x30);
    enc28j60Write(EPMCSL, 0xf9);
    enc28j60Write(EPMCSH, 0xf7);    
    enc28j60Write(MACON1, MACON1_MARXEN|MACON1_TXPAUS|MACON1_RXPAUS);
    // bring MAC out of reset 
    enc28j60Write(MACON2, 0x00);	  
    
    enc28j60WriteOp(ENC28J60_BIT_FIELD_SET, MACON3, MACON3_PADCFG0|MACON3_TXCRCEN|MACON3_FRMLNEN|MACON3_FULDPX);
    // set inter-frame gap (non-back-to-back)

    enc28j60Write(MAIPGL, 0x12);
    enc28j60Write(MAIPGH, 0x0C);
    // set inter-frame gap (back-to-back)

    enc28j60Write(MABBIPG, 0x15);	 
    // Set the maximum packet size which the controller will accept
    // Do not send packets longer than MAX_FRAMELEN:
  
    enc28j60Write(MAMXFLL, MAX_FRAMELEN&0xFF);	
    enc28j60Write(MAMXFLH, MAX_FRAMELEN>>8);
    // do bank 3 stuff
    // write MAC address
    // NOTE: MAC address in ENC28J60 is byte-backward
    enc28j60Write(MAADR5, macaddr[0]);	
    enc28j60Write(MAADR4, macaddr[1]);
    enc28j60Write(MAADR3, macaddr[2]);
    enc28j60Write(MAADR2, macaddr[3]);
    enc28j60Write(MAADR1, macaddr[4]);
    enc28j60Write(MAADR0, macaddr[5]);

    //����PHYΪȫ˫��  LEDBΪ������
    enc28j60PhyWrite(PHCON1, PHCON1_PDPXMD);    
     /* PHY LED */	
    enc28j60PhyWrite(PHLCON,0x476);

    // no loopback of transmitted frames
    enc28j60PhyWrite(PHCON2, PHCON2_HDLDIS);

    // switch to bank 0    
    enc28j60SetBank(ECON1);

    // enable interrutps
 //   enc28j60WriteOp(ENC28J60_BIT_FIELD_SET, EIE, EIE_INTIE|EIE_PKTIE);

    // enable packet reception
    enc28j60WriteOp(ENC28J60_BIT_FIELD_SET, ECON1, ECON1_RXEN);
		
}

// read the revision of the chip:
unsigned char enc28j60getrev(void)
{
    //��EREVID ��Ҳ�洢�˰汾��Ϣ�� EREVID ��һ��ֻ����
    //�ƼĴ���������һ��5 λ��ʶ����������ʶ�����ض���Ƭ
    //�İ汾��
    return(enc28j60Read(EREVID));
}

void enc28j60PacketSend(unsigned int len, unsigned char* packet)
{
	 //enc28j60WriteOp(ENC28J60_BIT_FIELD_SET,ECON1, ECON1_TXRST);		   //by gjk
     //enc28j60WriteOp(ENC28J60_BIT_FIELD_CLR,ECON1, ECON1_TXRST);		   //by gjk
     //enc28j60WriteOp(ENC28J60_BIT_FIELD_CLR,EIR, EIR_TXERIF | EIR_TXIF); //by gjk
	 //enc28j60WriteOp(ENC28J60_BIT_FIELD_SET,ECON1, ECON1_TXRTS);		   //by gjk




    // Set the write pointer to start of transmit buffer area
	enc28j60Write(EWRPTL, (TXSTART_INIT)&0xFF);
	enc28j60Write(EWRPTH, (TXSTART_INIT)>>8);
	// Set the TXND pointer to correspond to the packet size given
	enc28j60Write(ETXNDL, (TXSTART_INIT+len)&0xFF);
	enc28j60Write(ETXNDH, (TXSTART_INIT+len)>>8);
	// write per-packet control byte (0x00 means use macon3 settings)
	enc28j60WriteOp(ENC28J60_WRITE_BUF_MEM, 0, 0x00);
	// copy the packet into the transmit buffer
	enc28j60WriteBuffer(len, packet);
	// send the contents of the transmit buffer onto the network
	enc28j60WriteOp(ENC28J60_BIT_FIELD_SET, ECON1, ECON1_TXRTS);

    if(enc28j60getrev() == 0x05u || enc28j60getrev() == 0x06u)
	{
		u16 AttemptCounter = 0x0000;
		while((enc28j60Read(EIR) & (EIR_TXERIF | EIR_TXIF)) && (++AttemptCounter < 1000));
		if((enc28j60Read(EIR) & EIR_TXERIF) || (AttemptCounter >= 1000))
		{
			WORD_VAL ReadPtrSave;
			WORD_VAL TXEnd;
			TXSTATUS TXStatus;
			u8 i;

			// Cancel the previous transmission if it has become stuck set
			//BFCReg(ECON1, ECON1_TXRTS);
            enc28j60WriteOp(ENC28J60_BIT_FIELD_CLR, ECON1, ECON1_TXRTS);

			// Save the current read pointer (controlled by application)
			ReadPtrSave.v[0] = enc28j60Read(ERDPTL);
			ReadPtrSave.v[1] = enc28j60Read(ERDPTH);

			// Get the location of the transmit status vector
			TXEnd.v[0] = enc28j60Read(ETXNDL);
			TXEnd.v[1] = enc28j60Read(ETXNDH);
			TXEnd.Val++;
			
			// Read the transmit status vector
			enc28j60Write(ERDPTL, TXEnd.v[0]);
			enc28j60Write(ERDPTH, TXEnd.v[1]);

			enc28j60ReadBuffer(sizeof(TXStatus) ,(u8*)&TXStatus);

			// Implement retransmission if a late collision occured (this can 
			// happen on B5 when certain link pulses arrive at the same time 
			// as the transmission)
			for(i = 0; i < 16u; i++)
			{
				if((enc28j60Read(EIR) & EIR_TXERIF) && TXStatus.bits.LateCollision)
				{
					// Reset the TX logic
                    enc28j60WriteOp(ENC28J60_BIT_FIELD_SET, ECON1, ECON1_TXRTS);
                    enc28j60WriteOp(ENC28J60_BIT_FIELD_CLR, ECON1, ECON1_TXRTS);
                    enc28j60WriteOp(ENC28J60_BIT_FIELD_CLR, EIR, EIR_TXERIF | EIR_TXIF);

					// Transmit the packet again
					enc28j60WriteOp(ENC28J60_BIT_FIELD_SET, ECON1, ECON1_TXRTS);
					while(!(enc28j60Read(EIR) & (EIR_TXERIF | EIR_TXIF)));

					// Cancel the previous transmission if it has become stuck set
					enc28j60WriteOp(ENC28J60_BIT_FIELD_CLR, ECON1, ECON1_TXRTS);

					// Read transmit status vector
					enc28j60Write(ERDPTL, TXEnd.v[0]);
					enc28j60Write(ERDPTH, TXEnd.v[1]);
                    enc28j60ReadBuffer(sizeof(TXStatus) ,(u8*)&TXStatus);
				}
				else
				{
					break;
				}
			}

			// Restore the current read pointer
			enc28j60Write(ERDPTL, ReadPtrSave.v[0]);
			enc28j60Write(ERDPTH, ReadPtrSave.v[1]);
		}
	}
    // Reset the transmit logic problem. See Rev. B4 Silicon Errata point 12.
	if( (enc28j60Read(EIR) & EIR_TXERIF) )
    {
        //enc28j60WriteOp(ENC28J60_BIT_FIELD_CLR, ECON1, ECON1_TXRTS);
		enc28j60WriteOp(ENC28J60_BIT_FIELD_CLR, ECON1, ECON1_TXRST);
    }
}
// Gets a packet from the network receive buffer, if one is available.
// The packet will by headed by an ethernet header.
//      maxlen  The maximum acceptable length of a retrieved packet.
//      packet  Pointer where packet data should be stored.
// Returns: Packet length in bytes if a packet was retrieved, zero otherwise.
unsigned int enc28j60PacketReceive(unsigned int maxlen, unsigned char* packet)
{
 unsigned int rxstat;
    unsigned int len;
    
    // check if a packet has been received and buffered
    //if( !(enc28j60Read(EIR) & EIR_PKTIF) ){
    // The above does not work. See Rev. B4 Silicon Errata point 6.
    if( enc28j60Read(EPKTCNT) ==0 )  //�յ�����̫�����ݰ�����
    {
        return(0);
    }
    
    // Set the read pointer to the start of the received packet		 ��������ָ��
    enc28j60Write(ERDPTL, (NextPacketPtr));
    enc28j60Write(ERDPTH, (NextPacketPtr)>>8);
    
    // read the next packet pointer
    NextPacketPtr  = enc28j60ReadOp(ENC28J60_READ_BUF_MEM, 0);
    NextPacketPtr |= enc28j60ReadOp(ENC28J60_READ_BUF_MEM, 0)<<8;
    
    // read the packet length (see datasheet page 43)
    len  = enc28j60ReadOp(ENC28J60_READ_BUF_MEM, 0);
    len |= enc28j60ReadOp(ENC28J60_READ_BUF_MEM, 0)<<8;
    
    len-=4; //remove the CRC count
    // read the receive status (see datasheet page 43)
    rxstat  = enc28j60ReadOp(ENC28J60_READ_BUF_MEM, 0);
    rxstat |= enc28j60ReadOp(ENC28J60_READ_BUF_MEM, 0)<<8;
    // limit retrieve length
    if (len>maxlen)
    {
        len=maxlen;		//by gjk
    }
    
    // check CRC and symbol errors (see datasheet page 44, table 7-3):
    // The ERXFCON.CRCEN is set by default. Normally we should not
    // need to check this.
    if ((rxstat & 0x80)==0)
    {
        // invalid
        len=0;
    }
    else
    {
        // copy the packet from the receive buffer
        enc28j60ReadBuffer(len, packet);
    }
    // Move the RX read pointer to the start of the next received packet
    // This frees the memory we just read out
    enc28j60Write(ERXRDPTL, (NextPacketPtr));
    enc28j60Write(ERXRDPTH, (NextPacketPtr)>>8);
    
    // decrement the packet counter indicate we are done with this packet
    enc28j60WriteOp(ENC28J60_BIT_FIELD_SET, ECON2, ECON2_PKTDEC);
    return(len);
}
//*******************************************************************************************
//
// Function : icmp_send_request
// Description : Send ARP request packet to destination.
//
//*******************************************************************************************

unsigned int enc28j60_read_phyreg(unsigned char address)	 //by gjk 2013-02-20
{
	unsigned int mydat;
	
	// set the PHY register address
	enc28j60Write(MIREGADR, address);
	enc28j60Write(MICMD, MICMD_MIIRD);
	
	// Loop to wait until the PHY register has been read through the MII
	// This requires 10.24us
	while( (enc28j60Read(MISTAT) & MISTAT_BUSY) );
	
	// Stop reading
	//enc28j60Write(MICMD, MICMD_MIIRD);
	enc28j60Write(MICMD,0x00);	  /*by gjk 09/03/09  ��ֵ0x00*/
	// Obtain results and return
	mydat = enc28j60Read ( MIRDH );
	mydat<<=8;	 /*jerkoh090120*/
	mydat |= enc28j60Read ( MIRDL );
	

	return mydat;
}


//*******************************************************************************************
//
// Function : enc28j60_mac_is_linked
// Description : return MAC link status.
//
//*******************************************************************************************

unsigned char  enc28j60_mac_is_linked(void)		//by gjk 2013-02-20
{
	if ( (enc28j60_read_phyreg(PHSTAT1) & PHSTAT1_LLSTAT ) )
	   {    
		return 1;	    /*ok*/
	   }
	else
	   {	   
		return 0;	    /*error*/
	   }
}

/*
void enc28j60RegDump(void)
{   			
	debug_printf("RevID: 0x%x\n", enc28j60Read(EREVID));

	debug_printf( ("Cntrl: ECON1 ECON2 ESTAT  EIR  EIE\n"));
	debug_printf( ("         "));
	debug_printf("%02x",enc28j60Read(ECON1));
	debug_printf( ("    "));
	debug_printf("%02x",enc28j60Read(ECON2));
	debug_printf( ("    "));
	debug_printf("%02x",enc28j60Read(ESTAT));
	debug_printf( ("    "));
	debug_printf("%02x",enc28j60Read(EIR));
	debug_printf( ("   "));
	debug_printf("%02x",enc28j60Read(EIE));
	debug_printf( ("\n"));

	debug_printf( ("MAC  : MACON1  MACON2  MACON3  MACON4  MAC-Address\n"));
	debug_printf( ("        0x"));
	debug_printf("%02x",enc28j60Read(MACON1));
	debug_printf( ("    0x"));
	debug_printf("%02x",enc28j60Read(MACON2));
	debug_printf( ("    0x"));
	debug_printf("%02x",enc28j60Read(MACON3));
	debug_printf( ("    0x"));
	debug_printf("%02x",enc28j60Read(MACON4));
	debug_printf( ("   "));
	debug_printf("%02x",enc28j60Read(MAADR5));
	debug_printf("%02x",enc28j60Read(MAADR4));
	debug_printf("%02x",enc28j60Read(MAADR3));
	debug_printf("%02x",enc28j60Read(MAADR2));
	debug_printf("%02x",enc28j60Read(MAADR1));
	debug_printf("%02x",enc28j60Read(MAADR0));
	debug_printf( ("\n"));

	debug_printf( ("Rx   : ERXST  ERXND  ERXWRPT ERXRDPT ERXFCON EPKTCNT MAMXFL\n"));
	debug_printf( ("       0x"));
	debug_printf("%02x",enc28j60Read(ERXSTH));
	debug_printf("%02x",enc28j60Read(ERXSTL));
	debug_printf( (" 0x"));
	debug_printf("%02x",enc28j60Read(ERXNDH));
	debug_printf("%02x",enc28j60Read(ERXNDL));
	debug_printf( ("  0x"));
	debug_printf("%02x",enc28j60Read(ERXWRPTH));
	debug_printf("%02x",enc28j60Read(ERXWRPTL));
	debug_printf( ("  0x"));
	debug_printf("%02x",enc28j60Read(ERXRDPTH));
	debug_printf("%02x",enc28j60Read(ERXRDPTL));
	debug_printf( ("   0x"));
	debug_printf("%02x",enc28j60Read(ERXFCON));
	debug_printf( ("    0x"));
	debug_printf("%02x",enc28j60Read(EPKTCNT));
	debug_printf( ("  0x"));
	debug_printf("%02x",enc28j60Read(MAMXFLH));
	debug_printf("%02x",enc28j60Read(MAMXFLL));
	debug_printf( ("\n"));

	debug_printf( ("Tx   : ETXST  ETXND  MACLCON1 MACLCON2 MAPHSUP\n"));
	debug_printf( ("       0x"));
	debug_printf("%02x",enc28j60Read(ETXSTH));
	debug_printf("%02x",enc28j60Read(ETXSTL));
	debug_printf( (" 0x"));
	debug_printf("%02x",enc28j60Read(ETXNDH));
	debug_printf("%02x",enc28j60Read(ETXNDL));
	debug_printf( ("   0x"));
	debug_printf("%02x",enc28j60Read(MACLCON1));
	debug_printf( ("     0x"));
	debug_printf("%02x",enc28j60Read(MACLCON2));
	debug_printf( ("     0x"));
	debug_printf("%02x",enc28j60Read(MAPHSUP));
	debug_printf( ("\n"));
	debug_printf( ("PHY   : PHCON1  PHCON2  PHSTAT1 PHSTAT2\n"));
	debug_printf( ("       0x"));
	debug_printf("%02x",enc28j60Read(PHCON1));//ist 16 bit breit nicht 8 !
	debug_printf( ("     0x"));
    debug_printf("%02x",enc28j60Read(PHCON2));//ist 16 bit breit nicht 8 !
    debug_printf( ("     0x"));
    debug_printf("%02x",enc28j60Read(PHSTAT1));//ist 16 bit breit nicht 8 !
	debug_printf( ("     0x"));
    debug_printf("%02x",enc28j60Read(PHSTAT2));//ist 16 bit breit nicht 8 !
    debug_printf( ("\n"));

}
*/
