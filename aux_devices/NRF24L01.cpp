#include "NRF24L01.h"

#include <HAL/Interface/ISysTimer.h>

using namespace HAL;

namespace devices
{

#define NOP             0xFF  //�ղ���,����������״̬�Ĵ���	 
#define TX_ADDR         0x10  //���͵�ַ(���ֽ���ǰ),ShockBurstTMģʽ��,RX_ADDR_P0��˵�ַ���
#define NRF_WRITE_REG   0x20  //д���üĴ���,��5λΪ�Ĵ�����ַ
#define RX_ADDR_P0      0x0A  //����ͨ��0���յ�ַ,��󳤶�5���ֽ�,���ֽ���ǰ

#define RD_RX_PLOAD     0x61  //��RX��Ч����,1~32�ֽ�
#define WR_TX_PLOAD     0xA0  //дTX��Ч����,1~32�ֽ�
#define FLUSH_TX        0xE1  //���TX FIFO�Ĵ���.����ģʽ����
#define FLUSH_RX        0xE2  //���RX FIFO�Ĵ���.����ģʽ����
#define REUSE_TX_PL     0xE3  //����ʹ����һ������,CEΪ��,���ݰ������Ϸ���.
#define NOP             0xFF  //�ղ���,����������״̬�Ĵ���	 
	//SPI(NRF24L01)�Ĵ�����ַ
#define CONFIG          0x00  //���üĴ�����ַ;bit0:1����ģʽ,0����ģʽ;bit1:��ѡ��;bit2:CRCģʽ;bit3:CRCʹ��;
	//bit4:�ж�MAX_RT(�ﵽ����ط������ж�)ʹ��;bit5:�ж�TX_DSʹ��;bit6:�ж�RX_DRʹ��
#define EN_AA           0x01  //ʹ���Զ�Ӧ����  bit0~5,��Ӧͨ��0~5
#define EN_RXADDR       0x02  //���յ�ַ����,bit0~5,��Ӧͨ��0~5
#define SETUP_AW        0x03  //���õ�ַ���(��������ͨ��):bit1,0:00,3�ֽ�;01,4�ֽ�;02,5�ֽ�;
#define SETUP_RETR      0x04  //�����Զ��ط�;bit3:0,�Զ��ط�������;bit7:4,�Զ��ط���ʱ 250*x+86us
#define RF_CH           0x05  //RFͨ��,bit6:0,����ͨ��Ƶ��;
#define RF_SETUP        0x06  //RF�Ĵ���;bit3:��������(0:1Mbps,1:2Mbps);bit2:1,���书��;bit0:�������Ŵ�������
#define STATUS          0x07  //״̬�Ĵ���;bit0:TX FIFO����־;bit3:1,��������ͨ����(���:6);bit4,�ﵽ�����ط�
	//bit5:���ݷ�������ж�;bit6:���������ж�;

#define TX_ADR_WIDTH    5   //5�ֽڵĵ�ַ���
#define RX_ADR_WIDTH    5   //5�ֽڵĵ�ַ���
//uint8_t TX_ADDRESS[TX_ADR_WIDTH] = {0xb0,0x3d,0x12,0x34,0x01}; //���͵�ַ
//uint8_t RX_ADDRESS[RX_ADR_WIDTH] = {0xb0,0x3d,0x12,0x34,0x01}; //���͵�ַ
const uint8_t TX_ADDRESS[TX_ADR_WIDTH]={0xE7,0xE7,0xE7,0xE7,0xE7}; //���͵�ַ
const uint8_t RX_ADDRESS[RX_ADR_WIDTH]={0xC2,0xC2,0xC2,0xC2,0xC2}; //���͵�ַ
#define TX_PLOAD_WIDTH  32
#define RX_PLOAD_WIDTH  32



#define RX_PW_P0        0x11  //��������ͨ��0��Ч���ݿ��(1~32�ֽ�),����Ϊ0��Ƿ�
#define RX_PW_P1        0x12  //��������ͨ��1��Ч���ݿ��(1~32�ֽ�),����Ϊ0��Ƿ�
#define RX_PW_P2        0x13  //��������ͨ��2��Ч���ݿ��(1~32�ֽ�),����Ϊ0��Ƿ�
#define RX_PW_P3        0x14  //��������ͨ��3��Ч���ݿ��(1~32�ֽ�),����Ϊ0��Ƿ�
#define RX_PW_P4        0x15  //��������ͨ��4��Ч���ݿ��(1~32�ֽ�),����Ϊ0��Ƿ�
#define RX_PW_P5        0x16  //��������ͨ��5��Ч���ݿ��(1~32�ֽ�),����Ϊ0��Ƿ�
#define FIFO_STATUS     0x17  //FIFO״̬�Ĵ���;bit0,RX FIFO�Ĵ����ձ�־;bit1,RX FIFO����־;bit2,3,����
	//bit4,TX FIFO�ձ�־;bit5,TX FIFO����־;bit6,1,ѭ��������һ���ݰ�.0,��ѭ��;
int NRF24L01::init(HAL::ISPI *spi, HAL::IGPIO *cs, HAL::IGPIO *ce)
{
	this->spi = spi;
	this->cs = cs;
	this->ce = ce;

	cs->set_mode(MODE_OUT_PushPull);
	ce->set_mode(MODE_OUT_PushPull);

	cs->write(true);
	ce->write(false);

	spi->set_speed(10000000);
	spi->set_mode(0, 0);

	systimer->delayms(100);
	power_on();

	write_cmd(FLUSH_TX, NOP);
	write_cmd(FLUSH_RX, NOP);

	uint8_t buf[5] = {0xc2, 0xc2, 0xc2, 0xc2, 0xc2, };
	write_cmd(TX_ADDR | NRF_WRITE_REG, buf, 5);
	for(int i=0; i<5; i++)
		buf[i] = 0xff;
	read_cmd(TX_ADDR, buf, 5);

	for(int i=0; i<5; i++)
		if (buf[i] != 0xc2)
			return -1;

	write_cmd(TX_ADDR | NRF_WRITE_REG, TX_ADDRESS, TX_ADR_WIDTH);
	write_cmd(RX_ADDR_P0 | NRF_WRITE_REG, RX_ADDRESS, RX_ADR_WIDTH);
	write_reg(EN_AA, 0);
	write_reg(EN_RXADDR, 3);
	write_reg(SETUP_RETR, 0);
	write_reg(RF_CH, 24);
	write_reg(RX_PW_P0, RX_PLOAD_WIDTH);
	write_reg(RX_PW_P1, RX_PLOAD_WIDTH);
	write_reg(RF_SETUP, 0x27);
	write_reg(CONFIG, 0x0e);
		
	write_reg(7, read_reg(7));	// clear all interrupt

	rf_on(false);

	return 0;
}

int NRF24L01::rf_on(bool rx)		// power up and enter standby-I, should be called only in power down state
{
	write_reg(CONFIG, (read_reg(CONFIG) & 0xfe) | (rx ? 1 : 0));

	ce->write(true);
	return 0;
}

int NRF24L01::rf_off()
{
	ce->write(false);
}

int NRF24L01::write_tx(const uint8_t *data, int count)
{
	write_reg(STATUS, read_reg(STATUS));
	write_cmd(WR_TX_PLOAD, data, count);

	return 0;
}

int NRF24L01::read_rx(uint8_t *data, int maxcount)
{
	if (maxcount > 32)
		maxcount = 32;

	read_cmd(RD_RX_PLOAD, data, maxcount);

	return maxcount;
}

int NRF24L01::power_on()		// power up and enter standby-I, should be called only in power down state
{
	write_reg(CONFIG, read_reg(CONFIG) | 2);

	return 0;
}
int NRF24L01::power_off()	// power down the whole chip.
{
	write_reg(CONFIG, read_reg(CONFIG) & (~2));
	return 0;
}


int NRF24L01::write_cmd(uint8_t cmd, const uint8_t *data, int count)
{
	cs->write(false);
	spi->txrx(cmd);
	for(int i=0; i<count; i++)
		spi->txrx(data[i]);
	cs->write(true);

	return 0;
}

int NRF24L01::read_cmd(uint8_t cmd, uint8_t *data, int count)
{
	cs->write(false);
	spi->txrx(cmd);
	for(int i=0; i<count; i++)
		data[i] = spi->txrx(0);
	cs->write(true);

	return 0;
}

uint8_t NRF24L01::read_cmd(uint8_t cmd)
{
	uint8_t v;
	read_cmd(cmd, &v, 1);

	return 1;
}
void NRF24L01::write_cmd(uint8_t cmd, uint8_t data)
{
	write_cmd(cmd, &data, 1);
}

uint8_t NRF24L01::read_reg(uint8_t cmd)
{
	uint8_t v;
	read_cmd(cmd & 0x1f, &v, 1);

	return v;
}
void NRF24L01::write_reg(uint8_t cmd, uint8_t data)
{
	write_cmd((cmd & 0x1f) | NRF_WRITE_REG, &data, 1);
}

}