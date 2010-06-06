Router# configure terminal 
Router(config)# login block-for "seconds" attempts tries within "seconds" 
Router(config)# login quiet-mode access-class "{acl-name | acl-number}" 
Router(config)# login delay "seconds" 
Router(config)# login on-failure log
Router(config)# login on-success log

security authentication failure rate threshold-rate log //generate log when login failure rate is exceeded
show login // normal or quiet mode
show login failure //show the IP address from which the failed login attempts originated

banner {exec | incoming | login | motd | slip-ppp} d message d
$(hostname) - Displays the host name for the router.
$(domain) - Displays the domain name for the router.
$(line) - Displays the vty or tty (asynchronous) line number.
$(line-desc) - Displays the description that is attached to the line.
//--------------------Configuring SSH--------------------------//
Router# configure terminal 
Router(config)# ip domain-name "nombre del dominio"
Router(config)# crypto key generate rsa general-keys modulus "modulus-size" //minimum recommended length 1024
Router(config)# crypto key zeroize rsa //to clean existing keys
Router# show crypto key mypubkey rsa //display generated keys
Router(config)# username "usuario" secret "password" //local database

Router(config)# line vty 0 4
Router(config-line)# login local
Router(config-line)# transport input ssh

//optional
Router(config)# ip ssh version {1|2}
Router(config)# ip ssh time-out "seconds" //default 120 secs
Router(config)# ip ssh authentication-retries "integer" //default 3 attempts
Router# show ip ssh //to verify optional settings
Router# show ssh //verify the status of clients connections

Cisco SDM
Configure > Additional Tasks > Router Access > SSH //to configure SSH daemon
Configure > Additional Tasks > Router Access > VTY //to configure vty lines to support ssh 
//--------------------Configuring SSH--------------------------//
//---------------Assigning Privilege Levels--------------------//
The Cisco IOS Software CLI has two levels
User Exec Mode like router> prompt (privilege level 1)
Privileged Exec Mode router# prompt (privilege level 15)

Router(config)# privilege "mode" {level level command | reset} "command"
Router(config)# enable secret level "level" "password" //to assign password for a level
Router(config)# username "user" privilege "level" secret "password" //to privilege a user for the level

Examples
Router(config)# privilege exec level 5 ping //to assign level 5 the ping command
Router(config)# enable secret level 5 cisco5 //to assign password for level 5
Router(config)# username support privilege 5 secret cisco5 //to assign a specific username to privilege level 5

Router#enable "level" //to switch between privilege levels, by, default enable commands is the same that enable 15
Router# show privilege //display and confirm the current privilege levels
//---------------Assigning Privilege Levels--------------------//
//-----------Configuring Role-Based CLI Access-----------------//
Router(config)# aaa new-model //to enable aaa
Router(config)# enable view //to enter the root view
Router(config)# parser view "view-name" //to create a view (maximum 15 views)
Router(config-parser)# secret "password"
Router(config-parser)# commands parser-mode {include | include-exclusive | exclude} [all] [interface interface-name | command]

Router(config)# enable view
Router(config)# parser view "view-name" superview
Router(config-parser)# secret "password"
Router(config-parser)# view "name" //to assign an existing view

Router# show parser view all //from root view to see a summary of all views
//-----------Configuring Role-Based CLI Access-----------------//
//-----------Cisco IOS Resilent Configuration -----------------//
Router(config)# secure boot-image //hide Cisco IOS
Router(config)# secure boot-config //hide startup-config
Router(config)# no service password-recovery //hide IOS and prevent enter to ROMMON
//-----------Cisco IOS Resilent Configuration -----------------//
//-----------------Syslog Configuration -----------------------//
logging host //set the destination
logging trap "level" //is optional
logging on //to enable logging, if this command is disabled, messages aren't sent
logging buffered
logging monitor
logging
//-----------------Syslog Configuration -----------------------//
//--------------------NTP Configuration -----------------------//
Router(config)# ntp master //on server
Router(config)# ntp server "ip address" //on clients
Router(config)# ntp broadcast client //optional on clients

Router(config)# ntp authenticate
Router(config)# ntp authentication-key "key-value" md5 "word"
Router(config)# ntp trusted-key "key-value"
Router# show ntp associations details
//--------------------NTP Configuration -----------------------//

