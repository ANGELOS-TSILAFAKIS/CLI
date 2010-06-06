//------------------Config. Local AAA Authentication with CLI----------------//
Router(config)# aaa new-model //to enable aaa
Router(config)# aaa authentication login "list-name" {local | local-case} {enable | none}//to define auth method
Router(config)# aaa authentication login default method1 ... method4 //default method is automatically applied to all interfaces and lines
Router(config)# aaa local authentication attempts "max-failnumber-of-unsuccessful-attempts" //to secures AAA user accounts by locking out accounts that have excessive failed attempts

Router# show aaa local user lockout //to display a list of all locked-out users
Router# clear aaa local user lockout {username username | all} //to unlock a specific user or to unlock all locked users
Router# show aaa user {all| unique id} //to display the attributes that are collected for an AAA session
Router# show aaa sessions //to show the unique ID of a session

Router# debug aaa authentication // to troubleshooting authentication issues

/*
Radius only encrypt the password, utilizes udp 1645, 1646, 1812, 1813...
TACACS+ encrypt everything, utilizes tcp port 49
*/
//Cisco Access Control Server (ACS) using TACACS+
Router(config)# aaa new-model
Router(config)# tacacs-server host "ip-address" single-connection
Router(config)# tacacs-server key "key"
Router(config)# aaa authentication login default group tacacs+ local-case

//Cisco Access Control Server (ACS) using RADIUS
Router(config)# aaa new-model
Router(config)# radius-server host "ip-address"
Router(config)# radius-server key "key"
Router(config)# aaa authentication login default group radius local-case

//TSHOOT
Router# debug aaa authentication //return PASS or FAIL
Router# debug tacacs
Router# debug tacacs events //command displays the opening and closing of a TCP connection to a TACACS+ server
Router# debug radius

//Authorization and Accounting
Router(config)# aaa authorization {network | exec | commands level} {default | list-name} method1...[method4]
commands level for exec (shell) commands 
exec for starting an exec (shell) 
network for network services (PPP, SLIP, ARAP)
Router(config)# aaa authorization exec default group tacacs+ //An example character mode (exec)
Router(config)# aaa authorization network default group tacacs+ //An example network mode

Router(config)# aaa accounting { network | exec | connection} {default | list-name} {start-stop | stop-only | none} [broadcast] method1...[method4]
Router(config)# aaa accounting exec default start-stop group tacacs+ //to log exec sessions
Router(config)# aaa accounting network default start-stop group tacacs+ //to log network connections

//------------------Config. Local AAA Authentication with CLI----------------//
