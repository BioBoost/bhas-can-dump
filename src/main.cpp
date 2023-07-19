#if !DEVICE_CAN
#error [NOT_SUPPORTED] CAN is not supported for this target
#endif

#include "mbed.h"
#include "InterfaceCAN.h"

DigitalOut activity(LED1);
DigitalOut alive(LED2);
// CAN canBus(D15, D14);     // RD, TX => NUCLEO
CAN canBus(p30, p29);        // RD, TX => LPC
Thread listenerThread;
Timer timer;

void can_listener() {
  CANMessage msg;
  char buffer[64] = {};
  auto previousTime = timer.elapsed_time();

  while(true) {
    activity = false;
    if (canBus.read(msg)) {
      unsigned int offset = 0;
      for (unsigned int i = 0; i < msg.len; i++) {
        offset += sprintf(buffer+offset, "0x%02x ", msg.data[i]);
      }

      auto now = timer.elapsed_time();
      printf("_%llums_ (%llums since previous) CAN message received: [CANID = %d]: %s\r\n",
          std::chrono::duration_cast<std::chrono::milliseconds>(now).count(),
          std::chrono::duration_cast<std::chrono::milliseconds>(now - previousTime).count(),
          msg.id, buffer
        );
      
      previousTime = now;
      activity = true;
    }
    ThisThread::sleep_for(50ms);
  }
}

int main() {
  ThisThread::sleep_for(5s);
  printf("Starting CAN dump ...\r\n");
  timer.start();

  listenerThread.start(can_listener);

  while(true) {
    ThisThread::sleep_for(1s);
    alive = !alive;
  }

  return 0;
}