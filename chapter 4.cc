//-------------Common Access List Control (ACL)---------------------//
//Remember: Standard ACL 1-99 and 1300-1999
//			Extended ACL 100-199 and 2000-2699 
			
//Extended ACLs are placed on routers as close as possible to the source that is being filtered
//Standard ACLs are placed as close to the destination as possible
Router(config)# access-list {1-99} {permit | deny} source-addr [source-wildcard] //standart ACL permit or deny traffic based on source address.
Router(config)# access-list {100-199} {permit | deny} protocol source-addr [source-wildcard] [operator operand] destination-addr [destination-wildcard] [operator operand] [established] //Extended ACL match packets based on Layer 3 and Layer 4 source and destination information

Router(config-if)# ip access-group access-list-number {in | out} //to apply the ACL to an interface
Router(config-line)# access-class access-list-number {in | out} //to apply the ACL to a vty line

Router(config)# ip access-list [standard | extended] name_of_ACL //Named ACL
Router(config-std-nacl)# deny {source [source-wildcard] | any}
Router(config-std-nacl)# permit {source [source-wildcard] | any}

Router(config-ext-nacl)# {permit | deny} protocol source-addr [source-wildcard] [operator operand] destination-addr [destination-wildcard] [operator operand] [established]

Router(config-if)# ip access-group access-list-name {in | out} //to apply the named ACL to an interface
Router(config-line)# access-class access-list-name {in | out} //to apply the named ACL to a vty line

/*
At the end of an ACL statement, the administrator has the option to configure the log parameter.
Several pieces of information are logged:
	■	Action - permit or deny 
	■	Protocol - TCP, UDP, or ICMP 
	■	Source and destination addresses 
	■	For TCP and UDP - source and destination port numbers 
	■	For ICMP - message types
	
Note: The log parameter should be used only when the network is under attack and an administrator is trying to determine who the attacker is.
*/
Router# show ip access-list //used as a basic means of checking the intended effect of an ACL
//-------------Common Access List Control (ACL)---------------------//
//-------------TCP Established and Reflexive ACL--------------------//
Router(config)# access-list {100-199} {permit | deny} protocol source-addr [source-wildcard] [operator operand] destination-addr [destination-wildcard] [operator operand] [established] //TCP Established

Router(config)# ip access-list extended internal_ACL_name //Reflexive Internal ACL
Router(config-ext-nacl)# permit protocol source-addr [source-mask] [operator operand] destination-addr [destination-mask] [operator operand] [established] reflect reflexive_ACL_name [timeout seconds]

//An example
R1(config)# ip access-list extended internal_ACL 
R1(config-ext-nacl)# permit tcp any any eq 80 reflect web-only-reflexive-ACL 
R1(config-ext-nacl)# permit udp any any eq 53 reflect dns-only-reflexive-ACL timeout 10

Router(config)# ip access-list extended external_ACL_name //Reflexive External ACL
Router(config-ext-nacl)# evaluate reflexive_ACL_name

//Another example
R1(config)# ip access-list extended external_ACL
R1(config-ext-nacl)# evaluate web-only-reflexive-ACL 
R1(config-ext-nacl)# evaluate dns-only-reflexive-ACL 
R1(config-ext-nacl)# deny ip any any

R1(config)# interface s0/0/0 //to assign the reflexive ACL to an interface
R1(config-if)# description connection to the ISP. 
R1(config-if)# ip access-group internal_ACL out 
R1(config-if)# ip access-group external_ACL in
//-------------TCP Established and Reflexive ACL--------------------//
//------------------------Dynamic ACL-------------------------------//
Router(config)# access-list {100-199} dynamic dynamic_ACL_name [timeout minutes] {permit | deny} protocol source-addr [source-wildcard] [operator operand] destination-addr [destination-wildcard] [operator operand] [established]
//The timeout can range from 1 to 9999 minutes.

Router(config)# line vty 0 4
Router(config-line)# autocommand access-enable host [timeout minutes] //to enable lock-and-key authentication on the vty lines
//------------------------Dynamic ACL-------------------------------//
//----------------------Time Based ACL------------------------------//
Router(config)# time-range time_range_name //The time_range_name must begin with a letter and cannot contain a space
//two types of ranges can be specified: one-time only (absolute) and recurring (periodic).
Router(config-time-range)# absolute [start_time start_date] [end_time end_date] 
Router(config-time-range)# periodic day_of_the_week hh:mm to [day_of_the_week] hh:mm

