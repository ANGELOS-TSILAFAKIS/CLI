/*
IPS - Intrusion Prevention System

A signature is tuned to one of four levels (listed alphabetically), based on the perceived severity of the signature:
	High - Attacks used to gain access or cause a DoS attack are detected, and an immediate threat is extremely likely.
	Informational - Activity that triggers the signature is not considered an immediate threat, but the information provided is useful information.
	Low - Abnormal network activity is detected that could be perceived as malicious, but an immediate threat is not likely.
	Medium - Abnormal network activity is detected that could be perceived as malicious, and an immediate threat is likely.
	
There are several factors to consider when implementing the alarms that a signature uses: 
	The level assigned to the signature determines the alarm severity level.
	When tuning a signature alarm, the severity level of the signature should be the same as the severity level of the alarm.
	To minimize false positives, the administrator must study the existing network traffic patterns and then tune the signatures to recognize intrusion patterns that are atypical (out of character).
	
A false positive alarm occurs when an intrusion system generates an alarm after processing normal user traffic that should not have resulted in the alarm.
A true negative describes a situation in which normal network traffic does not generate an alarm.
A false negative is when an intrusion system fails to generate an alarm after processing attack traffic that the intrusion system is configured to detect
A true positive describes a situation in which an in- trusion system generates an alarm in response to known attack traffic.

Several actions can be performed:
	Generate an alert.
	Log the activity.
	Drop or prevent the activity.
	Reset a TCP connection.
	Block future activity.
	Allow the activity.

Secure Device Event Exchange (SDEE)

To implement IOS IPS: 
Step 1. Download the IOS IPS files. 
Step 2. Create an IOS IPS configuration directory in flash. 
Step 3. Configure an IOS IPS crypto key. 
Step 4. Enable IOS IPS. 
Step 5. Load the IOS IPS signature package to the router.

*/
Router(config)# no crypto key pubkey-chain rsa //to remove the key
Router(config)# no named-key realm-cisco.pub signature //to reconfigure the key

//Identify the IPS rule name and specify the location.
Use the ip ips name [rule name] [optional ACL] command to create a rule name. An optional extended or standard access control list (ACL) can be configured to filter the scanned traffic. 
All traffic that is permitted by the ACL is subject to inspection by the IPS. Traffic that is denied by the ACL is not inspected by the IPS. Use the ip ips config location flash:directory-name command to configure the IPS signature storage location. 
Prior to IOS 12.4(11)T, the ip ips sdf location command was used.

//Enable SDEE and logging event notification.
To use SDEE, the HTTP server must first be enabled with the ip http server command. If the HTTP server is not enabled, the router cannot respond to the SDEE clients because it cannot see the requests. 
SDEE notification is disabled by default and must be explicitly enabled. Use the ip ips notify sdee command to enable IPS SDEE event notification. IOS IPS also supports logging to send event notification. 
SDEE and logging can be used independently or enabled at the same time. Logging notification is enabled by default. If the logging console is enabled, IPS log messages are displayed on the console. 
Use the ip ips notify log command to enable logging.

//Configure the signature category.
All signatures are grouped into categories, and the categories are hierarchical. This helps classify signatures for easy grouping and tuning. 
The three most common categories are all, basic, and advanced.

Router(config)# ip ips signature-category //to enter the ips category mode
Router(config-ips-category)# category "category-name" //to change a category
Router(config-ips-category)# category all //to enter IPS category all action mode
Router(config-ips-category-action)# retired true //To retire a category
Router(config-ips-category-action)# retired false //to unretire a category

Caution: Do not unretire the all category. The all signature category contains all signatures in a signature release. 
The IOS IPS cannot compile and use all the signatures at one time, because it will run out of memory

Router(config-if)# ip ips "rule-name" [in|out] //to apply the ips rule to the interface
Router# show ip ips signature count //to verify that the signature package is properly compiled

Router(config-if)# ip virtual-reassembly //to enable Virtual Fragment Reassembly (VFR) on the interface
Router(config-ips-category-action)# event-action {produce-alert, deny-packet-in- line, reset-tcp-connection}//to change an action

//Verify and Monitor IOS IPS
Router# show ip	ips	all //displays all IPS configuration data
Router# show ip	ips	configuration //displays additional configuration data that is not displayed with the show running-config
Router# show ip	ips	interfaces //displays interface configuration data.
Router# show ip	ips	signatures {detail} //verify the signature configuration.
Router# show ip	ips	statistics {reset} //displays the number of packets audited and the number of alarms sent.
Router# clear ip ips configuration //to disable IPS, remove all IPS configuration entries, and release dynamic resources.
Router# clear ip ips statistics //resets statistics on packets analyzed and alarms sent.

Router(config)# ip ips notify [log|sdee] //To specify the method of event notification
Router(config)# ip sdee events "events" //to altere the default buffer size
Router# clear ip ips sdee {events | subscription} //to clears SDEE events or subscriptions
