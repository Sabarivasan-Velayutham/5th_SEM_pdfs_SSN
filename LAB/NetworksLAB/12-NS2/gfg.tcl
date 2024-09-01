#Create a simulator object
set ns [new Simulator]

#Define different colors for data flows (for NAM)
$ns color 1 Red
$ns color 2 Green

#Open the NAM trace file
set nf [open out.nam w]
$ns namtrace-all $nf

#Create trace file 
set tracefile1 [open out.tr w]
$ns trace-all $tracefile1

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


#Create the network nodes
set A [$ns node]
set B [$ns node]
set C [$ns node]
set D [$ns node]
set E [$ns node]
set F [$ns node]

$A label "node 1"
$B label "node 2"
$C label "node 3"
$D label "node 4"
$E label "node 5"
$F label "node 6"

$A label-color red
$B label-color red
$C label-color red
$D label-color blue
$E label-color blue
$F label-color blue


#Create a duplex link between the nodes
#this code block is for graph creation
$ns duplex-link $A $C 800Kb 70ms DropTail
$ns duplex-link $B $C 800Kb 70ms DropTail
$ns duplex-link $C $D 500Kb 70ms DropTail
$ns duplex-link $D $E 800Kb 70ms DropTail
$ns duplex-link $D $F 800Kb 70ms DropTail

# The queue size at $R is to be 7, including the packet being sent
$ns queue-limit $C $D 10

#Monitor the queue for link (n2-n3). (for NAM)
$ns duplex-link-op $C $D queuePos 0.5

# some hints for nam
# color packets of flow 0 red
#this code block is for packet traveling animation
$ns duplex-link-op $A $C orient right-down
$ns duplex-link-op $B $C orient right-up
$ns duplex-link-op $C $D orient right
$ns duplex-link-op $D $E orient right-up
$ns duplex-link-op $D $F orient right-down


#Setup a TCP connection
set tcp [new Agent/TCP]
$tcp set class_ 2
$tcp set fid_ 1
$ns attach-agent $A $tcp
set sink [new Agent/TCPSink]
$ns attach-agent $E $sink
$ns connect $tcp $sink


#Setup a FTP over TCP connection
set ftp [new Application/FTP]
$ftp attach-agent $tcp
$ftp set type_ FTP


#Setup a UDP connection
set udp [new Agent/UDP]
$udp set fid_ 2
$ns attach-agent $B $udp
set null [new Agent/Null]
$ns attach-agent $F $null
$ns connect $udp $null


#Setup a CBR over UDP connection
set cbr [new Application/Traffic/CBR]
$cbr attach-agent $udp
$cbr set type_ CBR

$cbr set packet_size_ 1000
$cbr set rate_ 1mb
$cbr set random_ false

$ns at 0.1 "$cbr start"
$ns at 0.1 "$ftp start"
$ns at 4.0 "$ftp stop"
$ns at 4.0 "$cbr stop"


#Call the finish procedure after 5 seconds of simulation time
$ns at 5.0 "finish"


$ns run
