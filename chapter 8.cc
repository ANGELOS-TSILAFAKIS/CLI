//--------------Configuring a Site-to-Site GRE Tunnel----------//
Router(config)# interface tunnel 0 //to create a tunnel interface
Router(config-if)# ip address "ip-address" "netmask" // to assign the ip address
Router(config-if)# tunnel source //to identify the source tunnel interface
Router(config-if)# tunnel destination //to identify the destination tunnel interface
Router(config-if)# tunnel mode gre //to configure which protocol GRE will encapsulate

/*
Note.:
-> GRE are that it can be used to tunnel non-IP traffic over an IP network.
-> IPsec, which only supports unicast traffic, GRE supports multicast and broadcast traffic over the tunnel link.
-> Routing protocols are supported in GRE.
-> GRE does not provide encryption
*/

//----------IPsec VPN Components and Operation----------------//
/*
	IPsec provides these essential security functions:
	Confidentiality -> DES, 3DES, AES, SEAL
	Integrity -> HMAC-MD5, HMAC-SHA-1
	Authentication -> PSK, RSA
	Secure Key Exchange -> DH group 1, 2, 5, 7
		DH groups 1, 2, and 5 support exponentiation over a prime modulus with a key size of 768 bits, 1024 bits, and 1536 bits, respectively.
		Cisco 3000 clients support DH groups 1, 2, and 5. DES and 3DES encryption support DH groups 1 and 2.
		AES encryption supports DH groups 2 and 5.
		Group 7 supports Elliptical Curve Cryptography (ECC), which reduces the time needed to generate keys.
		
	
	Authentication Header (AH) ->  is the appropriate protocol to use when confidentiality is not required or permitted.
	AH supports the HMAC-MD5 and HMAC-SHA-1 algorithms. AH can have problems if the envi- ronment uses NAT.
	Encapsulating Security Payload (ESP) -> can provide confidentiality and authentication.
	
	ESP transport mode is used between hosts. Transport mode works well with GRE, because GRE hides the addresses of the end devices by adding its own IP.
	ESP tunnel mode is used between a host and a security gateway or between two security gateways.
	
	Internet Security Association and Key Management Protocol (ISAKMP)
*/
//---------Implementing Site-to-Site IPsec VPNs with CLI-----------//
Router(config)#access-list acl permit ahp "source" "wildcard" "destination" "wildcard" //to permit AH Traffic
Router(config)#access-list acl permit esp "source" "wildcard" "destination" "wildcard" //to permit ESP Traffic
Router(config)#access-list acl permit udp "source" "wildcard" "destination" "wildcard" eq isakmp //to permit ISAKMP Traffic

Router(config)#crypto isakmp policy "priority" //to create a ISAKMP policy with priority (1...10000, highest...lowest)
Router(config)#crypto isakmp key "keystring" address "peer-address" //to configure a PSK
Router(config)#crypto ipsec transform-set transform-set-name transform1 [transform2] [transform3] [transform4] //To define a transform set

Router(config)#crypto map "map-name" "seq-num" cisco 
Router(config)#crypto map "map-name" "seq-num" ipsec-manual 
Router(config)#crypto map "map-name" "seq-num" ipsec-isakmp [dynamic dynamic-map-name] 
Router(config)#no crypto map "map-name" [seq-num]

Router(config-if)#crypto map "map-name" //The crypto map is applied to the outgoing interface of the VPN tunnel

//--------Verify and Troubleshoot the IPsec Configuration---------------//
Router# show crypto map //this command verifies the configurations and show the SAs lifetime
Router# show crypto isakmp policy //to display configured IKE policies and the default IKE policy settings
Router# show crypto ipsec transform-set //to show all configured transform sets.
Router# show crypto ipsec sa //If the output indicates that an SA is established, the rest of the configuration is assumed to be working
Router# show crypto isakmp sa //This command displays all current IKE SAs.
Router# debug crypto isakmp //displays detailed information about the IKE Phase 1 and IKE Phase 2 negotiation processes.
Router# debug crypto ipsec //displays detailed information about IPsec events.
