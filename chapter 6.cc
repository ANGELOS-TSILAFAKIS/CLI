//---------------------Configuring Port Security---------------------//
switch (config-if)# switchport mode access //to Configure an interface as an access interface
switch (config-if)# switchport port-security //to enabled port-security on the interface
switch (config-if)# switchport port-security [mac-address mac-address [vlan {vlan- id | {access | voice}}]] | [mac-address sticky [mac-address| vlan {vlan-id | {access | voice}}]] [maximum value [vlan {vlan-list | {access | voice}}]]
switch (config-if)# switchport port-security maximum "value" //default value is 1, assign a value between 1 and 132
switch (config-if)# switchport port-security violation {protect | restrict | shutdown | shutdown vlan} //to set violation mode
switch (config)# errdisable recovery cause psecure-violation
switch (config-if)# switchport port-security mac-address "mac-address" //to assign a static mac-address to an interfaces
switch (config-if)# switchport port-security mac-address sticky //to assign a dynamic mac-address to an interfaces
switch (config-if)# no switchport port-security violation {protect | restrict} //to return the violation mode to the default condition (shutdown mode).
switch (config-if)# switchport port-security aging {static | time time | type {absolute | inactivity}} //to enable or disable static aging for the secure port or to set the aging time or type.
//---------------------Verifying Port Security---------------------//
switch# show port-security //to view port security settings for the switch,including violation count, configured interfaces, and security violation actions.
switch# show port-security [interfaceinterface-id] //to view port security settings for the specified interface
switch# show port-security [interface interface-id] address //to view all secure MAC addresses configured on all switch interfaces or on a specified interface with aging informa- tion for each address.
switch (config)# mac address-table notification //to enable the MAC address notification feature on a switch.
//-----------------Configuring BPDU Guard and Root Guard-----------//
switch (config)# spanning-tree portfast default //configures PortFast for all non-trunking ports at once
switch(config-if)# spanning-tree portfast //configures Portfast on an interface.
switch(config)# spanning-tree portfast bpduguard default //to enable BPDU guard on all ports with PortFast enabled.
switch# show spanning-tree summary //to display information about the state of spanning tree
switch(config-if)# spanning-tree guard root //configuring root guard on an interface
//--------------------Configuring Storm Control--------------------//
switch(config-if)# storm-control {{broadcast | multicast | unicast} level {level [level-low] | bps bps [bps-low] | pps pps [pps-low]}} | {action {shutdown | trap}} //to enable storm control
switch# show storm-control [interface] //to verify storm control settings
//------------------Configuring VLAN Trunk Security----------------//
switch(config-if)# switchport mode trunk //cause the interface to become a trunk link.
switch(config-if)# switchport nonegotiate //to prevent the generation of DTP frames.
switch(config-if)# switchport trunk native vlan "vlan_id" //to set the native VLAN on the trunk to an unused VLAN. The default native VLAN is VLAN 1.
//----------Configuring Cisco Switched Port Analyzer---------------//
//with examples
switch(config)# monitor session 1 source vlan 10 rx
switch(config)# monitor session 1 source vlan 20 tx
switch(config)# monitor session 1 destination interface FastEthernet 3/4
switch# show monitor session "session-number" //to verify the span configuration
//------Configuring Cisco Remote Switched Port Analyzer----------//
switch(config)# vlan 100 
switch(config-vlan)# remote-span //to configure the RSPAN VLAN
switch(config-vlan)# exit

switch(config)# monitor session 1 source interface FastEthernet 0/1 
switch(config)# monitor session 1 destination remote vlan 100 reflector-port FastEthernet 0/24 
switch(config)# interface FastEthernet 0/2 
switch(config-if)# switchport mode trunk

switch(config)# monitor session 2 source remote vlan 100 
switch(config)# monitor session 2 destination interface FastEthernet 0/3 
switch(config)# interface FastEthernet 0/2 
switch(config-if)# switchport mode trunk

switch# show monitor //to verify the RSPAN Configuration
switch# show interfaces trunk //to verify the RSPAN Configuration