import time

from gpiozero import Servo
from gpiozero.pins.pigpio import PiGPIOFactory


class Servo180:
    def __init__(self):
        factory = PiGPIOFactory()
        self.servo = Servo(
            18,
            pin_factory=factory,
            min_pulse_width=0.0005,
            max_pulse_width=0.0025,
        )

        self.servo.min()

    def main(self):
        try:
            while True:
                self.servo.min()
                time.sleep(1)
                self.servo.mid()
                time.sleep(1)

        except KeyboardInterrupt:
            servo.detach()


if __name__ == "__main__":
    servo = Servo180()
    servo.main()