Router(config)# access-list {100-199} {permit | deny} protocol source-addr [source-mask] [operator operand] destination-addr [destination-mask] [operator operand] [established][log | log-input][established][time-range name_of_time_range]
//An example
R1(config)# time-range employee-time 
R1(config-time-range)# periodic weekdays 12:00 to 13:00 
R1(config-time-range)# periodic weekdays 17:00 to 19:00 
R1(config-time-range)# exit 
R1(config)# access-list 100 permit ip 192.168.1.0 0.0.0.255 any time-range employee-time 
R1(config)# access-list 100 deny ip any any R1(config)# interface FastEthernet 0/1 
R1(config-if)# ip access-group 100 in 
R1(config-if)# exit
//----------------------Time Based ACL------------------------------//
//--------------------TSHOOT Complex ACL----------------------------//
Router# show access-lists [access-list-number | access-list-name] //shows how many packets have been matched against each entry in the ACLs
Router# debug ip packet [access-list-number] [detail] //for analyzing the messages traveling between the local and remote hosts
//The detail option displays detailed IP packet debugging information
//--------------------TSHOOT Complex ACL----------------------------//
//-----------------Define inspection Rules--------------------------//
Router(config)# ip inspect name "inspection_name protocol" [alert {on | off}] [audit-trail {on | off}] [timeout seconds] //to define inspection rule
//Examples
Router(config)# ip inspect name FWRULE ftp alert on audit-trail on timeout 300
//Examples
Router(config)# ip inspect name PERMIT_JAVA http java-list 10
Router(config)# access-list 10 permit 10.224.10.0 0.0.0.255
//Examples
Router(config)# ip inspect name in2out ftp

Router(config-if)# ip inspect "inspection_name" {in | out} //to activate an inspection rule on an interface

Router(config)# no ip inspect //to remove CBAC from the router
//removes all CBAC commands, the state table, and all temporary ACL entries cre- ated by CBAC. 
//It also resets all timeout and threshold values to their factory defaults
//-----------------Define inspection Rules--------------------------//
//----------------------TSHOOT CBAC---------------------------------//
//CBAC inspection supports two types of logging functions: alerts and audits
Router(config)# ip inspect alert-off //to disable alerts, enabled by default
Router(config)# ip inspect audit-trail //to enable audits, disabled by default

Router# show ip inspect //to view information about CBAC Operation
Router# show ip inspect name inspect_outbound //shows the inspection rules configured for the inspect_outbound inspection rule.
Router# show ip inspect sessions //to view information about Established sessions

Router# debug ip inspect //inspect various applications and other operation details.
Router# debug ip inspect protocol "parameter" //cuseeme, dns, ftp-cmd, ftp-token, h323, http, netshow, rcmd, realaudio, rpc, rtsp, sip, skinny, smtp, sqlnet, streamworks, tftp, and vdolive.
Router# debug ip inspect timers //when idle timeouts are reached.
Router# debug policy-firewall //replaces the debug ip inspect command
//----------------------TSHOOT CBAC---------------------------------//
//----------------Zone-Based Policy Firewall------------------------//
//actions when configured using Cisco SDM are: inspect, drop and pass
Router(config)# zone security "zone name"//to create the zones for the firewall
Router(config-sec-zone)# description "line-of-descriptions"
Router(config)# class-map type inspect [match-any | match-all] "class-map-name"//to define traffic classes
Router(config-cmap)# match access-group {access-group | name access-group-name} //to referencing access lists from within the class map
Router(config-cmap)# match protocol "protocol-name" //Protocols are matched from within the class map 
Router(config-cmap)# match class-map "class-map-name" //Nested class maps can be configured
Router(config)# policy-map type inspect //to specify firewall policies
Router(config)# zone-pair security //to apply firewall policies to pairs of source and destination zones
Router(config-if)# zone-member security //to assign router interfaces to zones

//Specify Firewall Policies ... The options are pass, inspect, drop, and police.
Router(config)# policy-map type inspect "policy-map-name" //to create ZPF policy maps
Router(config-pmap)# class type inspect "class-name" //Traffic classes on which an action must be performed are specified within the policy map.
Router(config-pmap)# class class-default //The default class (matching all remaining traffic) is specified using this command.
Router(config-pmap-c)# pass | inspect | drop [log] | police //the action to take on the traffic is specified.

//Apply Firewall Policies
Router(config)# zone-pair security "zone-pair-name" [source source-zone-name | self] destination [self | destination-zone-name] //the administrator applies it to traffic between a pair of zones
Router(config-pmap-c)# service-policy {h323 | http | im | imap | p2p | pop3 | sip | smtp | sunrpc | urlfilter} policy-map //to attach a policy-map and its associated actions to a zone-pair

Router(config-if)# zone-member security "zone-name" //to assign the appropriate security zones in the interface.

Router# show policy-map type inspect zone-pair session //to examine the active connections in the ZPF state table
//----------------Zone-Based Policy Firewall------------------------//
