
#include <stdint.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#define TRUE 1
#define FALSE 0

#define I2C_M_NOSTOP 0x0040 

struct i2c_msg {
	__u16 addr;
	__u16 flags;
	__u16 len;
	__u8 *buf;
};

///////////////////////////////////////////////////////////////////////////////
int writeIoctl(int file_i2c, struct i2c_msg *msg)
{
  struct i2c_rdwr_ioctl_data msgset[1];

  msgset[0].msgs = msg;
  msgset[0].nmsgs = 1;

  if (ioctl(file_i2c, I2C_RDWR, &msgset) < 0)
  {
    printf("Failed to write to the i2c bus.\n");
    return FALSE;
  }

  printf("writeBytes complete\n");

  return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
int setup(char* filename, int addr)
{
  int file_i2c = 0;
  if ((file_i2c = open(filename, O_RDWR)) < 0) 
  {
    printf("Failed to open the i2c bus");
    return FALSE;
  }

  if (ioctl(file_i2c, I2C_SLAVE, addr) < 0) 
  {
    printf("Failed to acquire bus access and/or talk to slave.\n");
    close(file_i2c);
    return FALSE;
  }

  printf("Setup complete\n");
  return file_i2c;
}

///////////////////////////////////////////////////////////////////////////////
int main(void)
{
  int addr = 0x09;
  int file_i2c = setup("/dev/i2c-0", addr);
  struct i2c_msg msg[1];

  if (file_i2c < 0)
  {
    return 1;
  }

  unsigned char buffer[60];
  int length=2;
  uint8_t reg = 0x33;
  buffer[0] = reg; //reg
  buffer[1] = reg; //data

  msg[0].buf = buffer;
  msg[0].len = length;
  msg[0].flags = I2C_M_NOSTOP;
  msg[0].addr = addr;

  if (writeIoctl(file_i2c, &msg[0]) == FALSE)
  {
    return 1;
  }

  sleep(1000);

  close(file_i2c);

  return 0;
}
