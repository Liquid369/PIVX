# Tor Wallet and Masternode Setup

- [Tor Wallet and Masternode Setup](#tor-wallet-and-masternode-setup)
  - [Installing Tor](#installing-tor)
    - [MacOS](#macos)
  - [Configuring Tor Process](#configuring-tor-process)
    - [Cookie Authentication](#cookie-authentication)
      - [Mac Cookie Config](#mac-cookie-config)
    - [Hidden Service Directory](#hidden-service-directory)
    - [Hidden Service Port](#hidden-service-port)
  - [Managing Tor Process](#managing-tor-process)
    - [Mac](#mac)
  - [Configuring Core Wallet](#configuring-core-wallet)
    - [Core Wallet PIVX.conf](#core-wallet-pivxconf)
  - [Configuring Masternodes](#configuring-masternodes)
    - [Masternode Wallet PIVX.conf](#masternode-wallet-pivxconf)

## Installing Tor
The TOR project has become more simplified in its releases over time to where it is for many much easier to setup the TOR daemon and configure the service with minimal work. We have gathered information in the basic configuration for multiple OS types, below you can check your corresponding section.

### MacOS
```brew install tor```

## Configuring Tor Process
Based on your needs, configuring the TOR process is not that difficult thankfully. In most regards configuring the Hidden Service and Port is majority necessary to mess with. You can find each portion below

For Mac users the directories for the Config and TOR are as follows:

Config File:
```/etc/tor/torrc```

Service Directory:
```/var/lib/tor/```

### Cookie Authentication
Cookie Authentication is a must for all for security purposes, so we would want to modify the config using a text editor. Copy the lines below into the torrc file and save it. Keep the file open as in the lower sections we will add more to it based on your needs.

#### Mac Cookie Config
Directory for config is ```/etc/tor/torrc```

```
ControlPort 9051
CookieAuthentication 1
CookieAuthFileGroupReadable 1
```

### Hidden Service Directory
In these next two sections we will not divie the tor config file up for other distros because at this point if you have made it, you should have it open in a text editor ready for the next portions. It is also the same for all.

```
HiddenServiceDir /var/lib/tor/pivx-service
```

Copy these lines into your torrc configuration file. 

### Hidden Service Port
Hidden Service port is where you will define the PIVX Port and a localhost IP:PORT combination to route traffic for your node(s).

```
HiddenServicePort 51472 127.0.0.1:10000
HiddenServiceVersion 3
```

Multiple HiddenServicePort lines will allow for configuration in multiple daemons running on a single server/computer using Tor. 

For example you can do like so
```
HiddenServicePort 51472 127.0.0.1:10000
HiddenServicePort 51472 127.0.0.1:10001
HiddenServicePort 51472 127.0.0.1:10002
HiddenServiceVersion 3
```

This will allow you to then configure your nodes with different port options to run more than one daemon.

The final configuration should look something like below
```
ControlPort 9051
CookieAuthentication 1
CookieAuthFileGroupReadable 1
HiddenServiceDir /var/lib/tor/pivx-service
HiddenServicePort 51472 127.0.0.1:10000
HiddenServiceVersion 3
```
**NOTE:** The config must be in this format/order. Remember you can have as many HiddenServicePorts as you would like for multiple redirects to multiple wallets setup, they just have to be before HiddenServiceVersion.

## Managing Tor Process
After you have created/saved/modified your torrc config file we must restart the process. The commands are interchangable such as ```start```, ```stop```, and ```restart```.

### Mac
```brew services restart tor```

## Configuring Core Wallet
Core Wallet Configuration is important because we want to connect to the TOR Service alongside potentially running more than 1 wallet.

### Core Wallet PIVX.conf
Below is a sample configuration:
```
rpcuser=123456
rpcpassword=123456789
daemon=1
server=1
proxy=127.0.0.1:9050
listen=1
rpcport=12001
rpcallowip=127.0.0.1
port=10000
```
```RPCPort=``` and ```Port=``` must be a different port for each node. The ```Port=``` option must match a HiddenServicePort as defined in your Tor config.

## Configuring Masternodes
Configuring Masternodes is also very important to make sure that we are properly routing information so the Masternodes are available to the network and giving some users the capability to run more than one per server.

### Masternode Wallet PIVX.conf
In order to get your Onion address, you can load your wallet without the masternode params and use the RPC command ```getnetworkinfo```

Response example:
```
getnetworkinfo
{
  "version": 5050000,
  "subversion": "/PIVX Core:5.5.0/",
  "protocolversion": 70926,
  "localservices": "0000000000000005",
  "timeoffset": 0,
  "networkactive": true,
  "connections": 16,
  "networks": [
    {
      "name": "ipv4",
      "limited": false,
      "reachable": true,
      "proxy": "127.0.0.1:9050",
      "proxy_randomize_credentials": true
    },
    {
      "name": "ipv6",
      "limited": false,
      "reachable": true,
      "proxy": "127.0.0.1:9050",
      "proxy_randomize_credentials": true
    },
    {
      "name": "onion",
      "limited": false,
      "reachable": true,
      "proxy": "127.0.0.1:9050",
      "proxy_randomize_credentials": true
    }
  ],
  "relayfee": 0.00010000,
  "localaddresses": [
     {
      "address": "oyie3w4wutittqgr2usb3ieyhib32sb3n4jpbquwf7vfvbmsvakjazad.onion",
      "port": 51472,
      "score": 4
    }
  ],
  "warnings": ""
}
```
You can see your Tor address in the field ```"address":``` that contains the long string ending in .onion

Below is a sample configuration:
```
rpcuser=123456
rpcpassword=123456789
daemon=1
server=1
proxy=127.0.0.1:9050
listen=1
rpcport=12001
rpcallowip=127.0.0.1
port=10000
masternode=1
masternodeaddr=<onion_address>:51472
masternodeprivkey=<mastrnodeprivkey>
```

```RPCPort=``` and ```Port=``` must be a different port for each node. The ```Port=``` option must match a HiddenServicePort as defined in your Tor config.