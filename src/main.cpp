#if !DEVICE_CAN
#error [NOT_SUPPORTED] CAN not supported for this target
#endif

#include "mbed.h"
#include "InterfaceCAN.h"

#if defined(TARGET_LPC1768)
  CAN canBus(p30, p29);     // RD, TX => LPC
#elif defined(TARGET_NUCLEO_L476RG)
  CAN canBus(D15, D14);     // RD, TX => NUCLEO
#endif

Timer timer;
std::chrono::microseconds previousTime;

void can_receive() {
  CANMessage msg;

  if (canBus.read(msg)) {
    if (msg.len < 3) {
      printf("[ERROR] Received invalid CAN message\r\n");
      return;
    }

    auto now = timer.elapsed_time();
    
    printf("\r\n_%llums_ (%llums since previous) CAN message received [length = %d bytes]:\r\n",
        std::chrono::duration_cast<std::chrono::milliseconds>(now).count(),
        std::chrono::duration_cast<std::chrono::milliseconds>(now - previousTime).count(),
        msg.len
      );
    printf("-----------------------------------------------------------------------------------------------\r\n");
    printf("| DESTINATION ID | SOURCE ID | ENTITY ID | BASE_TYPE | SUB_TYPE | DATA (%d bytes)\r\n", (msg.len-3));
    printf("|      %3d       |   %3d     |   %3d     |    0x%02x   |   0x%02x   |",
      msg.id,
      msg.data[0],
      msg.data[1],
      ((msg.data[2] >> 4)&0x0F),
      ((msg.data[2])&0x0F)
    );
    for (int i = 0; i < (msg.len-3); i++) {
      printf(" 0x%02x ", msg.data[3+i]);
    }
    printf("\r\n");
    printf("-----------------------------------------------------------------------------------------------\r\n");

    previousTime = now;
  }
}

int main() {
  previousTime = timer.elapsed_time();

  ThisThread::sleep_for(5s);

  printf("----------------------------------------------------------------------------------\r\n");
  printf("\r\n");
  printf(".______    __    __       ___           _______.\r\n");
  printf("|   _  \\  |  |  |  |     /   \\         /       |\r\n");
  printf("|  |_)  | |  |__|  |    /  ^  \\       |   (----`\r\n");
  printf("|   _  <  |   __   |   /  /_\\  \\       \\   \\    \r\n");
  printf("|  |_)  | |  |  |  |  /  _____  \\  .----)   |   \r\n");
  printf("|______/  |__|  |__| /__/     \\__\\ |_______/    \r\n");
  printf("                                                \r\n");
  printf("  ______     ___      .__   __.                 \r\n");
  printf(" /      |   /   \\     |  \\ |  |                 \r\n");
  printf("|  ,----'  /  ^  \\    |   \\|  |                 \r\n");
  printf("|  |      /  /_\\  \\   |  . `  |                 \r\n");
  printf("|  `----./  _____  \\  |  |\\   |                 \r\n");
  printf(" \\______/__/     \\__\\ |__| \\__|                 \r\n");
  printf("                                                \r\n");
  printf(" _______   __    __  .___  ___. .______         \r\n");
  printf("|       \\ |  |  |  | |   \\/   | |   _  \\        \r\n");
  printf("|  .--.  ||  |  |  | |  \\  /  | |  |_)  |       \r\n");
  printf("|  |  |  ||  |  |  | |  |\\/|  | |   ___/        \r\n");
  printf("|  '--'  ||  `--'  | |  |  |  | |  |            \r\n");
  printf("|_______/  \\______/  |__|  |__| | _|            \r\n");
  printf("\r\n");
  printf("----------------------------------------------------------------------------------\r\n");
  printf("\r\n");
  // https://patorjk.com/software/taag
  // Font Name: Star Wars

  timer.start();

  canBus.frequency(100*1000);

  while(true) {
    can_receive();
  }

  return 0;
}