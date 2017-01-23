$cat /proc/interrupts (current list of interrupt handlers)

$make
$sudo insmod basic_interrupts.ko

$sudo insmod basic_interrupts.ko IRQN=[Whatever IRQN You like]


$cat /proc/interrupts (this will show our module registered as interrupt handler for that IRQ number)
$dmesg

$sudo rmmod basic_interrupts
$cat /proc/interrupts (module gone)
$make clean

