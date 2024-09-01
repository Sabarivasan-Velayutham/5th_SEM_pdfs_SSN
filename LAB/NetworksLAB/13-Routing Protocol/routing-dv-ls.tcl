set ns [new Simulator]

$ns color 1 red
$ns color 2 blue

set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]
set n4 [$ns node]
set n5 [$ns node]
set n6 [$ns node]
set n7 [$ns node]


set nr [open out.tr w]
$ns trace-all $nr
set nf [open out.nam w]
$ns namtrace-all $nf

#Define a 'finish' procedure
proc finish {} {
        global ns nf
        $ns flush-trace
        #Close the NAM trace file
        close $nf
        #Execute NAM on the trace file
        exec nam out.nam &
        exit 0
}

$ns duplex-link $n0 $n1 10Mb 10ms DropTail
$ns duplex-link $n0 $n7 5Mb 10ms DropTail
$ns duplex-link $n1 $n2 10Mb 10ms DropTail
$ns duplex-link $n7 $n6 5Mb 10ms DropTail
$ns duplex-link $n2 $n3 10Mb 10ms DropTail
$ns duplex-link $n6 $n5 5Mb 10ms DropTail
$ns duplex-link $n3 $n4 10Mb 10ms DropTail
$ns duplex-link $n5 $n4 5Mb 10ms DropTail



$ns duplex-link-op $n0 $n1 orient left-down
$ns duplex-link-op $n0 $n7 orient right-down
$ns duplex-link-op $n1 $n2 orient down
$ns duplex-link-op $n2 $n3 orient down
$ns duplex-link-op $n3 $n4 orient right-down
$ns duplex-link-op $n7 $n6 orient down
$ns duplex-link-op $n6 $n5 orient down
$ns duplex-link-op $n5 $n4 orient left-down


set udp [new Agent/UDP]
$ns attach-agent $n0 $udp
$udp set fid_ 1

set cbr [new Application/Traffic/CBR]
$cbr set packetSize_ 1000
$cbr set rate_ 0.15mb
$cbr set random_ true
$cbr attach-agent $udp

set null [new Agent/Null]
$ns attach-agent $n4 $null
$ns connect $udp $null


#either comment either one of these 
$ns rtproto LS
#$ns rtproto DV

$ns rtmodel-at 1.0 down $n2 $n3
$ns rtmodel-at 1.0 down $n3 $n4

$ns at 0.0 "$cbr start"
$ns at 3.0 "$cbr stop"
$ns at 5.0 "finish"
$ns run

